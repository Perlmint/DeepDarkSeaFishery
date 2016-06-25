cmake_minimum_required(VERSION 3.0)
project(DeepDarkSeaFishery)

set(APPNAME DeepDarkSeaFishery)

if(WIN32)
  list(APPEND SRCS src/win/main_win.cpp)
  if("${CMAKE_SIZEOF_VOID_P}" EQUAL 8)
    set(EXT_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ext/lib/x64)
  else()
    set(EXT_LIB_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ext/lib/x86)
  endif()
  list(APPEND CMAKE_LIBRARY_PATH ${EXT_LIB_PATH})
  find_library(LIBSDL SDL2)
  find_library(LIBSDLIMG SDL2_image)

  # copy dll
  foreach(dllname ITEMS
          SDL2.dll
          SDL2_image.dll)
    list(APPEND DLL_LIST ${EXT_LIB_PATH}/${dllname})
    list(APPEND OUTPUT_DLL_LIST ${CMAKE_CURRENT_BINARY_DIR}/${dllname})
  endforeach(dllname)
  execute_process(COMMAND cmake -E copy_if_different ${DLL_LIST} ${CMAKE_CURRENT_BINARY_DIR})

  include_directories(ext/include ext/include/SDL2)
elseif(APPLE)
  list(APPEND CMAKE_FRAMEWORK_PATH ${CMAKE_CURRENT_SOURCE_DIR}/ext)
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
