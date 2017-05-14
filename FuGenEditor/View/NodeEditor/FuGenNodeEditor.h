#ifndef FUGENNODEEDITOR_H
#define FUGENNODEEDITOR_H

#include <Presenter/PipelinePresenter.h>

#include <View/NodeEditor/TurtleNodeEditor.h>
#include <View/NodeEditor/HypergraphNodeEditor.h>
#include <View/NodeEditor/MeshNodeEditor.h>

#include <QStackedWidget>

class FuGenNodeEditor : public QStackedWidget, public IPipelineListener
{
    Q_OBJECT
private:
	//
	class NodeListener : public INodeListener
	{
	private:
		FuGenNodeEditor *NodeEditor;
		QWidget *EditorWidget;
		//
	public:
		//
		virtual void OnClicked() override
		{
			NodeEditor->setCurrentWidget(EditorWidget);
		}
		//
		NodeListener(FuGenNodeEditor *node_editor,QWidget *editor_widget)
			:NodeEditor(node_editor),EditorWidget(editor_widget)
		{}
		//
		virtual ~NodeListener() override
		{}
	};
	//
	std::list<INodeListener *> AllocatedListeners;
	//
public:
	//
	virtual void TurtleNodeAdded(TurtleNodePresenter *new_node) override
	{
		TurtleNodeEditor *NewWidget = new TurtleNodeEditor(new_node);
		insertWidget(0,NewWidget);
		setCurrentWidget(NewWidget);
		//
		NodeListener *NewListener = new NodeListener(this,NewWidget);
		new_node->AddListener(NewListener);
		AllocatedListeners.push_back(NewListener);
	}
	//
	virtual void HypergraphNodeAdded(HypergraphNodePresenter *new_node) override
	{
		HypergraphNodeEditor *NewWidget = new HypergraphNodeEditor(new_node);
		insertWidget(0,NewWidget);
		setCurrentWidget(NewWidget);
		//
		NodeListener *NewListener = new NodeListener(this,NewWidget);
		new_node->AddListener(NewListener);
		AllocatedListeners.push_back(NewListener);
	}
	//
	virtual void MeshNodeAdded(MeshNodePresenter *new_node) override
	{
		MeshNodeEditor *NewWidget = new MeshNodeEditor(new_node);
		insertWidget(0,NewWidget);
		setCurrentWidget(NewWidget);
		//
		NodeListener *NewListener = new NodeListener(this,NewWidget);
		new_node->AddListener(NewListener);
		AllocatedListeners.push_back(NewListener);
	}
	//
	FuGenNodeEditor(QWidget *parent = nullptr);
	//
	virtual ~FuGenNodeEditor() override;
};

#endif // FUGENNODEEDITOR_H
