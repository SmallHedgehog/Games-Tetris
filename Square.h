#pragma once

// Square类表示单个正方形，由四个square组成游戏块
// 在游戏中每消除一行时，上面的块会向下移动，因此定义一个square类来组成我们的游戏块更加合理

#include <SDL.h>
#include "Defines.h"
#include "Enums.h"

class Square
{
public:
	Square(void);
	Square(int center_x, int center_y, SDL_Texture* texture);
	~Square(void);

public:
	// 绘制单个正方形
	void DrawToRenderer(SDL_Renderer* renderer);
	// 处理单个正方形的移动
	void Move(Direction dir);

// 访问和修改属性的方法
public:
	// 访问属性方法
	int getCenter_x() const { return center_x; }
	int getCenter_y() const { return center_y; }
	// 设置属性方法
	void setCenter_x(int center_x) { this->center_x = center_x; }
	void setCenter_y(int center_y) { this->center_y = center_y; }
	void setTexture(SDL_Texture* texture) { this->texture = texture; }

private:
	// 存储单个正方形的中心位置
	int center_x;					// 中心x坐标
	int center_y;					// 中心y坐标
	
	SDL_Texture* texture;			// 存储单个正方形纹理数据
};

