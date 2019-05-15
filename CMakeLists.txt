cmake_minimum_required(VERSION 3.8.2...3.14)

project(LARC VERSION 1.0 LANGUAGES C)

add_subdirectory(check)
add_subdirectory(utils)

include(CTest)
enable_testing()
add_subdirectory(tests)

if (ENABLE_FILE_OP)
  add_subdirectory(file_op/seq)
endif()
