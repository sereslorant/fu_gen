#ifndef STOCHASTIC_TREE_2D_H
#define STOCHASTIC_TREE_2D_H

#include "Demo2D.h"

#include <DemoUtils/DrawSkeleton.h>

class StochasticTree2D : public Demo2D
{
private:
	TreeNode *RandomPlantSkeleton;

public:

	virtual void Draw() override
	{
		glColor3f(0.0,0.0,0.0);
		DrawSkeleton DrawSkel;
		DrawSkel.Draw(RandomPlantSkeleton);
	}

	StochasticTree2D(unsigned int random_seed);
	virtual ~StochasticTree2D() override;
};

#endif // STOCHASTIC_TREE_2D_H
