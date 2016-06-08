cmake_minimum_required(VERSION 3.0)
project(DeepDarkSeaFishery)

set(APPNAME DeepDarkSeaFishery)
list(APPEND CMAKE_FRAMEWORK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ext)

if(WIN32)
  list(APPEND SRCS src/win/main_win.cpp)
  find_library(LIBSDL SDL2)
  find_library(LIBSDLIMG SDL2_image)
  include_directories(ext/include ext/include/SDL2)
elseif(APPLE)
  find_library(LIBSDL SDL2)
  find_library(LIBSDLIMG SDL2_image)
  find_library(COCOA COCOA)
  list(APPEND PLATFORM_SPECIFIC_LIBS ${COCOA})
endif()

if ("${LIBSDL}" STREQUAL LIBSDL-NOTFOUND)
  message(FATAL_ERROR "libsdl is notfound place libsdl files into ext")
endif()

add_subdirectory(res)
include(src/CMakeLists.txt)

add_executable(${APPNAME} MACOSX_BUNDLE WIN32 ${SRCS} ${RESOURCES})
set_target_properties(${APPNAME} PROPERTIES RESOURCE "${RESOURCES}")
target_link_libraries(${APPNAME} ${LIBSDL} ${LIBSDLIMG} ${PLATFORM_SPECIFIC_LIBS})
