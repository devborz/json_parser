#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Json" for configuration ""
set_property(TARGET Json APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(Json PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_NOCONFIG "CXX"
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libJson.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS Json )
list(APPEND _IMPORT_CHECK_FILES_FOR_Json "${_IMPORT_PREFIX}/lib/libJson.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
