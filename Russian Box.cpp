#include <afxwin.h>
#include "Russian Class.h"

#define gamestop 0
#define gamestart 1
#define gameover -1
#define gameing 2

void CMainFrame::GameInit()
{
	NewBox();
	NewBox();
	mBrushColor[0] = RGB(150, 130, 160);
	mBrushColor[1] = RGB(110, 130, 160);
	mBrushColor[2] = RGB(190, 100, 130);
	mBrushColor[3] = RGB(100, 110, 200);
	mBrushColor[4] = RGB(100, 110, 130);
	mBrushColor[5] = RGB(10, 10, 10);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			board[i][j] = FALSE;
			color[i][j] = 5;
		}
	}
	score = 0;
}
void CMainFrame::NewBox()
{
	//更新当前方块
	tempbox.colormod = nextbox.colormod;
	tempbox.pos = nextbox.pos;
	for (int i = 0; i < 4; i++)
	{
		tempbox.posin[i] = nextbox.posin[i];
	}
	//更新下一个方块
	BoxType = rand() % 7;
	nextbox.colormod = rand() % 5;
	nextbox.pos = CPoint(4, 1);
	switch (BoxType)
	{
	case 0:
		nextbox.posin[0] = CPoint(0, 0);
		nextbox.posin[1] = CPoint(0, 1);
		nextbox.posin[2] = CPoint(0, 2);
		nextbox.posin[3] = CPoint(0, -1);
		break;
	case 1:
		nextbox.posin[0] = CPoint(0, -1);
		nextbox.posin[1] = CPoint(0, 0);
		nextbox.posin[2] = CPoint(0, 1);
		nextbox.posin[3] = CPoint(1, 0);
		break;
	case 2:
		nextbox.posin[0] = CPoint(0, -1);
		nextbox.posin[1] = CPoint(0, 0);
		nextbox.posin[2] = CPoint(1, 0);
		nextbox.posin[3] = CPoint(1, 1);
		break;
	case 3:
		nextbox.posin[0] = CPoint(0, -1);
		nextbox.posin[1] = CPoint(0, 0);
		nextbox.posin[2] = CPoint(1, -1);
		nextbox.posin[3] = CPoint(1, 0);
		break;
	case 4:
		nextbox.posin[0] = CPoint(0, -1);
		nextbox.posin[1] = CPoint(0, 0);
		nextbox.posin[2] = CPoint(0, 1);
		nextbox.posin[3] = CPoint(1, 1);
		break;
	case 5:
		nextbox.posin[0] = CPoint(0, -1);
		nextbox.posin[1] = CPoint(0, 0);
		nextbox.posin[2] = CPoint(0, 1);
		nextbox.posin[3] = CPoint(-1, 1);
		break;
	case 6:
		nextbox.posin[0] = CPoint(-1, -1);
		nextbox.posin[1] = CPoint(1, -1);
		nextbox.posin[2] = CPoint(0, 1);
		nextbox.posin[3] = CPoint(0, 0);
		break;
	}
	DrawNextBox();
	if (!BoxOk()) gamestate = gameover;
}

BOOL CMainFrame::RollAble()
{
	int cx, cy;
	for (int i = 0; i < 4; i++)
	{
		cy = 0 - tempbox.posin[i].x + tempbox.pos.y;
		cx = tempbox.posin[i].y + tempbox.pos.x;
		if (0 <= cx && cx < 9 && 0 <= cy && cy < 14)
		{
			if (board[cx][cy]) return FALSE;
		}
		else return FALSE;
	}
	return TRUE;
}

void CMainFrame::RollBox()
{
	int ty;
	for (int i = 0; i < 4; i++)
	{
		ty = tempbox.posin[i].y;
		tempbox.posin[i].y = 0 - tempbox.posin[i].x;
		tempbox.posin[i].x = ty;
	}
}

BOOL CMainFrame::BoxOk()
{
	for (int i = 0; i < 4; i++)
	{
		int sumx = tempbox.pos.x + tempbox.posin[i].x;
		int sumy = tempbox.pos.y + tempbox.posin[i].y;
		if (0 <= sumx && sumx < 9 && 0 <= sumy && sumy < 14)
		{
			if (board[sumx][sumy]) return FALSE;
		}
		else return FALSE;
	}
	return TRUE;
}

