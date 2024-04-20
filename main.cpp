#include<iostream>
#include<graphics.h>
#include<windows.h>

using namespace std;

void menu();

class ping_pong{	
	int padx1, pady1_1, pady1_2, pady1_3, pady1_4;	//paddle1
	int padx2,pady2_1, pady2_2, pady2_3, pady2_4;	//paddle 2
	int bx,by;										//ball
	int score_1, score_2;							//scores
	char text[30];
	int i;
	
	public:
		void score(int,int);
		void display_ball(int, int);
		void display_paddle1(int, int);
		void display_paddle2(int, int);
		
		void display_mand_level_1();		//level : 1 border
		void display_mand_level_2();		//level : 2 border
		void display_mand_level_3();		//level : 3 border

		void play_game_level_1();
		void play_game_level_2();
		void play_game_level_3();
		
		void game_over_1();
		void game_over_2();
};

class table : public ping_pong{
	int x, y, level_shift;
	char text[50];
	public:
		void tutorial();
		void level_menu();
		void loading_animation();
};

void ping_pong::display_ball(int a, int b){
	bx = a;
	by = b;
	setfillstyle(1,WHITE);
	setcolor(WHITE);
	//bar(bx,by,bx+20,by+20);
	circle(bx+10,by+10,15);
}

void ping_pong::display_paddle1(int a, int b){
	padx1   = a,	
	pady1_1 = b,
	setfillstyle(1,RED);
	bar(padx1,pady1_1,padx1+20,pady1_1+80);
}

void ping_pong::display_paddle2(int a, int b){
	padx2   = a,	
	pady2_1 = b,
	setfillstyle(1,BLUE);
	bar(padx2,pady2_1,padx2+20,pady2_1+80);
}

void ping_pong::score(int s1, int s2){
	score_1=s1, score_2=s2;
	
	int t1=score_1,	t2=score_2;
	
	char text[25];
	
	if(t1!=s1 || t2!=s2){
		system("cls");
		cout<<"Player 1 score : "<<score_1<<endl;
		cout<<"Player 2 score : "<<score_2<<endl;
	}
	if(score_1==5)	game_over_1();
	if(score_2==5)	game_over_2();
}

void ping_pong::display_mand_level_1(){
	setfillstyle(1,GREEN);
	
	bar(0,0,1020,20);		    //top bar
	bar(0,740,1020,760);		//bottom bar
	bar(0,0,20,760);		    //right bar
	bar(1000,0,1020,760);		//left bar
}

void ping_pong::display_mand_level_2(){
	setfillstyle(1,GREEN);
	bar(0,0,1020,20);		    //top bar
	bar(0,740,1020,760);		//bottom bar
	bar(0,0,20,760);		    //right bar
	bar(1000,0,1020,760);		//left bar
	bar(500,320,520,440);		//mid obstacle
}

void ping_pong::display_mand_level_3(){
	setfillstyle(1,GREEN);
	bar(0,0,1020,20);		    //top bar
	bar(0,740,1020,760);		//bottom bar
	bar(0,0,20,760);		    //right bar
	bar(1000,0,1020,760);		//left bar
	bar(520,0,540,180);			//mid bar top
	bar(520,580,540,760);		//mid bar bottom
}

