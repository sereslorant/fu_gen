
#include "DemoTexture.h"

#include <SOIL/SOIL.h>

struct Color
{
	float r, g, b;
	
	Color(float r0, float g0, float b0)
	{
		r = r0;
		g = g0;
		b = b0;
	}
};

GLuint CreateTexture()
{
	const unsigned int TEXTURE_X = 2;
	const unsigned int TEXTURE_Y = 2;

	Color Texture[TEXTURE_X][TEXTURE_Y] = {{Color(0.0,1.0,0.0),Color(0.0,0.8,0.2)},{Color(0.0,0.8,0.0),Color(0.0,1.0,0.2)}};
	
	GLuint TextureId;
	
	glGenTextures(1,&TextureId);
	glBindTexture(GL_TEXTURE_2D,TextureId);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TEXTURE_X, TEXTURE_Y, 0, GL_RGB, GL_FLOAT, &Texture[0][0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glBindTexture(GL_TEXTURE_2D,0);

	return TextureId;
}

GLuint LoadBarkTexture()
{
	GLuint BarkTexId = SOIL_load_OGL_texture("SeamlessBark2.jpg",
										SOIL_LOAD_AUTO,
										SOIL_CREATE_NEW_ID,
										/*SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT*/
										SOIL_FLAG_DDS_LOAD_DIRECT);
	
	glBindTexture(GL_TEXTURE_2D,BarkTexId);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	glBindTexture(GL_TEXTURE_2D,0);
	
	return BarkTexId;
}
