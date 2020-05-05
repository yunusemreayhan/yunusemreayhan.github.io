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

