#ifndef DRAW_SKELETON_H
#define DRAW_SKELETON_H

#include <Data/TreeSkeleton.h>

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

/*
 * Március 25
 */
class DrawSkeleton : public ITreeVisitor
{
private:

	class DrawSegment : public ITreeVisitor
	{
	private:
		TrunkNode *Parent;

	public:
		bool Value = false;

		virtual void Visit(TrunkNode *node) override
		{
			const vec4 &p_pos = Parent->GetPosition();
			const vec4 &c_pos = node->GetPosition();

			glVertex3f(p_pos[0],p_pos[1],p_pos[2]);
			glVertex3f(c_pos[0],c_pos[1],c_pos[2]);
		}

		virtual void Visit(PolygonNode *node) override
		{

		}

		DrawSegment(TrunkNode *parent)
			:Parent(parent)
		{}

		virtual ~DrawSegment() override {}
	};

public:

	virtual void Visit(TrunkNode *node) override
	{
		DrawSegment Puszcsy(node);

		for(auto I = node->GetChildrenBegin();I != node->GetChildrenEnd();I++)
		{
			(*I)->Accept(&Puszcsy);
		}
	}

	virtual void Visit(PolygonNode *node) override
	{
		glEnd();
		
		glBegin(GL_TRIANGLE_FAN);
		
		for(int i=0;i < node->Size();i++)
		{
			const vec4 &pos1 = node->GetVertex(i);
			//const glm::vec3 &pos2 = node->GetVertex(i+1);

			glVertex3f(pos1[0],pos1[1],pos1[2]);
			//glVertex3f(pos2.x,pos2.y,pos2.z);
		}
		
		glEnd();
		
		glBegin(GL_LINES);
	}

	void Draw(TreeNode *node)
	{
		//glColor3f(0.0,0.0,0.0);
		glBegin(GL_LINES);

		std::list<TreeNode *> NodeList;
		NodeList.push_back(node);

		for(auto I = NodeList.begin();I != NodeList.end();)
		{
			(*I)->Accept(this);

			for(auto J = (*I)->GetChildrenBegin();J != (*I)->GetChildrenEnd();J++)
			{
				NodeList.push_back(*J);
			}

			I++;
			NodeList.pop_front();
		}

		glEnd();
	}

	DrawSkeleton(){}
	virtual ~DrawSkeleton(){}
};

#endif // DRAW_SKELETON_H
