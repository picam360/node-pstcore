#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "pstcore" for configuration ""
set_property(TARGET pstcore APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(pstcore PROPERTIES
  IMPORTED_IMPLIB_NOCONFIG "${_IMPORT_PREFIX}/lib/picam360/x86_64/libpstcore${CMAKE_IMPORT_LIBRARY_SUFFIX}"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/bin/libpstcore.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS pstcore )
list(APPEND _IMPORT_CHECK_FILES_FOR_pstcore "${_IMPORT_PREFIX}/lib/picam360/x86_64/libpstcore${CMAKE_IMPORT_LIBRARY_SUFFIX}" "${_IMPORT_PREFIX}/bin/libpstcore.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
