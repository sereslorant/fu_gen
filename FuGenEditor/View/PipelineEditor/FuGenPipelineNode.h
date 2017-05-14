#ifndef FU_GEN_PIPELINE_NODE_H
#define FU_GEN_PIPELINE_NODE_H

class IPipelineNodeListener
{
public:
	virtual void OnClicked() = 0;
	virtual void OnPositionChanged(int x,int y) = 0;
	virtual void OnDeleted() = 0;
	//
	IPipelineNodeListener()
	{}
	virtual ~IPipelineNodeListener()
	{}
};

class FuGenPipelineNode;

#include <string>

class IPipelineNodeModel
{
public:
	//
	virtual const std::string &GetName() = 0;
	//
	virtual void *GetUserData() = 0;
	//
	virtual void SetPipelineNode(FuGenPipelineNode *pipeline_node) = 0;
	//
	virtual bool IsConnectable(IPipelineNodeModel *other_model) = 0;
	virtual bool Connect(IPipelineNodeModel *other_model) = 0;
	//
	IPipelineNodeModel()
	{}
	virtual ~IPipelineNodeModel()
	{}
};

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

#include <list>

class FuGenPipelineNode : public QGraphicsEllipseItem
{
private:
	//QString NodeLabel = "Pipeline node text";
	IPipelineNodeModel *NodeModel = nullptr;
	//
	std::list<IPipelineNodeListener *> Listeners;
	//
protected:
	//
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *Event) override;
	//
	virtual QVariant itemChange(GraphicsItemChange change, const QVariant & value) override;
	//
	virtual void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget) override;
	//
public:
	//
	void SetModel(IPipelineNodeModel *new_model)
	{
		NodeModel = new_model;
		NodeModel->SetPipelineNode(this);
	}
	//
	IPipelineNodeModel *GetModel()
	{
		return NodeModel;
	}
	//
	QPointF GetCenter();
	//
	void AddListener(IPipelineNodeListener *new_listener)
	{
		Listeners.push_back(new_listener);
	}
	//
	void RemoveListener(IPipelineNodeListener *removable_listener)
	{
		Listeners.remove(removable_listener);
	}
	//
	FuGenPipelineNode(int x,int y);
	//
	virtual ~FuGenPipelineNode() override;
	/*
	 * End of class
	 */
};


#endif // FU_GEN_PIPELINE_NODE_H
