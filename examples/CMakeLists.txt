file(GLOB examples "*.c")
foreach(example ${examples})
  # extract filename without extension and use it as test executable's name
  get_filename_component(example_name ${example} NAME_WE)
  add_executable(${example_name} ${example})

  # link against cthings framework
  target_link_libraries(${example_name} rose)
endforeach()
