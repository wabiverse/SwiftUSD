# Work : Multi-threaded Dispatch

## Summary

The **Work** library is intended to simplify the use of
*multithreading* in the context of our software ecosystem.

This library is intended as a thin abstraction layer on
top of a multithreading subsystem.

The abstraction serves two purposes:
  - To simplify the use of common constructs like **"Parallel For"**
  - To centralize our dependency on a particular multithreading
    subsystem (e.g., **TBB**, etc.).

Because of the way multithreading subsystems work and because of the way they 
need to interact with each other in managing system resources, it is not generally
practical for each client to use whatever threading system they like (e.g., **TBB**
for one client, **OpenMP** for another).

## Initializing and Limiting Multithreading

The library defaults to maximum concurrency, i.e. it will attempt to use as
many threads as available on the system. The default concurrency limit is
established at static initialization time.

The ``PXR_WORK_THREAD_LIMIT`` environment variable can be set to further limit
concurrency, such as for example in a farm environment. ``PXR_WORK_THREAD_LIMIT``
must be set to an integer `N`, denoting one of the following:

  - `0` - maximum concurrency (default if unset)
  - `1` - single-threaded mode
  - positive `N` - limit to `N` threads (clamped to number of hardware threads available)
  - negative `N` - limit to all but `N` hardware threads (clamped to 1)

The concurrency limit can be set programmatically, using for example:

```cpp
  WorkSetConcurrencyLimitArgument(N);
```
#### or

```cpp
  WorkSetMaximumConcurrencyLimit();
```

It is preferable to use ``WorkSetMaximumConcurrencyLimit()`` when the desire
to use the hardware to its fullest rather than specify the maximum concurrency
limit manually.

## Simple "Parallel For" Example

Once you've initialized the library, you can now harness the awesome power of
your multi-core machine. 

Here's a simple example of a **Parallel For**:

```cpp
static void _DoubleTheValues(size_t begin, size_t end, std::vector<int> *v)
{
  for (size_t i = begin; i < end; ++i)
    (*v)[i] *= 2;
}


static void DoubleInParallel(std::vector<int> *v)
{
  WorkParallelForN(v->size(), std::bind(&_DoubleTheValues, _1, _2, v));
}
```

> [!NOTE]
> You can avoid the ``std::bind`` and provide your own functor object as well.
