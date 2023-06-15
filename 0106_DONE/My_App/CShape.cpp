#include "CShape.h"
///////////////////////////////////////////////////////////////////
Point newPoint(int x, int y)
{
	Point p(x, y);
	return p;
}

///////////////////////////////////////////////////////////////////
COLORREF CShape::getColor()
{
	return this->color;
}

int CShape::getCount()
{
	return 0;
}

void CShape::setType(ShapeMode type)
{
	this->type = type;
}

void CShape::setPenSize(int n)
{
	this->penSize = n;
}
//RECT* CShape::getDimens()
//{
//	RECT* rect = new RECT();
//	rect->left = x1;
//	rect->top = y1;
//	rect->right = x2;
//	rect->bottom = y2;
//
//	return rect;
//}

//void CShape::setDimens(RECT* rect)
//{
//	this->x1 = rect->left;
//	this->x2 = rect->right;
//	this->y1 = rect->top;
//	this->y2 = rect->bottom;
//}

void CShape::setColor(COLORREF color)
{
	this->color = color;
}

int CShape::getPenStyle()
{
	return this->penStyle;
}


//////////////////////////////////////////////////////////////////////////
void CLine::SetData(int a, int b, int c, int d, COLORREF color, int penStyle, int penSize)
{
	int x1 = a;
	int y1 = b;
	int x2 = c;
	int y2 = d;

	A.setData(x1, y1);
	B.setData(x2, y2);

	this->type = LINE;
	this->color = color;
	this->penStyle = penStyle;
	this->penSize = penSize;
}

void CLine::Draw(HDC hdc,HPEN hpen,HBRUSH hbr)
{
	
	if (this->getFlag() == 1)
	{
		hpen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
	}
	SelectObject(hdc, hpen);
	MoveToEx(hdc, A.getX(), A.getY(), NULL);
	LineTo(hdc, B.getX(), B.getY());
}

CShape* CLine::Create()
{
	return new CLine;
}

ShapeMode CLine::getType()
{
	return this->type;
}


//////////////////////////////////////////////////////////////////////////
CShape* CRectangle::Create()
{
	return new CRectangle;
}

void CRectangle::SetData(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, COLORREF color, int penStyle, int penSize)
{
	int x1 = nLeftRect;
	int y1 = nTopRect;
	int x2 = nRightRect;
	int y2 = nBottomRect;
	A.setData(x1, y1);
	B.setData(x2, y2);

	this->type = DRAWRECT;
	this->color = color;
	this->penStyle = penStyle;
	this->penSize = penSize;
}

void CRectangle::Draw(HDC hdc,HPEN hpen,HBRUSH hbr)
{
	int x1 = A.getX();
	int x2 = B.getX();
	int y1 = A.getY();
	int y2 = B.getY();
	if (x1 < x2)
	{
		int tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 < y2)
	{
		int tmp = y1;
		y1 = y2;
		y2 = tmp;
	}

	
	if (this->getFlag() == 1)
	{
		hpen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		hbr = CreateSolidBrush(RGB(0, 255, 0));
	}
	SelectObject(hdc, hpen);
	SelectObject(hdc, hbr);
	Rectangle(hdc, x1, y1, x2, y2);
}

ShapeMode CRectangle::getType()
{
	return this->type;
}

////////////////////////////////////////////////////////////////////////////////
void CSquare::SetData(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, COLORREF color, int penStyle, int penSize)
{
	{
		int x1 = nLeftRect;
		int y1 = nTopRect;
		int y2 = nBottomRect;
		int x2 = x1 + (y2 - y1);
		A.setData(x1, y1);
		B.setData(x2, y2);

		this->type = DRAWSQUARE;
		this->color = color;
		this->penStyle = penStyle;
		this->penSize = penSize;
	}
}


///////////////////////////////////////////////////////////////////////////////////
CShape* CEllipse::Create()
{
	return new CEllipse;
}

