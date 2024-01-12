# ``Arch`` Architecture Dependent

The ``Arch`` library is a repository for all architecture-dependent
code. It isolates all platform dependencies (and confusing `#ifdefs`)
into one small library and also serves as a common area for
documentation of these multi-platform issues.

### ``Arch/Bits``
Functions having to do with how bits are laid out on a machine.

### ``Arch/Multithreading``
Functions having to do with multithreading.

### ``Arch/Math``
Functions for math.

### ``Arch/Strings``
Functions having to do with string massaging/manipulation

### ``Arch/System``
Functions that encapsulate differing low-level system calls.

### ``Arch/Memory``
Functions having to do with memory allocation/handling.

### ``Arch/Diagnostics``
Functions having to do with error reporting/handling.

### ``Arch/Symbols``
Macros having to do with symbol visibility

Symbols for use within Arch:

For OS:
  - ``ARCH_OS_LINUX``
  - ``ARCH_OS_DARWIN``
  - ``ARCH_OS_WINDOWS``

For processor:
  - ``ARCH_CPU_INTEL``
  - ``ARCH_CPU_ARM``
    

For bits:
  - ``ARCH_BITS_64``
    

For compiler:
  - ``ARCH_COMPILER_CLANG``
    - ``ARCH_COMPILER_CLANG_MAJOR``
    - ``ARCH_COMPILER_CLANG_MINOR``
    - ``ARCH_COMPILER_CLANG_PATCHLEVEL``     
    - ``ARCH_COMPILER_GCC``
      - ``ARCH_COMPILER_GCC_MAJOR``
      - ``ARCH_COMPILER_GCC_MINOR``
      - ``ARCH_COMPILER_GCC_PATCHLEVEL``
    - ``ARCH_COMPILER_MSVC``
      - ``ARCH_COMPILER_MSVC_VERSION``
    - ``ARCH_COMPILER_ICC``
