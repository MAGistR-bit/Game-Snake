#pragma once

#include <vector>

using namespace std ;

// Класс точки
struct Point2 {
  int x ;
  int y ;
  static Point2 newPoint2(int Ax, int Ay) {
    Point2 p2 ;
    p2.x=Ax ;
    p2.y=Ay ;    
    return p2 ;
  }
  bool isEqual(int Ax, int Ay) const {
    return (x==Ax)&&(y==Ay) ;
  }
} ;

// Направления движения
enum Direction { dXplus,dXminus,dYplus,dYminus } ;

// класс змейки
class Snake {
private:
  // Текущее движение
  Direction dir ;
  // Стоим или движемся
  bool stopped ;
  // Тело змейки
  vector<Point2> body ;
  // Кролики
  vector<Point2> rabbits ;
  // Карта стен
  bool ** walls ;
  // Ширина и длина карты
  int width ;
  int height ;
  // Очки
  int score ;
  // На сколько вырасти змейке
  int grow ;
  // Общее время игры
  int mtime ;
  // Маркер конца игры
  bool gameover ;  
  // Проверка ячейки в карте
  bool isCellIn(int x, int y) const ;
  // Обновление точки по направлению
  void updateXY(int * x, int * y) const ;
  // То же, но по указанному направлени.
  void updateXYCustomDir(Direction cdir, int * x, int * y) const ;
  // Проверка змеи по координатам
  bool isSnakeAt(int x, int y) const ;
  // Проверка кролика в радиусе 1 клетки
  bool isRabbitNear(int x, int y) const ;
  // Попытка установить новое направление
  void trySetDir(Direction ndir) ;
public:
  Snake(const char * mapfile) ;
  ~Snake() ;

  // Проверка на кролика и тело змейки
  bool isBodyAt(int x, int y) const ;
  // Получить голову змеи
  void getHead(int * x, int * y, Direction * tekdir) const ;
  // Проверка на кролика
  bool isRabbitAt(int x, int y) const ;
  // Проверка на стену
  bool isWallAt(int x, int y) const ;
  // Число кроликов, очков, время игры
  int getRabbitCount() const ;
  int getScore() const ;
  void getTimeStr(char * str) const ;
  // Маркер конца игры
  bool isGameOver() const ;
  // Маркер победы
  bool isWin() const ;
  // Следующий ход
  void nextStep(int dtmsec) ;
  // Параметры карты
  int getWidth() const ;
  int getHeight() const ;
  // Управление
  void rotLeft() ;
  void rotRight() ;
  void rotUp() ;
  void rotDown() ;  
} ;
