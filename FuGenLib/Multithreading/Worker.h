#ifndef WORKER_H
#define WORKER_H

#include "JobQueue.h"

class Worker
{
private:
	JobQueue &jobQueue;
	bool ForceRunning = true;
	//
public:
	//
	void AllowToStop()
	{
		ForceRunning = false;
	}
	//
	void Run()
	{
		while(ForceRunning || (jobQueue.GetQueuedJobCount() != 0))
		{
			Job *nextJob = jobQueue.GetNextJob();
			if(nextJob != nullptr)
			{
				nextJob->Execute();
			}
		}
	}
	//
	static void RunWorker(Worker *worker)
	{
		worker->Run();
	}
	//
	Worker(JobQueue &job_queue)
		:jobQueue(job_queue)
	{}
	//
	~Worker(){}
	/*
	 * End of class
	 */
};


#endif // WORKER_H
