#include <graphics\TextureRectangle.h>

pm::TextureRectangle::TextureRectangle() : Component()
{
	left = 0;
	top = 1;
	right = 1;
	bottom = 0;
}

pm::TextureRectangle::TextureRectangle(float left, float top, float right, float bottom) : Component()
{
	this->left =	left;
	this->top =		top;
	this->right =	right;
	this->bottom =	bottom;
}

void pm::TextureRectangle::SetTextureRectangle(float newLeft, float newTop, float newRight, float newBottom)
{
	this->left =	newLeft;
	this->top =		newTop;
	this->right =	newRight;
	this->bottom =	newBottom;
}