void ping_pong::play_game_level_1(){	//level 1
	table m;
	int ballx=500, 	bally=380;  //ball position
	int px1 = 40,   py1 = 380;	//paddle 1
	int px2 = 960,  py2 = 380;	//paddle 2
	
	int dir=1;					//determining direction
	int a1=0,a2=0;				//storing score
	int paddle_hit=0;			//counting number of hits for increasing the speed of ball
	int i=0;
	
	int point_a1_y=325;
	int point_a2_y=325;
	m.loading_animation();
	
	for(;;)
	{
		setfillstyle(1,BLACK);
		floodfill(21,21,YELLOW);
		
		display_mand_level_1();
		display_ball(ballx,bally);
		
		display_paddle1(px1, py1);
		display_paddle2(px2, py2);

		//graphical representation of score of player 1 
		point_a1_y=325;	
		setfillstyle(1,WHITE);
		
		for(i=0;i<a1;i++)
		{
			bar(0,point_a1_y,20,point_a1_y+20);
			point_a1_y+=30;
		}
		
		point_a2_y=325;
		for(i=0;i<a2;i++)
		{
			bar(1000,point_a2_y,1020,point_a2_y+20);
			point_a2_y+=30;
		}		

		//changing ball position
		if(dir==1){					//ball direction : right down
			ballx+=20;
			bally+=20;
		}					
		else if(dir==2){	        //ball direction : right up
			ballx+=20;
			bally-=20;
		}							
		else if(dir==3){            //ball direction : left up              
			ballx-=20;
			bally-=20;
		}							
		else{                        //ball direction : left down
			ballx-=20;
			bally+=20;
		}							

		//changing ball direction
		if(ballx==20  && dir==4 || bally<=20  && dir==2)	dir=1;
		if(ballx==20  && dir==3 || bally==720 && dir==1)	dir=2;
		if(bally>=720 && dir==4 || ballx==980 && dir==2)	dir=3;
		if(bally==20  && dir==3 || ballx==980 && dir==1)	dir=4;
		
		//changing paddle 1 position
		if(GetAsyncKeyState(VK_UP))
			if(py2>=40)
				py2-=20;

		if(GetAsyncKeyState(VK_DOWN))
			if(py2<=640)
				py2+=20;

		//changing paddle 2 position
		if(GetAsyncKeyState(VK_TAB))
			if(py1>=40)
				py1-=20;
		
		if(GetAsyncKeyState(VK_LCONTROL))
			if(py1<=640)
				py1+=20;

		//conditions for paddles hitting the ball : paddle 1
		if(ballx-20==px1)
		{
			if(bally==py1 || bally==py1+20 || bally==py1+40 || bally==py1+60)
			{
				if(dir==3)	dir=2;
				if(dir==4)	dir=1;

				paddle_hit++;
			}
			
			//corner top hit case
			if(bally+20==py1)
				if(dir==4)
					dir=2;
			
			//bottom top hit case
			if(bally-20==py1+60)
				if(dir==3)
					dir=1;
		}
				
		//conditions for paddles hitting the ball : paddle 2
		if(ballx+20==px2)
		{
			if(bally==py2 || bally==py2+20 || bally==py2+40 || bally==py2+60)
			{
				if(dir==1)	dir=4;
				if(dir==2)	dir=3;
			}
			
			//corner hit case top
			if(bally+20==py2)
				if(dir==1)
					dir=3;
			
			//bottom hit case
			if(bally-20==py2+60)
				if(dir==2)
					dir=4;
		}
		
		//unusual game abortion
		if(GetAsyncKeyState(VK_ESCAPE))
			menu();
		
		//changing score	1020 760
		if(ballx==980)		a1++;
		if(ballx==20)		a2++;
		
		score(a1,a2);
		
		if(paddle_hit<=5)			delay(25);
		else if(paddle_hit<=10)		delay(15);
		else						delay(10);
	}
}

