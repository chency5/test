cmake_minimum_required(VERSION 3.8)

project(demo)

set(TARGET tsCharger)

set(CMAKE_BUILD_TYPE "debug")
SET(CMAKE_C_FLAGS "-O3 -Wall -g -ggdb")
#SET(CFLAGS -O0 -Wall -pthread -g -ggdb)
#SET(CMAKE_CFLAGS_DEBUG "-O3 -Wall -pthread")


find_package(Threads)

add_subdirectory(${CMAKE_SOURCE_DIR}/tool/timer)
add_subdirectory(${CMAKE_SOURCE_DIR}/tool/public)
#add_subdirectory(${CMAKE_SOURCE_DIR}/hardware/libiec61850-1.5.1)
add_subdirectory(${CMAKE_SOURCE_DIR}/hardware/uart)
add_subdirectory(${CMAKE_SOURCE_DIR}/hardware/socket)
add_subdirectory(${CMAKE_SOURCE_DIR}/hardware/can)
add_subdirectory(${CMAKE_SOURCE_DIR}/software)
add_subdirectory(${CMAKE_SOURCE_DIR}/tool/json)


include_directories(${CMAKE_SOURCE_DIR}/software/inc)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/bin)


add_executable(${TARGET} tscharger.c)

target_link_libraries(${TARGET} 
	can_lib 
	socket_lib
	uart_lib 
	fun_lib 
	json_lib
	public_lib 
	timer_lib 
	${CMAKE_SOURCE_DIR}/software/chargerport/lib/libport_lib.a
	${CMAKE_SOURCE_DIR}/software/datacontrol/lib/libcenter_lib.a
	#	iec61850
	#	${CMAKE_SOURCE_DIR}/hardware/lib/libiec61850.so
	/usr/lib/libmodbus.so
	${CMAKE_THREAD_LIBS_INIT}
	#	m
	)

#target_link_libraries(client -lddsc -lpthread)
#target_link_libraries(server -lddsc -lpthread)
