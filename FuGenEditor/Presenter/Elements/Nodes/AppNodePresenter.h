#ifndef APP_NODE_PRESENTER_H
#define APP_NODE_PRESENTER_H

#include "../NodePresenter.h"

#include <Presenter/Data/TreeHypergraphPresenter.h>

class AppNodePresenter : public NodePresenter
{
private:
	TreeHypergraphPresenter DummyPresenter;
	//
	const std::string AppNodeName = "Application";
	//
	virtual void Refresh() override
	{}
	//
public:
	//
	virtual TreeDataPresenter &GetDataPresenter() override
	{
		return DummyPresenter;
	}
	//
	virtual const std::string &GetName() override
	{
		return AppNodeName;
	}
	//
	virtual bool IsConnectable(IPipelineNodeModel *other_model) override
	{
		return true;
	}
	//
	virtual bool ConnectInput(TreeDataPresenter &input_data_presenter) override
	{
		return true;
	}
	//
	AppNodePresenter()
	{
		//
	}
	//
	virtual ~AppNodePresenter() override
	{}
};


#endif // APP_NODE_PRESENTER
