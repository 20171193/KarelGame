#ifndef __KAREL_H__
#define __KAREL_H__
#include <iostream>
#include <windows.h>
using namespace std;

#define DEFAULT_WIDTH 5
#define DEFAULT_HEIGHT 5

int dx[4] = { 1,0,-1,0 };
int dy[4] = { 0,1,0,-1 };
char beeper = '#', road = '\"', agentDir[4] = { '>', '^', '<', 'v' };
char myMap[101][101];

struct Transform {
	int x;
	int y;
	int d;
};

class KarelGame {
public:
	KarelGame() {
		
	}
	~KarelGame() {
	}

	// StartGame
	void Start() {
		cout << "너비와 높이를 입력하시오. (1 <= 너비(*홀수),높이 <= 100)\n";
		cin >> width >> height;
		while ((1 > width || 100 < width) || (1 > height || 100 < height) || (width % 2 == 0)) {
			cout << "다시 입력하세요. (1 <= 너비(*홀수),높이 <= 100)\n";
			cin >> width >> height;
		}
		Setting();
	}
	void End() {
		Sleep(200);
		system("cls");
		Sleep(50);

		if (checkGameClear()) {
			cout << "--------------------------\n";
			cout << "--------------------------\n";
			cout << "--------------------------\n";
			cout << "       게임 클리어!!       \n";
			cout << "--------------------------\n";
			cout << "--------------------------\n";
			cout << "--------------------------\n";
		}
		else {
			cout << "--------------------------\n";
			cout << "--------------------------\n";
			cout << "--------------------------\n";
			cout << "          실패!!          \n";
			cout << "--------------------------\n";
			cout << "--------------------------\n";
			cout << "--------------------------\n";
		}
	}

private:
	// map, Karel setting
	void Setting() {
		tr.x = 0;
		tr.y = height - 1;
		tr.d = 0;

		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				myMap[y][x] = '\"';
			}
		}
		myMap[tr.y][tr.x] = agentDir[tr.d];
	}

	// rendering 
	void Render() {
		Clear();
		cout << "\n";
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				cout << myMap[y][x];
			}
			cout << "\n";
		}
	}

	// clear
	void Clear() {
		Sleep(500);
		system("cls");
	}

public:
	// action
	void TurnLeft() {
		tr.d = (tr.d + 1) % 4;
		if (!BeepersPresent()) myMap[tr.y][tr.x] = agentDir[tr.d];
		Render();
	}
	void Move() {
		int _x = tr.x + dx[tr.d];
		int _y = tr.y + dy[tr.d];
		if (!checkClear(_x, _y)) {
			for (int i = 0; i < 4; i++) {
				Sleep(200);
				system("cls");
				cout << "Front Is Block!";
				for (int j = 0; j < i; j++) {
					cout << " !";
				}
				cout << "\n";
			}
			Sleep(1000);
			system("cls");
			Sleep(50);
			cout << "--------------------------\n";
			cout << "--------------------------\n";
			cout << "--------------------------\n";
			cout << "          실패!!          \n";
			cout << "--------------------------\n";
			cout << "--------------------------\n";
			cout << "--------------------------\n";
			system("pause");
			return;
		}
		if (myMap[tr.y][tr.x] != beeper) myMap[tr.y][tr.x] = road;
		if (myMap[_y][_x] != beeper) myMap[_y][_x] = agentDir[tr.d];
		tr.x = _x;  tr.y = _y;

		Render();
	}

public:
	// facing
	bool FacingNorth() {
		if (tr.d == 1) return true;
		return false;
	}
	bool FacingEast() {
		if (tr.d == 0) return true;
		return false;
	}
	bool FacingSouth() {
		if (tr.d == 2) return true;
		return false;
	}
	bool FacingWest() {
		if (tr.d == 3) return true;
		return false;
	}

private:
	// check next position
	bool checkClear(int nx, int ny) {
		if (nx >= width || nx < 0 || ny >= height || ny < 0) return false;
		return true;
	}
public:
	bool FrontIsClear() {
		int _x = dx[tr.d] + tr.x;
		int _y = dy[tr.d] + tr.y;
		return checkClear(_x, _y);
	}
	bool LeftIsClear() {
		int _x = dx[(tr.d + 1) % 4] + tr.x;
		int _y = dy[(tr.d + 1) % 4] + tr.y;
		return checkClear(_x, _y);
	}
	bool RightIsClear() {
		int _x = dx[(tr.d + 3) % 4] + tr.x;
		int _y = dy[(tr.d + 3) % 4] + tr.y;
		return checkClear(_x, _y);
	}

	// check current position
	bool BeepersPresent() {
		if (myMap[tr.y][tr.x] == beeper) return true;
		return false;
	}

public:
	// Beeper 
	void PutBeeper() {
		myMap[tr.y][tr.x] = beeper;
		Render();
	}
	void PickBeeper() {
		myMap[tr.y][tr.x] = agentDir[tr.d];
		Render();
	}

	// check game clear
	bool checkGameClear() {
		pair<int, int> midPoint = { height - 1, width / 2 };
		for (int y = 0; y < height; y++) {
			for (int x = 0; x < width; x++) {
				if (myMap[y][x] == beeper) {
					if (y == midPoint.first && x != midPoint.second) return false;
				}
			}
		}
		if (tr.x != width - 1 || tr.y != height - 1 || tr.d != 0) return false;

		return true;
	}
private:
	int width, height;
	Transform tr;
};

#endif