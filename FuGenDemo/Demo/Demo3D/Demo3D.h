#ifndef DEMO3D_H
#define DEMO3D_H

#include <Demo/IDemo.h>

#include <Filters/Turtles/Turtle3D.h>
#include <Filters/Turtles/TurtleInterpreter.h>

class Demo3D : public IDemo
{
protected:
	Turtle3D Turtle;// = Turtle3D(vec4(1.0,0.0,0.0),vec4(0.0,1.0,0.0),2.0,PI/2.0);
	TurtleInterpreter Turtle3DInterpreter;

public:
	
	virtual void SetPreviousDemo() override
	{}
	
	virtual void SetNextDemo() override
	{}

	virtual void ChangeState() override
	{}

	Demo3D()
		:Turtle(vec4(0.0,0.0,0.0),vec4(1.0,0.0,0.0),vec4(0.0,1.0,0.0),0.0,0.0),Turtle3DInterpreter(IsTurtle3DCommand)
	{
		char From3D[14]	= {'F','f','^','&','+','-','\\','/','|','[',']','{','}','.'};
		char To3D[14]	= {'F','f','(',')','<','>','+' ,'-','|','[',']','{','}','.'};

		for(int i=0;i < 14;i++)
		{
			Turtle3DInterpreter.AddInterpretation(From3D[i],To3D[i]);

			//std::cout << From3D[i] << ";" << To3D[i] << std::endl;
		}
	}

	virtual ~Demo3D() override
	{}
};

#endif // DEMO3D_H
