
#include "FuGenGLView.h"

#include <glmath.hpp>

void CreateTestTriangle(vec4 triangle_array[3])
{
	triangle_array[0] = { 0.0, 0.8};
	triangle_array[1] = {-0.8,-0.8};
	triangle_array[2] = { 0.8,-0.8};
}

void CreateTestLinestrip(vec4 line_strip[4])
{
	line_strip[0] = { 1.0,-1.0};
	line_strip[1] = { 0.0, 1.0};
	line_strip[2] = {-1.0,-1.0};
}

PFNGLGENBUFFERSPROC glGenBuffers;
PFNGLBINDBUFFERPROC glBindBuffer;
PFNGLBUFFERDATAPROC glBufferData;
PFNGLDELETEBUFFERSPROC glDeleteBuffers;

PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;

PFNGLCREATESHADERPROC glCreateShader;
PFNGLSHADERSOURCEPROC glShaderSource;
PFNGLCOMPILESHADERPROC glCompileShader;
PFNGLDELETESHADERPROC glDeleteShader;

PFNGLGETOBJECTPARAMETERIVARBPROC glGetObjectParameterivARB;
PFNGLGETINFOLOGARBPROC glGetInfoLogARB;

PFNGLCREATEPROGRAMPROC glCreateProgram;
PFNGLATTACHSHADERPROC glAttachShader;
PFNGLDETACHSHADERPROC glDetachShader;
PFNGLLINKPROGRAMPROC glLinkProgram;
PFNGLUSEPROGRAMPROC glUseProgram;
PFNGLDELETEPROGRAMPROC glDeleteProgram;

PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;

void PrintShaderCompileError(GLuint shader);

const char *VertexShaderSource = R"(
#version 140

in vec2 Position;

void main()
{
	gl_Position = vec4(Position.x,Position.y,0.0,1.0);
}
)";

const char *FragmentShaderSource = R"(
#version 140

out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0,0.0,0.0,1.0);
}
)";


void InitGL(const QOpenGLContext *context)
{
	glGenBuffers = (PFNGLGENBUFFERSPROC)context->getProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)context->getProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)context->getProcAddress("glBufferData");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)context->getProcAddress("glDeleteBuffers");
	
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)context->getProcAddress("glGenVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)context->getProcAddress("glBindVertexArray");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)context->getProcAddress("glEnableVertexAttribArray");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)context->getProcAddress("glVertexAttribPointer");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)context->getProcAddress("glDeleteVertexArrays");
	
	glCreateShader = (PFNGLCREATESHADERPROC)context->getProcAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)context->getProcAddress("glShaderSource");
	glCompileShader = (PFNGLCOMPILESHADERPROC)context->getProcAddress("glCompileShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)context->getProcAddress("glDeleteShader");
	//
	glGetObjectParameterivARB = (PFNGLGETOBJECTPARAMETERIVARBPROC)context->getProcAddress("glGetObjectParameterivARB");
	glGetInfoLogARB = (PFNGLGETINFOLOGARBPROC)context->getProcAddress("glGetInfoLogARB");
	//
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)context->getProcAddress("glCreateProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)context->getProcAddress("glAttachShader");
	glDetachShader = (PFNGLDETACHSHADERPROC)context->getProcAddress("glDetachShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)context->getProcAddress("glLinkProgram");
	glUseProgram = (PFNGLUSEPROGRAMPROC)context->getProcAddress("glUseProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)context->getProcAddress("glDeleteProgram");
	
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)context->getProcAddress("glGetUniformLocation");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)context->getProcAddress("glGetAttribLocation");
}

void FuGenGLView::initializeGL()
{
	//GL.initializeGLFunctions(context());
	//
	InitGL(context());
	//
	glClearColor(1.0,1.0,1.0,1.0);
	//
	VertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShader,1,&VertexShaderSource,nullptr);
	glCompileShader(VertexShader);
	//
	PrintShaderCompileError(VertexShader);
	//
	FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShader,1,&FragmentShaderSource,nullptr);
	glCompileShader(FragmentShader);
	//
	PrintShaderCompileError(FragmentShader);
	//
	Program = glCreateProgram();
	//
	glAttachShader(Program,VertexShader);
	glAttachShader(Program,FragmentShader);
	//
	glLinkProgram(Program);
	//
	glDetachShader(Program,VertexShader);
	glDetachShader(Program,FragmentShader);
	//
	//float VertexArray[] = {0.0,1.0,-1.0,-1.0,1.0,-1.0};
	//float VertexArray[] = {100.0,0.0,0.0,100.0,200.0,100.0};
	vec4 TriangleArray[3];
	CreateTestTriangle(TriangleArray);
	//
	TriangleList = new GLTriangleList(TriangleArray,1,Program);
	//
	CreateTestLinestrip(TriangleArray);
	//
	LineStrip = new GLLineStrip(TriangleArray,3,Program);
}

void FuGenGLView::resizeGL(int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;
	//
	glViewport(0,0,newWidth,newHeight);
}

void FuGenGLView::paintGL()
{
	//std::cout << glGetString(GL_VERSION) << std::endl;
	//
	glClear(GL_COLOR_BUFFER_BIT);
	//
	glUseProgram(Program);
	//
	TriangleList->Draw();
	LineStrip->Draw();
}

FuGenGLView::FuGenGLView(QWidget *parent)
	:QOpenGLWidget(parent)
{
	QSurfaceFormat NewFormat;
	//
	NewFormat.setVersion(3,1);
	NewFormat.setProfile(QSurfaceFormat::CoreProfile);
	//
	setFormat(NewFormat);
}

FuGenGLView::~FuGenGLView()
{
	makeCurrent();
	//glDeleteBuffers(1,&VBO);
	//glDeleteVertexArrays(1,&VAO);
	delete TriangleList;
	delete LineStrip;
	glUseProgram(0);
	glDeleteProgram(Program);
	glDeleteShader(VertexShader);
	glDeleteShader(FragmentShader);
}

#include "FuGenGLView.moc"

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
