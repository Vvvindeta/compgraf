#include <iostream>
#include <conio.h>
#include <cmath>
#include <stdlib.h>
#include "graphics.h"
#pragma comment(lib,"graphics.lib")
#define M_PI 3.14
#define stdN 5
using namespace std;

void Draw();
void DrawFigure();
void Moving(char key);
void Spin(char key);
void Scaling(char key);
void CulculateTops();

struct Point {
	double x, y;
};
int X = 0;
int Y = 0;
bool spinBool = 1;
double spin = 0;
int mas = 0;
double angle = 0;
Point* arr_points = new Point[stdN + 1];
int stdRadius[stdN] = { 50, 50, 50, 50, 50};
double rLogic[stdN] = {1, 1, 1, 1, 1};
int* ptr = &stdRadius[0];

int main() {
	initwindow(540, 540);
	Draw();
	closegraph();
	return 0;
}

void Draw() {
	char key;
	if (stdN < 3) {
		cout << "mission impossible, N must be greater 2\n";
		cin.get();
	}
	else {
		CulculateTops();
		int err = graphresult();
		if (err != grOk) {
			cout << "ERROR" << grapherrormsg(err);
			cout << "Press any key to halt";
			cin.get();
			exit(1);
		}
		else {
			while (true) {
				system("cls");
				cleardevice();
				DrawFigure();
				key = _getch();
				if (key == 'd' || key == 'a' || key == 'w' || key == 's') {
					Moving(key);
				}
				if (key == 'q' || key == 'e') {
					Spin(key);
				}
				if (key == '+' || key == '-' || key == '=') {
					Scaling(key);
				}
			}
		}
		cin.get();
		closegraph();
		cin.get();
	}
}

void DrawFigure() {
	moveto(arr_points[0].x + (getmaxx() / 2 + X), arr_points[0].y + (getmaxy() / 2 + Y)); //устанавливаем курсор на точку начала рисования
	for (int i = 1; i <= stdN; i++) {
		setcolor(YELLOW);
		lineto(arr_points[i].x + (getmaxx() / 2 + X), arr_points[i].y + (getmaxy() / 2 + Y)); // Соединяем линии.Выводим это со смещением в центр экрана
	}
}

void CulculateTops() {
	for (int i = 0; i <= stdN; i++) {
		if (i == 0 && (stdRadius[i] < stdRadius[stdN - 1] && stdRadius[i] < stdRadius[i + 1])) {
			if (stdRadius[i] + mas <= 0) {
				rLogic[i] = 0;
				arr_points[i].x = ((stdRadius[i] + (mas / 3)) * rLogic[i]) * cos((angle * M_PI / 180) + spin);
				arr_points[i].y = ((stdRadius[i] + (mas / 3)) * rLogic[i]) * sin((angle * M_PI / 180) + spin);
			}
			if (stdRadius[i] + mas > 0) {
				rLogic[i] = 1;
				arr_points[i].x = ((stdRadius[i] + (mas / 3)) * rLogic[i]) * cos((angle * M_PI / 180) + spin);
				arr_points[i].y = ((stdRadius[i] + (mas / 3)) * rLogic[i]) * sin((angle * M_PI / 180) + spin);
			}
		}
		else {
			if (i == (stdN - 1) && stdRadius[i] < stdRadius[i - 1] && stdRadius[i] < stdRadius[0]) {
				if (stdRadius[i] + mas <= 0) {
					rLogic[i] = 0;
					arr_points[i].x = ((stdRadius[i] + (mas / 3)) * rLogic[i]) * cos((angle * M_PI / 180) + spin);
					arr_points[i].y = ((stdRadius[i] + (mas / 3)) * rLogic[i]) * sin((angle * M_PI / 180) + spin);
				}
				if (stdRadius[i] + mas > 0) {
					rLogic[i] = 1;
					arr_points[i].x = ((stdRadius[i] + (mas / 3)) * rLogic[i]) * cos((angle * M_PI / 180) + spin);
					arr_points[i].y = ((stdRadius[i] + (mas / 3)) * rLogic[i]) * sin((angle * M_PI / 180) + spin);
				}
			}
			else {
				if (stdRadius[i] < stdRadius[i - 1] && stdRadius[i] < stdRadius[i + 1]) {
					if (stdRadius[i] + mas <= 0) {
						rLogic[i] = 0;
						arr_points[i].x = ((stdRadius[i] + (mas / 3)) * rLogic[i]) * cos((angle * M_PI / 180) + spin);
						arr_points[i].y = ((stdRadius[i] + (mas / 3)) * rLogic[i]) * sin((angle * M_PI / 180) + spin);
					}
					if (stdRadius[i] + mas > 0) {
						rLogic[i] = 1;
						arr_points[i].x = ((stdRadius[i] + (mas / 3)) * rLogic[i]) * cos((angle * M_PI / 180) + spin);
						arr_points[i].y = ((stdRadius[i] + (mas / 3)) * rLogic[i]) * sin((angle * M_PI / 180) + spin);
					}
				}
				else {
					if (stdRadius[i] + mas <= 0) {
						rLogic[i] = 0;
						arr_points[i].x = ((stdRadius[i] + mas) * rLogic[i]) * cos((angle * M_PI / 180) + spin);
						arr_points[i].y = ((stdRadius[i] + mas) * rLogic[i]) * sin((angle * M_PI / 180) + spin);
					}
					if (stdRadius[i] + mas > 0) {
						rLogic[i] = 1;
						arr_points[i].x = ((stdRadius[i] + mas) * rLogic[i]) * cos((angle * M_PI / 180) + spin);
						arr_points[i].y = ((stdRadius[i] + mas) * rLogic[i]) * sin((angle * M_PI / 180) + spin);
					}
				}
			}
		}
		angle = angle + 360.0 / stdN;
	}
	arr_points[stdN].x = arr_points[0].x;
	arr_points[stdN].y = arr_points[0].y;
	angle = 0;
}

void Moving(char key) {

	if (key == 'd') {
		X += 10;
	}
	if (key == 'a') {
		X = X - 10;
	}
	if (key == 'w') {
		Y = Y - 10;
	}
	if (key == 's') {
		Y += 10;
	}
}

void Spin(char key) {
	if (key == 'q') {
		spinBool = 0;
		spin += 0.025;
	}
	if (key == 'e') {
		spinBool = 1;
		spin -= 0.025;
	}
	CulculateTops();
}

void Scaling(char key) {
	if (key == '+' || key == '=') {
		mas = mas + 20;
	}
	if (key == '-') {
		mas = mas - 20;
	}
	CulculateTops();
}