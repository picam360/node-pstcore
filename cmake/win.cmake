
set(TARGET_ARCH "x86_64")

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/lib/win/pstcore/lib/picam360/${TARGET_ARCH}/libpstcore.dll
                ${CMAKE_CURRENT_BINARY_DIR}/Release/libpstcore.dll
)
file(GLOB MING_DLLS ${CMAKE_CURRENT_SOURCE_DIR}/lib/win/mingw/*.dll)
foreach(_DLL_FILE IN LISTS MING_DLLS)
    add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${_DLL_FILE}
                        ${CMAKE_CURRENT_BINARY_DIR}/Release/)
endforeach()

target_link_directories(${PROJECT_NAME} PRIVATE
)

target_link_libraries(${PROJECT_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/lib/win/pstcore/lib/picam360/${TARGET_ARCH}/libpstcore.lib
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/lib/win/pstcore/include/picam360/pstcore
)