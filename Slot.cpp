#include <vector>
#include <algorithm>
#include <format>
#include "DxLib.h"
#include "Slot.h"
#include "GameLoader.h"
#include "Reach_Effect.h"

Slot SLOT;
Number_Management NM;
Reach_Text RT;

void Slot::Read()
{
	
	Pace_Speed = 1.0f;
	order[0] = 0;	
	order[1] = order[1] / Pace_Speed;
	order[2] = order[2] / Pace_Speed;

	Reel_GrobalTime_Increment = 1.0f*Pace_Speed;
	Constant_Count_Increment = 1.0f* Pace_Speed;
	Decel_Count_Increment = 1.0f* Pace_Speed;


	Symbol_IntervalTime = 20;
	Symbol_ScaleIncrement = 0.02f;

	Reel_Accel_Constant = 0.0010f;
	Symbol_Center_X.resize(3);
	Symbol_Center_Y.resize(3);
	Symbol_Scale.resize(3);
	Symbol_Active.resize(3);
	Reel_State.resize(3);;
	Reel_GrobalTime.resize(3);
	Reel_AlphaValue.resize(3);
	Constant_Count.resize(3);
	Decel_Count.resize(3);

	Decel_State.resize(3);
	Current_Number.resize(3);
	

	//座標配置
	for (int i = 0; i < REEL_NUMBER; i++)
	{
		Symbol_Center_X[i] = 120 + (i * 200);
		Symbol_Center_Y[i] = 240;
		Reel_AlphaValue[i] = 255;
		Symbol_Scale[i].resize(9);
		Reel_GrobalTime[i] = 0;
		Reel_State[i] = STATE::STOPPED;

		Decel_Count[i] = 0;
		
		Current_Number[i] = GetRand(8);

		for (int j = 0; j < SYMBOL_NUMBER; j++)
		{
			Symbol_Scale[i][j] = 0;
			if (Current_Number[i] == j)
				Symbol_Scale[i][j] = 0.40f;
		}
	}
	
	Accel_inTime = 20;
	Constant_inTime = 120;
	//Decel_inTime = (Constant_inTime + Symbol_IntervalTime * SYMBOL_NUMBER + 1)*2;
	Decel_inTime = 300;
	
	offset_time_swi = 10;
	Reset_inTime = (Decel_inTime + 100 * order[1]) +(1 + offset_time_swi * 3)+50;//(swi=3)
	//              (最後のリールがDecelに入るタイミング)+(最後のリールがDecelに入ってから完了する所要時間)
	Reel_Alpha = 5;
	white_Alpha = 0;

}

void Number_Management::Read()
{
	
	
	Number_Hit.resize(3);
	for (int i = 0; i < REEL_NUMBER; i++)
	{
		Number_Hit[i] = GetRand(8);
	}

	//Number_Hit[2] = 0;
	
	Current_ReachType = REACH_TYPE::NONE;
	
	
	


	//リーチ判定
	Number_Hit[0] = Number_Hit[2];//db

	if (Number_Hit[0] == Number_Hit[2])
	{
		is_Reach = true;
		Current_ReachType = static_cast<REACH_TYPE>(GetRand(REACHTYPE_NUMBER-1)+1);

	}
	else
	{
		Current_ReachType = Number_Management::REACH_TYPE::NONE;
		is_Reach = false;
	}

	Current_ReachType = REACH_TYPE::ACCEL_WHITEOUT;//db
	Stock = 0;

	
	SLOT.Pace_Speed = 1 + Stock / 10;
	
}

void Reach_Text::Read()
{
	t = 0;
	swi = false;
	for (int i = 0; i < 50; i++)
	{
		
		std::string filepath = std::format("REACH_TEXT/{:04d}.png", i + 1);
		image[i] = LoadGraph(filepath.c_str());


	}
}

void Number_Management::Out()
{
	for (int i = 0; i < REEL_NUMBER; i++)
	{
		NM.Number_Hit[i] = GetRand(8);
	}
	if (Number_Hit[0] == Number_Hit[2])
	{
		is_Reach = true;
		Current_ReachType = static_cast<REACH_TYPE>(GetRand(REACHTYPE_NUMBER - 1) + 1);
	}
	else
	{
		is_Reach = false;
		Current_ReachType = Number_Management::REACH_TYPE::NONE;

	}
	
	NM.Stock--;
	NM.Stock = std::max<int>(0, NM.Stock);
	SLOT.Pace_Speed = (1 + (Stock*2) / 10);

}


