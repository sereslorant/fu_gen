#ifndef SEGMENT_GENERATOR_H
#define SEGMENT_GENERATOR_H

#include "../../Data/MultiMesh.h"

#include "../../Utils/GeneralizedCylinder.h"
/*
class SegmentData
{
private:
	GeneralizedCylinder Cylinder;
	//
	float t_Begin;
	float t_End;
	//
public:
	//
	void GenerateVertices(unsigned int segment_width,unsigned int segment_height,Mesh<glm::vec3> &segment_mesh);
	//
	SegmentData(const GeneralizedCylinder &cylinder,float t_begin,float t_end)
		:Cylinder(cylinder),t_Begin(t_begin),t_End(t_end)
	{}
	//
	~SegmentData()
	{}
	/*
	 * End of class
	 * /
};
*/
class SegmentGenerator
{
private:
	GeneralizedCylinder Cylinder;
	//
	float t_Begin;
	float t_End;
	//
	unsigned int SegmentWidth;
	unsigned int SegmentHeight;
	//
	Mesh<vec4> &SegmentMesh;
	//
	/*void GenerateVertices()
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
				SegmentMesh.TexCoords[i*(SegmentWidth + 1) + j] = glm::vec2(y,x);
			}
			//
			float x = t_Begin + i*dt;
			float y = j*dAngle;
			//
			x /= (t_End - t_Begin);
			y /= 2.0*PI;
			SegmentMesh.TexCoords[i*(SegmentWidth + 1) + j] = glm::vec2(y,x);
		}
	}
	*/
	//
	unsigned int NumVertices()
	{
		return SegmentWidth*SegmentHeight;
	}
	//
	unsigned int NumTexCoords()
	{
		return (SegmentWidth+1)*SegmentHeight;
	}
	//
	unsigned int NumTriangleRows()
	{
		return (SegmentHeight - 1);
	}
	//
	unsigned int NumTrianglesPerRow()
	{
		return SegmentWidth * 2;
	}
	//
	unsigned int NumTriangles()
	{
		return NumTriangleRows()*NumTrianglesPerRow();
	}
	//
	void GenerateVertices();
	//
	void GenerateTriangles();
	//
public:
	//
	void SampleSegment()
	{
		SegmentMesh = Mesh<vec4>(NumVertices(),NumTexCoords(),NumTriangles());
		//
		GenerateVertices();
		//
		GenerateTriangles();
	}
	//
	SegmentGenerator(	const GeneralizedCylinder &cylinder,float t_begin,float t_end,
						unsigned int segment_width,unsigned int segment_height,
						Mesh<vec4> &segment_mesh)
		:Cylinder(cylinder),t_Begin(t_begin),t_End(t_end),
		SegmentWidth(segment_width),SegmentHeight(segment_height),
		SegmentMesh(segment_mesh)
	{}
	//
	~SegmentGenerator()
	{}
	/*
	 * End of class
	 */
};

#endif // SEGMENT_GENERATOR_H
