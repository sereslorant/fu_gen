#ifndef LOW_POLY_MESH_CREATOR
#define LOW_POLY_MESH_CREATOR

#include "../../Data/TreeHypergraph.h"
#include "../../Data/MultiMesh.h"

#include "../../Multithreading/Worker.h"

/*
 * Május 3 - 4
 */
class LowPolyMeshGenerator
{
private:
	//
	//void SampleSegment(const GeneralizedCylinder &cylinder,float t_begin,float t_end,Mesh<glm::vec3> *mesh);
	//
	//void SampleJunction(const TreeHypergraph::Junction &J,MultiMesh &multi_mesh,MyMesh *junction_mesh);
	//
	//void DeleteTriangles(MyMesh &half_edge);
	//
	//void CollapseEdges(MyMesh &half_edge);
	//
	//void AdjustSegments(MyMesh &half_edge,MultiMesh &multi_mesh);
	//
	//void SetTexCoord(MyMesh &half_edge,MultiMesh &multi_mesh,MyMesh::FaceHalfedgeIter E,unsigned int OneSegmentId,unsigned int OneSampleId,unsigned int OtherSegmentId,unsigned int OtherSampleId);
	//
	//void ParametrizeHalfedge(MyMesh &half_edge);
	//
	/*
	 * Itt válik undorítóvá az egész.
	 * Vagy mégse, mert nincs rá szükség.
	 * (a feature complete-séghez nem is kell, de azért illene megcsinálni.)
	 */
	 /*
	void HalfedgeToMesh(MyMesh &half_edge,VertexData vertices[],unsigned int vertices_size,Mesh<VertexData> *mesh)
	{
		Triangle T;

		for(MyMesh::FaceIter I = half_edge.faces_begin();I != half_edge.faces_end();I++)
		{
			unsigned int Index = 0;
			bool Stop = false;

			for(MyMesh::FaceVertexIter J = half_edge.fv_iter(*I);J.is_valid();J++)
			{
				if(Stop)
				{
					break;
				}

				for(unsigned int i=0;i < vertices_size;i++)
				{
					if(Index == 3)
					{
						Stop = true;
						break;
					}

					//MyMesh::VertexHandle J_Handle = J.handle();
					auto Data = half_edge.data(J);
					if((vertices[i].SegmentId == Data.SegmentId) && (vertices[i].SampleId == Data.SampleId))
					{
						T.VertexId[Index] = i;
						Index++;
						break;
					}
				}
			}

			mesh->Triangles.push_back(T);
		}

		mesh->Vertices.insert(mesh->Vertices.begin(),&vertices[0],&vertices[vertices_size]);

		glColor3f(1.0,1.0,1.0);

		glBegin(GL_TRIANGLES);

			for(Triangle &T : mesh->Triangles)
			{
				glm::vec2 &Tex1 = mesh->TexCoords[T.TexCoordId[0]];
				glm::vec3 &V1 = mesh->Vertices[T.VertexId[0]].Vertex;

				glm::vec2 &Tex2 = mesh->TexCoords[T.TexCoordId[1]];
				glm::vec3 &V2 = mesh->Vertices[T.VertexId[1]].Vertex;

				glm::vec2 &Tex3 = mesh->TexCoords[T.TexCoordId[2]];
				glm::vec3 &V3 = mesh->Vertices[T.VertexId[2]].Vertex;

				glTexCoord2f(Tex1.x,Tex1.y);
				glVertex3f(V1.x,V1.y,V1.z);

				glTexCoord2f(Tex2.x,Tex2.y);
				glVertex3f(V2.x,V2.y,V2.z);

				glTexCoord2f(Tex3.x,Tex3.y);
				glVertex3f(V3.x,V3.y,V3.z);
			}

		glEnd();
	}
	// */
	void GenerateSegments(std::vector<Job *> &generate_segment_jobs,JobQueue &jobQueue,TreeHypergraph *tree_hypergraph,MultiMesh &result);
	//
	void GenerateJunctions(std::vector<Job *> &generate_segment_jobs,JobQueue &jobQueue,TreeHypergraph *tree_hypergraph,MultiMesh &result);
	//
public:
	const float DELTA_UV = 0.15;
	//
	unsigned int SegmentWidth;
	unsigned int SegmentHeight;
	//
	void Generate(TreeHypergraph *tree_hypergraph,MultiMesh &result);

	LowPolyMeshGenerator(unsigned int segment_width,unsigned int segment_height)
		:SegmentWidth(segment_width),SegmentHeight(segment_height)
	{}

	~LowPolyMeshGenerator()
	{}
};

#endif // LOW_POLY_MESH_CREATOR
