
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "DrawModel.h"

//const double PI = 3.14159265359;

const vec4 UP = vec4(0.0,0.0,5.0);

void DrawSpline(const ICurve &curve,float t_begin,float t_end,float dt)
{
	glBegin(GL_LINES);

	glColor3f(1.0,0.75,0.0);

	float t = t_begin;
	vec4 Begin = curve.GetPoint(t);
	glVertex3f(Begin[0],Begin[1],Begin[2]);

	t += dt;
	vec4 V = curve.GetPoint(t);
	glVertex3f(V[0],V[1],V[2]);

	while(t < t_end)
	{
		glColor3f(1.0,0.75,0.0);

		glVertex3f(V[0],V[1],V[2]);

		V = curve.GetPoint(t);
		glVertex3f(V[0],V[1],V[2]);

		vec4 V1;
		vec4 V2;
		vec4 V3;

		const bool FRENET_FRAME = false;

		if(FRENET_FRAME)
		{
			ICurve::GetFrenetFrame(curve,t,&V1,&V2,&V3,true);
		}
		else
		{
			ICurve::GetExplicitUpFrame(curve,UP,t,1.0/25.0,&V1,&V2,&V3,true);
		}

		V1 = V + 5.0f*normalize(V1);
		V2 = V + 5.0f*normalize(V2);
		V3 = V + 5.0f*normalize(V3);

		glColor3f(1.0,0.0,0.0);

		glVertex3f(V[0],V[1],V[2]);
		glVertex3f(V1[0],V1[1],V1[2]);

		glColor3f(0.0,1.0,0.0);

		glVertex3f(V[0],V[1],V[2]);
		glVertex3f(V2[0],V2[1],V2[2]);

		glColor3f(0.0,0.0,1.0);

		glVertex3f(V[0],V[1],V[2]);
		glVertex3f(V3[0],V3[1],V3[2]);

		t += dt;
	}

	glVertex2f(Begin[0],Begin[1]);

	glEnd();
}

void DrawGeneralizedCylinder(const GeneralizedCylinder &cylinder,float t0,float t_fin)
{
	vec4 CylinderArray[CYLINDER_ARRAY_HEIGHT][CYLINDER_ARRAY_WIDTH];

	float dt = (t_fin - t0)/(CYLINDER_ARRAY_HEIGHT - 1);

	float dAngle = 2.0*PI/CYLINDER_ARRAY_WIDTH;

	for(unsigned int i=0;i < CYLINDER_ARRAY_HEIGHT;i++)
	{
		for(unsigned int j=0;j < CYLINDER_ARRAY_WIDTH;j++)
		{
			CylinderArray[i][j] = cylinder.GetPoint(t0 + i*dt,j*dAngle);
		}
	}

	glBegin(GL_QUADS);

	for(unsigned int i=0;i < CYLINDER_ARRAY_HEIGHT - 1;i++)
	{
		for(unsigned int j=0;j < CYLINDER_ARRAY_WIDTH;j++)
		{
			unsigned int I = (i+1);
			unsigned int J = (j+1) % CYLINDER_ARRAY_WIDTH;

			glVertex3f(CylinderArray[i][j][0],CylinderArray[i][j][1],CylinderArray[i][j][2]);
			glVertex3f(CylinderArray[I][j][0],CylinderArray[I][j][1],CylinderArray[I][j][2]);
			glVertex3f(CylinderArray[I][J][0],CylinderArray[I][J][1],CylinderArray[I][J][2]);
			glVertex3f(CylinderArray[i][J][0],CylinderArray[i][J][1],CylinderArray[i][J][2]);
		}
	}

	glEnd();
}

void DrawHalfedgeMesh(MyMesh &mesh)
{
	glColor3f(1.0,0.0,0.0);

	glBegin(GL_TRIANGLES);

	//unsigned int k = 0;
	for(MyMesh::FaceIter I = mesh.faces_begin();I != mesh.faces_end();I++)
	{
		for(MyMesh::FaceVertexIter J = mesh.fv_iter(*I);J.is_valid();J++)
		{
			OpenMesh::Vec3f Point = mesh.point(*J);
			glVertex3f(Point[0],Point[1],Point[2]);
		}
		//k++;
	}

	glEnd();
}

void DrawTexturedHalfedgeMesh(MyMesh &mesh)
{
	glBegin(GL_TRIANGLES);

	//unsigned int k = 0;
	for(MyMesh::FaceIter I = mesh.faces_begin();I != mesh.faces_end();I++)
	{
		for(MyMesh::FaceVertexIter J = mesh.fv_iter(*I);J.is_valid();J++)
		{
			auto &Data = mesh.data(*J);
			OpenMesh::Vec3f Point = mesh.point(*J);
			//std::cout << Point[0] << ";" << Point[1] << ";" << Point[2] << std::endl;

			glTexCoord2f(Data.TexCoord[0],Data.TexCoord[1]);
			glVertex3f(Point[0],Point[1],Point[2]);
		}
		//k++;
	}

	glEnd();
}