void Slot::Out()
{
	
	clsDx();
	//printfDx("Stock=%f\n", NM.Stock);
	//printfDx("t= %f\n", RT.t);
	//printfDx("order[1]= %f\n", order[1]);

	//printfDx("Reel_GrobalTime[0]= %f\n", Reel_GrobalTime[0]);
	//printfDx("Reel_GrobalTime[1]= %f\n", Reel_GrobalTime[1]);
	//printfDx("Reel_GrobalTime[2]= %f\n", Reel_GrobalTime[2]);

	//printfDx("Reset_inTime= %d\n", Reset_inTime);
	//printfDx("Decel_inTime= %f\n", Decel_inTime+100*order[1]);
	//printfDx("= %d\n", Decel_inTime + 100 * order[0] + 1 + offset_time_swi * 2);
	//printfDx("> %d\n", SLOT.Decel_inTime);
	//printfDx("Reel_State[0]= %d\n", static_cast<int> (Reel_State[0]));
	//printfDx("Reel_State[1]= %d\n", static_cast<int>(Reel_State[1]));
//	printfDx("Current_ReachType=%d\n", static_cast<int>(NM.Current_ReachType));
	//printfDx("SLOT.Reel_AlphaValue[0]= %d\n", SLOT.Reel_AlphaValue[0]);
	//printfDx("SLOT.Constant_Count[1]= %f\n", SLOT.Constant_Count[1]);
	//printfDx("Decel_State[0]= %d\n", SLOT.Decel_State[0]);
	//printfDx("Constant_Count_Increment=%f\n", Constant_Count_Increment);

	//for (int j = 0; j < SYMBOL_NUMBER; j++)
	//{
	//printfDx("Symbol_Scale= %f\n", Symbol_Scale[0][0]);
	//}
	//printfDx("Number_Hit[0]= %d\n", NM.Number_Hit[0]+1);
	//printfDx("Number_Hit[1]= %d\n", NM.Number_Hit[1]+1);
	//printfDx("Number_Hit[2]= %d\n", NM.Number_Hit[2]+1);
	//printfDx("Pace_Speed= %f\n", Pace_Speed);
	//for (int i = 0; i < 3; i++)
	//{
		//printfDx("Current_Number= %d\n", Current_Number[1]);

	//}

	
	

	for (int i = 0; i < 3; i++)
	{
		Reel_GrobalTime[i]+=Pace_Speed;
		
		if (Reel_GrobalTime[i] > Reset_inTime+order[1]+100&&
			Reel_State[1]!=STATE::CONSTANT)
		{
			Reel_State[i] = STATE::RESET;
		}
		else if (Reel_GrobalTime[i] > Decel_inTime + 100 * order[1] &&
				NM.is_Reach == true && 
				i == 1 && 
				order[1] < 4.0f && 
				Reel_State[i] == STATE::CONSTANT)
		{
			Reel_State[i] = STATE::REACH;

		}
		else if (Reel_GrobalTime[i] > Decel_inTime+100*order[i]
			&& Current_Number[i] == NM.Number_Hit[i]&&order[1]<20.0f)
		{
			Reel_State[i] = STATE::DECEL;
		}
		else if (Reel_GrobalTime[i] > Constant_inTime&&
			Reel_GrobalTime[i] <= Decel_inTime + 100 * order[i]
			&&Reel_State[i]==STATE::ACCEL)
		{
			if (i == 0) PlaySoundMem(SOUND.Field, DX_PLAYTYPE_BACK);
			Reel_State[i] = STATE::CONSTANT;
		}
		else if (Reel_GrobalTime[i] > Accel_inTime&&
			Reel_GrobalTime[i]<=Constant_inTime&&
			Reel_State[i]==STATE::STOPPED)
		{

			Reel_State[i] = STATE::ACCEL;
			
		}

		

		switch (Reel_State[i])
		{
		case STATE::STOPPED:
			
			break;
		case STATE::ACCEL:
			
			Accel_Out(i);
			break;
		case STATE::CONSTANT:
			Constant_Out(i);
			break;
		case STATE::DECEL:
			Decel_Out(i);
			break;
		case STATE::RESET:
			Reset_Out(i);
			break;
		case STATE::REACH:
			Reach_Out(i);
			break;

		}


	}

}

void Slot::Stopped_Out(int i)
{
	
		for (int j = 0; j < SYMBOL_NUMBER; j++)
		{
			;
		}
	
}


void Slot::Accel_Out(int i)
{
	
	
		for (int j = 0; j < SYMBOL_NUMBER; j++)
		{
			
		}
	

}

