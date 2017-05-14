
#include "GLExt.h"

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

PFNGLUNIFORM1FPROC glUniform1f;


void InitGL(const QOpenGLContext *context)
{
	glGenBuffers = (PFNGLGENBUFFERSPROC)context->getProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)context->getProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)context->getProcAddress("glBufferData");
	glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)context->getProcAddress("glDeleteBuffers");
	//
	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)context->getProcAddress("glGenVertexArrays");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)context->getProcAddress("glBindVertexArray");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)context->getProcAddress("glEnableVertexAttribArray");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)context->getProcAddress("glVertexAttribPointer");
	glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)context->getProcAddress("glDeleteVertexArrays");
	//
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
	//
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)context->getProcAddress("glGetUniformLocation");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)context->getProcAddress("glGetAttribLocation");
	//
	glUniform1f = (PFNGLUNIFORM1FPROC)context->getProcAddress("glUniform1f");
}
