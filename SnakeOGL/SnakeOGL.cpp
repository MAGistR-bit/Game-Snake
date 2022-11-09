// SnakeOGL.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

/*����������� ���������� GLUT*/
#include "glut.h"
#include "glaux.h"
#include "Engine.h"
#include "Snake.h"

// ���������� ���������� ��� �����������.
#pragma comment (lib, "glaux.lib")

int mainWindow ;
// �������. ������ - ����������� ������ � ������������ �������.
Sprite sprite_wall ;
Sprite sprite_rabbit ;
Sprite sprite_head ;
Sprite sprite_body ;
Sprite sprite_score ;
Sprite sprite_food ;
Sprite sprite_time ;
Sprite digits[10] ;
Sprite dsep ;
Sprite butnew ;
Sprite labwin ;
Sprite labfail ;

Snake * snake ;

// ���� �������.
int msec ;

// ���� �����.
char * tekfile = "map1" ;

// ������ �����.
const int BLOCKW = 38 ;
// ����. 
const int WINDOWW = 800 ;
const int WINDOWH = 600 ;
// ������.
const int LEFT = 10 ;
const int TOP = 10 ;
// ���� �������� �������� �� ��, ������� ����������� ��������� �� ���� ���.
const int MSEC_UPD = 70 ;
// ����� ������� ����������� ���������� ������ ����������.
const int DT = 10 ;
// ���������� ������.
const int BUTNEWX = 640 ;
const int BUTNEWY = 20 ;

// ������� �������.
// ��������� - ��������� ����������� �� ������. 
void display(){
 
  // ������ ������
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
    
  // ���� �����
  glColor3f(1.0,1.0,1.0) ;

  // ������ ���� (������������) ���� 
  for (int i=0; i<snake->getWidth(); i++)
	  for (int j=0; j<snake->getHeight(); j++) {
		    if (snake->isWallAt(i,j)) renderSprite(sprite_wall,LEFT+i*BLOCKW,TOP+j*BLOCKW) ;    
			if (snake->isBodyAt(i,j)) renderSprite(sprite_body,LEFT+i*BLOCKW,TOP+j*BLOCKW) ;    
			if (snake->isRabbitAt(i,j)) renderSprite(sprite_rabbit,LEFT+i*BLOCKW,TOP+j*BLOCKW) ;    
		}
 
	// ������ ������ ����.
	Direction tekdir ;
	int hx ;
	int hy ;
	snake->getHead(&hx,&hy,&tekdir) ;
	if (tekdir==dXminus) renderSpriteRotated(sprite_head,LEFT+hx*BLOCKW,TOP+hy*BLOCKW,dLeft) ;
	if (tekdir==dXplus) renderSpriteRotated(sprite_head,LEFT+hx*BLOCKW,TOP+hy*BLOCKW,dRight) ;
	if (tekdir==dYminus) renderSpriteRotated(sprite_head,LEFT+hx*BLOCKW,TOP+hy*BLOCKW,dUp) ;
	if (tekdir==dYplus) renderSpriteRotated(sprite_head,LEFT+hx*BLOCKW,TOP+hy*BLOCKW,dDown) ;
  
	// ������ ����� ����.
	renderSprite(butnew,BUTNEWX,BUTNEWY) ;    

	// ������ � ��������.
	renderSprite(sprite_score,630,110) ;    
	renderDigits(snake->getScore(),digits,636,150) ;

	renderSprite(sprite_food,630,200) ;    
	renderDigits(snake->getRabbitCount(),digits,636,240) ;

	renderSprite(sprite_time,635,290) ;    
	static char timestr[32] ;
	snake->getTimeStr(timestr) ;
	renderTimeStr(timestr,digits,dsep,636,330) ;
	
	// ��������� � ����� ����.
	if (snake->isGameOver()) {
		if (snake->isWin()) {
			glColor3f(0.5,1.0,0.5) ;
			renderSprite(labwin,630,400) ;    
		}
		else {
			glColor3f(1.0,0.5,0.5) ;
			renderSprite(labfail,630,400) ;    
		}
	}

  // ������������ �������.
  glutSwapBuffers();
}

// ������
void frameFunc(int value) {	
	// �������� �����
	msec-=DT ;
	// ���� ��������� ������� ����, �� ��������� ����.
	if (msec<=0) {
		snake->nextStep(MSEC_UPD) ;
		msec = MSEC_UPD ;	
		glutSetWindow(mainWindow);
		glutPostRedisplay(); 
	}
	// ������ ������ ������.
	glutTimerFunc(DT, frameFunc, 100);	
}

// ������� ����, ��������� ����� ����� ����
void mouseFunc(int button, int state, int x, int y) {
	if ((button == GLUT_LEFT_BUTTON)&&(state == GLUT_UP)) {
		if ((x>=BUTNEWX)&&(x<=BUTNEWX+butnew.width)&&(y>=BUTNEWY)&&(y<=BUTNEWY+butnew.height))
			snake = new Snake(tekfile) ;
		}
}

