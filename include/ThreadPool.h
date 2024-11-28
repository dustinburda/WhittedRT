//
// Created by Dustin on 11/27/24.
//

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <cstdint>
#include <thread>
#include <vector>

struct ThreadPool {
    ThreadPool()
        : num_threads_{std::thread::hardware_concurrency() - 4} { pool_.reserve(num_threads_); }
    ~ThreadPool() {
        for(auto&& thread : pool_)
            if(thread.joinable())
                thread.join();
    }
    void Add(std::thread&& t) {
        pool_.push_back(std::move(t));
    }

    size_t num_threads_;
    std::vector<std::thread> pool_;
};

#endif //THREADPOOL_H
