cmake_minimum_required(VERSION 3.0.0)
project(PluginDev)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if(MSVC)
    add_compile_options(-MD)
endif()


aux_source_directory(src PLUGINDEV_SOURCE)
add_library(${PROJECT_NAME} SHARED ${PLUGINDEV_SOURCE})

find_package(protobuf CONFIG REQUIRED)
find_package(Drogon CONFIG REQUIRED)

if(NOT PROTOCOL_ADDED)
    message("------------------${protocol}")
    add_subdirectory(protocol)
    include_directories(protocol/src)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE protobuf::protobuf)
target_link_libraries(${PROJECT_NAME} PRIVATE Drogon::Drogon)
target_link_libraries(${PROJECT_NAME} PRIVATE protocol)