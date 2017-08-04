#ifndef DETERMINISTIC_TREE_H
#define DETERMINISTIC_TREE_H

#include "TreeDemo.h"

class DeterministicTree : public TreeDemo
{
public:

	DeterministicTree(unsigned int Res_X,unsigned int Res_Y,unsigned int texture_id);
	virtual ~DeterministicTree() override;
};

#endif // DETERMINISTIC_TREE_H