void CMainFrame::SaveBox()
{
	for (int i = 0; i < 4; i++)
	{
		int mx = tempbox.pos.x + tempbox.posin[i].x;
		int my = tempbox.pos.y + tempbox.posin[i].y;
		board[mx][my] = TRUE;
		color[mx][my] = tempbox.colormod;
	}
}

void CMainFrame::DrawBox()
{
	CClientDC dc(this);
	CPen mPen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* OldPen = dc.SelectObject(&mPen);
	CBrush mBrush(mBrushColor[tempbox.colormod]);
	CBrush* OldBrush = dc.SelectObject(&mBrush);
	//下面开始绘制方块
	for (int i = 0; i < 4; i++)
	{
		int mx = (tempbox.pos.x + tempbox.posin[i].x)*boxwidth + left;
		int my = (tempbox.pos.y + tempbox.posin[i].y)*boxhight;
		dc.Rectangle(mx, my, mx + boxwidth, my + boxhight);
	}
	//绘制完成
}
void CMainFrame::DrawNextBox()
{
	CClientDC dc(this);
	CPen mPen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* OldPen = dc.SelectObject(&mPen);
	CBrush mBrush(mBrushColor[5]);
	dc.SelectObject(&mBrush);
	dc.Rectangle(10 * boxwidth + left, boxhight, 14 * boxwidth + left, 5 * boxhight);
	for (int i = 1; i < 4; i++)
	{
		dc.MoveTo((i + 10)*boxwidth + left, boxhight);
		dc.LineTo((i + 10)*boxwidth + left, 5 * boxhight);
		dc.MoveTo(10*boxwidth + left, (i+1) * boxhight);
		dc.LineTo(14*boxwidth + left, (i+1) * boxhight);
	}
	
	CBrush nBrush(mBrushColor[nextbox.colormod]);
	dc.SelectObject(&nBrush);
	for (int i = 0; i < 4; i++)
	{
		int mx = (nextbox.posin[i].x + 11)*boxwidth + left;
		int my = (nextbox.posin[i].y+2)*boxhight;
		dc.Rectangle(mx, my, mx + boxwidth, my + boxhight);
	}
}
void CMainFrame::UnDrawBox()
{
	CClientDC dc(this);
	CPen mPen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* OldPen = dc.SelectObject(&mPen);
	CBrush mBrush(mBrushColor[5]);
	CBrush* OldBrush = dc.SelectObject(&mBrush);
	
	for (int i = 0; i < 4; i++)
	{
		int mx = (tempbox.pos.x + tempbox.posin[i].x)*boxwidth + left;
		int my = (tempbox.pos.y + tempbox.posin[i].y)*boxhight;
		dc.Rectangle(mx, my, mx + boxwidth, my + boxhight);
	}
	

}
BOOL CMainFrame::ClearnLine()
{
	BOOL mFlag;
	int count = 0;
	for (int i = 13; i >= 0; i--)
	{
		mFlag = TRUE;
		for (int j = 0; j < 9; j++)
		{
			if (!board[j][i]) { mFlag = FALSE; break; }
		}
		if (mFlag)
		{
			count++;
			for (int m = 0; m < 9; m++)
			{
				for (int n = i; n > 0; n--)
				{
					board[m][n] = board[m][n - 1];
					color[m][n] = color[m][n - 1];
				}
				board[m][0] = FALSE;
				color[m][0] = 5;
			}
			i++;
		}
	}
	int mscore = 0;
	for (int i = 0; i < count; i++)
	{
		mscore = 2 * mscore+1;
	}
	score += mscore;
	if (count != 0) return TRUE;
	else return FALSE;
}
void CMainFrame::DrawGame()
{
	CClientDC dc(this);
	boxwidth = dc.GetDeviceCaps(LOGPIXELSX) / 2;
	boxhight = dc.GetDeviceCaps(LOGPIXELSY) / 2;
	left = 10;
	CPen mPen(PS_SOLID, 1, RGB(0, 0, 0));
	CPen* OldPen = dc.SelectObject(&mPen);
	
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 14; j++)
		{
			CBrush mBrush(mBrushColor[color[i][j]]);
			dc.SelectObject(&mBrush);
			dc.Rectangle(i*boxwidth + left, j*boxhight, (i + 1)*boxwidth + left, (j + 1)*boxhight);
			mBrush.DeleteObject();
		}
	}
	//
	CString strscore;
	strscore.Format(_T("分数：%d"), score);
	dc.DrawText(strscore, CRect(490, 450, 680, 500), DT_LEFT | DT_TOP);
}