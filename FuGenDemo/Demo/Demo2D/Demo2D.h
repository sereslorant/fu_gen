#ifndef DEMO2D_H
#define DEMO2D_H

#include <Demo/IDemo.h>

#include <Filters/Turtles/Turtle2D.h>
#include <Filters/Turtles/TurtleInterpreter.h>

class Demo2D : public IDemo
{
protected:
	Turtle2D Turtle = Turtle2D(0.0,0.0);
	TurtleInterpreter Turtle2DInterpreter = TurtleInterpreter(IsTurtle2DCommand);

public:
	
	virtual void SetPreviousDemo() override
	{}
	
	virtual void SetNextDemo() override
	{}

	virtual void ChangeState() override
	{}

	Demo2D()
	{
		char From2D[9]	= {'F','f','+','-','[',']','{','}','.'};
		char To2D[9]	= {'F','f','+','-','[',']','{','}','.'};

		for(int i=0;i < 9;i++)
		{
			Turtle2DInterpreter.AddInterpretation(From2D[i],To2D[i]);
		}
	}

	virtual ~Demo2D() override
	{}
};

#endif // DEMO2D_H
