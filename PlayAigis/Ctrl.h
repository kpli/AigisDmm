#pragma once
class CCtrl
{

public:
	CCtrl();
	~CCtrl();

	// 注册并监听热键
	void initHotKey();

	// 线程是否可以继续
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

