#pragma once
#include <queue>
#include <functional>
#include <condition_variable>
#include <mutex>

template <typename T>
class Safe_queue {
private:
    std::queue<T> queue;
    std::mutex mtx;
    std::condition_variable cv;
    bool stop = false;

public:
    void push(const T& func){
        std::unique_lock<std::mutex> lock(this->mtx);
        queue.push(func);
        cv.notify_one();
    }

    T pop(){
        std::unique_lock<std::mutex> lock(this->mtx);
        cv.wait(lock, [this]{ return !queue.empty() || stop; });
        if (queue.empty()) {
            return {};
        }
        T value = std::move(queue.front());
        queue.pop();
        return value;
    }

    void stop_queue() {
        std::unique_lock<std::mutex> lock(this->mtx);
        stop = true;
        cv.notify_all();
    }

    [[nodiscard]] bool is_stopped() const {
        return stop;
    }
};
