#ifndef SHAPE_H

#define SHAPE_H

#include <vector>

class Shape
{
public:

	Shape();
	~Shape();

private:

	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	int positionX, positionY;
	bool hasTexture;

};
#endif
