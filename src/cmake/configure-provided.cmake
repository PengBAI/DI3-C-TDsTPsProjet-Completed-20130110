message( STATUS "Adding provided object code dependencies" )
  set( main_includes_directories ${main_includes_directories} ${PROVIDED_INCLUDEDIR} )
  set( main_link_directories ${main_link_directories} ${PROVIDED_LIBDIR} )
  set( main_link_libraries ${main_link_libraries} facturationprovided )
  