void Slot::Constant_Out(int i)
{
	// Slot::Out() の中に追加
	
	
	if (NM.Current_ReachType == Number_Management::REACH_TYPE::ACCEL_WHITEOUT)
	{
		// 中央リールがリーチ時間を過ぎたあたりから加速＆ホワイトアウト開始
		if (Reel_GrobalTime[1] > Decel_inTime + 100 * 4.0f &&
			Reel_GrobalTime[1] < Decel_inTime + 100 * 6.0f)
		{
			Reel_Alpha = 255;
			Constant_Count_Increment = 0.0020f * Pace_Speed;
			Symbol_ScaleIncrement = 0.0020f * Pace_Speed;
		}

		// ① 特定の絵柄になった瞬間に「ホワイトアウト開始フラグ」だけを立てる
		if (Reel_GrobalTime[1] > Decel_inTime + 100 * 6.0f &&
			Current_Number[1] == (NM.Number_Hit[1] + 1) % SYMBOL_NUMBER)
		{
			is_white = true; // トリガーを引く
		}

		// ② フラグが立っていたら、現在の絵柄(Current_Number)に関係なく毎フレーム実行する
		if (is_white == true)
		{
			// まだ白くなり始め(0)の時だけ音を鳴らす
			if (white_Alpha == 0) PlaySoundMem(SOUND.whiteout, DX_PLAYTYPE_BACK);

			white_Alpha += 10;
			white_Alpha = std::min<int>(white_Alpha, 255); // 255でストップ

			// 画面が白くなりきったらバトル演出を毎フレーム進める
			if (white_Alpha > 253)
			{
				//white_Alpha = 0;
				
			}

			Constant_Count_Increment += 0.01f;
			Symbol_ScaleIncrement += 0.01f;
			StopSoundMem(SOUND.Field);
		}
	}
	else if ((NM.Current_ReachType == Number_Management::REACH_TYPE::LONGREACH_NOWHITE))
	{
		if (Reel_GrobalTime[1] > Decel_inTime + 100 * 4.0f &&
			Reel_GrobalTime[1] < Decel_inTime + 100 * 6.0f)
		{
			Reel_Alpha = 255;
			Constant_Count_Increment = 0.0020f * Pace_Speed;
			Symbol_ScaleIncrement = 0.0020f * Pace_Speed;
		}
		if (Reel_GrobalTime[1] > Decel_inTime + 100 * 6.0f &&
			Current_Number[1] ==(NM.Number_Hit[0]+1) % SYMBOL_NUMBER)
		{
			
			StopSoundMem(SOUND.Field);
			order[1] = 4.0f;
			Reel_State[1] = STATE::DECEL;
			Reset_inTime = Reel_GrobalTime[1] + (1 + offset_time_swi * 3) + 50;
			NM.Number_Hit[1] = Current_Number[1];
		}

	}
	
	Constant_Count[i]+=Constant_Count_Increment;
	
	if (Constant_Count[i] > (SYMBOL_NUMBER)*Symbol_IntervalTime)
	{
		Constant_Count[i] = 0;
	}
	
	if (Decel_State[2] < 1) Reel_AlphaValue[i] -= 10;
	else Reel_AlphaValue[i] = Reel_Alpha;
	
	
	if (Reel_AlphaValue[i] < 0)
	{
		if (NM.is_Reach == true&& Reel_GrobalTime[2] > Decel_inTime + 100 * order[1]-100)
		{
			Reel_AlphaValue[1] = 255;

		}
		else if (NM.is_Reach == false)
		{
			Reel_AlphaValue[i] = 5;
		}

	}
	
	

		for (int j = 0; j < SYMBOL_NUMBER; j++)
		{
			if (Symbol_Scale[i][j]>=0.65)
			{
				if (j < SYMBOL_NUMBER - 1)
				{
					Symbol_Scale[i][j+1] = 0.5f;
					Symbol_Scale[i][j] = 0;
					
					Current_Number[i] = j+1;

				}
				else if (j == SYMBOL_NUMBER - 1)
				{
					Symbol_Scale[i][0] = 0.5f;
					Symbol_Scale[i][SYMBOL_NUMBER - 1] = 0;
					Current_Number[i] = 0;
				}

			}
			
			if (Current_Number[i] == j&& Symbol_Scale[i][j] < 0.65)
			{
				Symbol_Scale[i][j] += Symbol_ScaleIncrement;

			}
				
			//else if (Constant_Count[i] == Symbol_IntervalTime * (j + 1))
			//{
			//	Symbol_Scale[i][j] = 0;
			//}
			
		}
}

