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

	static const CHAR* getURL();

private:
	void stop();
	void start();
	void second();
	static bool s_bEffect;
	static CHAR s_gameurl[MAX_PATH];
};

