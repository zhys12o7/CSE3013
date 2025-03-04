#include "Header.h" //헤더파일

int main()  //메인함수
{
	int T,N,i; //각각 책 권수, 페이지 수, 반복문에 사용되는 변수
	printf("how many book :"); //입력해야할내용 풀력
	scanf("%d",&T);  //실행해야 할 책의 권수 받기

	for(i=0;i<T;i++)  //책의 권수에 대해서 각각의 페이지 수 입력받기
	{
		printf("number of pages :");  //입력해야 할 내용
		scanf("%d",&N); //사용자가 페이지 수 입력하기
		printf("\n");  //줄바꿈
		page(N);  //페이지를 받고 그 안에 있는 0~9까지의 숫자 카운트 함수
	}
	return 0; //종료
}
