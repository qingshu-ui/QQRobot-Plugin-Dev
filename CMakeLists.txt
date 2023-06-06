cmake_minimum_required(VERSION 3.26.3)
project(PluginDev)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

file(GLOB_RECURSE PluginDev_SOURCES src/*.cpp src/*.h src/*.cc)

if(NOT _MY_CUSTOM_BUILD)
    message("====================Conan install===================")
    execute_process(
        COMMAND conan install ${CMAKE_SOURCE_DIR} -of ${CMAKE_BINARY_DIR} --build missing -s build_type=Debug
        RESULT_VARIABLE CONAN_RESULT 
    )

    if(CONAN_RESULT EQUAL 0)
        message("================Conan install succeeded===============")
    else()
        message(FATAL_ERROR "Conan install failed, Return code: ${CONAN_RESULT}")
    endif()
endif()


add_library(${PROJECT_NAME} SHARED ${PluginDev_SOURCES})

if(MSVC)
    message("-- Set msvc runtime")
    set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
endif()


find_package(PROTOBUF CONFIG REQUIRED)
find_package(DROGON CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC protobuf::protobuf)
target_link_libraries(${PROJECT_NAME} PUBLIC Drogon::Drogon)