#ifndef FuGenEditor_H
#define FuGenEditor_H

#include <QtWidgets/QMainWindow>

#include <View/EdgeVisualizer/FuGenGLView.h>
#include <View/PipelineEditor/FuGenPipelineEditor.h>
#include <QtWidgets/QListView>

#include <iostream>

class FuGenWindow : public QMainWindow
{
    Q_OBJECT
private:
	FuGenGLView *EdgeVisualizer;
	QListView	*PipelineElementList;
    //
private slots:
	//
    void Slot_New()
    {
		std::cout << "New" << std::endl;
    }
    //
    void Slot_Open()
    {
		std::cout << "Open" << std::endl;
    }
    //
    void Slot_Save()
    {
		std::cout << "Save" << std::endl;
    }
    //
    void Slot_SaveAs()
    {
		std::cout << "SaveAs" << std::endl;
    }
    //
    void Slot_Undo()
	{
		std::cout << "Undo" << std::endl;
	}
    //
    void Slot_Redo()
	{
		std::cout << "Redo" << std::endl;
	}
	//
public:
	//
    FuGenWindow();
    virtual ~FuGenWindow();
};

#endif // FuGenEditor_H

