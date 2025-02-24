//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//

#include "pxr/pxrns.h"

#include "Tf/pyEnum.h"

#include "Tf/instantiateSingleton.h"
#include "Tf/mallocTag.h"
#include "Tf/pyWrapContext.h"

#if defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED

PXR_NAMESPACE_OPEN_SCOPE

TF_INSTANTIATE_SINGLETON(Tf_PyEnumRegistry);

using std::string;

using namespace boost::python;

Tf_PyEnumRegistry::Tf_PyEnumRegistry()
{
  // Register general conversions to and from python for TfEnum.
  to_python_converter<TfEnum, _EnumToPython<TfEnum>>();

  _EnumFromPython<TfEnum>();
  _EnumFromPython<int>();
  _EnumFromPython<unsigned int>();
  _EnumFromPython<long>();
  _EnumFromPython<unsigned long>();
}

// CODE_COVERAGE_OFF No way to destroy the enum registry currently.
Tf_PyEnumRegistry::~Tf_PyEnumRegistry()
{
  // release our references on all the objects we own.
  TF_FOR_ALL(i, _objectsToEnums)
  decref(i->first);
}
// CODE_COVERAGE_ON

PyObject *Tf_PyEnumRegistry::_ConvertEnumToPython(TfEnum const &e)
{
  // If there is no registered enum object, create a new one of the
  // appropriate type.
  if (!_enumsToObjects.count(e)) {
    std::string name = ArchGetDemangled(e.GetType());
    name = TfStringReplace(name, " ", "_");
    name = TfStringReplace(name, "::", "_");
    name = TfStringReplace(name, "<", "_");
    name = TfStringReplace(name, ">", "_");
    name = "AutoGenerated_" + name + "_" + TfStringify(e.GetValueAsInt());

    boost::python::object wrappedVal = boost::python::object(Tf_PyEnumWrapper(name, e));

    wrappedVal.attr("_baseName") = std::string();

    RegisterValue(e, wrappedVal);
  }

  return boost::python::incref(_enumsToObjects[e]);
}

string Tf_PyEnumRepr(object const &self)
{
  string moduleName = extract<string>(self.attr("__module__"));
  string baseName = extract<string>(self.attr("_baseName"));
  string name = extract<string>(self.attr("name"));

  return TfStringGetSuffix(moduleName) + "." + (baseName.empty() ? string() : baseName + ".") +
         name;
}

// Returns true if name is a Python keyword and cannot be used as an
// identifier. This encompasses keywords from both Python 2 and 3 so
// that enum names don't change depending on the version of Python
// being used.
static bool _IsPythonKeyword(const std::string &name)
{
  static const char *_PythonKeywords[] = {
      "False",  "None",    "True",     "and",  "as",     "assert", "async",  "await",
      "break",  "class",   "continue", "def",  "del",    "elif",   "else",   "except",
      "exec",   "finally", "for",      "from", "global", "if",     "import", "in",
      "is",     "lambda",  "nonlocal", "not",  "or",     "pass",   "print",  "raise",
      "return", "try",     "while",    "with", "yield"};

  TF_DEV_AXIOM(std::is_sorted(std::begin(_PythonKeywords),
                              std::end(_PythonKeywords),
                              [](const char *x, const char *y) { return strcmp(x, y) < 0; }));

  return std::binary_search(std::begin(_PythonKeywords), std::end(_PythonKeywords), name);
}

string Tf_PyCleanEnumName(string name, bool stripPackageName)
{
  if (stripPackageName) {
    const string pkgName = Tf_PyWrapContextManager::GetInstance().GetCurrentContext();
    if (TfStringStartsWith(name, pkgName) && name != pkgName) {
      name.erase(0, pkgName.size());
    }
  }

  if (_IsPythonKeyword(name)) {
    name += "_";
  }

  return TfStringReplace(name, " ", "_");
}

void Tf_PyEnumAddAttribute(boost::python::scope &s,
                           const std::string &name,
                           const boost::python::object &value)
{
  // Skip exporting attr if the scope already has an attribute
  // with that name, but do make sure to place it in .allValues
  // for the class.
  if (PyObject_HasAttrString(s.ptr(), name.c_str())) {
    TF_CODING_ERROR(
        "Ignoring enum value '%s'; an attribute with that "
        "name already exists in that scope.",
        name.c_str());
  }
  else {
    s.attr(name.c_str()) = value;
  }
}

void Tf_PyEnumRegistry::RegisterValue(TfEnum const &e, object const &obj)
{
  TfAutoMallocTag2 tag("Tf", "Tf_PyEnumRegistry::RegisterValue");

  // we take a reference to obj.
  incref(obj.ptr());

  _enumsToObjects[e] = obj.ptr();
  _objectsToEnums[obj.ptr()] = e;
}

PXR_NAMESPACE_CLOSE_SCOPE

#endif // defined(PXR_PYTHON_SUPPORT_ENABLED) && PXR_PYTHON_SUPPORT_ENABLED
