#pragma once

#include <vector>

using namespace std ;

// ����� �����
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

// ����������� ��������
enum Direction { dXplus,dXminus,dYplus,dYminus } ;

// ����� ������
class Snake {
private:
  // ������� ��������
  Direction dir ;
  // ����� ��� ��������
  bool stopped ;
  // ���� ������
  vector<Point2> body ;
  // �������
  vector<Point2> rabbits ;
  // ����� ����
  bool ** walls ;
  // ������ � ����� �����
  int width ;
  int height ;
  // ����
  int score ;
  // �� ������� ������� ������
  int grow ;
  // ����� ����� ����
  int mtime ;
  // ������ ����� ����
  bool gameover ;  
  // �������� ������ � �����
  bool isCellIn(int x, int y) const ;
  // ���������� ����� �� �����������
  void updateXY(int * x, int * y) const ;
  // �� ��, �� �� ���������� ����������.
  void updateXYCustomDir(Direction cdir, int * x, int * y) const ;
  // �������� ���� �� �����������
  bool isSnakeAt(int x, int y) const ;
  // �������� ������� � ������� 1 ������
  bool isRabbitNear(int x, int y) const ;
  // ������� ���������� ����� �����������
  void trySetDir(Direction ndir) ;
public:
  Snake(const char * mapfile) ;
  ~Snake() ;

  // �������� �� ������� � ���� ������
  bool isBodyAt(int x, int y) const ;
  // �������� ������ ����
  void getHead(int * x, int * y, Direction * tekdir) const ;
  // �������� �� �������
  bool isRabbitAt(int x, int y) const ;
  // �������� �� �����
  bool isWallAt(int x, int y) const ;
  // ����� ��������, �����, ����� ����
  int getRabbitCount() const ;
  int getScore() const ;
  void getTimeStr(char * str) const ;
  // ������ ����� ����
  bool isGameOver() const ;
  // ������ ������
  bool isWin() const ;
  // ��������� ���
  void nextStep(int dtmsec) ;
  // ��������� �����
  int getWidth() const ;
  int getHeight() const ;
  // ����������
  void rotLeft() ;
  void rotRight() ;
  void rotUp() ;
  void rotDown() ;  
} ;
