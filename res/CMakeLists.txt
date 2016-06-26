set(R ${CMAKE_CURRENT_SOURCE_DIR}/res)
set(RESOURCES
  ${R}/grass.png)

if(NOT DEFINED CMAKE_SCRIPT_MODE_FILE)
  set(OUTPUTS ${CMAKE_CURRENT_BINARY_DIR}/gen/res.h)
  if(MSVC)
    list(APPEND OUTPUTS
      ${CMAKE_CURRENT_BINARY_DIR}/gen/res.rc
      ${CMAKE_CURRENT_BINARY_DIR}/gen/res_map.h
      ${CMAKE_CURRENT_BINARY_DIR}/gen/res_map.cpp)
    set(RESOURCES "")
  endif()
  add_custom_command(OUTPUT
    ${OUTPUTS}
    DEPENSD
    ${CMAKE_CURRENT_SOURCE_DIR}/res/gen.cmake
    ${CMAKE_CURRENT_SOURCE_DIR}/res/gen.py
    COMMAND cmake -DMSVC=${MSVC} -P ${CMAKE_CURRENT_SOURCE_DIR}/res/gen.cmake)

  list(APPEND SRCS ${OUTPUTS})
  source_group(gen FILES ${OUTPUTS})
else()
  MESSAGE(${RESOURCES})
endif()
