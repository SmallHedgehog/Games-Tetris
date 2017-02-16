#pragma once

/*
定义Window类主要负责窗口的创建、显示与更新，加载资源
*/

#include <SDL_image.h>
#include <iostream>
#include "Game.h"

using namespace std;

class Window
{
public:
	Window(void);
	~Window(void);

public:
	void Start();				// 进入消息循环
	void Refresh();				// refresh到屏幕上
	void Update();				// 更新图像信息
	void LoadResouceFile();		// 加载资源文件
	SDL_Texture* Load_image(std::string FilePath);	// 加载图像
	void Init();				// 初始化游戏对象
	void ResetGame();			// 重置游戏
	SDL_Texture* Draw_text(std::string message);	// 绘制文字

private:
	SDL_Window* win;			// 窗口
	SDL_Renderer* renderer;		// 渲染器
	SDL_Texture* bg1;			// 背景纹理
	SDL_Texture* bg2;
	SDL_Texture* bg3;
	SDL_Texture* texture;		// 方块纹理
	TTF_Font* Font;				// 字体

	Game* game;
};

