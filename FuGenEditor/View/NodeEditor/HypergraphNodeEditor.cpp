
#include "HypergraphNodeEditor.h"

#include "ui_HypergraphNodeEditor.h"

HypergraphNodeEditor::HypergraphNodeEditor(HypergraphNodePresenter *hypergraph_node)
	:HypergraphNode(hypergraph_node)
{
	Ui::HypergraphNodeEditor Ui;
	Ui.setupUi(this);
	//
	Radius = Ui.Radius;
	RadiusDecay = Ui.RadiusDecay;
	ParentWeight = Ui.ParentWeight;
	InitSpeed = Ui.InitSpeed;
	EndSpeed = Ui.EndSpeed;
	//
	QString Tmp;
	Tmp.setNum(hypergraph_node->GetRadius());
	Radius->setText(Tmp);
	Tmp.setNum(hypergraph_node->GetRadiusDecay());
	RadiusDecay->setText(Tmp);
	ParentWeight->setValue(hypergraph_node->GetParentWeight()*100);
	Tmp.setNum(hypergraph_node->GetInitSpeed());
	InitSpeed->setText(Tmp);
	Tmp.setNum(hypergraph_node->GetEndSpeed());
	EndSpeed->setText(Tmp);
}

HypergraphNodeEditor::~HypergraphNodeEditor()
{}

#include "HypergraphNodeEditor.moc"
