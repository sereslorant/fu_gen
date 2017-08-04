#ifndef HILBERT_CURVE_H
#define HILBERT_CURVE_H

#include "Demo3D.h"

#include "DemoUtils/DrawSkeleton.h"

class HilbertCurve : public Demo3D
{
private:
	TreeNode *HilbertCurveSkeleton;
	
public:
	
	virtual void Draw() override
	{
		/*glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		gluPerspective(90,1.0,1.0,-200.0);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();*/
		
		//glTranslatef(X,Y,Z);
		
		//glRotatef(CameraAngle,0.0,1.0,0.0);
		//glRotatef(-90.0,1.0,0.0,0.0);
		
		glColor3f(0.0,0.0,0.0);
		DrawSkeleton HilbertDraw;
		HilbertDraw.Draw(HilbertCurveSkeleton);
	}
	
	HilbertCurve();
	virtual ~HilbertCurve() override;
};

#endif // HILBERT_CURVE_H
