#include "20211599.h"
#pragma warning(disable:4996)

int main() {
	//난수 초기화
	srand(time(NULL));

	scanf("%d", &m);
	scanf("%d", &n);

	init();
	maze();
	print();
}

void init(void) {
	int i, j;

	//2차원 배열 생성
	mapp = (char**)malloc((2 * n + 1) * sizeof(char*));

	for (i = 0; i < (2 * n + 1); i++) {
		*(mapp + i) = (char*)malloc((2 * m + 1) * sizeof(char));
	}


	for (i = 0; i < 2 * n + 1; i++)
	{
		for (j = 0; j < 2 * n + 1; j++)
		{
			if ((i % 2 == 0) && (j % 2 == 0))
			{
				mapp[i][j]='+';
			}
			else if ((i % 2 == 0) && (j % 2 != 0))
			{
				mapp[i][j] = '-';
			}
			else if ((i % 2 != 0) && (j % 2 == 0))
			{
				mapp[i][j] = '|';
			}
			else if ((i % 2 != 0) && (j % 2 != 0))
			{
				mapp[i][j] = (++cnt);
			}
			
		}
	}
	
    c = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++)
    {
        c[i] = (int*)malloc(sizeof(int) * m);
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            c[i][j] = i * m + j;
        }
    }
}

void maze(void)
{
    int flag;

    for (int i = 0; i < n - 1; i++)
    {
        //수평으로 병합하는 과정
        for (int j = 0; j < m - 1; j++) 
        {
            //서로 영역이 같지 않으면
            if (c[i][j] != c[i][j + 1]) 
            {
                //임의로 벽 삭제
                if (rand() % 2 == 1) 
                {
                    mapp[i * 2 + 1][(j + 1) * 2] = ' ';
                    equalize(c[i][j], c[i][j + 1]);
                }
            }
        }

        //수직으로 병합하는 과정

        flag = 0;

        for (int j = 0; j < m; j++) 
        {
            //임의로 벽 합치기
            if (rand() % 2 == 1) 
            {
                mapp[(i + 1) * 2][j * 2 + 1] = ' ';
                c[i + 1][j] = c[i][j];
                flag = 1;
            }

            //끝부분까지 갔을 때
            if (c[i][j + 1] != c[i][j]) 
            {
                // 그 전에 합쳐진 경우가 없을 때
                if (flag == 0) 
                {
                    mapp[(i + 1) * 2][j * 2 + 1] = ' ';
                    c[i + 1][j] = c[i][j];
                }
                //다시 초기화
                flag = 0;
            }
        }
    }

    for (int j = 0; j < m - 1; j++) 
    {
        if (c[n - 1][j] != c[n - 1][j + 1]) 
        {
            mapp[2 * n - 1][(j + 1) * 2] = ' ';
            equalize(c[n - 1][j], c[n - 1][j + 1]);

        }
    }
}


void equalize(int a, int b)
{
    int i, j;
    int temp;

    //크기 비교후 적은 숫자를 영역으로 가진 것으로 합병
    if (a > b)
    {
        temp = b;
        b = a;
        a = temp;
    }
    for (i = 0; i < n ; i ++)
    {
        for (j = 0; j <  m ; j++)
        {
            if (c[i][j] == b)
                c[i][j] = a;
        }
    }
}

void print(void)
{
    int i, j;
    FILE *fp = fopen("maze.maz", "w");

    for (i = 0; i <= 2 * n ; i++)
    {
        for (j = 0; j <= 2 * m ; j++)
        {
            if ((i % 2 != 0) && (j % 2!=0))
            {
                fprintf(fp, " ");
                printf(" ");
            }
            else
            {
                fprintf(fp, "%c", mapp[i][j]);
                printf("%c", mapp[i][j]);
            }
        }
        fprintf(fp, "\n");
        printf("\n");
    }
}

int mn(int a, int b)
{
    if (a < b)
        return a;
    return b;
}
