#pragma once
class CStcVal
{
public:
	CStcVal();
	~CStcVal();

public:

	static CPnt5 s_CardSilver;		// 银卡
	static CPnt5 s_CardGold;		// 金卡
	static CPnt5 s_CardWhite;		// 白金
	static CPnt5 s_CardBlack;		// 黑金

	static CPnt5 s_GameIcon;		// 开始界面游戏LOGO
	static CPnt5 s_GameStory;		// 第二关第三关入口
	static CPnt5 s_GameBtnOK;		// 确认按钮
	static CPnt5 s_GameBtnBack;		// 返回按钮

	static CPnt5 s_GameSpeed1;		// 第1关加速
	static CPnt5 s_GameSpeed2;		// 第2关加速
	static CPnt5 s_GameSpeed3;		// 第3关加速
	static CPnt5 s_GameSpeed4;		// 第4关加速
	static CPnt5 s_GameSpeed5;		// 第5关加速
	static CPnt5 s_GameSpeed6;		// 第6关加速
	static CPnt5 s_GameSpeed7;		// 第7关加速

	//static CPnt5 s_Bounding1;		// 选择增益1步
	static CPnt5 s_Bounding1;		// 选择增益1步
	static CPnt5 s_Bounding2;		// 选择增益2步
	static CPnt5 s_Bounding3;		// 选择增益3步
	static CPnt5 s_Bounding4;		// 选择增益4步

	static CPnt5 s_Random1;			// 抽卡1步
	static CPnt5 s_Random2;			// 抽卡2步
	static CPnt5 s_Random3;			// 抽卡3步
	static CPnt5 s_Random4;			// 抽卡4步

	
	static RECT s_rcRange;				// 搜索颜色的范围 (for got the form size)
	static COLORREF s_arrColor[5];		// 要搜索的颜色 (for got the form size)
	static CPnt5 s_pnt5Rider;			// 骑士的搜索起点和特征色
	static CPnt5 s_GameUnit1;			// 选择骑士1步
	static CPnt5 s_GameUnit2;			// 选择骑士2步
	static CPnt5 s_GameUnit3;			// 选择骑士3步
	static CPnt5 s_GameUnit4;			// 选择骑士4步, 需配合按键精灵查图
	static CPnt5 s_GameUnit5;			// 选择骑士5步

	static CPnt5 s_SelectStory0_1;		// 选择第x关
	static CPnt5 s_SelectStory4_2;		// 选择第4关
	static CPnt5 s_SelectStory5_2;		// 选择第5关
	static CPnt5 s_SelectStory6_2;		// 选择第6关
	static CPnt5 s_SelectStory7_2;		// 选择第7关
	static CPnt5 s_SelectStory0_3;		// 选择第x关
	static CPnt5 s_SelectStory0_4;		// 选择第x关

	static CRolePnt s_ST1_Role1;		// 第1关角色1
	static CRolePnt s_ST1_Role2;		// 第1关角色2
	static CRolePnt s_ST1_Role3;		// 第1关角色3
	static CRolePnt s_ST1_Role4;		// 第1关角色4
	static CRolePnt s_ST1_Role5;		// 第1关角色5
	static CRolePnt s_ST2_Role1;		// 第2关角色1
	static CRolePnt s_ST2_Role2;		// 第2关角色2
	static CRolePnt s_ST2_Role3;		// 第2关角色3
	static CRolePnt s_ST2_Role4;		// 第2关角色4
	static CRolePnt s_ST2_Role5;		// 第2关角色5
	static CRolePnt s_ST3_Role1;		// 第3关角色1
	static CRolePnt s_ST3_Role2;		// 第3关角色2
	static CRolePnt s_ST3_Role3;		// 第3关角色3
	static CRolePnt s_ST3_Role4;		// 第3关角色4
	static CRolePnt s_ST3_Role5;		// 第3关角色5

	static CRolePnt s_ST4_Role1;		// 第4关角色1
	static CRolePnt s_ST4_Role2;		// 第4关角色2
	static CRolePnt s_ST4_Role3;		// 第4关角色3
	static CRolePnt s_ST4_Role4;		// 第4关角色4
	static CRolePnt s_ST4_Role5;		// 第4关角色5
	static CRolePnt s_ST4_Role6;		// 第4关角色6
	static CRolePnt s_ST4_Role7;		// 第4关角色7
	static CRolePnt s_ST4_Role8;		// 第4关角色8

	static CRolePnt s_ST5_Role1;		// 第5关角色1
	static CRolePnt s_ST5_Role2;		// 第5关角色2
	static CRolePnt s_ST5_Role3;		// 第5关角色3
	static CRolePnt s_ST5_Role4;		// 第5关角色4
	static CRolePnt s_ST5_Role5;		// 第5关角色5
	static CRolePnt s_ST5_Role6;		// 第5关角色6
	static CRolePnt s_ST5_Role7;		// 第5关角色7

	static CRolePnt s_ST6_Role1;		// 第6关角色1
	static CRolePnt s_ST6_Role2;		// 第6关角色2
	static CRolePnt s_ST6_Role3;		// 第6关角色3
	static CRolePnt s_ST6_Role4;		// 第6关角色4
	static CRolePnt s_ST6_Role5;		// 第6关角色5
	static CRolePnt s_ST6_Role6;		// 第6关角色6
	static CRolePnt s_ST6_Role7;		// 第6关角色7

	static CRolePnt s_ST7_Role1;		// 第7关角色1
	static CRolePnt s_ST7_Role2;		// 第7关角色2
	static CRolePnt s_ST7_Role3;		// 第7关角色3
	static CRolePnt s_ST7_Role4;		// 第7关角色4
	static CRolePnt s_ST7_Role5;		// 第7关角色5
	static CRolePnt s_ST7_Role6;		// 第7关角色6

};

// --END
