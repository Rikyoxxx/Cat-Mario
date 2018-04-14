/*
 * mygame.cpp: ����������Ϸ������class��implementation
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2002-03-04 V3.1
 *          Add codes to demostrate the use of CMovingBitmap::ShowBitmap(CMovingBitmap &).
 *	 2004-03-02 V4.0
 *      1. Add CGameStateInit, CGameStateRun, and CGameStateOver to
 *         demonstrate the use of states.
 *      2. Demo the use of CInteger in CGameStateRun.
 *   2005-09-13
 *      Rewrite the codes for CBall and CEraser.
 *   2005-09-20 V4.2Beta1.
 *   2005-09-29 V4.2Beta2.
 *      1. Add codes to display IDC_GAMECURSOR in GameStateRun.
 *   2006-02-08 V4.2
 *      1. Revise sample screens to display in English only.
 *      2. Add code in CGameStateInit to demo the use of PostQuitMessage().
 *      3. Rename OnInitialUpdate() -> OnInit().
 *      4. Fix the bug that OnBeginState() of GameStateInit is not called.
 *      5. Replace AUDIO_CANYON as AUDIO_NTUT.
 *      6. Add help bitmap to CGameStateRun.
 *   2006-09-09 V4.3
 *      1. Rename Move() and Show() as OnMove and OnShow() to emphasize that they are
 *         event driven.
 *   2006-12-30
 *      1. Bug fix: fix a memory leak problem by replacing PostQuitMessage(0) as
 *         PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0).
 *   2008-02-15 V4.4
 *      1. Add namespace game_framework.
 *      2. Replace the demonstration of animation as a new bouncing ball.
 *      3. Use ShowInitProgress(percent) to display loading progress.
 *   2010-03-23 V4.6
 *      1. Demo MP3 support: use lake.mp3 to replace lake.wav.
*/

#include "stdafx.h"
#include "Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "audio.h"
#include "gamelib.h"
#include "mygame.h"

namespace game_framework
{
/////////////////////////////////////////////////////////////////////////////
// ���classΪ��Ϸ����Ϸ��ͷ�������
/////////////////////////////////////////////////////////////////////////////

CGameStateInit::CGameStateInit(CGame* g): CGameState(g)
{
}

void CGameStateInit::OnInit()
{
    //
    // ��ͼ�ܶ�ʱ��OnInit�������е�ͼҪ���ܶ�ʱ�䡣Ϊ��������Ϸ����
    //     �ȵĲ��ͷ�����Ϸ����֡�Loading ...������ʾLoading�Ľ��ȡ�
    //
	CDDraw::BltBackColor(DEFAULT_BG_COLOR);		// �� Back Plain Ϳ��Ԥ�����ɫ
    ShowInitProgress(0);	// һ��ʼ��loading����Ϊ0%
    //
    // ��ʼ��������
    //
    /*logo.LoadBitmap(IDB_BACKGROUND);*/
	block_floor_1_ground.LoadBitmap(IDB_BLOCK_FLOOR_1_GROUND);
	block_floor_2_ground.LoadBitmap(IDB_BLOCK_FLOOR_2_GROUND);
	player.LoadBitmap(IDB_PLAYER_1, RGB(160, 180, 250));
	title.LoadBitmap(IDB_TITLE);
	mountain.LoadBitmap(IDB_MOUNTAIN, RGB(160, 180, 250));
	brush.LoadBitmap(IDB_BRUSH, RGB(160, 180, 250));
    Sleep(300);				// �������Ա㿴������ȣ�ʵ����Ϸ��ɾ����Sleep
    //
    // ��OnInit������ӵ�CGameStaterRun::OnInit()�����Խ��Ȼ�û��100%
    //
}

void CGameStateInit::OnBeginState()
{
}

void CGameStateInit::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_ESC = 27;
    const char KEY_SPACE = ' ';

    if (nChar == KEY_SPACE)
        GotoGameState(GAME_STATE_RUN);						// �л���GAME_STATE_RUN
    else if (nChar == KEY_ESC)								// Demo �ر���Ϸ�ķ���
        PostMessage(AfxGetMainWnd()->m_hWnd, WM_CLOSE,0,0);	// �ر���Ϸ
}

void CGameStateInit::OnLButtonDown(UINT nFlags, CPoint point)
{
    GotoGameState(GAME_STATE_RUN);		// �л���GAME_STATE_RUN
}

