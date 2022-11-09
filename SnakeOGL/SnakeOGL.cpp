// SnakeOGL.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

/*Подключение библиотеки GLUT*/
#include "glut.h"
#include "glaux.h"
#include "Engine.h"
#include "Snake.h"

// Подключаем библиотеку для изображений.
#pragma comment (lib, "glaux.lib")

int mainWindow ;
// Спрайты. Спрайт - графический объект в компьютерной графике.
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

// Счет времени.
int msec ;

// Файл карты.
char * tekfile = "map1" ;

// Размер блока.
const int BLOCKW = 38 ;
// Окно. 
const int WINDOWW = 800 ;
const int WINDOWH = 600 ;
// Отступ.
const int LEFT = 10 ;
const int TOP = 10 ;
// Этот параметр отвечает за то, сколько миллисекунд отводится на один шаг.
const int MSEC_UPD = 70 ;
// Через сколько миллисекунд вызывается таймер обновления.
const int DT = 10 ;
// Координаты кнопки.
const int BUTNEWX = 640 ;
const int BUTNEWY = 20 ;

// Функция рендера.
// Рендеринг - получение изображения по модели. 
void display(){
 
  // Чистка буфера
  glClearColor(0,0,0,0);
  glClear(GL_COLOR_BUFFER_BIT);
    
  // Цвет белый
  glColor3f(1.0,1.0,1.0) ;

  // Рендер тела (визуализация) змеи 
  for (int i=0; i<snake->getWidth(); i++)
	  for (int j=0; j<snake->getHeight(); j++) {
		    if (snake->isWallAt(i,j)) renderSprite(sprite_wall,LEFT+i*BLOCKW,TOP+j*BLOCKW) ;    
			if (snake->isBodyAt(i,j)) renderSprite(sprite_body,LEFT+i*BLOCKW,TOP+j*BLOCKW) ;    
			if (snake->isRabbitAt(i,j)) renderSprite(sprite_rabbit,LEFT+i*BLOCKW,TOP+j*BLOCKW) ;    
		}
 
	// Рендер головы змеи.
	Direction tekdir ;
	int hx ;
	int hy ;
	snake->getHead(&hx,&hy,&tekdir) ;
	if (tekdir==dXminus) renderSpriteRotated(sprite_head,LEFT+hx*BLOCKW,TOP+hy*BLOCKW,dLeft) ;
	if (tekdir==dXplus) renderSpriteRotated(sprite_head,LEFT+hx*BLOCKW,TOP+hy*BLOCKW,dRight) ;
	if (tekdir==dYminus) renderSpriteRotated(sprite_head,LEFT+hx*BLOCKW,TOP+hy*BLOCKW,dUp) ;
	if (tekdir==dYplus) renderSpriteRotated(sprite_head,LEFT+hx*BLOCKW,TOP+hy*BLOCKW,dDown) ;
  
	// Кнопка новой игры.
	renderSprite(butnew,BUTNEWX,BUTNEWY) ;    

	// Тексты и счетчики.
	renderSprite(sprite_score,630,110) ;    
	renderDigits(snake->getScore(),digits,636,150) ;

	renderSprite(sprite_food,630,200) ;    
	renderDigits(snake->getRabbitCount(),digits,636,240) ;

	renderSprite(sprite_time,635,290) ;    
	static char timestr[32] ;
	snake->getTimeStr(timestr) ;
	renderTimeStr(timestr,digits,dsep,636,330) ;
	
	// Сообщения о конце игры.
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

  // Переключение буферов.
  glutSwapBuffers();
}

// Таймер
void frameFunc(int value) {	
	// Вычитаем время
	msec-=DT ;
	// Если набралось сколько надо, то обновляем цикл.
	if (msec<=0) {
		snake->nextStep(MSEC_UPD) ;
		msec = MSEC_UPD ;	
		glutSetWindow(mainWindow);
		glutPostRedisplay(); 
	}
	// Ставим таймер заново.
	glutTimerFunc(DT, frameFunc, 100);	
}