//level 2
void ping_pong::play_game_level_2(){	
	int ballx=520, 	bally=380;	//ball position
	int px1 = 40,   py1 = 380;	//paddle 1
	int px2 = 960,  py2 = 380;	//paddle 2
	
	int dir=1;	      		    //determining direction
	int a1=0,a2=0;		        //storing score
	int paddle_hit=0;	        //counting number of hits for increasing the speed of ball
	
	int i=0;
	
	table m;
	m.loading_animation();
	
	int point_a1_y=325;
	int point_a2_y=325;
	
	while(1)
	{
		setfillstyle(1,BLACK);
		floodfill(21,21,YELLOW);
		
		display_mand_level_2();
		display_ball(ballx,bally);
		
		display_paddle1(px1, py1);
		display_paddle2(px2, py2);

		//graphical representation of score of player 1 
		point_a1_y=325;	
		setfillstyle(1,WHITE);
		for(i=0;i<a1;i++)
		{
			bar(0,point_a1_y,20,point_a1_y+20);
			point_a1_y+=30;
		}
		
		point_a2_y=325;
		for(i=0;i<a2;i++)
		{
			bar(1000,point_a2_y,1020,point_a2_y+20);
			point_a2_y+=30;
		}

		//changing ball position
		if(dir==1){					//ball direction : right down
			ballx+=20;
			bally+=20;
		}					
		else if(dir==2){	            //ball direction : right up
			ballx+=20;
			bally-=20;
		}							
		else if(dir==3){            //ball direction : left up              
			ballx-=20;
			bally-=20;
		}							
		else{                        //ball direction : left down
			ballx-=20;
			bally+=20;
		}							

		//changing ball direction
		if(ballx==20  && dir==4 || bally<=20  && dir==2)	dir=1;
		if(ballx==20  && dir==3 || bally==720 && dir==1)	dir=2;
		if(bally>=720 && dir==4 || ballx==980 && dir==2)	dir=3;
		if(bally==20  && dir==3 || ballx==980 && dir==1)	dir=4;
		
		//changing paddle 1 position
		if(GetAsyncKeyState(VK_UP))
			if(py2>=40)
				py2-=20;

		if(GetAsyncKeyState(VK_DOWN))
			if(py2<=640)
				py2+=20;
		
		//changing paddle 2 position
		if(GetAsyncKeyState(VK_TAB))
			if(py1>=40)
				py1-=20;
		
		if(GetAsyncKeyState(VK_LCONTROL))
			if(py1<=640)
				py1+=20;
		
		//conditions for paddles hitting the ball : paddle 1
		if(ballx-20==px1)
		{
			if(bally==py1 || bally==py1+20 || bally==py1+40 || bally==py1+60)
			{
				if(dir==3)	dir=2;
				if(dir==4)	dir=1;

				paddle_hit++;
			}
			//corner top hit case
			if(bally+20==py1)
				if(dir==4)
					dir=2;
					
			//bottom top hit case
			if(bally-20==py1+60)
				if(dir==3)
					dir=1;
		}
				
		//conditions for paddles hitting the ball : paddle 2
		if(ballx+20==px2)
		{
			if(bally==py2 || bally==py2+20 || bally==py2+40 || bally==py2+60)
			{
				if(dir==1)	dir=4;
				if(dir==2)	dir=3;
			}
			
			//corner hit case top
			if(bally+20==py2)
				if(dir==1)
					dir=3;

			//bottom hit case
			if(bally-20==py2+60)
				if(dir==2)
					dir=4;
		}
		
		//changing score
		if(ballx==980)		a1++;
		if(ballx==20)		a2++;
		
		score(a1,a2);

		if(paddle_hit<=5)			delay(25);
		else if(paddle_hit<=10)		delay(15);
		else						delay(10);
		
		//mid obstacle of level 2
		//when ball is moving right direction
		if(ballx+20==500)
		{
			for(i=0;i<=120;i+=20)
			{
				if(bally==320+i)
				{
					if(dir==1)	dir=4;
					if(dir==2)	dir=3;
				}
			}
			//corner hit top
			if(bally==300)
				if(dir==1)	
					dir=3;
			
			//corner hit top
			if(bally+20==440)
				if(dir==2)	
					dir=4;
		}
		
		//when ball is moving left direction
		if(ballx==520)
		{
			for(i=0;i<=120;i+=20)
			{
				if(bally==320+i)
				{
					if(dir==3)	dir=2;
					if(dir==4)	dir=1;
				}
			}
			
			//corner hit top
			if(bally==300)
				if(dir==4)	
					dir=2;
			
			//corner hit top
			if(bally+20==440)
				if(dir==3)	
					dir=1;
		}
		
		//unusual game abortion
		if(GetAsyncKeyState(VK_ESCAPE))
			menu();
	}
}

