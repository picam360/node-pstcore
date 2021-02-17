
set(TARGET_ARCH ${CMAKE_HOST_SYSTEM_PROCESSOR})
#set(TARGET_ARCH "aarch64")

find_file(BCM_HOST bcm_host.h /opt/vc/include)
if (BCM_HOST)
	set(PSTCOREDIR "rpi")
else ()
	set(PSTCOREDIR "linux")
endif ()

find_package(PkgConfig REQUIRED)

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/lib/${PSTCOREDIR}/pstcore/lib/picam360/${TARGET_ARCH}/libpstcore.so
                ${CMAKE_CURRENT_BINARY_DIR}/Release/libpstcore.so
)
                
target_link_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_BINARY_DIR}/Release
)

target_link_libraries(${PROJECT_NAME}
	pstcore
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/lib/${PSTCOREDIR}/pstcore/include/picam360/pcommon
	${CMAKE_CURRENT_SOURCE_DIR}/lib/${PSTCOREDIR}/pstcore/include/picam360/pstcore
)
