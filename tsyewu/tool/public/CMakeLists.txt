
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src PUBLIC_DIR)

#link_directories(${CMAKE_SOURCE_DIR}/lib)

include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

#set(INC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/inc/projdebug.h)

add_library(public_lib STATIC 
	${PUBLIC_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/inc/projdebug.h
	)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build/lib)

message("************public cmake over*************  ${PUBLIC_DIR}")