void ping_pong::play_game_level_3(){	//level 3
	int ballx=500, 	bally=380;  //ball position
	int px1 = 40,   py1 = 380;	//paddle 1
	int px2 = 960,  py2 = 380;	//paddle 2
	
	int dir=1;					//determining direction
	int a1=0,a2=0;				//storing score
	int paddle_hit=0;			//counting number of hits for increasing the speed of ball
	int i=0;
	
	int point_a1_y=325;
	int point_a2_y=325;
	
	table m;
	m.loading_animation();
	
	for(;;)
	{
		setfillstyle(1,BLACK);
		floodfill(21,21,YELLOW);
		
		display_mand_level_3();
		display_ball(ballx,bally);
		
		display_paddle1(px1, py1);
		display_paddle2(px2, py2);
	
		//graphical representation of score of player 1 
		point_a1_y=325;	
		setfillstyle(1,WHITE);
		for(i=0;i<a1;i++)
		{
			bar(0,point_a1_y,20,point_a1_y+20);
			point_a1_y+=30;
		}
		
		point_a2_y=325;
		for(i=0;i<a2;i++)
		{
			bar(1000,point_a2_y,1020,point_a2_y+20);
			point_a2_y+=30;
		}

		//changing ball position
		if(dir==1){					//ball direction : right down
			ballx+=20;
			bally+=20;
		}					
		else if(dir==2){	        //ball direction : right up
			ballx+=20;
			bally-=20;
		}							
		else if(dir==3){            //ball direction : left up              
			ballx-=20;
			bally-=20;
		}							
		else{                       //ball direction : left down
			ballx-=20;
			bally+=20;
		}							

		//changing ball direction
		if(ballx==20  && dir==4 || bally<=20  && dir==2)	dir=1;
		if(ballx==20  && dir==3 || bally==720 && dir==1)	dir=2;
		if(bally>=720 && dir==4 || ballx==980 && dir==2)	dir=3;
		if(bally==20  && dir==3 || ballx==980 && dir==1)	dir=4;
		
		//changing paddle 1 position
		if(GetAsyncKeyState(VK_UP))
			if(py2>=40)
				py2-=20;

		if(GetAsyncKeyState(VK_DOWN))
			if(py2<=640)
				py2+=20;

		//changing paddle 2 position
		if(GetAsyncKeyState(VK_TAB))
			if(py1>=40)
				py1-=20;

		if(GetAsyncKeyState(VK_LCONTROL))
			if(py1<=640)
				py1+=20;
		
		//conditions for paddles hitting the ball : paddle 2
		if(ballx+20==px2)
		{
			if(bally==py2 || bally==py2+20 || bally==py2+40 || bally==py2+60)
			{
				if(dir==1)	dir=4;
				if(dir==2)	dir=3;
			}
			
			//corner hit case top
			if(bally+20==py2)
				if(dir==1)
					dir=3;
			
			//bottom hit case
			if(bally-20==py1+80)
				if(dir==2)
					dir=4;
		}
		
		//conditions for paddles hitting the ball : paddle 1
		if(ballx-20==px1)
		{
			if(bally==py1 || bally==py1+20 || bally==py1+40 || bally==py1+60)
			{
				if(dir==3)	dir=2;
				if(dir==4)	dir=1;
				paddle_hit++;
			}
			
			//corner top hit case
			if(bally+20==py1)
				if(dir==4)
					dir=2;
			
			//bottom top hit case
			if(bally-20==py1+80)
				if(dir==3)
					dir=1;
		}
		
		//mid top and bottom bar hit case : player 1 side
		if(ballx+20==520)
		{
			if(	bally==40 || bally==60 || bally==80 || bally==100 || bally==120 || bally==140 || bally==160 ||
				bally==580 || bally==600 || bally==620 || bally==640 || bally==660 || bally==680 || bally==700 )
			{
				if(dir==2)	dir=3;
				if(dir==1)	dir=4;
			}
			
			//corner top hit
			if( bally==20 || bally==180)
				if(dir==2)	
					dir=4;
			
			//corner hit
			if(bally==720 || bally==560)
				if(dir==1)	
					dir=3;
		}

		//mid top and bottom bar hit case : player 2 side
		if(ballx==540)
		{
			if( bally==40 || bally==60 || bally==80 || bally==100 || bally==120 || bally==140 || bally==160 ||
				bally==580 || bally==600 || bally==620 || bally==640 || bally==660 || bally==680 || bally==700 )
			{
				if(dir==3)	dir=2;
				if(dir==4)	dir=1;
			}
			
			//mid top corner bar hit case
			if(bally==20 || bally==180)
				if(dir==3)
					dir=1;
			
			//mid bottom corner bar hit case
			if(bally==720 || bally==560)
				if(dir==4)
					dir=2;
		}
		
		//flat corner hit case
		if(ballx==520 && bally==560)
		{
				if(dir==1)	dir=2;
				if(dir==4)	dir=3;			
		}
		
		//changing score	1020 760
		if(ballx==980)		a1++;
		if(ballx==20)		a2++;
		
		score(a1,a2);

		if(paddle_hit<=5)			delay(25);
		else if(paddle_hit<=10)		delay(15);
		else						delay(10);
		
		//unusual game abortion
		if(GetAsyncKeyState(VK_ESCAPE))
			menu();
	}
}

