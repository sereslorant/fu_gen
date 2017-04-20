
#include "GLEdgeVisualizer.h"

const char *VertexShaderSource = R"(
#version 150

in vec3 Position;
in vec3 Velocity;
in float Time;

out CtrlPointData
{
	vec3 gVelocity;
	float gTime;
} CtrlPoint;

void main()
{
	CtrlPoint.gVelocity = Velocity;
	CtrlPoint.gTime = Time;
	gl_Position = vec4(Position.x,Position.y,0.0,1.0);
}
)";

const char *GSHermiteHelper = R"(
#version 150

vec3 Hermite(vec3 p0,vec3 p1,vec3 v0,vec3 v1,float t0,float t1,float t)
{
	vec3 a0 = p0;
	vec3 a1 = v0;
	vec3 a2 = (3.0f*(p1-p0)/pow(t1-t0,2)) - ((v1+2.0f*v0)/(t1-t0));
	vec3 a3 = (2.0f*(p0-p1)/pow(t1-t0,3)) + ((v1+v0)/pow(t1-t0,2));

	return a0 + a1*(t-t0) + a2*pow(t-t0,2) + a3*pow(t-t0,3);
}

vec3 HermiteDerivative(vec3 p0,vec3 p1,vec3 v0,vec3 v1,float t0,float t1,float t)
{
	vec3 a1 = v0;
	vec3 a2 = (3.0f*(p1-p0)/pow(t1-t0,2)) - ((v1+2.0f*v0)/(t1-t0));
	vec3 a3 = (2.0f*(p0-p1)/pow(t1-t0,3)) + ((v1+v0)/pow(t1-t0,2));

	return a1 + 2.0f*a2*(t-t0) + 3.0f*a3*(pow(t-t0,2));
}

vec3 GetCylinderPoint(vec3 p0,vec3 v0,float t0,
			vec3 p1,vec3 v1,float t1,
			float radius,
			float spine_param,float angle)
{
	vec3 HermitePoint = Hermite(p0,p1,v0,v1,t0,t1,spine_param);
	vec3 HermiteDeriv = HermiteDerivative(p0,p1,v0,v1,t0,t1,spine_param);
	
	vec3 up = vec3(0,1,1);
	
	/*vec3 i = vec3(1,0,0);
	vec3 j = vec3(0,1,0);
	vec3 k = vec3(0,0,1);*/
	
	vec3 j = HermiteDeriv;
	vec3 i = cross(up,j);
	vec3 k = cross(i,j);
	
	j = normalize(j);
	i = normalize(i);
	k = normalize(k);

	vec3 DiskPoint = cos(angle)*i + sin(angle)*k;

	return HermitePoint + radius * DiskPoint;
}

vec4 Transform(vec3 pos)
{
	return vec4(pos.x / 8.0 - 0.8,pos.y / 8.0 - 0.8,0.0,1.0);
}

)";

const char *CatmullRomSource = R"(
#version 150

layout (lines) in;
layout (line_strip,max_vertices = 10) out;

in CtrlPointData
{
	vec3 gVelocity;
	float gTime;
} CtrlPoint[2];

vec3 Hermite(vec3 p0,vec3 p1,vec3 v0,vec3 v1,float t0,float t1,float t);

vec4 Transform(vec3 pos);

void main()
{
	vec3 p0  = gl_in[0].gl_Position.xyz;
	vec3 p1  = gl_in[1].gl_Position.xyz;
	vec3 v0  = CtrlPoint[0].gVelocity;
	vec3 v1  = CtrlPoint[1].gVelocity;
	float t0 = CtrlPoint[0].gTime;
	float t1 = CtrlPoint[1].gTime;
	float dt = (t1 - t0) / 9;
	for(int i=0;i < 10;i++)
	{
		vec3 HermitePos = Hermite(p0,p1,v0,v1,t0,t1,t0 + i*dt);
		gl_Position = Transform(HermitePos);
		//
		EmitVertex();
	}
	EndPrimitive();
}
)";

const char *GenCylinderSource = R"(
#version 150

layout (lines) in;
layout (triangle_strip,max_vertices = 256) out;

uniform float BeginTime;
uniform float EndTime;

uniform float Radius;

in CtrlPointData
{
	vec3 gVelocity;
	float gTime;
} CtrlPoint[2];

vec3 GetCylinderPoint(vec3 p0,vec3 v0,float t0,
			vec3 p1,vec3 v1,float t1,
			float radius,
			float spine_param,float angle);

