#pragma once
#include<iostream>
using namespace std;
class Point
{
private:
	float x;
    float y;
public:
	Point();// default Constructor
	Point(float a, float b);//Parametrized Constructor
	void SetPoint(const float& i, const float& j);

	// getter and setter Functions
	float getX();
	float getY();
	void SetX(const float& a);
	void SetY(const float& b);

	void Print();//debug function
};
