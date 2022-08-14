#include "LifeBar.h"

LifeBar::LifeBar(PlayerObject* v)
{
	this->viktor = v;
}

LifeBar::~LifeBar()
{
}

void LifeBar::Draw(HDC screen)
{
	// Update the current health
	int _height = 80 * (double)viktor->currentHealth / viktor->totalHealth;

	// define red and white brushes
	HBRUSH _hbrRed, _hbrWhite;

	// define the colors repesented by brushes
	_hbrRed = CreateSolidBrush(RGB(255, 0, 0));
	_hbrWhite = CreateSolidBrush(RGB(255, 255, 255));

	//tell the screen to use the white brush
	SelectObject(screen, _hbrWhite);
	Rectangle(screen, 10, 10, 20, 90);

	//tell the screen to use the red brush
	SelectObject(screen, _hbrRed);
	Rectangle(screen, 10, 90 - _height, 20, 90);

	// delete brushes from memory
	DeleteObject(_hbrRed);
	DeleteObject(_hbrWhite);
}
