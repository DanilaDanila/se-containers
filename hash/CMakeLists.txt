project(hash)

add_executable(hash_test tests.cpp hash.h mm.h)
target_compile_options(hash_test PRIVATE -Wextra -Wall -Werror -fPIC)
