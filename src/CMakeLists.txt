cmake_minimum_required(VERSION 3.14.0)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

set(CPPHTTPLIB_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/CppHttplib/include")



if(ANDROID)
    set(OPENSSL_ROOT_DIR "$ENV{ANDROID_OPENSSL_ROOT_DIR}/${ANDROID_ABI}")
    set(OPENSSL_FOUND true)
    set(OPENSSL_LIBRARIES_DIR "${OPENSSL_ROOT_DIR}/lib")
    set(OPENSSL_INCLUDE_DIR "${OPENSSL_ROOT_DIR}/include")
    set(OPENSSL_LIBRARIES "${OPENSSL_LIBRARIES_DIR}/libssl.so" "${OPENSSL_LIBRARIES_DIR}/libcrypto.so")
else()
    find_package(OpenSSL REQUIRED)

    if(NOT ${OPENSSL_FOUND})
        set(OPENSSL_INCLUDE_DIR "")
    endif()
endif()

include_directories("${INCLUDE_DIR}" "${CPPHTTPLIB_INCLUDE_DIR}" "${OPENSSL_INCLUDE_DIR}")

file(GLOB_RECURSE src "${PROJECT_SOURCE_DIR}/src" "*.h" "*.hpp" "*.cpp" "*.cc")

if(MSVC)
    add_definitions("-D_CRT_SECURE_NO_WARNINGS=1")
endif()

add_library(PawalApi ${src})

if(MSVC)
    target_compile_options(PawalApi PRIVATE /W4 /WX)
else()
    target_compile_options(PawalApi PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

if(${OPENSSL_FOUND})
    target_link_libraries(PawalApi ${OPENSSL_LIBRARIES})
    if(ANDROID)
        target_link_libraries(PawalApi ${CMAKE_DL_LIBS})
    endif()
endif()
