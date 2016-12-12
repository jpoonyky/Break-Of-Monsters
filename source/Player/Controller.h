#pragma once

#include	"iextreme.h"

class Controller
{
private:
	unsigned int keycode;
	int axisX , axisY;

public:
	void KeyCheck();
	int GetKey( int num );
	int Getkeycode() { return keycode; }
	int GetaxisX() { return axisX; }
	int GetaxisY() { return axisY; }
};