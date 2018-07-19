// 广东麻将.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"在visual studio中运行需要添加，并且strcpy函数改为了strcpy_s。
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <vector>
#include <time.h>
#include<iostream>
#include <algorithm>

using namespace std;

//牌结构体
typedef struct Pai {
	int Number;
	char Name[5];
}Card;

//用于摸牌后对玩家手牌排序
struct less {
	bool operator()(Card C1, Card C2) {
		return(C1.Number < C2.Number);
	};
}myobject;

static vector<Card> OldArray;//洗牌前牌容器
static vector<Card> NewArray;//洗牌后牌容器
static vector<Card> GiveOutArray;//出牌后桌面牌的容器
static vector<Card> Player;//玩家手牌容器
static vector<Card> PlayerC1;//电脑玩家1手牌容器
static vector<Card> PlayerC2;//电脑玩家1手牌容器
static vector<Card> PlayerC3;//电脑玩家1手牌容器
static vector<Card> PlayerGangAndPeng;//杠和碰的牌的容器
static vector<Card> PlayerC1GangAndPeng;//杠和碰的牌的容器
static vector<Card> PlayerC2GangAndPeng;//杠和碰的牌的容器
static vector<Card> PlayerC3GangAndPeng;//杠和碰的牌的容器

void Init();
void CardWash(vector<Card> &OldArray, vector<Card> &NewArray);
void CardGiveout();
int CardPengOrMingGang();
int CardCanHu(int TureOrFalse);
void UI();

//创建牌
void Init() {
	Card card[136] = {};
	for (int i = 0; i <= 6; i++) {//0-27四组东南西北中发白
		card[i].Number = i + 1;
	}
	for (int i = 7; i <= 13; i++) {
		card[i].Number = i - 6;
	}
	for (int i = 14; i <= 20; i++) {
		card[i].Number = i - 13;
	}
	for (int i = 21; i <= 27; i++) {
		card[i].Number = i - 20;
	}
	for (int i = 28; i <= 36; i++) {//28-63四组万子
		card[i].Number = i - 17;
	}
	for (int i = 37; i <= 45; i++) {
		card[i].Number = i - 26;
	}
	for (int i = 46; i <= 54; i++) {
		card[i].Number = i - 35;
	}
	for (int i = 55; i <= 63; i++) {
		card[i].Number = i - 44;
	}
	for (int i = 64; i <= 72; i++) {//64-99四组条
		card[i].Number = i - 43;
	}
	for (int i = 73; i <= 81; i++) {
		card[i].Number = i - 52;
	}
	for (int i = 82; i <= 90; i++) {
		card[i].Number = i - 61;
	}
	for (int i = 91; i <= 99; i++) {
		card[i].Number = i - 70;
	}
	for (int i = 100; i <= 108; i++) {//100-135四组筒
		card[i].Number = i - 69;
	}
	for (int i = 109; i <= 117; i++) {
		card[i].Number = i - 78;
	}
	for (int i = 118; i <= 126; i++) {
		card[i].Number = i - 87;
	}
	for (int i = 127; i <= 135; i++) {
		card[i].Number = i - 96;
	}
	for (int i = 0; i <= 135; i++) {//对所有牌进行赋予名字
		switch (card[i].Number / 10) {
		case 0:
			switch (card[i].Number % 10) {
			case 1:
				strcpy_s(card[i].Name, "东");
				break;
			case 2:
				strcpy_s(card[i].Name, "南");
				break;
			case 3:
				strcpy_s(card[i].Name, "西");
				break;
			case 4:
				strcpy_s(card[i].Name, "北");
				break;
			case 5:
				strcpy_s(card[i].Name, "中");
				break;
			case 6:
				strcpy_s(card[i].Name, "发");
				break;
			case 7:
				strcpy_s(card[i].Name, "白");
				break;
			}
			break;
		case 1:
			switch (card[i].Number % 10) {
			case 1:
				strcpy_s(card[i].Name, "一万");
				break;
			case 2:
				strcpy_s(card[i].Name, "二万");
				break;
			case 3:
				strcpy_s(card[i].Name, "三万");
				break;
			case 4:
				strcpy_s(card[i].Name, "四万");
				break;
			case 5:
				strcpy_s(card[i].Name, "五万");
				break;
			case 6:
				strcpy_s(card[i].Name, "六万");
				break;
			case 7:
				strcpy_s(card[i].Name, "七万");
				break;
			case 8:
				strcpy_s(card[i].Name, "八万");
				break;
			case 9:
				strcpy_s(card[i].Name, "九万");
				break;
			}
			break;
		case 2:
			switch (card[i].Number % 10) {
			case 1:
				strcpy_s(card[i].Name, "一条");
				break;
			case 2:
				strcpy_s(card[i].Name, "二条");
				break;
			case 3:
				strcpy_s(card[i].Name, "三条");
				break;
			case 4:
				strcpy_s(card[i].Name, "四条");
				break;
			case 5:
				strcpy_s(card[i].Name, "五条");
				break;
			case 6:
				strcpy_s(card[i].Name, "六条");
				break;
			case 7:
				strcpy_s(card[i].Name, "七条");
				break;
			case 8:
				strcpy_s(card[i].Name, "八条");
				break;
			case 9:
				strcpy_s(card[i].Name, "九条");
				break;
			}
			break;
		case 3:
			switch (card[i].Number % 10) {
			case 1:
				strcpy_s(card[i].Name, "一筒");
				break;
			case 2:
				strcpy_s(card[i].Name, "二筒");
				break;
			case 3:
				strcpy_s(card[i].Name, "三筒");
				break;
			case 4:
				strcpy_s(card[i].Name, "四筒");
				break;
			case 5:
				strcpy_s(card[i].Name, "五筒");
				break;
			case 6:
				strcpy_s(card[i].Name, "六筒");
				break;
			case 7:
				strcpy_s(card[i].Name, "七筒");
				break;
			case 8:
				strcpy_s(card[i].Name, "八筒");
				break;
			case 9:
				strcpy_s(card[i].Name, "九筒");
				break;
			}
			break;
		}
	}
	for (int i = 0; i <= 135; i++) {//初始化乱序前的全部牌的容器
		OldArray.push_back(card[i]);
	}
	CardWash(OldArray, NewArray);//洗牌
	return;
}

