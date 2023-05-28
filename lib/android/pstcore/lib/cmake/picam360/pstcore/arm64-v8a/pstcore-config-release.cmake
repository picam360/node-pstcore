#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "pstcore" for configuration "Release"
set_property(TARGET pstcore APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(pstcore PROPERTIES
  IMPORTED_COMMON_LANGUAGE_RUNTIME_RELEASE ""
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/picam360/arm64-v8a/libpstcore.so"
  IMPORTED_NO_SONAME_RELEASE "TRUE"
  )

list(APPEND _cmake_import_check_targets pstcore )
list(APPEND _cmake_import_check_files_for_pstcore "${_IMPORT_PREFIX}/lib/picam360/arm64-v8a/libpstcore.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
