########################################
###             basyxpp-http         ###
########################################

project(basyxpp-http)

set(SOURCE_FILES
		basyxpp-http/SubmodelRepositoryHttpHandler.cpp
		basyxpp-http/SubmodelHttpHandler.cpp
		basyxpp-http/HttpHandler.cpp
		)

set(HEADER_FILES
		basyxpp-http/SubmodelRepositoryHttpHandler.h
		basyxpp-http/SubmodelHttpHandler.h
		basyxpp-http/HttpHandler.h

	basyxpp-http/httplib/httplib.h
)

add_library(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${BASYX_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} 
	PUBLIC 
		BaSyx::libaas
		BaSyx::libutil
		BaSyx::api
)

add_library(BaSyx::http ALIAS basyxpp-http)

add_executable(basyxpp-http-exe basyxpp-http/main.cpp)
target_link_libraries(basyxpp-http-exe
	PUBLIC
		BaSyx::http
	)

build_source_group()
