#include <graphics\TextureRectangle.h>

pm::TextureRectangle::TextureRectangle() : Component()
{
	rectangle[0] = 0;
	rectangle[1] = 1;
	rectangle[2] = 1;
	rectangle[3] = 0;
}

pm::TextureRectangle::TextureRectangle(float left, float top, float right, float bottom) : Component()
{
	rectangle[0] = left;
	rectangle[1] = top;
	rectangle[2] = right;
	rectangle[3] = bottom;
}

void pm::TextureRectangle::SetTextureRectangle(float newLeft, float newTop, float newRight, float newBottom)
{
	rectangle[0] = newLeft;
	rectangle[1] = newTop;
	rectangle[2] = newRight;
	rectangle[3] = newBottom;
}

glm::vec4 pm::TextureRectangle::GetTextureRectangle()
{
	return rectangle;
}