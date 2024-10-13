cmake_minimum_required(VERSION 3.16.0)
project(thin-walls)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

option(LIBIGL_INSTALL             "Enable installation of libigl targets"  ON)
option(LIBIGL_COPYLEFT_CORE       "Build target igl_copyleft::core"        ON)
option(LIBIGL_GLFW                "Build target igl::glfw"                 ON)

include(FetchContent)
FetchContent_Declare(
    libigl
    GIT_REPOSITORY https://github.com/libigl/libigl.git
    GIT_TAG v2.4.0
)
FetchContent_MakeAvailable(libigl)

igl_include(core)

add_executable(
    ${PROJECT_NAME}
        
        src/thinwalls.cpp
        src/main.cpp
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        igl::core
        igl::glfw
        Eigen3::Eigen
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
