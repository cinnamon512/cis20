cmake_minimum_required(VERSION 4.3)
project(ch2_ex_1 C)

set(CMAKE_C_STANDARD 11)

add_executable(ch2_ex_1
        ch2_array_pointer.c
        ch2_data_type_sizes.c
        ch2_malloc.c
        ch2_pointer.c
        ch2_pointer_size.c
        ch2_xy_1.c
        ch2_xy_2.c)
