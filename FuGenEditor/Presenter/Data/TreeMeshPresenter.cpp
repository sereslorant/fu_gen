
#include "TreeMeshPresenter.h"

void TreeMeshPresenter::BranchPresenter::RefreshBranch()
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

void TreeMeshPresenter::JunctionPresenter::RefreshBranch()
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

void TreeMeshPresenter::Refresh()
{
	if(ShaderProgram != nullptr)
	{
		DrawableList.Clear();
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
				currentPresenter.branchRepresentation = new GLTriangleList(nullptr,0,*ShaderProgram);
			}
			DrawableList.Add(currentPresenter.branchRepresentation);
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
				currentPresenter.junctionRepresentation = new GLTriangleList(nullptr,0,*ShaderProgram);
			}
			DrawableList.Add(currentPresenter.junctionRepresentation);
			currentPresenter.RefreshBranch();
			//
			junctionPresenterIterator++;
		}
	}
}
