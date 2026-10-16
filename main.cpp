//db=デバッグ用の処理


#include "DxLib.h"
#include "GameLoader.h"
#include "Slot.h"
#include "Reach_Effect.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

    //SetFullScreenResolutionMode(DX_FSRESOLUTIONMODE_MAXIMUM);
    SetWindowSize(640, 480);
    ChangeWindowMode(1);
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    SRand(GetRand(100));
    
    
    GL.Read();
	BL.Read();
    SLOT.Read();
    NM.Read();
	SOUND.Read();
    BT.Read();
    RT.Read();
    Reach_EF1.Read();

    enum class GameScene {
        NORMAL, // 通常の回転中(リーチ時も含める)
        REACH,  // リーチ演出中(数字のバトルなど)
    };

    GameScene Current_GameScene = GameScene::NORMAL;


    while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
    {
        ClearDrawScreen();
        
        switch (Current_GameScene) 
        {
        case GameScene::NORMAL:
            BT.Out();
            BL.Out();
            SLOT.Out();
            RT.Out();
            SLOT.Draw();
            RT.Draw();
            if (SLOT.is_white == true && SLOT.white_Alpha > 253) 
            {
                Current_GameScene = GameScene::REACH;
            }
            break;
        case GameScene::REACH:
            Reach_EF1.Out();
            if (Reach_EF1.Sta == Reach_EF1.STATE::Finish &&
                Reach_EF1.Time > 254)
            {
                Reach_EF1.Sta = 0;
                SLOT.Reel_State[0] = Slot::STATE::RESET;
                SLOT.Reel_State[1] = Slot::STATE::RESET;
                SLOT.Reel_State[2] = Slot::STATE::RESET;

                for (int i = 0; i < SYMBOL_NUMBER; i++)
                {
                    if (NM.Number_Hit[0] == i)
                    {
                        SLOT.Current_Number[1] = (i + 1) % SYMBOL_NUMBER;
                        //GL.Symbol_GraphHandle[1] = (i + 1) % SYMBOL_NUMBER;

                    }

                }

                Current_GameScene = GameScene::NORMAL; // シーンを通常に戻す
                SLOT.is_white = false;                 // スロット側の白フラグをオフ
                SLOT.white_Alpha = 0;// スロット側の白の濃さをリセット
                Reach_EF1.is_white = false;
            }
            break;
        }

        //保留
        if (BT.is_RMOUSE == true&&NM.Stock<5)
        {
            NM.Stock++;
        }

        ScreenFlip();
        
        if (CheckHitKey(KEY_INPUT_SPACE))//db
        {
            WaitTimer(60);
        }
        else WaitTimer(12);
    }


    DxLib_End();

    return 0;
}