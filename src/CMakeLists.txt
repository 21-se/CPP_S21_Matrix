cmake_minimum_required(VERSION 3.15)
project(s21_matrxi_opp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Werror -Wextra)

# Подключение GTest через FetchContent
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)

# Принудительное использование GTest общей среды выполнения в Windows 
# (обычно это необязательно)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB SOURCES "*.cpp")
file(GLOB TEST_SOURCES "tests/*.cpp")

add_library(s21_matrix_oop STATIC ${SOURCES})

add_executable(run_tests ${TEST_SOURCES})

# Линковка
target_link_libraries(run_tests PRIVATE
  s21_matrix_oop
  gtest
  gtest_main
  pthread
)

enable_testing()
add_test(NAME AllTests COMMAND run_tests)

file(GLOB_RECURSE ALL_CXX_FILES *.cpp *.h)
add_custom_target(format
  COMMAND clang-format --style=Google -i ${ALL_CXX_FILES}
)

add_custom_target(check-format
  COMMAND clang-format --style=Google -n ${ALL_CXX_FILES}
)

add_custom_target(cppcheck
  COMMAND cppcheck --enable=all --check-level=exhaustive 
  --suppress=missingIncludeSystem 
  --suppress=*:*_deps*
  .
)

add_custom_target(valgrind
  COMMAND valgrind --leak-check=full --show-leak-kinds=all ./run_tests
  DEPENDS run_tests
)

add_custom_target(gcov_report
  COMMAND ${CMAKE_COMMAND} -DCMAKE_CXX_FLAGS="--coverage" ..
  COMMAND ${CMAKE_COMMAND} --build .
  COMMAND ./run_tests
  COMMAND ${CMAKE_COMMAND} -E make_directory coverage_report
  COMMAND gcovr -r .. 
          --html --html-details 
          --output coverage_report/coverage_report.html 
          --filter "\\.\\./[^/]+\\.cpp"
          --exclude ".*tests/.*"
          --exclude-unreachable-branches
          --print-summary
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)
