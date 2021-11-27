
// ShooterView.cpp: CShooterView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Shooter.h"
#endif

#include "ShooterDoc.h"
#include "ShooterView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CShooterView

IMPLEMENT_DYNCREATE(CShooterView, CView)

BEGIN_MESSAGE_MAP(CShooterView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CShooterView 생성/소멸

CShooterView::CShooterView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

	Recx = 500;
	Recy = 980;// box.bottom;
	play = 0;
	score = 0;
	radius = 30;
}

CShooterView::~CShooterView()
{
}

BOOL CShooterView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CShooterView 그리기

void CShooterView::OnDraw(CDC* /*pDC*/)
{
	CShooterDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CClientDC dc(this);

	CRect rect;
	GetClientRect(rect);

	for (int i = 0; i < ball.size(); i++) {
		if (ball[i].y + radius > rect.bottom)
			score++;
		dc.Ellipse(ball[i].x - radius, ball[i].y - radius, ball[i].x + radius, ball[i].y + radius);
	}

	CString str;
	str.Format(L"점수: %d", score);
	dc.TextOutW(1500, 20 , str);

	CString s;
	s.Format(_T("최종 점수: %d"), score);

	dc.Rectangle(Recx-100, Recy-100, Recx, Recy); //플레이어

	for (int j = 0; j < ball.size(); j++) {
		if ((ball[j].y - radius) > (Recy - 100) && (ball[j].x - 30) < Recx && (ball[j].x + 30) > Recx - 100) {	
			KillTimer(1);
			KillTimer(2); 
			MessageBox(s, L"게임 종료");
			//return; 
			break;
		}
	}

}


// CShooterView 인쇄

BOOL CShooterView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CShooterView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CShooterView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CShooterView 진단

#ifdef _DEBUG
void CShooterView::AssertValid() const
{
	CView::AssertValid();
}

void CShooterView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShooterDoc* CShooterView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShooterDoc)));
	return (CShooterDoc*)m_pDocument;
}
#endif //_DEBUG


// CShooterView 메시지 처리기

void CShooterView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	switch (nChar) {
	case VK_RIGHT:
		Recx += 10;
		break;
	case VK_LEFT:
		Recx -= 10;
		break;
	case VK_F1: //공 생성
		SetTimer(1, 1000, NULL);
	case VK_SPACE:
		play = !play;
		if (play) SetTimer(2, 500, NULL);
		else KillTimer(2);
		break;

	}

	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
//#include <ctime>
//#include <cstdlib>
//#include <iostream>
//using namespace std;
#include<time.h> 
#include<stdlib.h>

void CShooterView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	srand((unsigned)time(NULL));
	CRect box;
	GetClientRect(box);

	if (nIDEvent == 1) {		
		int bx = (box.right / 30) * (rand() % 30);
		int by = 50;
		ball.push_back({ bx,by });
		ballspd.push_back(20);
		Invalidate();
	}
	if (nIDEvent == 2)
		for (int i = 0; i < ball.size(); i++) 
			ball[i].y += ballspd[i];

	Invalidate();

	CView::OnTimer(nIDEvent);
}


void CShooterView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CView::OnLButtonDown(nFlags, point);
}
