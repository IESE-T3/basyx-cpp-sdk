########################################
###                 api              ###
########################################

project(basyx_api)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS *.cpp)
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS *.h)

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} 
	PUBLIC	
		BaSyx::libaas
)

add_library(basyx::api ALIAS ${PROJECT_NAME})
add_library(BaSyx::api ALIAS ${PROJECT_NAME})

build_source_group()
diagnostics_print(${PROJECT_NAME})
