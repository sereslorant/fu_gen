#ifndef FuGenEditor_H
#define FuGenEditor_H

#include <QtWidgets/QMainWindow>

#include <View/EdgeVisualizer/FuGenGLView.h>
#include <View/NodeEditor/FuGenNodeEditor.h>
#include <View/PipelineEditor/FuGenPipelineEditor.h>

#include <Presenter/PipelinePresenter.h>

#include <iostream>

class FuGenWindow : public QMainWindow
{
    Q_OBJECT
private:
	FuGenPipelineEditor	*PipelineEditor;
	FuGenNodeEditor		*NodeEditor;
	FuGenGLView			*EdgeVisualizer;
	//
	//PipelineEditorListener *EditorListener;
	//
	PipelinePresenter	*Presenter;
	//QListView	*PipelineElementList;
	//
	class GLViewListener : public IGLViewListener
	{
	private:
		FuGenWindow *Window = nullptr;
	public:
		//
		virtual void OnInitialization() override
		{
			if(Window != nullptr)
			{
				//Window->EditorListener = new PipelineEditorListener(Window->PipelineEditor);
				Window->Presenter = new PipelinePresenter(Window->EdgeVisualizer);
				//
				//Window->Presenter->AddListener(Window->EditorListener);
				Window->Presenter->AddListener(Window->NodeEditor);
				//
				Window->PipelineEditor->SetModel(Window->Presenter);
				//
				Window->PipelineEditor->AddNode(60,200)->SetModel(Window->Presenter->AddAppNode());
			}
		}
		//
		virtual void OnDraw() override
		{
			//
		}
		//
		GLViewListener(FuGenWindow *window)
			:Window(window)
		{}
		//
		virtual ~GLViewListener()
		{}
		/*
		 * End of class
		 */
	};
	//
	GLViewListener ViewListener;
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
	void Slot_ChangeNodeType(QString new_value)
	{
		if(new_value == "Turtle")
		{
			Presenter->SetSpawnTurtle();
		}
		if(new_value == "Hypergraph generator")
		{
			Presenter->SetSpawnHypergraph();
		}
		if(new_value == "Mesh generator")
		{
			Presenter->SetSpawnMesh();
		}
	}
	//
public:
	//
    FuGenWindow();
    virtual ~FuGenWindow();
};

#endif // FuGenEditor_H