void ping_pong::game_over_1(){
	i = 1;
	
	for(;;)
	{
		setcolor(WHITE);
		
		strcpy(text,"Game over");
		
		settextstyle(8,HORIZ_DIR,4);
		
		outtextxy(512-90,360-25,text);
		
		rectangle(512-120,380-60,512+120,380);
		
		settextstyle(8,HORIZ_DIR,1);
		
		bar(0,445,20,465);
		
		strcpy(text,"Player 1 won the match");
		
		outtextxy(391,400,text);
		
		if(i==1){
			setcolor(WHITE);
			i=2;
		}
		else{
			setcolor(BLACK);
			i=1;
		}
	
		strcpy(text,"Press ENTER to continue...");
		outtextxy(377,700,text);
		
		if(GetAsyncKeyState(VK_RETURN))
			break;
		
		delay(500);
	}
	menu();
}

void ping_pong::game_over_2(){
	
	i = 1;
	
	for(;;)
	{
		setcolor(WHITE);
		
		strcpy(text,"Game over");
		settextstyle(8,HORIZ_DIR,4);
		outtextxy(512-90,360-25,text);
		
		rectangle(512-120,380-60,512+120,380);
		
		settextstyle(8,HORIZ_DIR,1);
		
		bar(1000,445,1020,465);
			
		strcpy(text,"Player 2 won the match");
		outtextxy(391,400,text);
		
		if(i==1){
			setcolor(WHITE);
			i=2;
		}
		else{
			setcolor(BLACK);
			i=1;
		}
	
		strcpy(text,"Press ENTER to continue...");
		outtextxy(377,700,text);
		
		if(GetAsyncKeyState(VK_RETURN))
			break;

		delay(500);
	}
	menu();
}

int main(){
//	int initwindow(int width = 1024, int height = 768, const char* title="Ping-pong", int left=0, int top=0);
    initwindow(1024,768);
    menu();
    closegraph();
	return 0;
}

void menu(){
	table play;
	
	int shift = 1;
	char text[15];
    
	for(;;)
    {
		setfillstyle(1,BLACK);
		floodfill(21,21,YELLOW);
	
    	setcolor(WHITE);
		strcpy(text,"PING PONG");
		settextstyle(8,HORIZ_DIR,5);
	    outtextxy(396,227,text);
			
		settextstyle(8,HORIZ_DIR,2);
		strcpy(text,"Quick play");
	    outtextxy(449,316,text);
			
	    strcpy(text,"Choose level");
		settextstyle(8,HORIZ_DIR,2);
	    outtextxy(439,366,text);
			
	    strcpy(text,"How to play");
		settextstyle(8,HORIZ_DIR,2);
	    outtextxy(442,416,text);
	    	
	    strcpy(text,"Exit");
		settextstyle(8,HORIZ_DIR,2);
	    outtextxy(482,466,text);
			
	    if(GetAsyncKeyState(VK_DOWN))
			if(shift<4)
				shift++;
	
		if(GetAsyncKeyState(VK_UP))
			if(shift>1)
				shift--;
	    	
	    setcolor(GREEN);
	    setfillstyle(1,GREEN);
		
		setlinestyle(1,1,2);

		if(shift==1)	rectangle(396,302,624,352);
		if(shift==2)	rectangle(396,352,624,402);
		if(shift==3)	rectangle(396,402,624,452);
		if(shift==4)	rectangle(396,452,624,502);
			
		if(GetAsyncKeyState(VK_RETURN))
		{
			if(shift==1)	play.play_game_level_1();	//quick play	
			if(shift==2)	play.level_menu();			//choosing level
			if(shift==3)	play.tutorial();			//how to play
			if(shift==4)	exit(1);		
		}		
		delay(50);
	}
}

