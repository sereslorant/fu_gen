#ifndef FU_GEN_PIPELINE_EDITOR_H
#define FU_GEN_PIPELINE_EDITOR_H

class PipelineEditorLogic;

#include <QtWidgets/QGraphicsView>
#include <QKeyEvent>

#include "FuGenPipelineNode.h"
#include "FuGenPipelineEdge.h"

#include <list>

class FuGenPipelineEditor : public QGraphicsView
{
    Q_OBJECT
private:
	//
	class PipelineEditorLogic
	{
	private:
		//
		class ListenerBase
		{
		protected:
			PipelineEditorLogic &EditorLogic;
			bool Deleted = false;
			//
		public:
			//
			ListenerBase(PipelineEditorLogic &editor_logic)
				:EditorLogic(editor_logic)
			{}
			//
			virtual ~ListenerBase()
			{}
			/*
			* End of class
			*/
		};
		//
		class PipelineNodeListener : public ListenerBase, IPipelineNodeListener
		{
		private:
			FuGenPipelineNode *PipelineNode;
			//
		public:
			//
			virtual void OnClicked() override
			{
				EditorLogic.OnNodeClicked(PipelineNode);
			}
			//
			virtual void OnPositionChanged(int x,int y) override
			{
				//
			}
			//
			virtual void OnDeleted() override
			{
				EditorLogic.OnNodeDeleted(this);
				Deleted = true;
			}
			//
			PipelineNodeListener(PipelineEditorLogic &editor_logic,FuGenPipelineNode *pipeline_node)
				:ListenerBase(editor_logic),PipelineNode(pipeline_node)
			{
				PipelineNode->AddListener(this);
			}
			//
			virtual ~PipelineNodeListener() override
			{
				if(!Deleted)
					{PipelineNode->RemoveListener(this);}
			}
			/*
			* End of class
			*/
		};
		//
		class PipelineEdgeListener : public ListenerBase, IPipelineEdgeListener
		{
		private:
			FuGenPipelineEdge *PipelineEdge;
			//
		public:
			virtual void OnClicked() override
			{
				//
			}
			//
			virtual void OnEndpointDeleted() override
			{
				EditorLogic.DeleteEdge(PipelineEdge);
			}
			//
			virtual void OnDeleted() override
			{
				EditorLogic.OnEdgeDeleted(this);
				Deleted = true;
			}
			//
			PipelineEdgeListener(PipelineEditorLogic &editor_logic,FuGenPipelineEdge *pipeline_edge)
				:ListenerBase(editor_logic),PipelineEdge(pipeline_edge)
			{
				PipelineEdge->AddListener(this);
			}
			//
			virtual ~PipelineEdgeListener() override
			{
				if(!Deleted)
				{
					PipelineEdge->RemoveListener(this);
				}
			}
			/*
			* End of class
			*/
		};
		//
		enum PipelineEditorState
		{
			NORMAL_MODE,
			EDIT_MODE,
			CONNECTING_MODE,
		};
		//
		FuGenPipelineEditor *PipelineEditor;
		//
		PipelineEditorState EditorState = NORMAL_MODE;
		//
		FuGenPipelineNode *SelectedNode = nullptr;
		//
		std::list<PipelineNodeListener *> NodeListeners;
		std::list<PipelineEdgeListener *> EdgeListeners;
		//
		std::list<ListenerBase *> DeletableListeners;
		//
		void ConnectBegin(FuGenPipelineNode *pipeline_node)
		{
			SelectedNode = pipeline_node;
			EditorState = CONNECTING_MODE;
			std::cout << "Connecting mode" << std::endl;
		}
		//
		void ConnectEnd(FuGenPipelineNode *pipeline_node)
		{
			if(EditorState == CONNECTING_MODE && SelectedNode != nullptr && SelectedNode != pipeline_node)
			{
				EditorState = EDIT_MODE;
				PipelineEditor->AddEdge(SelectedNode,pipeline_node);
				SelectedNode = pipeline_node;
				std::cout << "Connected!" << std::endl;
			}
		}
		//
		void DeleteEdge(FuGenPipelineEdge *pipeline_edge)
		{
			PipelineEditor->DeleteItem(pipeline_edge);
		}
		//
		void DeleteListener(ListenerBase *listener)
		{
			DeletableListeners.push_back(listener);
		}
		//
	public:
		//
		void EnableEditMode()
		{
			EditorState = EDIT_MODE;
			std::cout << "Edit mode" << std::endl;
		}
		//
		void DisableEditMode()
		{
			EditorState = NORMAL_MODE;
			std::cout << "Normal mode" << std::endl;
		}
		//
		void FreeDeletableListeners()
		{
			for(ListenerBase *Listener : DeletableListeners)
			{
				delete Listener;
			}
			DeletableListeners.clear();
		}
		//
		void OnNodeClicked(FuGenPipelineNode *pipeline_node)
		{
			switch(EditorState)
			{
			case NORMAL_MODE:
				
				break;
			case EDIT_MODE:
				ConnectBegin(pipeline_node);
				break;
			case CONNECTING_MODE:
				ConnectEnd(pipeline_node);
				break;
			}
		}
		//
		void OnNodeAdded(FuGenPipelineNode *new_node)
		{
			NodeListeners.push_back(new PipelineNodeListener(*this,new_node));
			std::cout << "Node added" << std::endl;
		}
		//
		void OnNodeDeleted(PipelineNodeListener *deleted_listener)
		{
			NodeListeners.remove(deleted_listener);
			DeleteListener(deleted_listener);
			std::cout << "Deleted node" << std::endl;
		}
		//
		void OnEdgeAdded(FuGenPipelineEdge *new_edge)
		{
			EdgeListeners.emplace_back(new PipelineEdgeListener(*this,new_edge));
			std::cout << "Edge added" << std::endl;
		}
		//
		void OnEdgeDeleted(PipelineEdgeListener *deleted_listener)
		{
			EdgeListeners.remove(deleted_listener);
			DeleteListener(deleted_listener);
			std::cout << "Deleted edge" << std::endl;
		}
		//
		PipelineEditorLogic(FuGenPipelineEditor *pipeline_editor)
			:PipelineEditor(pipeline_editor)
		{}
		//
		~PipelineEditorLogic()
		{}
		/*
		* End of class
		*/
	};
	//
	PipelineEditorLogic *EditorLogic;
	QGraphicsScene *PipelineScene;
	//
protected:
	//
	virtual void keyPressEvent(QKeyEvent *Event) override;
	//
	virtual void keyReleaseEvent(QKeyEvent *Event) override;
	//
	std::list<QGraphicsItem *> DeletableItems;
	//
public:
	//
	void AddNode(int x,int y);
	//
	void AddEdge(FuGenPipelineNode *begin_node,FuGenPipelineNode *end_node);
	//
	void DeleteItem(QGraphicsItem *deletable_item)
	{
		PipelineScene->removeItem(deletable_item);
		DeletableItems.push_back(deletable_item);
	}
	//
	virtual bool event(QEvent *event) override;
	//
	FuGenPipelineEditor(QWidget *parent = nullptr);
	//
	virtual ~FuGenPipelineEditor() override;
	/*
	 * End of class
	 */
};

#endif // FU_GEN_PIPELINE_EDITOR_H
