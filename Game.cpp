#include "stdafx.h"
#include "Game.h"


Game::Game(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* Font):
	FocusBlock(nullptr), NextBlock(nullptr), renderer(renderer),
	texture(texture), Font(Font)
{
	Score	= 0;
	Level	= 1;
	FocusBlockSpeed = INITIAL_SPEED;
}

// 初始化游戏
void Game::Init()
{
	// 初始化随机数种子
	srand((unsigned int)time(0));
	// 初始化游戏块，位置等信息
	FocusBlock = new GameBlock(BLOCK_START_X, BLOCK_START_Y, (BlockType)(rand() % 7), texture);
	NextBlock = new GameBlock(NEXT_BLOCK_X, NEXT_BLOCK_Y, (BlockType)(rand() % 7), texture);
}

// 当前游戏自动向下移动
void Game::GameBlock_selfMove()
{
	// 当前游戏块向下移动每一帧的逻辑
	static int GameBlock_down_counter = 0;
	// 当当前游戏块移动到底部的逻辑
	static int Slide_counter = SLIDE_TIME;

	// 处理当前游戏块自动下落
	GameBlock_down_counter++;
	if (GameBlock_down_counter >= FocusBlockSpeed)
	{
		// 游戏块向下移动需要做碰撞检测
		if (!CheckWallCollisions(FocusBlock, DOWN) && 
			!CheckEntityCollisions(FocusBlock, DOWN))
		{
			FocusBlock->Move(DOWN);
			GameBlock_down_counter = 0;
		}
	}

	// 处理当前游戏块移动到底部的逻辑
	if (CheckWallCollisions(FocusBlock, DOWN) || 
		CheckEntityCollisions(FocusBlock, DOWN))
	{
		Slide_counter--;
	}
	else
	{
		Slide_counter = SLIDE_TIME;
	}
	
	if (Slide_counter == 0)
	{
		Slide_counter = SLIDE_TIME;
		HandleStaticBlockCollision();
	}

	// 绘制
	Draw();
}

// 绘制当前游戏块、下一个游戏块以及所有方块
void Game::Draw()
{
	// 绘制当前游戏块、下一个游戏块
	FocusBlock->DrawSquares(renderer);
	NextBlock->DrawSquares(renderer);
	// 绘制所有方块
	for (int i=0; i<GameSquares.size(); ++i)
	{
		GameSquares[i]->DrawToRenderer(renderer);
	}

	// 绘制当前得分、进入下一关所需得分、级别
	char nex_square[50];
	sprintf_s(nex_square, "NEXT SQUARE:");
	Draw_text(nex_square, NEXT_BLOCK_X - 95, (NEXT_BLOCK_Y - 115));
	// 得分
	char cur_score[50];
	sprintf_s(cur_score, "CURRENT SCORE: %d", Score);
	Draw_text(cur_score, SCORE_POSITION_X, SCORE_POSITION_Y);
	// 级别
	char cur_level[50];
	sprintf_s(cur_level, "CURRENT LEVEL: %d", Level);
	Draw_text(cur_level, LEVEL_POSITION_X, LEVEL_POSITION_Y);
	// 每关所需得分
	char level_score[50];
	sprintf_s(level_score, "SCORE OF LEVEL: %d", SCORE_PRE_LEVEL);
	Draw_text(level_score, SCORE_PER_LEVEL_X, SCORE_PER_LEVEL_Y);
	// 当前游戏块下落速度
	char cur_speed[50];
	sprintf_s(cur_speed, "CURRENT SPEED: %d", INITIAL_SPEED);
	Draw_text(cur_speed, SPEED_X, SPEED_Y);
}

