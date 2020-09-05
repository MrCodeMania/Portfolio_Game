
// BhzzangView.cpp : CBhzzangView 클래스의 구현



#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Bhzzang.h"
#endif
#include <stdlib.h>
#include <time.h>
#include "BhzzangDoc.h"
#include "BhzzangView.h"
#include "InfoView.h"
#include <stdio.h>
#include <conio.h>
#include <mmsystem.h> 
#pragma comment(lib, "winmm.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBhzzangView

IMPLEMENT_DYNCREATE(CBhzzangView, CView)

BEGIN_MESSAGE_MAP(CBhzzangView, CView)
	ON_WM_KILLFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CBhzzangView 생성/소멸

CBhzzangView::CBhzzangView()
{
	// TODO: 여기에 생성 코드를 추가합니다.
	timer = false;
	Loop = false;
	MusicBattle = false;
	CreateM = 0;
	Momtong = 0;
	P_Momtong = 0;
	Skill = 0;
	Bite = 0;
	CBite = 0;
	Leaf_pos = 0;
	MonsterMove = 0;
	Throw = 0;
	MusicMode = 0;
	srand((unsigned)time(NULL));
	PlaySound(_T("../BGM.wav"), NULL, SND_ASYNC | SND_LOOP);
}

CBhzzangView::~CBhzzangView()
{
}

BOOL CBhzzangView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, ::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return CView::PreCreateWindow(cs);
}

// CBhzzangView 그리기