void CEllipse::SetData(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, COLORREF color, int penStyle, int penSize)
{
	int x1 = nLeftRect;
	int y1 = nTopRect;
	int x2 = nRightRect;
	int y2 = nBottomRect;
	A.setData(x1, y1);
	B.setData(x2, y2);

	this->type = DRAWELLIPSE;
	this->color = color;
	this->penStyle = penStyle;
	this->penSize = penSize;
}

void CEllipse::Draw(HDC hdc,HPEN hpen,HBRUSH hbr)
{
	int x1 = A.getX();
	int x2 = B.getX();
	int y1 = A.getY();
	int y2 = B.getY();
	/*if (x1 < x2)
	{
		int tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	if (y1 < y2)
	{
		int tmp = y1;
		y1 = y2;
		y2 = tmp;
	}*/
	if (this->getFlag() == 1)
	{
		hpen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		hbr = CreateSolidBrush(RGB(0, 255, 0));
	}
	SelectObject(hdc, hpen);
	SelectObject(hdc, hbr);
	Ellipse(hdc, x1, y1, x2, y2);
}

ShapeMode CEllipse::getType()
{
	return this->type;
}


////////////////////////////////////////////////////////////////////
void CCircle::SetData(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, COLORREF color, int penStyle, int penSize)
{
	{
		int x1 = nLeftRect;
		int y1 = nTopRect;
		int y2 = nBottomRect;
		int x2 = x1 + (y2 - y1);
		A.setData(x1, y1);
		B.setData(x2, y2);
		this->type = DRAWCIRCLE;
		this->color = color;
		this->penStyle = penStyle;
		this->penSize = penSize;
	}
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
CShape* CSemicircle::Create()
{
	return new CSemicircle;
}

void CSemicircle::SetData(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, COLORREF color, int penStyle, int penSize)
{
	int x1 = nLeftRect;
	int y1 = nTopRect;
	int x2 = nRightRect;
	int y2 = nBottomRect;
	A.setData(x1, y1);
	B.setData(x2, y2);

	this->type = DRAWSEMICIRCLE;
	this->color = color;
	this->penStyle = penStyle;
	this->penSize = penSize;
}

void CSemicircle::Draw(HDC hdc,HPEN hpen,HBRUSH hbr)
{
	int x1 = A.getX();
	int x2 = B.getX();
	int y1 = A.getY();
	int y2 = B.getY();
	int yMean = (y1 + y2) / 2;
	BeginPath(hdc);
	if (y1 < y2)
	{
		Arc(hdc, x1, y1, x2, y2, x2, yMean, x1, yMean);
	}
	else
	{
		Arc(hdc, x2, y2, x1, y1, x2, yMean, x1, yMean);
	}
	MoveToEx(hdc, x1, yMean, NULL);
	LineTo(hdc, x2, yMean);
	EndPath(hdc);
	if (this->getFlag() == 1)
	{
		hpen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		hbr = CreateSolidBrush(RGB(0, 255, 0));
	}
	SelectObject(hdc, hpen);
	SelectObject(hdc, hbr);
	StrokeAndFillPath(hdc);

}

ShapeMode CSemicircle::getType()
{
	return this->type;
}


//////////////////////////////////////////////////////////////////
CShape* CTriangle::Create()
{
	return new CTriangle;
}

void CTriangle::SetData(int nLeftRect, int nTopRect, int nRightRect, int nBottomRect, COLORREF color, int penStyle, int penSize)
{
	int x1 = nLeftRect;
	int y1 = nTopRect;
	int x2 = nRightRect;
	int y2 = nBottomRect;
	A.setData(x1, y1);
	B.setData(x2, y2);

	this->type = DRAWTRIANGLE;
	this->color = color;
	this->penStyle = penStyle;
	this->penSize = penSize;
}

void CTriangle::Draw(HDC hdc,HPEN hpen,HBRUSH hbr)
{
	int x1 = A.getX();
	int x2 = B.getX();
	int y1 = A.getY();
	int y2 = B.getY();
	int xMean = (x1 + x2) / 2;
	int yMean = y1;
	//BeginPath(hdc);
	//MoveToEx(hdc, x1, y2, NULL);
	//LineTo(hdc, xMean, yMean);
	//LineTo(hdc, x2, y2);
	//LineTo(hdc, x1, y2);
	//EndPath(hdc);
	//hpen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
	//hbr = CreateSolidBrush(RGB(0, 255, 0));
	//SelectObject(hdc, hpen);
	//SelectObject(hdc, hbr);
	////StrokePath(hdc);
	//StrokeAndFillPath(hdc);

	BeginPath(hdc);
	MoveToEx(hdc, x1, y2, NULL);
	LineTo(hdc, xMean, yMean);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x1, y2);
	EndPath(hdc);
	if (this->getFlag() == 1)
	{
		hpen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		hbr = CreateSolidBrush(RGB(0, 255, 0));
	}
	SelectObject(hdc, hpen);
	SelectObject(hdc, hbr);
	StrokeAndFillPath(hdc);
}

