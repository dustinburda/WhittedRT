//
// Created by Dustin on 11/29/24.
//

#include "../include/ThreadPool.h"


ThreadPool::~ThreadPool() {
    for(auto&& thread : pool_)
        if(thread.joinable())
            thread.join();
}
void ThreadPool::Add(std::thread&& t) {
    pool_.push_back(std::move(t));
}