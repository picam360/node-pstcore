#snipet cmake-js compile -G \"Visual Studio 15 2017 Win64\"
#snipet cmake-js compile -G \"Unix Makefiles\"

cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)
set (CMAKE_CXX_STANDARD 11)

project (node-pstcore)
include_directories(${CMAKE_JS_INC})
file(GLOB SOURCE_FILES "pstcore-napi.cpp")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

target_include_directories(${PROJECT_NAME} PRIVATE
	node_modules/node-addon-api/
)

if (WIN32)
	message("include win.cmake")
	include(cmake/win.cmake)
elseif (APPLE)
	message("include osx.cmake")
	include(cmake/osx.cmake)
elseif (UNIX)
	message("include linux.cmake")
	include(cmake/linux.cmake)
else ()
	message("unknown platform")
endif ()


# Define NAPI_VERSION
add_definitions(-DNAPI_VERSION=4)
