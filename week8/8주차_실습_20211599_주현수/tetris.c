#include "tetris.h"

static struct sigaction act, oact;

int main(){
	int exit=0;

	initscr();
	noecho();
	keypad(stdscr, TRUE);	

	srand((unsigned int)time(NULL));
	createRankList();

	while(!exit){
		clear();
		switch(menu()){
		case MENU_PLAY: play(); break;
		case MENU_RANK: rank(); break;
		case MENU_EXIT: exit=1; break;
		default: break;
		}
	}

	writeRankFile();

	//노드 해제해주기
	NODE* curr=first->link;
	while(curr!=NULL){
		NODE* next=curr->link;
		free(curr);
		curr=next;
	}
	free(first);

	endwin();
	system("clear");
//	printf("%d\n",blockY)
	return 0;
}

void InitTetris(){
	int i,j;

	for(j=0;j<HEIGHT;j++)
		for(i=0;i<WIDTH;i++)
			field[j][i]=0;

	nextBlock[0]=rand()%7;
	nextBlock[1]=rand()%7;
	nextBlock[2]=rand()%7;

	blockRotate=0;
	blockY=-1;
	blockX=WIDTH/2-2;
	score=0;	
	gameOver=0;
	timed_out=0;

	DrawOutline();
	DrawField();
	DrawBlock(blockY,blockX,nextBlock[0],blockRotate,' ');
	DrawNextBlock(nextBlock);
	PrintScore(score);
}

void DrawOutline(){	
	int i,j;
	/* 블럭이 떨어지는 공간의 태두리를 그린다.*/
	DrawBox(0,0,HEIGHT,WIDTH);

	/* next block을 보여주는 공간의 태두리를 그린다.*/
	move(2,WIDTH+10);
	printw("NEXT BLOCK");
	DrawBox(3,WIDTH+10,4,8);
	
	//next next블록을 그릴 박스 생성
	move(0,WIDTH+9);
	DrawBox(9,WIDTH+10,4,8);
	/* score를 보여주는 공간의 태두리를 그린다.*/
	move(15,WIDTH+10);
	printw("SCORE");
	DrawBox(16,WIDTH+10,1,8);
}

int GetCommand(){
	int command;
	command = wgetch(stdscr);
	switch(command){
	case KEY_UP:
		break;
	case KEY_DOWN:
		break;
	case KEY_LEFT:
		break;
	case KEY_RIGHT:
		break;
	case ' ':	/* space key*/
		/*fall block*/
		break;
	case 'q':
	case 'Q':
		command = QUIT;
		break;
	default:
		command = NOTHING;
		break;
	}
	return command;
}

int ProcessCommand(int command){
	int ret=1;
	int drawFlag=0;
	switch(command){
	case QUIT:
		ret = QUIT;
		break;
	case KEY_UP:
		if((drawFlag = CheckToMove(field,nextBlock[0],(blockRotate+1)%4,blockY,blockX)))
			blockRotate=(blockRotate+1)%4;
		break;
	case KEY_DOWN:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX)))
			blockY++;
		break;
	case KEY_RIGHT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX+1)))
			blockX++;
		break;
	case KEY_LEFT:
		if((drawFlag = CheckToMove(field,nextBlock[0],blockRotate,blockY,blockX-1)))
			blockX--;
		break;
	default:
		break;
	}
	if(drawFlag) DrawChange(field,command,nextBlock[0],blockRotate,blockY,blockX);
	return ret;	
}

