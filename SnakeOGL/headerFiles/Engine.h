#include "stdafx.h"

#include "glut.h"
#include "glaux.h"

// Данный файл содержит описание функций движка игры

// Структура спрайта
struct Sprite {
	int width ;
	int height ;
	GLuint texcode ;
} ;

// Поворот спрайта
enum SpriteDir { dLeft, dUp, dRight, dDown } ;

// Загрузка текстур
void loadTexture(GLuint * tex, const char * filename) ;
// Рендер спрайта
void renderSprite(const Sprite & spr, int x, int y) ;
// Рендер спрайта с поворотом
void renderSpriteRotated(const Sprite & spr, int x, int y, SpriteDir dir) ;
// Рендер чисел (по спрайтам-цифрам)
void renderDigits(int num, Sprite * digits, int x, int y) ;
// Рендер времени
void renderTimeStr(char * timestr, Sprite * digits, const Sprite & dsep, int x, int y) ;