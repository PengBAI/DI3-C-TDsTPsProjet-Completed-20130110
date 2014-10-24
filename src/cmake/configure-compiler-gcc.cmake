# GCC/G++ compiler/linker flags
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  message( STATUS "Configuring compiler and linker flags" )

  # warnings
  add_definitions( -Wall -Wimplicit -Wunused -Wshadow -Wconversion -Wfloat-equal -Wparentheses -Wundef -Wextra )
  add_definitions( --std=c89 -Wstrict-prototypes -pedantic -Wwrite-strings -Wconversion )
  add_definitions( -fdiagnostics-show-option -Werror )
  

  if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_definitions( -Wuninitialized -DNDEBUG )
  endif()

  if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions( -g3 -ggdb3 )
  endif()
endif()
