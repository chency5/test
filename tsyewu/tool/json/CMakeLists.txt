
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src DIR_JSON)

#link_directories(${CMAKE_SOURCE_DIR}/lib)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_library(json_lib STATIC ${DIR_JSON})
target_link_libraries(json_lib m)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/lib)