void Slot::Decel_Out(int i)
{
	Decel_Count[i] += Decel_Count_Increment;
	for (int j = 0; j < SYMBOL_NUMBER; j++)
	{
		if (Decel_Count[i] > 1&& 
			NM.Number_Hit[i]!=j)//あたり以外隠す
		{
			Symbol_Scale[i][j] = 0;
		}
		
		for (int swi = 0; swi < 4; swi++)
		{
			if (Decel_Count[i] == 10 + offset_time_swi * 3)
			{
				PlaySoundMem(SOUND.Reelfinish, DX_PLAYTYPE_BACK);

			}
			
			if (Decel_Count[i] > 10 + offset_time_swi * swi)
			{
				Decel_State[i] = swi;
			}
			//swi 0:0.5倍スケール
			//swi 1:縮小
			//swi 2:確定
		}
		
		
		if (NM.Number_Hit[i] == j)//j番を動かす
		{
			switch (Decel_State[i])
			{
				case 0:
					//Symbol_Scale[i][j] = 0.5;
					Reel_AlphaValue[i] = 5;
					break;
				case 1:
					Symbol_Scale[i][j] -= 0.05f*Pace_Speed;
					Symbol_Scale[i][j] = std::max<float>(Symbol_Scale[i][j], 0.3);
					Reel_AlphaValue[i] += 15;
					break;
				case 2:
					Symbol_Scale[i][j] += 0.01f*Pace_Speed;
					Symbol_Scale[i][j] = std::min<float>(Symbol_Scale[i][j], 0.4f);
					Reel_AlphaValue[i] += 15;
					break;
				case 3:
					Symbol_Scale[i][j] = 0.4f;
					Reel_AlphaValue[i] = 255;
					if (i == 1) StopSoundMem(SOUND.Field);
					break;
			}
		}
	}
	
}

void Slot::Reset_Out(int i)
{
	
	Reel_GrobalTime_Increment = 1.0f*Pace_Speed;
	Constant_Count_Increment = 1.0f*Pace_Speed;
	Symbol_ScaleIncrement = 0.02f*Pace_Speed;
	Reel_GrobalTime[i] = 0;
	Reel_State[i] = STATE::STOPPED;
	Decel_State[i] = 0;          
	Reel_AlphaValue[i] = 255;
	Constant_Count[i] = (Symbol_IntervalTime * (NM.Number_Hit[i]+1));
	Decel_Count[i] = 0;
	for (int j = 0; j < SYMBOL_NUMBER; j++) 
	{
		Symbol_Scale[i][j] = 0;
		if (Current_Number[i]==j)
			Symbol_Scale[i][j] = 0.40f;
	}
	order[0] = 0.0f;
	order[1] = 2.5f;
	order[2] = 1.0f;


	Reset_inTime = (Decel_inTime + 100 * order[1]) + (1 + offset_time_swi * 3) + 50;

	if (i == 1)
	{
		StopSoundMem(SOUND.Reachstart);
		NM.Out();
	}

	RT.swi = false;
}

void Slot::Reach_Out(int i)
{
	if (i == 1)
	{
		StopSoundMem(SOUND.Field);
		PlaySoundMem(SOUND.Reachstart, 1);
		PlaySoundMem(SOUND.Reach_Voice[0], 1);

		RT.swi = true;
		

		

	}
		
	if (Number_Management::REACH_TYPE::ACCEL_WHITEOUT!= NM.Current_ReachType) SLOT.order[1] = 4.0f;
	

	//リーチリール演出選出
	

	switch (NM.Current_ReachType)
	{
	case Number_Management::REACH_TYPE::NORMAL_MISS:
		break;
	case Number_Management::REACH_TYPE::CLOSE_MISS:
		NM.Number_Hit[1] = (NM.Number_Hit[0] + 1) % SYMBOL_NUMBER;
		break;
	case Number_Management::REACH_TYPE::ACCEL_WHITEOUT:
		SLOT.order[1] = 20.0f;
		break;
	case Number_Management::REACH_TYPE::LONGREACH_NOWHITE:
		SLOT.order[1] = 20.0f;
		//NM.Number_Hit[1] = (NM.Number_Hit[0]+1) % 9;
		break;

	}

	order[1] = order[1] / Pace_Speed;
	Reset_inTime = (Decel_inTime + 100 * order[1]) + (1 + offset_time_swi * 3) + 50;
	Reel_State[i] = STATE::CONSTANT;
}

void Reach_Text::Out()
{
	if (swi)
	{
		t += 0.50f;
		if (t == 20)
		{
			PlaySoundMem(SOUND.ReachPut, DX_PLAYTYPE_BACK);
		}
		else if (t==22)
		{

			PlaySoundMem(SOUND.ReachBlow,DX_PLAYTYPE_BACK);
		}
	}
	else 
	{
		t = 0; 
		swi = false;
	}
}

void Slot::Draw()
{
		
	for (int i = 0; i < REEL_NUMBER; i++)
	{
		
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, Reel_AlphaValue[i]);
		
		

		for (int j = 0; j < SYMBOL_NUMBER; j++)
			{
			
			DrawRotaGraph
			(
				Symbol_Center_X[i],
				Symbol_Center_Y[i],
				Symbol_Scale[i][j],
				0,
				GL.Symbol_GraphHandle[j],
				true
			);

			
			}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	//whiteout描画処理

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, white_Alpha);
	DrawGraph(0, 0, BL.White_Back, 0);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

}

void Reach_Text::Draw()
{
	
	int tt = t;
	if (swi) DrawGraph(0, 0, image[tt], 1);
	
}




