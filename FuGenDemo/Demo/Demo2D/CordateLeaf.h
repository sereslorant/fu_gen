#ifndef CORDATE_LEAF_H
#define CORDATE_LEAF_H

#include "Demo2D.h"

#include <DemoUtils/DrawSkeleton.h>

class CordateLeaf : public Demo2D
{
private:
	TreeNode *CurveSkeleton;
	
public:

	virtual void Draw() override
	{
		glColor3f(0.0,0.0,0.0);
		DrawSkeleton DrawSkel;
		DrawSkel.Draw(CurveSkeleton);
	}

	CordateLeaf();
	virtual ~CordateLeaf() override;
};

#endif // CORDATE_LEAF_H
