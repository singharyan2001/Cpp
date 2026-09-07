#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <vector>

// A Global Mutex
std::mutex hw_mutex;

// A Global Shared Buffer
std::string shared_buffer = "";

//=========================================================
// The Manual Way of using Mutex (Why need to avoid this)
//=========================================================
void writeHardwareManual(const std::string& data){
    hw_mutex.lock();    // ACQUIRE: Other threads wait here

    // --- CRITICAL SECTION ---
    if(data.empty()){
        // DANGERl If we return here without unlocking, we deadlock the system!
        // hw_mutex.unlock(); // we must rebemember to do this
        return;
    }
    shared_buffer += data + "\n";
    std::cout << "Wrote: " << data << std::endl;
    // ------------------------
    hw_mutex.unlock();  // RELEASE: Next thread wakes up
}

//=========================================================
// std::lock_guard - The Daily Workhorse & RAII Approach
// 
// Note: The lock is tied to the memory scope { }.
// The moment the function ends—whether by a normal return, an early return, 
// or an exception—the C++ runtime destroys the lock_guard object, which automatically releases the mutex.
//=========================================================
// Example to understand use
void writeHardwareSafe(const std::string& data){
    // ACQUIRE: Mutex locked the moment this object is created
    std::lock_guard<std::mutex> lock(hw_mutex);

    // --- Critical Section ---
    if(data.empty()){
        return; // SAFE: lock_guard is destroyed here, mutex is unlocked automatically
    }

    shared_buffer += data + "\n";
    // ------------------------
} // SAFE: lock_guard destroyed here, mutex inlocked automatically

// Test example
void test_writeHardwareSafe(int thread_id) {
    // Mutex acquired here
    std::lock_guard<std::mutex> lock(hw_mutex); 
    
    std::string data = "Thread [" + std::to_string(thread_id) + "] (lock_guard) writing.";
    shared_buffer += data + "\n";
    
    // Simulating hardware write time
    std::cout << ">>> " << data << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
    // Mutex released automatically here
}

//=========================================================
// std::unique_lock - The Flexible Tool & RAII Approach
//
// @brief: 
// sometimes you have a heavy computation that doesn't need the lock, followed by a quick write that does.
// You want to hold the lock for the absolute shortest time possible.
// std::unique_lock allows you to unlock before the scope ends, or delay locking until you need it.
//=========================================================
// Example to understand use
void processAndWriteFlexible(const std::string& raw_data){
    // 1. Heavy Processing (No lock needed, let other threads run!)
    std::string processed = "PROCESSED_" + raw_data;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // 2. Lock just we need to touch the shared resource
    std::unique_lock<std::mutex> lock(hw_mutex);
    shared_buffer += processed + "\n";
    std::cout << "Flexible Write: " << processed << std::endl;

    // 3. We are done with the hardware, but still have local math to do
    // Unlock manually so other threads can use the hardware immediately!
    lock.unlock();

    // 4. Do some more local work...
    int checksum = processed.length() * 42;    
} // If you forget to call lock.unlock(), unique_lock still safely unlocks here

// Test example
// 2. unique_lock Example
void test_processAndWriteFlexible(int thread_id) {
    // Heavy processing OUTSIDE the lock (Threads run this concurrently)
    std::this_thread::sleep_for(std::chrono::milliseconds(50)); 
    std::string processed = "Thread [" + std::to_string(thread_id) + "] (unique_lock) processed & writing.";

    // Lock ONLY for the shared resource update
    std::unique_lock<std::mutex> lock(hw_mutex);
    shared_buffer += processed + "\n";
    std::cout << ">>> " << processed << std::endl;
    
    lock.unlock(); // Release early!
    
    // Do more work OUTSIDE the lock
    std::this_thread::sleep_for(std::chrono::milliseconds(20)); 
}

//=========================================================
// std::scoped_lock - The Deadlock Preventer
//
// @brief:
// Imagine a workflow where you need to lock both the RS485 Bus and a separate I2C Bus simultaneously to orchestrate a sensor reading.
// If Thread A locks RS485 then I2C, but Thread B locks I2C then RS485, they cand eadlock waiting on each other.
// std::scoped_lock (C++17) takes multiple mutexes and locks them all at once using a safe algorithm that makes deadlocks impossible
//=========================================================
std::mutex rs485_mutex;
std::mutex i2c_mutex;

void test_orchestrateDualBusTransfer(int thread_id) {
    // Locks both without risking deadlock
    std::scoped_lock lock(rs485_mutex, i2c_mutex);
    
    std::cout << ">>> Thread [" << thread_id << "] (scoped_lock) secured both buses." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

int main() {
    std::cout << "--- STARTING MUTEX TEST ---\n" << std::endl;

    std::vector<std::thread> threads;

    // Spawn 10 threads competing for resources
    for (int i = 0; i < 4; ++i) {
        threads.push_back(std::thread(test_writeHardwareSafe, i));
        threads.push_back(std::thread(test_processAndWriteFlexible, i + 4));
    }
    
    // Spawn 2 threads competing for dual buses
    threads.push_back(std::thread(test_orchestrateDualBusTransfer, 8));
    threads.push_back(std::thread(test_orchestrateDualBusTransfer, 9));

    // Wait for all threads to finish
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    std::cout << "\n--- FINAL SHARED BUFFER CONTENTS ---\n";
    std::cout << shared_buffer;
    std::cout << "------------------------------------\n";

    return 0;
}

/* MY OUTPUT
--- STARTING MUTEX TEST ---

>>> Thread [1] (lock_guard) writing.
>>> Thread [8] (scoped_lock) secured both buses.
>>> Thread [0] (lock_guard) writing.
>>> Thread [9] (scoped_lock) secured both buses.
>>> Thread [2] (lock_guard) writing.
>>> Thread [3] (lock_guard) writing.
>>> Thread [4] (unique_lock) processed & writing.
>>> Thread [5] (unique_lock) processed & writing.
>>> Thread [6] (unique_lock) processed & writing.
>>> Thread [7] (unique_lock) processed & writing.

--- FINAL SHARED BUFFER CONTENTS ---
Thread [1] (lock_guard) writing.
Thread [0] (lock_guard) writing.
Thread [2] (lock_guard) writing.
Thread [3] (lock_guard) writing.
Thread [4] (unique_lock) processed & writing.
Thread [5] (unique_lock) processed & writing.
Thread [6] (unique_lock) processed & writing.
Thread [7] (unique_lock) processed & writing.
------------------------------------
*/

/* The Key Takeaways from the Output:
 * 1. No Garbled Text: If we didn't use mutexes, std::cout would mash the letters together (e.g., >T>hTrheeraeda...), 
 * and appending to shared_buffer at the same time would cause a memory segmentation fault and crash the program. The clean output proves the lock works.
 * 
 * 2. unique_lock is Slower to Start: Notice how threads 4-7 (the unique_lock ones) usually print last? That's because they sleep for 50ms before locking, simulating heavy math.
 * Because they didn't lock the mutex during that math, threads 0-3 were able to use the hardware immediately.
 * 
 * 3. scoped_lock is Independent: Threads 8 and 9 locked entirely different mutexes (rs485_mutex and i2c_mutex). 
 * They didn't have to wait for the hw_mutex to free up, demonstrating how separate mutexes protect separate resources concurrently.
*/