#include "stdafx.h"
#include "Snake.h"

#include <time.h>

// Обрезка переноса строки
void strip(char * str) {
        while ((str[strlen(str)-1]==13)||(str[strlen(str)-1]==10))
            str[strlen(str)-1]=0 ;
}

bool Snake::isCellIn(int x, int y) const {
	return (x>=0)&&(x<width)&&(y>=0)&&(y<height) ;
}

bool Snake::isSnakeAt(int x, int y) const {
	for (unsigned int i=0; i<body.size(); i++)
		if (body [i].isEqual(x,y)) return true ;
	return false ;
}

bool Snake::isRabbitNear(int x, int y) const {
	for (int dx=-1; dx<=1; dx++)
		for (int dy=-1; dy<=1; dy++) {
			for (int i=0; i<rabbits.size(); i++)
				if (rabbits[i].isEqual(x+dx,y+dy)) return true ;
		}
	return false ;
}

void Snake::updateXY(int * x, int * y) const {
	if (dir==dXplus) (*x)+=1 ;
	if (dir==dXminus) (*x)-=1 ;
	if (dir==dYplus) (*y)+=1 ;
	if (dir==dYminus) (*y)-=1 ;				
}

void Snake::updateXYCustomDir(Direction cdir, int * x, int * y) const {
	if (cdir==dXplus) (*x)+=1 ;
	if (cdir==dXminus) (*x)-=1 ;
	if (cdir==dYplus) (*y)+=1 ;
	if (cdir==dYminus) (*y)-=1 ;				
}

Snake::Snake(const char * mapfile) {  
  
  // Читаем карту
  char line[256] ;
  FILE * f = fopen(mapfile,"r") ;
  fgets(line,255,f) ; strip(line) ; width = atoi(line) ;
  fgets(line,255,f) ; strip(line) ; height = atoi(line) ;
  walls = new bool*[width] ;
  for (int i=0; i<width; i++)
	  walls[i]=new bool[height] ;
  for (int j=0; j<height; j++) {
	  fgets(line,255,f) ;
	  for (int i=0; i<width; i++)
		  walls[i][j]=line[i]=='#' ;
  }
  fgets(line,255,f) ; strip(line) ; int rabcount = atoi(line) ;
  fclose(f) ;

  srand(time(NULL)) ;

  // Заливаем змейку в произвольное место
  bool completed = false ;
  while (!completed) {
	  int x = rand()%width ;
	  int y = rand()%height ;
	  if (walls[x][y]) continue ;
	  	  
	  for (dir = dXplus ; dir<=dYminus; dir=Direction(dir+1)) {
		  int nx = x ;
		  int ny = y ;
		  int cnt = 0 ;
		  for (int i=0; i<2; i++) {
			  updateXY(&nx,&ny) ;
			  if (isCellIn(nx,ny))
					if (!walls[nx][ny]) cnt++ ;
		  }
		  if (cnt==2) {
			  completed = true ;
			  body.push_back(Point2::newPoint2(x,y)) ;
			  int nx = x ;
			  int ny = y ;		  
			  for (int i=0; i<2; i++) {
				updateXY(&nx,&ny) ;
				body.push_back(Point2::newPoint2(nx,ny)) ;
			  }
			  break ;
		  }  	  
	  }	  	  
  }
  
  // Ставим кроликов
  for (int i=0; i<rabcount; i++) {
	  while (true) {
		  int x = rand() % width ;
		  int y = rand() % height ;
		  if ((!isRabbitNear(x,y))&&(!isWallAt(x,y))&&(!isSnakeAt(x,y))) {
			rabbits.push_back(Point2::newPoint2(x,y)) ;
			break ;
		  }
	  }
  }  

  grow=0 ;
  score=0 ;
  mtime=0 ;
  gameover=false ;
  stopped = true ;
}

Snake::~Snake() {
	for (int i=0; i<width; i++)
		delete[] walls[i] ;
	delete[] walls ;
}

int Snake::getWidth() const {
	return width ;
}

int Snake::getHeight() const {
	return height ;
}
 
bool Snake::isWin() const {
	return rabbits.size()==0 ;
}

bool Snake::isBodyAt(int x, int y) const {
  for (unsigned int i=0; i<body.size()-1; i++)
    if (body [i].isEqual(x,y)) return true ;
  return false ;
}

void Snake::getHead(int * x, int * y, Direction * tekdir) const {
  *x = body[body.size()-1].x ;
  *y = body[body.size()-1].y ;
  *tekdir = dir ;
}

bool Snake::isRabbitAt(int x, int y) const {
  for (unsigned int i=0; i<rabbits.size(); i++)
    if (rabbits[i].isEqual(x,y)) return true ;
  return false ;
}

bool Snake::isWallAt(int x, int y) const {
	return walls[x][y] ;
}

void Snake::nextStep(int dtmsec) {
  if (gameover) return  ;

  mtime+=dtmsec ;
    
  if (stopped) return ;

  // Обновляем голову змеи
  Point2 head = body[body.size()-1] ;
  updateXY(&head.x,&head.y) ;
    
  // Проверка конца игры
  if (isBodyAt(head.x,head.y)) gameover=true ;
  if (gameover) return ;

  if (isWallAt(head.x,head.y)) stopped=true ;
  if (stopped) return ;

  // Ползем вперед
  body.push_back(head) ;
  
  // Если не надо расти, то убираем хвост, иначе растем
  if (grow==0)
    body.erase(body.begin()) ;
  else
    grow-- ;
  
  // Если съели кролика, то растем
  for (unsigned int i=0; i<rabbits.size(); i++)
    if (rabbits[i].isEqual(head.x,head.y)) {
      grow=3 ;
	  score+=10 ;
      rabbits.erase(rabbits.begin()+i) ;
	  // Победили, если съели всех кроликов
	  if (rabbits.size()==0) gameover=true ;
      break ;
    }
}

void Snake::trySetDir(Direction ndir) {
	Point2 head = body[body.size()-1] ;
	updateXYCustomDir(ndir,&head.x,&head.y) ;
	// Можно двигаться только туда, где нет стены и соседней с головы ячейки тела
	if ((!body[body.size()-2].isEqual(head.x,head.y))&&(!isWallAt(head.x,head.y))) {
		stopped=false ;
		dir=ndir;
	}
}

void Snake::rotLeft() {	
  if (dir!=dXplus) trySetDir(dXminus) ;
}

void Snake::rotRight() {
  if (dir!=dXminus) trySetDir(dXplus) ;
}

void Snake::rotDown() {	
  if (dir!=dYminus) trySetDir(dYplus);
}

void Snake::rotUp() {	
  if (dir!=dYplus) trySetDir(dYminus);
}

bool Snake::isGameOver() const {
  return gameover ;
}

int Snake::getRabbitCount() const {
	return rabbits.size() ;
}

int Snake::getScore() const {
	return score ;
}

void Snake::getTimeStr(char * str) const {
	sprintf(str,"%.2d:%.2d",(mtime/1000) / 60,(mtime/1000) % 60) ;
}