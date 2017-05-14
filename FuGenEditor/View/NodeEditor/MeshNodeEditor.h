#ifndef MESHNODEEDITOR_H
#define MESHNODEEDITOR_H

#include <QLineEdit>

#include <QWidget>

#include <Presenter/Elements/Nodes/MeshNodePresenter.h>

class MeshNodeEditor : public QWidget
{
    Q_OBJECT

private:
	QLineEdit *SegmentWidth;
	QLineEdit *SegmentHeight;
	//
	MeshNodePresenter *MeshNode;
	//
private slots:
	//
	void SegmentWidthChanged()
	{
		unsigned int NewWidth = SegmentWidth->text().toInt();
		if(NewWidth >= 4)
		{
			MeshNode->SetSegmentWidth(NewWidth);
		}
	}
	//
	void SegmentHeightChanged()
	{
		unsigned int NewHeight = SegmentHeight->text().toInt();
		if(NewHeight >= 2)
		{
			MeshNode->SetSegmentHeight(NewHeight);
		}
	}
	//
public:
	//
	MeshNodeEditor(MeshNodePresenter *mesh_node);
	//
	virtual ~MeshNodeEditor() override;
};

#endif // MESHNODEEDITOR_H
