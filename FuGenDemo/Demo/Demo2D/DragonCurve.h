#ifndef DRAGON_CURVE_H
#define DRAGON_CURVE_H

#include "Demo2D.h"

#include <DemoUtils/DrawSkeleton.h>

class DragonCurve : public Demo2D
{
private:
	TreeNode *DragonCurveSkeleton;

public:

	virtual void Draw() override
	{
		glColor3f(0.0,0.0,0.0);
		DrawSkeleton DrawSkel;
		DrawSkel.Draw(DragonCurveSkeleton);
	}

	DragonCurve();
	virtual ~DragonCurve() override;
};

#endif // DRAGON_CURVE_H
