
#include "FuGenPipelineEdge.h"

#include <iostream>

void FuGenPipelineEdge::mouseReleaseEvent(QGraphicsSceneMouseEvent *Event)
{
	QGraphicsLineItem::mouseReleaseEvent(Event);
	//
	if (Event->button() == Qt::LeftButton)
	{
		for(IPipelineEdgeListener *Listener : Listeners)
		{
			Listener->OnClicked();
		}
	}
}

void FuGenPipelineEdge::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
	QGraphicsLineItem::paint(painter,option,widget);
	//
	float DirX = line().dx();
	float DirY = line().dy();
	//
	float PointX = line().x1() + DirX / 2.0f;
	float PointY = line().y1() + DirY / 2.0f;
	//
	float Length = line().length();
	DirX /= Length;
	DirY /= Length;
	float SideDirX = DirY;
	float SideDirY = -DirX;
	//
	float ArrowSize = 10.0;
	//
	QPointF Dir(DirX,DirY);
	QPointF SideDir(SideDirX,SideDirY);
	//
	QPointF ArrowPoint(PointX,PointY);
	QPointF ArrowOnePoint	= ArrowPoint - 10.0f * Dir + 10.0f * SideDir;
	QPointF ArrowOtherPoint	= ArrowPoint - 10.0f * Dir - 10.0f * SideDir;
	//
	QLineF ArrowOnePart(ArrowPoint,ArrowOnePoint);
	QLineF ArrowOtherPart(ArrowPoint,ArrowOtherPoint);
	//
	painter->drawLine(ArrowOnePart);
	painter->drawLine(ArrowOtherPart);
}

FuGenPipelineEdge::FuGenPipelineEdge(FuGenPipelineNode *begin_node,FuGenPipelineNode *end_node)
	:QGraphicsLineItem(QLineF(begin_node->GetCenter(),end_node->GetCenter())),BeginNode(begin_node),EndNode(end_node),BeginListener(this,true,BeginNode),EndListener(this,false,EndNode)
{
	setFlag(QGraphicsItem::ItemIsSelectable);
}

FuGenPipelineEdge::~FuGenPipelineEdge()
{
	if(!BeginListener.IsDeleted())
		{BeginNode->RemoveListener(&BeginListener);}
	if(!EndListener.IsDeleted())
		{EndNode->RemoveListener(&EndListener);}
	//
	for(IPipelineEdgeListener *Listener : Listeners)
	{
		Listener->OnDeleted();
	}
}
