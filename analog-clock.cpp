#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<easyx.h>
#include <iostream>
#include<time.h>
#include<math.h>
#include<string.h>
#include<Windows.h>
#undef UNICODE
#define pi 3.1415926
void roundrect(int left, int top, int right, int bottom, int ellipsewidth, int ellipseheight);
void DralDial1();
void Draw_Hand(int hour, int minute, int second, int millsecond);
void Draw_NEWHand(int hour, int minute, int second, int millsecond);
void date();

int main()
{
	time_t t;
	int i;
	struct tm* nowTime;
	int hour, min, sec;
	char time_h[3] = { 00 }, time_m[3] = { 00 }, time_s[3];
	int hor = 0, mn = 0, sc = 0;
	int cnt = 0;
	int mClock = 0;
	initgraph(480, 520);
	MOUSEMSG m; //定义鼠标信息
	DralDial1();//绘制表盘
	SYSTEMTIME time;
	BeginBatchDraw();
	while (1)
	{
		GetLocalTime(&time);//获取当前的时间
		//time.
		Draw_Hand(time.wHour, time.wMinute, time.wSecond, time.wMilliseconds); //把表针绘制出来
		mClock = cnt / 10;
		hor = mClock / 3600;      //获取计时小时数
		mn = mClock / 60;          //获取计时分钟数
		sc = mClock % 60;//获取计时秒数
		sprintf_s(time_h, "%02d", hor);
		sprintf_s(time_m, "%02d", mn);
		sprintf_s(time_s, "%02d", sc);  //实现秒表功能
		outtextxy(190, 380, time_h);
		outtextxy(230, 380, time_m);
		outtextxy(270, 380, time_s);
		FlushBatchDraw();
		Sleep(100);
		cnt++;
		date();

		Draw_NEWHand(time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	}
	EndBatchDraw();
	closegraph();
}

void Draw_Hand(int hour, int minute, int second, int millsecond)

{

	double h_hour, h_minute, h_second; //三个弧度值
	double h_millsecond;//毫秒弧度值

	int x_hour, y_hour, x_minute, y_minute, x_second, y_second; //末尾位置

	//盘算弧度值
	h_millsecond = (double)millsecond / 1000 * 2 * pi / 60;
	h_second = second * 2 * pi / 60;
	h_second = h_second + h_millsecond;

	h_minute = minute * 2 * pi / 60 + h_second / 60;

	h_hour = hour * 2 * pi / 12 + h_minute / 12;

	//盘算末尾位置

	x_second = int(120 * sin(h_second));
	y_second = int(120 * cos(h_second));
	//std::cout << "x_second:" << x_second << "\ty_second:" << y_second << std::endl;

	x_minute = int(100 * sin(h_minute));
	y_minute = int(100 * cos(h_minute));

	x_hour = int(70 * sin(h_hour));
	y_hour = int(70 * cos(h_hour));

	//绘制秒针

	setlinestyle(PS_SOLID, 4);

	setcolor(RGB(255, 211, 155));

	line(240 + x_second, 260 - y_second, 240 - x_second / 3, 260 + y_second / 3);

	//绘制分针

	setlinestyle(PS_SOLID, 6);

	setcolor(RGB(189, 183, 10));

	line(240 + x_minute, 260 - y_minute, 240 - x_minute / 5, 260 + y_minute / 5);

	//绘制时针

	setlinestyle(PS_SOLID, 9);

	setcolor(RGB(139, 69, 19));

	line(240 + x_hour, 260 - y_hour, 240 - x_hour / 5, 260 + y_hour / 5);
	int x, y;
	setlinecolor(RGB(139, 117, 0));
	setlinestyle(PS_SOLID, 2);
	for (int i = 0; i < 60; i = i + 15)

	{
		x = 240 + int(170 * sin(pi * 2 * i / 60));

		y = 260 + int(170 * cos(pi * 2 * i / 60));

		if (i == 30 || i == 60 || i == 0) {

			rectangle(x - 7, y - 30, x + 7, y + 30);
			setfillcolor(RGB(255, 193, 37));
			fillrectangle(x - 7, y - 30, x + 7, y + 30);
		}

		if (i == 15 || i == 45)
		{
			rectangle(x - 30, y - 7, x + 30, y + 7);
			setfillcolor(RGB(255, 193, 37));
			fillrectangle(x - 30, y - 7, x + 30, y + 7);
		}
	}
	setcolor(WHITE);
	settextstyle(40, 0, "Kunstler Script");
	outtextxy(218, 380, ":");
	outtextxy(258, 380, ":");
}
void Draw_NEWHand(int hour, int minute, int second, int millsecond)  //用黑色指针覆盖
{
	double h_hour, h_minute, h_second;

	double h_millsecond;//毫秒弧度值

	int x_hour, y_hour, x_minute, y_minute, x_second, y_second;

	h_second = second * 2 * pi / 60;
	h_millsecond = (double)millsecond / 1000 * 2 * pi / 60;
	h_second += h_millsecond;

	h_minute = minute * 2 * pi / 60 + h_second / 60;

	h_hour = hour * 2 * pi / 12 + h_minute / 12;

	x_second = int(120 * sin(h_second)); y_second = int(120 * cos(h_second));

	x_minute = int(100 * sin(h_minute)); y_minute = int(100 * cos(h_minute));

	x_hour = int(70 * sin(h_hour)); y_hour = int(70 * cos(h_hour));
	setcolor(BLACK);
	setlinestyle(PS_SOLID, 4);
	line(240 + x_second, 260 - y_second, 240 - x_second / 3, 260 + y_second / 3);
	setlinestyle(PS_SOLID, 6);
	line(240 + x_minute, 260 - y_minute, 240 - x_minute / 5, 260 + y_minute / 5);
	setlinestyle(PS_SOLID, 9);
	line(240 + x_hour, 260 - y_hour, 240 - x_hour / 5, 260 + y_hour / 5);
	settextcolor(RGB(255, 250, 205));
	settextstyle(60, 0, "Vladimir Script");
	outtextxy(215, 150, "Ω");
	settextstyle(45, 0, "Arial Rounded MT Bold");
	outtextxy(170, 190, "OMEGA");
	settextcolor(RGB(178, 34, 34));
	settextstyle(40, 0, "Brush Script MT");
	outtextxy(185, 227, "seamaster");
	int x, y;

	for (int i = 0; i < 60; i = i + 15)

	{
		x = 240 + int(170 * sin(pi * 2 * i / 60));

		y = 260 + int(170 * cos(pi * 2 * i / 60));

		if (i == 30 || i == 60 || i == 0) {

			rectangle(x - 7, y - 30, x + 7, y + 30);
			setfillcolor(RGB(255, 193, 37));
			fillrectangle(x - 7, y - 30, x + 7, y + 30);
		}

		if (i == 15 || i == 45)
		{
			rectangle(x - 30, y - 7, x + 30, y + 7);
			setfillcolor(RGB(255, 193, 37));
			fillrectangle(x - 30, y - 7, x + 30, y + 7);
		}
	}
}
void DralDial1()//画表盘
{
	int i;
	int x1, y1, x2, y2, x5, y5; //表心坐标系坐标 

	setlinecolor(RGB(139, 119, 101));
	setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 2);
	roundrect(20, 20, 460, 500, 220, 240);
	setfillcolor(BLACK);
	fillroundrect(20, 20, 460, 500, 220, 240);
	roundrect(40, 40, 440, 480, 200, 220);
	setfillcolor(BLACK);
	fillroundrect(40, 40, 440, 480, 200, 220);
	setlinestyle(PS_SOLID, 2);

	circle(240, 260, 6);
	setfillcolor(BLUE);
	fillcircle(240, 260, 5);
	circle(240, 260, 200);
	for (i = 0; i <= 59; i++) {
		if (i % 5 == 0) {
			setlinestyle(PS_SOLID, 3);
			setlinecolor(RGB(139, 115, 85));
			//line(240 + 170 * sin(i * pi / 30), 260 - 170 * cos(i * pi / 30), 240 + 200 * sin(i * pi / 30), 260 - 200 * cos(i * pi / 30)); // 画时钟线
			circle(240 + 170 * sin(i * pi / 30), 260 - 170 * cos(i * pi / 30), 10);
			setfillcolor(RGB(255, 193, 37));
			fillcircle(240 + 170 * sin(i * pi / 30), 260 - 170 * cos(i * pi / 30), 10);
		}
		else
			setlinestyle(PS_SOLID, 1);
		line(240 + 185 * sin(i * pi / 30), 260 - 185 * cos(i * pi / 30), 240 + 200 * sin(i * pi / 30), 260 - 200 * cos(i * pi / 30)); //画分秒线
	}
	settextcolor(RGB(255, 250, 205));
	settextstyle(60, 0, "Vladimir Script");
	outtextxy(215, 150, "Ω");
	settextstyle(45, 0, "Arial Rounded MT Bold");
	outtextxy(170, 190, "OMEGA");
	settextcolor(RGB(178, 34, 34));
	settextstyle(40, 0, "Brush Script MT");
	outtextxy(185, 227, "seamaster");
}

void date()
{
	int year = 0, month = 0, day = 0;
	char date_y[5] = { 0000 }, date_m[3] = { 00 }, date_d[3];
	struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间
	setcolor(WHITE);
	settextstyle(25, 0, "Ink Free");
	year = t.tm_year + 1900;
	month = t.tm_mon + 1;
	day = t.tm_mday;
	setlinecolor(RGB(131, 139, 191));
	roundrect(180, 345, 310, 380, 30, 35);

	setcolor(WHITE);
	sprintf_s(date_y, "%02d", year);
	sprintf_s(date_m, "%02d", month);
	sprintf_s(date_d, "%02d", day);
	outtextxy(190, 350, (date_y));
	outtextxy(240, 350, "-");
	outtextxy(250, 350, (date_m));
	outtextxy(270, 350, "-");
	outtextxy(280, 350, (date_d));



}