ShapeMode CTriangle::getType()
{
	return this->type;
}


///////////////////////////////////////////////////////////////////
void CPolygon::Draw(HDC hdc,HPEN hpen,HBRUSH hbr)
{
	/*MoveToEx(hdc, ptr[0].x, ptr[0].y, NULL);
	Polyline(hdc, ptr, 20);*/
	//BeginPath(hdc);
	//MoveToEx(hdc, ptr[0].x, ptr[0].y, NULL);
	//LineTo(hdc, ptr[1].x, ptr[1].y);
	//for (int i = 2; i < 20; i++)
	//{
	//	LineTo(hdc, ptr[i].x, ptr[i].y);
	//}
	//EndPath(hdc);
	//hpen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
	//hbr = CreateSolidBrush(RGB(0, 255, 0));
	//SelectObject(hdc, hpen);
	//SelectObject(hdc, hbr);
	////StrokePath(hdc);
	//StrokeAndFillPath(hdc);

	BeginPath(hdc);
	MoveToEx(hdc, ptr[0].x, ptr[0].y, NULL);
	LineTo(hdc, ptr[1].x, ptr[1].y);
	for (int i = 2; i < 20; i++)
	{
		LineTo(hdc, ptr[i].x, ptr[i].y);
	}
	EndPath(hdc);
	if (this->getFlag() == 1)
	{
		hpen = CreatePen(PS_SOLID, 4, RGB(255, 0, 0));
		hbr = CreateSolidBrush(RGB(0, 255, 0));
	}
	SelectObject(hdc, hpen);
	SelectObject(hdc, hbr);
	StrokeAndFillPath(hdc);


}

CShape* CPolygon::Create()
{
	return new CPolygon;
}

void CPolygon::SetData(POINT ptr[20], int n, COLORREF color, int penStyle, int penSize)
{

	for (int i = 0; i < 20; i++)
	{
		this->ptr[i] = ptr[i];
	}
	this->n = n;
	this->type = DRAWPOLYGON;
	this->color = color;
	this->penStyle = penStyle;
	this->penSize = penSize;
}

ShapeMode CPolygon::getType()
{
	return this->type;
}

void CPolygon::getPtr(POINT ptr[20])
{
	for (int i = 0; i < n; i++)
	{
		ptr[i] = this->ptr[i];
	}
}

int CPolygon::getCount()
{
	return this->n;
}


