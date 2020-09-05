
// BhzzangDoc.h : CBhzzangDoc 클래스의 인터페이스
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
protected: // serialization에서만 만들어집니다.
	CBhzzangDoc();
	DECLARE_DYNCREATE(CBhzzangDoc)
// 특성입니다.
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
// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CBhzzangDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
