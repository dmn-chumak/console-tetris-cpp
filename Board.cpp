#include "Board.h"

Board::Board(int x, int y, int width, int height)
{
	mArea = new bool*[height];

	for (int y = 0; y < height; y++)
	{
		mArea[y] = new bool[width];

		for (int x = 0; x < width; x++)
		{
			mArea[y][x] = true;
		}
	}

	mWidth = width;
	mHeight = height;
	mX = x;
	mY = y;
}

Board::~Board()
{
	for (int y = 0; y < mHeight; y++)
	{
		delete[] mArea[y];
	}

	delete[] mArea;
}

void Board::DrawShape(BaseApp* app, Shape* shape)
{
	for (int i = 0; i < shape->cells.size(); i++)
	{
		app->SetChar(mX + shape->cells[i]->x, mY + shape->cells[i]->y, L'*');
	}
}

void Board::DrawArea(BaseApp* app)
{
	for (int y = -1; y <= mHeight; y++)
	{
		for (int x = -1; x <= mWidth; x++)
		{
			if (x == -1 || x == mWidth || y == -1 || y == mHeight)
			{
				app->SetChar(mX + x, mY + y, L'#');
			}
			else
			{
				app->SetChar(mX + x, mY + y, (mArea[y][x] ? L'.' : L'*'));
			}
		}
	}
}

void Board::JoinAreaWithShape(Shape *shape)
{
	for (int i = 0; i < shape->cells.size(); i++)
	{
		mArea[shape->cells[i]->y][shape->cells[i]->x] = false;
	}
}

void Board::ClearArea()
{
	for (int y = 0; y < mHeight; y++)
	{
		for (int x = 0; x < mWidth; x++)
		{
			mArea[y][x] = true;
		}
	}
}

void Board::RemoveFilledLines()
{
	int removed = 0;
	int filled;

	for (int y = mHeight - 1; y > removed; y--)
	{
		filled = 0;

		for (int x = 0; x < mWidth; x++)
		{
			if (removed > 0)
			{
				mArea[y][x] = mArea[y - removed][x];
			}

			if (!mArea[y][x])
			{
				filled++;
			}
		}

		if (filled == mWidth)
		{
			removed++;
			y++;
		}
	}

	for (int y = removed; y >=0; y--)
	{
		for (int x = 0; x < mWidth; x++)
		{
			mArea[y][x] = true;
		}
	}
}

bool Board::IsCellEmpty(int x, int y)
{
	return mArea[y][x];
}

bool Board::IsCellInBounds(int x, int y)
{
	return (x >= 0 && x < mWidth && y >= 0 && y < mHeight);
}

bool Board::IsGameOver()
{
	for (int x = 0; x < mWidth; x++)
	{
		if (!mArea[0][x])
		{
			return true;
		}
	}

	return false;
}