#include "Reach_Effect.h"
#include "Slot.h"
#include "DxLib.h"
#include "GameLoader.h"

Reach_Effect1 Reach_EF1;

void Reach_Effect1::Read()
{
	
	for (int i = 0; i < SYMBOL_NUMBER; i++)
	{
		if (NM.Number_Hit[0] == i)
		{
			Gh0 = (i + 1) % SYMBOL_NUMBER;
			Gh1 = i;
		}

	}
	
	X0 = 400;
	X1 = 200;

	X_increment = 5.0f;

	Y0 = 240;
	Y1 = 240;

	aX0 = 0;
	aX1 = 0;

	S0=0;
	S1=0;
	S_increment = 0.010f;

	R0=0;
	R1=0;

	Sta = 0;
	Time = 0;
	StateTimer = 60;

	Conflict_Count = 0;

	is_white = false;
	white_alpha = 0;

}

void Reach_Effect1::Out()
{
	
		Time++;

		for (int i = 1; i <= 10; i++)
		{
			if (Time > StateTimer &&
				Sta == i - 1)
			{
				Sta = i;
				Time = 0;
			}
		}



		switch (Sta)
		{

		case STATE::Expansion:
			S0+=S_increment;
			S1+= S_increment;
			break;
		case STATE::Reduction:
			S0-= S_increment;
			S1-= S_increment;
			if (S0 < 0.5f) S0 = 0.5f;
			if (S1 < 0.5f) S1 = 0.5f;
			break;
		case STATE::Stop:
			X0 = 400;
			X1 = 200;
			break;
		case STATE::Repulsion:
			X0+=X_increment;
			X1-=X_increment;
			break;
		case STATE::Suction:
			StateTimer = 180;
			X_increment = 10.0f;
			if (X0 - X1 <= 363 * S0)
			{
				StateTimer = 60;
				Sta = STATE::Conflict;
			}
			X0-=X_increment;
			X1+=X_increment;
			break;
		case STATE::Conflict:
			
			//printfDx("c=%d\n", Conflict_Count);
			if (Time % 2 == 0)
			{
				X0 += 20; // キャラ0を右へ
				X1 -= 20; // キャラ1を左へ（お互い押し込む）
			}
			else
			{
				X0 -= 20; // キャラ0を左へ戻す
				X1 += 20; // キャラ1を右へ戻す（反発する）
			}
			break;
		case STATE::ConflictLose:
			
			

			if (Time % 2 == 0)
			{
				X0 += 20; 
				X1 += 20; 
			}
			else
			{
				X0 -= 30; 
				X1 -= 30; 
			}
			break;
		case STATE::ConflictWin:
			if (Conflict_Count == 2)
			{
				is_white = true;
				white_alpha = 255;
				Sta = STATE::Lose;
				Time = 0;
				StateTimer = 300;
				X0 = 320;
				S1 = 0;
				
				
				break;

			}
			if (Time % 2 == 0)
			{
				X0 += 30; 
				X1 += 30; 
			}
			else
			{
				X0 -= 20; 
				X1 -= 20; 
			}
			break;
		case STATE::Result:
			Time = 0;
			Conflict_Count ++;
			Sta = STATE::Stop;
			break;
		case STATE::Lose:
			if (Time>60) white_alpha--;
			break;
		case STATE::Finish:
			is_white = true;
			white_alpha++;
			
			
		

		}

		Reach_EF1.Draw();
		if (is_white)
		{
			
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, white_alpha);
			DrawGraph(0, 0, BL.White_Back, 0);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		}
	
	
	
}

void Reach_Effect1::Draw()
{
	
	DrawRotaGraph(X0, Y0, S0, 0.0f, GL.Symbol_GraphHandle[Gh0], TRUE);
	DrawRotaGraph(X1, Y1, S1, 0.0f, GL.Symbol_GraphHandle[Gh1], TRUE);

}
