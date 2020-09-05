
// BhzzangView.h : CBhzzangView 클래스의 인터페이스
//

#pragma once

class CBhzzangView : public CView
{
protected: // serialization에서만 만들어집니다.
	CBhzzangView();
	DECLARE_DYNCREATE(CBhzzangView)

// 특성입니다.
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
// 작업입니다.
public:
	virtual void InHuntingRgn();
	virtual void SelectRun();
	virtual void SelectBall();
	virtual void SelectPotion();
	virtual void SelectSkill2();
// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CBhzzangView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
	
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent); 
	
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // BhzzangView.cpp의 디버그 버전
inline CBhzzangDoc* CBhzzangView::GetDocument() const
   { return reinterpret_cast<CBhzzangDoc*>(m_pDocument); }
#endif

