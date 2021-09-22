/* **********************************************
Author      : kuangbin
Created Time: 2013/8/13 14:13:06
File Name   : F:\2013ACM��ϰ\2013��У7\1002.cpp
*********************************************** */

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <math.h>
#include <stdlib.h>
using namespace std;

const double eps = 1e-8;
const double PI = acos(-1.0);
int sgn(double x)
{
	if(fabs(x) < eps)return 0;
	if(x < 0)return -1;
	else return 1;
}
struct Point
{
	double x,y;
	int index;
	Point(){}
	Point(double _x,double _y,int _index)
	{
		x = _x;y = _y;index = _index;
	}
	Point(double _x,double _y)
	{
		x = _x;y = _y;
	}
	Point operator -(const Point &b)const
	{
		return Point(x - b.x,y - b.y);
	}
	//���
	double operator ^(const Point &b)const
	{
		return x*b.y - y*b.x;
	}
	//���
	double operator *(const Point &b)const
	{
		return x*b.x + y*b.y;
	}
	//��ԭ����ת�Ƕ�B������ֵ������x,y�ı仯
	void transXY(double B)
	{
		double tx = x,ty = y;
		x = tx*cos(B) - ty*sin(B);
		y = tx*sin(B) + ty*cos(B);
	}
};

//*��������
double dist(Point a,Point b)
{
    return sqrt((a-b)*(a-b));
}


/*
 * ��͹����Graham�㷨
 * ��ı��0~n-1
 * ����͹�����Stack[0~top-1]Ϊ͹���ı��
 */
const int MAXN = 1010000;
Point list[MAXN];
int Stack[MAXN],top;
//�����list[0]�ļ�������
bool _cmp(Point p1,Point p2)
{
	double tmp = (p1-list[0])^(p2-list[0]);
	if(sgn(tmp) > 0)return true;
	else if(sgn(tmp) == 0 && sgn(dist(p1,list[0]) - dist(p2,list[0])) <= 0)
		return true;
	else return false;
}
void Graham(int n)
{
	Point p0;
	int k = 0;
	p0 = list[0];
	//�����±ߵ�һ����
	for(int i = 1;i < n;i++)
	{
		if( (p0.y > list[i].y) || (p0.y == list[i].y && p0.x > list[i].x) )
		{
			p0 = list[i];
			k = i;
		}
	}
	swap(list[k],list[0]);
	sort(list+1,list+n,_cmp);
	if(n == 1)
	{
		top = 1;
		Stack[0] = 0;
		return;
	}
	if(n == 2)
	{
		top = 2;
		Stack[0] = 0;
		Stack[1] = 1;
		return ;
	}
	Stack[0] = 0;
	Stack[1] = 1;
	top = 2;
	for(int i = 2;i < n;i++)
	{
		while(top > 1 && sgn((list[Stack[top-1]]-list[Stack[top-2]])^(list[i]-list[Stack[top-2]])) <= 0)
			top--;
		Stack[top++] = i;
	}
}
const int NUM  = 500;
int X[100],Y[100],R[100];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int N,M;
	while(scanf("%d%d",&N,&M) == 2)
	{
		
		for(int i =0;i < N;i++)
		{
			scanf("%d%d%d",&X[i],&Y[i],&R[i]);
			for(int j = 0;j < NUM;j++)
			{
				double tmp = 2*PI*j/NUM;
				list[j+i*NUM] =  Point( X[i] + R[i]*cos(tmp),Y[i] + R[i]*sin(tmp),i );
			}
			
		}
		int x,y;
		for(int i = 0;i < M;i++)
		{
			scanf("%d%d",&x,&y);
			list[N*NUM+i*3] = Point(x,y,-1);
			scanf("%d%d",&x,&y);
			list[N*NUM+i*3+1] = Point(x,y,-1);	
			scanf("%d%d",&x,&y);
			list[N*NUM+i*3+2] = Point(x,y,-1);
		}
		Graham(N*NUM+M*3);
		double ans = 0;
		//cout<<top<<endl;
		for(int i = 0;i < top;i++)
		{
			int t1 = Stack[i];
			int t2 = Stack[(i+1)%top];
		//	cout<<t1<<" "<<t2<<endl;
	//		printf("%.2lf %.2lf\n",list[t1].x,list[t2].y);
			if(list[t1].index != -1 && list[t2].index == list[t1].index)
			{
				int tt = list[t1].index;
				ans += R[tt]*2*PI/(NUM);
			}
			else ans += dist(list[t1],list[t2]);
		}
		printf("%.5lf\n",ans);
	}
    return 0;
}
