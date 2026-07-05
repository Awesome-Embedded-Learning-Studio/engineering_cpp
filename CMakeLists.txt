# =============================================================================
# engineering-cpp —— 现代 C++ 工程实践 hub 仓的根构建脚本
# =============================================================================
# 设计要点(见 refactor 计划阶段 1 A2):
#   - 统一 C++23(DirScanner 从 C++17 升上来)
#   - argparser 是共享库(消双源后的唯一源头,替代 src/DirScanner/third_party 副本)
#   - 不 add_subdirectory 子项目:它们的 CMakeLists 自带 project(),会触发多 project 警告
#     根直接定义所有 target,子项目 CMakeLists 已移除
#   - 纯 CMake,无 vcpkg:本仓零外部依赖,clone 即 build
#   - Catch2 是全仓唯一 test framework,FetchContent 一次
# =============================================================================
cmake_minimum_required(VERSION 3.25)
project(engineering-cpp VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)  # 自动 enable_testing() + BUILD_TESTING 默认 ON

option(HUB_BUILD_ARGPARSER  "Build ArgParser demo"      ON)
option(HUB_BUILD_FILECOPIER "Build FileCopier demo"     ON)
option(HUB_BUILD_DIRSCANNER "Build DirScanner demo"     ON)
option(HUB_BUILD_TESTS      "Build unit tests (Catch2)" ON)

# ── 共享库:argparser(消双源后的唯一源头)─────────────────────────
add_library(argparser STATIC src/ArgParser/ArgParser.cpp)
target_include_directories(argparser PUBLIC src/ArgParser)

# ── Catch2(全仓唯一 test framework,FetchContent 一次)────────────
if(BUILD_TESTING AND HUB_BUILD_TESTS)
  include(FetchContent)
  FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG        v3.5.2)
  FetchContent_MakeAvailable(Catch2)
endif()

# ── ArgParser demo ──────────────────────────────────────────────
if(HUB_BUILD_ARGPARSER)
  add_executable(argparser_demo src/ArgParser/demo.cpp)
  target_link_libraries(argparser_demo PRIVATE argparser)
endif()

# ── FileCopier demo ─────────────────────────────────────────────
if(HUB_BUILD_FILECOPIER)
  add_executable(fcopy src/FileCopier/FileCopier.cpp src/FileCopier/demo.cpp)
  target_include_directories(fcopy PRIVATE src/FileCopier)
endif()

# ── DirScanner(lib + demo + test)────────────────────────────────
# dir_scan.cpp 不依赖 ArgParser;只有 main.cpp 用 ArgParser。
if(HUB_BUILD_DIRSCANNER)
  add_library(dirscanner_lib STATIC src/DirScanner/src/dir_scan.cpp)
  target_include_directories(dirscanner_lib PUBLIC src/DirScanner/src)

  add_executable(dirscanner src/DirScanner/src/main.cpp)
  target_link_libraries(dirscanner PRIVATE dirscanner_lib argparser)

  if(BUILD_TESTING AND HUB_BUILD_TESTS)
    add_executable(dirscanner_test src/DirScanner/test/test.cpp)
    target_link_libraries(dirscanner_test PRIVATE dirscanner_lib Catch2::Catch2WithMain)
    add_test(NAME dirscanner_test COMMAND dirscanner_test)
  endif()
endif()

# ── ArgParser tests ─────────────────────────────────────────────
if(BUILD_TESTING AND HUB_BUILD_TESTS)
  add_executable(argparser_test src/ArgParser/test/argparser_test.cpp)
  target_link_libraries(argparser_test PRIVATE argparser Catch2::Catch2WithMain)
  add_test(NAME argparser_test COMMAND argparser_test)
endif()
