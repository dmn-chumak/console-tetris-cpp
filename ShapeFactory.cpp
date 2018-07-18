#include "ShapeFactory.h"
#include "Random.h"

Shape* ShapeFactory::createShapeByType(ShapeType type)
{
	Shape* shape = new Shape();

	switch (type)
	{
		case SHAPE_I:
		{
			shape->cells.push_back(new Cell(0, 1));
			shape->cells.push_back(new Cell(1, 1));
			shape->cells.push_back(new Cell(2, 1));
			shape->cells.push_back(new Cell(3, 1));
			shape->square = 4;
			break;
		}

		case SHAPE_T:
		{
			shape->cells.push_back(new Cell(0, 1));
			shape->cells.push_back(new Cell(1, 0));
			shape->cells.push_back(new Cell(1, 1));
			shape->cells.push_back(new Cell(2, 1));
			shape->square = 3;
			break;
		}

		case SHAPE_O:
		{
			shape->cells.push_back(new Cell(0, 0));
			shape->cells.push_back(new Cell(0, 1));
			shape->cells.push_back(new Cell(1, 0));
			shape->cells.push_back(new Cell(1, 1));
			shape->square = 2;
			break;
		}

		case SHAPE_J:
		{
			shape->cells.push_back(new Cell(0, 0));
			shape->cells.push_back(new Cell(0, 1));
			shape->cells.push_back(new Cell(1, 1));
			shape->cells.push_back(new Cell(2, 1));
			shape->square = 3;
			break;
		}

		case SHAPE_L:
		{
			shape->cells.push_back(new Cell(0, 1));
			shape->cells.push_back(new Cell(1, 1));
			shape->cells.push_back(new Cell(2, 0));
			shape->cells.push_back(new Cell(2, 1));
			shape->square = 3;
			break;
		}

		case SHAPE_S:
		{
			shape->cells.push_back(new Cell(0, 1));
			shape->cells.push_back(new Cell(1, 0));
			shape->cells.push_back(new Cell(1, 1));
			shape->cells.push_back(new Cell(2, 0));
			shape->square = 3;
			break;
		}

		case SHAPE_Z:
		{
			shape->cells.push_back(new Cell(0, 0));
			shape->cells.push_back(new Cell(1, 0));
			shape->cells.push_back(new Cell(1, 1));
			shape->cells.push_back(new Cell(2, 1));
			shape->square = 3;
			break;
		}

		default:
		{
			shape->square = 0;
			break;
		}
	}

	return shape;
}

Shape* ShapeFactory::createRandomShape()
{
	return ShapeFactory::createShapeByType(
		static_cast<ShapeType>(Random::getInt(7))
	);
}

void ShapeFactory::destroyShape(Shape* shape)
{
	delete shape;
}