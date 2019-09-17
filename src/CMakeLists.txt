set(${PROJECT_NAME}_examples_src)

add_subdirectory(common)
add_subdirectory(estimation)
add_subdirectory(examples)

add_library(${PROJECT_NAME} ${${PROJECT_NAME}_src})
target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_LINKER_LIBS})
target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_PROTO_LIB})
target_include_directories(${PROJECT_NAME} PRIVATE ".")
install(TARGETS ${PROJECT_NAME} DESTINATION ${${PROJECT_NAME}_INSTALL_LIB_PREFIX})

foreach (${PROJECT_NAME}_example_src ${${PROJECT_NAME}_examples_src})
  get_filename_component(${PROJECT_NAME}_example_fil_we ${${PROJECT_NAME}_example_src} NAME_WE)
  add_executable(${${PROJECT_NAME}_example_fil_we} ${${PROJECT_NAME}_example_src})
  target_link_libraries(${${PROJECT_NAME}_example_fil_we} ${PROJECT_NAME})
  target_include_directories(${${PROJECT_NAME}_example_fil_we} PRIVATE ".")
  install(TARGETS ${${PROJECT_NAME}_example_fil_we} DESTINATION ${${PROJECT_NAME}_INSTALL_BIN_PREFIX})
endforeach ()
