#pragma once

#include <vector>
#include <string>

constexpr int REEL_COUNT = 3;
constexpr int SYMBOL_HEIGHT = 312;
constexpr int SYMBOL_WIDTH = 363;
constexpr int REEL_NUMBER = 3;
constexpr int SYMBOL_NUMBER = 9;
constexpr int REEL_MARGIN = 30;
constexpr int REEL_GAP = 50;
constexpr int SYMBOL_GAP = 20;
constexpr int REEL_INITIALPOSITION_X = 0;
constexpr int REEL_INITIALPOSITION_Y = -600;
constexpr int BACKGROUND_NUMBER = 2;
constexpr int REACHTYPE_NUMBER = 4;
constexpr int REACH_VOICE_NUMBER = 1;









class GameLoader
{
public:
	
	
	std::vector<int> Symbol_GraphHandle;//9個の絵柄配列
	std::string GraphName;
	

	void Read();
};

extern GameLoader GL;

class BackGround
{
public:
	std::string GraphName;

	std::vector<int> BackGroundHandle;//3個の背景配列
	int White_Back;
	float time;
	float speed;
	int a;
	int x;

	void Read();
	void Out();

};

extern BackGround BL;

class Sound
{
public:
	void Read();
	int Field;
	int Reelfinish;
	int Reachstart;
	int whiteout;
	int ReachPut;
	int ReachBlow;
	int Reach_Voice[REACH_VOICE_NUMBER];
	

};

extern Sound SOUND;

class Button
{
public:
	bool is_RMOUSE;
	int  RMOUSE_Counter;

	void Read();
	void Out();

};

extern Button BT;





