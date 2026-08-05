cmake_minimum_required(VERSION 3.20)

project(
  Calculator
  VERSION 0.1.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_ASAN "Enable AddressSanitizer and UndefinedBehaviorSanitizer" ON)
option(BUILD_TESTS "Build tests" ON)

# ---------------------------
# Compiler warnings
# ---------------------------

add_library(project_warnings INTERFACE)

target_compile_options(project_warnings INTERFACE
  -Wall
  -Wextra
  -Wpedantic
  -Wshadow
  -Wconversion
  -Wsign-conversion
  -Wunused
)


# ---------------------------
# Sanitizers
# ---------------------------

if(ENABLE_ASAN)

  include(CheckCXXCompilerFlag)

  check_cxx_compiler_flag(
    "-fsanitize=address,undefined"
    HAS_SANITIZERS
  )

  if(HAS_SANITIZERS)
    target_compile_options(project_warnings INTERFACE
      -fsanitize=address,undefined
      -fno-omit-frame-pointer
      -g
    )

    target_link_options(project_warnings INTERFACE
      -fsanitize=address,undefined
      -fno-omit-frame-pointer
    )

    message(STATUS "Sanitizers enabled")
  else()
    message(WARNING "Sanitizers not supported")
  endif()

endif()


# ---------------------------
# Main executable
# ---------------------------

add_executable(Calculator
  main.cpp
  src/Calculator.cpp

  src/InputProcessor.cpp
  src/CommandExecutor.cpp

  src/Token.cpp
  src/Utils.cpp

  src/Lexer.cpp
  src/Parser.cpp
  src/Evaluator.cpp

  src/Constant.cpp
  src/Function.cpp

  src/Context.cpp

  src/Evaluator.cpp
  src/History.cpp
)

target_link_libraries(Calculator PRIVATE
  project_warnings
)


# ---------------------------
# Tests
# ---------------------------

if(BUILD_TESTS)

  include(FetchContent)

  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
  )

  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

  FetchContent_MakeAvailable(googletest)


  enable_testing()

  add_executable(
    CalculatorTests
    tests/main.cpp
  )

  target_link_libraries(
    CalculatorTests
    PRIVATE
    GTest::gtest_main
    project_warnings
  )

  include(GoogleTest)

  gtest_discover_tests(CalculatorTests)

endif()
