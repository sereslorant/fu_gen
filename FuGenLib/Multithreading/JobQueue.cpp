
#include "JobQueue.h"

size_t JobQueue::GetQueuedJobCount()
{
	std::lock_guard<Spinlock> LockGuard(queuedLock);
	return queuedJobs.size();
}

Job *JobQueue::GetNextJob()
{
	Job *nextJob = nullptr;
	//
	{
		std::lock_guard<Spinlock> LockGuard(queuedLock);
		if(queuedJobs.size() > 0)
		{
			auto I = queuedJobs.begin();
			while(I != queuedJobs.end() && !(*I)->IsReady())
			{
				I++;
			}
			//
			if(I != queuedJobs.end())
			{
				nextJob = *I;
				queuedJobs.erase(I);
			}
		}
	}
	//
	if(nextJob != nullptr)
	{
		std::lock_guard<Spinlock> LockGuard(startedLock);
		startedJobs.push_back(nextJob);
	}
	return nextJob;
}

JobQueue::~JobQueue()
{
	for(auto I : queuedJobs)
	{
		delete I;
	}
	//
	for(auto I : startedJobs)
	{
		delete I;
	}
}
