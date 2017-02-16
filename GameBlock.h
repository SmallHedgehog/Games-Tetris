#pragma once

// 定义了游戏中的游戏块，由四个square组成
// 我们在Enums.h文件中定义了七种游戏块类型，我们需要根据指定的游戏块类型来
// 生成我们的游戏块类型形状

#include "Square.h"

class GameBlock
{
public:
	GameBlock(void);
	GameBlock(int center_x, int center_y, BlockType type, SDL_Texture* texture);
	GameBlock(BlockType type, SDL_Texture* texture);
	~GameBlock(void);

public:
	// 根据游戏块类型来构造我们的游戏块
	void SetupBlock(int x, int y, SDL_Texture* texture);
	// 绘制游戏块
	void DrawSquares(SDL_Renderer* renderer);
	// 移动游戏块
	void Move(Direction dir);
	// 旋转方块
	void Rotate();
	// 获取旋转方块后的位置
	int* GetRotatedPositions();
	BlockType getBlockType() const;

	Square** GetSquares();

private:
	// 游戏块中心位置
	int center_x;			// 中心x坐标
	int center_y;			// 中心y坐标

	BlockType type;			// 游戏块类型
	SDL_Texture* texture;	// 构成游戏块形状的小正方形纹理
	Square* squares[4];		// 组成游戏块的4个指针数组
};

