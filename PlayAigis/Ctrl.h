#pragma once
class CCtrl
{

public:
	CCtrl();
	~CCtrl();

	// ע�Ტ�����ȼ�
	void initHotKey();

	// �߳��Ƿ���Լ���
	static bool canPlay();

	static const CHAR* getURL();

private:
	void stop();
	void start();
	void second();
	static bool s_bEffect;
	static CHAR s_gameurl[MAX_PATH];
};

