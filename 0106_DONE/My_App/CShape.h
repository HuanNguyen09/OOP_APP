#pragma once
#include <vector>
#include"framework.h"
enum ShapeMode   //Chế độ vẽ
{
	LINE,
	DRAWRECT,
	DRAWELLIPSE,
	DRAWCIRCLE,
	DRAWSEMICIRCLE,
	DRAWTRIANGLE,
	DRAWSQUARE,  
	DRAWPOLYGON,
	FILLRECT,
	FILLELLIPSE,
	MODE_WAITING
};


class Point
{
	int x;
	int y;
public:
	Point(int _x = 0, int _y = 0) : x(_x), y(_y) {};
	void setData(int _x, int _y) { x = _x; y = _y; };
	int getX() { return x; };
	int getY() { return y; };

};

 Point newPoint(int x, int y);

class CShape
{
protected:
	Point A;
	Point B;
	COLORREF color;
	ShapeMode type;
	int penStyle;
	int penSize;
	int flag ;
public:
	
	 virtual void Draw(HDC hdc,HPEN hpen,HBRUSH hbr) = 0;
	 virtual CShape* Create() = 0;
	 virtual void SetData(int a, int b, int c, int d, COLORREF color, int penStyle, int penSize) {};
	 virtual ShapeMode getType() = 0;
	 virtual Point getPointA() { return A; }
	 virtual Point getPointB() { return B; }
	 virtual int getPenSize() { return penSize; }
	 virtual void getPtr(POINT ptr[20]) {  }
	 virtual int getCount() ;
	 void setType(ShapeMode type);
	 COLORREF getColor();
	 //RECT* getDimens();
	 //void setDimens(RECT* rect);
	 void setColor(COLORREF color);
	 int getPenStyle();
	 void setPenSize(int n);
	 int getFlag() { return flag; };
	 void setFlag(int n) { flag = n; }
};

class CLine : public CShape {
private:
public:
	 void Draw(HDC hdc,HPEN hpen,HBRUSH hbr);
	 CShape* Create();
	 void SetData(int a, int b, int c, int d, COLORREF color, int penStyle, int penSize);
	 ShapeMode getType();
};

class CEllipse : public CShape {
private:
public:
	 void Draw(HDC hdc,HPEN hpen,HBRUSH hbr);
	 CShape* Create();
	 void SetData(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, COLORREF color, int penStyle, int penSize);
	 ShapeMode getType();
};


class CCircle : public CEllipse {
private:
public:
	void SetData(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, COLORREF color, int penStyle, int penSize);
};

class CRectangle : public CShape {
private:
public:
	 void Draw(HDC hdc,HPEN hpen,HBRUSH hbr);
	 CShape* Create();
	 void SetData(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, COLORREF color, int penStyle, int penSize);
	 ShapeMode getType();
};


class CSquare : public CRectangle {
private:
public:
	void SetData(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, COLORREF color, int penStyle, int penSize);
	
};

class CSemicircle : public CShape {
private:
public:
	void Draw(HDC hdc,HPEN hpen,HBRUSH hbr);
	CShape* Create();
	void SetData(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, COLORREF color, int penStyle, int penSize);
	ShapeMode getType();
};

class CTriangle : public CShape {
private:
public:
	void Draw(HDC hdc,HPEN hpen,HBRUSH hbr);
	CShape* Create();
	void SetData(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, COLORREF color, int penStyle,  int penSize);
	ShapeMode getType();
};

class CPolygon : public CShape
{
protected:
	POINT ptr[20];
	int n;
public:
	void Draw(HDC hdc,HPEN hpen,HBRUSH hbr);
	CShape* Create();
	void SetData(POINT ptr[20],int n, COLORREF color, int penStyle, int penSize);
	ShapeMode getType();
	void getPtr(POINT ptr[20]);
	int getCount();
};

//////////////////////////////////////////////////////////
bool checkRect(Point PointX_SHAPE, Point PointY_SHAPE, Point PointA_LINE, Point PointB_LINE);

bool checkEllipse(Point PointA_LINE, Point PointB_LINE, Point PointX_SHAPE, Point PointY_SHAPE);

bool checkSemicircle(Point PointX_SHAPE, Point PointY_SHAPE, Point PointA_LINE, Point PointB_LINE);

bool checkGiao(Point A, Point B, Point X, Point Y);

bool checkGiao1(POINT A, POINT B, Point X, Point Y);

bool checkMulti(POINT arr[20], int n, Point X, Point Y);

bool checkTriangle(Point PointX_SHAPE, Point PointY_SHAPE, Point PointA_LINE, Point PointB_LINE);
