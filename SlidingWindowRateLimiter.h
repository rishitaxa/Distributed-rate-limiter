
#pragma once
#include "RateLimiter.h"
#include <unordered_map>
#include <deque>
#include <mutex>
#include <chrono>

class SlidingWindowRateLimiter : public RateLimiter {
private:
    std::unordered_map<std::string, std::deque<long>> logs;
    std::mutex lock;

public:
    SlidingWindowRateLimiter(int maxReq, long windowMs)
        : RateLimiter(maxReq, windowMs) {}

    bool allowRequest(const std::string& key) override {
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::steady_clock::now().time_since_epoch()).count();

        std::lock_guard<std::mutex> g(lock);
        auto& q = logs[key];

        while (!q.empty() && now - q.front() > windowMillis)
            q.pop_front();

        if ((int)q.size() < maxRequests) {
            q.push_back(now);
            return true;
        }
        return false;
    }
};
