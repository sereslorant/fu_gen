
#include "FuGenPipelineNode.h"



constexpr unsigned int FU_GEN_NODE_WIDTH = 80;
constexpr unsigned int FU_GEN_NODE_HEIGHT = 50;
constexpr unsigned int FU_GEN_NODE_TEXT_HORIZONTAL_DISPLACEMENT = 0;
constexpr unsigned int FU_GEN_NODE_TEXT_VERTICAL_DISPLACEMENT = 5;

static QPointF ToCenter(QPointF point)
{
	return QPointF(point.x() + FU_GEN_NODE_WIDTH/2,point.y() + FU_GEN_NODE_HEIGHT/2);
}

/*
 * Protected
 */

void FuGenPipelineNode::mouseReleaseEvent(QGraphicsSceneMouseEvent *Event)
{
	QGraphicsEllipseItem::mouseReleaseEvent(Event);
	//
	if (Event->button() == Qt::LeftButton)
	{
		for(IPipelineNodeListener *Listener : Listeners)
		{
			Listener->OnClicked();
		}
	}
}

QVariant FuGenPipelineNode::itemChange(GraphicsItemChange change, const QVariant & value)
{
	if (change == ItemPositionChange)
	{
		QPointF newCenter = ToCenter(value.toPointF());
		
		for(IPipelineNodeListener *Listener : Listeners)
		{
			Listener->OnPositionChanged(newCenter.x(),newCenter.y());
		}
	}
	
	return QGraphicsEllipseItem::itemChange(change,value);
}

void FuGenPipelineNode::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
	QGraphicsEllipseItem::paint(painter,option,widget);
	//
	if(NodeModel != nullptr)
	{
		QString NodeLabel = QString(NodeModel->GetName().c_str());
		painter->drawText(rect(),Qt::AlignCenter | Qt::TextWordWrap,NodeLabel);
	}
}

/*
 * Public
 */

QPointF FuGenPipelineNode::GetCenter()
{
	return QPointF(pos().x() + FU_GEN_NODE_WIDTH/2,pos().y() + FU_GEN_NODE_HEIGHT/2);
}

FuGenPipelineNode::FuGenPipelineNode(int x,int y)
	:QGraphicsEllipseItem(0,0,FU_GEN_NODE_WIDTH,FU_GEN_NODE_HEIGHT)
{
	setPos(x,y);
	//
	setPen(QPen(Qt::black));
	setBrush(QBrush(Qt::lightGray));
	//
	setFlag(QGraphicsItem::ItemIsMovable);
	setFlag(QGraphicsItem::ItemIsSelectable);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges);
	//
	setZValue(1.0);
}

FuGenPipelineNode::~FuGenPipelineNode()
{
	for(IPipelineNodeListener *Listener : Listeners)
	{
		Listener->OnDeleted();
	}
}
