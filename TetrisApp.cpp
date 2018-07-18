#include "TetrisApp.h"
#include "Random.h"
#include "ShapeFactory.h"
#include "Constants.h"

TetrisApp::TetrisApp()
{
	Random::setSeed();

	mMainBoard = new Board(MAIN_BOARD_X, MAIN_BOARD_Y, MAIN_BOARD_W, MAIN_BOARD_H);
	mPreviewBoard = new Board(PREVIEW_BOARD_X, PREVIEW_BOARD_Y, PREVIEW_BOARD_W, PREVIEW_BOARD_H);
	
	mCurShape = ShapeFactory::createRandomShape();
	PlaceShape(mCurShape, FALLING_SHAPE_X, FALLING_SHAPE_Y);

	mNextShape = ShapeFactory::createRandomShape();
	PlaceShape(mNextShape, PREVIEW_SHAPE_X, PREVIEW_SHAPE_Y);

	mIsFallingFast = false;
	mFallingSpeed = FALLING_NORMAL_SPD;
	mSleepTime = 0;
}

TetrisApp::~TetrisApp()
{
	delete mMainBoard;
	delete mPreviewBoard;
	delete mCurShape;
	delete mNextShape;
}

void TetrisApp::PlaceShape(Shape* shape, int x, int y)
{
	for (int i = 0; i < shape->cells.size(); i++)
	{
		shape->cells[i]->x += x - shape->x;
		shape->cells[i]->y += y - shape->y;
	}

	shape->x = x;
	shape->y = y;
}

bool TetrisApp::TryRotateShape(Board* board, Shape* shape)
{
	Cell* cell;
	int nx;
	int ny;

	for (int i = 0; i < shape->cells.size(); i++)
	{
		cell = shape->cells[i];
		
		nx = (shape->square - (cell->y - shape->y) - 1) + shape->x;
		ny = (cell->x - shape->x) + shape->y;

		if (!board->IsCellInBounds(nx, ny)
		||  !board->IsCellEmpty(nx, ny))
		{
			return false;
		}
	}

	for (int i = 0; i < shape->cells.size(); i++)
	{
		cell = shape->cells[i];
		
		nx = (shape->square - (cell->y - shape->y) - 1) + shape->x;
		ny = (cell->x - shape->x) + shape->y;

		cell->x = nx;
		cell->y = ny;
	}

	return true;
}

bool TetrisApp::TryMoveShape(Board* board, Shape* shape, int dx, int dy)
{
	int nx;
	int ny;

	for (int i = 0; i < shape->cells.size(); i++)
	{
		nx = shape->cells[i]->x + dx;
		ny = shape->cells[i]->y + dy;

		if (!board->IsCellInBounds(nx, ny)
		||  !board->IsCellEmpty(nx, ny))
		{
			return false;
		}
	}

	for (int i = 0; i < shape->cells.size(); i++)
	{
		shape->cells[i]->x += dx;
		shape->cells[i]->y += dy;
	}

	shape->x += dx;
	shape->y += dy;

	return true;
}

void TetrisApp::KeyPressed(int btnCode)
{
	if (mIsFallingFast)
	{
		return;
	}

	switch (btnCode)
	{
		case KEYBOARD_ROTATE:
		{
			TryRotateShape(mMainBoard, mCurShape);
			break;
		}

		case KEYBOARD_LEFT:
		{
			TryMoveShape(mMainBoard, mCurShape, -1, 0);
			break;
		}

		case KEYBOARD_RIGHT:
		{
			TryMoveShape(mMainBoard, mCurShape, 1, 0);
			break;
		}

		case KEYBOARD_DOWN:
		{
			mIsFallingFast = true;
			mFallingSpeed = FALLING_FAST_SPD;
			break;
		}
	}
}

void TetrisApp::UpdateF(float deltaTime)
{
	mSleepTime += deltaTime;

	if (mSleepTime < mFallingSpeed)
	{
		return;
	}
	
	mSleepTime -= mFallingSpeed;

	if (!TryMoveShape(mMainBoard, mCurShape, 0, 1))
	{
		mMainBoard->JoinAreaWithShape(mCurShape);

		if (mMainBoard->IsGameOver())
		{
			mMainBoard->ClearArea();
		}
		else
		{
			mMainBoard->RemoveFilledLines();
		}

		ShapeFactory::destroyShape(mCurShape);

		mCurShape = mNextShape;
		PlaceShape(mCurShape, FALLING_SHAPE_X, FALLING_SHAPE_Y);

		mNextShape = ShapeFactory::createRandomShape();
		PlaceShape(mNextShape, PREVIEW_SHAPE_X, PREVIEW_SHAPE_Y);

		mIsFallingFast = false;
		mFallingSpeed = FALLING_NORMAL_SPD;
	}

	mMainBoard->DrawArea(this);
	mMainBoard->DrawShape(this, mCurShape);

	mPreviewBoard->DrawArea(this);
	mPreviewBoard->DrawShape(this, mNextShape);
}