#pragma once

//このヘッダーはリーチ時の数字同士のバトル演出


class Reach_Effect1
{
public:
	//0=はずれ番号,1=あたり番号,
	
	enum STATE
	{
		Expansion,
		Reduction,
		Stop,
		Repulsion,
		Suction,
		Conflict,
		ConflictWin,
		ConflictLose,
		Result,
		Lose,
		Finish,
	};

	int Gh0;//Gh=グラフハンドル
	int Gh1;

	int X0;
	int Y0;
	
	int X1;
	int Y1;

	double X_increment;

	double aX0; //a=X座標加速度
	double aX1;

	double S0;//S=拡大率
	double S1;
	double S_increment;

	int R0;//R=回転率
	int R1;

	int Sta;//Sta=状態

	int Time;//Time=経過時間
	int StateTimer;//StateTimer=目標時間
	
	int Conflict_Count;

	bool is_white;
	int white_alpha;

	void Read();
	void Out();
	void Draw();

};

extern Reach_Effect1 Reach_EF1;

