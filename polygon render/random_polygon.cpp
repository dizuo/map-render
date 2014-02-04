#include "random_polygon.h"

#include <ctime>  // random
#include <cstdlib>
#include <cmath>

RandomPolygon::RandomPolygon(unsigned int pointNum, int width, int height)
{
	srand( (unsigned)time( NULL ) );  

	vertexNum = pointNum;
	vertexList = new data_type[ 2*vertexNum ];

	// �����ʼ����  
	for (int i=0; i<vertexNum; i++)  
	{  
		vertexList[i].x = rand() % width;  
		vertexList[i].y = rand() % height;  
	} 

	_grahamScan();
}

RandomPolygon::~RandomPolygon()
{
	if (vertexList)
		delete[] vertexList;

	vertexList = NULL;
	vertexNum = 0;
}

void RandomPolygon::getPolygonContour(float* & contour, unsigned int& pointNum)
{
	pointNum = vertexNum;

	if (contour==NULL)
	{
		contour = new float[ 3*pointNum ];
	}

	for (int i=0; i<pointNum; i++)
	{
		contour[3*i + 0] = vertexList[i].x;
		contour[3*i + 1] = vertexList[i].y;
		contour[3*i + 2] = 0;
	}
}

/******************************************************************************  
�ж������㹹����ʱ��/˳ʱ�뷽�� 
r = multiply(begPnt, endPnt, nextPnt),�õ�(nextPnt-begPnt)*(endPnt-begPne)�Ĳ��  
r>0: nextPnt��ʸ��<beg, end>����ʱ�뷽�� 
r=0: opspep���㹲��  
r<0: ep��ʸ��<beg, end>��˳ʱ�뷽��  
*******************************************************************************/   
double multiply(POINT begPnt,POINT endPnt,POINT nextPnt)   
{   
    return((nextPnt.x-begPnt.x)*(endPnt.y-begPnt.y) - (endPnt.x-begPnt.x)*(nextPnt.y-begPnt.y));   
}   
double distance(const POINT& pnt1, const POINT& pnt2)  
{  
    return sqrtf( (pnt2.x-pnt1.x) * (pnt2.x-pnt1.x) + (pnt2.y-pnt1.y) * (pnt2.y-pnt1.y) );  
}    

void RandomPolygon::_grahamScan()
{
	data_ptr PointSet = vertexList;
	int i,j,k=0,top=2;
	POINT tmp;   
	// ѡȡPointSet��y������С�ĵ�PointSet[k]����������ĵ��ж������ȡ����ߵ�һ��   
	for(i=1; i<vertexNum; i++)   
		if ( PointSet[i].y<PointSet[k].y || (PointSet[i].y==PointSet[k].y) && (PointSet[i].x<PointSet[k].x) )   
			k=i;

	tmp = PointSet[0];   
	PointSet[0] = PointSet[k];   
	PointSet[k] = tmp; // ����PointSet��y������С�ĵ���PointSet[0]   
	//  �Զ��㰴�����PointSet[0]�ļ��Ǵ�С�����������  
	//  ������ͬ�İ��վ���PointSet[0]�ӽ���Զ��������  
	for (i=1; i<vertexNum-1; i++)   
	{   
		k=i;   
		for (j=i+1; j<vertexNum; j++)   
			if ( multiply(PointSet[j], PointSet[k], PointSet[0])>0 ||  // ���Ǹ�С      
				(multiply(PointSet[j], PointSet[k], PointSet[0])==0) && /* ������ȣ�������� */    
				distance(PointSet[0], PointSet[j]) < distance(PointSet[0], PointSet[k]) )   
				k=j;

		tmp = PointSet[i];   
		PointSet[i] = PointSet[k];   
		PointSet[k] = tmp;   
	}  

}
