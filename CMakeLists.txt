cmake_minimum_required (VERSION 2.6)
project (yawa)

set(PACKAGE_NAME "yawa")
set(PACKAGE_VERSION "0.0.1")
set(PACKAGE_STRING "${PACKAGE_NAME} ${PACKAGE_VERSION}")
set(PACKAGE_DESCRIPTION "yet another wallpaper application")
set(PACKAGE_BUGREPORT "johannes@kyriasis.com")

configure_file(
	${CMAKE_SOURCE_DIR}/src/config.h.in
	${CMAKE_SOURCE_DIR}/src/config.h
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_subdirectory("src")
