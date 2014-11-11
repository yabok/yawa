cmake_minimum_required (VERSION 2.6)
project (yawa)

set(PACKAGE_NAME "yawa")
set(PACKAGE_VERSION "0.0.1")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_DESCRIPTION "Yet Another Wallpaper Application")
set(PACKAGE_BUGREPORT "johannes@kyriasis.com")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

configure_file(
	${CMAKE_SOURCE_DIR}/src/config.h.in
	${CMAKE_SOURCE_DIR}/src/config.h
)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_C_FLAGS    "-Weverything -std=c11")
set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory("src")
add_subdirectory("doc")
