cmake_minimum_required(VERSION 3.10)

project(CANService)

# set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local/lib/cmake/CommonAPI-SomeIP-3.2")
# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})
# set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "/usr/local")

set(PRJ_NAME CANService)

#set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



#find vsomeip package
find_package(vsomeip3 REQUIRED)
find_package(CommonAPI REQUIRED)
find_package( Boost 1.55 COMPONENTS system thread log REQUIRED )
find_package(CommonAPI-SomeIP REQUIRED)
# if(TARGET CommonAPI-SomeIP)
#     get_target_property(SOMEIP_LIBRARY CommonAPI-SomeIP IMPORTED_LOCATION)
#     if(NOT SOMEIP_LIBRARY)
#         set_target_properties(CommonAPI-SomeIP PROPERTIES
#             IMPORTED_LOCATION "/usr/local/lib/libCommonAPI-SomeIP.so")
#     endif()
# endif()
# find_package(CommonAPI-SOME/IP REQUIRED)

#include directories
include_directories(
	${Boost_INCLUDE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/Service
	${CMAKE_CURRENT_SOURCE_DIR}/middleware/src-gen/
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware
	/usr/local/include/vsomeip
	/usr/local/include/CommonAPI-3.2
	/usr/local/include/CommonAPI-SomeIP-3.2
)

#collect all .cpp files in the Service directory
file(GLOB SERVICE_SOURCES
	"${CMAKE_CURRENT_SOURCE_DIR}/Service/*.cpp"
)

# Collect all .cpp files in the middleware/src-gen/v1/org/example/canservice directory
file(GLOB GENERATED_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/middleware/src-gen/v1/org/example/canservice/*.cpp"
)



#Add executable for the can service
add_executable(CANService
${SERVICE_SOURCES} 
${GENERATED_SOURCES}
# ${CMAKE_CURRENT_SOURCE_DIR}/Service/main.cpp
# ${CMAKE_CURRENT_SOURCE_DIR}/Service/CANService.cpp
)

# add_custom_command(TARGET CANService PRE_BUILD
#     COMMAND export COMMONAPI_SOMEIP_CONFIG=/etc/commonapi-someip.ini
# 	COMMAND export VSOMEIP_CONFIG=/etc/vsomeip.json
# )


#Link vsomeip library
target_link_libraries(CANService vsomeip3 CommonAPI CommonAPI-SomeIP)