///////////////////////////////////////////////////////////////////////////////
bool checkEllipse(Point A,Point B,Point X, Point Y)
{
	// line ax+by+c=0
	float x1 = A.getX();
	float x2 = B.getX();
	float y1 = A.getY();
	float y2 = B.getY();
	float x3 = X.getX();
	float x4 = Y.getX();
	float y3 = X.getY();
	float y4 = Y.getY();

	float xMean = (x3 + x4) / 2;
	float yMean = (y3 + y4) / 2;

	x1 -= xMean;
	y1 -= yMean;
	x2 -= xMean;
	y2 -= yMean;
	x3 -= xMean;
	y3 -= yMean;
	x4 -= xMean;
	y4 -= yMean;
	//Point X(x1-xMean, y1-yMean), Y(x2 - xMean, y2 - yMean), A(x3 - xMean, y3 - yMean), B(x4 - xMean, y4 - yMean);

	float a = y1 - y2;
	float b = x2 - x1;
	float c = -a * x1 - b * y1;

	// check elip
	float a_elip = abs((x4 - x3) / 2);
	float b_elip = abs((y4 - y3) / 2);
	float delta = pow(((a * c * 1.0 / pow(b, 2)) / pow(b_elip, 2)), 2) - (1 / pow(a_elip, 2) +
		(pow(a, 2) / pow(b, 2)) / pow(b_elip, 2)) * ((pow(c, 2) / pow(b, 2)) / pow(b_elip, 2) - 1);
	if (delta >= 0)
	{
		return true;
	}
	else
		return false;
}


// chackRect Bản 1 - 

//bool checkRect(Point A, Point B, Point X, Point Y)
//{
//	// line ax+by+c=0 
//	//
//	double a = X.getY()*1.0 - Y.getY() * 1.0;
//	double b = Y.getX() * 1.0 - X.getX() * 1.0;
//	double c = -a * X.getX() - b * X.getY();
//
//	
//	double x1 = A.getX();
//	double y1 = A.getY();
//	double x2 = B.getX();
//	double y2 = B.getY();
//
//	if (a != 0 && b != 0 && c != 0)
//	{
//		if ((-c - b * y1) / a >= x1 && (-c - b * y1) / a <= x2)
//			return 1;
//		if ((-c - b * y2) / a >= x1 && (-c - b * y2) / a <= x2)
//			return 1;
//		if ((-c - a * x1) / b >= y2 && (-c - a * x1) / b <= y1)
//			return 1;
//		if ((-c - a * x2) / b >= y2 && (-c - a * x2) / b <= y1)
//			return 1;
//	}
//	if (a == 0)
//	{
//		if (-c / b >= y2 && -c / b <= y1)
//			return 1;
//	}
//	if (b == 0)
//	{
//		if (-c / a >= x1 && -c / a <= x2)
//			return 1;
//	}
//	if (x1 < x2)
//	{
//		int tmp = x1;
//		x1 = x2;
//		x2 = tmp;
//	}
//	if (y1 < y2)
//	{
//		int tmp = y1;
//		y1 = y2;
//		y2 = tmp;
//	}
//	if (a != 0 && b != 0 && c != 0)
//	{
//		if ((-c - b * y1) / a >= x1 && (-c - b * y1) / a <= x2)
//			return 1;
//		if ((-c - b * y2) / a >= x1 && (-c - b * y2) / a <= x2)
//			return 1;
//		if ((-c - a * x1) / b >= y2 && (-c - a * x1) / b <= y1)
//			return 1;
//		if ((-c - a * x2) / b >= y2 && (-c - a * x2) / b <= y1)
//			return 1;
//	}
//	if (a == 0)
//	{
//		if (-c / b >= y2 && -c / b <= y1)
//			return 1;
//	}
//	if (b == 0)
//	{
//		if (-c / a >= x1 && -c / a <= x2)
//			return 1;
//	}
//	return 0;
//
//}


