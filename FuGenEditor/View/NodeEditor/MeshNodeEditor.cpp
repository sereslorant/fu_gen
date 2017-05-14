
#include "MeshNodeEditor.h"

#include "ui_MeshNodeEditor.h"

MeshNodeEditor::MeshNodeEditor(MeshNodePresenter *mesh_node)
	:MeshNode(mesh_node)
{
	Ui::MeshNodeEditor Ui;
	Ui.setupUi(this);
	//
	SegmentWidth = Ui.SegmentWidth;
	SegmentHeight = Ui.SegmentHeight;
	//
	QString Tmp;
	Tmp.setNum(mesh_node->GetSegmentWidth());
	SegmentWidth->setText(Tmp);
	Tmp.setNum(mesh_node->GetSegmentHeight());
	SegmentHeight->setText(Tmp);
}

MeshNodeEditor::~MeshNodeEditor()
{
	//
}
