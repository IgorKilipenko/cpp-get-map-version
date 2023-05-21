cmake_minimum_required(VERSION 3.14)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(PROJECT_NAME "cpp_get_map_version")
project(${PROJECT_NAME} CXX)

set(IS_LIB 0)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(MAIN_FILE ${SRC_DIR}/main.cpp )

if (DEFINED BUILD_LIB AND BUILD_LIB)
    set(IS_LIB 1)
endif()

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
    EXCLUDE_FROM_ALL TRUE
    DOWNLOAD_DIR ${CMAKE_CURRENT_SOURCE_DIR}
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs
    STEP_TARGETS build
    INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/libs/install
    CMAKE_ARGS -DHTTPLIB_REQUIRE_OPENSSL=on -DBUILD_SHARED_LIBS=on -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Get_Property(httplib INSTALL_DIR)

set(LIBS 
    ${SRC_DIR}/map_version_info.cpp
    ${SRC_DIR}/raw_data_loader.cpp
)

set(CFLAGS -Wall -Werror -pedantic)
set(DEFS -DCPPHTTPLIB_OPENSSL_SUPPORT)
set(LINK_OPTS)
set(LDLIBS tbb pthread OpenSSL::SSL OpenSSL::Crypto)

add_library(spreadsheetLib)
target_sources(spreadsheetLib
    PRIVATE
        ${SRC_DIR}/map_version_info.cpp
        ${SRC_DIR}/raw_data_loader.cpp
    PUBLIC
        ${SRC_DIR}/raw_data_loader.h
        ${SRC_DIR}/map_version_info.h
)
add_dependencies(spreadsheetLib httplib)
target_compile_features(spreadsheetLib PUBLIC cxx_std_20)
target_compile_options(spreadsheetLib PRIVATE ${CFLAGS})
target_compile_definitions(spreadsheetLib PRIVATE ${DEFS})
target_link_options(spreadsheetLib PRIVATE ${LINK_OPTS})
target_link_libraries(spreadsheetLib ${LDLIBS})
target_include_directories(spreadsheetLib PUBLIC ${INSTALL_DIR}/include)

install(FILES ${SRC_DIR}/raw_data_loader.h ${SRC_DIR}/map_version_info.h DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/include)
install(TARGETS spreadsheetLib
	EXPORT spreadsheetLibTargets
)

if (NOT IS_LIB)
    add_executable(${PROJECT_NAME} ${SRC_DIR}/main.cpp)
    target_compile_features(spreadsheetLib PUBLIC cxx_std_20)
    target_link_libraries(${PROJECT_NAME} spreadsheetLib)
endif()