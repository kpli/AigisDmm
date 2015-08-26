#include "stdafx.h"
#include "StcVal.h"


CStcVal::CStcVal()
{
}


CStcVal::~CStcVal()
{
}

CPnt5 CStcVal::s_CardSilver(205, 573, 0xb1b1b1, 0x878787, 0x9a9a9a, 0x9f9f9f, 0xa6a6a6);	// 银卡
CPnt5 CStcVal::s_CardGold(204, 576, 0x3af9ff, 0x1feff, 0x15e3f1, 0x39e8f3, 0x2b1cc);		// 金卡
CPnt5 CStcVal::s_CardWhite(203, 575, 0xecede9, 0xbbbdb2, 0xadb0a5, 0xfcfdfc, 0xe1e1dc);	// 白金
CPnt5 CStcVal::s_CardBlack(155, 574, 0x1879d, 0x13b47, 0x1414d, 0x35a66, 0x24f5f);		// 黑金

CPnt5 CStcVal::s_GameIcon(454, 261, 0xaeaeae, 0x12128d, 0x5e5e5e, 0xffffff, 0xe2e2e1);	// 开始界面游戏LOGO
CPnt5 CStcVal::s_GameStory(654, 176, 0x8adafa, 0x8792bb, 0x6eb6e5, 0x45cbea, 0x62a0e6);	// 第二关第三关入口
CPnt5 CStcVal::s_GameBtnOK(474, 424, 0xffffff, 0xb67600, 0xffffff, 0xad6400, 0xbf7600);	// 确认按钮
CPnt5 CStcVal::s_GameBtnBack(908, 64, 0xf6f6f9, 0xeaeaf0, 0x5353c1, 0xe0e0eb, 0xffffff);	// 返回按钮

CPnt5 CStcVal::s_GameSpeed1(871, 36, 0x212455, 0x1e214e, 0x292d6b, 0x212455, 0x181a3d);	// 第1关加速
CPnt5 CStcVal::s_GameSpeed2(871, 36, 0x212455, 0x1e214e, 0x292d6b, 0x212455, 0x181a3d);	// 第2关加速
CPnt5 CStcVal::s_GameSpeed3(871, 37, 0x1f2250, 0x1c1f49, 0x272b67, 0x1f2250, 0x161839);	// 第3关加速
CPnt5 CStcVal::s_GameSpeed4(872, 36, 0x212455, 0x212455, 0x292d6b, 0x212455, 0x181a3d);	// 第4关加速
CPnt5 CStcVal::s_GameSpeed5(870, 39, 0x1b1e47, 0xe0f24, 0x24285e, 0x1b1e47, 0x121430);	// 第5关加速
CPnt5 CStcVal::s_GameSpeed6(872, 39, 0x1b1e47, 0x1b1e47, 0x24285e, 0x1b1e47, 0x121430);	// 第6关加速
CPnt5 CStcVal::s_GameSpeed7(871, 36, 0x212455, 0x1e214e, 0x292d6b, 0x212455, 0x181a3d);	// 第7关加速

CPnt5 CStcVal::s_Bounding1(92, 577, 0x4d6a4, 0x4d6a4, 0x257c8, 0x9489, 0x4b37f);			// 选择增益1步
CPnt5 CStcVal::s_Bounding2(399, 287, 0x3d5572, 0x5c7093, 0xc1d3dd, 0xd686e3, 0xef94ff);	// 选择增益2步
CPnt5 CStcVal::s_Bounding3(442, 175, 0x92aded, 0xc9d2ff, 0x8092d2, 0x3f1b40, 0x3f1b40);	// 选择增益3步
CPnt5 CStcVal::s_Bounding4(266, 448, 0x2f2d8a, 0xffffff, 0x373693, 0xcbcae6, 0x5050a4);	// 选择增益4步

CPnt5 CStcVal::s_Random1(355, 301, 0xffffff, 0xefffff, 0x4f1ad8, 0x1a15b1, 0xffffff);		// 抽卡1步
CPnt5 CStcVal::s_Random2(55, 326, 0x53c4, 0x53c4, 0xaa, 0x41c1, 0x1afde);					// 抽卡2步
CPnt5 CStcVal::s_Random3(546, 422, 0x7ca6d5, 0x91b5f7, 0x325979, 0x698fb5, 0x4345c);		// 抽卡3步
CPnt5 CStcVal::s_Random4(379, 410, 0x1b1bbf, 0xa4a4db, 0x1b12c0, 0xffffff, 0x3f3fc0);		// 抽卡4步

