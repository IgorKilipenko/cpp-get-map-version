cmake_minimum_required(VERSION 3.14)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(PROJECT_NAME "cpp-get-map-version")
project(${PROJECT_NAME} CXX)

set(SRC_DIR ./src)
set(MAIN_FILE ${SRC_DIR}/main.cpp )

#include(./libs/cpp-httplib/CMakeLists.txt)

include(ExternalProject)
ExternalProject_Add(cpp-httplib
    PREFIX libs
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    #EXCLUDE_FROM_ALL TRUE
    #BUILD_COMMAND $(MAKE) fmt
    DOWNLOAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ddd
    CMAKE_ARGS HTTPLIB_COMPILE=on
    STEP_TARGETS build
)
#set(cpp-httplib_BINARY_DIR "${CMAKE_BINARY_DIR}/libs/src/fmtlib-build")
set(cpp-httplib_SOURCE_DIR "${CMAKE_BINARY_DIR}/libs/src/cpp-httplib")

set(LIBS 
    ${MAIN_FILE}
    #${SRC_DIR}/transport_catalogue.cpp
)

if (DEFINED TESTS AND TESTS)
    list(APPEND LIBS ${TESTS_DIR}/server_test.cpp)
endif()

set(CFLAGS -Wall -Werror -pedantic)
set(DEFS)
set(LINK_OPTS)
set(LDLIBS tbb pthread)

add_executable(${PROJECT_NAME} ${LIBS})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE ${CFLAGS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${DEFS})
target_link_options(${PROJECT_NAME} PRIVATE ${LINK_OPTS})
target_link_libraries(${PROJECT_NAME} ${LDLIBS})