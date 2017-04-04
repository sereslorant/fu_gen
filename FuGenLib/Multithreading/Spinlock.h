#ifndef SPINLOCK_H
#define SPINLOCK_H

#include <atomic>

class Spinlock
{
private:
    std::atomic_flag locked = ATOMIC_FLAG_INIT;
	//
public:
	//
    void lock()
	{
        while (locked.test_and_set(std::memory_order_acquire)) { ; }
    }
    //
    void unlock()
	{
        locked.clear(std::memory_order_release);
    }
    //
    Spinlock()
	{
		//
	}
	//
	~Spinlock()
	{
		//
	}
	/*
	 * End of class
	 */
};

#endif // SPINLOCK_H