// for got the form size
RECT CStcVal::s_rcRange;			// 搜索颜色的范围
COLORREF CStcVal::s_arrColor[5];	// 要搜索的颜色

CPnt5 CStcVal::s_pnt5Rider(444, 172, 0x498040, 0x243636, 0x497f36, 0x1b2d09, 0x528940);	// 骑士的搜索起点和特征色
CPnt5 CStcVal::s_GameUnit1(s_Random1);													// 选择骑士1步
CPnt5 CStcVal::s_GameUnit2(95, 244, 0x1c2e6, 0x96cd, 0x14b3, 0x26ccde, 0x708c);			// 选择骑士2步
CPnt5 CStcVal::s_GameUnit3(387, 199, 0x3d7699, 0x2a1509, 0x33180a, 0x345c76, 0x502510);	// 选择骑士3步
CPnt5 CStcVal::s_GameUnit4(564, 311, 0x6c3400, 0x6c3400, 0x713500, 0x6c3400, 0x743700);	// 选择骑士4步, 需配合按键精灵查图
CPnt5 CStcVal::s_GameUnit5(260, 534, 0x3c3ba0, 0x464597, 0x373693, 0x2d2b82, 0x373693);	// 选择骑士5步

CPnt5 CStcVal::s_SelectStory0_1(361, 197, 0x2545aa, 0x122075, 0x324daa, 0xf2595, 0x2640b8);		// 选择第x关
CPnt5 CStcVal::s_SelectStory4_2(645, 129, 0x66351c, 0x67361c, 0x847bd2, 0x663318, 0x643113);		// 选择第4关
CPnt5 CStcVal::s_SelectStory5_2(651, 212, 0x693c2e, 0x847bd2, 0xbba9ab, 0x663315, 0x663317);		// 选择第5关
CPnt5 CStcVal::s_SelectStory6_2(650, 121, 0x725f9a, 0x3a38c0, 0x625fe8, 0x68381e, 0x6a3a29);		// 选择第6关
CPnt5 CStcVal::s_SelectStory7_2(650, 121, 0x725f9a, 0x3a38c0, 0x625fe8, 0x68381e, 0x6a3a29);		// 选择第7关
CPnt5 CStcVal::s_SelectStory0_3(353, 560, 0x405b6, 0xaeaeae, 0x4142cf, 0x181abf, 0x40106);		// 选择第x关
CPnt5 CStcVal::s_SelectStory0_4(417, 536, 0x474548, 0x6b696c, 0x4b4cca, 0x474548, 0x20147);		// 选择第x关

