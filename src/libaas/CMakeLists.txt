########################################
###               AAS                ###
########################################

set (BASYX_AAS_LIB_SHORTNAME "basyx_metamodel")
set (BASYX_AAS_LIBRARY_NAME "${PROJECT_SHORTNAME}${BASYX_AAS_LIB_SHORTNAME}")
set (BASYX_AAS_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

include(sources.cmake)

add_library(${BASYX_AAS_LIB_SHORTNAME} ${SOURCE_FILES_BASYX} ${HEADER_FILES_BASYX})

set_target_properties(${BASYX_AAS_LIB_SHORTNAME}
   PROPERTIES VERSION ${PROJECT_VERSION}
)

set_target_properties(${BASYX_AAS_LIB_SHORTNAME}
   PROPERTIES PREFIX "${CMAKE_STATIC_LIBRARY_PREFIX}${PROJECT_SHORTNAME}"
)

target_include_directories(${BASYX_AAS_LIB_SHORTNAME}
   PUBLIC
   $<BUILD_INTERFACE:${BASYX_AAS_INCLUDE_DIR}>
   $<INSTALL_INTERFACE:${CMAKE_INSTALL_PREFIX}/include>
)

target_link_libraries(${BASYX_AAS_LIB_SHORTNAME}
   PUBLIC
       BaSyx::libutil
       nlohmann_json::nlohmann_json
       pugixml::pugixml
)

add_library(BaSyx::libaas ALIAS ${BASYX_AAS_LIB_SHORTNAME})
add_library(basyx::libaas ALIAS ${BASYX_AAS_LIB_SHORTNAME})
add_library(${PROJECT_SHORTNAME}::${BASYX_AAS_LIB_SHORTNAME} ALIAS ${BASYX_AAS_LIB_SHORTNAME})

build_source_group()

if(${BASYX_INSTALL_SDK})

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/${BASYX_AAS_LIBRARY_NAME}Config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/${BASYX_AAS_LIBRARY_NAME}Config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_AAS_LIBRARY_NAME}
    PATH_VARS
    CMAKE_INSTALL_PREFIX
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BASYX_AAS_LIBRARY_NAME}Config.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_AAS_LIBRARY_NAME}
)

install(EXPORT ${BASYX_AAS_LIB_SHORTNAME}Targets
        NAMESPACE ${PROJECT_SHORTNAME}::
        FILE ${BASYX_AAS_LIBRARY_NAME}Targets.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${BASYX_AAS_LIBRARY_NAME}
)

install(TARGETS ${BASYX_AAS_LIB_SHORTNAME}
        EXPORT ${BASYX_AAS_LIB_SHORTNAME}Targets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# Install all headers except the private folder priv*.h headers
install(DIRECTORY "${BASYX_AAS_INCLUDE_DIR}/${PROJECT_INCLUDENAME}"
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
        FILES_MATCHING PATTERN "*.h"
        PATTERN "private" EXCLUDE
)
endif()

diagnostics_print(${BASYX_AAS_LIB_SHORTNAME})
