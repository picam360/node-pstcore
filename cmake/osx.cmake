
set(TARGET_ARCH "x86_64")

find_package(PkgConfig REQUIRED)

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