CRolePnt CStcVal::s_ST1_Role1(CPnt5(161, 599, 0x525b5b, 0x49525b, 0xc9e4ff, 0x526480, 0x8992a4), 542, 340);		// 第1关角色1
CRolePnt CStcVal::s_ST1_Role2(CPnt5(180, 595, 0x120900, 0x494040, 0x241b12, 0x363636, 0x5b5252), 506, 244);		// 第1关角色2
CRolePnt CStcVal::s_ST1_Role3(CPnt5(164, 597, 0xdbffff, 0xd2f6ff, 0x243f5b, 0x5b9bf6, 0xb6c0b6), 433, 262);		// 第1关角色3
CRolePnt CStcVal::s_ST1_Role4(CPnt5(137, 569, 0x2452bf, 0x91b49, 0x5bdbff, 0x4989db, 0x243f80), 576, 246);		// 第1关角色4
CRolePnt CStcVal::s_ST1_Role5(CPnt5(143, 584, 0x9, 0xc0bfc0, 0x12122d, 0xedffff, 0x364064), 655, 251);			// 第1关角色5
CRolePnt CStcVal::s_ST2_Role1(CPnt5(549, 601, 0x241b3f, 0x523f64, 0xd2e4ff, 0xedffff, 0x2d2d40), 551, 361);		// 第2关角色1
CRolePnt CStcVal::s_ST2_Role2(CPnt5(348, 598, 0x7f807f, 0xbfc9bf, 0x3f3f3f, 0x404040, 0xc0d2bf), 494, 382);		// 第2关角色2
CRolePnt CStcVal::s_ST2_Role3(CPnt5(152, 582, 0x2d3f6d, 0x6d7f80, 0x2d365b, 0xc9e4ff, 0x9122d), 379, 322);		// 第2关角色3
CRolePnt CStcVal::s_ST2_Role4(CPnt5(71, 588, 0x5b769b, 0x809bc9, 0x5b7692, 0x2d1212, 0x1b1b24), 484, 302);		// 第2关角色4
CRolePnt CStcVal::s_ST2_Role5(CPnt5(347, 594, 0x7f899b, 0xd2a464, 0x404040, 0xb6e4ff, 0xadd2ff), 364, 253);		// 第2关角色5
CRolePnt CStcVal::s_ST3_Role1(CPnt5(151, 590, 0x364092, 0xc0d2e4, 0x12, 0xb6c9f6, 0x405bbf), 327, 256);			// 第3关角色1
CRolePnt CStcVal::s_ST3_Role2(CPnt5(155, 597, 0x928992, 0x898080, 0xe4ffff, 0xa49ba4, 0x7f7676), 302, 396);		// 第3关角色2
CRolePnt CStcVal::s_ST3_Role3(CPnt5(251, 577, 0xedffff, 0xbfd2e4, 0x4989db, 0xdbffff, 0xd2f6ff), 531, 472);		// 第3关角色3
CRolePnt CStcVal::s_ST3_Role4(CPnt5(248, 579, 0x5b76a4, 0x12122d, 0x9bbfed, 0x8992bf, 0x767f9b), 385, 348);		// 第3关角色4
CRolePnt CStcVal::s_ST3_Role5(CPnt5(343, 594, 0xd2a464, 0xb6641b, 0x6dadd2, 0x3f4980, 0x80491b), 467, 387);		// 第3关角色5

CRolePnt CStcVal::s_ST4_Role1(CPnt5(170, 581, 0x5276d2, 0x89b6ff, 0x808080, 0x90912, 0x7692db), 431, 239);		// 第4关角色1
CRolePnt CStcVal::s_ST4_Role2(CPnt5(151, 594, 0x524952, 0x403f40, 0x7680ad, 0xedffff, 0x807f7f), 656, 241);		// 第4关角色2
CRolePnt CStcVal::s_ST4_Role3(CPnt5(665, 573, 0xd2edf6, 0x92bfff, 0x1b2424, 0x7fad6d, 0xc0d2ff), 322, 261);		// 第4关角色3
CRolePnt CStcVal::s_ST4_Role4(CPnt5(52, 585, 0x405b80, 0x5b6d76, 0x2d3f52, 0x1b121b, 0x405b80), 759, 277);		// 第4关角色4
CRolePnt CStcVal::s_ST4_Role5(CPnt5(354, 595, 0x5b5b52, 0x76766d, 0xa4a492, 0x7f7f6d, 0x929b89), 551, 213);		// 第4关角色5
CRolePnt CStcVal::s_ST4_Role6(CPnt5(354, 592, 0x527f92, 0xa4c0ff, 0xbfedff, 0x89c0db, 0xbfedff), 465, 304);		// 第4关角色6
CRolePnt CStcVal::s_ST4_Role7(CPnt5(250, 588, 0xffffff, 0xc9edff, 0xe4f6ff, 0xdbedff, 0xdbedff), 595, 310);		// 第4关角色7
CRolePnt CStcVal::s_ST4_Role8(CPnt5(51, 591, 0xbfbfd2, 0x649bed, 0x497fad, 0x646d52, 0xdbffff), 665, 337);		// 第4关角色8

