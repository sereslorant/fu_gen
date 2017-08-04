#ifndef STOCHASTIC_TREE_3D_H
#define STOCHASTIC_TREE_3D_H

#include "TreeDemo.h"

class StochasticTree3D : public TreeDemo
{
public:
	
	/*
	 * TODO: Át kell majd írnu GLuintre a texture_id-t!
	 */
	StochasticTree3D(unsigned int random_seed,unsigned int Res_X,unsigned int Res_Y,unsigned int texture_id);
	virtual ~StochasticTree3D() override;
};

#endif // STOCHASTIC_TREE_3D_H
