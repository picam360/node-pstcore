
set(TARGET_ARCH "x86_64")

target_link_directories(${PROJECT_NAME} PRIVATE
)

target_link_libraries(${PROJECT_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/../../build/win/pstcore/lib/picam360/${TARGET_ARCH}/libpstcore.lib
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/../../include
	${CMAKE_CURRENT_SOURCE_DIR}/../../lib
)