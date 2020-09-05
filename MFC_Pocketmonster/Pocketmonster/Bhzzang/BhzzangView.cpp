
// BhzzangView.cpp : CBhzzangView Ŭ������ ����



#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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

// CBhzzangView ����/�Ҹ�

CBhzzangView::CBhzzangView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
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
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS, ::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return CView::PreCreateWindow(cs);
}

// CBhzzangView �׸���

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
			if (CreateM == 0) // �̻��ؾ�
			{
				pDoc->MonsterStat.Name.Format(_T("�̻��ؾ�"));
				pDoc->MonsterStat.Skill1.Format(_T("�����ġ��"));
				pDoc->MonsterStat.Skiil2.Format(_T("�ٳ�������"));
				pDoc->MonsterStat.iAtt = 4;
				pDoc->MonsterStat.iHp = 20;
				pDoc->MonsterStat.iMaxHp = 20;
				pDoc->MonsterStat.iLevel = 3;
				pDoc->MonsterStat.iExp = 0;
			}
			else if (CreateM == 1)
			{
				pDoc->MonsterStat.Name.Format(_T("����"));
				pDoc->MonsterStat.Skill1.Format(_T("�����ġ��"));
				pDoc->MonsterStat.Skiil2.Format(_T("����"));
				pDoc->MonsterStat.iAtt = 3;
				pDoc->MonsterStat.iHp = 24;
				pDoc->MonsterStat.iMaxHp = 24;
				pDoc->MonsterStat.iLevel = 3;
				pDoc->MonsterStat.iExp = 0;
			} // ����
			else if (CreateM == 2)
			{
				pDoc->MonsterStat.Name.Format(_T("���α�"));
				pDoc->MonsterStat.Skill1.Format(_T("�����ġ��"));
				pDoc->MonsterStat.Skiil2.Format(_T("�ĵ�Ÿ��"));
				pDoc->MonsterStat.iAtt = 2;
				pDoc->MonsterStat.iHp = 40;
				pDoc->MonsterStat.iMaxHp = 40;
				pDoc->MonsterStat.iLevel = 3;
				pDoc->MonsterStat.iExp = 0;
			}
			else if (CreateM == 3)
			{
				pDoc->MonsterStat.Name.Format(_T("���̸�"));
				pDoc->MonsterStat.Skill1.Format(_T("�����ġ��"));
				pDoc->MonsterStat.Skiil2.Format(_T("�Ҳ� �߻�"));
				pDoc->MonsterStat.iAtt = 5;
				pDoc->MonsterStat.iHp = 15;
				pDoc->MonsterStat.iMaxHp = 15;
				pDoc->MonsterStat.iLevel = 3;
				pDoc->MonsterStat.iExp = 0;
			}//���̸�
			else if (CreateM == 4)
			{
				pDoc->MonsterStat.Name.Format(_T("��ī��"));
				pDoc->MonsterStat.Skill1.Format(_T("������ȭ"));
				pDoc->MonsterStat.Skiil2.Format(_T("���� ���"));
				pDoc->MonsterStat.iAtt = 5;
				pDoc->MonsterStat.iHp = 18;
				pDoc->MonsterStat.iMaxHp = 18;
				pDoc->MonsterStat.iLevel = 3;
				pDoc->MonsterStat.iExp = 0;
			}
			else if (CreateM == 5)
			{
				pDoc->MonsterStat.Name.Format(_T("����"));
				pDoc->MonsterStat.Skill1.Format(_T("ȭ�� ���"));
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
				MessageBox(_T("��� ���ϸ��� ü���� ȸ���Ǿ���!"), L"���ϸ� ����", MB_OK);
				SetTimer(3, 100, NULL);
			}
		}
		else if (pDoc->Battle)
		{
			if (!MusicBattle)
			{
				MusicBattle = true;
				PlaySound(_T("../������.wav"), NULL, SND_ASYNC|SND_LOOP);
			}
			CBitmap MyPkBit;
			CBitmap ComPkBit;
			CBitmap BattleMapBit;
			CBitmap Speed;
			Speed.LoadBitmapW(IDB_SPEED);
			if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("�̻��ؾ�"))
				MyPkBit.LoadBitmap(IDB_MYISANG);
			else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("����"))
				MyPkBit.LoadBitmap(IDB_MYGADI);
			else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("���α�"))
				MyPkBit.LoadBitmap(IDB_MYSQUIT);
			else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("���̸�"))
				MyPkBit.LoadBitmap(IDB_MYFIRI);
			else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("��ī��"))
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
			/*���� ����
			�̻��ؾ�, ����, ��ī��, ���̸�, ���α�
			//////////////////////////////////////////*/

			if (pDoc->BattleStart == 0)
			{
				pDC->TransparentBlt(193, 280, (MyPkinfo.bmWidth + 10), (MyPkinfo.bmHeight + 10), &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
				if (CreateM == 0) // �̻��ؾ�
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

				} // ����
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
				}//���̸�
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
			/*���� ����*/
			else if (pDoc->BattleStart == 1)
			{
				MonsterMove = 1;
				if (CreateM == 0) // �̻��ؾ�
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
				} // ����
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
				}//���̸�
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
				if (pDoc->POKEDEX[pDoc->Pkbattle].Name==_T("��ī��") && P_Momtong)
				{
					CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
					pDC->SelectObject(&Text);
					pDC->SetBkMode(TRANSPARENT);
					pDC->TextOutW(180, 150, _T("������ȭ!"));
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
					pDC->TextOutW(180, 150, _T("�����ġ��!"));

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
						pDC->TextOutW(180, 150, _T("�ٳ�������!"));
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
						//����ä��
					}
					else if (Skill == 2)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("����!!"));
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
						//���¢��
					}
					else if (Skill == 3)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("�ĵ�Ÿ��!"));
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

						//�ĵ�Ÿ��
					}
					else if (Skill == 4)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("ȭ�����!"));
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
						//ȭ�����
					}
					else if (Skill == 5)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("����!"));
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
						//���¢��
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
			}//����
			else if (pDoc->BattleStart == 2)
			{
				MyPkBit.GetBitmap(&MyPkinfo);
				dcmem.SelectObject(&MyPkBit);
				pDC->TransparentBlt(193, 280, (MyPkinfo.bmWidth + 10), (MyPkinfo.bmHeight + 10), &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
				if (CreateM == 0) // �̻��ؾ�
					ComPkBit.LoadBitmap(IDB_COMISANG);
				else if (CreateM == 1)
					ComPkBit.LoadBitmap(IDB_COMGADI);
				else if (CreateM == 2)
					ComPkBit.LoadBitmap(IDB_COMSQUIT);
				else if (CreateM == 3)
					ComPkBit.LoadBitmap(IDB_COMFIRI);
				//���̸�
				else if (CreateM == 4)
					ComPkBit.LoadBitmap(IDB_COMPIKA);
				else if (CreateM == 5)
					ComPkBit.LoadBitmap(IDB_WENDY);
				if (MonsterMove == 1)
				{
					ComPkBit.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPkBit);
					if (CreateM == 0) // �̻��ؾ�
						pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth+10, ComPkinfo.bmHeight+10, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 1)
						pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 2)
						pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 3)
						pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));//���̸�
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
					if (pDoc->MonsterStat.Name == _T("��ī��"))
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("������ȭ!"));
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
						pDC->TextOutW(180, 150, _T("ȭ�����!"));
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
						pDC->TextOutW(180, 150, _T("�����ġ��!"));
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
						pDC->TextOutW(180, 150, _T("�ٳ�������!"));
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
						pDC->TextOutW(180, 150, _T("����!!"));
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
						pDC->TextOutW(180, 150, _T("�ĵ�Ÿ��!"));
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
						pDC->TextOutW(180, 150, _T("ȭ�����!"));
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
						//ȭ�����
					}
					else if (CreateM == 4)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("����!"));
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
						//���¢��
					}
					else if (CreateM == 5)
					{
						CPen Text(PS_SOLID, 10, RGB(0, 0, 0));
						pDC->SelectObject(&Text);
						pDC->SetBkMode(TRANSPARENT);
						pDC->TextOutW(180, 150, _T("ȭ�����!"));
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
					if (CreateM == 0) // �̻��ؾ�
						pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth + 10, ComPkinfo.bmHeight + 10, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 1)
						pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 2)
						pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 3)
						pDC->TransparentBlt(193, 10, (ComPkinfo.bmWidth )*2, (ComPkinfo.bmHeight)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));//���̸�
					else if (CreateM == 4)
						pDC->TransparentBlt(193, 10, ComPkinfo.bmWidth, ComPkinfo.bmHeight, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
					else if (CreateM == 5)
						pDC->TransparentBlt(186, 6, (ComPkinfo.bmWidth)*2, (ComPkinfo.bmHeight + 10)*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));//���̸�
					Momtong = 0;
					P_Momtong = 0;
				}
				
			}//��ǻ����
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
					MessageBox(_T("���� �� �����ϴ�!"), L"���� ��", MB_OK | MB_ICONQUESTION);
					pDoc->BattleStart = 2;
					SetTimer(3, 100, NULL);
				}
				else if (SuccessOrFail <2)
				{
					if (pDoc->PKNum > 2)
					{
						MessageBox(_T("���� �� �ִ� ���� �ʰ�!"), L"���� ��", MB_OK | MB_ICONQUESTION);
						pDoc->BattleStart = 2;
						SetTimer(3, 100, NULL);
					}
					else {
						MessageBox(_T("��ȹ ����!"), L"���� ��", MB_OK | MB_ICONQUESTION);
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
					MessageBox(_T("��ȹ ����!"), L"���� ��", MB_OK | MB_ICONQUESTION);
					pDoc->BattleStart = 2;
					SetTimer(3, 100, NULL);
				}
			}//�¸���//��ȹ
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
					MessageBox(GOLD + _T("��� ȹ��!") + Exp + _T("����ġ ȹ��"), L"���� �¸�!", MB_OK);
					pDoc->POKEDEX[pDoc->Pkbattle].iExp += iExp;
					pDoc->iGold += iRandGold;
					if (pDoc->POKEDEX[pDoc->Pkbattle].iExp > pDoc->POKEDEX[pDoc->Pkbattle].iLevel * 5)
					{
						pDoc->POKEDEX[pDoc->Pkbattle].iLevel++;
						pDoc->POKEDEX[pDoc->Pkbattle].iMaxHp += 5;
						pDoc->POKEDEX[pDoc->Pkbattle].iHp = pDoc->POKEDEX[pDoc->Pkbattle].iMaxHp;
						pDoc->POKEDEX[pDoc->Pkbattle].iExp = 0;
						pDoc->POKEDEX[pDoc->Pkbattle].iAtt += 2;
						MessageBox(pDoc->POKEDEX[pDoc->Pkbattle].Name + _T(" �������ߴ�!"), L"���� �¸�!", MB_OK);
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
				if ((pDoc->Pkbattle > pDoc->PKNum) || (pDoc->PKNum == 0))//�������ִ� ���������ٸ�
				{
					pDoc->Battle = false;
					MessageBox(_T("�й�!"), L"�޽���", MB_OK);
					for (int i = 0; i < pDoc->POKEDEX.GetSize(); i++)
						pDoc->POKEDEX[i].iHp = pDoc->POKEDEX[i].iMaxHp;

					pDoc->CharPos_x = 210;
					pDoc->CharPos_y = 360;
					pDoc->iGold = 0;
					MusicMode = 0;
					pDoc->Select = 0;
					MusicBattle = false;
					SetTimer(3, 1000, NULL);
					//ó������ ���ư���.
				}
				else
					pDoc->Pkbattle++;
			}
		}
	}
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CBhzzangView ����

