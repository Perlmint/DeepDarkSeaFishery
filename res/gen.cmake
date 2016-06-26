get_filename_component(SCRIPT_DIR "${CMAKE_SCRIPT_MODE_FILE}" DIRECTORY)
execute_process(COMMAND cmake -P ${SCRIPT_DIR}/CMakeLists.txt
                WORKING_DIRECTORY ${SCRIPT_DIR}/..
                ERROR_VARIABLE RESOURCES)
foreach(res IN LISTS RESOURCES)
  string(STRIP "${res}" res)
  file(RELATIVE_PATH rel_res ${SCRIPT_DIR} ${res})
  string(REPLACE "." "__" identifier ${rel_res})
  string(REPLACE "/" "__" identifier ${identifier})
  string(MAKE_C_IDENTIFIER identifier ${identifier})
  file(APPEND "${CMAKE_BINARY_DIR}/RES_FILES" "IDB_${identifier} ${res}\n")
endforeach(res)

execute_process(COMMAND python ${SCRIPT_DIR}/gen.py ${CMAKE_BINARY_DIR}/gen/res
                INPUT_FILE "${CMAKE_BINARY_DIR}/RES_FILES")
MESSAGE("${CMAKE_BINARY_DIR}/res")
file(REMOVE "RES_FILES")
