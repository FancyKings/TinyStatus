cmake_minimum_required(VERSION 3.17)

project(TinyStatus)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# Prevent in-situ build operations from contaminating the source directory
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR “In-source builds not allowed! Create a build directory and run CMake from there.”)
endif ()

# Json START
FetchContent_Declare(
        json
        GIT_REPOSITORY https://hub.fastgit.org/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
        GIT_TAG v3.9.1
        GIT_SHALLOW TRUE)
FetchContent_GetProperties(json)
if (NOT json_POPULATED)
    FetchContent_Populate(json)
    add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()
# Json END

# Spdlog START
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://hub.fastgit.org/gabime/spdlog.git
        GIT_TAG v1.8.5
        GIT_SHALLOW TRUE)
FetchContent_GetProperties(spdlog)
if (NOT spdlog_POPULATED)
    FetchContent_Populate(spdlog)
    add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()
# Spdlog END

# fmt START
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://hub.fastgit.org/fmtlib/fmt.git
        GIT_TAG 7.1.3
        GIT_SHALLOW TRUE
)
FetchContent_GetProperties(fmt)
if (NOT fmt_POPULATED)
    FetchContent_Populate(fmt)
    add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR} EXCLUDE_FROM_ALL)
endif ()
# fmt END

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/utils/logs)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/utils/cpu)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/utils/net)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/utils/conf)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/utils/memory)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/utils/connect)

add_executable(TinyStatus main.cpp)

target_compile_options(TinyStatus PRIVATE -Werror -Wall -Wextra)

target_link_libraries(TinyStatus PRIVATE Log)
target_link_libraries(TinyStatus PRIVATE CPU)
target_link_libraries(TinyStatus PRIVATE Memory)
target_link_libraries(TinyStatus PRIVATE Network)
target_link_libraries(TinyStatus PRIVATE Parser)
target_link_libraries(TinyStatus PRIVATE Connect)
target_link_libraries(TinyStatus PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(TinyStatus PRIVATE fmt::fmt)