void DrawHalfedgeVertices(MyMesh &mesh)
{
	glBegin(GL_POINTS);

	for(MyMesh::VertexIter I = mesh.vertices_begin();I != mesh.vertices_end();I++)
	{
		OpenMesh::Vec3f Point = mesh.point(*I);
		glVertex3f(Point[0],Point[1],Point[2]);
	}

	glEnd();
}

bool DRAW_SPLINE = true;
bool DRAW_MODEL = true;
bool DRAW_SPLINE_FRONT_TO_BACK = false;
bool DRAW_CSO = false;
bool DRAW_JUNCTION = false;

void DrawHypergraph(TreeHypergraph *hypergraph)
{
	for(TreeHypergraph::Branch *B : hypergraph->Branches)
	{
		if(DRAW_SPLINE)
		{
			if(DRAW_SPLINE_FRONT_TO_BACK)
			{
				DrawSpline(*B->Curve,-0.25,B->t_End,1.0/20.0);
			}
			else
			{
				DrawSpline(*B->Curve,B->t_Begin,B->t_End,1.0/20.0);
			}
		}

		if(DRAW_CSO)
		{
			glColor3f(0.0,0.0,1.0);
			DrawGeneralizedCylinder(GeneralizedCylinder(*B->Curve,B->Up,B->Width),
									B->t_Begin,
									B->t_End
									);
		}
	}

	//if(DRAW_MODEL)
	//{
		for(TreeHypergraph::Branch *B : hypergraph->Branches)
		{
			if(DRAW_CSO)
			{
				glColor3f(0.0,0.0,1.0);
				DrawGeneralizedCylinder(GeneralizedCylinder(*B->Curve,B->Up,B->Width),
										B->t_Begin,
										B->t_End
										);
			}
		}

		if(DRAW_JUNCTION)
		{
			for(TreeHypergraph::Junction *J : hypergraph->Junctions)
			{
				float dAngle = 2.0*PI/CYLINDER_ARRAY_WIDTH;
				unsigned int NumVertices = J->Children.size()*CYLINDER_ARRAY_WIDTH;

				if(J->Root != 0)
					{NumVertices += CYLINDER_ARRAY_WIDTH;}
				else
					{continue;}

				std::vector<VertexData> Vertices(NumVertices);

				unsigned int j=0;
				if(J->Root != nullptr)
				{
					GeneralizedCylinder Cylinder(*J->Root->Curve,J->Root->Up,J->Root->Width);
					for(unsigned int i=0;i < CYLINDER_ARRAY_WIDTH;i++)
					{
						Vertices[j].Vertex = Cylinder.GetPoint(J->Root->t_End,i*dAngle);
						Vertices[j].SegmentId = J->Root->Id;
						Vertices[j].SampleId = i;
						j++;
					}
				}

				for(TreeHypergraph::Branch *B : J->Children)
				{
					GeneralizedCylinder Cylinder(*B->Curve,B->Up,B->Width);
					for(unsigned int i=0;i < CYLINDER_ARRAY_WIDTH;i++)
					{
						Vertices[j].Vertex = Cylinder.GetPoint(B->t_Begin,i*dAngle);
						Vertices[j].SegmentId = B->Id;
						Vertices[j].SampleId = i;
						j++;
					}
				}

				MyMesh JunctionMesh;

				Quickhull(&Vertices[0],Vertices.size(),JunctionMesh);

				DrawHalfedgeMesh(JunctionMesh);
			}
		}
	//}
}

void DrawMesh(const Mesh<vec4> &DrawableMesh)
{
	glBegin(GL_TRIANGLES);
	//
	for(const Mesh<vec4>::Triangle &T : DrawableMesh.Triangles)
	{
		const vec4 &Tex1 = DrawableMesh.TexCoords[T.TexCoordId[0]];
		const vec4 &V1 = DrawableMesh.Vertices[T.VertexId[0]];
		//
		const vec4 &Tex2 = DrawableMesh.TexCoords[T.TexCoordId[1]];
		const vec4 &V2 = DrawableMesh.Vertices[T.VertexId[1]];
		//
		const vec4 &Tex3 = DrawableMesh.TexCoords[T.TexCoordId[2]];
		const vec4 &V3 = DrawableMesh.Vertices[T.VertexId[2]];
		//
		glTexCoord2f(Tex1[0],Tex1[1]);
		glVertex3f(V1[0],V1[1],V1[2]);
		//
		glTexCoord2f(Tex2[0],Tex2[1]);
		glVertex3f(V2[0],V2[1],V2[2]);
		//
		glTexCoord2f(Tex3[0],Tex3[1]);
		glVertex3f(V3[0],V3[1],V3[2]);
	}
	//
	glEnd();
}

bool DrawBranch = true;

void DrawMultiMesh(MultiMesh &Mesh)
{
	for(auto &Junction : Mesh.JunctionMeshes)
	{
		DrawTexturedHalfedgeMesh(Junction);
	}
	//
	for(auto &Branch : Mesh.Segments)
	{
		if(DrawBranch)
		{
			DrawMesh(Branch);
		}
	}
}