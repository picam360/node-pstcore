
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

execute_process(
    COMMAND 7z x -aoa ${PSTCOREDIR}.7z
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib
    RESULT_VARIABLE result
)
if(result)
    message(FATAL_ERROR "Error extracting lib: ${result}")
endif()

if (TEGRA)
        set(L4T_VERSION $ENV{L4T_VERSION})
        if(DEFINED L4T_VERSION)
                message(STATUS "L4T Version from ENV: ${L4T_VERSION}")
        else()
                execute_process(
                        COMMAND dpkg-query --show nvidia-l4t-core
                        RESULT_VARIABLE command_result
                        OUTPUT_VARIABLE L4T_PACKAGE_INFO
                        ERROR_QUIET
                        OUTPUT_STRIP_TRAILING_WHITESPACE
                )
                if(NOT command_result EQUAL 0) # command failed
                        set(L4T_VERSION "0.0")
                else()
                        string(REGEX MATCH "nvidia-l4t-core[ \t]+([0-9]+\\.[0-9]+\\.[0-9]+)" _ ${L4T_PACKAGE_INFO})
                        set(L4T_VERSION ${CMAKE_MATCH_1})
                endif()
                message(STATUS "L4T Version: ${L4T_VERSION}")
        endif()


        if(L4T_VERSION VERSION_GREATER_EQUAL "32.5" AND L4T_VERSION VERSION_LESS_EQUAL "32.7.4")
                message(STATUS "JP46")
                execute_process(
                        COMMAND ${CMAKE_COMMAND} -E copy
                                ${CMAKE_CURRENT_SOURCE_DIR}/lib/${PSTCOREDIR}/pstcore/lib/picam360/${TARGET_ARCH}/libpstcore.so.jp46
                                ${CMAKE_CURRENT_SOURCE_DIR}/lib/${PSTCOREDIR}/pstcore/lib/picam360/${TARGET_ARCH}/libpstcore.so
                )
        else()
                message(STATUS "JP51")
                execute_process(
                        COMMAND ${CMAKE_COMMAND} -E copy
                                ${CMAKE_CURRENT_SOURCE_DIR}/lib/${PSTCOREDIR}/pstcore/lib/picam360/${TARGET_ARCH}/libpstcore.so.jp51
                                ${CMAKE_CURRENT_SOURCE_DIR}/lib/${PSTCOREDIR}/pstcore/lib/picam360/${TARGET_ARCH}/libpstcore.so
                )

        endif()
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
