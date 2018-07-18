#pragma once

#include <vector>
#include "Cell.h"

enum ShapeType
{
	SHAPE_I,
	SHAPE_T,
	SHAPE_O,
	SHAPE_J,
	SHAPE_L,
	SHAPE_S,
	SHAPE_Z
};

struct Shape : public Cell
{
	std::vector<Cell*> cells;
	int square;

	Shape() : Cell(0, 0)
	{
		// empty
	}

	~Shape()
	{
		for (int i = 0; i < cells.size(); i++)
		{
			delete cells[i];
		}

		cells.clear();
	}
};