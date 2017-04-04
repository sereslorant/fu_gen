#ifndef JOB_H
#define JOB_H

#include <vector>

class Job
{
private:
	std::vector<Job *> Dependencies;
	//
public:
	//
	bool IsReady();
	//
	virtual bool IsFinished() = 0;
	//
	virtual void Execute() = 0;
	//
	Job(unsigned int num_dependencies,Job *dependencies[]);
	//
	virtual ~Job()
	{}
	/*
	 * End of class
	 */
};

#endif // JOB_H
