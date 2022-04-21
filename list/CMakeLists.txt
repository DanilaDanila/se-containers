project(list)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_executable(list_test tests.cpp list.h)
add_executable(list_terminal list_console.cpp list.h)
