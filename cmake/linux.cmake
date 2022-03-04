
set(TARGET_ARCH ${CMAKE_HOST_SYSTEM_PROCESSOR})
#set(TARGET_ARCH "aarch64")

find_file(BCM_HOST bcm_host.h /opt/vc/include)
find_file(TEGRA tegra_drm.h /usr/include/drm)
if (BCM_HOST)
	set(PSTCOREDIR "rpi")
elseif (TEGRA)
	set(PSTCOREDIR "jetson")
else ()
	set(PSTCOREDIR "linux")
endif ()

find_package(PkgConfig REQUIRED)

#search path $ORIGIN first
set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-rpath,$ORIGIN")

add_custom_command(
        TARGET ${PROJECT_NAME} PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/lib/${PSTCOREDIR}/pstcore/lib/picam360/${TARGET_ARCH}/libpstcore.so
                ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/libpstcore.so)
                
file(GLOB DEPENDS_MODULES ${CMAKE_CURRENT_SOURCE_DIR}/lib/${PSTCOREDIR}/depends/${TARGET_ARCH}/*)
foreach(_FILE IN LISTS DEPENDS_MODULES)
    add_custom_command(
                TARGET ${PROJECT_NAME} PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${_FILE}
                        ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/)
endforeach()

#target_link_directories(${PROJECT_NAME} PRIVATE
#)

target_link_libraries(${PROJECT_NAME}
	${CMAKE_CURRENT_SOURCE_DIR}/lib/${PSTCOREDIR}/pstcore/lib/picam360/${TARGET_ARCH}/libpstcore.so
)

target_include_directories(${PROJECT_NAME} PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/lib/${PSTCOREDIR}/pstcore/include/picam360/pcommon
	${CMAKE_CURRENT_SOURCE_DIR}/lib/${PSTCOREDIR}/pstcore/include/picam360/pstcore
)