void CBhzzangView::OnDraw(CDC* pDC)
{
	CBhzzangDoc* pDoc = (CBhzzangDoc*)GetDocument();
	
	


	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (pDoc->TUTORIAL == 1)
	{
		CPen Pen(PS_SOLID, 1, RGB(0, 0, 0));
		CBitmap Start;
		Start.LoadBitmapW(IDB_START);
		CDC dcmem;
		dcmem.CreateCompatibleDC(pDC);
		BITMAP Startinfo;
		Start.GetBitmap(&Startinfo);
		dcmem.SelectObject(&Start);
		pDC->BitBlt(0, 0, Startinfo.bmWidth, Startinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		pDC->SelectObject(&Pen);
		pDC->SetBkMode(TRANSPARENT);
		pDC->Rectangle(150, 40, 300, 70);
		pDC->TextOutW(175, 45, _T("GAME START"));
		SetTimer(3, 1000, NULL);
	}
	else if (pDoc->ENDING)
	{
		CPen Pen(PS_SOLID, 1, RGB(0, 0, 0));
		CBitmap Start;
		Start.LoadBitmapW(IDB_START);
		CDC dcmem;
		dcmem.CreateCompatibleDC(pDC);
		BITMAP Startinfo;
		Start.GetBitmap(&Startinfo);
		dcmem.SelectObject(&Start);
		pDC->BitBlt(0, 0, Startinfo.bmWidth, Startinfo.bmHeight, &dcmem, 0, 0, SRCCOPY);
		pDC->SelectObject(&Pen);
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOutW(175, 45, _T("CLEAR!!"));
		PlaySound(_T("../BGM.wav"), NULL, SND_ASYNC);
	}
	
	else 
	{
		if (!pDoc->Battle)
		{
			if (MusicMode == 0)
			{
				MusicMode = 1;
				PlaySound(_T("../BGM.wav"), NULL, SND_ASYNC | SND_LOOP);
			}
			else if (MusicMode == 2)
			{
				PlaySound(_T("../Door.wav"), NULL, SND_ASYNC);
				MusicMode = 0;
				SetTimer(3, 2000, NULL);
			}
			CBitmap CharBit;
			CBitmap MapBit;
			MapBit.LoadBitmap(IDB_MAP);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			

			switch (pDoc->CharDirect)
			{
			case 1:
				CharBit.LoadBitmap(IDB_Stand);
				break;
			case 2:
				CharBit.LoadBitmap(IDB_GoFront);
				break;
			case 3:
				CharBit.LoadBitmap(IDB_Back);
				break;
			case 4:
				CharBit.LoadBitmap(IDB_GoBack);
				break;
			case 5:
				CharBit.LoadBitmap(IDB_Left);
				break;
			case 6:
				CharBit.LoadBitmap(IDB_GoLeft);
				break;
			case 7:
				CharBit.LoadBitmap(IDB_Right);
				break;
			case 8:
				CharBit.LoadBitmap(IDB_GoRight);
				break;
			}
			BITMAP Charinfo;
			BITMAP Mapinfo;
			MapBit.GetBitmap(&Mapinfo);
			dcmem.SelectObject(&MapBit);
			pDC->StretchBlt(0, 0, Mapinfo.bmWidth, Mapinfo.bmHeight, &dcmem, pDoc->CharPos_x, pDoc->CharPos_y, (pDoc->CharPos_x) + 450, (pDoc->CharPos_y) + 333, SRCCOPY);
			CharBit.GetBitmap(&Charinfo);
			dcmem.SelectObject(&CharBit);
			pDC->TransparentBlt(180, 140, Charinfo.bmWidth, Charinfo.bmHeight, &dcmem, 0, 0, Charinfo.bmWidth, Charinfo.bmHeight, RGB(51, 0, 51));
	
			if (pDoc->BOSS)
			{
				pDoc->BattleStart = 0;
				pDoc->Select = 0;
				pDoc->Pkbattle = 0;
				CreateM = 5;
				if(pDoc->Battle)
					pDoc->BOSS = false;
				pDoc->Battle = true;
				SetTimer(3, 500, NULL);
			}		
			else if (!pDoc->BOSS)
				CreateM = rand() % 5;
			if (CreateM == 0) // 이상해씨
			{
				pDoc->MonsterStat.Name.Format(_T("이상해씨"));
				pDoc->MonsterStat.Skill1.Format(_T("몸통박치기"));
				pDoc->MonsterStat.Skiil2.Format(_T("잎날가르기"));
				pDoc->MonsterStat.iAtt = 4;
				pDoc->MonsterStat.iHp = 20;
				pDoc->MonsterStat.iMaxHp = 20;
				pDoc->MonsterStat.iLevel = 3;
				pDoc->MonsterStat.iExp = 0;
			}
			else if (CreateM == 1)
			{
				pDoc->MonsterStat.Name.Format(_T("가디"));
				pDoc->MonsterStat.Skill1.Format(_T("몸통박치기"));
				pDoc->MonsterStat.Skiil2.Format(_T("물기"));
				pDoc->MonsterStat.iAtt = 3;
				pDoc->MonsterStat.iHp = 24;
				pDoc->MonsterStat.iMaxHp = 24;
				pDoc->MonsterStat.iLevel = 3;
				pDoc->MonsterStat.iExp = 0;
			} // 가디
			else if (CreateM == 2)
			{
				pDoc->MonsterStat.Name.Format(_T("꼬부기"));
				pDoc->MonsterStat.Skill1.Format(_T("몸통박치기"));
				pDoc->MonsterStat.Skiil2.Format(_T("파도타기"));
				pDoc->MonsterStat.iAtt = 2;
				pDoc->MonsterStat.iHp = 40;
				pDoc->MonsterStat.iMaxHp = 40;
				pDoc->MonsterStat.iLevel = 3;
				pDoc->MonsterStat.iExp = 0;
			}
			else if (CreateM == 3)
			{
				pDoc->MonsterStat.Name.Format(_T("파이리"));
				pDoc->MonsterStat.Skill1.Format(_T("몸통박치기"));
				pDoc->MonsterStat.Skiil2.Format(_T("불꽃 발사"));
				pDoc->MonsterStat.iAtt = 5;
				pDoc->MonsterStat.iHp = 15;
				pDoc->MonsterStat.iMaxHp = 15;
				pDoc->MonsterStat.iLevel = 3;
				pDoc->MonsterStat.iExp = 0;
			}//파이리
			else if (CreateM == 4)
			{
				pDoc->MonsterStat.Name.Format(_T("피카츄"));
				pDoc->MonsterStat.Skill1.Format(_T("전광석화"));
				pDoc->MonsterStat.Skiil2.Format(_T("전기 충격"));
				pDoc->MonsterStat.iAtt = 5;
				pDoc->MonsterStat.iHp = 18;
				pDoc->MonsterStat.iMaxHp = 18;
				pDoc->MonsterStat.iLevel = 3;
				pDoc->MonsterStat.iExp = 0;
			}
			else if (CreateM == 5)
			{
				pDoc->MonsterStat.Name.Format(_T("웬디"));
				pDoc->MonsterStat.Skill1.Format(_T("화염 방사"));
				pDoc->MonsterStat.iAtt = 10;
				pDoc->MonsterStat.iHp = 10;
				pDoc->MonsterStat.iMaxHp = 150;
				pDoc->MonsterStat.iLevel = 10;
				pDoc->MonsterStat.iExp = 0;
			}

			if (pDoc->CENTER)
			{
				for (int i = 0; i < pDoc->POKEDEX.GetSize(); i++)
					pDoc->POKEDEX[i].iHp = pDoc->POKEDEX[i].iMaxHp;
				pDoc->CENTER = false;
				pDoc->CharPos_y += 5;
				MessageBox(_T("모든 포켓몬의 체력이 회복되었다!"), L"포켓몬 센터", MB_OK);
				SetTimer(3, 100, NULL);
			}
		}
		else if (pDoc->Battle)
		{
			if (!MusicBattle)
			{
				MusicBattle = true;
				PlaySound(_T("../전투시.wav"), NULL, SND_ASYNC|SND_LOOP);
			}
			CBitmap MyPkBit;
			CBitmap ComPkBit;
			CBitmap BattleMapBit;
			CBitmap Speed;
			Speed.LoadBitmapW(IDB_SPEED);
			if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("이상해씨"))
				MyPkBit.LoadBitmap(IDB_MYISANG);
			else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("가디"))
				MyPkBit.LoadBitmap(IDB_MYGADI);
			else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("꼬부기"))
				MyPkBit.LoadBitmap(IDB_MYSQUIT);
			else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("파이리"))
				MyPkBit.LoadBitmap(IDB_MYFIRI);
			else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("피카츄"))
				MyPkBit.LoadBitmap(IDB_MYPIKA);
			BattleMapBit.LoadBitmap(IDB_BATTLEMAP);
			CDC dcmem;
			dcmem.CreateCompatibleDC(pDC);
			/////////////////////////
			BITMAP MyPkinfo;
			BITMAP ComPkinfo;
			BITMAP BattleMapinfo;
			BITMAP Speedinfo;
			BattleMapBit.GetBitmap(&BattleMapinfo);
			dcmem.SelectObject(&BattleMapBit);
			pDC->StretchBlt(0, 0, BattleMapinfo.bmWidth * 2, BattleMapinfo.bmHeight * 2, &dcmem, 0, 0, BattleMapinfo.bmWidth, BattleMapinfo.bmHeight, SRCCOPY);
			////////////////////////////////////////////

			MyPkBit.GetBitmap(&MyPkinfo);
			dcmem.SelectObject(&MyPkBit);

			////////////////////////////////////////////
			/*몬스터 생성
			이상해씨, 가디, 피카츄, 파이리, 꼬부기
			//////////////////////////////////////////*/

			if (pDoc->BattleStart == 0)
			{
				pDC->TransparentBlt(193, 280, (MyPkinfo.bmWidth + 10), (MyPkinfo.bmHeight + 10), &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
				if (CreateM == 0) // 이상해씨
				{
					ComPkBit.LoadBitmap(IDB_COMISANG);
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth + 10, ComPkinfo.bmHeight + 10, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));

				}
				else if (CreateM == 1)
				{
					ComPkBit.LoadBitmap(IDB_COMGADI);
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));

				} // 가디
				else if (CreateM == 2)
				{
					ComPkBit.LoadBitmap(IDB_COMSQUIT);
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}
				else if (CreateM == 3)
				{
					ComPkBit.LoadBitmap(IDB_COMFIRI);
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}//파이리
				else if (CreateM == 4)
				{
					ComPkBit.LoadBitmap(IDB_COMPIKA);
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth, ComPkinfo.bmHeight, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}
				else if (CreateM == 5)
				{
					ComPkBit.LoadBitmap(IDB_WENDY);
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth*2, ComPkinfo.bmHeight*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}
				SetTimer(3, 300, NULL);
			}
			/*전투 돌입*/
			else if (pDoc->BattleStart == 1)
			{
				MonsterMove = 1;
				if (CreateM == 0) // 이상해씨
				{
					ComPkBit.LoadBitmap(IDB_COMISANG);
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth + 10, ComPkinfo.bmHeight + 10, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}
				else if (CreateM == 1)
				{
					ComPkBit.LoadBitmap(IDB_COMGADI);
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				} // 가디
				else if (CreateM == 2)
				{
					ComPkBit.LoadBitmap(IDB_COMSQUIT);
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}
				else if (CreateM == 3)
				{
					ComPkBit.LoadBitmap(IDB_COMFIRI);
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}//파이리
				else if (CreateM == 4)
				{
					ComPkBit.LoadBitmap(IDB_COMPIKA);
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth, ComPkinfo.bmHeight, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}
				else if (CreateM == 5)
				{
					ComPkBit.LoadBitmap(IDB_WENDY);
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth*2, ComPkinfo.bmHeight*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}
				if (pDoc->POKEDEX[pDoc->Pkbattle].Name==_T("피카츄") && P_Momtong)
				{
					CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
					pDC->SelectObject(&Text);
					pDC->SetBkMode(TRANSPARENT);
					pDC->TextOutW(180, 150, _T("전광석화!"));
					if (P_Momtong > 200)
					{
						Speed.GetBitmap(&Speedinfo);
						dcmem.SelectObject(&Speed);
						pDC->TransparentBlt(193, 280, (Speedinfo.bmWidth + 10), (Speedinfo.bmHeight + 10), &dcmem, 0, 0, Speedinfo.bmWidth, Speedinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(4, 300, NULL);
						MyPkBit.GetBitmap(&MyPkinfo);
						dcmem.SelectObject(&MyPkBit);
						pDC->TransparentBlt(110, 250, (MyPkinfo.bmWidth + 10), (MyPkinfo.bmHeight + 10), &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(4, 150, NULL);
					}
					else if (P_Momtong > 150)
					{
						Speed.GetBitmap(&Speedinfo);
						dcmem.SelectObject(&Speed);
						pDC->TransparentBlt(110, 250, (Speedinfo.bmWidth + 10), (Speedinfo.bmHeight + 10), &dcmem, 0, 0, Speedinfo.bmWidth, Speedinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(4, 300, NULL);
						MyPkBit.GetBitmap(&MyPkinfo);
						dcmem.SelectObject(&MyPkBit);
						pDC->TransparentBlt(290, 160, (MyPkinfo.bmWidth + 10), (MyPkinfo.bmHeight + 10), &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(4, 150, NULL);
					}
					else if (P_Momtong > 100)
					{
						Speed.GetBitmap(&Speedinfo);
						dcmem.SelectObject(&Speed);
						pDC->TransparentBlt(290, 160, (Speedinfo.bmWidth + 10), (Speedinfo.bmHeight + 10), &dcmem, 0, 0, Speedinfo.bmWidth, Speedinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(4, 300, NULL);
						MyPkBit.GetBitmap(&MyPkinfo);
						dcmem.SelectObject(&MyPkBit);
						pDC->TransparentBlt(175, 80, (MyPkinfo.bmWidth + 10), (MyPkinfo.bmHeight + 10), &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(4, 150, NULL);
					}
					else if (P_Momtong > 50)
					{
						Speed.GetBitmap(&Speedinfo);
						dcmem.SelectObject(&Speed);
						pDC->TransparentBlt(175, 80, (Speedinfo.bmWidth + 10), (Speedinfo.bmHeight + 10), &dcmem, 0, 0, Speedinfo.bmWidth, Speedinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(4, 300, NULL);
						MyPkBit.GetBitmap(&MyPkinfo);
						dcmem.SelectObject(&MyPkBit);
						pDC->TransparentBlt(193, 40, (MyPkinfo.bmWidth + 10), (MyPkinfo.bmHeight + 10), &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(4, 150, NULL);

					}
					else if (P_Momtong < 50)
					{
						pDoc->MonsterStat.iHp -= pDoc->POKEDEX[0].iAtt;
						P_Momtong = 0;
						Momtong = 0;
						MyPkBit.GetBitmap(&MyPkinfo);
						dcmem.SelectObject(&MyPkBit);
						pDC->TransparentBlt(193, 280, (MyPkinfo.bmWidth + 10), (MyPkinfo.bmHeight + 10), &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
						pDoc->BattleStart = 2;
						SetTimer(3, 300, NULL);
					}
				}
				else if (Momtong)
				{
					CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
					pDC->SelectObject(&Text);
					pDC->SetBkMode(TRANSPARENT);
					pDC->TextOutW(180, 150, _T("몸통박치기!"));

					MyPkBit.GetBitmap(&MyPkinfo);
					dcmem.SelectObject(&MyPkBit);
					if (Momtong > 41)
					{
						pDC->TransparentBlt(193, Momtong, (MyPkinfo.bmWidth + 10), (MyPkinfo.bmHeight + 10), &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(2, 50, NULL);
					}
					if (Momtong < 41)
					{
						pDoc->MonsterStat.iHp -= pDoc->POKEDEX[0].iAtt;
						Momtong = 0;
						pDC->TransparentBlt(193, 280, (MyPkinfo.bmWidth + 10), (MyPkinfo.bmHeight + 10), &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
						pDoc->BattleStart = 2;
						SetTimer(3, 300, NULL);
					}
				}
				
				else if (Skill)
				{
					if (Skill == 1)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("잎날가르기!"));
						CBitmap Skill_Leaf;
						Skill_Leaf.LoadBitmapW(IDB_LEAF);
						BITMAP Leafinfo;

						if (!Leaf_pos)
							Leaf_pos = 280;
						else if (Leaf_pos < 5)
						{
							pDoc->BattleStart = 2;
							Leaf_pos = 0;
							Skill = 0;
							pDoc->MonsterStat.iHp -= pDoc->POKEDEX[0].iAtt * 2;
							SetTimer(3, 300, NULL);
						}
						if (Leaf_pos > 5)
						{
							Skill_Leaf.GetBitmap(&Leafinfo);
							dcmem.SelectObject(&Skill_Leaf);
							pDC->TransparentBlt(193, Leaf_pos, (Leafinfo.bmWidth), (Leafinfo.bmHeight), &dcmem, 0, 0, Leafinfo.bmWidth, Leafinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(5, 50, NULL);
						}
						//덩쿨채찍
					}
					else if (Skill == 2)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("물기!!"));
						if (!Bite)
						{
							CBitmap Skill_BITE1;
							Skill_BITE1.LoadBitmapW(IDB_BITE1);
							BITMAP Bite1info;
							Skill_BITE1.GetBitmap(&Bite1info);
							dcmem.SelectObject(&Skill_BITE1);
							pDC->TransparentBlt(150, 5, (Bite1info.bmWidth), (Bite1info.bmHeight), &dcmem, 0, 0, Bite1info.bmWidth, Bite1info.bmHeight, RGB(255, 255, 255));
							SetTimer(6, 300, NULL);
						}
						else if (Bite == 1)
						{
							CBitmap Skill_BITE2;
							Skill_BITE2.LoadBitmapW(IDB_BITE2);
							BITMAP Bite2info;
							Skill_BITE2.GetBitmap(&Bite2info);
							dcmem.SelectObject(&Skill_BITE2);
							pDC->TransparentBlt(160, 5, (Bite2info.bmWidth), (Bite2info.bmHeight), &dcmem, 0, 0, Bite2info.bmWidth, Bite2info.bmHeight, RGB(255, 255, 255));
							pDoc->BattleStart = 2; 
							Skill = 0;
							pDoc->MonsterStat.iHp -= pDoc->POKEDEX[0].iAtt * 2;
							Bite = 0;
							SetTimer(3, 300, NULL);
						}
						//울부짖기
					}
					else if (Skill == 3)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("파도타기!"));
						CBitmap Skill_Surf;
						Skill_Surf.LoadBitmapW(IDB_SURF);
						BITMAP Surfinfo;

						if (!Leaf_pos)
							Leaf_pos = 280;
						else if (Leaf_pos < 5)
						{
							pDoc->BattleStart = 2;
							Leaf_pos = 0;
							Skill = 0;
							pDoc->MonsterStat.iHp -= pDoc->POKEDEX[0].iAtt * 2;
							SetTimer(3, 300, NULL);
						}
						if (Leaf_pos > 5)
						{
							Skill_Surf.GetBitmap(&Surfinfo);
							dcmem.SelectObject(&Skill_Surf);
							pDC->TransparentBlt(150, Leaf_pos, (Surfinfo.bmWidth), (Surfinfo.bmHeight), &dcmem, 0, 0, Surfinfo.bmWidth, Surfinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(5, 50, NULL);
						}

						//파도타기
					}
					else if (Skill == 4)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("화염방사!"));
						if (!Bite)
						{
							CBitmap Skill_FIRE1;
							Skill_FIRE1.LoadBitmapW(IDB_FLAME);
							BITMAP FIRE1info;
							Skill_FIRE1.GetBitmap(&FIRE1info);
							dcmem.SelectObject(&Skill_FIRE1);
							pDC->TransparentBlt(199, 20, (FIRE1info.bmWidth) + 10, (FIRE1info.bmHeight) + 10, &dcmem, 0, 0, FIRE1info.bmWidth, FIRE1info.bmHeight, RGB(255, 255, 255));
							SetTimer(6, 1000, NULL);
						}
						else
						{
							pDoc->BattleStart = 2;
							Bite = 0;
							Skill = 0;
							pDoc->MonsterStat.iHp -= pDoc->POKEDEX[0].iAtt * 2;
							SetTimer(3, 300, NULL);
						}
						//화염방사
					}
					else if (Skill == 5)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("번개!"));
						if (Bite == 0)
						{
							CBitmap Skill_Thunder;
							Skill_Thunder.LoadBitmapW(IDB_PIKATHUNDER);
							BITMAP Thunderinfo;
							Skill_Thunder.GetBitmap(&Thunderinfo);
							dcmem.SelectObject(&Skill_Thunder);
							pDC->TransparentBlt(188, 280, (Thunderinfo.bmWidth) + 10, (Thunderinfo.bmHeight) + 10, &dcmem, 0, 0, Thunderinfo.bmWidth, Thunderinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(6, 1200, NULL);
						}
						if (Bite == 1)
						{
							CBitmap Thunder;
							Thunder.LoadBitmapW(IDB_THUNDER);
							BITMAP SThunderinfo;
							Thunder.GetBitmap(&SThunderinfo);
							dcmem.SelectObject(&Thunder);
							pDC->TransparentBlt(190, 0, (SThunderinfo.bmWidth) + 10, (SThunderinfo.bmHeight) + 10, &dcmem, 0, 0, SThunderinfo.bmWidth, SThunderinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(7, 600, NULL);
						}

						else if (Bite == 2)
						{
							pDoc->BattleStart = 2;
							Bite = 0;
							Skill = 0;
							pDoc->MonsterStat.iHp -= pDoc->POKEDEX[0].iAtt * 2;
							SetTimer(3, 300, NULL);
						}
						//울부짖기
					}
				}
				else if (Throw == 1)
				{
					CBitmap Ball;
					Ball.LoadBitmapW(IDB_BALL);
					BITMAP Ballinfo;
					if (Leaf_pos == 0)
					{
						Leaf_pos = 252;
						SetTimer(5, 100, NULL);
					}
					else if (Leaf_pos > 230)
					{
						Ball.GetBitmap(&Ballinfo);
						dcmem.SelectObject(&Ball);
						pDC->TransparentBlt(199, Leaf_pos, (Ballinfo.bmWidth) + 10, (Ballinfo.bmHeight) + 10, &dcmem, 0, 0, Ballinfo.bmWidth, Ballinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(5, 100, NULL);
					}
					else if (Leaf_pos > 180)
					{
						Ball.GetBitmap(&Ballinfo);
						dcmem.SelectObject(&Ball);
						pDC->TransparentBlt(220, Leaf_pos, (Ballinfo.bmWidth) + 10, (Ballinfo.bmHeight) + 10, &dcmem, 0, 0, Ballinfo.bmWidth, Ballinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(5, 100, NULL);
					}
					else if (Leaf_pos > 150)
					{
						Ball.GetBitmap(&Ballinfo);
						dcmem.SelectObject(&Ball);
						pDC->TransparentBlt(250, Leaf_pos, (Ballinfo.bmWidth) + 10, (Ballinfo.bmHeight) + 10, &dcmem, 0, 0, Ballinfo.bmWidth, Ballinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(5, 100, NULL);
					}
					else if (Leaf_pos > 100)
					{
						Ball.GetBitmap(&Ballinfo);
						dcmem.SelectObject(&Ball);
						pDC->TransparentBlt(230, Leaf_pos, (Ballinfo.bmWidth) + 10, (Ballinfo.bmHeight) + 10, &dcmem, 0, 0, Ballinfo.bmWidth, Ballinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(5, 100, NULL);
					}
					else if (Leaf_pos > 60)
					{
						Ball.GetBitmap(&Ballinfo);
						dcmem.SelectObject(&Ball);
						pDC->TransparentBlt(220, Leaf_pos, (Ballinfo.bmWidth) + 10, (Ballinfo.bmHeight) + 10, &dcmem, 0, 0, Ballinfo.bmWidth, Ballinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(5, 100, NULL);
					}
					else if (Leaf_pos > 22)
					{
						Ball.GetBitmap(&Ballinfo);
						dcmem.SelectObject(&Ball);
						pDC->TransparentBlt(193, Leaf_pos, (Ballinfo.bmWidth) + 10, (Ballinfo.bmHeight) + 10, &dcmem, 0, 0, Ballinfo.bmWidth, Ballinfo.bmHeight, RGB(255, 255, 255));
						SetTimer(5, 100, NULL);
					}
					else if (Leaf_pos < 22)
					{
						Leaf_pos = 0;
						Throw = 0;
						pDoc->BattleStart = 3;
						SetTimer(3, 100, NULL);
					}
				}
			}//내턴
			else if (pDoc->BattleStart == 2)
			{
				MyPkBit.GetBitmap(&MyPkinfo);
				dcmem.SelectObject(&MyPkBit);
				pDC->TransparentBlt(193, 280, (MyPkinfo.bmWidth + 10), (MyPkinfo.bmHeight + 10), &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
				if (CreateM == 0) // 이상해씨
					ComPkBit.LoadBitmap(IDB_COMISANG);
				else if (CreateM == 1)
					ComPkBit.LoadBitmap(IDB_COMGADI);
				else if (CreateM == 2)
					ComPkBit.LoadBitmap(IDB_COMSQUIT);
				else if (CreateM == 3)
					ComPkBit.LoadBitmap(IDB_COMFIRI);
				//파이리
				else if (CreateM == 4)
					ComPkBit.LoadBitmap(IDB_COMPIKA);
				else if (CreateM == 5)
					ComPkBit.LoadBitmap(IDB_WENDY);
				if (MonsterMove == 1)
				{
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					if (CreateM == 0) // 이상해씨
						pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth+10, ComPkinfo.bmHeight+10, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 1)
						pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 2)
						pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 3)
						pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));//파이리
					else if (CreateM == 4)
						pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth, ComPkinfo.bmHeight, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 5)
						pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth*2, ComPkinfo.bmHeight*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					
					MonsterMove = rand() % 2 + 2;
					Momtong = 10;
					P_Momtong = 5;
				}
				if (MonsterMove == 2)
				{
					if (pDoc->MonsterStat.Name == _T("피카츄"))
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("전광석화!"));
						if (P_Momtong > 200)
						{
							pDoc->POKEDEX[0].iHp -= pDoc->MonsterStat.iAtt;
							pDoc->BattleStart = 0; 
							P_Momtong = 0;
							Momtong = 0;
							ComPkBit.GetBitmap(&ComPkinfo);
							dcmem.SelectObject(&ComPkBit);
							pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth, ComPkinfo.bmHeight, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(3, 300, NULL);
						}
						else if (P_Momtong > 150)
						{
							Speed.GetBitmap(&Speedinfo);
							dcmem.SelectObject(&Speed);
							pDC->TransparentBlt(150, 170, (Speedinfo.bmWidth + 10), (Speedinfo.bmHeight + 10), &dcmem, 0, 0, Speedinfo.bmWidth, Speedinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(9, 300, NULL);
							ComPkBit.GetBitmap(&ComPkinfo);
							dcmem.SelectObject(&ComPkBit);
							pDC->TransparentBlt(190, 260, (ComPkinfo.bmWidth + 10), (ComPkinfo.bmHeight + 10), &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(9, 150, NULL);
						}
						else if (P_Momtong > 100)
						{
							Speed.GetBitmap(&Speedinfo);
							dcmem.SelectObject(&Speed);
							pDC->TransparentBlt(253, 80, (Speedinfo.bmWidth + 10), (Speedinfo.bmHeight + 10), &dcmem, 0, 0, Speedinfo.bmWidth, Speedinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(9, 300, NULL);
							ComPkBit.GetBitmap(&ComPkinfo);
							dcmem.SelectObject(&ComPkBit);
							pDC->TransparentBlt(150, 170, (ComPkinfo.bmWidth + 10), (ComPkinfo.bmHeight + 10), &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(9, 150, NULL);
						}
						else if (P_Momtong > 50)
						{
							Speed.GetBitmap(&Speedinfo);
							dcmem.SelectObject(&Speed);
							pDC->TransparentBlt(110, 40, (Speedinfo.bmWidth + 10), (Speedinfo.bmHeight + 10), &dcmem, 0, 0, Speedinfo.bmWidth, Speedinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(9, 300, NULL);
							ComPkBit.GetBitmap(&ComPkinfo);
							dcmem.SelectObject(&ComPkBit);
							pDC->TransparentBlt(253, 80, (ComPkinfo.bmWidth + 10), (ComPkinfo.bmHeight + 10), &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(9, 150, NULL);

						}
						else if (P_Momtong > 0)
						{
							Speed.GetBitmap(&Speedinfo);
							dcmem.SelectObject(&Speed);
							pDC->TransparentBlt(193, 10, (Speedinfo.bmWidth + 10), (Speedinfo.bmHeight + 10), &dcmem, 0, 0, Speedinfo.bmWidth, Speedinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(9, 300, NULL);
							ComPkBit.GetBitmap(&ComPkinfo);
							dcmem.SelectObject(&ComPkBit);
							pDC->TransparentBlt(110, 40, (ComPkinfo.bmWidth + 10), (ComPkinfo.bmHeight + 10), &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(9, 150, NULL);
						}
					}
					else if (CreateM == 5)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("화염방사!"));
						CBitmap Skill_FIRE1;
						Skill_FIRE1.LoadBitmapW(IDB_FLAME);
						BITMAP FIRE1info;
						if (CBite == 0)
						{
							Skill_FIRE1.GetBitmap(&FIRE1info);
							dcmem.SelectObject(&Skill_FIRE1);
							pDC->TransparentBlt(199, 270, (FIRE1info.bmWidth) + 10, (FIRE1info.bmHeight) + 10, &dcmem, 0, 0, FIRE1info.bmWidth, FIRE1info.bmHeight, RGB(255, 255, 255));
							SetTimer(11, 1000, NULL);
						}
						else if (CBite == 1)
						{
							pDoc->POKEDEX[0].iHp -= pDoc->MonsterStat.iAtt * 2;
							pDoc->BattleStart = 0;
							CBite = 0;
							SetTimer(3, 300, NULL);
						}
					}
					else if(CreateM<=3)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("몸통박치기!"));
						ComPkBit.GetBitmap(&ComPkinfo);
						dcmem.SelectObject(&ComPkBit);
						if (Momtong < 230)
						{
							pDC->TransparentBlt(193, Momtong, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(10, 50, NULL);
						}
						else if (Momtong > 230)
						{
							pDoc->POKEDEX[0].iHp -= pDoc->MonsterStat.iAtt;
							pDoc->BattleStart = 0;
							Momtong = 0;
							P_Momtong = 0;
							pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(3, 300, NULL);
						}
					}
				}
				else if (MonsterMove == 3)
				{
					if (CreateM == 0)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("잎날가르기!"));
						CBitmap Skill_Leaf;
						Skill_Leaf.LoadBitmapW(IDB_LEAF);
						BITMAP Leafinfo;

						if (Leaf_pos == 0)
							Leaf_pos = 10;
						else if (Leaf_pos > 250)
						{
							Leaf_pos = 0;
							pDoc->POKEDEX[0].iHp -= pDoc->MonsterStat.iAtt * 2;
							pDoc->BattleStart = 0;
						}
						if (Leaf_pos > 5)
						{
							Skill_Leaf.GetBitmap(&Leafinfo);
							dcmem.SelectObject(&Skill_Leaf);
							pDC->TransparentBlt(193, Leaf_pos, (Leafinfo.bmWidth), (Leafinfo.bmHeight), &dcmem, 0, 0, Leafinfo.bmWidth, Leafinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(8, 50, NULL);
						}
					}
					else if (CreateM == 1)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("물기!!"));
						CBitmap Skill_BITE1;
						Skill_BITE1.LoadBitmapW(IDB_BITE1);
						BITMAP Bite1info;
						CBitmap Skill_BITE2;
						Skill_BITE2.LoadBitmapW(IDB_BITE2);
						BITMAP Bite2info;
						if (CBite == 0)
						{
							Skill_BITE1.GetBitmap(&Bite1info);
							dcmem.SelectObject(&Skill_BITE1);
							pDC->TransparentBlt(150, 250, (Bite1info.bmWidth), (Bite1info.bmHeight), &dcmem, 0, 0, Bite1info.bmWidth, Bite1info.bmHeight, RGB(255, 255, 255));
							SetTimer(11, 300, NULL);
						}
						else if (CBite == 1)
						{
							Skill_BITE2.GetBitmap(&Bite2info);
							dcmem.SelectObject(&Skill_BITE2);
							pDC->TransparentBlt(160, 250, (Bite2info.bmWidth), (Bite2info.bmHeight), &dcmem, 0, 0, Bite2info.bmWidth, Bite2info.bmHeight, RGB(255, 255, 255));
							pDoc->POKEDEX[0].iHp -= pDoc->MonsterStat.iAtt * 2;
							pDoc->BattleStart = 0;
							CBite = 0;
							SetTimer(3, 300, NULL);
						}
					}
					else if (CreateM == 2)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("파도타기!"));
						CBitmap Skill_Surf1;
						Skill_Surf1.LoadBitmapW(IDB_SURF);
						BITMAP Surf1info;

						if (!Leaf_pos)
							Leaf_pos = 10;
						else if (Leaf_pos > 250)
						{
							Leaf_pos = 0;
							pDoc->POKEDEX[0].iHp -= pDoc->MonsterStat.iAtt * 2;
							pDoc->BattleStart = 0;
						}
						if (Leaf_pos > 5)
						{
							Skill_Surf1.GetBitmap(&Surf1info);
							dcmem.SelectObject(&Skill_Surf1);
							pDC->TransparentBlt(150, Leaf_pos, (Surf1info.bmWidth), (Surf1info.bmHeight), &dcmem, 0, 0, Surf1info.bmWidth, Surf1info.bmHeight, RGB(255, 255, 255));
							SetTimer(8, 50, NULL);
						}
					}
					else if (CreateM == 3)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("화염방사!"));
						CBitmap Skill_FIRE1;
						Skill_FIRE1.LoadBitmapW(IDB_FLAME);
						BITMAP FIRE1info;
						if (CBite == 0)
						{
							Skill_FIRE1.GetBitmap(&FIRE1info);
							dcmem.SelectObject(&Skill_FIRE1);
							pDC->TransparentBlt(199, 270, (FIRE1info.bmWidth) + 10, (FIRE1info.bmHeight) + 10, &dcmem, 0, 0, FIRE1info.bmWidth, FIRE1info.bmHeight, RGB(255, 255, 255));
							SetTimer(11, 1000, NULL);
						}
						else if (CBite == 1)
						{
							pDoc->POKEDEX[0].iHp -= pDoc->MonsterStat.iAtt * 2;
							pDoc->BattleStart = 0;
							CBite = 0;
							SetTimer(3, 300, NULL);
						}
						//화염방사
					}
					else if (CreateM == 4)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("번개!"));
						CBitmap Skill_Thunder;
						Skill_Thunder.LoadBitmapW(IDB_PIKATHUNDER);
						BITMAP Thunderinfo;
						CBitmap Thunder;
						Thunder.LoadBitmapW(IDB_THUNDER);
						BITMAP SThunderinfo;
						if (CBite == 0)
						{
							Skill_Thunder.GetBitmap(&Thunderinfo);
							dcmem.SelectObject(&Skill_Thunder);
							pDC->TransparentBlt(188, 10, (Thunderinfo.bmWidth) + 10, (Thunderinfo.bmHeight) + 10, &dcmem, 0, 0, Thunderinfo.bmWidth, Thunderinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(11, 1200, NULL);
						}
						if (CBite == 1)
						{
							Thunder.GetBitmap(&SThunderinfo);
							dcmem.SelectObject(&Thunder);
							pDC->TransparentBlt(190, 200, (SThunderinfo.bmWidth) + 10, (SThunderinfo.bmHeight) + 10, &dcmem, 0, 0, SThunderinfo.bmWidth, SThunderinfo.bmHeight, RGB(255, 255, 255));
							SetTimer(12, 600, NULL);
						}
						else if (CBite == 2)
						{
							pDoc->POKEDEX[0].iHp -= pDoc->MonsterStat.iAtt * 2;
							pDoc->BattleStart = 0;
							CBite = 0;
							SetTimer(3, 300, NULL);
						}
						//울부짖기
					}
					else if (CreateM == 5)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("화염방사!"));
						CBitmap Skill_FIRE1;
						Skill_FIRE1.LoadBitmapW(IDB_FLAME);
						BITMAP FIRE1info;
						if (CBite == 0)
						{
							Skill_FIRE1.GetBitmap(&FIRE1info);
							dcmem.SelectObject(&Skill_FIRE1);
							pDC->TransparentBlt(199, 270, (FIRE1info.bmWidth) + 10, (FIRE1info.bmHeight) + 10, &dcmem, 0, 0, FIRE1info.bmWidth, FIRE1info.bmHeight, RGB(255, 255, 255));
							SetTimer(11, 1000, NULL);
						}
						else if (CBite == 1)
						{
							pDoc->POKEDEX[0].iHp -= pDoc->MonsterStat.iAtt * 2;
							pDoc->BattleStart = 0;
							CBite = 0;
							SetTimer(3, 300, NULL);
						}
					}
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					if (CreateM == 0) // 이상해씨
						pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth + 10, ComPkinfo.bmHeight + 10, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 1)
						pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 2)
						pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 3)
						pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth )*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));//파이리
					else if (CreateM == 4)
						pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth, ComPkinfo.bmHeight, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 5)
						pDC->TransparentBlt(186, 6, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight + 10)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));//파이리
					Momtong = 0;
					P_Momtong = 0;
				}
				
			}//컴퓨터턴
			else if (pDoc->BattleStart == 3)
			{
				CBitmap Ball;
				Ball.LoadBitmapW(IDB_BALL);
				BITMAP Ballinfo;
				Ball.GetBitmap(&Ballinfo);
				dcmem.SelectObject(&Ball);
				pDC->TransparentBlt(193, 10, (Ballinfo.bmWidth) + 10, (Ballinfo.bmHeight) + 10, &dcmem, 0, 0, Ballinfo.bmWidth, Ballinfo.bmHeight, RGB(255, 255, 255));

				int SuccessOrFail = rand() % 5;
				if (CreateM == 5)
				{
					MessageBox(_T("잡을 수 없습니다!"), L"몬스터 볼", MB_OK | MB_ICONQUESTION);
					pDoc->BattleStart = 2;
					SetTimer(3, 100, NULL);
				}
				else if (SuccessOrFail <2)
				{
					if (pDoc->PKNum > 2)
					{
						MessageBox(_T("잡을 수 있는 몬스터 초과!"), L"몬스터 볼", MB_OK | MB_ICONQUESTION);
						pDoc->BattleStart = 2;
						SetTimer(3, 100, NULL);
					}
					else {
						MessageBox(_T("포획 성공!"), L"몬스터 볼", MB_OK | MB_ICONQUESTION);
						pDoc->POKEDEX.Add(pDoc->MonsterStat);
						pDoc->PKNum++;
						pDoc->Battle = false;
						MusicBattle = false; 
						MusicMode = 0;
						pDoc->BattleStart = 0;
						Bite = 0;
						CBite = 0;

						SetTimer(3, 100, NULL);
					}
				}
				else if (SuccessOrFail >= 2)
				{
					MessageBox(_T("포획 실패!"), L"몬스터 볼", MB_OK | MB_ICONQUESTION);
					pDoc->BattleStart = 2;
					SetTimer(3, 100, NULL);
				}
			}//승리시//포획
			if (pDoc->MonsterStat.iHp < 1)
			{
				if (CreateM == 5)
				{
					pDoc->ENDING = true;
					SetTimer(3, 100, NULL);
				}
				else
				{
					int iRandGold = rand() % 10 + 30;
					int iExp = rand() % 3 + 5;
					CString GOLD;
					GOLD.Format(_T("%d"), iRandGold);
					CString Exp;
					Exp.Format(_T("%d"), iExp);
					pDoc->Battle = false;
					MessageBox(GOLD + _T("골드 획득!") + Exp + _T("경험치 획득"), L"전투 승리!", MB_OK);
					pDoc->POKEDEX[pDoc->Pkbattle].iExp += iExp;
					pDoc->iGold += iRandGold;
					if (pDoc->POKEDEX[pDoc->Pkbattle].iExp > pDoc->POKEDEX[pDoc->Pkbattle].iLevel * 5)
					{
						pDoc->POKEDEX[pDoc->Pkbattle].iLevel++;
						pDoc->POKEDEX[pDoc->Pkbattle].iMaxHp += 5;
						pDoc->POKEDEX[pDoc->Pkbattle].iHp = pDoc->POKEDEX[pDoc->Pkbattle].iMaxHp;
						pDoc->POKEDEX[pDoc->Pkbattle].iExp = 0;
						pDoc->POKEDEX[pDoc->Pkbattle].iAtt += 2;
						MessageBox(pDoc->POKEDEX[pDoc->Pkbattle].Name + _T(" 레벨업했다!"), L"전투 승리!", MB_OK);
					}
					Bite = 0;
					CBite = 0;
					MusicMode = 0;
					pDoc->Select = 0;
					MusicBattle = false;
					pDoc->BattleStart = 0;
					SetTimer(3, 1000, NULL);
				}
			}
			else if (pDoc->POKEDEX[pDoc->Pkbattle].iHp < 1)
			{
				if ((pDoc->Pkbattle > pDoc->PKNum) || (pDoc->PKNum == 0))//가지고있는 수보다적다면
				{
					pDoc->Battle = false;
					MessageBox(_T("패배!"), L"메시지", MB_OK);
					for (int i = 0; i < pDoc->POKEDEX.GetSize(); i++)
						pDoc->POKEDEX[i].iHp = pDoc->POKEDEX[i].iMaxHp;

					pDoc->CharPos_x = 210;
					pDoc->CharPos_y = 360;
					pDoc->iGold = 0;
					MusicMode = 0;
					pDoc->Select = 0;
					MusicBattle = false;
					SetTimer(3, 1000, NULL);
					//처음으로 돌아간다.
				}
				else
					pDoc->Pkbattle++;
			}
		}
	}
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CBhzzangView 진단