// ������� ��������� ������� ����, ������ ������������, ����� �������� � 2D.
void changeSize(int w, int h) {
	/*��������� ���������� OpenGL �� ��, ��� ����� ����� �������������� �� ���� �������*/
	glViewport(0,0,WINDOWW,WINDOWH);
	/*������ ��������� �����: ���������� �������, ��� ������� �����
	�������� � ����������. GL_PROJECTION - ������� ��������.*/
    glMatrixMode(GL_PROJECTION);
	/*������� ������� (������ ������� �������� ������� ������� �� ���������)*/
    glLoadIdentity();
    glOrtho(0.0f,WINDOWW,WINDOWH,0.0f,-1.0f,1.0f);
	/*� �������� ������� ������� ������ ��������-������� �������*/
    glMatrixMode(GL_MODELVIEW);
}

// ��������� ����������.
void specialKeys( int key, int x, int y ) {
	// ������� �� ���������� 
  if (key == GLUT_KEY_RIGHT)
	  snake->rotRight() ;
  else if (key == GLUT_KEY_LEFT)
    snake->rotLeft() ;
  else if (key == GLUT_KEY_UP)
    snake->rotUp() ;
  else if (key == GLUT_KEY_DOWN)
    snake->rotDown() ;
  glutSetWindow(mainWindow);						// ������ ���� mainWindow �������.
  glutPostRedisplay();								// ���������� ������� ������������ ������� ����.
}

// ��������� ������ ������
void mainKeys(unsigned char key, int xx, int yy)
{
	// ��������� Escape
	switch (key) {
    case 27:
		exit(EXIT_SUCCESS);
		break;
	}
    glutSetWindow(mainWindow);
    glutPostRedisplay();
}

// ����� ����� � main
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
  // ����� ������������� OpenGL, � ������ �����������, ����� �������� 2D � ��������

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );		/*���������� 3 ���������� ����� (RGB)
													����� � ���� ������������ ��� ������ 2 �������, ��� ���� 
													����� ��������� ������ ��������.*/
 
  /*������ ��������� ������������ ���� ������������ �������� ������ ���� ������.*/
  glutInitWindowPosition(100, 100);
  /*��������� ������� ���� � ��������.*/
  glutInitWindowSize(WINDOWW, WINDOWH);

  mainWindow = glutCreateWindow("���� � �������");	/*������� ���� � ����������.*/

  glEnable(GL_TEXTURE_2D);		// ���������� ��������� ��������.
  glEnable(GL_BLEND);			// �������� ����� ����������.

  // ��������� �������
  glutDisplayFunc(display);			/*������� display ����� �������� �� ���������*/
  glutReshapeFunc(changeSize);		/*changeSize �������� �� ��������� �������� ����*/
  glutSpecialFunc(specialKeys);
  glutKeyboardFunc(mainKeys);
  glutMouseFunc(mouseFunc) ;
 
  // ��������� ��� �������.
  sprite_rabbit.width = BLOCKW ;  sprite_rabbit.height = BLOCKW ;
  loadTexture(&sprite_rabbit.texcode,"rabbit.bmp") ;  
  
  sprite_wall.width = BLOCKW ;  sprite_wall.height = BLOCKW ;  
  loadTexture(&sprite_wall.texcode,"wall.bmp") ;
  
  sprite_head.width = BLOCKW ;  sprite_head.height = BLOCKW ;  
  loadTexture(&sprite_head.texcode,"head.bmp") ;
  
  sprite_body.width = BLOCKW ;  sprite_body.height = BLOCKW ;  
  loadTexture(&sprite_body.texcode,"body.bmp") ;

  sprite_score.width = 90 ;  sprite_score.height = 32 ;
  loadTexture(&sprite_score.texcode,"text_score.bmp") ;  

  sprite_food.width = 150 ;  sprite_food.height = 32 ;
  loadTexture(&sprite_food.texcode,"text_food.bmp") ;  

  sprite_time.width = 100 ;  sprite_time.height = 32 ;
  loadTexture(&sprite_time.texcode,"text_time.bmp") ;  

  labwin.width = 200 ;  labwin.height = 32 ;
  loadTexture(&labwin.texcode,"win.bmp") ;  

  labfail.width = 200 ;  labfail.height = 32 ;
  loadTexture(&labfail.texcode,"fail.bmp") ;  

  char str[32] ;
  for (int i=0; i<10; i++) {
	digits[i].width = 16 ;  digits[i].height = 32 ;  
	sprintf(str,"d%d.bmp",i) ;
	loadTexture(&digits[i].texcode,str) ;
  }
  dsep.width = 16 ;  dsep.height = 32 ;  
  loadTexture(&dsep.texcode,"dsep.bmp") ;
  
  butnew.width = 128 ;  butnew.height = 32 ;  
  loadTexture(&butnew.texcode,"newgame.bmp") ;
  
  // ������� ������
  snake = new Snake(tekfile) ;
  msec = MSEC_UPD ;
  // ������ ������ � ������� � ������� ����
  glutTimerFunc(DT, frameFunc, 0);
  glutMainLoop(); /*���� � ������� ���� GLUT. ���� ���� ������������ ����������� ����� ������������ ��������
				  � ���������.*/

  return 0;
}

