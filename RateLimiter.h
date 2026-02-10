
#pragma once
#include <string>

class RateLimiter {
protected:
    int maxRequests;
    long windowMillis;

public:
    RateLimiter(int maxReq, long windowMs)
        : maxRequests(maxReq), windowMillis(windowMs) {}
    virtual bool allowRequest(const std::string& key) = 0;
    virtual ~RateLimiter() = default;
};