void CGameStateInit::OnShow()
{
    //
    // ����logo
    //
    /*logo.SetTopLeft((SIZE_X - logo.Width())/2, SIZE_Y/8);
    logo.ShowBitmap();*/
	//
	// ����floor
	//
	for (int i = 0; i < 17; i++)
	{
		block_floor_1_ground.SetTopLeft(BLOCK_WIDTH_HEIGHT * i, BLOCK_WIDTH_HEIGHT * 13);
		block_floor_1_ground.ShowBitmap();
		block_floor_2_ground.SetTopLeft(BLOCK_WIDTH_HEIGHT * i, BLOCK_WIDTH_HEIGHT * 14);
		block_floor_2_ground.ShowBitmap();
	}
	//
	// ����player
	//
	

	player.SetTopLeft(33* 2, SIZE_Y - BLOCK_WIDTH_HEIGHT * 2 - PLAYER_HEIGHT);
	player.ShowBitmap();
	//
	// ����title
	//
	title.SetTopLeft((SIZE_X - title.Width()) / 2, SIZE_Y / 7);
	title.ShowBitmap();
	//
	// ����brush
	//
	brush.SetTopLeft(BLOCK_WIDTH_HEIGHT * 6 + 5, SIZE_Y - BLOCK_WIDTH_HEIGHT * 2 - 28);
	brush.ShowBitmap();
	//
	// ����mountain
	//
	mountain.SetTopLeft(BLOCK_WIDTH_HEIGHT * 12 + 20, SIZE_Y - BLOCK_WIDTH_HEIGHT * 2 - 74);
	mountain.ShowBitmap();
    //
    // DemoӫĻ���͵�ʹ�ã���������ʱ�뾡������ֱ��ʹ�����ͣ�����CMovingBitmap�ȽϺ�
    //
    CDC* pDC = CDDraw::GetBackCDC();			// ȡ�� Back Plain �� CDC
    CFont f,*fp;
    f.CreatePointFont(160,"Yu Gothic UI");	// ���� font f; 160��ʾ16 point����
    fp=pDC->SelectObject(&f);					// ѡ�� font f
    pDC->SetBkColor(RGB(160,180,250));
    pDC->SetTextColor(RGB(0,0,0));
    pDC->TextOut(170, 240,"Press SPACE Key");
    /*pDC->TextOut(5,395,"Press Ctrl-F to switch in between window mode and full screen mode.");*/

    if (ENABLE_GAME_PAUSE)
        pDC->TextOut(5,425,"Press Ctrl-Q to pause the Game.");

    /*pDC->TextOut(5,455,"Press Alt-F4 or ESC to Quit.");*/
    pDC->SelectObject(fp);						// �ŵ� font f (ǧ��Ҫ©�˷ŵ�)
    CDDraw::ReleaseBackCDC();					// �ŵ� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// ���classΪ��Ϸ�Ľ���״̬(Game Over)
/////////////////////////////////////////////////////////////////////////////

CGameStateOver::CGameStateOver(CGame* g): CGameState(g)
{
}

void CGameStateOver::OnMove()
{
    counter--;

    if (counter < 0)
        GotoGameState(GAME_STATE_RUN);
}

void CGameStateOver::OnBeginState()
{
    counter = 30 * 2; // 5 seconds
	lives--;
}

void CGameStateOver::OnInit()
{
    //
    // ��ͼ�ܶ�ʱ��OnInit�������е�ͼҪ���ܶ�ʱ�䡣Ϊ��������Ϸ����
    //     �ȵĲ��ͷ�����Ϸ����֡�Loading ...������ʾLoading�Ľ��ȡ�
    //
    ShowInitProgress(66);	// �Ӹ�ǰһ��״̬�Ľ��ȣ��˴�������Ϊ66%
    //
    // ��ʼ��������
    //
    Sleep(300);				// �������Ա㿴������ȣ�ʵ����Ϸ��ɾ����Sleep
    //
    // ���ս���Ϊ100%
    //
    ShowInitProgress(100);
}

void CGameStateOver::OnShow()
{
	CDDraw::BltBackColor(RGB(0, 0, 0));
    CDC* pDC = CDDraw::GetBackCDC();			// ȡ�� Back Plain �� CDC
    CFont f,*fp;
    f.CreatePointFont(160,"Yu Gothic UI");	// ���� font f; 160��ʾ16 point����
    fp=pDC->SelectObject(&f);					// ѡ�� font f
    pDC->SetBkColor(RGB(0, 0, 0));
    pDC->SetTextColor(RGB(255, 255, 255));
    char str[80];								// Demo ���ֶ��ִ���ת��
    sprintf(str, "Lives x %d", lives);
    pDC->TextOut(230,210,str);
    pDC->SelectObject(fp);						// �ŵ� font f (ǧ��Ҫ©�˷ŵ�)
    CDDraw::ReleaseBackCDC();					// �ŵ� Back Plain �� CDC
}

/////////////////////////////////////////////////////////////////////////////
// ���classΪ��Ϸ����Ϸִ���������Ҫ����Ϸ��ʽ��������
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame* g): CGameState(g)
{
	enemy.push_back(new CGameEnemy(1));
	enemy.push_back(new CGameEnemy(1));
    /*ball = new CBall [NUMBALLS];*/
}