// Функция мыши, отработка клика новой игры
void mouseFunc(int button, int state, int x, int y) {
	if ((button == GLUT_LEFT_BUTTON)&&(state == GLUT_UP)) {
		if ((x>=BUTNEWX)&&(x<=BUTNEWX+butnew.width)&&(y>=BUTNEWY)&&(y<=BUTNEWY+butnew.height))
			snake = new Snake(tekfile) ;
		}
}

// Функция обработки размера окна, ставим ортопроекцию, чтобы работало в 2D.
void changeSize(int w, int h) {
	/*Указываем библиотеке OpenGL на то, что вывод будет осуществляться во всей области*/
	glViewport(0,0,WINDOWW,WINDOWH);
	/*Задаем матричный режим: определяем матрицу, над которой будем
	работать в дальнейшем. GL_PROJECTION - матрица проекций.*/
    glMatrixMode(GL_PROJECTION);
	/*Очищаем матрицу (данная функция заменяет текущую матрицу на единичную)*/
    glLoadIdentity();
    glOrtho(0.0f,WINDOWW,WINDOWH,0.0f,-1.0f,1.0f);
	/*В качестве текущей матрицы ставим объектно-видовую матрицу*/
    glMatrixMode(GL_MODELVIEW);
}

// Обработка спецклавиш.
void specialKeys( int key, int x, int y ) {
	// Стрелки на управление 
  if (key == GLUT_KEY_RIGHT)
	  snake->rotRight() ;
  else if (key == GLUT_KEY_LEFT)
    snake->rotLeft() ;
  else if (key == GLUT_KEY_UP)
    snake->rotUp() ;
  else if (key == GLUT_KEY_DOWN)
    snake->rotDown() ;
  glutSetWindow(mainWindow);						// Делаем окно mainWindow текущим.
  glutPostRedisplay();								// Заставляем систему перерисовать текущее окно.
}

// Обработка прочих клавиш
void mainKeys(unsigned char key, int xx, int yy)
{
	// Обработка Escape
	switch (key) {
    case 27:
		exit(EXIT_SUCCESS);
		break;
	}
    glutSetWindow(mainWindow);
    glutPostRedisplay();
}

// Точка входа в main
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
  // Здесь инициализация OpenGL, с такими параметрами, чтобы работало 2D и текстуры

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB );		/*Используем 3 компонента цвета (RGB)
													Вывод в окно осуществляем при помощи 2 буферов, для того 
													чтобы исключить эффект мерцания.*/
 
  /*Задаем положение создаваемого окна относительно верхнего левого угла экрана.*/
  glutInitWindowPosition(100, 100);
  /*Указываем размеры окна в пикселях.*/
  glutInitWindowSize(WINDOWW, WINDOWH);

  mainWindow = glutCreateWindow("Удав и кролики");	/*Создаем окно с заголовком.*/

  glEnable(GL_TEXTURE_2D);		// Разрешение наложения текстуры.
  glEnable(GL_BLEND);			// Включаем режим смешивания.

  // Установка функций
  glutDisplayFunc(display);			/*Функция display будет отвечать за рисование*/
  glutReshapeFunc(changeSize);		/*changeSize отвечает за изменение размеров окна*/
  glutSpecialFunc(specialKeys);
  glutKeyboardFunc(mainKeys);
  glutMouseFunc(mouseFunc) ;
 
  // Загружаем все спрайты.
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
  
  // Создаем змейку
  snake = new Snake(tekfile) ;
  msec = MSEC_UPD ;
  // Ставим таймер и поехали в главный цикл
  glutTimerFunc(DT, frameFunc, 0);
  glutMainLoop(); /*Вход в главный цикл GLUT. Этот цикл обеспечивает взаимосвязь между операционной системой
				  и функциями.*/

  return 0;
}

