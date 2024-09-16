cmake_minimum_required(VERSION 3.27)
project(threadSafeQueue)

set(CMAKE_CXX_STANDARD 23)

add_executable(threadSafeQueue main.cpp
        Thread_pool/Thread_pool.cpp
        Safe_queue/Safe_queue.cpp)
