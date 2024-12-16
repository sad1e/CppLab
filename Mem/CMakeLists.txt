cmake_minimum_required(VERSION 3.20.0)
project(CppLearner)

set(MEM_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(MEM_SOURCES
    ../Common/core.h
    mem_common.cpp
    mem_common.h
    allocator.h
    callocator.cpp
    callocator.h
    io.h
    linear_allocator.cpp
    linear_allocator.h

    stl_simple_allocator.h
    stl_allocator_adapter.h

    membase.h
    membase.cpp
)

add_executable(mem_bench mem_bench.cpp ${MEM_SOURCES})
if(MSVC)
    target_compile_definitions(mem_bench PUBLIC UNICODE _UNICODE)
endif()
target_link_libraries(mem_bench PRIVATE benchmark::benchmark benchmark::benchmark_main)

add_executable(mem_test mem_test.cpp ${MEM_SOURCES})
if(MSVC)
    target_compile_definitions(mem_test PUBLIC UNICODE _UNICODE)
endif()
