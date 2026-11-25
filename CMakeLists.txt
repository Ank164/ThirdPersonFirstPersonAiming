cmake_minimum_required(VERSION 3.28)
project(ThirdPersonFirstPersonAiming VERSION 1.2.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

find_package(CommonLibSSE CONFIG REQUIRED)
find_package(directxtk CONFIG REQUIRED)

add_commonlibsse_plugin(
    ${PROJECT_NAME}
    AUTHOR "Zzyxzz (original mod)"
    COMPATIBLE_RUNTIMES "1.7.104.0"
    SOURCES src/main.cpp
)
target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /Zc:preprocessor /permissive- /EHsc)
endif()
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION SKSE/Plugins)
