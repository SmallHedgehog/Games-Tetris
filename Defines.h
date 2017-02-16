
/*
define const values
*/

// 定义窗口常量
#define WINDOW_CAPTION		"Tetris"		// 窗口标题
#define WINDOW_WIDTH		892				// 窗口宽度
#define WINDOW_HEIGHT		714				// 窗口高度

// 定义游戏区域
#define GAME_AREA_LEFT		0				// 游戏区域左边界
#define GAME_AREA_RIGHT		612				// 游戏区域右边界
#define GAME_AREA_BOTTOM	714				// 游戏区域下边界

// 定义游戏关卡属性值
#define GAME_NUM_LEVELS		5				// 游戏总共有5个关卡
#define SCORE_PRE_LINE		125				// 玩家消除一条线时获得的分数
#define SCORE_PRE_LEVEL		1300			// 提升一级需要的分数

// 定义游戏块相关的属性
#define INITIAL_SPEED		60				// 方块块向下移动的间隔
#define SPEED_CHANGE		10				// 进入下一关时，游戏块下落的速度加快

// 游戏块到达游戏区域底部时，给予玩家一个短暂的时间，以向左或向右滑动
#define SLIDE_TIME			15

#define SQUARES_PER_ROW		18				// 一行有18个方块
#define SQUARES_PER_COL		21				// 一列有21个方块
#define SQUARES_MEDIAN		17				// 从正方形的中心到其边的距离

// 游戏块（焦点块）的起始位置
#define BLOCK_START_X		300
#define BLOCK_START_Y		72
// 下一个游戏块的位置
#define NEXT_BLOCK_X		(612+155)
#define NEXT_BLOCK_Y		140

// 定义得分、级别、每关所需得分、当前游戏块下落的速度等位置
#define SCORE_POSITION_X	(612+60)		// 绘制得分位置
#define SCORE_POSITION_Y	(65+180)
#define LEVEL_POSITION_X	(612+60)		// 游戏级别
#define LEVEL_POSITION_Y	300
#define SCORE_PER_LEVEL_X	(612+60)		// 每关所需得分
#define SCORE_PER_LEVEL_Y	350
#define SPEED_X				(612+60)		// 当前游戏块下落的速度绘制位置
#define SPEED_Y				400

// 背景图片绘制位置
#define BG1_POSITION_x		0				// 背景图片1
#define BG1_POSITION_y		0
#define BG2_POSITION_x		612				// 背景图片2
#define BG2_POSITION_y		0
#define BG3_POSITION_x		623				// 背景图片2
#define BG3_POSITION_y		480