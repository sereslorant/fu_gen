#ifndef NODE_PRESENTER_H
#define NODE_PRESENTER_H

#include "../Data/TreeDataPresenter.h"

#include <View/PipelineEditor/FuGenPipelineNode.h>

class INodeListener
{
public:
	virtual void OnClicked() = 0;
	//
	INodeListener()
	{}
	//
	virtual ~INodeListener()
	{}
};

class NodePresenter : public IPipelineNodeModel, public IPipelineNodeListener
{
protected:
	FuGenPipelineNode *PipelineNode = nullptr;
	//
	class TreeDataListener : public ITreeDataListener
	{
	private:
		NodePresenter &Node;
		//
	public:
		//
		virtual void OnChanged() override
		{
			Node.Refresh();
		}
		//
		TreeDataListener(NodePresenter &node)
			:Node(node)
		{}
		//
		virtual ~TreeDataListener() override
		{}
	};
	//
	TreeDataListener DataListener;
	//
	std::list<INodeListener *> Listeners;
	//
	virtual void Refresh() = 0;
	//
public:
	//
	void AddListener(INodeListener *listener)
	{
		Listeners.push_back(listener);
	}
	//
	virtual void *GetUserData() override
	{
		return this;
	}
	//
	virtual void SetPipelineNode(FuGenPipelineNode *pipeline_node) override
	{
		PipelineNode = pipeline_node;
		PipelineNode->AddListener(this);
	}
    //
	virtual void OnClicked() override
	{
		for(INodeListener *Listener : Listeners)
			{Listener->OnClicked();}
	}
	//
	virtual void OnPositionChanged(int x,int y) override
	{}
	//
	virtual void OnDeleted() override
	{}
    //
    virtual TreeDataPresenter &GetDataPresenter() = 0;
	//
    virtual bool ConnectInput(TreeDataPresenter &input_data_presenter) = 0;
	//
	virtual bool Connect(IPipelineNodeModel *other_model) override
	{
		NodePresenter *OtherPresenter = (NodePresenter *)other_model->GetUserData();
		std::cout << "Presenter connect called" << std::endl;
		return ConnectInput(OtherPresenter->GetDataPresenter());
	}
    //
	NodePresenter()
		:DataListener(*this)
	{}
	//
	virtual ~NodePresenter() override
	{
		if(PipelineNode != nullptr)
		{
			//PipelineNode->RemoveModel(this);
			PipelineNode->RemoveListener(this);
		}
	}
};

#endif // NODE_PRESENTER_H
