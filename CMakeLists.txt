cmake_minimum_required(VERSION 3.20.0)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_WARN_DEPRECATED OFF CACHE BOOL "" FORCE)

project(CppLearner  VERSION 0.0.1
                    DESCRIPTION "CppLearner"
                    LANGUAGES CXX)


add_subdirectory(Mem)