#include "Header.h"//헤더파일

void print(int a[])//찾은 결과를 출력하는 함수
{
	int i;//반복문에 사용되는 변수
	for(i=0;i<10;i++)//0~9까지 각각의  갯수 출력
	{
		printf("%d : %d \n",i,a[i]); //숫자 0은 페이지를 통틀어서 몇개 나오는지 출력
	}
}