void DrawField(){
	int i,j;
	for(j=0;j<HEIGHT;j++){
		move(j+1,1);
		for(i=0;i<WIDTH;i++){
			if(field[j][i]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(".");
		}
	}
}


void PrintScore(int score){
	move(17,WIDTH+11);
	printw("%8d",score);
}

void DrawNextBlock(int *nextBlock){
	int i, j;
	for( i = 0; i < 4; i++ ){
		move(4+i,WIDTH+13);
		for( j = 0; j < 4; j++ ){
			if( block[nextBlock[1]][0][i][j] == 1 ){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
	for(i=0;i<4;i++){
		move(10+i,WIDTH+13);
		for(j=0;j<4;j++){
			if(block[nextBlock[2]][0][i][j]==1){
				attron(A_REVERSE);
				printw(" ");
				attroff(A_REVERSE);
			}
			else printw(" ");
		}
	}
}

void DrawBlock(int y, int x, int blockID,int blockRotate,char tile){
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++){
			if(block[blockID][blockRotate][i][j]==1 && i+y>=0){
				move(i+y+1,j+x+1);
				attron(A_REVERSE);
				printw("%c",tile);
				attroff(A_REVERSE);
			}
		}

	move(HEIGHT,WIDTH+10);
}
void DrawBlockWithFeatures(int y, int x, int blockID, int blockRotate){
	
	RecNode node;
	RecNode *Head;
	Head=&node;
	
	//초기화
	Head->lv=0;
	Head->score=0;
	memcpy(Head->field,field,sizeof(field));
	
	
	if(recommendQ==0)
	{
		recommend(Head);
	}
	else if(recommendQ==1){
		modified_recommend(Head);}
	
	
	DrawRecommend(recommendY,recommendX,blockID,recommendR);
	if(recommendQ==0)
		DrawShadow(y,x,blockID,blockRotate);
	DrawBlock(y,x,blockID,blockRotate,' ');
}

void DrawBox(int y,int x, int height, int width){
	int i,j;
	move(y,x);
	addch(ACS_ULCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_URCORNER);
	for(j=0;j<height;j++){
		move(y+j+1,x);
		addch(ACS_VLINE);
		move(y+j+1,x+width+1);
		addch(ACS_VLINE);
	}
	move(y+j+1,x);
	addch(ACS_LLCORNER);
	for(i=0;i<width;i++)
		addch(ACS_HLINE);
	addch(ACS_LRCORNER);
}

void play(){
	int command;
	clear();
	act.sa_handler = BlockDown;
	sigaction(SIGALRM,&act,&oact);
	InitTetris();
	do{
		if(timed_out==0){
			alarm(1);
			timed_out=1;
		}

		command = GetCommand();
		if(ProcessCommand(command)==QUIT){
			alarm(0);
			DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
			move(HEIGHT/2,WIDTH/2-4);
			printw("Good-bye!!");
			refresh();
			getch();

			return;
		}
	}while(!gameOver);

	alarm(0);
	getch();
	DrawBox(HEIGHT/2-1,WIDTH/2-5,1,10);
	move(HEIGHT/2,WIDTH/2-4);
	printw("GameOver!!");
	refresh();
	getch();
	newRank(score);
}

char menu(){
	printw("1. play\n");
	printw("2. rank\n");
	printw("3. recommended play\n");
	printw("4. exit\n");
	return wgetch(stdscr);
}

/////////////////////////첫주차 실습에서 구현해야 할 함수/////////////////////////
int CheckToMove(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
        int x;
        int y;
		//4*4블록을 탐색할 반복문
        for(int i=0;i<BLOCK_HEIGHT;i++){ 
                for(int j=0;j<BLOCK_WIDTH;j++){
                        if(block[currentBlock][blockRotate][i][j]==1){//만약 채워져 있을 경우, 밑의 조건일 경우 0을 리턴
                                y=blockY+i;
                                x=blockX+j;
                        		if(y>=HEIGHT || x<0 || x>=WIDTH || f[y][x]==1 || y<0)
									 return 0;
                        }
        }
		}
        return 1;
}

void DrawChange(char f[HEIGHT][WIDTH],int command,int currentBlock,int blockRotate, int blockY, int blockX){
        
		int i;
		int j;
		//변수 초기화
		int y=blockY;
		int x=blockX;

		//command로 받은 결과의 이전결과를 찾아서 그 전블록을 지우는 과정
		switch(command){
			case KEY_DOWN:
			{
				y=blockY-1;
				break;}
			case KEY_LEFT:
			{
				x=blockX+1;
				break;}
			case KEY_RIGHT:
			{
				x=blockX-1;
				break;}
		}
		//4*4블록에서 채워졌던 과거 블록을 찾아서 지우는 반복문
		for(i=0;i<BLOCK_HEIGHT;i++){
			for(j=0;j<BLOCK_WIDTH;j++){
			if(block[currentBlock][blockRotate][i][j]==1)
				{
					f[y+i][x+j]=0;
                    DrawField();
                }
                 
        }}
		//command에 의해 새로 바뀐 블록을 그리는 과정+ shadow도 그리기
        DrawBlockWithFeatures(blockY,blockX,currentBlock,blockRotate);
        move(9,WIDTH+10);

}

void BlockDown(int sig){
	//checktomove함수를 써서 이동이 가능하면밑으로 한칸 이동시키기
        if(CheckToMove(field,nextBlock[0],blockRotate,blockY+1,blockX))
        {
                blockY+=1;
                DrawChange(field,KEY_DOWN,nextBlock[0],blockRotate,blockY,blockX);}
		//그렇지 않은경우
        else{
			score=score+AddBlockToField(field,nextBlock[0],blockRotate,blockY,blockX);
            if(blockY==-1)
              gameOver=1;

            else{
				 

				
                        score+=DeleteLine(field); //점수갱신
                        nextBlock[0]=nextBlock[1]; //다음블록을 현재블록으로 땡겨오기
						nextBlock[1]=nextBlock[2];
                        nextBlock[2]=rand()%7; //다음블록을 랜덤하게 부여하기
                        DrawNextBlock(nextBlock);
					    blockY=-1;//초기화
                        blockX=WIDTH/2-2;
        				blockRotate=0;
                       
                        PrintScore(score);
                       }
				DrawField();
        }
        timed_out=0;//초기화

 }

int AddBlockToField(char f[HEIGHT][WIDTH],int currentBlock,int blockRotate, int blockY, int blockX){
	int touched=0;
	for(int i=0;i<BLOCK_HEIGHT;i++)
		for(int j=0;j<BLOCK_WIDTH;j++)
			if(block[currentBlock][blockRotate][i][j]==1 && 0<=blockY+i && blockY+i<HEIGHT && 0<=blockX+j && blockX+j<WIDTH)
			{
				f[blockY+i][blockX+j]=1;
                touched++;
				if(recommendQ==1)
				{
					//왼쪽
					if(!(blockX+j==0 || f[blockY+i][blockX+j-1]!=1 || j==0 || block[currentBlock][blockRotate][i][j-1]!=0))
					{
						touched++;
					}
					//오른쪽
					if(blockX+j!=WIDTH-1 && f[blockY+i][blockX+j+1]==1 && j!=BLOCK_WIDTH-1 && block[currentBlock][blockRotate][i][j+1]==0)
					{
						touched++;
					}
					//블록 아래가 비면 엄청 감점.
					if(blockY+i!=HEIGHT-1&&f[blockY+i+1][blockX+j]==0&&i!=BLOCK_HEIGHT-1&&block[currentBlock][blockRotate][i+1][j]==0)
					{
						touched--;
					}
				}
				
			}
	return 10*touched;
	//Block이 추가된 영역의 필드값을 바꾼다.
}
int DeleteLine(char f[HEIGHT][WIDTH]){
        int i;
		int j;
		int flag=1;//한 줄이 채워졌는지 확인하는 변수
		int n=0; //지워진 줄의 갯수
        for(i=0;i<HEIGHT;i++){
				flag=1;
                for(j=0;j<WIDTH;j++){
					//한줄이 다채워지지 않은경우 flag값을 변경한다.
                        if(f[i][j]==0){
							flag=0;
							break;}}
				if(flag==1){
					n++;
					for(j=0;j<WIDTH;j++){
						f[i][j]=0;} //한줄이 다 채워졌을 경우 지운다.

					for(int k=i-1;k>=0;k--){
						for(int m=0;m<WIDTH;m++){
							f[k+1][m]=f[k][m];}} //위에서 한칸씩 내린다.
				            }
		}

        return n*n*100;
        
}

///////////////////////////////////////////////////////////////////////////

void DrawShadow(int y, int x, int blockID,int blockRotate){
	while(CheckToMove(field,blockID,blockRotate,y+1,x)){
		y++;}
	DrawBlock(y,x,blockID,blockRotate,'/');
}
//////////////////////////////////////////////////////////////////
void createRankList(){
	FILE *fp;
	int i,j;

	fp=fopen("rank.txt","r");
	char a[NAMELEN]; //읽어들일 이름
	int s; //읽어들일 개인의 점수
	
	first=malloc(sizeof(NODE));
	first->link=NULL;

	if(fscanf(fp,"%d",&size)!=0)
	{
		for(i=1;i<=size;i++){
			fscanf(fp,"%s %d",a, &s);
			addrank(a,s);}
	}

	printw("%d\n",size);
	fclose(fp);
}

void addrank(char* n, int s){
	NODE* new=malloc(sizeof(NODE));
	new->score=s;
	strcpy(new->name,n);
	new->link=NULL;

	NODE *curr=first;

	NODE *prev=NULL;
	while(curr){
		if(curr->score < s)break;
		prev=curr;
		curr=curr->link;
	}
	if(prev==NULL){
		first=new;}
	else{
		prev->link=new;
		new->link=curr;}
}

void rank(){
	int X=1,Y=size,ch,i,j;
	clear();
	//printw로 세개의 메뉴입력
	printw("1. list ranks from X to Y\n");
	printw("2. list ranks by a specific name\n");
	printw("3. delete a specific rank\n");
	//wgetch로 ch에 메뉴 번호를 받는다.
	ch=wgetch(stdscr);
	
	
	if(ch=='1'){
		//사용자에게 결과 받아오기
		echo();
		printw("X: ");
		scanw("%d",&X);
		printw("Y: ");
		scanw("%d",&Y);
		noecho();

		printw("       name       |   score   \n");
		printw("------------------------------\n");
		
		if(X=='\0') X=0;
		if(Y=='\0') Y=0;
		
		if(X<1) X=1;
		if(Y<1 || Y>size) Y=size;

		//printw("X:%d\n",X);
		//printw("Y:%d\n",Y);

		if(X>Y){
			printw("search failure: no rank in the list\n");
		}

 
		else{


			NODE* curr=first;

			for(i=1;i<X;i++){
				curr=curr->link;}
			for(j=X;j<=Y;j++){
				printw("%-17s | %-10d\n",curr->name,curr->score);
				curr=curr->link;}
		}

	}


	else if(ch=='2'){
		char str[NAMELEN+1];
		int check=0;
		
		echo();
		printw("input the name :");
		scanw("%s",str);
		noecho();

		printw("       name       |   score   \n");
		printw("------------------------------\n");
		int key=0;
		NODE *curr=first;

		while(curr){
			if(strcmp(str,curr->name)==0){
				printw("%-17s | %-10d\n",curr->name,curr->score);
				key++;
			}
			curr=curr->link;
		}
		if(key==0){
			printw("search failure: no name in the list\n");}


	}

	else if(ch=='3'){
		int num;

		echo();
		printw("input the rank: ");
		scanw("%d",&num);
		noecho();

		printw("       name       |   score   \n");
		printw("------------------------------\n");

		NODE *curr=first;
		NODE *prev=NULL;

		if(num<0 || num>size){
			printw("search failure: the rank not in the list\n");}
		else{
			if(num==1){
				prev=curr->link;
				first=prev;
				free(curr);}
			else{
				for(i=1;i<num;i++){
					prev=curr;
					curr=curr->link;}
				prev->link=curr->link;
				free(curr);}
					
			size--;
			printw("result: the rank deleted\n");
			writeRankFile();
		}


	}

	getch();
}

void writeRankFile(){
	int sn, i; //

	FILE *fp =fopen("rank.txt","w"); //파일 열기
	NODE *curr=first;

	if(sn==size-1) return; //추가된 정보가 없으면 종료
	else{
		 //추가 정보가 입력된 경우
		fprintf(fp,"%d\n",size);

		for(i=1;i<=size;i++){
			fprintf(fp,"%s %d\n",curr->name, curr->score);
			curr=curr->link;}
	}
	fclose(fp);
}

void newRank(int score){
	char str[NAMELEN+1];
	int i,j;
	clear();
	echo();
	printw("your name: ");
	scanw("%s",str);
	noecho();
	size++;
	addrank(str,score); //노드를 만들어서 적절한 위치에 삽입하는 것
	writeRankFile();
}
///////////////////////////////////////////////////////////////////////////////////



void DrawRecommend(int y, int x, int blockID,int blockRotate){
	// user code
	DrawBlock(y, x, blockID, blockRotate, 'R');
}

int recommend(RecNode *root){
	int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수
	RecNode node;
	RecNode* childnode=&node;
	int x, y, i, currscore=0;

	for(i=0; i<4; i++)
	{
		for(x=-2;x<=WIDTH+2;x++)
		{
			if(!CheckToMove(root->field, nextBlock[root->lv], i, 0, x))
				continue;
			//level한단계 높이기
			childnode->lv = root->lv+1;
			memcpy(childnode->field, root->field, sizeof(field));

			//field의 width기준으로 왼쪽부터
			y=0;
			while(CheckToMove(root->field, nextBlock[root->lv], i, y+1, x))
				y++;
			currscore = AddBlockToField(childnode->field, nextBlock[root->lv], i, y, x) + DeleteLine(childnode->field);
		
			if(childnode->lv < MAX_LEVEL)
			{
				currscore+=recommend(childnode);
			}
		
			if(!(max>currscore))
			{
				if(root->lv == 0 && (max<currscore||y>recommendY))
				{
					recommendY = y;
					recommendX = x;
					recommendR = i;
				}
				max = currscore;
			}
		}
	}
	return max;
}

int modified_recommend(RecNode *root){
    int max=0; // 미리 보이는 블럭의 추천 배치까지 고려했을 때 얻을 수 있는 최대 점수
    RecNode node;
    RecNode* childnode;
    int x, y, i, currscore=0;

    // user code
    childnode = &node;
    for(i=0; i<=modified_blockrotate[root->lv]; i++)
    {
        for(x=-2;x<=WIDTH+2;x++)
        {
            if(CheckToMove(root->field, nextBlock[root->lv], i, 0, x)==0)
                continue;
            childnode->lv = root->lv+1;
            memcpy(childnode->field, root->field, sizeof(field));
            y=0;
            while(CheckToMove(root->field, nextBlock[root->lv], i, y+1, x))
                y++;
            currscore = AddBlockToField(childnode->field, nextBlock[root->lv], i, y, x) + DeleteLine(childnode->field);
        
            if(childnode->lv < MAX_LEVEL && currscore>=30)
            {
                currscore+=recommend(childnode);
            }
        
            if(max<=currscore)
            {
                if(root->lv == 0 && (max<currscore||y>recommendY))
                {
                    recommendY = y;
                    recommendX = x;
                    recommendR = i;
                }
                max = currscore;
            }
        }
    }
    if(recommendY == 0)
        gameOver = 1;
    return max;
}



void recommendedPlay(){
	// user code
}
