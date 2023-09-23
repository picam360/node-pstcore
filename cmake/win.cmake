
set(TARGET_ARCH "x86_64")

set(PSTCOREDIR "win")

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
                ${CMAKE_CURRENT_SOURCE_DIR}/lib/win/pstcore/lib/picam360/${TARGET_ARCH}/libpstcore.dll
                ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/libpstcore.dll
)
file(GLOB MING_DLLS ${CMAKE_CURRENT_SOURCE_DIR}/lib/win/mingw/*.dll)
foreach(_DLL_FILE IN LISTS MING_DLLS)
    add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${_DLL_FILE}
                        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/)
endforeach()

target_link_directories(${PROJECT_NAME} PRIVATE
)

target_link_libraries(${PROJECT_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/lib/win/pstcore/lib/picam360/${TARGET_ARCH}/libpstcore.lib
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/lib/win/pstcore/include/picam360/pcommon
	${CMAKE_CURRENT_SOURCE_DIR}/lib/win/pstcore/include/picam360/pstcore
	${CMAKE_CURRENT_SOURCE_DIR}/lib/win/pthread/include
)