//洗牌函数
void CardWash(vector<Card> &OldArray, vector<Card> &NewArray) {
	for (int i = 135; i > 0; i--) {
		srand(unsigned(time(NULL)));
		// 选中的随机下标
		int index = rand() % i;
		// 根据选中的下标将原数组选中的元素push到新数组
		NewArray.push_back(OldArray[index]);
		// 将原数组中选中的元素剔除
		OldArray.erase(OldArray.begin() + index);
	}
	/*for (vector<Card>::iterator it = NewArray.begin(); it != NewArray.end(); it++) {
	cout << it->Name << it->Number <<" ";
	}
	cout << endl;*/
	return;
}

//显示PC玩家出的牌
void CardThatPcJustGiveOut(int pcplayer) {
	switch (pcplayer) {
	case 1:
		cout << "PC1出的牌为：" << GiveOutArray.back().Name << endl;
		break;
	case 2:
		cout << "PC2出的牌为：" << GiveOutArray.back().Name << endl;
		break;
	case 3:
		cout << "PC3出的牌为：" << GiveOutArray.back().Name << endl;
		break;
	default:
		break;
	}
	return;
}

//显示剩余牌数
void CardLeft() {
	int NO = NewArray.size();
	cout << endl << "                                                                     剩余牌数: " << NO << endl;
	return;
}

//发牌函数
void CardGiveout() {
	int count = 1;
	for (int i = 135; i >83; i--) {
		switch (count)
		{
		case 1:
			Player.push_back(NewArray.back());//玩家手牌容器
			break;
		case 2:
			PlayerC1.push_back(NewArray.back());//电脑玩家1手牌容器
			break;
		case 3:
			PlayerC2.push_back(NewArray.back());//电脑玩家1手牌容器
			break;
		case 4:
			PlayerC3.push_back(NewArray.back());//电脑玩家1手牌容器
			break;
		default:
			break;
		}
		NewArray.pop_back();
		if (count == 4)
			count = 1;
		else
		{
			count++;
		}

	}
	return;
}