///////////////////////////////////////////////////////////////////
bool checkGiao(Point A, Point B, Point X, Point Y)
{
	// A,B 2 điểm tạo thành đoạn thẳng cần kiểm tra
	// X,Y 2 điểm tạo thành đường thẳng cần kiểm tra
	double a1 = A.getY() * 1.0 - B.getY() * 1.0;
	double b1 = B.getX() * 1.0 - A.getX() * 1.0;
	double c1 = -a1 * A.getX() - b1 * A.getY();

	////
	double a2 = X.getY() * 1.0 - Y.getY() * 1.0;
	double b2 = Y.getX() * 1.0 - X.getX() * 1.0;
	double c2 = -a2 * X.getX() - b2 * X.getY();

	double denta1 = a1 * b2 - a2 * b1;
	double denta2 = b1 * c2 - b2 * c1;
	double denta3 = c1 * a2 - c2 * a1;
	//GIao điểm I(x,y)
	double x = 0;
	double y = 0;
	if ((denta1==0&&denta2!=0)||(denta1==0&&denta3!=0))
	{
		return 0;
	}
	else
	{
		x = (b2 * c1 - c2 * b1) / (a2 * b1 - a1 * b2);
		y = (-c1 - a1 * x) / b1;
		if (b2 == 0)
		{
			x = (b2 * c1 - c2 * b1) / (a2 * b1 - a1 * b2);
			y = (-c1 - a1 * x) / b1;
		}
		if (b1 == 0)
		{
			x = (b1 * c2 - c1 * b2) / (a1 * b2 - a2 * b1);
			y = (-c2 - a2 * x) / b2;
		}
		/*x = (b2 - b1) / (a1 - a2);
		y = a1 * x + b1;*/
	}


	// Kiểm tra xem giao điểm I có thuộc đoạn thẳng AB không?
	if (A.getX() < B.getX())
	{
		if (A.getX() < x && B.getX() > x)
			return 1;
	}
	else
	{
		if (A.getX() > x && B.getX() < x)
			return 1;
	}
	if (A.getY() < B.getY())
	{
		if (A.getY() < y && B.getY() > y)
			return 1;
	}
	else
	{
		if (A.getY() > y && B.getY() < y)
			return 1;
	}
	return 0;
}

bool checkGiao1(POINT A, POINT B, Point X, Point Y)
{
	//
	double a1 = A.y * 1.0 - B.y * 1.0;
	double b1 = B.x * 1.0 - A.x * 1.0;
	double c1 = -a1 * A.x - b1 * A.y;


	////
	double a2 = X.getY() * 1.0 - Y.getY() * 1.0;
	double b2 = Y.getX() * 1.0 - X.getX() * 1.0;
	double c2 = -a2 * X.getX() - b2 * X.getY();


	double denta1 = a1 * b2 - a2 * b1;
	double denta2 = b1 * c2 - b2 * c1;
	double denta3 = c1 * a2 - c2 * a1;
	double x = 0;
	double y = 0;
	if ((denta1 == 0 && denta2 != 0) || (denta1 == 0 && denta3 != 0))
	{
		return 0;
	}
	else
	{
		x = (b2 * c1 - c2 * b1) / (a2 * b1 - a1 * b2);
		y = (-c1 - a1 * x) / b1;
		if (b2 == 0)
		{
			x = (b2 * c1 - c2 * b1) / (a2 * b1 - a1 * b2);
			y = (-c1 - a1 * x) / b1;
		}
		if (b1 == 0)
		{
			x = (b1 * c2 - c1 * b2) / (a1 * b2 - a2 * b1);
			y = (-c2 - a2 * x) / b2;
		}
	}

	if (A.x < B.x)
	{
		if (A.x < x && B.x > x)
			return 1;
	}
	else
	{
		if (A.x > x && B.x < x)
			return 1;
	}
	if (A.y < B.y)
	{
		if (A.y < y && B.y > y)
			return 1;
	}
	else
	{
		if (A.y > y && B.y < y)
			return 1;
	}
	return 0;
}

bool checkRect(Point A, Point B, Point X, Point Y)
{
	//A,B SHAPES
	//X,Y LINE
	//	double x1 = A.getX();
	
	Point C(B.getX(), A.getY()), D(A.getX(), B.getY());
	return checkGiao(A, C, X, Y) || checkGiao(C, B, X, Y) || checkGiao(B, D, X, Y) || checkGiao(D, A, X, Y);
}

bool checkMulti(POINT arr[20], int n, Point X, Point Y)
{
	for (int i = 0; i < n-1; i++)
	{
		if (checkGiao1(arr[i], arr[i + 1], X, Y) == 1) return 1;
	}
	return 0;
}