#ifdef _DEBUG
void CBhzzangView::AssertValid() const
{
	CView::AssertValid();
}

void CBhzzangView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBhzzangDoc* CBhzzangView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBhzzangDoc)));
	return (CBhzzangDoc*)m_pDocument;
}
#endif //_DEBUG


// CBhzzangView �޽��� ó����


void CBhzzangView::OnKillFocus(CWnd* pNewWnd)
{
	CView::OnKillFocus(pNewWnd);
	ReleaseCapture();
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CBhzzangView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
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
				if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("��ī��"))
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
				else if(!(pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("��ī��")))
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
	
	if ((nIDEvent == 0)&&(!pDoc->Battle)) {	// ��� ������
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
	else if ((nIDEvent == 1)&&(!pDoc->Battle))	// ����Ϳ� ���� �� ��Ʋ
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
	else if ((nIDEvent == 2) && (pDoc->Battle)) // ���� ��ġ�� ����
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
		MessageBox(_T("���� ���� ������...."), L"���� ��", MB_OK);
		Throw = 1;
		pDoc->Ball--;
		pDoc->BattleStart = 1;
	}
	else
	{
		Throw = 0; 
		MessageBox(_T("���� ���� �����ϴ�!"), L"���� ��", MB_OK);
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
		MessageBox(pDoc->POKEDEX[pDoc->Pkbattle].Name + _T(" ü���� ȸ���Ǿ���!"), L"����", MB_OK);
	}
	else
		MessageBox(_T("������ �����ϴ�!"), L"����", MB_OK);
}

void CBhzzangView::SelectRun()
{
	CBhzzangDoc* pDoc = (CBhzzangDoc*)GetDocument();
	int RunOrFail = rand() % 4;
	if (RunOrFail)
	{
		MessageBox(_T("����!"), L" ����", MB_OK);
		pDoc->Battle = false;
		MusicBattle = false;
		MusicMode = 0;
		pDoc->BattleStart = 0;
		Invalidate();
	}
	else
	{	MessageBox(_T("����!"), L" ����", MB_OK); 
		pDoc->BattleStart = 2;
		MonsterMove = 1;
		Invalidate();
	}
}

void CBhzzangView::SelectSkill2()
{
	CBhzzangDoc* pDoc = (CBhzzangDoc*)GetDocument();
	if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("�̻��ؾ�"))
		Skill = 1;
	else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("����"))
		Skill = 2;
	else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("���α�"))
		Skill = 3;
	else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("���̸�"))
		Skill = 4;
	else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("��ī��"))
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CView::OnLButtonDown(nFlags, point);
}
