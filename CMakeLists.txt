cmake_minimum_required(VERSION 3.20)

project(helang_test
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)

add_executable(helang_test
    main.c
    power.c
    helang.c
)