
#include "FuGenPipelineEditor.h"

#include <iostream>

void FuGenPipelineEditor::keyPressEvent(QKeyEvent *Event)
{
	QGraphicsView::keyPressEvent(Event);
	//
	if(Event->key() == Qt::Key_Delete)
	{
		QList<QGraphicsItem *> SelectedItems = PipelineScene->selectedItems();
		for(QGraphicsItem *SelectedItem : SelectedItems)
		{
			DeleteItem(SelectedItem);
		}
	}
	if(Event->key() == Qt::Key_Shift)
	{
		EditorLogic->EnableEditMode();
	}
}

void FuGenPipelineEditor::keyReleaseEvent(QKeyEvent *Event)
{
	QGraphicsView::keyPressEvent(Event);
	//
	if(Event->key() == Qt::Key_Shift)
	{
		EditorLogic->DisableEditMode();
	}
}

void FuGenPipelineEditor::mouseReleaseEvent(QMouseEvent *Event)
{
	QGraphicsView::mouseReleaseEvent(Event);
	//
	if(Event->button() == Qt::RightButton)
	{
		if(Model != nullptr)
		{
			FuGenPipelineNode *NewNode = AddNode(Event->pos().x(),Event->pos().y());
			NewNode->SetModel(Model->SpawnNode());
		}
	}
}

FuGenPipelineNode *FuGenPipelineEditor::AddNode(int x, int y)
{
	FuGenPipelineNode *NewNode;
	NewNode = new FuGenPipelineNode(x,y);
	EditorLogic->OnNodeAdded(NewNode);
	//
	PipelineScene->addItem(NewNode);
    //
    return NewNode;
}

FuGenPipelineEdge *FuGenPipelineEditor::AddEdge(FuGenPipelineNode *begin_node,FuGenPipelineNode *end_node)
{
	FuGenPipelineEdge *NewEdge;
	NewEdge = new FuGenPipelineEdge(begin_node,end_node);
	EditorLogic->OnEdgeAdded(NewEdge);
	//
	PipelineScene->addItem(NewEdge);
    //
    return NewEdge;
}

bool FuGenPipelineEditor::event(QEvent *event)
{
	for(auto *DeletableItem : DeletableItems)
	{
		delete DeletableItem;
	}
	DeletableItems.clear();
	//
	EditorLogic->FreeDeletableListeners();
	//
	return QGraphicsView::event(event);
}

FuGenPipelineEditor::FuGenPipelineEditor(QWidget *parent)
	:QGraphicsView(parent)
{
	EditorLogic = new PipelineEditorLogic(this);
	//
	PipelineScene = new QGraphicsScene(this);
	setScene(PipelineScene);
}

FuGenPipelineEditor::~FuGenPipelineEditor()
{
	delete EditorLogic;
	std::cout << "Pipeline editor destroyed" << std::endl;
}

#include "FuGenPipelineEditor.moc"
