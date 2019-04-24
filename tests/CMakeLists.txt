add_executable(lu lu.c)
target_link_libraries(lu PRIVATE mvoputils)
add_test(lutest lu)
