
// ShooterView.h: CShooterView 클래스의 인터페이스
//

#pragma once
#include <vector>
#include <algorithm>
#include<iostream>
#include <string>
#include<vector>
#include<fstream>
#include<cmath>
#include <windows.h>
#include <stdio.h>

using namespace std;


class CShooterView : public CView
{
protected: // serialization에서만 만들어집니다.
	CShooterView() noexcept;
	DECLARE_DYNCREATE(CShooterView)

// 특성입니다.
public:
	CShooterDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CShooterView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	int Recx;
	int Recy;
	int score;
	vector<CPoint> ball;
	int radius;
	vector<int> ballspd;
	//vector<CPoint> bullet;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	int play;
};

#ifndef _DEBUG  // ShooterView.cpp의 디버그 버전
inline CShooterDoc* CShooterView::GetDocument() const
   { return reinterpret_cast<CShooterDoc*>(m_pDocument); }
#endif

