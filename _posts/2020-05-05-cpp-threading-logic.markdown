---
layout: post
title: Threading vs Parallelism
author: Yunus Emre AYHAN
date:   2020-05-05 14:29:32
categories: Cpp
comments: true
---

Threading vs Parallelism

In summary difference of this two concept, begins with cpu core count. 
Single core cpu will not provide any gains in terms of time. 
More cpu core means, shorter the total task will consume (if writen appropriately), this is what real parallelism is.
It is better to experiment the things up.
---

### Threading Gains Limitation

With below code snippet i have tried to experiment the total gain that threading can provide.
First of all we have the gain parameter that i have selected as "total saved time / single core time consumption".
When we run it, i have seen that gain is increased with thread count, but after a while, when thread count reached to 8, the gain is limited to %75. 
No matter we increment the number of threads, which is in my machine I have 8 cores.
With this simple experiment I have able to see the core count, thread gain limitation, yahooo.

```cpp
#include <iostream> 
#include <chrono> 
#include <ctime> 
#include <thread>
  
using namespace std;

// Function to calculate 
// Fibonacci series 
long fibonacci(unsigned n) 
{ 
    if (n < 2) return n; 
    return fibonacci(n-1) + fibonacci(n-2); 
} 
  
double process() {
    // Using time point and system_clock 
    std::chrono::time_point<std::chrono::system_clock> start, end; 
  
    start = std::chrono::system_clock::now(); 
    fibonacci(39); 
    end = std::chrono::system_clock::now(); 
  
    std::chrono::duration<double> elapsed_seconds = end - start; 
    std::time_t end_time = std::chrono::system_clock::to_time_t(end); 
  
    return elapsed_seconds.count();
}

double test_thread(int count) {

    std::chrono::time_point<std::chrono::system_clock> start, end; 
    start = std::chrono::system_clock::now(); 

    thread * mthreads[count];
    for(int i = 0; i < count; i++) {
        thread * temp = new thread(process);
        mthreads[i] = temp;
    }

    for(int i = 0; i < count; i++) {
        mthreads[i]->join();
    }

    for(int i = 0; i < count; i++) {
        delete mthreads[i];
    }

    end = std::chrono::system_clock::now(); 
    std::chrono::duration<double> elapsed_seconds = end - start; 
    std::time_t end_time = std::chrono::system_clock::to_time_t(end); 
  
    std::cout << count <<" threads " << count << " jobs finished computation at " << std::ctime(&end_time) 
              << "elapsed time: " << elapsed_seconds.count() << "s\n"; 
    return elapsed_seconds.count();
}

int main() 
{ 
    double ref_time = process();
    double prev = 0;
    double prev_2 = 0;
    std::cout << "direct run elapsed time: " << ref_time << "s\n"; 
    for(int i = 0; i < 20; i++) {
        prev_2 = prev;
        prev = test_thread(i);
        std::cout << "diff with prev : " << prev_2 - prev << "s\n"; 
        std::cout << "expected " << ref_time * i << "s\n"; 
        std::cout << "actual " << prev << "s\n"; 
        std::cout << "gain % " << ( ref_time * i - prev) / (ref_time * i) * 100 << "s\n"; 
    }
}

```

### What is the possible scenarios that this may not work?

Gain in above example, a kind of limitation for a pc (what I unterstrehe). 
In case of threads dependencies, with eachother, gains may not reach upper limitation. 
In my problematic case I was using an RNG (due to my MS project), and it was not reaching the given limitation.
In upcomming revision of this file I may try that, RNGs.

