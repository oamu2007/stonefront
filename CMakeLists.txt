cmake_minimum_required(VERSION 3.20)
project(Stonefront LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---------------------------------------------------------------------------
# Dependencies
# ---------------------------------------------------------------------------
include(FetchContent)

# SFML 3 — pulled via FetchContent so the repo doesn't require a system-wide
# SFML install. First configure will take a while; subsequent ones are cached.
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG        3.0.0
    GIT_SHALLOW    ON
)
FetchContent_MakeAvailable(SFML)

# nlohmann/json — header-only, used for rock/customer/event data files.
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.11.3
    GIT_SHALLOW    ON
)
FetchContent_MakeAvailable(json)

# ---------------------------------------------------------------------------
# Main executable
# ---------------------------------------------------------------------------
file(GLOB_RECURSE STONEFRONT_SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(Stonefront ${STONEFRONT_SOURCES})

target_include_directories(Stonefront PRIVATE include)

target_link_libraries(Stonefront PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
    SFML::Audio
    nlohmann_json::nlohmann_json
)

# Copy assets next to the built binary so relative paths ("assets/...") work
# the same in-IDE and from a packaged build.
add_custom_command(TARGET Stonefront POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:Stonefront>/assets
)

# ---------------------------------------------------------------------------
# Tests (optional, enable once tests/ has content)
# ---------------------------------------------------------------------------
option(STONEFRONT_BUILD_TESTS "Build unit tests" OFF)
if(STONEFRONT_BUILD_TESTS)
    add_subdirectory(tests)
endif()
