#include "DxLib.h"
#include "GameLoader.h"
#include <vector>
#include <cmath>

GameLoader GL;
Button BT;
BackGround BL;
Sound SOUND;

void GameLoader::Read()
{
	

		for (int j = 0; j < SYMBOL_NUMBER; j++)
		{
			Symbol_GraphHandle.resize(9);//行生成

			GraphName = std::to_string(j + 1) + ".png";

			Symbol_GraphHandle[j] = LoadGraph(GraphName.c_str());
			if (LoadGraph(GraphName.c_str()) == -1) MessageBox(NULL, "No Image", "Error", MB_ICONERROR), exit(0);

		}
	
		//背景
		
}

void BackGround::Read()
{
	BackGroundHandle.resize(BACKGROUND_NUMBER);
	x = 0;
	a = 100;
	speed = 0.005f;
	time = 0;
	
	for (int i = 0; i < BACKGROUND_NUMBER; i++)
	{
		GraphName = "background" + std::to_string(i + 1) + ".png";
		BackGroundHandle[i] = LoadGraph(GraphName.c_str());
		if (LoadGraph(GraphName.c_str()) == -1) MessageBox(NULL, "No Image", "Error", MB_ICONERROR), exit(0);
	}
	
	White_Back=LoadGraph("white.png");
}

void BackGround::Out()
{
	
	//基準値 + sin(時間 * スピード) * 振幅幅;
	time += 1;;
	x = -150 + sin(time * speed) * a;
	
	
		DrawGraph(x, 0, BackGroundHandle[1], true);
		DrawGraph(x, 0, BackGroundHandle[0], true);

}

void Sound::Read()
{
	for (int i=0;i<REACH_VOICE_NUMBER;i++)
	{
		//Reach_Voice[i] = LoadSoundMem("act_rich.mp3");
	
	}
	Field = LoadSoundMem("fieldbgm1.mp3");
	//Field = LoadSoundMem("Evakakunouko.mp3");

	Reelfinish = LoadSoundMem("reelok.mp3");

	//Reachstart=LoadSoundMem("yashima.mp3");
	Reachstart = LoadSoundMem("Riichi.mp3");
	whiteout = LoadSoundMem("horror_9.mp3");

	ReachPut = LoadSoundMem("wadaiko.mp3");

	ReachBlow = LoadSoundMem("shakiin2.mp3");

}

void Button::Read()
{
	is_RMOUSE = false;
	RMOUSE_Counter = 0;

}

void Button::Out()
{
	if (((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0))
	{
		RMOUSE_Counter++;
		if (RMOUSE_Counter == 1)
		{
			is_RMOUSE = true;
		}
		else is_RMOUSE = false;
	}
	else if ((GetMouseInput() & MOUSE_INPUT_RIGHT) == 0) RMOUSE_Counter = 0;
}


