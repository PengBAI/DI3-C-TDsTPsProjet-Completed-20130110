
FIND_PACKAGE(PkgConfig)

#find_package(GTK2  2.6 REQUIRED gtk )

#IF(GTK2_FOUND)
#  set( main_includes_directories ${main_includes_directories} ${GTK2_INCLUDE_DIRS} )
#  set( main_link_libraries ${main_link_libraries} ${GTK2_LIBRARIES} )
#ENDIF(GTK2_FOUND)


message( STATUS "Checking dependencies" )
  foreach( alt gtk+-2.0 )
    execute_process(
    COMMAND ${PKG_CONFIG_EXECUTABLE} ${alt} "--cflags"
    OUTPUT_VARIABLE DEPS_CFLAGS
    RESULT_VARIABLE failed)
    if(failed)
        message( FATAL_ERROR "An error occured while executing pkg-config of the dependency ${alt}" )
    endif()

    execute_process(
    COMMAND ${PKG_CONFIG_EXECUTABLE} ${alt} "--libs"
    OUTPUT_VARIABLE DEPS_LDFLAGS
    RESULT_VARIABLE failed)
    if(failed)
        message( FATAL_ERROR "An error occured while executing pkg-config of the dependency ${alt}" )
    endif()

    string(REGEX REPLACE "[\r\n]" " " DEPS_CFLAGS "${DEPS_CFLAGS}" )
    string(REGEX REPLACE " +$" "" DEPS_CFLAGS "${DEPS_CFLAGS}" )
    string(REGEX REPLACE "[\r\n]" " " DEPS_LDFLAGS "${DEPS_LDFLAGS}" )
    string(REGEX REPLACE " +$" "" DEPS_LDFLAGS "${DEPS_LDFLAGS}" )

    set( main_compiler_flags "${main_compiler_flags} ${DEPS_CFLAGS}" )
    set( main_link_flags "${main_link_flags} ${DEPS_LDFLAGS}" )
    message( STATUS "  Compiler flags: ${DEPS_CFLAGS}" )
    message( STATUS "  Linker flags: ${DEPS_LDFLAGS}" )
  endforeach()