#ifdef _DEBUG
void CBhzzangView::AssertValid() const
{
	CView::AssertValid();
}

void CBhzzangView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBhzzangDoc* CBhzzangView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBhzzangDoc)));
	return (CBhzzangDoc*)m_pDocument;
}
#endif //_DEBUG


// CBhzzangView 메시지 처리기


void CBhzzangView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);
	ReleaseCapture();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


void CBhzzangView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CBhzzangDoc* pDoc = (CBhzzangDoc*)GetDocument();
	if (pDoc->TUTORIAL == 0)
	{
		if (!pDoc->Battle)
		{
			InHuntingRgn();
			if ((pDoc->CharPos_x == 745) && (pDoc->CharPos_y == 340) && (pDoc->CharDirect = 5))
			{
				switch (nChar)
				{
				case VK_RETURN:pDoc->BOSS = true; pDoc->TUTORIAL = -1; Invalidate(); break;
				}
			}
			if ((pDoc->CharPos_x == 515) && (pDoc->CharPos_y >= 350) && (pDoc->CharPos_y <= 360) && (pDoc->CharDirect == 5))
			{
				switch (nChar)
				{
				case VK_RETURN: pDoc->GUMAE = true; break;
				}
			}
			if ((pDoc->CharPos_x >= 795) && (pDoc->CharPos_x <= 805) && (pDoc->CharPos_y == 155) && (pDoc->CharDirect == 3))
			{
				switch (nChar)
				{
				case VK_RETURN: pDoc->CENTER = true; Invalidate(); break;
				}
			}
			if (!pDoc->GUMAE&&MusicMode!=2)
			{
				switch (nChar)
				{
				case VK_LEFT:
					pDoc->CharPos_x -= 5;
					pDoc->CharDirect = 6;
					Invalidate();
					SetTimer(0, 200, NULL);
					break;
				case VK_RIGHT:
					pDoc->CharPos_x += 5;
					pDoc->CharDirect = 8;
					Invalidate();
					SetTimer(0, 200, NULL);
					break;
				case VK_DOWN:
					pDoc->CharPos_y += 5;
					pDoc->CharDirect = 2;
					Invalidate();
					SetTimer(0, 200, NULL);
					break;
				case VK_UP:
					pDoc->CharPos_y -= 5;
					pDoc->CharDirect = 4;
					Invalidate();
					SetTimer(0, 200, NULL);
					break;
				}
			}
			else if (pDoc->GUMAE)
			{
				if (pDoc->ShopSelect == 0)
				{
					switch (nChar)
					{
					case VK_LEFT: pDoc->ShopSelect = 2; break;
					case VK_RIGHT: pDoc->ShopSelect = 1; break;
					}
					if (pDoc->iGold >= 100)
					{
						switch (nChar)
						{
						case VK_UP: pDoc->Ball++; pDoc->iGold -= 100; break;
						}
					}
					if (pDoc->Ball > 0)
					{
						switch (nChar)
						{
						case VK_DOWN: pDoc->Ball--; pDoc->iGold += 100; break;
						}
					}
				}
				else if (pDoc->ShopSelect == 1)
				{
					switch (nChar)
					{
					case VK_LEFT: pDoc->ShopSelect = 0; break;
					case VK_RIGHT: pDoc->ShopSelect = 2; break;
					}
					if (pDoc->iGold >= 50)
					{
						switch (nChar)
						{
						case VK_UP: pDoc->Potion++; pDoc->iGold -= 50; break;
						}
					}
					if (pDoc->Potion > 0)
					{
						switch (nChar)
						{
						case VK_DOWN: pDoc->Potion--; pDoc->iGold += 50; break;
						}
					}
				}
				else if (pDoc->ShopSelect == 2)
				{
					switch (nChar)
					{
					case VK_LEFT: pDoc->ShopSelect = 1; break;
					case VK_RIGHT: pDoc->ShopSelect = 0; break;
					case VK_RETURN: pDoc->ShopSelect = 0; pDoc->CharPos_x += 5; pDoc->GUMAE = false; break;
					}
				}
				SetTimer(3, 100, NULL);
			}
		}
		else if (pDoc->Battle&&pDoc->BattleStart == 0)
		{
			if (pDoc->Select == 0)
			{
				if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("피카츄"))
				{
					switch (nChar)
					{
					case VK_LEFT:pDoc->Select = 3; break;
					case VK_RIGHT:pDoc->Select = 2; break;
					case VK_DOWN:pDoc->Select = 1; break;
					case VK_UP:pDoc->Select = 1; break;
					case VK_RETURN:pDoc->BattleStart = 1; P_Momtong = 210; Invalidate(); break;
					}
				}
				else if(!(pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("피카츄")))
				{
					switch (nChar)
					{
					case VK_LEFT:pDoc->Select = 4; break;
					case VK_RIGHT:pDoc->Select = 2; break;
					case VK_DOWN:pDoc->Select = 1; break;
					case VK_UP:pDoc->Select = 1; break;
					case VK_RETURN:pDoc->BattleStart = 1; Momtong = 240; Invalidate(); break;
					}
				}
			}
			else if (pDoc->Select == 1)
			{
				switch (nChar)
				{
				case VK_LEFT:pDoc->Select = 4; break;
				case VK_RIGHT:pDoc->Select = 3; break;
				case VK_DOWN:pDoc->Select = 0; break;
				case VK_UP:pDoc->Select = 0; break;
				case VK_RETURN:pDoc->BattleStart = 1; SelectSkill2(); break;
				}
			}
			else if (pDoc->Select == 2)
			{
				switch (nChar)
				{
				case VK_LEFT:pDoc->Select = 0; break;
				case VK_RIGHT:pDoc->Select = 4; break;
				case VK_DOWN:pDoc->Select = 3; break;
				case VK_UP:pDoc->Select = 3; break;
				case VK_RETURN:SelectBall(); break;
				}
			}
			else if (pDoc->Select == 3)
			{
				switch (nChar)
				{
				case VK_LEFT:pDoc->Select = 1; break;
				case VK_RIGHT:pDoc->Select = 4; break;
				case VK_DOWN:pDoc->Select = 2; break;
				case VK_UP:pDoc->Select = 2; break;
				case VK_RETURN:SelectPotion(); break;
				}
			}
			else if (pDoc->Select == 4)
			{
				switch (nChar)
				{
				case VK_LEFT:pDoc->Select = 2; break;
				case VK_RIGHT:pDoc->Select = 0; break;
				case VK_RETURN:SelectRun(); break;
				}
			}
		}
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}



