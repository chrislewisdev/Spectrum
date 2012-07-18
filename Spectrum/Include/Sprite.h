/********************************************************************
*Spectrum
*Sprite.h by Chris Lewis
********************************************************************/

#ifndef SPECTRUM_SPRITE_H
#define SPECTRUM_SPRITE_H

#include <Windows.h>
#include <gl/GL.h>
#include <il/il.h>
#include <il/ilu.h>
#include <il/ilut.h>
#include <Box2D.h>

class Sprite
{
public:
	//Constructor takes filename of image to use as the sprite
	Sprite(const char *filename);
	//Destructor deletes our texture
	~Sprite();

	//Declare public functions
	void Draw(CEngine::Box2D area) const;

private:
	//Declare private functions
	//This function loads in our image for our texture
	void Load(const char *filename);

	//Declare private properties
	//OpenGL texture handle
	GLuint texture;
};

#endif