//碰牌或明杠函数
int CardPengOrMingGang() {
	int count = 0;
	char YorN;
	int GorPorN = 0;
	Card  temp;
	vector <Card>::iterator it = Player.begin();
	if (!GiveOutArray.empty()) {
		for (; it != Player.end(); it++) {
			if ((*it).Number == GiveOutArray.back().Number) {
				count++;
			}
		}
	}
	if (count == 2) {
		it = Player.begin();
		cout << "是否碰？Y/N" << endl;
		cin >> YorN;
		while (YorN != 'Y' && YorN != 'y' && YorN != 'n' && YorN != 'N') {
			cout << "输入有误请重新输入？Y/N" << endl;
			cin >> YorN;
		}
		if (YorN == 'y' || YorN == 'Y') {
			for (; it != Player.end(); ) {
				if ((*it).Number == GiveOutArray.back().Number) {
					temp.Number = GiveOutArray.back().Number;
					strcpy_s(temp.Name, (GiveOutArray.back().Name));
					PlayerGangAndPeng.push_back(temp);
					PlayerGangAndPeng.push_back(temp);
					PlayerGangAndPeng.push_back(temp);
					sort(PlayerGangAndPeng.begin(), PlayerGangAndPeng.end(), myobject);//对玩家的碰杠牌按牌号从小到大排序
					it = Player.erase(it);
					if (it != Player.end()) {
						it = Player.erase(it);//不等于最后一个要指向下一个
					}
					else {
						Player.erase(it);//等于最后一个，it指向不重新赋值
					}
					
				}
				else {
					it++;
				}
			}
			return 1;//碰返回1
		}
		else if (YorN == 'n' || YorN == 'N') {
			return 0;//不操作返回0
		}
		else {
			return 0;
		}
	}
	if (count == 3) {
		it = Player.begin();
		cout << "选择碰或者杠或不操作？1/2/3" << endl;
		cin >> GorPorN;
		while (GorPorN != 1 && GorPorN != 2 && GorPorN != 3) {
			cout << "输入有误请重新输入？Y/N" << endl;
			cin >> GorPorN;
		}
		int count1 = 0;
		switch (GorPorN) {
		case 1:
			for (; it != Player.end(); ) {
				if ((*it).Number == GiveOutArray.back().Number) {
					temp.Number = GiveOutArray.back().Number;
					strcpy_s(temp.Name, (GiveOutArray.back().Name));
					PlayerGangAndPeng.push_back(temp);
					PlayerGangAndPeng.push_back(temp);
					PlayerGangAndPeng.push_back(temp);
					sort(PlayerGangAndPeng.begin(), PlayerGangAndPeng.end(), myobject);
					it = Player.erase(it);
					Player.erase(it);
					count1=2;
					if (count1 == 2) {
						return 1;//碰返回1
					}
				}
				else {
					it++;
				}
			}
			break;
		case 2:
			for (; it != Player.end();) {
				if ((*it).Number == GiveOutArray.back().Number) {
					temp.Number = GiveOutArray.back().Number;
					strcpy_s(temp.Name, (GiveOutArray.back().Name));
					PlayerGangAndPeng.push_back(temp);
					PlayerGangAndPeng.push_back(temp);
					PlayerGangAndPeng.push_back(temp);
					PlayerGangAndPeng.push_back(temp);
					sort(PlayerGangAndPeng.begin(), PlayerGangAndPeng.end(), myobject);
					it = Player.erase(it);
					it = Player.erase(it);
					Player.erase(it);
					count1=3;
					if (count1 == 3) {
						return 2;//杠返回2
					}
				}
				else {
					it++;
				}
			}
			break;
		case 3:
			return 0;
		default:
			return 0;
		}
	}
	return 0;
}

//暗杠牌函数
void CardAnGang() {

}

//胡牌函数
int CardCanHu(int IsPlayerOrPC) {
	int length = Player.size() - 1;
	int first = 0;
	while (first != length) {
		for (int second = first + 1; second <= length; second++) {
			if (Player[first].Number == Player[second].Number) {
				vector <Card> temp(Player);
				temp.erase(temp.begin() + first);
				temp.erase(temp.begin() + second - 1);
				vector <Card> temp1(temp);
				while (!temp1.empty()) {
					if (((*temp1.begin()).Number == (*(temp1.begin() + 1)).Number == (*(temp1.begin() + 2)).Number)
						|| ((*temp1.begin()).Number + 1 == (*(temp1.begin() + 1)).Number && (*temp1.begin()).Number + 2 == (*(temp1.begin() + 2)).Number)) {
						temp1.erase(temp1.begin());
						temp1.erase(temp1.begin());
						temp1.erase(temp1.begin());
					}
					else if (temp1.empty()) {
						cout << "是否要胡牌?Y/N" << endl;
						char YorN;
						cin >> YorN;
						if (YorN == 'Y' || YorN == 'y') {
							return 1;//可以胡牌返回1
						}
						else if (YorN == 'N' || YorN == 'n') {
							return 0;
						}
						else {
							return 0;
						}
					}
					else if (((*temp1.begin()).Number != (*(temp1.begin() + 1)).Number) || ((*temp1.begin()).Number + 1 != (*(temp1.begin() + 1)).Number)) {
						break;
					}
				}
			}
		}
		first++;
	}
	return 0;
}

