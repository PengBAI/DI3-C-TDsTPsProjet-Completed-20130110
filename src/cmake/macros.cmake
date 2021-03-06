# Add compiler flags to the specified target
macro(add_compiler_flags_to_target target flags)
    get_target_property( XX ${target} COMPILE_FLAGS )
    if(NOT XX)
      set_target_properties( ${target} PROPERTIES COMPILE_FLAGS "${flags}" )
    else()
      set_target_properties( ${target} PROPERTIES COMPILE_FLAGS "${XX} ${flags}" )
    endif()
endmacro(add_compiler_flags_to_target)

# Add linker flags to the specified target
function(add_linker_flags_to_target target flags)
    get_target_property( XX ${target} LINK_FLAGS )
    if(NOT XX)
      set_target_properties( ${target} PROPERTIES LINK_FLAGS "${flags}" )
    else()
      set_target_properties( ${target} PROPERTIES LINK_FLAGS "${XX} ${flags}" )
    endif()
endfunction(add_linker_flags_to_target)

macro(split_compilerflags flags includedir compilerflags )
  string(REGEX MATCHALL "[^ ]+" split "${flags}" )
  set( ${includedir} )
  set( ${compilerflags} )

  foreach( flag ${split} )

    string(STRIP ${flag} stripped)
    string(SUBSTRING ${stripped} 0 2 start)
    string(LENGTH ${stripped} len)
    math( EXPR len ${len}-2 )
    string(SUBSTRING ${stripped} 2 ${len} end )

    if( ${start} STREQUAL "-I" )
        set( lincludedir ${lincludedir} ${end} )
    else()
        set( lcompilerflags "${lcompilerflags} ${flag}" )
    endif()
  endforeach()
  set( ${includedir} ${lincludedir} )
  set( ${compilerflags} ${lcompilerflags} )
endmacro(split_compilerflags)

macro(split_linkerflags flags library librarydir libraryflags )
  string(REGEX MATCHALL "[^ ]+" split "${flags}" )
  set( ${library} )
  set( ${librarydir} )
  set( ${libraryflags} )

  foreach( flag ${split} )

    string(STRIP ${flag} stripped)
    string(SUBSTRING ${stripped} 0 2 start)
    string(LENGTH ${stripped} len)
    math( EXPR len ${len}-2 )
    string(SUBSTRING ${stripped} 2 ${len} end )

    if( ${start} STREQUAL "-l" )
        set( llibrary ${llibrary} ${end} )
    else()
      if( ${start} STREQUAL "-L" )
        set( llibrarydir ${llibrarydir} ${end} )
      else()
        set( llibraryflags "${llibraryflags} ${flag}" )
      endif()
    endif()
  endforeach()

  set( ${library} ${llibrary} )
  set( ${librarydir} ${llibrarydir} )
  set( ${libraryflags} ${llibraryflags} )
endmacro(split_linkerflags)
