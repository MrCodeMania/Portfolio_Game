#pragma once


// CInfoView ���Դϴ�.

class CInfoView : public CView
{
	DECLARE_DYNCREATE(CInfoView)

public:
	CInfoView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CInfoView();
public:
	virtual void OnDraw(CDC* pDC);      // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
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


