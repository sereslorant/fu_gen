
#include "Job.h"

bool Job::IsReady()
{
	bool Ready = true;
	for(Job *Dependency : Dependencies)
	{
		if(!Dependency->IsFinished())
		{
			Ready = false;
			break;
		}
	}
	return Ready;
}

Job::Job(unsigned int num_dependencies,Job *dependencies[])
	:Dependencies(num_dependencies)
{
	for(int i=0;i < num_dependencies;i++)
	{
		Dependencies[i] = dependencies[i];
	}
}