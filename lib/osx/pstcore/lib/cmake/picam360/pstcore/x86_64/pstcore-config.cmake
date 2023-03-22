# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6...3.18)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget pstcore)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Compute the installation prefix relative to this file.
get_filename_component(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
get_filename_component(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
if(_IMPORT_PREFIX STREQUAL "/")
  set(_IMPORT_PREFIX "")
endif()

# Create imported target pstcore
add_library(pstcore SHARED IMPORTED)

set_target_properties(pstcore PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "${_IMPORT_PREFIX}/include"
  INTERFACE_LINK_LIBRARIES "pcommon;pthread;dl;jpeg;png16;z;curl;ldap;z;-framework VideoToolbox;-framework CoreFoundation;-framework CoreMedia;-framework CoreVideo;/usr/local/opt/openssl/lib/libssl.dylib;/usr/local/opt/openssl/lib/libcrypto.dylib;/usr/local/opt/opencv/lib/libippicv.a;/usr/local/opt/opencv/lib/libippiw.a;/usr/local/opt/opencv/lib/libittnotify.a;/usr/local/opt/opencv/lib/libopencv_calib3d.a;/usr/local/opt/opencv/lib/libopencv_core.a;/usr/local/opt/opencv/lib/libopencv_features2d.a;/usr/local/opt/opencv/lib/libopencv_flann.a;/usr/local/opt/opencv/lib/libopencv_imgcodecs.dylib;/usr/local/opt/opencv/lib/libopencv_imgproc.a;/usr/local/opt/opencv/lib/libopencv_sfm.a;/usr/local/opt/opencv/lib/libopencv_xfeatures2d.a;-framework OpenCL;/usr/local/lib/libtbb.dylib;/usr/local/opt/openblas/lib/libopenblas.a;/usr/local/Cellar/gcc/12.2.0/lib/gcc/12/libgfortran.a;/usr/local/Cellar/gcc/12.2.0/lib/gcc/12/libgomp.a;/usr/local/Cellar/gcc/12.2.0/lib/gcc/12/libquadmath.a;/usr/local/Cellar/gcc/12.2.0/lib/gcc/12/gcc/x86_64-apple-darwin22/12/libgcc.a;/usr/local/Cellar/libde265/1.0.11/lib/libde265.a;/usr/local/Cellar/glew/2.2.0_1/lib/libGLEW.a;/usr/local/Cellar/opus/1.3.1/lib/libopus.a;/usr/local/Cellar/libogg/1.3.5/lib/libogg.a;/usr/local/Cellar/opusfile/0.12/lib/libopusfile.a;/usr/local/Cellar/libopusenc/0.2.1/lib/libopusenc.a;/usr/local/lib/libglfw3.a;/usr/local/Cellar/libwebsockets/4.3.2/lib/libwebsockets.dylib;/Users/hirayama.takuma/github/pstcore/lib/tcsdk/mac/libtoupcam.dylib;-framework OpenGL;-framework OpenAL;-framework Cocoa;-framework IOKit"
)

# Load information for each installed configuration.
get_filename_component(_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
file(GLOB CONFIG_FILES "${_DIR}/pstcore-config-*.cmake")
foreach(f ${CONFIG_FILES})
  include(${f})
endforeach()

# Cleanup temporary variables.
set(_IMPORT_PREFIX)

# Loop over all imported files and verify that they actually exist
foreach(target ${_IMPORT_CHECK_TARGETS} )
  foreach(file ${_IMPORT_CHECK_FILES_FOR_${target}} )
    if(NOT EXISTS "${file}" )
      message(FATAL_ERROR "The imported target \"${target}\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    endif()
  endforeach()
  unset(_IMPORT_CHECK_FILES_FOR_${target})
endforeach()
unset(_IMPORT_CHECK_TARGETS)

# Make sure the targets which have been exported in some other
# export set exist.
unset(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets)
foreach(_target "pcommon" )
  if(NOT TARGET "${_target}" )
    set(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets "${${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets} ${_target}")
  endif()
endforeach()

if(DEFINED ${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets)
  if(CMAKE_FIND_PACKAGE_NAME)
    set( ${CMAKE_FIND_PACKAGE_NAME}_FOUND FALSE)
    set( ${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE "The following imported targets are referenced, but are missing: ${${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets}")
  else()
    message(FATAL_ERROR "The following imported targets are referenced, but are missing: ${${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets}")
  endif()
endif()
unset(${CMAKE_FIND_PACKAGE_NAME}_NOT_FOUND_MESSAGE_targets)

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
