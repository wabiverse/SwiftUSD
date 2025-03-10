//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "Pcp/mapExpression.h"
#include "Pcp/layerStack.h"
#include "Pcp/mapFunction.h"
#include "pxr/pxrns.h"

#include "Trace/traceImpl.h"

#include <OneTBB/tbb/concurrent_hash_map.h>

PXR_NAMESPACE_OPEN_SCOPE

struct Pcp_VariableImpl;

// Add a mapping from </> to </> if the function does not already have one.
static PcpMapFunction _AddRootIdentity(const PcpMapFunction &value)
{
  if (value.HasRootIdentity()) {
    // This function already maps </> to </>; use it as-is.
    return value;
  }
  // Re-create the function with an added root identity mapping.
  PcpMapFunction::PathMap sourceToTargetMap = value.GetSourceToTargetMap();
  SdfPath const &absRoot = SdfPath::AbsoluteRootPath();
  sourceToTargetMap[absRoot] = absRoot;
  return PcpMapFunction::Create(sourceToTargetMap, value.GetTimeOffset());
}

////////////////////////////////////////////////////////////////////////

const PcpMapExpression::Value &PcpMapExpression::Evaluate() const
{
  static PcpMapExpression::Value defaultValue;
  return _node ? _node->EvaluateAndCache() : defaultValue;
}

PcpMapExpression PcpMapExpression::Identity()
{
  static const PcpMapExpression val = Constant(PcpMapFunction::Identity());
  return val;
}

PcpMapExpression PcpMapExpression::Constant(const Value &value)
{
  return PcpMapExpression(_Node::New(_OpConstant, _NodeRefPtr(), _NodeRefPtr(), value));
}

PcpMapExpression PcpMapExpression::Compose(const PcpMapExpression &f) const
{
  // Fast path short-circuits for identities
  if (IsConstantIdentity()) {
    return f;
  }
  if (f.IsConstantIdentity()) {
    return *this;
  }
  if (_node->key.op == _OpConstant && f._node->key.op == _OpConstant) {
    // Apply constant folding
    return Constant(Evaluate().Compose(f.Evaluate()));
  }
  return PcpMapExpression(_Node::New(_OpCompose, _node, f._node));
}

PcpMapExpression PcpMapExpression::Inverse() const
{
  // Fast path short-circuits for identities
  if (IsConstantIdentity()) {
    return *this;
  }
  if (_node->key.op == _OpConstant) {
    // Apply constant folding
    return Constant(Evaluate().GetInverse());
  }
  return PcpMapExpression(_Node::New(_OpInverse, _node));
}

PcpMapExpression PcpMapExpression::AddRootIdentity() const
{
  // Fast path short-circuits for identities
  if (IsConstantIdentity()) {
    return *this;
  }
  if (_node->key.op == _OpConstant) {
    // Apply constant folding
    return Constant(_AddRootIdentity(Evaluate()));
  }
  if (_node->expressionTreeAlwaysHasIdentity) {
    return PcpMapExpression(_node);
  }

  return PcpMapExpression(_Node::New(_OpAddRootIdentity, _node));
}

////////////////////////////////////////////////////////////////////////
// Variable implementation

PcpMapExpression::Variable::~Variable()
{
  // Do nothing
}

// Private implementation for Variable.
struct Pcp_VariableImpl final : PcpMapExpression::Variable {
  ~Pcp_VariableImpl() override {}

  explicit Pcp_VariableImpl(PcpMapExpression::_NodeRefPtr &&node) : _node(std::move(node)) {}

  const PcpMapExpression::Value &GetValue() const override
  {
    return _node->GetValueForVariable();
  }

  void SetValue(PcpMapExpression::Value &&value) override
  {
    _node->SetValueForVariable(std::move(value));
  }

  PcpMapExpression GetExpression() const override
  {
    return PcpMapExpression(_node);
  }

  const PcpMapExpression::_NodeRefPtr _node;
};

PcpMapExpression::VariableUniquePtr PcpMapExpression::NewVariable(Value &&initialValue)
{
  Pcp_VariableImpl *var = new Pcp_VariableImpl(_Node::New(_OpVariable));

  var->SetValue(std::move(initialValue));

  return VariableUniquePtr(var);
}

////////////////////////////////////////////////////////////////////////
// Node

namespace {

template<class Key> struct _KeyHashEq {
  inline bool equal(const Key &l, const Key &r) const
  {
    return l == r;
  }
  inline size_t hash(const Key &k) const
  {
    return k.GetHash();
  }
};

}  // namespace

struct PcpMapExpression::_Node::_NodeMap {
  typedef PcpMapExpression::_Node::Key Key;
  typedef tbb::concurrent_hash_map<Key, PcpMapExpression::_Node *, _KeyHashEq<Key>> MapType;
  typedef MapType::accessor accessor;
  MapType map;
};

TfStaticData<PcpMapExpression::_Node::_NodeMap> PcpMapExpression::_Node::_nodeRegistry;

bool PcpMapExpression::_Node::_ExpressionTreeAlwaysHasIdentity(const Key &key)
{
  switch (key.op) {
    case _OpAddRootIdentity:
      return true;

    case _OpVariable:
      return false;

    case _OpConstant: {
      // Check if this maps </> back to </> -- in which case this
      // has a root identity mapping.
      return key.valueForConstant.HasRootIdentity();
    }

    case _OpCompose:
      // Composing two map expressions may cause the identity
      // mapping to be removed; consider the case where we compose
      // {</>:</>, </A>:</B>} and {</B>:</C>}. The expected result
      // is {</A>:</C>}.
      //
      // In this case, the expression tree will only have an identity
      // mapping if *both* subtrees being composed have an identity.
      return (key.arg1 && key.arg1->expressionTreeAlwaysHasIdentity && key.arg2 &&
              key.arg2->expressionTreeAlwaysHasIdentity);

    default:
      // For any other operation, if either of the subtrees has an
      // identity mapping, so does this tree.
      return (key.arg1 && key.arg1->expressionTreeAlwaysHasIdentity) ||
             (key.arg2 && key.arg2->expressionTreeAlwaysHasIdentity);
  }
}

