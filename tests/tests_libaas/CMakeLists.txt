###############################################
###              tests_libaas               ###
###############################################

cmake_minimum_required(VERSION 3.1.0)

project(tests_libaas)

file(GLOB_RECURSE SOURCE_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.h)

message(STATUS "${PROJECT_NAME}")
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} 
	BaSyx::libaas
	BaSyx::libutil
	gtest_main
)

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER tests)

diagnostics_print(${PROJECT_NAME})

gtest_discover_tests(${PROJECT_NAME})
