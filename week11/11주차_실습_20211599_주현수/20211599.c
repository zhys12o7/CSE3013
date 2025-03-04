#include "20211599.h"
#pragma warning(disable:4996)

int main() {
	//���� �ʱ�ȭ
	srand(time(NULL));

	scanf("%d", &m);
	scanf("%d", &n);

	init();
	maze();
	print();
}

void init(void) {
	int i, j;

	//2���� �迭 ����
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
        //�������� �����ϴ� ����
        for (int j = 0; j < m - 1; j++) 
        {
            //���� ������ ���� ������
            if (c[i][j] != c[i][j + 1]) 
            {
                //���Ƿ� �� ����
                if (rand() % 2 == 1) 
                {
                    mapp[i * 2 + 1][(j + 1) * 2] = ' ';
                    equalize(c[i][j], c[i][j + 1]);
                }
            }
        }

        //�������� �����ϴ� ����

        flag = 0;

        for (int j = 0; j < m; j++) 
        {
            //���Ƿ� �� ��ġ��
            if (rand() % 2 == 1) 
            {
                mapp[(i + 1) * 2][j * 2 + 1] = ' ';
                c[i + 1][j] = c[i][j];
                flag = 1;
            }

            //���κб��� ���� ��
            if (c[i][j + 1] != c[i][j]) 
            {
                // �� ���� ������ ��찡 ���� ��
                if (flag == 0) 
                {
                    mapp[(i + 1) * 2][j * 2 + 1] = ' ';
                    c[i + 1][j] = c[i][j];
                }
                //�ٽ� �ʱ�ȭ
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

    //ũ�� ���� ���� ���ڸ� �������� ���� ������ �պ�
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
