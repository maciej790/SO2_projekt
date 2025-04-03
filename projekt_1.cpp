#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

// Implementation of SpinLock
class SpinLock
{
private:
    mutex mtx; // Mutex to ensure mutual exclusion

public:
    void acquire()
    {
        mtx.lock(); // Lock the mutex to acquire the resource
    }

    void release()
    {
        mtx.unlock(); // Unlock the mutex to release the resource
    }
};

int philosopher_count; // Number of philosophers
SpinLock *chopsticks;  // Array of SpinLocks representing chopsticks
int max_iterations;    // Number of iterations each philosopher will execute

void philosopher_task(int id)
{
    for (int i = 0; i < max_iterations; ++i)
    {
        // Thinking phase
        cout << "Philosopher " << id << " is thinking.\n";
        this_thread::sleep_for(chrono::seconds(1));

        // Trying to eat
        cout << "Philosopher " << id << " wants to eat.\n";

        //  philosophers pick up the left fork first, then the right
        if (id % 2 == 0)
        {
            chopsticks[id].acquire(); // Lock left fork
            cout << "Philosopher " << id << " picked up the left fork.\n";
            chopsticks[(id + 1) % philosopher_count].acquire(); // Lock right fork
            cout << "Philosopher " << id << " picked up the right fork.\n";
        }
        else
        {                                                       // Odd philosophers pick up the right fork first, then the left
            chopsticks[(id + 1) % philosopher_count].acquire(); // Lock right fork
            cout << "Philosopher " << id << " picked up the right fork.\n";
            chopsticks[id].acquire(); // Lock left fork
            cout << "Philosopher " << id << " picked up the left fork.\n";
        }

        // Eating phase
        cout << "Philosopher " << id << " is eating.\n";
        this_thread::sleep_for(chrono::seconds(1));

        // Releasing the chopsticks after eating
        chopsticks[(id + 1) % philosopher_count].release(); // Release right fork
        cout << "Philosopher " << id << " put down the right fork.\n";
        chopsticks[id].release(); // Release left fork
        cout << "Philosopher " << id << " put down the left fork.\n";
    }
    cout << "Philosopher " << id << " has finished.\n";
}

int main()
{
    do
    {
        cout << "Enter the number of philosophers (minimum 2): ";
        cin >> philosopher_count;
        cout << "Enter the number of iterations (minimum 1): ";
        cin >> max_iterations;
    } while (philosopher_count < 2 || max_iterations < 1);

    // Allocate memory for chopsticks (one for each philosopher)
    chopsticks = new SpinLock[philosopher_count];
    thread *philosophers = new thread[philosopher_count];

    // Create philosopher threads
    for (int i = 0; i < philosopher_count; ++i)
    {
        philosophers[i] = thread(philosopher_task, i);
    }

    // Join philosopher threads
    for (int i = 0; i < philosopher_count; ++i)
    {
        philosophers[i].join();
    }

    // Free allocated memory
    delete[] chopsticks;
    delete[] philosophers;
    return 0;
}
