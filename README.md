
# Distributed Rate Limiter (C++)

A high-performance, in-memory **rate limiting system** implemented in **C++**, inspired by large-scale backend traffic control systems such as **Amazon API Gateway**.
The project focuses on **core data structures, concurrency, and constant-time request handling**, making it ideal for system-level and SDE interviews.

---

## 🚀 Project Overview

Modern backend systems must protect themselves from traffic spikes, abuse, and uneven load distribution.
This project implements a **rate limiter** that controls how frequently a client (user/service) can make requests within a given time window.

The system is designed to:

* Be **fast (O(1))**
* Be **thread-safe**
* Be **extensible**
* Demonstrate **strong DSA + systems fundamentals**

---

## ✨ Features

* Supports **multiple rate limiting algorithms**
* Thread-safe implementation using mutexes
* Efficient in-memory data structures
* Clean, modular C++ design
* Easy to extend to distributed systems

---

## 🧠 Algorithms Implemented

### 1️⃣ Token Bucket Algorithm

* Allows short bursts of traffic
* Smoothly refills tokens over time
* Commonly used in real-world APIs

**Use case:** APIs where burst tolerance is required.

---

### 2️⃣ Sliding Window Log Algorithm

* Tracks request timestamps within a rolling window
* More accurate than fixed window counters

**Use case:** Precise rate enforcement per user.

---

## 🧩 Core Data Structures Used

| Data Structure  | Purpose                                |
| --------------- | -------------------------------------- |
| `unordered_map` | Map users/services to rate limit state |
| `deque`         | Maintain sliding window timestamps     |
| `mutex`         | Ensure thread safety                   |
| Time utilities  | Handle request windows                 |

All operations are designed to run in **O(1) amortized time**.

---

## 🏗️ High-Level Architecture

```
Client Request
      ↓
RateLimiter (Interface)
      ↓
Algorithm Strategy
(Token Bucket / Sliding Window)
      ↓
In-Memory State Store
      ↓
Allow / Block Decision
```

This separation allows algorithms to be swapped without changing client logic.

---

## ⚙️ Build & Run Instructions

### Prerequisites

* C++17 or later
* GCC / Clang

### Compile

```bash
g++ -std=c++17 main.cpp -o limiter
```

### Run

```bash
./limiter
```

---

## 🧪 Example Output

```
Request 0 allowed
Request 1 allowed
Request 2 allowed
Request 3 blocked
Request 4 blocked
```

---

## 🔐 Thread Safety

* Global map access is protected using mutexes
* Each user bucket is independently synchronized
* Prevents race conditions under concurrent requests

This design mirrors **real backend concurrency patterns**.

---

## 📈 Time & Space Complexity

| Operation       | Complexity                        |
| --------------- | --------------------------------- |
| Allow Request   | O(1) amortized                    |
| Memory per user | O(N) where N = requests in window |

---

## 🌍 Scalability & Future Improvements

This project is intentionally **in-memory** to focus on correctness and performance.

Possible extensions:

* Redis or DynamoDB for distributed state
* Background cleanup for inactive users
* Per-API or per-service rate limits
* Adaptive rate limits based on load
* REST/gRPC interface

These tradeoffs are discussed during interviews.

---

## 🧠 Design Tradeoffs

* **Token Bucket vs Sliding Window**
  Token Bucket allows bursts, Sliding Window provides precision.

* **Accuracy vs Memory**
  Sliding Window uses more memory but offers finer control.

* **In-Memory vs Distributed**
  In-memory is fast; distributed adds fault tolerance.

---

## 👩‍💻 Author

**Rishita Sharma**
GitHub: [https://github.com/rishitaxa](https://github.com/rishitaxa)



* 🔥 **Resume bullets** written from this README
* 🧠 **Amazon interview Q&A based on this project**
* 📌 A **design-doc version** (1-pager, Amazon style)

Just say the word 👊
