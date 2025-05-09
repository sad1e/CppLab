cmake_minimum_required(VERSION 3.20.0)
project(CppTest)

# set(MEM_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(TEST_SOURCES
    Template.cpp
)

add_executable(Template ${TEST_SOURCES})
if(MSVC)
    target_compile_definitions(Template PUBLIC UNICODE _UNICODE)
endif()
# target_link_libraries(Test PRIVATE benchmark::benchmark benchmark::benchmark_main)

# add_executable(mem_test mem_test.cpp ${MEM_SOURCES})
# if(MSVC)
#     target_compile_definitions(mem_test PUBLIC UNICODE _UNICODE)
# endif()
