
set(TARGET_ARCH ${CMAKE_HOST_SYSTEM_PROCESSOR})
#set(TARGET_ARCH "aarch64")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW glfw3 REQUIRED)
pkg_check_modules(GLEW glew>=2.1 REQUIRED)
pkg_check_modules(LIBJPEG libjpeg REQUIRED)
pkg_check_modules(LIBJPEG libpng REQUIRED)
pkg_check_modules(LIBCURL libcurl REQUIRED)
pkg_check_modules(LIBDE265 libde265 REQUIRED)

target_link_directories(${PROJECT_NAME} PRIVATE
	${GLFW_LIBRARY_DIRS}
	${GLEW_LIBRARY_DIRS}
	${LIBJPEG_LIBRARY_DIRS}
	${LIBPNG_LIBRARY_DIRS}
	#${LIBCURL_LIBRARY_DIRS}
	${LIBDE265_LIBRARY_DIRS}
)

target_link_libraries(${PROJECT_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/pstcore/lib/picam360/${TARGET_ARCH}/libpstcore.a
	${GLFW_STATIC_LIBRARIES}
	${GLEW_STATIC_LIBRARIES}
	${LIBJPEG_STATIC_LIBRARIES}
	${LIBPNG_STATIC_LIBRARIES}
	#${LIBCURL_STATIC_LIBRARIES}
	${LIBDE265_STATIC_LIBRARIES}
	uuid
	curl
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/lib/linux/pstcore/include/picam360/pstcore
)
