cmake_minimum_required(VERSION 3.14.0)

set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")

set(CPPHTTPLIB_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/lib/CppHttplib/include")

find_package(OpenSSL REQUIRED)

if(NOT ${OPENSSL_FOUND})
    set(OPENSSL_INCLUDE_DIR "")
endif()

include_directories("${INCLUDE_DIR}" "${CPPHTTPLIB_INCLUDE_DIR}" "${OPENSSL_INCLUDE_DIR}")

file(GLOB_RECURSE src "${PROJECT_SOURCE_DIR}/src" "*.h" "*.hpp" "*.cpp" "*.cc")

add_library(PawalApi ${src})

if(${OPENSSL_FOUND})
    target_link_libraries(PawalApi ${OPENSSL_LIBRARIES})
endif()