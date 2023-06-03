cmake_minimum_required(VERSION 3.26.3)
project(PluginDev)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES src/*.cpp src/*.h src/*.cc)

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
    # 包含 Conan 构建信息
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(TARGETS)
endif()


add_library(${PROJECT_NAME} STATIC ${SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "libplugindev")

target_link_libraries(${PROJECT_NAME} PUBLIC CONAN_PKG::protobuf)
target_link_libraries(${PROJECT_NAME} PUBLIC CONAN_PKG::drogon)