
#include "TreeDemo.h"

#include <DemoUtils/DrawSkeleton.h>
#include <DemoUtils/DrawModel.h>

void TreeDemo::Draw()
{
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	
	DrawSkeleton DrawSkel;
	
	switch(State)
	{
	case DRAW_HYPERGRAPH:
		DrawHypergraph(Hypergraph);
		break;
		
	case DRAW_MESH:
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,TextureId);
		
		glColor3f(1.0,1.0,1.0);
		DrawMultiMesh(*Mesh);
		
		glDisable(GL_TEXTURE_2D);
		
	case DRAW_SKELETON:
		glDisable(GL_CULL_FACE);
		
		glColor3f(0.0,1.0,0.0);
		DrawSkel.Draw(TreeSkeleton);
	}
}
