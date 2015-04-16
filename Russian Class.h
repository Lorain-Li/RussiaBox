class mBox							//方块数据结构；
{
public:
	CPoint posin[4];
	CPoint pos;
	int colormod;
};

class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};

class CMainFrame : public CFrameWnd
{
public:
	CMainFrame();
private:
	int gamestate;
	int boxhight, boxwidth,left;			//保存小方块的高度，宽度，以及面板左边距离；
	BOOL board[9][14];				//保存面板里的方块状态；
	int color[9][14];				//保存面板里的方块颜色；
	int BoxType;					//方块类型；
	int score;					//存储分数；
	mBox tempbox,nextbox;				//当前方块；
	COLORREF mBrushColor[6];			//预定义颜色；
protected:
	void GameInit();				//初始化游戏；
	void NewBox();					//生成新方块；
	BOOL RollAble();				//判断方块是否能翻转；
	void RollBox();					//翻转方块；
	BOOL BoxOk();					//判断方块是否能存放；
	void SaveBox();					//存放方块；
	void DrawBox();					//绘出当前方块；
	void DrawNextBox();
	void UnDrawBox();				//消隐当前方块；
	BOOL ClearnLine();				//消除行；
	void DrawGame();				//绘制面板以及方块；
protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nTimerID);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint point);
	DECLARE_MESSAGE_MAP()
};



