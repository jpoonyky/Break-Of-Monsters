#include	"Controller.h"

void Controller::KeyCheck()
{
	int bit=0;
	keycode = 0;

	keycode |= (KEY_Get( KEY_A )<<bit);
	bit += 2;
	keycode |= (KEY_Get( KEY_B )<<bit);
	bit += 2;
	keycode |= (KEY_Get( KEY_C )<<bit);
	bit += 2;
	keycode |= (KEY_Get( KEY_D )<<bit);
	bit += 2;

	keycode |= (KEY_Get( KEY_UP )<<bit);
	bit += 2;
	keycode |= (KEY_Get( KEY_DOWN )<<bit);
	bit += 2;
	keycode |= (KEY_Get( KEY_LEFT )<<bit);
	bit += 2;
	keycode |= (KEY_Get( KEY_RIGHT )<<bit);
	bit += 2;

	keycode |= (KEY_Get( KEY_L1 )<<bit);
	bit += 2;
	keycode |= (KEY_Get( KEY_R1 )<<bit);
	bit += 2;
	keycode |= (KEY_Get( KEY_L2 )<<bit);
	bit += 2;
	keycode |= (KEY_Get( KEY_R2 )<<bit);
	bit += 2;

	keycode |= (KEY_Get( KEY_L3 )<<bit);
	bit += 2;
	keycode |= (KEY_Get( KEY_R3 )<<bit);
	bit += 2;
	keycode |= (KEY_Get( KEY_START )<<bit);
	bit += 2;
	keycode |= (KEY_Get( KEY_SELECT )<<bit);

	axisX = KEY_GetAxisX();
	axisY = KEY_GetAxisY();
}