void CBhzzangView::OnTimer(UINT_PTR nIDEvent)
{
	CBhzzangDoc* pDoc = (CBhzzangDoc*)GetDocument();
	
	if ((nIDEvent == 0)&&(!pDoc->Battle)) {	// 평소 움직임
		KillTimer(0); 
		if (pDoc->CharDirect == 2)
			pDoc->CharDirect = 1;
		if (pDoc->CharDirect == 8)
			pDoc->CharDirect = 7;
		if (pDoc->CharDirect == 6)
			pDoc->CharDirect = 5;
		if (pDoc->CharDirect == 4)
			pDoc->CharDirect = 3; 
		if ((pDoc->CharPos_x == 505) && (pDoc->CharPos_y == 210))
		{
			MusicMode = 2;
			pDoc->CharPos_x = 80;
			pDoc->CharPos_y = 155;
		}
			else if ((pDoc->CharPos_x == 80) && (pDoc->CharPos_y == 150))
			{
				MusicMode = 2;
				pDoc->CharPos_x = 505;
				pDoc->CharPos_y = 205;
			}
			else if ((pDoc->CharPos_x == 210) && (pDoc->CharPos_y == 355))
			{
				MusicMode = 2;
				pDoc->CharPos_x = 800;
				pDoc->CharPos_y = 220;
			}
			else if ((pDoc->CharPos_x == 800) && (pDoc->CharPos_y == 225))
			{
				MusicMode = 2;
				pDoc->CharPos_x = 210;
				pDoc->CharPos_y = 360;
			}
			else if ((pDoc->CharPos_x == 210) && (pDoc->CharPos_y == 275))
			{
				MusicMode = 2;
				pDoc->CharPos_x = 515;
				pDoc->CharPos_y = 405;
			}
			else if ((pDoc->CharPos_x == 515) && (pDoc->CharPos_y == 410))
			{
				MusicMode = 2;
				pDoc->CharPos_x = 210;
				pDoc->CharPos_y = 280;
			}
			else if ((pDoc->CharPos_x == 225) && (pDoc->CharPos_y == 130))
			{
				MusicMode = 2;
				pDoc->CharPos_x = 875;
				pDoc->CharPos_y = 320;
			}
			else if ((pDoc->CharPos_x == 875) && (pDoc->CharPos_y == 315))
			{
				MusicMode = 2;
				pDoc->CharPos_x = 225;
				pDoc->CharPos_y = 135;
			}
		pDoc->GUMAE = false;
	}
	else if ((nIDEvent == 1)&&(!pDoc->Battle))	// 사냥터에 있을 시 배틀
	{
		if (((pDoc->CharPos_x) >= -10) && ((pDoc->CharPos_x) <= 65) && ((pDoc->CharPos_y) >= 235) && ((pDoc->CharPos_y) <= 350))
		{
			KillTimer(1);
			pDoc->Battle = true;
			pDoc->BattleStart = 0;
			pDoc->Select = 0;
			pDoc->Pkbattle = 0;
		}
	}
	else if ((nIDEvent == 2) && (pDoc->Battle)) // 몸통 박치기 연출
	{
		KillTimer(2);
		Momtong -= 15;
	}
	else if ((nIDEvent == 3) && (pDoc->Battle))
	{
		KillTimer(3);
	}
	else if ((nIDEvent == 4) && (pDoc->Battle))
	{
		KillTimer(4);
		P_Momtong -= 25;
	}
	else if ((nIDEvent == 5) && (pDoc->Battle))
	{
		KillTimer(5);
		Leaf_pos -= 21;
	}
	else if ((nIDEvent == 6) && (pDoc->Battle))
	{
		KillTimer(6);
		Bite = 1;
		Invalidate();
	}
	else if ((nIDEvent == 7) && (pDoc->Battle))
	{
		KillTimer(7);
		Bite = 2;
		Invalidate();
	}
	else if ((nIDEvent == 8) && (pDoc->Battle))
	{
		KillTimer(8);
		Leaf_pos += 21;
	}
	else if ((nIDEvent == 9) && (pDoc->Battle))
	{
		KillTimer(9);
		P_Momtong += 25;
	}
	else if ((nIDEvent == 10) && (pDoc->Battle))
	{
		KillTimer(10);
		Momtong += 15;
	}
	else if ((nIDEvent == 11) && (pDoc->Battle))
	{
		KillTimer(11);
		CBite = 1;
		Invalidate();
	}
	else if ((nIDEvent == 12) && (pDoc->Battle))
	{
		KillTimer(12);
		CBite = 2;
		Invalidate();
	}
	Invalidate();
	
	CView::OnTimer(nIDEvent);
}

