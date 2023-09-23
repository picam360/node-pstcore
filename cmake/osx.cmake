
set(TARGET_ARCH "x86_64")

find_package(PkgConfig REQUIRED)

set(PSTCOREDIR "osx")

execute_process(
    COMMAND 7z x -aoa ${PSTCOREDIR}.7z
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
    RESULT_VARIABLE result
)
if(result)
    message(FATAL_ERROR "Error extracting lib: ${result}")
endif()

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/lib/osx/pstcore/lib/picam360/${TARGET_ARCH}/libpstcore.dylib
                ${CMAKE_CURRENT_BINARY_DIR}/Release/libpstcore.dylib
)
file(GLOB EXTFILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/osx/ext/*.dylib)
foreach(_EXT_FILE IN LISTS EXTFILES)
    add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${_EXT_FILE}
                        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/)
endforeach()
                
target_link_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}/Release
)

target_link_libraries(${PROJECT_NAME}
	pstcore
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/lib/osx/pstcore/include/picam360/pcommon
	${CMAKE_CURRENT_SOURCE_DIR}/lib/osx/pstcore/include/picam360/pstcore
)
