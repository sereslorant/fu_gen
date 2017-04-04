#ifndef JOB_QUEUE_H
#define JOB_QUEUE_H

#include "Job.h"
#include "Spinlock.h"

#include <mutex>
#include <list>

class JobQueue
{
private:
	Spinlock queuedLock;
	std::list<Job *> queuedJobs;
	Spinlock startedLock;
	std::list<Job *> startedJobs;
	//
public:
	//
	size_t GetQueuedJobCount();
	//
	Job *GetNextJob();
	//
	template<class JobType_T,class ... Args_T>
	JobType_T *CreateJob(Args_T ... args)
	{
		JobType_T *NewJob = new JobType_T(args ... );
		//
		{
			std::lock_guard<Spinlock> LockGuard(queuedLock);
			queuedJobs.push_back(NewJob);
		}
		//
		return NewJob;
	}
	//
	JobQueue()
	{
		//
	}
	//
	~JobQueue();
	/*
	 * End of class
	 */
};

#endif // JOB_QUEUE_H
