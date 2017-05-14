#include "FuGenNodeEditor.h"


FuGenNodeEditor::FuGenNodeEditor(QWidget *parent)
	:QStackedWidget(parent)
{}

FuGenNodeEditor::~FuGenNodeEditor()
{
	for(INodeListener *Listener : AllocatedListeners)
	{
		delete Listener;
	}
}

#include "FuGenNodeEditor.moc"
