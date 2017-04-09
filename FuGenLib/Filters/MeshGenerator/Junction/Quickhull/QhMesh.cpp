
#include "QhMesh.h"

bool operator == (const QhFace &one_face,const QhFace &other_face)
{
	return &one_face == &other_face;
}

void QhSetBorderLinks(QhHalfEdge *borders[3],QhFace *triangle)
{
	//std::cout << "Setting up links for triangle " << triangle << std::endl;
	//std::cout << borders[0] << ";" << borders[1] << ";" << borders[2] << std::endl;
	QhHalfEdge *Borders[3] = {borders[0],borders[1],borders[2]};
	triangle->OneBorderingEdge = Borders[0];
	//std::cout << "Bordering edge: " << triangle->OneBorderingEdge << std::endl;
	QhHalfEdge *PrevBorder = nullptr;
	for(QhHalfEdge *Border : Borders)
	{
		Border->BorderedFace = triangle;
		if(PrevBorder != nullptr)
		{
			PrevBorder->NextHalfEdge = Border;
		}
		PrevBorder = Border;
	}
	PrevBorder->NextHalfEdge = Borders[0];
}

void QhConnectTriangleHalfedges(std::list<QhFace *> &new_triangles)
{
	for(auto I = new_triangles.begin();I != new_triangles.end();I++)
	{
		QhFace *I_Triangle = *I;
		for(auto J = std::next(I);J != new_triangles.end();J++)
		{
			QhFace *J_Triangle = *J;
			QhHalfEdge *I_Iterator = I_Triangle->OneBorderingEdge;
			for(int i=0;i < 3;i++)
			{
				QhVertex *I_Begin = I_Iterator->BeginVertex;
				QhVertex *I_End = I_Iterator->NextHalfEdge->BeginVertex;
				//
				QhHalfEdge *J_Iterator = J_Triangle->OneBorderingEdge;
				for(int j=0;j < 3;j++)
				{
					QhVertex *J_Begin = J_Iterator->BeginVertex;
					QhVertex *J_End = J_Iterator->NextHalfEdge->BeginVertex;
					//std::cout << "I_Begin = " << I_Begin->VertexId  << std::endl;
					//std::cout << "I_End = " << I_End->VertexId  << std::endl;
					//std::cout << "J_Begin = " << J_Begin->VertexId  << std::endl;
					//std::cout << "J_End = " << J_End->VertexId  << std::endl;
					if(I_Begin->VertexId == J_End->VertexId && I_End->VertexId == J_Begin->VertexId)
					{
						I_Iterator->Pair = J_Iterator;
						J_Iterator->Pair = I_Iterator;
					}
					J_Iterator = J_Iterator->NextHalfEdge;
				}
				I_Iterator = I_Iterator->NextHalfEdge;
			}
		}
	}
}

void QhGetTriangleIds(const QhFace &face,unsigned int ids[3])
{
	QhHalfEdge *It = face.OneBorderingEdge;
	ids[0] = It->BeginVertex->VertexId;
	It = It->NextHalfEdge;
	ids[1] = It->BeginVertex->VertexId;
	It = It->NextHalfEdge;
	ids[2] = It->BeginVertex->VertexId;
}

void QhGetAdjacentHalfEdges(QhFace &triangle,QhHalfEdge *adjacent_edges[3])
{
	QhHalfEdge *Iterator = triangle.OneBorderingEdge;
	for(int i=0;i < 3;i++)
	{
		adjacent_edges[i] = Iterator->Pair;
		Iterator = Iterator->NextHalfEdge;
	}
}

void QhGetBorderingHalfEdges(QhFace &triangle,QhHalfEdge *bordering_edges[3])
{
	QhHalfEdge *Iterator = triangle.OneBorderingEdge;
	for(int i=0;i < 3;i++)
	{
		bordering_edges[i] = Iterator;
		Iterator = Iterator->NextHalfEdge;
	}
}