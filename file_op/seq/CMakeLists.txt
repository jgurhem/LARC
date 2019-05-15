macro (add_exe exe)
  add_executable(${exe} "${exe}.c")
  target_link_libraries(${exe} PRIVATE mvoputils)
  install (TARGETS ${exe} DESTINATION bin)
endmacro (add_exe)


add_exe(initv)
add_test(initv_test initv 5 99 v.bin)
add_exe(initm)
add_test(initm_test initm 5 5 88 m.bin)
add_exe(pmm1)
add_exe(pmm2)
add_exe(pmv)
add_exe(inv_gj)
add_exe(pmm_d)
add_exe(pmv_d)