CRolePnt CStcVal::s_ST5_Role1(CPnt5(453, 576, 0xb6dbff, 0x76525b, 0x499bed, 0xedffff, 0xdbf6ff), 694, 468);		// 第5关角色1
CRolePnt CStcVal::s_ST5_Role2(CPnt5(151, 588, 0x1b2d5b, 0xadbfc0, 0x364092, 0xc0e4ff, 0x1b2440), 810, 400);		// 第5关角色2
CRolePnt CStcVal::s_ST5_Role3(CPnt5(461, 591, 0xd2d2c9, 0x9ba492, 0xe4ede4, 0xb6bfa4, 0x40403f), 810, 310);		// 第5关角色3
CRolePnt CStcVal::s_ST5_Role4(CPnt5(51, 586, 0x7f89b6, 0x242424, 0x120909, 0x526489, 0xbfd2ff), 686, 348);		// 第5关角色4
CRolePnt CStcVal::s_ST5_Role5(CPnt5(449, 582, 0x92c0db, 0x1b2409, 0x6492ff, 0xa4c0ff, 0x899289), 600, 280);		// 第5关角色5
CRolePnt CStcVal::s_ST5_Role6(CPnt5(359, 586, 0xa4b6d2, 0xffffff, 0xb69b76, 0xffffff, 0x527f92), 744, 325);		// 第5关角色6
CRolePnt CStcVal::s_ST5_Role7(CPnt5(260, 594, 0xc9dbff, 0xc9dbff, 0xc9d2ff, 0x7f89d2, 0xd2e4ff), 746, 423);		// 第5关角色7

CRolePnt CStcVal::s_ST6_Role1(CPnt5(856, 586, 0xb6bfc0, 0x91200, 0x6dadff, 0xd2e4ff, 0xbfd2ff), 585, 335);		// 第6关角色1
CRolePnt CStcVal::s_ST6_Role2(CPnt5(47, 587, 0x494949, 0x90000, 0x241b24, 0x526480, 0xb6c9f6), 570, 254);			// 第6关角色2
CRolePnt CStcVal::s_ST6_Role3(CPnt5(559, 596, 0x76766d, 0xbfbfb6, 0xc9d2c9, 0x3f403f, 0xb6b6ad), 500, 235);		// 第6关角色3
CRolePnt CStcVal::s_ST6_Role4(CPnt5(359, 580, 0xdbf6ff, 0xd2f6ff, 0x3f80e4, 0xdbf6ff, 0xdbf6ff), 525, 439);		// 第6关角色4
CRolePnt CStcVal::s_ST6_Role5(CPnt5(460, 591, 0xbfffff, 0xa4e4ed, 0xc0c0c0, 0xa4c0ff, 0xb6e4ff), 504, 307);		// 第6关角色5
CRolePnt CStcVal::s_ST6_Role6(CPnt5(360, 587, 0xdbedff, 0xdbedff, 0xd2e4ff, 0xd2e4ff, 0xd2e4ff), 499, 376);		// 第6关角色6
CRolePnt CStcVal::s_ST6_Role7(CPnt5(268, 590, 0x1b3649, 0x3f6d92, 0x1b3649, 0x1b2d40, 0x3f64bf), 416, 274);		// 第6关角色7

CRolePnt CStcVal::s_ST7_Role1(CPnt5(49, 586, 0x120909, 0x6d89bf, 0x361b24, 0x526489, 0xbfd2f6), 353, 190);		// 第7关角色1
CRolePnt CStcVal::s_ST7_Role2(CPnt5(756, 585, 0x6d7f6d, 0x3f6d92, 0x5280ad, 0xd2e4ff, 0xd2e4ff), 235, 316);		// 第7关角色2
CRolePnt CStcVal::s_ST7_Role3(CPnt5(662, 584, 0x898989, 0x646464, 0x643f24, 0x6492d2, 0xbfedff), 376, 252);		// 第7关角色3
CRolePnt CStcVal::s_ST7_Role4(CPnt5(560, 584, 0xedede4, 0x929289, 0xededed, 0xdbdbd2, 0xedede4), 261, 232);		// 第7关角色4
CRolePnt CStcVal::s_ST7_Role5(CPnt5(457, 593, 0x9bbfff, 0xd2e4ff, 0xdbedff, 0xc9dbff, 0x929bb6), 429, 216);		// 第7关角色5
CRolePnt CStcVal::s_ST7_Role6(CPnt5(255, 591, 0xbfbfd2, 0x649bed, 0x497fad, 0x646d52, 0xdbffff), 329, 294);		// 第7关角色6



// --END

