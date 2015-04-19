#include <afxwin.h>
#include "Russian Class.h"

#define gamestop 0
#define gamestart 1
#define gameover -1
#define gameing 2

CMyApp Russian_Box;

BOOL CMyApp::InitInstance()
{
	m_pMainWnd = new CMainFrame;
	m_pMainWnd->ShowWindow(m_nCmdShow);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEWHEEL()
	ON_WM_TIMER()
END_MESSAGE_MAP()


CMainFrame::CMainFrame()
{
	gamestate = gamestop;
	CRect WinRect(0, 0, 740, 715);
	Create(NULL, _T("Russian Box"), WS_CAPTION | WS_MINIMIZEBOX | WS_OVERLAPPED | WS_SYSMENU, WinRect);
}
int CMainFrame::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CFrameWnd::OnCreate(lpcs) == -1) return -1;
	if (!SetTimer(1, 1000, NULL)) return - 1;
	return 0;
}
void CMainFrame::OnPaint()
{
	CPaintDC dc(this);
	if (gamestate == gamestop)
	{
		GameInit();
		gamestate = gamestart;
	}
	DrawGame();
	DrawBox();
	DrawNextBox();
	CFont mFont;
	mFont.CreatePointFont(140, _T("Arial"));
	dc.SelectObject(&mFont);
	dc.SetTextColor(RGB(40, 20, 60));
	dc.DrawText(_T("copyright©lorain·lynies"), CRect(490, 300, 680, 350), DT_LEFT | DT_TOP);
	dc.DrawText(_T("纯鼠标操作"), CRect(490, 350, 680, 400), DT_LEFT | DT_TOP);
	dc.DrawText(_T("鼠标左键开始游戏"), CRect(490, 400, 680, 450), DT_LEFT | DT_TOP);
}
void CMainFrame::OnTimer(UINT nTimerID)
{
	if (gamestate == gameing)
	{
		UnDrawBox();
		tempbox.pos.y++;
		if (BoxOk())
		{
			DrawBox();
		}
		else
		{
			tempbox.pos.y--;
			DrawBox();
			SaveBox();
			if (ClearnLine()) DrawGame();
			NewBox();
			DrawBox();
		}
	}
	if (gamestate == gameover)
	{
		KillTimer(1);
		CString tempstr;
		tempstr.Format(_T("score:%d"), score);
		MessageBox(tempstr, _T("game over"), MB_OK);
		GameInit();
		DrawGame();
		gamestate = gamestart;
		SetTimer(1, 1000, NULL);
	}
}

void CMainFrame::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (gamestate == gameing)
	{
		UnDrawBox();
		tempbox.pos.x--;
		if (!BoxOk()) tempbox.pos.x++;
		DrawBox();
	}
	if (gamestate == gamestart)
	{
		gamestate = gameing;
	}
}
void CMainFrame::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	int k = 2;
	while (--k)
	{
		if (gamestate == gameing)
		{
			UnDrawBox();
			tempbox.pos.x--;
			if (!BoxOk()) tempbox.pos.x++;
			DrawBox();
		}
	}
}
void CMainFrame::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (gamestate == gameing)
	{
		UnDrawBox();
		tempbox.pos.x++;
		if (!BoxOk()) tempbox.pos.x--;
		DrawBox();
	}
}
void CMainFrame::OnRButtonDblClk(UINT nFlags, CPoint point)
{
	int k = 2;
	while (--k)
	{
		if (gamestate == gameing)
		{
			UnDrawBox();
			tempbox.pos.x++;
			if (!BoxOk()) tempbox.pos.x--;
			DrawBox();
		}
	}
}

BOOL CMainFrame::OnMouseWheel(UINT nFlags, short zDelta, CPoint point)
{
	if (gamestate == gameing)
	{
		if (zDelta < 0)
		{
			UnDrawBox();
			tempbox.pos.y++;
			if (BoxOk())
			{
				DrawBox();
				return TRUE;
			}
			else
			{
				tempbox.pos.y--;
				DrawBox();
				return TRUE;
			}
		}
		else
		{
			UnDrawBox();
			if (RollAble()) RollBox();
			DrawBox();
		}
	}
	return TRUE;
}