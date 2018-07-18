#pragma once

#include "BaseApp.h"
#include "Board.h"
#include "Shape.h"

class TetrisApp : public BaseApp
{
private:
	Board* mMainBoard;
	Board* mPreviewBoard;
	Shape* mCurShape;
	Shape* mNextShape;

	bool mIsFallingFast;
	float mFallingSpeed;
	float mSleepTime;

	void PlaceShape(Shape* shape, int x, int y);
	bool TryRotateShape(Board* board, Shape* shape);
	bool TryMoveShape(Board* board, Shape* shape, int dx, int dy);

public:
	TetrisApp();
	virtual ~TetrisApp();

	virtual void KeyPressed(int btnCode);
	virtual void UpdateF(float deltaTime);
};