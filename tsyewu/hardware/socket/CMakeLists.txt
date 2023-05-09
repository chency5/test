
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src DIR_SOCKET)

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/inc

	${CMAKE_SOURCE_DIR}/tool/json/inc

	${CMAKE_SOURCE_DIR}/tool/timer/inc

	${CMAKE_SOURCE_DIR}/tool/public/inc

	${CMAKE_SOURCE_DIR}/software/fun/inc
)

#link_directories(${CMAKE_SOURCE_DIR}/lib)

LINK_LIBRARIES("${CMAKE_SOURCE_DIR}/build/lib/libjson_lib.a")

LINK_LIBRARIES("${CMAKE_SOURCE_DIR}/build/lib/libtimer_lib.a")

LINK_LIBRARIES("${CMAKE_SOURCE_DIR}/build/lib/libpublic_lib.a")

add_library(socket_lib STATIC ${DIR_SOCKET})

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/lib)
