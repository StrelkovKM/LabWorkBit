# Get all cpp-files in the current directory
file(GLOB app_list RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)


foreach(app_filename ${app_list})
  # Get file name without extension
  get_filename_component(BitApp ${app_filename} NAME_WE)

  # Add and configure executable file to be produced
  add_executable(${BitApp} ${app_filename})
  target_link_libraries(${BitApp} ${BIT_LIBRARY})
  set_target_properties(${BitApp} PROPERTIES
    OUTPUT_NAME "${BitApp}"
    PROJECT_LABEL "${BitApp}"
    RUNTIME_OUTPUT_DIRECTORY "../")
endforeach()
