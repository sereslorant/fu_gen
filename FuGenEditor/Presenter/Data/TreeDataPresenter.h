#ifndef TREE_DATA_PRESENTER_H
#define TREE_DATA_PRESENTER_H

#include <View/EdgeVisualizer/GL/GLDrawableList.h>

class TreeSkeletonPresenter;
class TreeHypergraphPresenter;
class TreeMeshPresenter;

class ITreeDataVisitor
{
public:
	//
	virtual void Visit(TreeSkeletonPresenter &skeleton_presenter) = 0;
	virtual void Visit(TreeHypergraphPresenter &hypergraph_presenter) = 0;
	virtual void Visit(TreeMeshPresenter &mesh_presenter) = 0;
	//
	ITreeDataVisitor()
	{}
	//
	virtual ~ITreeDataVisitor()
	{}
};

class ITreeDataListener
{
public:
	//
	virtual void OnChanged() = 0;
	//
	ITreeDataListener()
	{}
	//
	virtual ~ITreeDataListener()
	{}
};

class TreeDataPresenter
{
private:
	std::list<ITreeDataListener *> Listeners;
	//
protected:
	//
	GLDrawableList DrawableList;
	//
	IGLShaderProgram *ShaderProgram = nullptr;
	//
	bool Changed = false;
	//
	void NotifyChanged()
	{
		for(ITreeDataListener *Listener : Listeners)
		{
			Listener->OnChanged();
		}
	}
	//
	virtual void Refresh() = 0;
	//
public:
	//
	GLDrawableList &GetDrawableList()
	{
		if(Changed)
		{
			Refresh();
			Changed = false;
		}
		//
		return DrawableList;
	}
	//
	void SetShaderProgram(IGLShaderProgram *shader_program)
	{
		ShaderProgram = shader_program;
	}
	//
	void AddListener(ITreeDataListener *new_listener)
	{
		Listeners.push_back(new_listener);
	}
	//
	void RemoveListener(ITreeDataListener *new_listener)
	{
		Listeners.remove(new_listener);
	}
	//
	virtual void Accept(ITreeDataVisitor &visitor) = 0;
	//
	TreeDataPresenter()
	{}
	//
	virtual ~TreeDataPresenter()
	{}
};

#endif // TREE_DATA_PRESENTER_H
