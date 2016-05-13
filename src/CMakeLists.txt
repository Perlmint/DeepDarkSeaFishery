macro(include_sub name)
  set(OLD_R ${R})
  set(R ${R}/${name})
  include(${R}/CMakeLists.txt)
  set(R ${OLD_R})
  unset(OLD_R)
endmacro()
macro(add_sources group)
  list(APPEND SRCS ${ARGN})
  string(REPLACE / \\\\ group_escaped ${group})
  source_group(${group_escaped} FILES ${ARGN})
endmacro()

set(R ${CMAKE_CURRENT_SOURCE_DIR}/src)
include_sub(game)
if(APPLE)
  if(NOT IOS)
    include_sub(osx)
  else()
  endif()
endif()

include_directories(${R})
add_sources(
  Sources
  ${R}/main.cpp
  ${R}/platform.h)