void CBhzzangView::InHuntingRgn()
{
	CBhzzangDoc* pDoc = (CBhzzangDoc*)GetDocument();
	if (((pDoc->CharPos_x) >= -10) && ((pDoc->CharPos_x) <= 65) && ((pDoc->CharPos_y) >= 235) && ((pDoc->CharPos_y) <= 350) && (!pDoc->Battle))
	{
		SetTimer(1, 500, NULL);
	}
}

void CBhzzangView::SelectBall()
{
	CBhzzangDoc* pDoc = (CBhzzangDoc*)GetDocument();
	if (pDoc->Ball > 0)
	{
		MessageBox(_T("몬스터 볼을 던졌다...."), L"몬스터 볼", MB_OK);
		Throw = 1;
		pDoc->Ball--;
		pDoc->BattleStart = 1;
	}
	else
	{
		Throw = 0; 
		MessageBox(_T("몬스터 볼이 없습니다!"), L"몬스터 볼", MB_OK);
		pDoc->BattleStart = 2;
	}
	SetTimer(3, 200, NULL);
}

void CBhzzangView::SelectPotion()
{
	CBhzzangDoc* pDoc = (CBhzzangDoc*)GetDocument();
	if (pDoc->Potion > 0)
	{
		pDoc->POKEDEX[pDoc->Pkbattle].iHp = pDoc->POKEDEX[pDoc->Pkbattle].iMaxHp;
		pDoc->Potion--;
		MessageBox(pDoc->POKEDEX[pDoc->Pkbattle].Name + _T(" 체력이 회복되었다!"), L"포션", MB_OK);
	}
	else
		MessageBox(_T("포션이 없습니다!"), L"포션", MB_OK);
}

