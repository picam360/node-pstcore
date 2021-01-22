#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "pcommon" for configuration "Release"
set_property(TARGET pcommon APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(pcommon PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "C;CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/picam360/armeabi-v7a/libpcommon.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS pcommon )
list(APPEND _IMPORT_CHECK_FILES_FOR_pcommon "${_IMPORT_PREFIX}/lib/picam360/armeabi-v7a/libpcommon.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
