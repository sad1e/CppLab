cmake_minimum_required(VERSION 3.20.0)
project(CppLearner)

set(TARGET Mem)
set(MEM_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(MEM_SOURCES
    mem_common.h
    allocator.h
    benchmark.cpp
    benchmark.h
    callocator.cpp
    callocator.h
    io.h
    linear_allocator.cpp
    linear_allocator.h

    membase.h
    membase.cpp

    mem_bench.cpp
)

add_executable(${TARGET} ${MEM_SOURCES})
if (MSVC)
    target_compile_definitions(${TARGET} PUBLIC UNICODE _UNICODE)
endif ()
target_link_libraries(${TARGET} PRIVATE benchmark::benchmark benchmark::benchmark_main)