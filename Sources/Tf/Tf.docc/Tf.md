# ``Tf``

Contains foundation classes and functions for all C/C++ software development.

### Comprehensive Package Documentation:
- Notification System
- Error-posting Facility
- Diagnostic Facilities
- Initialization Facilities
- Memory Tagging System

### Classes and Functions by Groups:

#### Object Creation
Classes for controlling creation of objects

#### Memory Management
Classes for memory management.

#### Runtime Typing
Classes having to do with run-time typing.

#### Basic Mathematical Operations
Functions for basic mathematical operations.

#### Output for Debugging Purposes
Functions/classes that generate output solely as a debugging aid

#### Path Utilities
Functions/classes for pathname manipulation.

#### C++ STL Utilities
Helper functions/classes for STL

#### Preprocessor Utilities
Preprocessor macros.

#### String Utilities
Functions/classes for string manipulation.

#### File Utilities
Functions/classes for file handling.

#### Performance Measurements
Functions/classes for measuring performance.

#### Systems Extensions and Enhancements
Functions/classes for extending/enhancing standard OS functionality.

#### Container classes
Classes that hold objects

#### UI Support
Classes/functions for package-independent UI concepts

#### Compiler Aids
Classes/functions that help getting code compiled cleanly

#### Internals Non-exported Functionality
Functions/classes for libtf internal use only

The high-level grouping of C++ classes and functions is as follows:
   
<ul>
	<li> \link group_tf_Memory \b Memory \b Management - \endlink 
		TfRefPtr,  TfWeakPtr,  TfRefBase,  TfWeakBase,  TfMallocTag
	<li> \link group_tf_RuntimeTyping \b Runtime \b Typing - \endlink 
		TfType,  TfEnum,  TfTypeInfoMap
	<li> \link group_tf_Path \b Path \b Utilities - \endlink
		TfRealPath, TfNormPath, TfAbsPath, TfReadLink, TfGlob
	<li> \link group_tf_Diagnostic \b Diagnostic \b Utilities - \endlink 
		TF_AXIOM(), TF_VERIFY(), TF_FATAL_ERROR(), TF_THROW(), TF_CODING_ERROR(), TF_RUNTIME_ERROR(), TF_WARN(), TF_STATUS()
	<li> \link group_tf_DebuggingOutput \b Output \b For \b Debugging - \endlink 
		TfDebug,  TF_DEBUG(),  TF_FUNC_NAME() 
	<li> \link group_tf_String \b String \b Utilities - \endlink 
		TfStringPrintf(),  TfHash, (and a large number of miscellaneous free functions) 
	<li> \link group_tf_Containers \b Containers - \endlink 
		TfByteData,  TfArray2,  TfArray3, TfTypeInfoMap
	<li> \link group_tf_Stl \b STL \b Utilities - \endlink 
		TfIterator,  TfDeleter, TfMapLookup(),  TfOrderedPair()
	<li> \link group_tf_ObjectCreation \b Object \b Creation - \endlink 
		TfSingleton,  TfType
	<li> \link group_tf_BasicMath \b Mathematical \b Operations - \endlink 
		TfAbs(),  TfMin(),  TfMax()
	<li> \link group_tf_Performance \b Performance \b Measurements - \endlink 
		TfStopwatch
	<li> \link group_tf_File \b File \b Utilities - \endlink 
		TfSearchPath
	<li> \link group_tf_SystemsExt \b Systems \b Extensions \b and \b Enhancements - \endlink 
		TfDlopen(),  TfDlclose(),  TfGetenv()
</ul>

For a detailed explanation of topics specific to C++, see these additional Related Pages in the C++ API documentation: 
<ul> 
    <li> \subpage page_tf_Notification  </li> 
    <li> \subpage page_tf_TfError   </li> 
    <li> \subpage page_tf_Diagnostic   </li> 
    <li> \subpage page_tf_RegistryManager   </li> 
    <li> \subpage page_tf_MallocTag   </li> 
</ul> 
