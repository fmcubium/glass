cmake_minimum_required(VERSION 3.20)

project(Test
    VERSION 1.0.0
    DESCRIPTION "TBA"
    LANGUAGES CXX
)

# ── Global settings ────────────────────────────────────────────────────────────
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
 
# Export compile commands for tooling (clangd, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
 
# ── Target ─────────────────────────────────────────────────────────────────────
add_executable(${PROJECT_NAME})
 
target_sources(${PROJECT_NAME} PRIVATE
    src/main.cpp
    src/parse/lexer.cpp
    src/parse/token.cpp
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ── Compiler warnings ──────────────────────────────────────────────────────────
target_compile_options(${PROJECT_NAME} PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:
        -Wall -Wextra -Wpedantic -Wconversion>
    $<$<CXX_COMPILER_ID:MSVC>:
        /W4 /WX>
)
 
# ── Install rules ──────────────────────────────────────────────────────────────
install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION bin
)
