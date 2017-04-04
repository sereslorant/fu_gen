
#include <iostream>

#include "../../Const.h"

#include "Turtle3D.h"
#include "TurtleStateStack.hpp"

bool IsTurtle3DCommand(char command)
{
	if( (command == 'F') ||
		(command == 'f') ||
		(command == '(') || // Pitch up
		(command == ')') || // Pitch down
		(command == '<') || // Turn left
		(command == '>') || // Turn right
		(command == '+') || // Roll left
		(command == '-') || // Roll right
		(command == '|') || // Turn back
		(command == '[') ||
		(command == ']') ||
		(command == '{') ||
		(command == '}') ||
		(command == '.')
		)
	{
		return true;
	}

	std::cout << "ERROR!: " << command << std::endl;

	return false;
}

void Turtle3D::ExecuteCommands(const std::string &commands,TreeNode *&tree_skeleton)
{
	TurtleStateStack<Turtle3DState> StateStack(InitialState);
	
	tree_skeleton = new TrunkNode(StateStack.CurrentState.Position/*,Width*/);
	StateStack.CurrentState.Node = tree_skeleton;

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

			StateStack.CurrentState.Node = NewNode;
			//
			break;
		case 'f':
			StateStack.CurrentState.Move(dDist);
			//
			break;
		case '(':
			StateStack.CurrentState.Rotate(Turtle3DState::ROT_X, dAngle);
			//
			break;
		case ')':
			StateStack.CurrentState.Rotate(Turtle3DState::ROT_X,-dAngle);
			//
			break;
		case '<':
			StateStack.CurrentState.Rotate(Turtle3DState::ROT_Y, dAngle);
			//
			break;
		case '>':
			StateStack.CurrentState.Rotate(Turtle3DState::ROT_Y,-dAngle);
			//
			break;
		case '+':
			StateStack.CurrentState.Rotate(Turtle3DState::ROT_Z, dAngle);
			//
			break;
		case '-':
			StateStack.CurrentState.Rotate(Turtle3DState::ROT_Z,-dAngle);
			//
			break;
		case '|':
			StateStack.CurrentState.Rotate(Turtle3DState::ROT_Y,PI);
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

Turtle3D::Turtle3D(const dvec4 &direction_h,const dvec4 &direction_l,double d_dist,double d_angle)
	:TurtleBase(d_dist,d_angle,Turtle3DState(direction_h,direction_l))
{
	//
}
