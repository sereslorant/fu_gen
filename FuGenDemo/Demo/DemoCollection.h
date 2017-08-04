#ifndef DEMO_COLLECTION_H
#define DEMO_COLLECTION_H

#include <vector>
#include <initializer_list>

#include "IDemo.h"

class DemoCollection : public IDemo
{
private:
	unsigned int DemoId = 0;
	std::vector<IDemo *> Demos;
	
public:
	
	virtual void SetPreviousDemo() override
	{
		DemoId = (DemoId - 1) % Demos.size();
	}
	
	virtual void SetNextDemo() override
	{
		DemoId = (DemoId + 1) % Demos.size();
	}
	
	virtual void ChangeState() override
	{
		for(IDemo *Demo : Demos)
		{
			Demo->ChangeState();
		}
	}
	
	virtual void Draw() override
	{
		Demos[DemoId]->Draw();
	}
	
	DemoCollection(std::initializer_list<IDemo *> demos)
		:Demos(demos.size())
	{
		int i=0;
		for(IDemo *Demo : demos)
		{
			Demos[i] = Demo;
			i++;
		}
	}
	
	virtual ~DemoCollection() override
	{
		for(IDemo *Demo : Demos)
		{
			delete Demo;
		}
	}
};

#endif // DEMO_COLLECTION_H
