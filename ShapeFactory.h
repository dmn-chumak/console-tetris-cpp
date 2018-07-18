#pragma once

#include "Shape.h"

class ShapeFactory
{
public:
	static Shape* createShapeByType(ShapeType type);
	static Shape* createRandomShape();
	static void destroyShape(Shape* shape);
};