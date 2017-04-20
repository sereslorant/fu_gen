#ifndef TREE_MESH_PRESENTER_H
#define TREE_MESH_PRESENTER_H

#include <Data/MultiMesh.h>

#include <View/EdgeVisualizer/GL/GLRenderer.h>
#include <View/EdgeVisualizer/GL/GLDrawableList.h>
#include <View/EdgeVisualizer/GL/MeshRenderer/GLTriangleList.h>

class TreeMeshPresenter
{
private:
	//
	struct BranchPresenter
	{
		Mesh<vec4>  *wrappedBranch;
		GLTriangleList *branchRepresentation = nullptr;
		//
		void RefreshBranch()
		{
			std::vector<vec4> Vertices(wrappedBranch->Triangles.size() * 3);
			unsigned int CurrentVertex = 0;
			for(const Mesh<vec4>::Triangle &Triangle : wrappedBranch->Triangles)
			{
				for(int i=0;i < 3;i++)
				{
					Vertices[CurrentVertex] = wrappedBranch->Vertices[Triangle.VertexId[i]];
					CurrentVertex++;
				}
			}
			branchRepresentation->Fill(&Vertices[0],Vertices.size(),sizeof(vec4));
		}
		//
		BranchPresenter()
		{}
		//
		~BranchPresenter()
		{
			if(branchRepresentation != nullptr)
			{
				delete branchRepresentation;
			}
		}
	};
	//
	struct JunctionPresenter
	{
		MyMesh  *wrappedJunction;
		GLTriangleList *junctionRepresentation = nullptr;
		//
		void RefreshBranch()
		{
			std::vector<vec4> Vertices(wrappedJunction->n_faces() * 3);
			unsigned int CurrentVertex = 0;
			for(MyMesh::FaceHandle F : wrappedJunction->faces())
			{
				for(MyMesh::FaceVertexIter V = wrappedJunction->fv_iter(F);V.is_valid();V++)
				{
					//auto Data = wrappedJunction->data(*V);
					OpenMesh::Vec3f Vertex = wrappedJunction->point(*V);
					Vertices[CurrentVertex] = vec4(Vertex[0],Vertex[1],Vertex[2]);
					CurrentVertex++;
				}
			}
			junctionRepresentation->Fill(&Vertices[0],Vertices.size(),sizeof(vec4));
		}
		//
		JunctionPresenter()
		{}
		//
		~JunctionPresenter()
		{
			if(junctionRepresentation != nullptr)
			{
				delete junctionRepresentation;
			}
		}
	};
	//
	MultiMesh *wrappedMultiMesh;
	std::list<BranchPresenter> branchPresenters;
	std::list<JunctionPresenter> junctionPresenters;
	//
	GLDrawableList DrawableList;
	//
	IGLShaderProgram *MeshShaderProgram;
	IGLRenderer *MeshRenderer;
	//
public:
	//
	void SetMeshRenderer(IGLRenderer *mesh_renderer,IGLShaderProgram *mesh_shader_program)
	{
		MeshRenderer = mesh_renderer;
		MeshShaderProgram = mesh_shader_program;
	}
	//
	void OnChanged(MultiMesh *new_multi_mesh)
	{
		wrappedMultiMesh = new_multi_mesh;
		//
		if(branchPresenters.size() != wrappedMultiMesh->Segments.size())
		{
			branchPresenters.resize(wrappedMultiMesh->Segments.size());
		}
		//
		if(junctionPresenters.size() != wrappedMultiMesh->JunctionMeshes.size())
		{
			junctionPresenters.resize(wrappedMultiMesh->JunctionMeshes.size());
		}
		//
		auto branchPresenterIterator = branchPresenters.begin();
		for(Mesh<vec4> &Branch : wrappedMultiMesh->Segments)
		{
			BranchPresenter &currentPresenter = *branchPresenterIterator;
			currentPresenter.wrappedBranch = &Branch;
			if(currentPresenter.branchRepresentation == nullptr)
			{
				currentPresenter.branchRepresentation = new GLTriangleList(nullptr,0,*MeshShaderProgram);
				DrawableList.Add(currentPresenter.branchRepresentation);
			}
			currentPresenter.RefreshBranch();
			//
			branchPresenterIterator++;
		}
		//
		auto junctionPresenterIterator = junctionPresenters.begin();
		for(MyMesh &Junction : wrappedMultiMesh->JunctionMeshes)
		{
			JunctionPresenter &currentPresenter = *junctionPresenterIterator;
			currentPresenter.wrappedJunction = &Junction;
			if(currentPresenter.junctionRepresentation == nullptr)
			{
				currentPresenter.junctionRepresentation = new GLTriangleList(nullptr,0,*MeshShaderProgram);
				DrawableList.Add(currentPresenter.junctionRepresentation);
			}
			currentPresenter.RefreshBranch();
			//
			junctionPresenterIterator++;
		}
		//
		MeshRenderer->SetDrawable(&DrawableList);
	}
	//
	TreeMeshPresenter()
	{}
	//
	~TreeMeshPresenter()
	{}
};

#endif // TREE_MESH_PRESENTER_H
