
#pragma once
#include "RateLimiter.h"
#include <unordered_map>
#include <mutex>
#include <chrono>

class TokenBucketRateLimiter : public RateLimiter {
private:
    struct Bucket {
        double tokens;
        std::chrono::steady_clock::time_point lastRefill;
        std::mutex lock;
        Bucket(int cap)
            : tokens(cap), lastRefill(std::chrono::steady_clock::now()) {}
    };

    std::unordered_map<std::string, Bucket*> buckets;
    std::mutex globalLock;

public:
    TokenBucketRateLimiter(int maxReq, long windowMs)
        : RateLimiter(maxReq, windowMs) {}

    bool allowRequest(const std::string& key) override {
        Bucket* bucket;
        {
            std::lock_guard<std::mutex> g(globalLock);
            if (!buckets.count(key))
                buckets[key] = new Bucket(maxRequests);
            bucket = buckets[key];
        }

        std::lock_guard<std::mutex> b(bucket->lock);
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - bucket->lastRefill).count();

        double refill = (elapsed / 1000.0) * maxRequests;
        bucket->tokens = std::min((double)maxRequests, bucket->tokens + refill);
        bucket->lastRefill = now;

        if (bucket->tokens >= 1) {
            bucket->tokens--;
            return true;
        }
        return false;
    }
};
