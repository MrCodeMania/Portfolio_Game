// InfoView.cpp : ���� �����Դϴ�.
//

#include <conio.h>
#include "stdafx.h"
#include "Bhzzang.h"
#include "InfoView.h"
#include "BhzzangDoc.h"
#include "BhzzangView.h"
// CInfoView

IMPLEMENT_DYNCREATE(CInfoView, CView)

CInfoView::CInfoView()
{
}

CInfoView::~CInfoView()
{
}

BEGIN_MESSAGE_MAP(CInfoView, CView)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CInfoView �׸����Դϴ�.

void CInfoView::OnDraw(CDC* pDC)
{
	CBhzzangDoc* pDoc = (CBhzzangDoc*)GetDocument();
	CBrush HP(RGB(255, 0, 0));
	CBrush WhiteRect(RGB(255, 255, 255));
	CPen Text(PS_SOLID, 3, RGB(0, 0, 0));
	if (pDoc->TUTORIAL == 1)
		SetTimer(2, 500, NULL);
	if (pDoc->TUTORIAL > 1)
	{
		if (pDoc->TUTORIAL == 2)
		{
			pDC->SelectObject(&Text);
			pDC->TextOutW(10,70, _T("�Ҿƹ��� : ����� �� ���� �־��ܴ�"));
			pDoc->TUTORIAL++;
		}
		else if (pDoc->TUTORIAL == 3)
		{
			pDC->SelectObject(&Text);
			pDC->TextOutW(10,70, _T("���� : �Ҿƹ���, ���� ���� 15���̿���!"));
			pDoc->TUTORIAL++;
		}
		else if (pDoc->TUTORIAL == 4)
		{
			pDC->SelectObject(&Text);
			pDC->TextOutW(10,70, _T("���� : � ���� ������ ������ �ʹٰ��!"));
			pDoc->TUTORIAL++;
		}
		else if (pDoc->TUTORIAL == 5)
		{
			pDC->SelectObject(&Text);
			pDC->TextOutW(10,70, _T("�Ҿƹ��� : ���� ���ϸ� ������ �ؼ� �̱�� ������ָ�!"));
			pDoc->TUTORIAL++;
		}
		else if (pDoc->TUTORIAL == 6)
		{
			pDC->SelectObject(&Text);
			pDC->TextOutW(10,70, _T("���� : ��? ��¥��? �Ҿƹ��� �ݹ� �̰ܵ帮��!"));
			pDoc->TUTORIAL++;
		}
		else if (pDoc->TUTORIAL == 7)
		{
			pDC->SelectObject(&Text);
			pDC->TextOutW(10,70, _T("�Ҿƹ��� : ������"));
			pDoc->TUTORIAL++;
		}
		else if (pDoc->TUTORIAL == 8)
		{
			pDC->SelectObject(&Text);
			pDC->TextOutW(10, 70, _T("���� : ����! ��ī��!"));
			pDoc->TUTORIAL++;
		}
		else if (pDoc->TUTORIAL == 9)
		{
			pDoc->TUTORIAL = 0;
		}
		SetTimer(2, 2000, NULL);
	}
	if (pDoc->BOSS)
	{
		pDC->SelectObject(&Text);
		pDC->TextOutW(10, 70, _T("�Ҿƹ��� : �Ա���.. ���� ����!"));
		pDoc->TUTORIAL = 0;
		pDoc->BattleStart = 0;
		pDoc->Select = 0;
		pDoc->BOSS = false;
		SetTimer(2, 2500, NULL);
	}
	else if (pDoc->ENDING)
	{
		pDC->SelectObject(&Text);
		pDC->TextOutW(10, 70, _T("�Ҿƹ��� : ���� ���� ���� �Ǳ���~"));
		SetTimer(2, 5000, NULL);
	}
	else if(pDoc->TUTORIAL ==0)
	{
		if (!pDoc->Battle)
		{
			if (!pDoc->GUMAE)
			{
				pDC->SelectObject(Text);
				pDC->MoveTo(0, 75);
				pDC->LineTo(450, 75);
				pDC->MoveTo(215, 0);
				pDC->LineTo(215, 233);
				/*���� ���� ��� if��*/
				if (pDoc->POKEDEX.GetSize() > 0)
				{
					CString Temp;
					CBitmap PokePicture;
					BITMAP MyPkinfo;
					CDC dcmem;
					dcmem.CreateCompatibleDC(pDC);
					if (pDoc->POKEDEX[0].Name == _T("�̻��ؾ�"))
					{
						PokePicture.LoadBitmap(IDB_COMISANG);
						PokePicture.GetBitmap(&MyPkinfo);
						dcmem.SelectObject(&PokePicture);
						pDC->TransparentBlt(25, 20, MyPkinfo.bmWidth, MyPkinfo.bmHeight, &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
					}
					else if (pDoc->POKEDEX[0].Name == _T("����"))
					{
						PokePicture.LoadBitmap(IDB_COMGADI);
						PokePicture.GetBitmap(&MyPkinfo);
						dcmem.SelectObject(&PokePicture);
						pDC->TransparentBlt(25, 20, MyPkinfo.bmWidth * 2, MyPkinfo.bmHeight * 2, &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
					}
					else if (pDoc->POKEDEX[0].Name == _T("���α�"))
					{
						PokePicture.LoadBitmap(IDB_COMSQUIT);
						PokePicture.GetBitmap(&MyPkinfo);
						dcmem.SelectObject(&PokePicture);
						pDC->TransparentBlt(25, 20, MyPkinfo.bmWidth * 2, MyPkinfo.bmHeight * 2, &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
					}
					else if (pDoc->POKEDEX[0].Name == _T("���̸�"))
					{
						PokePicture.LoadBitmap(IDB_COMFIRI);
						PokePicture.GetBitmap(&MyPkinfo);
						dcmem.SelectObject(&PokePicture);
						pDC->TransparentBlt(25, 20, MyPkinfo.bmWidth * 2, MyPkinfo.bmHeight * 2, &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
					}
					else if (pDoc->POKEDEX[0].Name == _T("��ī��"))
					{
						PokePicture.LoadBitmap(IDB_COMPIKA);
						PokePicture.GetBitmap(&MyPkinfo);
						dcmem.SelectObject(&PokePicture);
						pDC->TransparentBlt(25, 20, MyPkinfo.bmWidth, MyPkinfo.bmHeight, &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
					}
					
					double Hp1 = pDoc->POKEDEX[0].iMaxHp / 10;
					pDC->TextOut(95, 5, pDoc->POKEDEX[0].Name);
					Temp.Format(_T("%d"), pDoc->POKEDEX[0].iLevel);
					pDC->TextOut(95, 20, _T("LEVEL : " + Temp));
					Temp.Format(_T("%d"), pDoc->POKEDEX[0].iHp);
					pDC->TextOut(90, 35, _T("HP  " + Temp));
					Temp.Format(_T("%d"), pDoc->POKEDEX[0].iMaxHp);
					pDC->TextOut(135, 35, _T("  /   " + Temp));
					pDC->SelectObject(Text);
					pDC->Rectangle(90, 55, 170, 65);
					pDC->FillRect(CRect(90, 55, 170, 65), &WhiteRect);
					pDC->SelectObject(HP);
					for (int iIndex = 0; iIndex < 11; iIndex++)
					{
						if (Hp1*iIndex <= pDoc->POKEDEX[0].iHp)
							pDC->Rectangle(90, 55, 90 + (8 * iIndex), 65);
						else break;
					}
					if (pDoc->POKEDEX.GetSize() > 1)
					{
						CBitmap PokePicture1;
						BITMAP MyPkinfo1;
						if (pDoc->POKEDEX[1].Name == _T("�̻��ؾ�"))
						{
							PokePicture1.LoadBitmap(IDB_COMISANG);
							PokePicture1.GetBitmap(&MyPkinfo1);
							dcmem.SelectObject(&PokePicture1);
							pDC->TransparentBlt(250, 20, MyPkinfo1.bmWidth, MyPkinfo1.bmHeight, &dcmem, 0, 0, MyPkinfo1.bmWidth, MyPkinfo1.bmHeight, RGB(255, 255, 255));
						}
						else if (pDoc->POKEDEX[1].Name == _T("����"))
						{
							PokePicture1.LoadBitmap(IDB_COMGADI);
							PokePicture1.GetBitmap(&MyPkinfo1);
							dcmem.SelectObject(&PokePicture1);
							pDC->TransparentBlt(250, 20, MyPkinfo1.bmWidth * 2, MyPkinfo1.bmHeight * 2, &dcmem, 0, 0, MyPkinfo1.bmWidth, MyPkinfo1.bmHeight, RGB(255, 255, 255));
						}
						else if (pDoc->POKEDEX[1].Name == _T("���α�"))
						{
							PokePicture1.LoadBitmap(IDB_COMSQUIT);
							PokePicture1.GetBitmap(&MyPkinfo1);
							dcmem.SelectObject(&PokePicture1);
							pDC->TransparentBlt(250, 20, MyPkinfo1.bmWidth * 2, MyPkinfo1.bmHeight * 2, &dcmem, 0, 0, MyPkinfo1.bmWidth, MyPkinfo1.bmHeight, RGB(255, 255, 255));
						}
						else if (pDoc->POKEDEX[1].Name == _T("���̸�"))
						{
							PokePicture1.LoadBitmap(IDB_COMFIRI);
							PokePicture1.GetBitmap(&MyPkinfo1);
							dcmem.SelectObject(&PokePicture1);
							pDC->TransparentBlt(250, 20, MyPkinfo1.bmWidth * 2, MyPkinfo1.bmHeight * 2, &dcmem, 0, 0, MyPkinfo1.bmWidth, MyPkinfo1.bmHeight, RGB(255, 255, 255));
						}
						else if (pDoc->POKEDEX[1].Name == _T("��ī��"))
						{
							PokePicture1.LoadBitmap(IDB_COMPIKA);
							PokePicture1.GetBitmap(&MyPkinfo1);
							dcmem.SelectObject(&PokePicture1);
							pDC->TransparentBlt(250, 20, MyPkinfo1.bmWidth, MyPkinfo1.bmHeight, &dcmem, 0, 0, MyPkinfo1.bmWidth, MyPkinfo1.bmHeight, RGB(255, 255, 255));
						}
						double Hp2 = pDoc->POKEDEX[1].iMaxHp / 10;
						pDC->TextOut(325, 5, pDoc->POKEDEX[1].Name);
						Temp.Format(_T("%d"), pDoc->POKEDEX[1].iLevel);
						pDC->TextOut(325, 20, _T("LEVEL : " + Temp));
						Temp.Format(_T("%d"), pDoc->POKEDEX[1].iHp);
						pDC->TextOut(320, 35, _T("HP  " + Temp));
						Temp.Format(_T("%d"), pDoc->POKEDEX[1].iMaxHp);
						pDC->TextOut(365, 35, _T("  /  " + Temp));
						pDC->SelectObject(Text);
						pDC->Rectangle(320, 55, 400, 65);
						pDC->FillRect(CRect(320, 55, 400, 65), &WhiteRect);
						pDC->SelectObject(HP);

						for (int iIndex = 0; iIndex < 11; iIndex++)
						{
							if (Hp2*iIndex <= pDoc->POKEDEX[1].iHp)
								pDC->Rectangle(320, 55, 320 + (8 * iIndex), 65);
							else break;
						}

						if (pDoc->POKEDEX.GetSize() > 2)
						{
							CBitmap PokePicture2;
							BITMAP MyPkinfo2;
							if (pDoc->POKEDEX[2].Name == _T("�̻��ؾ�"))
							{
								PokePicture2.LoadBitmap(IDB_COMISANG);
								PokePicture2.GetBitmap(&MyPkinfo2);
								dcmem.SelectObject(&PokePicture2);
								pDC->TransparentBlt(25, 105, MyPkinfo2.bmWidth, MyPkinfo2.bmHeight, &dcmem, 0, 0, MyPkinfo2.bmWidth, MyPkinfo2.bmHeight, RGB(255, 255, 255));
							}
							else if (pDoc->POKEDEX[2].Name == _T("����"))
							{
								PokePicture2.LoadBitmap(IDB_COMGADI);
								PokePicture2.GetBitmap(&MyPkinfo2);
								dcmem.SelectObject(&PokePicture2);
								pDC->TransparentBlt(25, 105, MyPkinfo2.bmWidth * 2, MyPkinfo2.bmHeight * 2, &dcmem, 0, 0, MyPkinfo2.bmWidth, MyPkinfo2.bmHeight, RGB(255, 255, 255));
							}
							else if (pDoc->POKEDEX[2].Name == _T("���α�"))
							{
								PokePicture2.LoadBitmap(IDB_COMSQUIT);
								PokePicture2.GetBitmap(&MyPkinfo2);
								dcmem.SelectObject(&PokePicture2);
								pDC->TransparentBlt(25, 105, MyPkinfo2.bmWidth * 2, MyPkinfo2.bmHeight * 2, &dcmem, 0, 0, MyPkinfo2.bmWidth, MyPkinfo2.bmHeight, RGB(255, 255, 255));
							}
							else if (pDoc->POKEDEX[2].Name == _T("���̸�"))
							{
								PokePicture2.LoadBitmap(IDB_COMFIRI);
								PokePicture2.GetBitmap(&MyPkinfo2);
								dcmem.SelectObject(&PokePicture2);
								pDC->TransparentBlt(25, 105, MyPkinfo2.bmWidth * 2, MyPkinfo2.bmHeight * 2, &dcmem, 0, 0, MyPkinfo2.bmWidth, MyPkinfo2.bmHeight, RGB(255, 255, 255));
							}
							else if (pDoc->POKEDEX[2].Name == _T("��ī��"))
							{
								PokePicture2.LoadBitmap(IDB_COMPIKA);
								PokePicture2.GetBitmap(&MyPkinfo2);
								dcmem.SelectObject(&PokePicture2);
								pDC->TransparentBlt(25, 105, MyPkinfo2.bmWidth, MyPkinfo2.bmHeight, &dcmem, 0, 0, MyPkinfo2.bmWidth, MyPkinfo2.bmHeight, RGB(255, 255, 255));
							}
							double Hp3 = pDoc->POKEDEX[2].iMaxHp / 10;
							pDC->TextOut(95, 85, pDoc->POKEDEX[2].Name);
							Temp.Format(_T("%d"), pDoc->POKEDEX[2].iLevel);
							pDC->TextOut(95, 100, _T("LEVEL : " + Temp));
							Temp.Format(_T("%d"), pDoc->POKEDEX[2].iHp);
							pDC->TextOut(90, 115, _T("HP  " + Temp));
							Temp.Format(_T("%d"), pDoc->POKEDEX[2].iMaxHp);
							pDC->TextOut(135, 115, _T("  /  " + Temp));
							pDC->SelectObject(Text);
							pDC->Rectangle(90, 135, 170, 145);
							pDC->FillRect(CRect(90, 135, 170, 145), &WhiteRect);
							pDC->SelectObject(HP);
							for (int iIndex = 0; iIndex < 11; iIndex++)
							{
								if (Hp3*iIndex <= pDoc->POKEDEX[2].iHp)
									pDC->Rectangle(90, 135, 90 + (8 * iIndex), 145);
								else break;
							}

							if (pDoc->POKEDEX.GetSize() > 3)
							{
								CBitmap PokePicture3;
								BITMAP MyPkinfo3;
								if (pDoc->POKEDEX[3].Name == _T("�̻��ؾ�"))
								{
									PokePicture3.LoadBitmap(IDB_COMISANG);
									PokePicture3.GetBitmap(&MyPkinfo3);
									dcmem.SelectObject(&PokePicture3);
									pDC->TransparentBlt(250, 105, MyPkinfo3.bmWidth, MyPkinfo3.bmHeight, &dcmem, 0, 0, MyPkinfo3.bmWidth, MyPkinfo3.bmHeight, RGB(255, 255, 255));
								}
								else if (pDoc->POKEDEX[3].Name == _T("����"))
								{
									PokePicture3.LoadBitmap(IDB_COMGADI);
									PokePicture3.GetBitmap(&MyPkinfo3);
									dcmem.SelectObject(&PokePicture3);
									pDC->TransparentBlt(250, 105, MyPkinfo3.bmWidth * 2, MyPkinfo3.bmHeight * 2, &dcmem, 0, 0, MyPkinfo3.bmWidth, MyPkinfo3.bmHeight, RGB(255, 255, 255));
								}
								else if (pDoc->POKEDEX[3].Name == _T("���α�"))
								{
									PokePicture3.LoadBitmap(IDB_COMSQUIT);
									PokePicture3.GetBitmap(&MyPkinfo3);
									dcmem.SelectObject(&PokePicture3);
									pDC->TransparentBlt(250, 105, MyPkinfo3.bmWidth * 2, MyPkinfo3.bmHeight * 2, &dcmem, 0, 0, MyPkinfo3.bmWidth, MyPkinfo3.bmHeight, RGB(255, 255, 255));
								}
								else if (pDoc->POKEDEX[3].Name == _T("���̸�"))
								{
									PokePicture3.LoadBitmap(IDB_COMFIRI);
									PokePicture3.GetBitmap(&MyPkinfo3);
									dcmem.SelectObject(&PokePicture3);
									pDC->TransparentBlt(250, 105, MyPkinfo3.bmWidth * 2, MyPkinfo3.bmHeight * 2, &dcmem, 0, 0, MyPkinfo3.bmWidth, MyPkinfo3.bmHeight, RGB(255, 255, 255));
								}
								else if (pDoc->POKEDEX[3].Name == _T("��ī��"))
								{
									PokePicture3.LoadBitmap(IDB_COMPIKA);
									PokePicture3.GetBitmap(&MyPkinfo3);
									dcmem.SelectObject(&PokePicture3);
									pDC->TransparentBlt(250, 105, MyPkinfo3.bmWidth, MyPkinfo3.bmHeight, &dcmem, 0, 0, MyPkinfo3.bmWidth, MyPkinfo3.bmHeight, RGB(255, 255, 255));
								}
								double Hp4 = pDoc->POKEDEX[3].iMaxHp / 10;
								pDC->TextOut(325, 85, pDoc->POKEDEX[3].Name);
								Temp.Format(_T("%d"), pDoc->POKEDEX[3].iLevel);
								pDC->TextOut(325, 100, _T("LEVEL : " + Temp));
								Temp.Format(_T("%d"), pDoc->POKEDEX[3].iHp);
								pDC->TextOut(320, 115, _T("HP  " + Temp));
								Temp.Format(_T("%d"), pDoc->POKEDEX[3].iMaxHp);
								pDC->TextOut(325, 115, _T("  /  " + Temp));
								pDC->SelectObject(Text);
								pDC->Rectangle(320, 135, 400, 145);
								pDC->FillRect(CRect(320, 135, 400, 145), &WhiteRect);
								pDC->SelectObject(HP);

								for (int iIndex = 0; iIndex < 11; iIndex++)
								{
									if (Hp4*iIndex <= pDoc->POKEDEX[3].iHp)
										pDC->Rectangle(320, 135, 320 + (8 * iIndex), 145);
									else break;
								}
							}
						}

					}
				}
			}
			else if (pDoc->GUMAE)
			{
				CBrush SelectRect(RGB(0, 200, 0));
				pDC->SelectObject(SelectRect);
				if (pDoc->ShopSelect == 0)
					pDC->Rectangle(0, 0, 150, 233);
				else if (pDoc->ShopSelect == 1)
					pDC->Rectangle(150, 0, 300, 233);
				else if (pDoc->ShopSelect == 2)
					pDC->Rectangle(300, 0, 450, 233);

				CPen Text(PS_SOLID, 3, RGB(0, 0, 0));
				pDC->SelectObject(&Text);
				pDC->SetBkMode(TRANSPARENT);
				pDC->MoveTo(150, 0);
				pDC->LineTo(150, 233);
				pDC->MoveTo(300, 0);
				pDC->LineTo(300, 233);
				pDC->TextOutW(20, 50, _T("���� �� (100)"));
				CString Ball;
				Ball.Format(_T("%d"), pDoc->Ball);
				pDC->TextOutW(60, 110, _T("���� :  ") + Ball);
				pDC->TextOutW(100, 90, _T("��"));
				pDC->TextOutW(100, 130, _T("��"));
				pDC->TextOutW(180, 50, _T("���� (50)"));
				CString Potion;
				Potion.Format(_T("%d"), pDoc->Potion);
				pDC->TextOutW(220, 110, _T("���� :  ") + Potion);
				pDC->TextOutW(265, 90, _T("��"));
				pDC->TextOutW(265, 130, _T("��"));
				CString Gold;
				Gold.Format(_T("%d"), pDoc->iGold);
				pDC->TextOutW(320, 70, _T("���� ��� : ") + Gold);
				pDC->TextOutW(330, 100, _T("������"));
			}
		}
		else if (pDoc->Battle)
		{
			CBrush NonSelect(RGB(255, 255, 254));
			pDC->SelectObject(NonSelect);
			pDC->Rectangle(0, 75, 450, 233);

			pDC->SelectObject(Text);
			pDC->MoveTo(0, 75);
			pDC->LineTo(450, 75);
			pDC->MoveTo(215, 0);
			pDC->LineTo(215, 75);
			//////////////////////�ؿ�
			pDC->MoveTo(150, 75);
			pDC->LineTo(150, 233);
			pDC->MoveTo(280, 75);
			pDC->LineTo(280, 233);
			pDC->MoveTo(0, 130);
			pDC->LineTo(280, 130);
			{
				CString Temp; 
				CBitmap PokePicture;
				BITMAP MyPkinfo;
				CBitmap ComPicture;
				BITMAP ComPkinfo;
				CDC dcmem;
				dcmem.CreateCompatibleDC(pDC);
				double Hp1 = pDoc->POKEDEX[pDoc->Pkbattle].iMaxHp / 10;
				pDC->TextOut(95, 5, pDoc->POKEDEX[pDoc->Pkbattle].Name);
				Temp.Format(_T("%d"), pDoc->POKEDEX[pDoc->Pkbattle].iLevel);
				pDC->TextOut(95, 20, _T("LEVEL : " + Temp));
				Temp.Format(_T("%d"), pDoc->POKEDEX[pDoc->Pkbattle].iHp);
				pDC->TextOut(90, 35, _T("HP  " + Temp));
				Temp.Format(_T("%d"), pDoc->POKEDEX[pDoc->Pkbattle].iMaxHp);
				pDC->TextOut(135, 35, _T("  /  " + Temp));
				pDC->SelectObject(Text);
				pDC->Rectangle(90, 55, 170, 65);
				pDC->FillRect(CRect(90, 55, 170, 65), &WhiteRect);
				pDC->SelectObject(HP);

				for (int iIndex = 0; iIndex < 11; iIndex++)
				{
					if (Hp1*iIndex <= pDoc->POKEDEX[pDoc->Pkbattle].iHp)
						pDC->Rectangle(90, 55, 90 + (8 * iIndex), 65);
					else break;
				}
				if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("�̻��ؾ�"))
				{
					PokePicture.LoadBitmap(IDB_COMISANG);
					PokePicture.GetBitmap(&MyPkinfo);
					dcmem.SelectObject(&PokePicture);
					pDC->TransparentBlt(25, 20, MyPkinfo.bmWidth, MyPkinfo.bmHeight, &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
				}
				else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("����"))
				{
					PokePicture.LoadBitmap(IDB_COMGADI);
					PokePicture.GetBitmap(&MyPkinfo);
					dcmem.SelectObject(&PokePicture);
					pDC->TransparentBlt(25, 20, MyPkinfo.bmWidth * 2, MyPkinfo.bmHeight * 2, &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
				}
				else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("���α�"))
				{
					PokePicture.LoadBitmap(IDB_COMSQUIT);
					PokePicture.GetBitmap(&MyPkinfo);
					dcmem.SelectObject(&PokePicture);
					pDC->TransparentBlt(25, 20, MyPkinfo.bmWidth * 2, MyPkinfo.bmHeight * 2, &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
				}
				else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("���̸�"))
				{
					PokePicture.LoadBitmap(IDB_COMFIRI);
					PokePicture.GetBitmap(&MyPkinfo);
					dcmem.SelectObject(&PokePicture);
					pDC->TransparentBlt(25, 20, MyPkinfo.bmWidth * 2, MyPkinfo.bmHeight * 2, &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
				}
				else if (pDoc->POKEDEX[pDoc->Pkbattle].Name == _T("��ī��"))
				{
					PokePicture.LoadBitmap(IDB_COMPIKA);
					PokePicture.GetBitmap(&MyPkinfo);
					dcmem.SelectObject(&PokePicture);
					pDC->TransparentBlt(25, 20, MyPkinfo.bmWidth, MyPkinfo.bmHeight, &dcmem, 0, 0, MyPkinfo.bmWidth, MyPkinfo.bmHeight, RGB(255, 255, 255));
				}
				double Hp2 = pDoc->MonsterStat.iMaxHp / 10;
				pDC->TextOut(325, 5, pDoc->MonsterStat.Name);
				Temp.Format(_T("%d"), pDoc->MonsterStat.iLevel);
				pDC->TextOut(325, 20, _T("LEVEL : " + Temp));
				Temp.Format(_T("%d"), pDoc->MonsterStat.iHp);
				pDC->TextOut(315, 35, _T("HP  " + Temp));
				Temp.Format(_T("%d"), pDoc->MonsterStat.iMaxHp);
				pDC->TextOut(365, 35, _T("  /  " + Temp));
				pDC->SelectObject(Text);
				pDC->Rectangle(320, 55, 400, 65);
				pDC->FillRect(CRect(320, 55, 400, 65), &WhiteRect);
				pDC->SelectObject(HP);
				for (int iIndex = 0; iIndex < 11; iIndex++)
				{
					if (Hp2*iIndex <= pDoc->MonsterStat.iHp)
						pDC->Rectangle(320, 55, 320 + (8 * iIndex), 65);
					else break;
				}
				if (pDoc->MonsterStat.Name == _T("�̻��ؾ�"))
				{
					ComPicture.LoadBitmap(IDB_COMISANG);
					ComPicture.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPicture);
					pDC->TransparentBlt(250, 20, ComPkinfo.bmWidth, ComPkinfo.bmHeight, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}
				else if (pDoc->MonsterStat.Name == _T("����"))
				{
					ComPicture.LoadBitmap(IDB_COMGADI);
					ComPicture.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPicture);
					pDC->TransparentBlt(250, 20, ComPkinfo.bmWidth * 2, ComPkinfo.bmHeight * 2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}
				else if (pDoc->MonsterStat.Name == _T("���α�"))
				{
					ComPicture.LoadBitmap(IDB_COMSQUIT);
					ComPicture.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPicture);
					pDC->TransparentBlt(250, 20, ComPkinfo.bmWidth * 2, ComPkinfo.bmHeight * 2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}
				else if (pDoc->MonsterStat.Name == _T("���̸�"))
				{
					ComPicture.LoadBitmap(IDB_COMFIRI);
					ComPicture.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPicture);
					pDC->TransparentBlt(250, 20, ComPkinfo.bmWidth * 2, ComPkinfo.bmHeight * 2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}
				else if (pDoc->MonsterStat.Name == _T("��ī��"))
				{
					ComPicture.LoadBitmap(IDB_COMPIKA);
					ComPicture.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPicture);
					pDC->TransparentBlt(250, 20, ComPkinfo.bmWidth, ComPkinfo.bmHeight, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}
				else if (pDoc->MonsterStat.Name == _T("����"))
				{
					ComPicture.LoadBitmap(IDB_WENDY);
					ComPicture.GetBitmap(&ComPkinfo);
					dcmem.SelectObject(&ComPicture);
					pDC->TransparentBlt(240, 0, ComPkinfo.bmWidth*2, ComPkinfo.bmHeight*2, &dcmem, 0, 0, ComPkinfo.bmWidth, ComPkinfo.bmHeight, RGB(255, 255, 255));
				}
			}
			CBrush SelectRect(RGB(0, 200, 0));
			pDC->SelectObject(SelectRect);
			if (pDoc->Select == 0)
				pDC->Rectangle(0, 75, 150, 130);
			else if (pDoc->Select == 1)
				pDC->Rectangle(0, 130, 150, 233);
			else if (pDoc->Select == 2)
				pDC->Rectangle(150, 75, 280, 130);
			else if (pDoc->Select == 3)
				pDC->Rectangle(150, 130, 280, 233);
			else if (pDoc->Select == 4)
				pDC->Rectangle(280, 75, 450, 233);
			pDC->SelectObject(Text);
			pDC->SetBkMode(TRANSPARENT);
			pDC->TextOutW(30, 80, pDoc->POKEDEX[pDoc->Pkbattle].Skill1);
			pDC->TextOutW(30, 135, pDoc->POKEDEX[pDoc->Pkbattle].Skiil2);
			pDC->TextOutW(175, 80, _T("���� ��"));
			CString Ball;
			Ball.Format(_T("%d"), pDoc->Ball);
			pDC->TextOutW(185, 110, _T("���� : ") + Ball);
			pDC->TextOutW(195, 135, _T("����"));
			CString Potion;
			Potion.Format(_T("%d"), pDoc->Potion);
			pDC->TextOutW(185, 155, _T("���� : ") + Potion);
			pDC->TextOutW(325, 110, _T("����"));


		}

		SetTimer(2, 300, NULL);
	}
	
		// TODO: ���⿡ �׸��� �ڵ带 �߰��մϴ�.
	}


// CInfoView �����Դϴ�.

#ifdef _DEBUG
void CInfoView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CInfoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CInfoView �޽��� ó�����Դϴ�.


void CInfoView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (nIDEvent == 2)
	{
		KillTimer(2);
		Invalidate();
	}
	CView::OnTimer(nIDEvent);
}

