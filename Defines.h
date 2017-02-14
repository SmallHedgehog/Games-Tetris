
/*
define const values
*/

// 定义窗口常量
#define WINDOW_CAPTION		"Tetris"		// 窗口标题
#define WINDOW_WIDTH		450				// 窗口宽度
#define WINDOW_HEIGHT		400				// 窗口高度

// 定义游戏区域
#define GAME_AREA_LEFT		53				// 游戏区域左边界
#define GAME_AREA_RIGHT		251				// 游戏区域右边界
#define GAME_AREA_BOTTOM	298				// 游戏区域下边界

// 定义游戏关卡属性值
#define GAME_NUM_LEVELS		5				// 游戏总共有5个关卡
#define SCORE_PRE_LINE		125				// 玩家消除一条线时获得的分数
#define SCORE_PRE_LEVEL		1300			// 提升一级需要的分数

// 定义游戏块相关的属性
#define INITIAL_SPEED		60				// 游戏块向下移动的初始间隔

// 游戏块到达游戏区域底部时，给予玩家一个短暂的时间，以向左或向右滑动
#define SLIDE_TIME			15

#define SQUARES_PER_ROW		10				// 一行有10个游戏块
#define SQUARES_MEDIAN		10				// 从正方形的中心到其边的距离

// 游戏块的起始位置
#define BLOCK_START_X		151
#define BLOCK_START_Y		59