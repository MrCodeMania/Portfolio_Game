
// BhzzangDoc.cpp : CBhzzangDoc Ŭ������ ����
//

#include <conio.h>
#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Bhzzang.h"
#endif

#include "BhzzangDoc.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBhzzangDoc

IMPLEMENT_DYNCREATE(CBhzzangDoc, CDocument)

BEGIN_MESSAGE_MAP(CBhzzangDoc, CDocument)
END_MESSAGE_MAP()


// CBhzzangDoc ����/�Ҹ�

CBhzzangDoc::CBhzzangDoc()
{
	// TODO: ���⿡ ��ȸ�� ���� �ڵ带 �߰��մϴ�.

}

CBhzzangDoc::~CBhzzangDoc()
{
}

BOOL CBhzzangDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	SystemText.RemoveAll();
	POKEDEX.RemoveAll();
	CharPos_x = 585;
	CharPos_y = 140;
	CharDirect = 1;
	STAT PIKA = { _T("��ī��"), _T("������ȭ"), _T("����"),3, 30, 30, 3, 3 };
	POKEDEX.Add(PIKA);
	COMWENDY = { _T("����"),0,0,10,150,150,10,0 };
	MonsterStat = { 0 };
	Select = 0;
	ShopSelect = 0;
	PKNum = 0;
	Pkbattle = 0;
	BattleStart = 0;
	Potion = 3;
	Ball = 5;
	iGold = 300;
	GUMAE = false;
	CENTER = false;
	Battle = false;
	TUTORIAL = 1;
	BOSS = false;
	ENDING = false;
	// TODO: ���⿡ ���ʱ�ȭ �ڵ带 �߰��մϴ�.
	// SDI ������ �� ������ �ٽ� ����մϴ�.

	return TRUE;
}




// CBhzzangDoc serialization

void CBhzzangDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	}
	else
	{
		// TODO: ���⿡ �ε� �ڵ带 �߰��մϴ�.
	}
}

#ifdef SHARED_HANDLERS

// ����� �׸��� �����մϴ�.
void CBhzzangDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// ������ �����͸� �׸����� �� �ڵ带 �����Ͻʽÿ�.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// �˻� ó���⸦ �����մϴ�.
void CBhzzangDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������ �����Ϳ��� �˻� �������� �����մϴ�.
	// ������ �κ��� ";"�� ���еǾ�� �մϴ�.

	// ��: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CBhzzangDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CBhzzangDoc ����

#ifdef _DEBUG
void CBhzzangDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBhzzangDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBhzzangDoc ���
