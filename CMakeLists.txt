###############################################
###              BaSyx C++ SDK  2.0         ###
###############################################
cmake_minimum_required(VERSION 3.13.0)

set(PROJECT_NAME "BaSyx C++ SDK 2.0")
set(PROJECT_SHORTNAME "BaSyx")
set(PROJECT_INCLUDENAME "basyx")

project(${PROJECT_NAME} VERSION "2.0")

### CMake settings ###
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(build_source_group)
include(diagnostics_print)
include(enable_clang_format)
include(enable_clang_tidy)
include(enable_cppcheck)
include(FetchContent)

# Check if standalone build or being included as submodule
get_directory_property(BASYX_IS_SUBMODULE PARENT_DIRECTORY)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

### Project settings ###
message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR: ${CMAKE_BINARY_DIR}")
message(STATUS "" )

if(NOT BASYX_IS_SUBMODULE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    set(BASYX_INSTALL_SDK_DEFAULT ON)
else()
    set(BASYX_INSTALL_SDK_DEFAULT OFF)
endif()

### BaSyx directories ###
set(BASYX_SOURCE_DIR  "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(BASYX_LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(BASYX_TEST_DIR    "${CMAKE_CURRENT_SOURCE_DIR}/tests")

### Build options ###
option(BASYX_BUILD_TESTS "Build unit tests" OFF)
option(BASYX_BUILD_API "Build BaSyx API" ON)
option(BASYX_VERBOSE_CMAKE_OUTPUT "Show detailed CMake output" ON)
option(BASYX_INSTALL_SDK "Create install instructions for BaSyx SDK" OFF)

### Compiler settings ###
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)


###############################################
###           Library Settings              ###
###############################################

### Detect OS threading library ###
find_package(Threads)

if (${FETCHCONTENT_FULLY_DISCONNECTED})
   find_package(nlohmann_json REQUIRED)
   find_package(pugixml REQUIRED)
else()
   ### nlohmann-json ###
   FetchContent_Declare(
     nlohmann_json
     GIT_REPOSITORY https://github.com/nlohmann/json
     GIT_TAG v3.10.4
     GIT_SHALLOW TRUE)

   if(${BASYX_INSTALL_SDK})
     set(JSON_Install ON)
   endif()

   FetchContent_GetProperties(nlohmann_json)
   if(NOT nlohmann_json_POPULATED)
      FetchContent_Populate(nlohmann_json)
      add_subdirectory(${nlohmann_json_SOURCE_DIR} ${nlohmann_json_BINARY_DIR})
   endif()


   ### pugixml
   FetchContent_Declare(
      pugixml
      GIT_REPOSITORY https://github.com/zeux/pugixml
      GIT_TAG v1.12
      )

   FetchContent_GetProperties(pugixml)
   if(NOT pugixml_POPULATED)
     FetchContent_Populate(pugixml)
     add_subdirectory(${pugixml_SOURCE_DIR} ${pugixml_BINARY_DIR})
     set_target_properties(pugixml PROPERTIES FOLDER lib)
     set_target_properties(pugixml-static PROPERTIES FOLDER lib)
   endif()
endif()

### GoogleTest ###
if(BASYX_BUILD_TESTS)
    include(GoogleTest)
    FetchContent_Declare(
	    googletest
	    GIT_REPOSITORY https://github.com/google/googletest
		GIT_TAG release-1.12.1)

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    set_target_properties(gmock PROPERTIES FOLDER lib/gtest)
    set_target_properties(gmock_main PROPERTIES FOLDER lib/gtest)
    set_target_properties(gtest PROPERTIES FOLDER lib/gtest)
    set_target_properties(gtest_main PROPERTIES FOLDER lib/gtest)
endif()

###############################################
###           Library Directory             ###
###############################################

###############################################
###           Source Directory              ###
###############################################

add_subdirectory(src/util)
add_subdirectory(src/libaas)

if(BASYX_BUILD_API)
	add_subdirectory(src/api)
	add_subdirectory(src/http)
endif()


###############################################
###           Test Directory                ###
###############################################

if(BASYX_BUILD_TESTS)
    include( CTest )

    add_subdirectory(tests/tests_libaas)
    add_subdirectory(tests/tests_json)
	
	if(BASYX_BUILD_API)
		add_subdirectory(tests/tests_api)
	endif()
endif()

###############################################
###           Utility Projects              ###
###############################################

if(${BASYX_UTILITY_PROJECTS})
    enable_clang_format()
    enable_clang_tidy()
    enable_cppcheck()
endif()
