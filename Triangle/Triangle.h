
// Triangle.h: PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include <afx.h>


// CTriangleApp:
// 有关此类的实现，请参阅 Triangle.cpp
//

class CTriangleApp : public CWinApp
{
public:
	CTriangleApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
};

extern CTriangleApp theApp;
struct Edge {
	CPoint p1;
	CPoint p2;
	bool operator<(const Edge& e2)const
	{
		if (min(p1.x, p2.x) < min(e2.p1.x, e2.p2.x))
			return true;
		else if (min(p1.x, p2.x) == min(e2.p1.x, e2.p2.x))
			return min(p1.y, p2.y) < min(e2.p1.y, e2.p2.y);
		else
			return false;
	}
	Edge(CPoint pp1, CPoint pp2) { 
		if (pp1.x < pp2.x)
		{
			p1 = pp1;
			p2 = pp2; 
		}
									
		else {
			p1 = pp2;
			p2 = pp1;
		}	
	}
	bool operator == (const Edge& e)
	{
		if (e.p1 == p1 && e.p2 == p2)return true;
		else if (e.p2 == p1 && e.p1 == p2)return true;
		else return false;
	}
};
bool cmp(const Edge& e1, const Edge& e2);
class Triangle :
	public CObject
{
	friend void swap(Triangle& t1, Triangle& t2);

public:
	Triangle();
	Triangle(CPoint pp1, CPoint pp2, CPoint pp3);
	Triangle(CPoint p, Edge e) :Triangle(p, e.p1, e.p2) {}
	Triangle(const Triangle& t);
	Triangle& operator=(const Triangle& t);
	bool CircleContain(const CPoint& p)const;
	bool Contain(const CPoint& p);
	void Draw(CDC* pDC);
	void GetBoundingCircle(CPoint* center, int * radius);
	~Triangle();
public:
	CPoint left;
	CPoint mid;
	CPoint right;
private:
	double circle_centerx;
	double circle_centery;
	double radius2;
};
