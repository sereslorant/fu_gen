#ifndef TURTLE_STATE_STACK_HPP
#define TURTLE_STATE_STACK_HPP

#include <list>

template<class TurtleState_T>
struct TurtleStateStack
{
	TurtleState_T CurrentState;
	std::list<TurtleState_T> StateStack;
	//
	std::list<PolygonNode::PolygonNodeBuilder> PolygonStack;
	//
	void Push()
	{
		StateStack.push_back(CurrentState);
	}
	//
	void Pop()
	{
		CurrentState = StateStack.back();
		StateStack.pop_back();
	}
	//
	TurtleStateStack(TurtleState_T &InitialState)
		:CurrentState(InitialState)
	{}
};

#endif // TURTLE_STATE_STACK_HPP
