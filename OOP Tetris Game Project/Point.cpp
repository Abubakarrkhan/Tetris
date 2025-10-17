#include "Point.h"


Point::Point() :x(0), y(0) {}

Point::Point(float a, float b) :x(a), y(b) {}

void Point::SetPoint(const float& i, const float& j)
{
	////(Tetris window has 400 x800)

	x = j * 40; // j can from 0 to 10 so 0 <= x <= 400
	y = i * 40; // i can from 0 to 20 so 0 <= y <= 800 
}
float Point::getX()
{
	return x;
}
float Point::getY()
{
	return y;
}
void Point::SetX(const float& a)
{
	x = a;
}
void Point::SetY(const float& b)
{
	y = b;
}
void Point::Print()
{
	cout << "(" << x << "," << y << ")" << endl;
}