void Game::Draw_text(std::string message, int x, int y)
{
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* surface = TTF_RenderText_Blended(Font, message.c_str(), color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	int width = 0, height = 0;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	SDL_Rect rect = {
		x, y, width, height
	};
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

// 检测游戏块是否与Wall碰撞
bool Game::CheckWallCollisions(GameBlock* FocusGameBlock, Direction dir)
{
	Square** squares = FocusGameBlock->GetSquares();
	for (int i=0; i<4; ++i)
	{
		if (CheckWallCollisions(squares[i], dir))
			return true;
	}

	return false;
}

bool Game::CheckWallCollisions(Square* square, Direction dir)
{
	// 每移动一次的距离
	int Distance = SQUARES_MEDIAN * 2;
	// 获得给定方块的中心
	int x = square->getCenter_x();
	int y = square->getCenter_y();

	bool result = false;
	switch (dir)
	{
	case LEFT:
		{
			if ((x - Distance) < GAME_AREA_LEFT)
				result = true;
			else
				result = false;
		}
		break;
	case RIGHT:
		{
			if ((x + Distance) > GAME_AREA_RIGHT)
				result = true;
			else
				result = false;
		}
		break;
	case DOWN:
		{
			if ((y + Distance) > GAME_AREA_BOTTOM)
				result = true;
			else
				result = false;
		}
		break;
	default:
		break;
	}

	return result;
}

bool Game::CheckEntityCollisions(Square* square, Direction dir)
{
	// 两个方块之间的距离
	int Distance = SQUARES_MEDIAN * 2;
	// 获得给定方块的中心
	int centerX = square->getCenter_x();
	int centerY = square->getCenter_y();

	switch (dir)
	{
	case LEFT:
		centerX -= Distance;
		break;
	case RIGHT:
		centerX += Distance;
		break;
	case DOWN:
		centerY += Distance;
		break;
	default:
		break;
	}
	// 检测给定方块是否与其它方块发生碰撞
	for (int i=0; i<GameSquares.size(); ++i)
	{
		int x = GameSquares[i]->getCenter_x();
		int y = GameSquares[i]->getCenter_y();
		if ((abs(x - centerX) < Distance) && 
			(abs(y - centerY) < Distance))
		{
			return true;
		}
	}

	return false;
}

// 检测游戏块是否与其它块碰撞
bool Game::CheckEntityCollisions(GameBlock* FocusGameBlock, Direction dir)
{
	Square** squares = FocusGameBlock->GetSquares();
	for (int i=0; i<4; ++i)
	{
		if (CheckEntityCollisions(squares[i], dir))
			return true;
	}

	return false;
}

// 处理游戏块移动到底部时的逻辑
void Game::HandleStaticBlockCollision()
{
	// 改变焦点块
	ChangeFocusBlock();
	// 获得已完成的行数
	int completeNums = CalcCompleteRows();

	if (completeNums > 0)
	{
		// 计算获得的分数
		Score += SCORE_PRE_LINE * completeNums;
		// 判断是否能进入下一关
		if (Score >= Level * SCORE_PRE_LEVEL)
		{
			Level++;
			// is Win?
			// 每进入下一关游戏块的移动速度将会增加
			FocusBlockSpeed -= SPEED_CHANGE;
		}
	}

	// is Fail?

}

// 检测当前游戏块旋转后是否发生碰撞
bool Game::CheckRotationCollisions(GameBlock* block)
{
	// 获取当前游戏块旋转后的位置
	int* arr = block->GetRotatedPositions();
	// 两个方块中心之间的距离
	int Distance = SQUARES_MEDIAN * 2;

	// 检测Wall和已有的方块
	for (int i=0; i<4; ++i)
	{
		// 检测左右游戏边界
		if (arr[i*2] < GAME_AREA_LEFT ||
			arr[i*2] > GAME_AREA_RIGHT)
		{
			delete arr;
			return true;
		}
		// 检测游戏下方边界
		if (arr[i*2 + 1] > GAME_AREA_BOTTOM)
		{
			delete arr;
			return true;
		}
		// 与已有的方块比较
		for (int j=0; j<GameSquares.size(); ++j)
		{
			if ((abs(arr[i*2] - GameSquares[j]->getCenter_x()) < Distance) && 
				(abs(arr[i*2+1] - GameSquares[j]->getCenter_y()) < Distance))
			{
				delete arr;
				return true;
			}
		}
	}

	delete arr;
	return false;
}

// 改变焦点块，每次改变焦点块时，我们需要将当前焦点块中的方块加入到已有方块集合中
// 删除焦点块，设置焦点块以及下一个游戏块
void Game::ChangeFocusBlock()
{
	Square** squares = FocusBlock->GetSquares();
	// 将焦点块中的方块加入到已有方块集合中
	for (int i=0; i<4; ++i)
	{
		GameSquares.push_back(squares[i]);
	}
	// 删除焦点块
	delete FocusBlock;
	// 重新设置焦点块
	FocusBlock = new GameBlock(NextBlock->getBlockType(), texture);
	FocusBlock->SetupBlock(BLOCK_START_X, BLOCK_START_Y, texture);
	// 设置下一个游戏块
	delete NextBlock;
	NextBlock = new GameBlock(NEXT_BLOCK_X, NEXT_BLOCK_Y, (BlockType)(rand() % 7), texture);
}

// 计算完成的行数
int Game::CalcCompleteRows()
{
	// 底线
	int bottomLine = GAME_AREA_BOTTOM - SQUARES_MEDIAN;
	// top line
	int topLine = SQUARES_MEDIAN;
	// 每一行的距离
	int rowSize = SQUARES_MEDIAN * 2;
	// 记录每行中方块的个数
	int SquareNums_per_row[21];
	for (int i=0; i<21; ++i)
	{
		SquareNums_per_row[i] = 0;
	}

	int row = 0, completeRows = 0;
	// Check for full lines
	for (int i=0; i<GameSquares.size(); ++i)
	{
		// 获得到当前方块所在的行
		int y = GameSquares[i]->getCenter_y();
		row = (y - topLine) / rowSize;
		SquareNums_per_row[row]++;
	}

	// Erase any full lines
	for (int line=0; line<21; ++line)
	{
		// 如果当前行被方块填满
		if (SquareNums_per_row[line] == SQUARES_PER_ROW)
		{
			completeRows++;
			// 删除掉被方块填满的行中的方块
			for (int i=0; i<GameSquares.size(); ++i)
			{
				if (((GameSquares[i]->getCenter_y() - topLine) / rowSize) == line)
				{
					delete GameSquares[i];
					GameSquares.erase(GameSquares.begin() + i);
					i--;
				}
			}
		}
	}

	// 将已填满行上面的所有方块向下移动
	for (int i=0; i<GameSquares.size(); ++i)
	{
		for (int line=0; line<21; ++line)
		{
			if (SquareNums_per_row[line] == SQUARES_PER_ROW)
			{
				int y = GameSquares[i]->getCenter_y();
				row = (y - topLine) / rowSize;
				if (line > row)
				{
					GameSquares[i]->Move(DOWN);
				}
			}
		}
	}

	return completeRows;
}

// 处理键盘输入，IsUp参数只对向上方向有效
void Game::HandleInput(Direction dir, bool IsUp)
{
	// 处理向上方向键，旋转当前游戏块
	if (IsUp)
	{
		if (!CheckRotationCollisions(FocusBlock))
			FocusBlock->Rotate();
	}
	else
	{
		if (!CheckWallCollisions(FocusBlock, dir) && 
			!CheckEntityCollisions(FocusBlock, dir))
		{
			FocusBlock->Move(dir);
		}
	}
}

Game::~Game(void)
{
	if (FocusBlock)
		delete FocusBlock;
	if (NextBlock)
		delete NextBlock;
	vector<Square*>::const_iterator it = GameSquares.begin();
	for (; it != GameSquares.end(); ++it)
	{
		const Square* del = (*it);
		if (del)
			delete del;
	}
	GameSquares.clear();
}
