#pragma once
#include <vector>

class Slot
{
	public:
		
		enum class STATE
		{
			STOPPED,
			ACCEL,
			CONSTANT,
			DECEL,
			RESET,
			REACH

		};

		
		std::vector <int> Symbol_Center_X;
		std::vector <int> Symbol_Center_Y;
		std::vector <std::vector<double>> Symbol_Scale;
		std::vector <STATE> Reel_State;
		std::vector <bool> Symbol_Active;
		std::vector <double> Reel_GrobalTime;
		std::vector <int> Reel_AlphaValue;
		std::vector<double>  Constant_Count;
		std::vector<double>  Decel_Count;

		std::vector<int> Decel_State;
		std::vector <int> Current_Number;

		
		double Reel_GrobalTime_Increment;
		double Constant_Count_Increment;
		double Decel_Count_Increment;


		double Reel_Accel_Constant;
		double Symbol_ScaleIncrement;

		
		int Symbol_IntervalTime;
		int Accel_inTime;
		int Constant_inTime;
		int Decel_inTime;
		int Reset_inTime;
		int Reel_Alpha;
		int offset_time_swi;
		float order[3] = { 0.0f,2.5f,1.0f };

		double Pace_Speed;

		bool is_white;
		int  white_Alpha;

		
		
		

		void Read();
		void Out();
		
		void Stopped_Out(int i);
		void Accel_Out(int i);
		void Constant_Out(int i);
		void Decel_Out(int i);
		void Reset_Out(int i);
		void Reach_Out(int i);


		void Draw();

};

extern Slot SLOT;

class Number_Management
{
public:
	
	enum class REACH_TYPE {
		NONE,            // リーチなし
		NORMAL_MISS,     // 挙動1: 最終リールはランダムの数字で停止
		CLOSE_MISS,      // 挙動2: 左右の番号の一つ後ろで停止
		ACCEL_WHITEOUT,   // 挙動3: 通り過ぎて加速からのホワイトアウト
		LONGREACH_NOWHITE  //挙動4:ホワイトアウトせず左右の番号の後ろで停止
	};

	std::vector<int> Number_Hit;
	std::vector<int> Reel_Number;
	
	bool is_Reach;

	double Stock;

	

	REACH_TYPE Current_ReachType;

	void Read();
	void Out();
};

extern Number_Management NM;

class Reach_Text
{
public:
	int image[50];
	float t;
	bool swi;

	void Read();
	void Out();
	void Draw();

};

extern Reach_Text RT;
