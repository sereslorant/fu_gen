#ifndef QUADRATIC_KOCH_CURVE_H
#define QUADRATIC_KOCH_CURVE_H

#include "Demo2D.h"

#include <DemoUtils/DrawSkeleton.h>

class QuadraticKochCurve : public Demo2D
{
private:
	TreeNode *QuadraticKochCurveSkeleton;

public:

	virtual void Draw() override
	{
		glColor3f(0.0,0.0,0.0);
		DrawSkeleton DrawSkel;
		DrawSkel.Draw(QuadraticKochCurveSkeleton);
	}

	QuadraticKochCurve();
	virtual ~QuadraticKochCurve() override;
};

#endif // QUADRATIC_KOCH_CURVE_H
