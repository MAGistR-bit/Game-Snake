#include "stdafx.h"

#include "glut.h"
#include "glaux.h"

// ������ ���� �������� �������� ������� ������ ����

// ��������� �������
struct Sprite {
	int width ;
	int height ;
	GLuint texcode ;
} ;

// ������� �������
enum SpriteDir { dLeft, dUp, dRight, dDown } ;

// �������� �������
void loadTexture(GLuint * tex, const char * filename) ;
// ������ �������
void renderSprite(const Sprite & spr, int x, int y) ;
// ������ ������� � ���������
void renderSpriteRotated(const Sprite & spr, int x, int y, SpriteDir dir) ;
// ������ ����� (�� ��������-������)
void renderDigits(int num, Sprite * digits, int x, int y) ;
// ������ �������
void renderTimeStr(char * timestr, Sprite * digits, const Sprite & dsep, int x, int y) ;