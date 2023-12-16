// Stanford Karel Unit 12 <Midpoint> 

#include "Karel.h"
using namespace std;

KarelGame *game;

// Karel commands
void move() { game->Move(); }
void turnLeft() { game->TurnLeft(); }
void putBeeper() { game->PutBeeper(); }
void pickBeeper() { game->PickBeeper(); }

// Karel conditions
bool frontIsClear() { return game->FrontIsClear(); }
bool leftIsClear() {  return game->LeftIsClear(); }
bool rightIsClear() { return game->RightIsClear(); }
bool facingNorth() { return game->FacingNorth(); }
bool facingEast() {  return game->FacingEast(); }
bool facingSouth() { return game->FacingSouth(); }
bool facingWest() {  return game->FacingWest(); }
bool beepersPresent() { return game->BeepersPresent(); }


// CustomFunction
void goStraight() {
	while (frontIsClear()) {
		move();
	}
}
void goStraightForBeeper() {
	while (!beepersPresent()) {
		move();
	}
}
void turnRight() {
	turnLeft();
	turnLeft();
	turnLeft();
}
void turnAround() {
	turnLeft(); 
	turnLeft();
}
void moveBack() {
	turnAround();
	move();
	turnAround();
}

int main() {
	game = new KarelGame();
	game->Start();

	// user custom
	putBeeper();
	goStraight();
	putBeeper();
	turnAround();

	move();

	while (!beepersPresent()) {
		goStraightForBeeper();
		pickBeeper();
		moveBack();
		putBeeper();
		turnAround();

		move();
	}

	pickBeeper();
	goStraight();
	// user custom end

	game->End();
	delete game;
	return 0;
}
