set(R ${CMAKE_CURRENT_SOURCE_DIR}/res)
set(RESOURCES
  ${R}/grass.png)

if(${WIN32} AND NOT DEFINED CMAKE_SCRIPT_MODE_FILE)
  add_custom_command(OUTPUT
    ${CMAKE_CURRENT_BINARY_DIR}/gen/res.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen/res.rc
    ${CMAKE_CURRENT_BINARY_DIR}/gen/res_map.h
    ${CMAKE_CURRENT_BINARY_DIR}/gen/res_map.cpp
    DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/res/gen.cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/res/gen.py
    COMMAND cmake -P ${CMAKE_CURRENT_SOURCE_DIR}/res/gen.cmake)
endif()
if(DEFINED CMAKE_SCRIPT_MODE_FILE)
  MESSAGE(${RESOURCES})
endif()
