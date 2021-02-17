#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "pglcore" for configuration "Release"
set_property(TARGET pglcore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(pglcore PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/picam360/armv7l/libpglcore.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS pglcore )
list(APPEND _IMPORT_CHECK_FILES_FOR_pglcore "${_IMPORT_PREFIX}/lib/picam360/armv7l/libpglcore.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
