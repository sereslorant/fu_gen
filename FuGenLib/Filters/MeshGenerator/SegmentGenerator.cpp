
#include "SegmentGenerator.h"

#include "../../Const.h"
/*
void SegmentData::GenerateVertices(unsigned int segment_width,unsigned int segment_height,Mesh<glm::vec3> &segment_mesh)
{
	float dt = (t_End - t_Begin)/(segment_height - 1);
	float dAngle = 2.0*PI/segment_width;
	//
	for(unsigned int i=0;i < segment_height;i++)
	{
		unsigned int j;
		for(j=0;j < segment_width;j++)
		{
			float x = t_Begin + i*dt;
			float y = j*dAngle;
			segment_mesh.Vertices[i*segment_width + j] = Cylinder.GetPoint(x,y);
			//
			x /= (t_End - t_Begin);
			y /= 2.0*PI;
			segment_mesh.TexCoords[i*(segment_width + 1) + j] = glm::vec2(y,x);
		}
		//
		float x = t_Begin + i*dt;
		float y = j*dAngle;
		//
		x /= (t_End - t_Begin);
		y /= 2.0*PI;
		segment_mesh.TexCoords[i*(segment_width + 1) + j] = glm::vec2(y,x);
	}
}
*/
void SegmentGenerator::GenerateVertices()
{
	float dt = (t_End - t_Begin)/(SegmentHeight - 1);
	float dAngle = 2.0*PI/SegmentWidth;
	//
	for(unsigned int i=0;i < SegmentHeight;i++)
	{
		unsigned int j;
		for(j=0;j < SegmentWidth;j++)
		{
			float x = t_Begin + i*dt;
			float y = j*dAngle;
			SegmentMesh.Vertices[i*SegmentWidth + j] = Cylinder.GetPoint(x,y);
			//
			x /= (t_End - t_Begin);
			y /= 2.0*PI;
			SegmentMesh.TexCoords[i*(SegmentWidth + 1) + j] = vec4(y,x);
		}
		//
		float x = t_Begin + i*dt;
		float y = j*dAngle;
		//
		x /= (t_End - t_Begin);
		y /= 2.0*PI;
		SegmentMesh.TexCoords[i*(SegmentWidth + 1) + j] = vec4(y,x);
	}
}

void SegmentGenerator::GenerateTriangles()
{
	for(unsigned int i=0;i < NumTriangleRows();i++)
	{
		for(unsigned int j=0;j < SegmentWidth;j++)
		{
			unsigned int I = (i+1);
			unsigned int J = (j+1) % SegmentWidth;
			//
			unsigned int V1_Id = i*SegmentWidth + j;
			unsigned int V2_Id = i*SegmentWidth + J;
			unsigned int V3_Id = I*SegmentWidth + j;
			unsigned int V4_Id = I*SegmentWidth + J;
			//
			unsigned int V1_TexCoord = i*(SegmentWidth + 1) + j;
			unsigned int V2_TexCoord = i*(SegmentWidth + 1) + (j+1);
			unsigned int V3_TexCoord = I*(SegmentWidth + 1) + j;
			unsigned int V4_TexCoord = I*(SegmentWidth + 1) + (j+1);
			//
			Triangle T1;
			T1.VertexId[2] = V1_Id;
			T1.VertexId[1] = V2_Id;
			T1.VertexId[0] = V3_Id;
			//
			T1.TexCoordId[2] = V1_TexCoord;
			T1.TexCoordId[1] = V2_TexCoord;
			T1.TexCoordId[0] = V3_TexCoord;
			//
			Triangle T2;
			T2.VertexId[2] = V3_Id;
			T2.VertexId[1] = V2_Id;
			T2.VertexId[0] = V4_Id;
			//
			T2.TexCoordId[2] = V3_TexCoord;
			T2.TexCoordId[1] = V2_TexCoord;
			T2.TexCoordId[0] = V4_TexCoord;
			//
			unsigned int T1Index = i*NumTrianglesPerRow() + j*2;
			unsigned int T2Index = T1Index + 1;
			SegmentMesh.Triangles[T1Index] = T1;
			SegmentMesh.Triangles[T2Index] = T2;
		}
	}
}