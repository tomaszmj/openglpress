cmake_minimum_required (VERSION 3.0)
project(gkom)

set(CMAKE_CXX_STANDARD 11)
find_package(OpenGL REQUIRED)
add_definitions(${OPENGL_DEFINITIONS})
include_directories("include")
FILE(GLOB SRC_LIST "src/*.cpp")
FILE(GLOB HEADER_LIST "include/*.h")
FILE(GLOB SHADERS "resources/shaders/*")

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message("Running Windows build configuration.")
    set(GLFW_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/win32/include/GLFW )
    set(GLEW_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/win32/include/GL )
    set(SOIL_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/win32/include/ )
    set(GLM_INCLUDE_PATH ${CMAKE_SOURCE_DIR}/win32/include/glm )
    set(GLFW_LIBRARY ${CMAKE_SOURCE_DIR}/win32/lib/glfw3 )
    set(GLEW_LIBRARY ${CMAKE_SOURCE_DIR}/win32/lib/glew32s )
    set(SOIL_LIBRARY ${CMAKE_SOURCE_DIR}/win32/lib/SOIL )
    include_directories(
        ${GLFW_INCLUDE_PATH}
        ${GLEW_INCLUDE_PATH}
        ${GLM_INCLUDE_PATH}
        ${SOIL_INCLUDE_PATH}
        "include"
    )
    message(STATUS "src ${SRC_LIST}")
    message(STATUS "src ${HEADER_LIST}")
    set(LIBS ${OPENGL_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${SOIL_LIBRARY} legacy_stdio_definitions)
    set (CMAKE_C_FLAGS "-m32")
    set (CMAKE_CXX_FLAGS "-m32")

elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message("Running Linux build configuration.")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
    find_package(GLFW3 REQUIRED)
    message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")
    find_package(SOIL REQUIRED)
    message(STATUS "Found SOIL in ${SOIL_INCLUDE_DIR}")
    find_package(GLEW REQUIRED)
    message(STATUS "Found GLEW in ${GLEW_INCLUDE_DIR}")
    find_package(GLM REQUIRED)
    message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

    set(DEFAULT_FLAGS "-Wall -pedantic -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${DEFAULT_FLAGS} -O0 -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${DEFAULT_FLAGS} -Werror -O3 -DNDEBUG")
    set(LIBS ${OPENGL_LIBRARY} ${GLEW_LIBRARY} ${GLFW3_LIBRARY} ${SOIL_LIBRARY})

else(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    message("Unsupported OS, try hand-editing Linux configuraion.")
endif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")    
    
add_executable(${PROJECT_NAME} ${SRC_LIST} ${HEADER_LIST} ${SHADERS})
target_link_libraries(${PROJECT_NAME} ${LIBS})
    
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD    
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/resources
        ${CMAKE_CURRENT_BINARY_DIR}/resources)
