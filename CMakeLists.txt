cmake_minimum_required(VERSION 3.28)
project(Silicomatica)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Path to the libraries
set(GLEW_DIR "C:/libs/glew")
set(GLFW_DIR "C:/libs/glfw")
set(GLM_DIR "C:/libs/glm")
set(GLAD_DIR "C:/libs/glad")
set(IMAGER_DIR "C:/libs/imager")

# Include directories for GLEW, GLFW, and GLM
include_directories(${GLEW_DIR}/include ${GLFW_DIR}/include ${GLM_DIR}  ${GLAD_DIR}/include ${PROJECT_SOURCE_DIR}/src ${IMAGER_DIR})

# Link directories for GLEW and GLFW
link_directories(${GLEW_DIR}/lib/Release/x64 ${GLFW_DIR}/lib-mingw-w64)

file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable
add_executable(Silicomatica main.cpp ${GLAD_DIR}/src/glad.c ${SOURCES})

# Link the libraries - only link against the dynamic version (glew32) if you are dynamically linking
target_link_libraries(Silicomatica opengl32 glfw3 glew32)

target_link_libraries(Silicomatica)

# Copy the GLEW DLL to the same folder as the executable after building
add_custom_command(TARGET Silicomatica POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${GLEW_DIR}/bin/Release/x64/glew32.dll"
        "$<TARGET_FILE_DIR:Silicomatica>")