bool checkSemicircle(Point A, Point B, Point X, Point Y)
{
	float yMean = (A.getY() + B.getY()) / 2;
	Point C(A.getX(), yMean), D(B.getX(), yMean);
	if (checkGiao(C, D, X, Y))
		return 1;

	double x_1 = A.getX();
	double y_1 = A.getY();
	double x_2 = B.getX();
	double y_2 = B.getY();

	double a = X.getY() * 1.0 - Y.getY() * 1.0;
	double b = Y.getX() * 1.0 - X.getX() * 1.0;
	double c = -a * X.getX() - b * X.getY();

	double x0 = (x_1 * 1.0 + x_2 * 1.0) / 2;
	double y0 = (y_1 * 1.0 + B.getY() * 1.0) / 2;

	double a_elip = (x_2 * 1.0 - x_1 * 1.0) / 2;
	double b_elip = (y_2 * 1.0 - y_1 * 1.0) / 2;

	double d = a_elip;
	double e = b_elip;

	double A_ = e * e + d * d * a * a / (b * b);
	double B_ = -2 * x0 * e * e + d * d * 2 * a * c / (b * b) + 2 * y0 * d * d * a / b;
	double C_ = d * d * c * c / (b * b) + 2 * y0 * d * d * c / b + e * e * x0 * x0 + y0 * y0 * d * d - d * d * e * e;

	double delta = B_ * B_ - 4 * A_ * C_;
	if (delta < 0)
		return 0;
	double x1 = (-B_ + sqrt(delta)) / (2 * A_);
	double x2 = (-B_ - sqrt(delta)) / (2 * A_);
	double y1 = (-c - a * x1) / b;
	double y2 = (-c - a * x2) / b;

	//A-C Done
	if ((x_1 < x_2 && y_1 < y_2))
	{
		if (x1 >= x_1 && x1 <= x_2 && y1 >= y_1 && y1 <= y_2 * 1.0 - b_elip)
			return 1;
		if (x2 >= x_1 && x2 <= x_2 && y2 >= y_1 && y2 <= y_2 * 1.0 - b_elip)
			return 1;
	}
	//C-A 
	if ((x_1 > x_2 && y_1 > y_2))
	{
		if (x1 >= x_2 && x1 <= x_1 && y1 >= y_1 - (y_1 - y_2) / 2 && y1 <= y_1)
			return 1;
		if (x2 >= x_2 && x2 <= x_1 && y2 >= y_1 - (y_1 - y_2) / 2 && y2 <= y_1)
			return 1;
	}
	//B-D Done
	if ((x_1 > x_2 && y_1 < y_2))
	{
		int tmp = x_1;
		x_1 = x_2;
		x_2 = tmp;
		if (x1 >= x_1 && x1 <= x_2 && y1 >= y_1 + b_elip && y1 <= y_2 * 1.0 )
			return 1;
		if (x2 >= x_1 && x2 <= x_2 && y2 >= y_1 + b_elip && y2 <= y_2 * 1.0 )
			return 1;
	}

	//D-B Done
	if ((x_2 > x_1 && y_2 < y_1))
	{
		//int tmp = y_1;
		//y_1 = y_2;
		//y_2 = tmp;

		if (x1 >= x_1 && x1 <= x_2 && y1 >= y_2 && y1 <= y_2 + (y_1 - y_2) / 2)
			return 1;
		if (x2 >= x_1 && x2 <= x_2 && y2 >= y_2 && y2 <= y_2 + (y_1 - y_2) / 2)
			return 1;
	}

	//
	
	return 0;
}

bool checkTriangle(Point A, Point B, Point X, Point Y)
{
	Point C(A.getX(), B.getY()), D((A.getX() + B.getX()) / 2, A.getY());
	return checkGiao(C, D, X, Y) || checkGiao(D, B, X, Y) || checkGiao(B, C, X, Y);
}

