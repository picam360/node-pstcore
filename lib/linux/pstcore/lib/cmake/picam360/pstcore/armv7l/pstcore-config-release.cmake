#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "pstcore" for configuration "Release"
set_property(TARGET pstcore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(pstcore PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/picam360/armv7l/libpstcore.so"
  IMPORTED_SONAME_RELEASE "libpstcore.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS pstcore )
list(APPEND _IMPORT_CHECK_FILES_FOR_pstcore "${_IMPORT_PREFIX}/lib/picam360/armv7l/libpstcore.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
