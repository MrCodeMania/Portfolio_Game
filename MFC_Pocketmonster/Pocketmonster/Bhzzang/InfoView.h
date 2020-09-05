#pragma once


// CInfoView 뷰입니다.

class CInfoView : public CView
{
	DECLARE_DYNCREATE(CInfoView)

public:
	CInfoView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CInfoView();
public:
	virtual void OnDraw(CDC* pDC);      // 이 뷰를 그리기 위해 재정의되었습니다.
	//void HPbarRect(double x1, double y1, double x2, double y2);
	//void SelectSkill1();
	//void SelectSkill2();
	//void SelectRun();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