CGameStateRun::~CGameStateRun()
{
	for (unsigned int i = 0; i < enemy.size(); i++)
		delete enemy[i];
    /*delete [] ball;*/
}

void CGameStateRun::OnBeginState()
{
    /*const int BALL_GAP = 90;
    const int BALL_XY_OFFSET = 45;
    const int BALL_PER_ROW = 7;
    const int HITS_LEFT = 10;
    const int HITS_LEFT_X = 590;
    const int HITS_LEFT_Y = 0;
    const int BACKGROUND_X = 60;
    const int ANIMATION_SPEED = 15;*/
	player.SetXY(0, SIZE_Y - BLOCK_WIDTH_HEIGHT * 2 - PLAYER_HEIGHT);              //�趨��ҵ���ʼ����
	enemy[0]->SetXY(11 * BLOCK_WIDTH_HEIGHT, SIZE_Y - BLOCK_WIDTH_HEIGHT * 2 - 30); //�趨�������ʼ���� enemy_normal_height = 30
	enemy[1]->SetXY(15 * BLOCK_WIDTH_HEIGHT, SIZE_Y - BLOCK_WIDTH_HEIGHT * 2 - 30);
	map_stage_1.SetScreenX(0);                          //���õ�ͼ����ʼ����

	for (unsigned int i = 0; i < enemy.size(); i++)
		enemy[i]->SetIsAlive(true);
    //for (int i = 0; i < NUMBALLS; i++) {				// �趨�����ʼ����
    //	int x_pos = i % BALL_PER_ROW;
    //	int y_pos = i / BALL_PER_ROW;
    //	ball[i].SetXY(x_pos * BALL_GAP + BALL_XY_OFFSET, y_pos * BALL_GAP + BALL_XY_OFFSET);
    //	ball[i].SetDelay(x_pos);
    //	ball[i].SetIsAlive(true);
    //}
    /*eraser.Initialize();*/
    //background.SetTopLeft(BACKGROUND_X,0);				// �趨��������ʼ����
    //help.SetTopLeft(0, SIZE_Y - help.Height());			// �趨˵��ͼ����ʼ����
    //hits_left.SetInteger(HITS_LEFT);					// ָ��ʣ�µ�ײ����
    //hits_left.SetTopLeft(HITS_LEFT_X,HITS_LEFT_Y);		// ָ��ʣ��ײ����������
    //CAudio::Instance()->Play(AUDIO_LAKE, true);			// ���� WAVE
    //CAudio::Instance()->Play(AUDIO_DING, false);		// ���� WAVE
    //CAudio::Instance()->Play(AUDIO_NTUT, true);			// ���� MIDI
}

