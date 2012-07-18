/******************************************************************
*Spectrum
*Sprite.cpp by Chris Lewis
******************************************************************/

#include "Sprite.h"

using namespace CEngine;

//Constructor
Sprite::Sprite(const char *filename)
{
	Load(filename);
}

//Destructor deletes texture
Sprite::~Sprite()
{
	glDeleteTextures(1, &texture);
}

//This function draws our sprite in the specified area
void Sprite::Draw(Box2D area) const
{
	glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, texture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex2f(area.pos.x, area.pos.y);
		glTexCoord2f(1.0f, 0.0f); glVertex2f(area.pos.x, area.pos.y + area.size.y);
		glTexCoord2f(0.0f, 0.0f); glVertex2f(area.pos.x + area.size.x, area.pos.y + area.size.y);
		glTexCoord2f(0.0f, 1.0f); glVertex2f(area.pos.x + area.size.x, area.pos.y);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_BLEND);
}

//This function loads in our sprite image to texture
void Sprite::Load(const char *filename)
{
	texture = ilutGLLoadImage(const_cast<char*>(filename));
}