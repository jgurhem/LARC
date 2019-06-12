add_executable(check_results check_results.c)
target_link_libraries(check_results PRIVATE mvoputils)
install (TARGETS check_results DESTINATION bin)
target_compile_features(check_results PRIVATE c_std_11)

add_executable(print_field print_field.c)
target_link_libraries(print_field PRIVATE mvoputils)
install (TARGETS print_field DESTINATION bin)
target_compile_features(print_field PRIVATE c_std_11)

add_executable(print_3Dfield print_3Dfield.c)
target_link_libraries(print_3Dfield PRIVATE mvoputils)
install (TARGETS print_3Dfield DESTINATION bin)
target_compile_features(print_3Dfield PRIVATE c_std_11)

