
#include "TurtleNodeEditor.h"

#include "ui_TurtleNodeEditor.h"


TurtleNodeEditor::TurtleNodeEditor(TurtleNodePresenter *turtle_node)
	:TurtleNode(turtle_node),TableModel(*turtle_node)
{
	Ui::TurtleNodeEditor Ui;
	Ui.setupUi(this);
	//
	DeltaDistance = Ui.DeltaDistance;
	DeltaAngle = Ui.DeltaAngle;
	Axiom = Ui.Axiom;
	RecursionDepth = Ui.RecursionDepth;
	Productions = Ui.Productions;
	//
	Productions->setModel(&TableModel);
	//
	QString Tmp;
	Tmp.setNum(turtle_node->GetDeltaDistance());
	DeltaDistance->setText(Tmp);
	Tmp.setNum(turtle_node->GetDeltaAngle()*180/FU_GEN_PI);
	DeltaAngle->setText(Tmp);
	Tmp = QString::fromStdString(turtle_node->GetAxiom());
	Axiom->setText(Tmp);
	Tmp.setNum(turtle_node->GetRecursionDepth());
	RecursionDepth->setText(Tmp);
	//std::cout << "EditorAxiom: " << turtle_node->GetAxiom() << ";" << Tmp.toStdString() << std::endl;
}

TurtleNodeEditor::~TurtleNodeEditor()
{
	//
}
