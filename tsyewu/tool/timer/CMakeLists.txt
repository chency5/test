aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src DIR_TIMER)

#link_directories(${CMAKE_SOURCE_DIR}/lib)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_library(timer_lib STATIC ${DIR_TIMER})

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/lib)
