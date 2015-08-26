#pragma once
class CLogic
{
public:
	static CLogic* getInstance();

	void startPlay();
	void startTest();

protected:
	void FirstRondomCard();
	void SecondRondomCard();
	
protected:

	// 选择骑士
	void selectUnit();

	void selectStory4567(CPnt5* pStoryEntry);

	// 选择第4关
	void playStory4();

	// 选择第5关
	void playStory5();


	// 选择第6关
	void playStory6();

	// 选择第7关
	void playStory7();


protected:
	// 启动注册流程
	void startRegist();
	void waitRegist();

	void playStory1();

	void playStory2();

	void playStory3();

	// 什么都不做，直到游戏开始
	void waitIcon_nothing();

	// 点击确认， 直到第二关入口
	void waitEntry_clickOK();

	// 点击确认， 直到选择增益
	void waitBound_clickOK();

	// 点击返回， 直到第三，四关入口
	void waitEntry_clickBack();

	// 点击确认， 直到显示返回按钮
	void waitBack_clickOK();

	// 点击确认， 直到可以抽卡
	void waitCard_clickOK();
	void waitCard_clickOK2();


private:
	void waitPnt_clickPnt(CPnt5* pClick, CPnt5* pWait, bool bfirst = true);

	// 点击加速， 直到角色上场
	void waitRole_bySpeedup(CPnt5* pntSpeed, CRolePnt* role, bool bfirst = true);

	// 点击加速， 直到完成关卡
	void waitOK_bySpeedup(CPnt5* pntSpeed);

	// 点击加速, 满足条件
	void clickSpeedUp(CPnt5* pntSpeed);

	void waitCard();

	// 等待
	void waitTime(size_t nseconds);

	// 超时重玩
	static void DetectTimeout(size_t bt, size_t iSecs);

	// 超时前都可以等待
	static bool canWait();

	// 线程主循环
	static void ThreadPlaying(void *);

	// 测试循环
	static void ThreadTest(void *);
private:
	CLogic();
	~CLogic();
	static bool s_bWaitFor;			// 没超时继续等待
	static int s_iCardStar;		// 可以二抽
};

