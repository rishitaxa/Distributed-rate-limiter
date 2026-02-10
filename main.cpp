
#include <iostream>
#include "TokenBucketRateLimiter.h"
#include "SlidingWindowRateLimiter.h"

int main() {
    TokenBucketRateLimiter limiter(3, 1000);

    for (int i = 0; i < 5; i++) {
        std::cout << "Request " << i
                  << (limiter.allowRequest("user1") ? " allowed" : " blocked")
                  << std::endl;
    }
    return 0;
}