//显示玩家手牌
void CardInHand() {
	cout << endl << "----------------------------------------手牌----------------------------------------" << endl;
	int length = Player.end() - Player.begin();
	for (int i = 1; i <= length - 5; i++) {
		cout << i;
		cout << "     ";
	}
	for (int i = length - 4; i <= length; i++) {
		cout << i;
		cout << "    ";
	}
	cout << endl;
	vector <Card>::iterator it = Player.begin();
	for (; it != Player.end(); it++) {
		if (((*it).Name)[2] == '\0') {
			cout << (*it).Name << "    ";
		}
		else {
			cout << (*it).Name << "  ";
		}
	}
	cout << endl << "------------------------------------------------------------------------------------" << endl;
	cout << endl;
	cout << endl << "----------杠和碰的牌------------" << endl;
	if (PlayerGangAndPeng.empty()==false) {
		vector <Card>::iterator it1 = PlayerGangAndPeng.begin();
		for (; it1 != PlayerGangAndPeng.end(); it1++) {
			if (((*it1).Name)[2] == '\0') {
				cout << (*it1).Name << "    ";
			}
			else{
				cout << (*it1).Name << "  ";
			}
		}
	}
	cout << endl << " --------------------------------" << endl;
	cout << endl;
	cout << endl;
	return;
}

//摸牌函数
void NextCard(int IsPlayerOrPC) {
	switch (IsPlayerOrPC)
	{
	case 1:
		Player.push_back(NewArray.back());
		NewArray.erase(NewArray.end() - 1);
		sort(Player.begin(), Player.end(), myobject);//对玩家的牌按牌号从小到大排序
		break;
	case 2:
		PlayerC1.push_back(NewArray.back());
		NewArray.erase(NewArray.end() - 1);
		break;
	case 3:
		PlayerC2.push_back(NewArray.back());
		NewArray.erase(NewArray.end() - 1);
		break;
	case 4:
		PlayerC3.push_back(NewArray.back());
		NewArray.erase(NewArray.end() - 1);
		break;
	default:
		break;

	}
}

//出牌函数
void GiveUpCard(int IsPlayerOrPC) {
	Card  temp;
	switch (IsPlayerOrPC)
	{
	case 1:
		cout << "请选择要出的牌:";
		int NO;
		cin >> NO;
		Player.erase(Player.begin() + NO - 1);
		CardInHand();
		break;
	case 2:
		temp.Number = (*PlayerC1.begin()).Number;
		strcpy_s(temp.Name, ((*PlayerC1.begin()).Name));
		PlayerC1.erase(PlayerC1.begin());
		GiveOutArray.push_back(temp);
		CardThatPcJustGiveOut(1);
		break;
	case 3:
		temp.Number = (*PlayerC2.begin()).Number;
		strcpy_s(temp.Name, ((*PlayerC2.begin()).Name));
		PlayerC2.erase(PlayerC2.begin());
		GiveOutArray.push_back(temp);
		CardThatPcJustGiveOut(2);
		break;
	case 4:
		temp.Number = (*PlayerC3.begin()).Number;
		strcpy_s(temp.Name, ((*PlayerC3.begin()).Name));
		PlayerC3.erase(PlayerC3.begin());
		GiveOutArray.push_back(temp);
		CardThatPcJustGiveOut(3);
		break;
	default:
		break;
	}
}

//当前玩家逻辑
int excute(int player,int gangorpeng) {//传入当前玩家id，是否碰或杠
	if (NewArray.empty()) {
		return 1;
	}
	int CanHu = 0;
	if (gangorpeng == 0|| gangorpeng == 2) {
		NextCard(player);//摸牌函数
	}
	CardLeft();//显示剩余牌数
	if (player == 1) {
		CardInHand(); //是玩家则显示手牌
		CanHu = CardCanHu(player);// 判断是否能胡，能1，不能0
	}
	if (CanHu == 0) {
		GiveUpCard(player);//出牌函数
	}
	return CanHu;//返回是否当前玩家是否选择了胡的信息；
}

//交互界面
void UI() {
	int PLAYER = 1;
	int PC1 = 2;
	int PC2 = 3;
	int PC3 = 4;
	int CanHu = 0;
	int pengorgang=0;
	cout << "                                       " << "广东麻将" << endl;
	Init();
	CardGiveout();
	cout << "                                 " << "洗牌完成，对局开始！" << endl;
	while (CanHu != 1 && !NewArray.empty()) {
		CanHu = excute(PLAYER,pengorgang);
		CanHu = excute(PC1,0);
		pengorgang=CardPengOrMingGang();//碰或杠以后置1（目前仅玩家可碰或杠）;
		if (pengorgang == 1|| pengorgang == 2) {
			pengorgang = 0;//重置0;
			continue;
		}
		CanHu = excute(PC2,0);
		pengorgang = CardPengOrMingGang();//碰或杠以后置1（目前仅玩家可碰或杠）;
		if (pengorgang == 1 || pengorgang == 2) {
			pengorgang = 0;
			continue;
		}
		CanHu = excute(PC3,0);
		pengorgang = CardPengOrMingGang();//碰或杠以后置1（目前仅玩家可碰或杠）;
		if (pengorgang == 1 || pengorgang == 2) {
			pengorgang = 0;
			continue;
		}
	}
	cout << "                                     " << "对局结束！" << endl;
	return;
}


int main()
{
	UI();
	return 0;
}

