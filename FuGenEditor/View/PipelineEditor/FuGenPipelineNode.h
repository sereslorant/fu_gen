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

#include <QGraphicsEllipseItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QWidget>

#include <list>

class FuGenPipelineNode : public QGraphicsEllipseItem
{
private:
	QString NodeLabel = "Pipeline node text";
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
