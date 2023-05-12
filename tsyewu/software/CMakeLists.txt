
file(GLOB_RECURSE DIR_FUN "*.c")


#file(GLOB_RECURSE DIR_PORT "${CMAKE_CURRENT_SOURCE_DIR}/chargerport/*.c")

#file(GLOB_RECURSE DIR_CENTER "${CMAKE_CURRENT_SOURCE_DIR}/datacontrol/*.c")

message("################")
message("## dir_port ${DIR_PORT}")
message("################")
message("## dir_center ${DIR_CENTER}")
message("################")

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/inc

	${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/tsfengchong/inc
	${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/xiaoju/inc
	${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/yunwei/inc
        ${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/sourcenetwork/inc

	${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/guowang/eng
        ${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/guowang/eng/dev_model
        ${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/guowang/eng/dev_sign
        ${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/guowang/eng/dynamic_register
        ${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/guowang/eng/infra
        ${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/guowang/eng/mqtt
        ${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/guowang/eng/ota
        ${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/guowang/eng/wrappers
        ${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/guowang/eng/wrappers/external_libs
        ${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/guowang/eng/wrappers/external_libs/mbedtls/library/mbedtls
	${CMAKE_CURRENT_SOURCE_DIR}/pingtaiport/guowang/examples


	${CMAKE_SOURCE_DIR}/hardware/libiec61850-1.5.1/config
        ${CMAKE_SOURCE_DIR}/hardware/libiec61850-1.5.1/src/common/inc
        ${CMAKE_SOURCE_DIR}/hardware/libiec61850-1.5.1/src/goose
        ${CMAKE_SOURCE_DIR}/hardware/libiec61850-1.5.1/src/sampled_values
        ${CMAKE_SOURCE_DIR}/hardware/libiec61850-1.5.1/src/hal/inc
        ${CMAKE_SOURCE_DIR}/hardware/libiec61850-1.5.1/src/iec61850/inc
        ${CMAKE_SOURCE_DIR}/hardware/libiec61850-1.5.1/src/iec61850/inc_private
        ${CMAKE_SOURCE_DIR}/hardware/libiec61850-1.5.1/src/mms/inc
        ${CMAKE_SOURCE_DIR}/hardware/libiec61850-1.5.1/src/mms/inc_private
        ${CMAKE_SOURCE_DIR}/hardware/libiec61850-1.5.1/src/mms/iso_mms/asn1c
        ${CMAKE_SOURCE_DIR}/hardware/libiec61850-1.5.1/src/logging
        ${CMAKE_SOURCE_DIR}/hardware/libiec61850-1.5.1/hal/inc


	${CMAKE_SOURCE_DIR}/tool/json/inc
	${CMAKE_SOURCE_DIR}/tool/timer/inc
	${CMAKE_SOURCE_DIR}/tool/public/inc
	${CMAKE_SOURCE_DIR}/hardware/can/inc
	${CMAKE_SOURCE_DIR}/hardware/socket/inc
	${CMAKE_SOURCE_DIR}/hardware/uart/inc
)

#link_directories(${CMAKE_SOURCE_DIR}/lib)

LINK_LIBRARIES("${CMAKE_SOURCE_DIR}/build/lib/libcan_lib.a")

LINK_LIBRARIES("${CMAKE_SOURCE_DIR}/build/lib/libsocket_lib.a")

LINK_LIBRARIES("${CMAKE_SOURCE_DIR}/build/lib/libuart_lib.a")

LINK_LIBRARIES("${CMAKE_SOURCE_DIR}/build/lib/libjson_lib.a")

LINK_LIBRARIES("${CMAKE_SOURCE_DIR}/build/lib/libtimer_lib.a")

LINK_LIBRARIES("${CMAKE_SOURCE_DIR}/build/lib/libpublic_lib.a")

LINK_LIBRARIES("${CMAKE_SOURCE_DIR}/hardware/lib/libiec61850.so")

add_library(fun_lib STATIC ${DIR_FUN})

#add_library(port_lib STATIC ${DIR_PORT})

#add_library(center_lib STATIC ${DIR_CENTER})

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/lib)