void CGameStateRun::OnMove()							// �ƶ���ϷԪ��
{
    //
    // ���ϣ���޸�cursor����ʽ���������ʽ��commmentȡ������
    //
    // SetCursor(AfxGetApp()->LoadCursor(IDC_GAMECURSOR));
    //
    // �ƶ�����ͼ������
    //
    /*if (background.Top() > SIZE_Y)
    	background.SetTopLeft(60 ,-background.Height());
    background.SetTopLeft(background.Left(),background.Top()+1);*/
    //
    // �ƶ���
    //
    /*for (int i=0; i < NUMBALLS; i++)
    	ball[i].OnMove();*/
    //
    // �ƶ�����
    //
    /*eraser.OnMove();*/
    //
    // �жϲ����Ƿ�������
    //
    //for (int i=0; i < NUMBALLS; i++)
    //	if (ball[i].IsAlive() && ball[i].HitEraser(&eraser)) {
    //		ball[i].SetIsAlive(false);
    //		CAudio::Instance()->Play(AUDIO_DING);
    //		hits_left.Add(-1);
    //		//
    //		// ��ʣ����ײ����Ϊ0��������Game Over״̬
    //		//
    //		if (hits_left.GetInteger() <= 0) {
    //			CAudio::Instance()->Stop(AUDIO_LAKE);	// ֹͣ WAVE
    //			CAudio::Instance()->Stop(AUDIO_NTUT);	// ֹͣ MIDI
    //			GotoGameState(GAME_STATE_OVER);
    //		}
    //	}
    //
    // �ƶ���������
    //
    /*bball.OnMove();*/
    player.OnMove(&map_stage_1);
	for (unsigned int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->OnMove(&map_stage_1);

		if (enemy[i]->IsAlive() && enemy[i]->HitPlayer(&player))
		{
			if (player.GetY() + PLAYER_HEIGHT <= enemy[i]->GetY() + 11)
				enemy[i]->SetIsAlive(false);
			else
			{
				player.SetMovingLeft(false);
				player.SetMovingRight(false);
				GotoGameState(GAME_STATE_OVER);
			}

		}
	}

	enemy[0]->OnMove(&map_stage_1);
	enemy[1]->OnMove(&map_stage_1);

	if (player.GetY() - map_stage_1.GetScreenY() > SIZE_Y)
	{
		player.SetMovingLeft(false);
		player.SetMovingRight(false);
		GotoGameState(GAME_STATE_OVER);
	}
}

