#ifndef GL_PRIMITIVE_RENDERER_H
#define GL_PRIMITIVE_RENDERER_H

#include "GLPrimitiveList.h"

#include <list>

class GLDrawableList : public IGLDrawableList
{
private:
	std::list<const IGLDrawable *> Drawables;
	//
public:
	//
	virtual void Clear() override
	{
		Drawables.clear();
	}
	//
	virtual void Add(const IGLDrawable *new_drawable) override
	{
		Drawables.push_back(new_drawable);
	}
	//
	virtual void Remove(const IGLDrawable *removable_drawable) override
	{
		Drawables.remove(removable_drawable);
	}
	//
	virtual void Draw(IGLShaderProgram &renderer) const override
	{
		for(const IGLDrawable *Drawable : Drawables)
		{
			std::cout << "Before drawable: " << glGetError() << std::endl;
			Drawable->Draw(renderer);
			std::cout << "After drawable: " << glGetError() << std::endl;
		}
	}
	//
	GLDrawableList()
	{}
	//
	virtual ~GLDrawableList() override
	{
		//
	}
	/*
	 * End of class
	 */
};

#endif // GL_PRIMITIVE_RENDERER_H
