
// BhzzangView.h : CBhzzangView Ŭ������ �������̽�
//

#pragma once

class CBhzzangView : public CView
{
protected: // serialization������ ��������ϴ�.
	CBhzzangView();
	DECLARE_DYNCREATE(CBhzzangView)

// Ư���Դϴ�.
public:
	CBhzzangDoc* GetDocument() const;
	BOOL timer;
	BOOL Loop;
	BOOL MusicBattle;
	int CreateM;
	int Momtong;
	int P_Momtong;
	int Skill;
	int Leaf_pos;
	int Bite;
	int CBite;
	int MonsterMove;
	int BattleStart;
	int Throw;
	int MusicMode;
// �۾��Դϴ�.
public:
	virtual void InHuntingRgn();
	virtual void SelectRun();
	virtual void SelectBall();
	virtual void SelectPotion();
	virtual void SelectSkill2();
// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// �����Դϴ�.
public:
	virtual ~CBhzzangView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent); 
	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // BhzzangView.cpp�� ����� ����
inline CBhzzangDoc* CBhzzangView::GetDocument() const
   { return reinterpret_cast<CBhzzangDoc*>(m_pDocument); }
#endif

