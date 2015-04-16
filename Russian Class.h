class mBox							//�������ݽṹ��
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
	int boxhight, boxwidth,left;			//����С����ĸ߶ȣ���ȣ��Լ������߾��룻
	BOOL board[9][14];				//���������ķ���״̬��
	int color[9][14];				//���������ķ�����ɫ��
	int BoxType;					//�������ͣ�
	int score;					//�洢������
	mBox tempbox,nextbox;				//��ǰ���飻
	COLORREF mBrushColor[6];			//Ԥ������ɫ��
protected:
	void GameInit();				//��ʼ����Ϸ��
	void NewBox();					//�����·��飻
	BOOL RollAble();				//�жϷ����Ƿ��ܷ�ת��
	void RollBox();					//��ת���飻
	BOOL BoxOk();					//�жϷ����Ƿ��ܴ�ţ�
	void SaveBox();					//��ŷ��飻
	void DrawBox();					//�����ǰ���飻
	void DrawNextBox();
	void UnDrawBox();				//������ǰ���飻
	BOOL ClearnLine();				//�����У�
	void DrawGame();				//��������Լ����飻
protected:
	afx_msg int  OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nTimerID);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint point);
	DECLARE_MESSAGE_MAP()
};



