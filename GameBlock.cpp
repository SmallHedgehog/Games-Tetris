#include "stdafx.h"
#include "GameBlock.h"


GameBlock::GameBlock(void):
	texture(nullptr)
{
	center_x = 0;
	center_y = 0;
	// 初始化方块指针为nullptr
	for (int i=0; i<4; ++i)
	{
		squares[i] = nullptr;
	}
}

GameBlock::GameBlock(int center_x, int center_y, BlockType type, SDL_Texture* texture):
	type(type), texture(texture)
{
	this->center_x = center_x;
	this->center_y = center_y;
	// 初始化方块指针为nullptr
	for (int i=0; i<4; ++i)
	{
		squares[i] = nullptr;
	}

	SetupBlock(center_x, center_y, texture);
}

GameBlock::GameBlock(BlockType type, SDL_Texture* texture):
	type(type), texture(texture)
{
	center_x = 0;
	center_y = 0;
	// 初始化方块指针为nullptr
	for (int i=0; i<4; ++i)
	{
		squares[i] = nullptr;
	}
}

// 根据游戏块类型来构造我们的游戏块
void GameBlock::SetupBlock(int x, int y, SDL_Texture* texture)
{
	// 根据给定的位置和类型来构造游戏块
	center_x = x;
	center_y = y;
	
	// 清除4个方块，防止内存泄漏
	for (int i=0; i<4; ++i)
	{
		if (squares[i] != nullptr)
		{
			delete squares[i];
			squares[i] = nullptr;
		}
	}

	// 根据给定的游戏块类型来构造游戏块
	switch (type)
	{
	case SQUARE_BLOCK:			// 正方形
		{
			squares[0] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[1] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[2] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[3] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
		}
		break;
	case T_BLOCK:				// T形
		{
			squares[0] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[1] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[2] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[3] = new Square(x - SQUARES_MEDIAN * 3, y + SQUARES_MEDIAN, texture);
		}
		break;
	case L_BLOCK:				// L形
		{
			squares[0] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[1] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[2] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, texture);
			squares[3] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, texture);
		}
		break;
	case BACKWARDS_T_BLOCK:		// 反向L形
		{
			squares[0] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[1] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[2] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[3] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, texture);
		}
		break;
	case STRAIGHT_BLOCK:		// 长方形
		{
			squares[0] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN * 3, texture);
			squares[1] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[2] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[3] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, texture);
		}
		break;
	case S_BLOCK:				// S形
		{
			squares[0] = new Square(x - SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[1] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[2] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[3] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, texture);
		}
		break;
	case BACKWARDS_S_BLOCK:		// 方向S形
		{
			squares[0] = new Square(x + SQUARES_MEDIAN, y - SQUARES_MEDIAN, texture);
			squares[1] = new Square(x + SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[2] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN, texture);
			squares[3] = new Square(x - SQUARES_MEDIAN, y + SQUARES_MEDIAN * 3, texture);
		}
		break;
	default:
		break;
	}
}

// 绘制游戏块
void GameBlock::DrawSquares(SDL_Renderer* renderer)
{
	// 调用Square类中的DrawToRenderer方法
	for (int i=0; i<4; ++i)
	{
		squares[i]->DrawToRenderer(renderer);
	}
}

// 移动游戏块
void GameBlock::Move(Direction dir)
{
	switch (dir)
	{
	case LEFT:
		center_x -= SQUARES_MEDIAN * 2;
		break;
	case RIGHT:
		center_x += SQUARES_MEDIAN * 2;
		break;
	case DOWN:
		center_y += SQUARES_MEDIAN * 2;
		break;
	default:
		break;
	}

	for (int i=0; i<4; ++i)
	{
		squares[i]->Move(dir);
	}
}

// 旋转方块，相对于(0, 0)点旋转90度
void GameBlock::Rotate()
{
	for (int i=0; i<4; ++i)
	{
		// 获取方块中心位置
		int x = squares[i]->getCenter_x();
		int y = squares[i]->getCenter_y();
		
		// 计算方块中心与游戏块中心的相对距离
		x -= center_x;
		y -= center_y;

		// 实际旋转
		int x2 = -y;
		int y2 = x;

		// 将方块移动到正确位置
		x2 += center_x;
		y2 += center_y;

		// 重新设置方块中心位置
		squares[i]->setCenter_x(x2);
		squares[i]->setCenter_y(y2);
	}
}

// 获取旋转后的方块地址，做碰撞检测
int* GameBlock::GetRotatedPositions()
{
	// 存储旋转后的方块地址
	int* SquaresPositions = new int[8];

	for (int i=0; i<4; ++i)
	{
		int x = squares[i]->getCenter_x();
		int y = squares[i]->getCenter_y();
		
		x -= center_x;
		y -= center_y;

		int x2 = -y;
		int y2 = x;

		x2 += center_x;
		y2 += center_y;

		// 记录方块旋转后的地址
		SquaresPositions[i*2] = x2;
		SquaresPositions[i*2+1] = y2;
	}
	return SquaresPositions;
}

Square** GameBlock::GetSquares()
{
	return squares;
}

BlockType GameBlock::getBlockType() const
{
	return type;
}

GameBlock::~GameBlock(void)
{
	// 释放方块纹理资源
	//if (texture)
	//	SDL_DestroyTexture(texture);
	// 释放游戏块资源
	//for (int i=0; i<4; ++i)
	//{
	//	if (squares[i])
	//		delete squares[i];
	//}
}
