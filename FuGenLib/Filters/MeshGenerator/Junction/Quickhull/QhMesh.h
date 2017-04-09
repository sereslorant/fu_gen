#ifndef QH_MESH_H
#define QH_MESH_H

/*
 * Halfedge: http://www.flipcode.com/archives/The_Half-Edge_Data_Structure.shtml
 */

struct QhHalfEdge;

class QhElement
{
private:
	bool Deleted = false;
public:
	//
	bool IsDeleted() const
	{
		return Deleted;
	}
	//
	void Delete()
	{
		Deleted = true;
	}
};

struct QhVertex : public QhElement
{
	unsigned int VertexId;
	//
	QhHalfEdge *OneEmanatingEdge = nullptr;
	//
	QhVertex(unsigned int vertex_id)
		:VertexId(vertex_id)
	{}
};

struct QhFace : public QhElement
{
	QhHalfEdge *OneBorderingEdge = nullptr;
	
	~QhFace()
	{
		//std::cout << "Deleted face: " << this << std::endl;
	}
};

bool operator == (const QhFace &one_face,const QhFace &other_face);

struct QhHalfEdge : public QhElement
{
	QhVertex	*BeginVertex	= nullptr;
	QhHalfEdge	*Pair			= nullptr;
	QhFace		*BorderedFace	= nullptr;
	QhHalfEdge	*NextHalfEdge	= nullptr;
	
	~QhHalfEdge()
	{
		//std::cout << "Deleted half edge: " << this << std::endl;
	}
};


#include <list>

struct QhMesh
{
	std::list<QhVertex>		Vertices;
	std::list<QhHalfEdge>	HalfEdges;
	std::list<QhFace>		Faces;
	
	void DeleteDeletedFaces()
	{
		for(auto I = Faces.begin();I != Faces.end();)
		{
			auto J = I;
			I++;
			if(J->IsDeleted())
			{
				Faces.erase(J);
			}
		}
		
		for(auto I = HalfEdges.begin();I != HalfEdges.end();)
		{
			auto J = I;
			I++;
			if(J->IsDeleted())
			{
				HalfEdges.erase(J);
			}
		}
	}
};

void QhSetBorderLinks(QhHalfEdge *borders[3],QhFace *triangle);

void QhConnectTriangleHalfedges(std::list<QhFace *> &new_triangles);

void QhGetTriangleIds(const QhFace &face,unsigned int ids[3]);

void QhGetAdjacentHalfEdges(QhFace &triangle,QhHalfEdge *adjacent_edges[3]);

void QhGetBorderingHalfEdges(QhFace &triangle,QhHalfEdge *bordering_edges[3]);

#endif // QH_MESH_H
