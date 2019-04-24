macro (do_test exe)
  add_executable(${exe} "${exe}.c")
  target_link_libraries(${exe} PRIVATE mvoputils)
  add_test("${exe}_test" ${exe})
endmacro (do_test)

do_test(sls_lu)
do_test(lu)
do_test(dgeaxpxmv)
do_test(powerIt)

