message( STATUS "Configuring sources directories for main project" )

set( main_sources_path ${PROJECT_SOURCE_DIR}/main/native )
set( main_includes_path ${PROJECT_SOURCE_DIR}/main/include )

IF(EXISTS "${main_includes_path}" )
  set( main_includes_directories ${main_includes_directories} ${main_includes_path} )
ENDIF()

aux_source_directory( ${main_sources_path} main_sources )