void CGameStateRun::OnInit()  								// ��Ϸ�ĳ�ֵ��ͼ���趨
{
    //
    // ��ͼ�ܶ�ʱ��OnInit�������е�ͼҪ���ܶ�ʱ�䡣Ϊ��������Ϸ����
    //     �ȵĲ��ͷ�����Ϸ����֡�Loading ...������ʾLoading�Ľ��ȡ�
    //
	CDDraw::BltBackColor(DEFAULT_BG_COLOR);		// �� Back Plain Ϳ��Ԥ�����ɫ
    ShowInitProgress(33);	// �Ӹ�ǰһ��״̬�Ľ��ȣ��˴�������Ϊ33%
    //
    // ��ʼ��������
    //
    //for (int i = 0; i < NUMBALLS; i++)
    //	ball[i].LoadBitmap();								// �����i�����ͼ��
    //eraser.LoadBitmap();
    map_stage_1.LoadBitmap(); //�����ͼ
    player.LoadBitmap();
	for (unsigned int i = 0; i < enemy.size(); i++)
		enemy[i]->LoadBitmap();
    /*background.LoadBitmap(IDB_BACKGROUND);*/					// ���뱳����ͼ��
    //
    // ��ɲ���Loading��������߽���
    //
    ShowInitProgress(50);
    Sleep(300); // �������Ա㿴������ȣ�ʵ����Ϸ��ɾ����Sleep
    //
    // ����������������
    //
    //help.LoadBitmap(IDB_HELP,RGB(255,255,255));				// ����˵����ͼ��
    //corner.LoadBitmap(IDB_CORNER);							// �������ͼ��
    //corner.ShowBitmap(background);							// ��corner����background
    //bball.LoadBitmap();										// ����ͼ��
    hits_left.LoadBitmap();
    //CAudio::Instance()->Load(AUDIO_DING,  "sounds\\ding.wav");	// ������0������ding.wav
    //CAudio::Instance()->Load(AUDIO_LAKE,  "sounds\\lake.mp3");	// ������1������lake.mp3
    //CAudio::Instance()->Load(AUDIO_NTUT,  "sounds\\ntut.mid");	// ������2������ntut.mid
    //
    // ��OnInit������ӵ�CGameStaterOver::OnInit()�����Խ��Ȼ�û��100%
    //
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT  = 0x25; // keyboard���ͷ
    const char KEY_UP    = 0x26; // keyboard�ϼ�ͷ
    const char KEY_RIGHT = 0x27; // keyboard�Ҽ�ͷ
    const char KEY_DOWN  = 0x28; // keyboard�¼�ͷ

    if (nChar == KEY_LEFT)
        player.SetMovingLeft(true);

    /*eraser.SetMovingLeft(true);*/
    if (nChar == KEY_RIGHT)
        player.SetMovingRight(true);

    /*eraser.SetMovingRight(true);*/
	if (nChar == KEY_UP && player.GetJump() && UpClickCount < 1)
	{
		UpClickCount += 1;
		player.SetMovingUp(true);
	}
    	/*eraser.SetMovingUp(true);*/
    /*if (nChar == KEY_DOWN)
    	eraser.SetMovingDown(true);*/
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    const char KEY_LEFT  = 0x25; // keyboard���ͷ
    const char KEY_UP    = 0x26; // keyboard�ϼ�ͷ
    const char KEY_RIGHT = 0x27; // keyboard�Ҽ�ͷ
    const char KEY_DOWN  = 0x28; // keyboard�¼�ͷ

    if (nChar == KEY_LEFT)
        player.SetMovingLeft(false);

    /*eraser.SetMovingLeft(false);*/
    if (nChar == KEY_RIGHT)
        player.SetMovingRight(false);

    /*eraser.SetMovingRight(false);*/
	if (nChar == KEY_UP)
	{
		UpClickCount = 0;
		player.SetMovingUp(false);
	}
    	/*eraser.SetMovingUp(false);
    if (nChar == KEY_DOWN)
    	eraser.SetMovingDown(false);*/
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // ��������Ķ���
{
    /*eraser.SetMovingLeft(true);*/
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// ��������Ķ���
{
    /*eraser.SetMovingLeft(false);*/
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// ��������Ķ���
{
    // û�¡������Ҫ���������ƶ��Ļ���дcode������
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // ��������Ķ���
{
    /*eraser.SetMovingRight(true);*/
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// ��������Ķ���
{
    /*eraser.SetMovingRight(false);*/
}

void CGameStateRun::OnShow()
{
    //
    //  ע�⣺Show����ǧ��Ҫ�ƶ��κ���������꣬�ƶ�����Ĺ���Ӧ��Move���Ŷԣ�
    //        �����Ӵ����»�ͼʱ(OnDraw)������ͻ��ƶ�����������ܹ֡���������
    //        ˵��Move����MVC�е�Model��Show����View����View��Ӧ����Model��
    //
    //
    //  ���ϱ���ͼ��ײ�������򡢲��ӡ���������
    //
	map_stage_1.OnShow();
	for (unsigned int i = 0; i < enemy.size(); i++)
		enemy[i]->OnShow(&map_stage_1);
	player.OnShow(&map_stage_1);
    /*background.ShowBitmap();*/			// ���ϱ���ͼ
    /*help.ShowBitmap();*/					// ����˵��ͼ
    hits_left.ShowBitmap();
    //for (int i=0; i < NUMBALLS; i++)
    //	ball[i].OnShow();				// ���ϵ�i����
    //bball.OnShow();						// ���ϵ�������
    //eraser.OnShow();					// ���ϲ���
    //
    //  �������ϼ����½����ͼ
    //
    /*corner.SetTopLeft(0,0);
    corner.ShowBitmap();
    corner.SetTopLeft(SIZE_X-corner.Width(), SIZE_Y-corner.Height());
    corner.ShowBitmap();*/
}

CGameMap::CGameMap():screen_x(0), screen_y(0)
{
	//1~17
    int map_init1[15][17] = {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 4, 3, 4, 3, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							 { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
							 { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }
    };

	//18~34
	int map_init2[15][17] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
							  { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }
	};

	//35~51
	int map_init3[15][17] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	                          { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 4, 4, 4, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
							  { 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1 },
							  { 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2 }
	};

	int map_init4[15][3] = { { 0, 0, 0 },
	                         { 0, 0, 0 },
							 { 0, 0, 0 },
							 { 0, 0, 0 },
							 { 0, 0, 0 },
							 { 4, 4, 4 },
							 { 0, 0, 0 },
							 { 0, 0, 0 },
							 { 0, 0, 0 },
							 { 0, 0, 0 },
							 { 0, 0, 0 },
							 { 0, 0, 0 },
							 { 0, 0, 0 },
							 { 1, 1, 1 },
							 { 2, 2, 2 }
	};

    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 17; j++)
            map_index[i][j] = map_init1[i][j];

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 17; j++)
			map_index[i][17 + j] = map_init2[i][j];

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 17; j++)
			map_index[i][17*2 + j] = map_init3[i][j];

	for (int i = 0; i < 15; i++)
		for (int j = 0; j < 3; j++)
			map_index[i][17*3 + j] = map_init4[i][j];
}

void CGameMap::LoadBitmap()
{
    block_floor_1_ground.LoadBitmap(IDB_BLOCK_FLOOR_1_GROUND);
    block_floor_2_ground.LoadBitmap(IDB_BLOCK_FLOOR_2_GROUND);
    block_fragile_ground.LoadBitmap(IDB_BLOCK_FRAGILE_GROUND);
    block_sturdy_ground.LoadBitmap(IDB_BLOCK_STURDY_GROUND);
    block_item_1_common.LoadBitmap(IDB_BLOCK_ITEM_1_COMMON);
    block_item_2_ground.LoadBitmap(IDB_BLOCK_ITEM_2_GROUND);
	mountain.LoadBitmap(IDB_MOUNTAIN, RGB(160, 180, 250));
	cloud_1.LoadBitmap(IDB_CLOUD_1, RGB(160, 180, 250));
	brush.LoadBitmap(IDB_BRUSH, RGB(160, 180, 250));
}

void CGameMap::OnShow()
{
    for (int i = 0; i < BLOCK_COLUMN; i++)
    {
        for (int j = 0; j < BLOCK_ROW; j++)
        {
            int x = BLOCK_WIDTH_HEIGHT * i - screen_x;
            int y = BLOCK_WIDTH_HEIGHT * j - screen_y;

            switch (map_index[j][i])
            {
            case 0:
                break;

            case 1:
                block_floor_1_ground.SetTopLeft(x, y);
                block_floor_1_ground.ShowBitmap();
                break;

            case 2:
                block_floor_2_ground.SetTopLeft(x, y);
                block_floor_2_ground.ShowBitmap();
                break;

            case 3:
                block_item_1_common.SetTopLeft(x, y);
                block_item_1_common.ShowBitmap();
                break;

            case 4:
                block_fragile_ground.SetTopLeft(x, y);
                block_fragile_ground.ShowBitmap();
                break;

            default:
                ASSERT(0);
            }
        }
    }

	mountain.SetTopLeft(BLOCK_WIDTH_HEIGHT - screen_x, SIZE_Y - 33 * 2 - 74 - screen_y);
	mountain.ShowBitmap();
	cloud_1.SetTopLeft(6 * BLOCK_WIDTH_HEIGHT - screen_x, 2 * BLOCK_WIDTH_HEIGHT - screen_y);
	cloud_1.ShowBitmap();
	cloud_1.SetTopLeft(22 * BLOCK_WIDTH_HEIGHT - screen_x, 2 * BLOCK_WIDTH_HEIGHT - screen_y);
	cloud_1.ShowBitmap();
	brush.SetTopLeft(19 * BLOCK_WIDTH_HEIGHT - screen_x, SIZE_Y - 33 * 2 - 28 - screen_y);
	brush.ShowBitmap();
	brush.SetTopLeft(26 * BLOCK_WIDTH_HEIGHT - screen_x, SIZE_Y - 33 * 2 - 28 - screen_y);
	brush.ShowBitmap();
}

void CGameMap::OnDraw() 
{
	// not the same class , change to CGameState
}

bool CGameMap::IsEmpty(int x, int y)
{
    int block_x = x / BLOCK_WIDTH_HEIGHT;
    int block_y = y / BLOCK_WIDTH_HEIGHT;
    return map_index[block_y][block_x] == 0;
}

void CGameMap::SetScreenX(int step)
{
	if (step == 0)
		screen_x = 0;
	else
		screen_x += step;
}

int CGameMap::GetScreenX()
{
	return screen_x;
}

int CGameMap::GetScreenY()
{
	return screen_y;
}

CGamePlayer::CGamePlayer()
{
}

void CGamePlayer::LoadBitmap()
{
    player.LoadBitmap(IDB_PLAYER_1, RGB(160, 180, 250));
}

void CGamePlayer::OnMove(CGameMap* map)
{
    const int STEP_SIZE = 11;

	if (isMovingUp)
		if ((map->IsEmpty(x, y - 1) && map->IsEmpty(x + PLAYER_WIDTH, y - 1)) && jumpingCount < 6)
		{
			jumpingCount++;
			y -= 33;
		}
		else if(!map->IsEmpty(x, y + 1) || !map->IsEmpty(x + PLAYER_WIDTH, y + 1))//���Ϸ�����
		{
			y += STEP_SIZE;
		}
			/*if (jumpingcount < 10)
			{
				jumpingcount++;
				y -= 30 / jumpingcount;
			}
			else
			{
				jumpingcount = 0;
			}*/
	if ((map->IsEmpty(x, y + PLAYER_HEIGHT + 1) && map->IsEmpty(x + PLAYER_WIDTH, y + PLAYER_HEIGHT + 1)) || y + PLAYER_HEIGHT >= SIZE_Y)
	{
		y += STEP_SIZE;
		isFalling = true;
	}
	else if (!map->IsEmpty(x, y + PLAYER_HEIGHT - 1) || !map->IsEmpty(x + PLAYER_WIDTH, y + PLAYER_HEIGHT - 1))  //���·�����
		y = (y + PLAYER_HEIGHT) / BLOCK_WIDTH_HEIGHT * BLOCK_WIDTH_HEIGHT - PLAYER_HEIGHT;
	else
	{
		jumpingCount = 0;
		isMovingUp = false;
 		isFalling = false;
	}

	if (isMovingLeft)
		if (x - 1 > map->GetScreenX())
			if (map->IsEmpty(x - 1, y))
				x -= STEP_SIZE;

	if (isMovingRight)
		if (x + 1 < BLOCK_WIDTH_HEIGHT * 53)
			if (map->IsEmpty(x + PLAYER_WIDTH + 1, y))
			{
				x += STEP_SIZE;

				if ((x - map->GetScreenX() > SIZE_X * 2 / 3) && (map->GetScreenX() + SIZE_X < BLOCK_WIDTH_HEIGHT * 54 - STEP_SIZE))
					map->SetScreenX(STEP_SIZE);
			}
}

void CGamePlayer::OnShow(CGameMap* map)
{
    player.SetTopLeft(x - map->GetScreenX(), y - map->GetScreenY());
    player.ShowBitmap();
}

void CGamePlayer::SetMovingLeft(bool flag)
{
    isMovingLeft = flag;
}

void CGamePlayer::SetMovingRight(bool flag)
{
    isMovingRight = flag;
}

void CGamePlayer::SetMovingUp(bool flag)
{
    isMovingUp = flag;
}

void CGamePlayer::SetXY(int x, int y)
{
    this->x = x;
    this->y = y;
}
int CGamePlayer::GetX()
{
	return x;
}
int CGamePlayer::GetY()
{
	return y;
}

void CGamePlayer::SetJump(bool state)
{
	isJumping = state;
}

bool CGamePlayer::GetJump()
{
	return !isFalling;
}


CGameEnemy::CGameEnemy(int speed)
{
	movingSpeed = speed;
}

void CGameEnemy::LoadBitmap()
{
	enemy.LoadBitmap(IDB_ENEMY_NORMAL, RGB(160, 180, 250));
}

void CGameEnemy::OnMove(CGameMap * map)
{
	if (!isAlive)
		return;
	x -= movingSpeed;
}

void CGameEnemy::OnShow(CGameMap * map)
{
	if (x - 1 > map->GetScreenX() && isAlive)
	{
		enemy.SetTopLeft(x - map->GetScreenX(), y - map->GetScreenY());
		enemy.ShowBitmap();
	}
	
}
void CGameEnemy::SetXY(int x, int y)
{
	this->x = x;
	this->y = y;
}
int CGameEnemy::GetX()
{
	return x;
}
int CGameEnemy::GetY()
{
	return y;
}

bool CGameEnemy::IsAlive()
{
	return isAlive;
}

void CGameEnemy::SetIsAlive(bool alive)
{
	isAlive = alive;
}
bool CGameEnemy::HitPlayer(CGamePlayer * player)
{
	int x_rb = x + 33;
	int y_rb = y + 30;
	int player_x = player->GetX();
	int player_y = player->GetY();
	int player_x_rb = player_x + PLAYER_WIDTH;
	int player_y_rb = player_y + PLAYER_HEIGHT;

	return ((player_x <= x_rb) && (player_y <= y_rb) && (player_x_rb >= x) && (player_y_rb >= y));
}
}