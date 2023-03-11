cmake_minimum_required(VERSION 3.14)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(PROJECT_NAME "cpp-get-map-version")
project(${PROJECT_NAME} CXX)

set(SRC_DIR ./src)
set(MAIN_FILE ${SRC_DIR}/main.cpp )


# ADD AND CONFIG httplib
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    set(HTTPLIB_IS_USING_OPENSSL TRUE)
endif()

include(ExternalProject)
ExternalProject_Add(httplib
    PREFIX libs
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    EXCLUDE_FROM_ALL TRUE
    DOWNLOAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs
    CMAKE_ARGS -DHTTPLIB_REQUIRE_OPENSSL=on -DBUILD_SHARED_LIBS=on
    STEP_TARGETS build
)

ExternalProject_Get_Property(httplib SOURCE_DIR)

set(LIBS 
    ${MAIN_FILE}
    #${SRC_DIR}/transport_catalogue.cpp
)
set(CFLAGS -Wall -Werror -pedantic)
set(DEFS)
set(LINK_OPTS)
set(LDLIBS tbb pthread OpenSSL::SSL OpenSSL::Crypto)

add_executable(${PROJECT_NAME} ${LIBS})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE ${CFLAGS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${DEFS})
target_link_options(${PROJECT_NAME} PRIVATE ${LINK_OPTS})
target_link_libraries(${PROJECT_NAME} ${LDLIBS})
target_include_directories(${PROJECT_NAME} PUBLIC ${httplib_SOURCE_DIR})