float PI = 3.14159265359;

int Width = 6;
int Height = 6;

vec4 Transform(vec3 pos);

void main()
{
	vec3 p0  = gl_in[0].gl_Position.xyz;
	vec3 p1  = gl_in[1].gl_Position.xyz;
	vec3 v0  = CtrlPoint[0].gVelocity;
	vec3 v1  = CtrlPoint[1].gVelocity;
	float t0 = CtrlPoint[0].gTime;
	float t1 = CtrlPoint[1].gTime;
	//
	float tbegin = max(BeginTime,CtrlPoint[0].gTime);
	float tend = min(EndTime,CtrlPoint[1].gTime);
	float dt = (tend - tbegin) / (Height - 1);
	float dAngle = 2.0 * PI / (Width - 1);
	for(int i=0;i < Height - 1;i++)
	{
		for(int j=0;j < Width;j++)
		{
			vec3 CylinderPos = GetCylinderPoint(p0,v0,t0,p1,v1,t1,Radius,tbegin + i*dt,j*dAngle);
			gl_Position = Transform(CylinderPos);
			//
			EmitVertex();
			//
			CylinderPos = GetCylinderPoint(p0,v0,t0,p1,v1,t1,Radius,tbegin + (i+1)*dt,j*dAngle);
			gl_Position = Transform(CylinderPos);
			//
			EmitVertex();
		}
		//
		EndPrimitive();
	}
}
)";

const char *FragmentShaderSource = R"(
#version 150

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0,0.0,0.0,1.0);
}
)";

const char *MeshVertexShaderSource = R"(
#version 150

in vec3 Position;

void main()
{
	gl_Position = vec4(Position.x / 8.0 - 0.8,Position.y / 8.0 - 0.8,0.0,1.0);
}
)";

const char *MeshFragmentShaderSource = R"(
#version 150

out vec4 FragColor;

void main()
{
	FragColor = vec4(0.0,0.0,1.0,1.0);
}
)";


GLuint CompileShader(const char *shader_source,GLenum shader_type);

void GLEdgeVisualizer::Initialize()
{
	glClearColor(1.0,1.0,1.0,1.0);
	//
	VertexShader = CompileShader(VertexShaderSource,GL_VERTEX_SHADER);
	GSHermite = CompileShader(GSHermiteHelper,GL_GEOMETRY_SHADER);
	CatmullRomShader = CompileShader(CatmullRomSource,GL_GEOMETRY_SHADER);
	CylinderShader = CompileShader(GenCylinderSource,GL_GEOMETRY_SHADER);
	FragmentShader = CompileShader(FragmentShaderSource,GL_FRAGMENT_SHADER);
	//
	MeshVertexShader = CompileShader(MeshVertexShaderSource,GL_VERTEX_SHADER);
	MeshFragmentShader = CompileShader(MeshFragmentShaderSource,GL_FRAGMENT_SHADER);
	//
	GLuint CRShaders[4] = {VertexShader,GSHermite,CatmullRomShader,FragmentShader};
	GLuint CyliShaders[4] = {VertexShader,GSHermite,CylinderShader,FragmentShader};
	HypergraphRenderer = new GLHypergraphRenderer(CRShaders,4,CyliShaders,4);
	//
	GLuint MeshShaders[2] = {MeshVertexShader,MeshFragmentShader};
	MeshRenderer = new GLRenderer(MeshShaders,2);
}

void GLEdgeVisualizer::Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	//
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	//
	switch(State)
	{
	case SHOW_HYPERGRAPH:
		HypergraphRenderer->Draw();
		break;
		//
	case SHOW_MESH:
		MeshRenderer->Draw();
		break;
	}
}

#include <iostream>

void PrintShaderCompileError(GLuint shader)
{
	GLint Compiled;
	//
	glGetObjectParameterivARB(shader,GL_COMPILE_STATUS,&Compiled);
	if(!Compiled)
	{
		GLint RetSize;
		char Log[256];
		glGetInfoLogARB(shader,sizeof(Log),&RetSize,Log);
		//
		std::cerr << Log << std::endl;
	}
}

GLuint CompileShader(const char *shader_source,GLenum shader_type)
{
	GLuint Shader = glCreateShader(shader_type);
	glShaderSource(Shader,1,&shader_source,nullptr);
	glCompileShader(Shader);
	//
	PrintShaderCompileError(Shader);
	//
	return Shader;
}
