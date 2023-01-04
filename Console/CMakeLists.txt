cmake_minimum_required(VERSION 3.14.0)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

include_directories("${INCLUDE_DIR}")

file(GLOB_RECURSE src "${PROJECT_SOURCE_DIR}/Console" "*.h" "*.hpp" "*.cpp" "*.cc")

if(MSVC)
    add_definitions("-D_CRT_SECURE_NO_WARNINGS=1")
endif()

if(MSVC)
    list(APPEND src "${PROJECT_SOURCE_DIR}/Console/logo.rc")
endif()

add_executable(PawalConsole ${src})

if(MSVC)
    target_compile_options(PawalConsole PRIVATE /W4 /WX)
else()
    target_compile_options(PawalConsole PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_link_libraries(PawalConsole PawalApi)

if(MSVC)
    set_property(TARGET PawalConsole PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    target_link_libraries(PawalConsole -static-libgcc -static-libstdc++)
endif()