//
// Created by Dustin on 11/27/24.
//

#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <cstdint>
#include <thread>
#include <vector>

struct ThreadPool {
    ThreadPool(int num_threads)
        : num_threads_{num_threads} { pool_.reserve(num_threads_); }
    ~ThreadPool();
    void Add(std::thread&& t);

    int num_threads_;
    std::vector<std::thread> pool_;
};

#endif //THREADPOOL_H
