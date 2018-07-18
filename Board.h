#pragma once

#include "BaseApp.h"
#include "Shape.h"

class Board
{
private:
	bool** mArea;
	int mWidth;
	int mHeight;
	int mX;
	int mY;

public:
	Board(int x, int y, int width, int height);
	~Board();

	void DrawShape(BaseApp* app, Shape* shape);
	void DrawArea(BaseApp* app);

	void JoinAreaWithShape(Shape* shape);
	void ClearArea();
	void RemoveFilledLines();

	bool IsCellEmpty(int x, int y);
	bool IsCellInBounds(int x, int y);
	bool IsGameOver();
};