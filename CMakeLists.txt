cmake_minimum_required(VERSION 3.26)

include(cmake/modules.cmake)
include(GitVersion)

project(timber
    VERSION ${GIT_VERSION_ABBREV}
    DESCRIPTION "C++ logging library"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS NO)

include(ProjectTesting)
include(packages.cmake)

add_library(timber "")
add_library(timber::timber ALIAS timber)

target_sources(timber PUBLIC FILE_SET HEADERS BASE_DIRS include)
target_link_libraries(timber PUBLIC fmt::fmt)

if(PROJECT_TESTING)
    add_executable(console "")
    target_link_libraries(console PRIVATE timber)
    add_test("Console Printer" console)
endif()

add_subdirectory(include)
add_subdirectory(src)

include(Sanitizers)
enable_asan()

include(EasyInstall)
easy_install(TARGETS timber DEPENDENCIES fmt)

if(PROJECT_IS_TOP_LEVEL)
    add_custom_target(docker
        docker build --progress=plain --no-cache .
        WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        USES_TERMINAL
    )
endif()
