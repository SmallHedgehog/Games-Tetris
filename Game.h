#pragma once

// 游戏控制类Game
// 存储游戏中的所有游戏块、碰撞检测等逻辑

#include <time.h>
#include <math.h>
#include <vector>
#include <SDL_ttf.h>
#include "GameBlock.h"

using namespace std;

class Game
{
public:
	Game(SDL_Renderer* renderer, SDL_Texture* texture, TTF_Font* Font);
	~Game(void);

public:
	// win the game
	// void Win();
	// fail the game
	// void Fail();
	// exit the game
	// void Exit();

public:
	// 初始化游戏
	void Init();
	// 当前游戏块自动向下移动
	void GameBlock_selfMove();
	// 绘制方法
	void Draw();
	void Draw_text(std::string message, int x, int y);
	// 改变焦点块
	void ChangeFocusBlock();
	// 计算完成的行数
	int CalcCompleteRows();
	// 处理键盘输入
	void HandleInput(Direction dir, bool IsUp);

// 碰撞检测逻辑
public:
	// 检测游戏块是否与Wall碰撞
	bool CheckWallCollisions(GameBlock* FocusGameBlock, Direction dir);
	bool CheckWallCollisions(Square* square, Direction dir);
	// 检测游戏块是否与其它游戏块碰撞
	bool CheckEntityCollisions(GameBlock* FocusGameBlock, Direction dir);
	bool CheckEntityCollisions(Square* square, Direction dir);
	// 处理游戏块不移动时的逻辑
	void HandleStaticBlockCollision();
	// 检测游戏块旋转后是否发生碰撞
	bool CheckRotationCollisions(GameBlock* block);

private:
	GameBlock* FocusBlock;				// 游戏玩家正在控制的块
	GameBlock* NextBlock;				// 下一个游戏块
	vector<Square*> GameSquares;		// 存储游戏中所有的方块

	// 渲染器
	SDL_Renderer* renderer;
	// 方块纹理
	SDL_Texture* texture;
	// 字体
	TTF_Font* Font;

	int Score;							// 玩家当前得分
	int Level;							// 当前游戏等级
	int FocusBlockSpeed;				// 玩家正在控制的块的速度
};

