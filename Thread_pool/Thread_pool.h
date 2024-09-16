//
// Created by user on 15.09.2024.
//
#pragma once
#include <thread>
#include <vector>
#include "../Safe_queue/Safe_queue.h"

class Thread_pool {
private:
    std::vector<std::thread> thr_vec;
    Safe_queue<std::function<void()>> task_queue;
    bool stop = false;

    void work() {
        while (true) {
            std::function<void()> task = task_queue.pop();
            if (task) {
                task();
            } else if (stop) {
                return;
            }
        }
    }

public:
    Thread_pool() {
        unsigned int threadCounts = (std::thread::hardware_concurrency());
        for (unsigned int i = 0; i < threadCounts; i++) {
            thr_vec.emplace_back([this] { work(); });
        }
    }

    ~Thread_pool() {
        stop = true;
        task_queue.stop_queue();
        for (auto& t : thr_vec) {
            if (t.joinable()) {
                t.join();
            }
        }
        thr_vec.clear();
    }

    void submit(const std::function<void()>& func) {
        task_queue.push(func);
    }
};

