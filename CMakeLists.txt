cmake_minimum_required(VERSION 3.14)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(PROJECT_NAME "cpp_get_map_version")
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
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/libs
    GIT_REPOSITORY https://github.com/yhirose/cpp-httplib.git
    GIT_TAG origin/master
    #EXCLUDE_FROM_ALL TRUE
    DOWNLOAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs
    CMAKE_ARGS -DHTTPLIB_REQUIRE_OPENSSL=on -DBUILD_SHARED_LIBS=on -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_BINARY_DIR}/libs/install
    STEP_TARGETS build
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs/install
)

ExternalProject_Get_Property(httplib INSTALL_DIR)

#include_directories(${INSTALL_DIR}/include)

set(LIBS 
    ${MAIN_FILE}
    #${SRC_DIR}/transport_catalogue.cpp
)
set(CFLAGS -Wall -Werror -pedantic)
set(DEFS -DCPPHTTPLIB_OPENSSL_SUPPORT)
set(LINK_OPTS)
set(LDLIBS tbb pthread OpenSSL::SSL OpenSSL::Crypto)

add_executable(${PROJECT_NAME} ${LIBS})
add_dependencies(${PROJECT_NAME} httplib)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)
target_compile_options(${PROJECT_NAME} PRIVATE ${CFLAGS})
target_compile_definitions(${PROJECT_NAME} PRIVATE ${DEFS})
target_link_options(${PROJECT_NAME} PRIVATE ${LINK_OPTS})
target_link_libraries(${PROJECT_NAME} ${LDLIBS})
#target_include_directories(${PROJECT_NAME} BEFORE PUBLIC ${httplib_INSTALL_DIR})