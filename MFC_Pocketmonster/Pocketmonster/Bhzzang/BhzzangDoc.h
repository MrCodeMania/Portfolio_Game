
// BhzzangDoc.h : CBhzzangDoc Ŭ������ �������̽�
//

#include <afxtempl.h>
#pragma once


typedef struct Stat
{
	CString Name;
	CString Skill1;
	CString Skiil2;
	int iAtt;
	int iHp;
	int iMaxHp;
	int iLevel;
	int iExp;
}STAT;

class CBhzzangDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CBhzzangDoc();
	DECLARE_DYNCREATE(CBhzzangDoc)
// Ư���Դϴ�.
public:
	CArray<STAT, STAT> POKEDEX;
	CArray<TCHAR, TCHAR> SystemText;
	STAT MonsterStat; 
	STAT COMWENDY;
	int CharPos_x;
	int CharPos_y;
	int CharDirect;
	int Select;
	int PKNum;
	int Pkbattle;
	int BattleStart;
	int Potion;
	int Ball;
	int iGold;
	int ShopSelect;
	int TUTORIAL;
	BOOL ENDING;
	BOOL GUMAE;
	BOOL CENTER;
	BOOL Battle;
	BOOL BOSS;
// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CBhzzangDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
