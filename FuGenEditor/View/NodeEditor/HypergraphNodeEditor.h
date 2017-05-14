#ifndef HYPERGRAPHNODEEDITOR_H
#define HYPERGRAPHNODEEDITOR_H

#include <QLineEdit>
#include <QSlider>

#include <QWidget>

#include <Presenter/Elements/Nodes/HypergraphNodePresenter.h>

#include <iostream>

class HypergraphNodeEditor : public QWidget
{
    Q_OBJECT

private:
	QLineEdit	*Radius;
	QLineEdit	*RadiusDecay;
	QSlider		*ParentWeight;
	QLineEdit	*InitSpeed;
	QLineEdit	*EndSpeed;
	//
	HypergraphNodePresenter *HypergraphNode;
	//
private slots:
	//
	void RadiusChanged()
	{
		HypergraphNode->SetRadius(Radius->text().toFloat());
	}
	//
	void RadiusDecayChanged()
	{
		HypergraphNode->SetRadiusDecay(RadiusDecay->text().toFloat());
	}
	//
	void ParentWeightChanged()
	{
		HypergraphNode->SetParentWeight(ParentWeight->value() / 100.0);
	}
	//
	void InitialSpeedChanged()
	{
		HypergraphNode->SetInitSpeed(InitSpeed->text().toFloat());
	}
	//
	void EndSpeedChanged()
	{
		HypergraphNode->SetEndSpeed(EndSpeed->text().toFloat());
	}
	//
public:
	//
	HypergraphNodeEditor(HypergraphNodePresenter *hypergraph_node);
	//
	virtual ~HypergraphNodeEditor() override;
};

#endif // HYPERGRAPHNODEEDITOR_H