PcpMapExpression::_NodeRefPtr PcpMapExpression::_Node::New(_Op op_,
                                                           const _NodeRefPtr &arg1_,
                                                           const _NodeRefPtr &arg2_,
                                                           const Value &valueForConstant_)
{
  TfAutoMallocTag2 tag("Pcp", "PcpMapExpresion");
  const Key key(op_, arg1_, arg2_, valueForConstant_);

  if (key.op != _OpVariable) {
    // Check for existing instance to re-use
    _NodeMap::accessor accessor;
    if (_nodeRegistry->map.insert(accessor, key) || accessor->second->_refCount.fetch_add(1) == 0)
    {
      // Either there was no node in the table, or there was but it had
      // begun dying (another client dropped its refcount to 0).  We have
      // to create a new node in the table.  When the client that is
      // killing the other node it looks for itself in the table, it will
      // either not find itself or will find a different node and so won't
      // remove it.
      _NodeRefPtr newNode{TfDelegatedCountIncrementTag, new _Node(key)};
      accessor->second = newNode.get();
      return newNode;
    }
    return {TfDelegatedCountDoNotIncrementTag, accessor->second};
  }
  return {TfDelegatedCountIncrementTag, new _Node(key)};
}

PcpMapExpression::_Node::_Node(const Key &key_)
    : key(key_), expressionTreeAlwaysHasIdentity(_ExpressionTreeAlwaysHasIdentity(key))
{
  _hasCachedValue = false;
  _refCount = 0;
  if (key.arg1) {
    tbb::spin_mutex::scoped_lock lock(key.arg1->_mutex);
    key.arg1->_dependentExpressions.insert(this);
  }
  if (key.arg2) {
    tbb::spin_mutex::scoped_lock lock(key.arg2->_mutex);
    key.arg2->_dependentExpressions.insert(this);
  }
}

PcpMapExpression::_Node::~_Node()
{
  if (key.arg1) {
    tbb::spin_mutex::scoped_lock lock(key.arg1->_mutex);
    key.arg1->_dependentExpressions.erase(this);
  }
  if (key.arg2) {
    tbb::spin_mutex::scoped_lock lock(key.arg2->_mutex);
    key.arg2->_dependentExpressions.erase(this);
  }

  if (key.op != _OpVariable) {
    // Remove from node map if present.
    _NodeMap::accessor accessor;
    if (_nodeRegistry->map.find(accessor, key) && accessor->second == this) {
      _nodeRegistry->map.erase(accessor);
    }
  }
}

const PcpMapExpression::Value &PcpMapExpression::_Node::EvaluateAndCache() const
{
  if (_hasCachedValue) {
    return _cachedValue;
  }

  TRACE_SCOPE("PcpMapExpression::_Node::EvaluateAndCache - cache miss");
  Value val = _EvaluateUncached();
  tbb::spin_mutex::scoped_lock lock(_mutex);
  if (!_hasCachedValue) {
    _cachedValue = val;
    _hasCachedValue = true;
  }
  return _cachedValue;
}

PcpMapExpression::Value PcpMapExpression::_Node::_EvaluateUncached() const
{
  switch (key.op) {
    case _OpConstant:
      return key.valueForConstant;
    case _OpVariable:
      return _valueForVariable;
    case _OpInverse:
      return key.arg1->EvaluateAndCache().GetInverse();
    case _OpCompose:
      return key.arg1->EvaluateAndCache().Compose(key.arg2->EvaluateAndCache());
    case _OpAddRootIdentity:
      return _AddRootIdentity(key.arg1->EvaluateAndCache());
    default:
      TF_VERIFY(false, "unhandled case");
      return PcpMapFunction();
  }
}

void PcpMapExpression::_Node::_Invalidate()
{
  // Caller must hold a lock on _mutex.
  if (_hasCachedValue) {
    _hasCachedValue = false;
    _cachedValue = Value();
    for (auto dep : _dependentExpressions) {
      tbb::spin_mutex::scoped_lock lock(dep->_mutex);
      dep->_Invalidate();
    }
  }
  else {
    // This node is already invalid so dependent nodes are already invalid.
  }
}

void PcpMapExpression::_Node::SetValueForVariable(Value &&value)
{
  if (key.op != _OpVariable) {
    TF_CODING_ERROR("Cannot set value for non-variable");
    return;
  }
  tbb::spin_mutex::scoped_lock lock(_mutex);
  if (_valueForVariable != value) {
    _valueForVariable = std::move(value);
    _Invalidate();
  }
}

inline size_t PcpMapExpression::_Node::Key::GetHash() const
{
  return TfHash::Combine(op, arg1.get(), arg2.get(), valueForConstant);
}

bool PcpMapExpression::_Node::Key::operator==(const Key &key) const
{
  return op == key.op && arg1 == key.arg1 && arg2 == key.arg2 &&
         valueForConstant == key.valueForConstant;
}

void TfDelegatedCountIncrement(PcpMapExpression::_Node *p)
{
  ++p->_refCount;
}

void TfDelegatedCountDecrement(PcpMapExpression::_Node *p) noexcept
{
  if (p->_refCount.fetch_sub(1) == 1)
    delete p;
}

PXR_NAMESPACE_CLOSE_SCOPE
