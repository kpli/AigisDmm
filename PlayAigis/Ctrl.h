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

	static const CHAR* getUrlPath();

private:
	void stop();
	void start();
	void test();
	static bool s_bEffect;
	static CHAR s_gameurl1[MAX_PATH];
	static CHAR s_gameurl2[MAX_PATH];
};

