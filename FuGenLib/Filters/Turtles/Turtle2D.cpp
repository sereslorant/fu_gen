
#include "Turtle2D.h"
#include "TurtleStateStack.hpp"

bool IsTurtle2DCommand(char command)
{
	if( (command == 'F') ||
		(command == 'f') ||
		(command == '+') ||
		(command == '-') ||
		(command == '[') ||
		(command == ']') ||
		(command == '{') ||
		(command == '}') ||
		(command == '.')
		)
	{
		return true;
	}
	//
	return false;
}

void Turtle2D::ExecuteCommands(const std::string &commands,TreeNode *&tree_skeleton)
{
	TurtleStateStack<Turtle2DState> StateStack(InitialState);
	//
	tree_skeleton = new TrunkNode(StateStack.CurrentState.Position/*,Width*/);
	StateStack.CurrentState.Node = tree_skeleton;
	//
	TreeNode *NewNode;
	for(unsigned int i=0;i < commands.size();i++)
	{
		switch(commands[i])
		{
		case 'F':
			StateStack.CurrentState.Move(dDist);
			//
			NewNode = new TrunkNode(StateStack.CurrentState.Position/*,Width*/);
			StateStack.CurrentState.Node->AddChild(NewNode);
			//
			StateStack.CurrentState.Node = NewNode;
			//
			break;
		case 'f':
			StateStack.CurrentState.Move(dDist);
			//
			break;
		case '+':
			StateStack.CurrentState.Rotate( dAngle);
			//
			break;
		case '-':
			StateStack.CurrentState.Rotate(-dAngle);
			//
			break;
		case '[':
			StateStack.Push();
			//
			break;
		case ']':
			StateStack.Pop();
			//
			break;
		case '{':
			StateStack.PolygonStack.emplace_back(StateStack.CurrentState.Node);
			//
			break;
		case '}':
			StateStack.PolygonStack.back().Construct(NewNode);
			StateStack.PolygonStack.pop_back();
			//
			break;
		case '.':
			StateStack.PolygonStack.back().AddVertex(StateStack.CurrentState.Position);
			//
			break;
		}
	}
}
