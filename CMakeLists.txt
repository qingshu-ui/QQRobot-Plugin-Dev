cmake_minimum_required(VERSION 3.0.0)
project(PluginDev)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)


# Import Post_Protocol sub library.
if(NOT POST_PROTOCOL_SOURCE_DIR AND NOT POST_PROTOCOL_BINARY_DIR)
    set(POST_PROTOCOL_SOURCE_DIR "C:\\Users\\17186\\Documents\\VisualCodeProjects\\Post-Protocol")
    set(POST_PROTOCOL_BINARY_DIR "C:\\Users\\17186\\Documents\\VisualCodeProjects\\Post-Protocol\\build")
    include_directories(${POST_PROTOCOL_SOURCE_DIR}/src)
    add_subdirectory(${POST_PROTOCOL_SOURCE_DIR} ${POST_PROTOCOL_BINARY_DIR})
endif()


file(GLOB_RECURSE PluginDev_SOURCES src/*.cpp src/*.h src/*.cc)
add_library(${PROJECT_NAME} SHARED ${PluginDev_SOURCES})

if(MSVC)
    set_property(TARGET PluginDev PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()


find_package(PROTOBUF CONFIG REQUIRED)
find_package(DROGON CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/lib/Post_Protocol/${CMAKE_BUILD_TYPE}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib/Post_Protocol/${CMAKE_BUILD_TYPE}/lib)

target_link_libraries(${PROJECT_NAME} PRIVATE protobuf::protobuf)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
target_link_libraries(${PROJECT_NAME} PRIVATE Post_Protocol)