void table::level_menu(){
	
	level_shift=0;
	
	for(;;)
	{
		setfillstyle(1,BLACK);
		floodfill(21,21,YELLOW);
		
		setcolor(WHITE);

		strcpy(text,"PING PONG");
		settextstyle(8,HORIZ_DIR,5);
	    outtextxy(396,227,text);

		settextstyle(8,HORIZ_DIR,2);
		
		strcpy(text,"Choose level");
	    outtextxy(437,316,text);
			
	    strcpy(text,"Easy");
	    outtextxy(484,366,text);
			
	    strcpy(text,"Moderate");
	    outtextxy(462,416,text);
	    	
	    strcpy(text,"Hard");
	    outtextxy(484,466,text);
			
		strcpy(text,"Go back");
	    outtextxy(469,516,text);
		
	    if(GetAsyncKeyState(VK_DOWN))
			if(level_shift<4)
				level_shift++;
	
		if(GetAsyncKeyState(VK_UP))
			if(level_shift>1)
				level_shift--;
	    	
		if(GetAsyncKeyState(VK_RETURN))
		{
			if(level_shift==1)	play_game_level_1();		
			if(level_shift==2)	play_game_level_2();
			if(level_shift==3)	play_game_level_3();		
			if(level_shift==4)	menu();		
		}
		
		setcolor(GREEN);
		
		if(level_shift==1)	rectangle(396,302+50,624,352+50);
		if(level_shift==2)	rectangle(396,352+50,624,402+50);
		if(level_shift==3)	rectangle(396,402+50,624,452+50);
		if(level_shift==4)	rectangle(396,452+50,624,502+50);
		
		delay(50);
	}		
}

void table::tutorial(){
	for(;;)
	{
		setfillstyle(1,BLACK);
		floodfill(20,20,BROWN);
	
		setcolor(WHITE);	
		settextstyle(7,HORIZ_DIR,7);
		strcpy(text,"Ping-Pong");
		outtextxy(310,180,text);
		
		setcolor(RED);
		settextstyle(3,HORIZ_DIR,1);
		setfillstyle(1,RED);
		bar(260,355,280,480);
		
		strcpy(text,"Red  - Player 1");
		outtextxy(290,355,text);
			
		strcpy(text, "Conrol for player 1 : ");	
		outtextxy(290,405,text);
		
		strcpy(text,"Tab       - Up");
		outtextxy(290,430,text);
		
		strcpy(text,"Control - Down");
		outtextxy(290,455,text);
			
		setcolor(BLUE);
		setfillstyle(1,BLUE);
			
		bar(765,355,785,480);
		strcpy(text,"Blue - Player 2");			
		outtextxy(575,355,text);
			
		strcpy(text,"Conrol for player 2 : ");
		outtextxy(575,405,text);
	
		strcpy(text,"Up Arrow       - Up");
		outtextxy(575,430,text);
		
		strcpy(text,"Down Arrow  - Down");
		outtextxy(575,455,text);
			
		setcolor(LIGHTGRAY);
		
		strcpy(text,"Rules :");
		outtextxy(260,505,text);
		
		strcpy(text,"-> Player missing the ball 5 times first, looses the game");
		outtextxy(260,560,text);
		
		strcpy(text,"-> Press ESCAPE to quit taw game.");
		outtextxy(260,590,text);
			
		setcolor(DARKGRAY);
		
		strcpy(text,"[Press Escape key to continue]");
		outtextxy(390,655,text);
		
		if(GetAsyncKeyState(VK_ESCAPE))	
			menu();
			
		delay(50);
	}
}

void table::loading_animation(){
	x=510,y=380;
	
	//for 3
	setfillstyle(1,BLACK);
	floodfill(21,21,YELLOW);
	setfillstyle(1,GREEN);
	bar(x-60,y-60,x+60,y-40);
	bar(x-60,y,x+60,y+20);
	bar(x-60,y+60,x+60,y+80);
	bar(x+40,y-60,x+60,y+80);
	delay(1000);
		
	// for 2
	setfillstyle(1,BLACK);
	floodfill(21,21,YELLOW);
	setfillstyle(1,GREEN);
	bar(x-60,y-60,x+60,y-40);
	bar(x-60,y,x+60,y+20);
	bar(x-60,y+60,x+60,y+80);
	bar(x+40,y-60,x+60,y);
	bar(x-40,y,x-60,y+80);
	delay(1000);
						
	// for 1
	setfillstyle(1,BLACK);
	floodfill(21,21,YELLOW);
	setfillstyle(1,GREEN);
	bar(x-10,y-60,x+10,y+80);
	delay(1000);
	
	//for 0
	setfillstyle(1,BLACK);
	floodfill(21,21,YELLOW);
	setfillstyle(1,GREEN);
	bar(x-60,y-60,x+60,y-40);
	bar(x+40,y-60,x+60,y+80);
	bar(x-60,y+60,x+60,y+80);
	bar(x-60,y-60,x-40,y+80);
	delay(1000);
}
