#ifndef TURTLE_NODE_PRESENTER_H
#define TURTLE_NODE_PRESENTER_H

#include "../NodePresenter.h"
#include "../../Data/TreeSkeletonPresenter.h"

#include <View/EdgeVisualizer/FuGenGLView.h>

#include <Filters/L_Systems/DOL_System.h>
#include <Filters/Turtles/TurtleInterpreter.h>
#include <Filters/Turtles/Turtle3D.h>

class TurtleNodePresenter : public NodePresenter
{
private:
	TurtleInterpreter Turtle3DInterpreter;
	//
	std::string Axiom;
	unsigned int RecursionDepth = 0;
	DOL_System Tree;
	Turtle3D Turtle;
	//
	TreeNode *Skeleton = nullptr;
	TreeSkeletonPresenter SkeletonPresenter;
	//
	static const std::string TurtleNodeName;
	//
	virtual void Refresh() override;
	//
public:
	//
	void SetDeltaDistance(double delta_distance);
	//
	double GetDeltaDistance();
	//
	void SetDeltaAngle(double delta_angle);
	//
	double GetDeltaAngle();
	//
	void SetAxiom(const std::string &axiom);
	//
	const std::string &GetAxiom();
	//
	void SetRecursionDepth(unsigned int recursion_depth);
	//
	unsigned int GetRecursionDepth();
	//
	void AddProduction(char predecessor,const std::string &successor);
	//
	bool HasProduction(char predecessor);
	//
	void DeleteProduction(char predecessor);
	//
	const std::map<char,DOL_Production> &GetProductions();
	//
	virtual const std::string &GetName() override;
	//
	virtual bool IsConnectable(IPipelineNodeModel *other_model) override;
	//
	virtual TreeDataPresenter &GetDataPresenter() override;
	//
	virtual bool ConnectInput(TreeDataPresenter &input_data_presenter) override;
	//
	TurtleNodePresenter(FuGenGLView *gl_view);
	//
	virtual ~TurtleNodePresenter() override;
};

#endif // TURTLE_NODE_PRESENTER_H
