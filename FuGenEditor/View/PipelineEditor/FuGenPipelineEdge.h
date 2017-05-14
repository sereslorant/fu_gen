#ifndef FU_GEN_PIPELINE_EDGE_H
#define FU_GEN_PIPELINE_EDGE_H

class IPipelineEdgeListener
{
public:
	virtual void OnClicked() = 0;
	virtual void OnEndpointDeleted() = 0;
	virtual void OnDeleted() = 0;
	//
	IPipelineEdgeListener()
	{}
	virtual ~IPipelineEdgeListener()
	{}
};

class FuGenPipelineEdge;

class IPipelineEdgeModel
{
public:
	//
	virtual void SetPipelineEdge(FuGenPipelineEdge *pipeline_edge) = 0;
	//
	IPipelineEdgeModel()
	{}
	//
	virtual ~IPipelineEdgeModel()
	{}
};

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

#include "FuGenPipelineNode.h"

#include <list>

#include <iostream>

class FuGenPipelineEdge : public QGraphicsLineItem
{
private:
	//
	std::list<IPipelineEdgeListener *> Listeners;
	//
	class EndpointListener : public IPipelineNodeListener
	{
	private:
		bool IsBegin;
		FuGenPipelineEdge *Edge;
		//
		bool NodeDeleted = false;
		//
	public:
		//
		bool IsDeleted()
		{
			return NodeDeleted;
		}
		//
		virtual void OnClicked() override
		{}
		//
		virtual void OnPositionChanged(int x,int y) override
		{
			if(IsBegin)
				{Edge->RefreshBeginPosition(x,y);}
			else
				{Edge->RefreshEndPosition(x,y);}
		}
		//
		virtual void OnDeleted() override
		{
			NodeDeleted = true;
			Edge->NotifyEndpointDeleted();
		}
		//
		EndpointListener(FuGenPipelineEdge *edge,bool is_begin,FuGenPipelineNode *end_point)
			:Edge(edge),IsBegin(is_begin)
		{
			end_point->AddListener(this);
			//std::cout << "Created " << this << std::endl;
		}
		//
		virtual ~EndpointListener() override
		{
			//std::cout << "Deleted " << this << std::endl;
		}
	};
	//
	FuGenPipelineNode *BeginNode;
	FuGenPipelineNode *EndNode;
	//
	EndpointListener BeginListener;
	EndpointListener EndListener;
	//
	IPipelineEdgeModel *EdgeModel;
	//
	void NotifyEndpointDeleted()
	{
		for(IPipelineEdgeListener *Listener : Listeners)
		{
			Listener->OnEndpointDeleted();
		}
	}
	//
	void RefreshBeginPosition(int x,int y)
	{
		if(!EndListener.IsDeleted())
		{
			setLine(QLineF(QPointF(x,y),EndNode->GetCenter()));
		}
	}
	//
	void RefreshEndPosition(int x,int y)
	{
		if(!BeginListener.IsDeleted())
		{
			setLine(QLineF(BeginNode->GetCenter(),QPointF(x,y)));
		}
	}
	//
protected:
	//
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *Event) override;
	//
	virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
	//
public:
	//
	void SetModel(IPipelineEdgeModel *new_model)
	{
		EdgeModel = new_model;
		EdgeModel->SetPipelineEdge(this);
	}
	//
	IPipelineEdgeModel *GetModel()
	{
		return EdgeModel;
	}
	//
	void AddListener(IPipelineEdgeListener *new_listener)
	{
		Listeners.push_back(new_listener);
	}
	//
	void RemoveListener(IPipelineEdgeListener *removable_listener)
	{
		Listeners.remove(removable_listener);
	}
	//
	FuGenPipelineEdge(FuGenPipelineNode *begin_node,FuGenPipelineNode *end_node);
	//
	virtual ~FuGenPipelineEdge() override;
	/*
	 * End of class
	 */
};

#endif // FU_GEN_PIPELINE_EDGE_H
