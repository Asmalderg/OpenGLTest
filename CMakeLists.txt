cmake_minimum_required(VERSION 3.11)

project(test LANGUAGES CXX)

add_executable(test
	main.cpp
	ShaderManipulator.cpp
	Graphics.cpp
	Coordinates.h
	Figure.cpp
	ShaderManipulator.cpp
	Triangle.cpp
    Rectangle.cpp
    Circle.cpp
)

target_compile_definitions(test 
	PUBLIC 
		ASSETS_DIR="${CMAKE_SOURCE_DIR}/assets"
)

set_property(TARGET test PROPERTY CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
)

if(NOT glfw_POPULATED)
    FetchContent_Populate(glfw)

    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs" FORCE)
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs" FORCE)
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation" FORCE)
    set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")

    add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})

    target_include_directories(test
        PRIVATE ${glfw_SOURCE_DIR}/include
    )

    message(${glfw_SOURCE_DIR}/include)
    message(${glfw_BINARY_DIR}/src)
endif()

FetchContent_Declare(
        glad
        GIT_REPOSITORY https://github.com/Dav1dde/glad.git
)

FetchContent_GetProperties(glad)

if(NOT glad_POPULATED)
    FetchContent_Populate(glad)
    set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
    set(GLAD_API "gl=3.3" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
    set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
    add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})

    target_include_directories(test
        PRIVATE ${glad_BINARY_DIR}/include
    )
endif()

FetchContent_MakeAvailable(glad)

target_include_directories(test
	PRIVATE ${glad_BINARY_DIR}/include
)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
		GIT_TAG 0.9.9.8
)
if(NOT glm_POPULATED)
    target_include_directories(test
        PRIVATE ${glm_SOURCE_DIR}
    )
endif()

FetchContent_MakeAvailable(glm)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED GLUT)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(test
	PRIVATE 
		glfw
		glad
        glm
        ${OPENGL_LIBRARIES}
        GLUT::GLUT
)