void CBhzzangView::SelectRun()
{
	CBhzzangDoc* pDoc = (CBhzzangDoc*)GetDocument();
	int RunOrFail = rand() % 4;
	if (RunOrFail)
	{
		MessageBox(_T("성공!"), L" 도망", MB_OK);
		pDoc->Battle = false;
		MusicBattle = false;
		MusicMode = 0;
		pDoc->BattleStart = 0;
		Invalidate();
	}
	else
	{	MessageBox(_T("실패!"), L" 도망", MB_OK); 
		pDoc->BattleStart = 2;
		MonsterMove = 1;
		Invalidate();
	}
}

void CBhzzangView::SelectSkill2()
{
	CBhzzangDoc* pDoc = (CBhzzangDoc*)GetDocument();
	if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("이상해씨"))
		Skill = 1;
	else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("가디"))
		Skill = 2;
	else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("꼬부기"))
		Skill = 3;
	else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("파이리"))
		Skill = 4;
	else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("피카츄"))
		Skill = 5;
	Invalidate();
}

void CBhzzangView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CBhzzangDoc* pDoc = (CBhzzangDoc*)GetDocument();
	CClientDC dc(this);
	if (pDoc->TUTORIAL == 1)
	{
		if ((point.x <= 300) && (point.x >= 150) && (point.y <= 70) && (point.y >= 40))
		{
			pDoc->TUTORIAL = 2;
			Invalidate();
		}

	}
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);
}
