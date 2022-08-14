#include "LifeBarEnemy.h"

LifeBarEnemy::LifeBarEnemy(EnemyObject* e)
{
	this->enemy = e;
}

LifeBarEnemy::~LifeBarEnemy()
{
}

void LifeBarEnemy::Draw(HDC screen)
{
	// Update the current health
	int _height = 80 * (double)enemy->currentHealth / enemy->totalHealth;

	// define red and white brushes
	HBRUSH _hbrRed, _hbrWhite;

	// define the colors repesented by brushes
	_hbrRed = CreateSolidBrush(RGB(255, 0, 0));
	_hbrWhite = CreateSolidBrush(RGB(255, 255, 255));

	//tell the screen to use the white brush
	SelectObject(screen, _hbrWhite);
	Rectangle(screen, enemy->xPos, 10, enemy->xPos + 10, 90);

	//tell the screen to use the red brush
	SelectObject(screen, _hbrRed);
	Rectangle(screen, enemy->xPos, 90 - _height, enemy->xPos + 10, 90);

	// delete brushes from memory
	DeleteObject(_hbrRed);
	DeleteObject(_hbrWhite);
}
