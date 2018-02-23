#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<graphics.h>
#include<dos.h>
#include<ctype.h>
#include<timer.h>

char c,ch[2];
int x=0,flag;
int err_handl();//Function Prototype
void main();
/****************************************************************************************
		     Class to create objects that
		     store details of each topic
****************************************************************************************/
class Topic
{
    int id;
    char name[25];
    public:
     int getid()  //Accessor  of id
      {  return id;
      }
     char *getname()
     {
	return name;
     }
     void insname(int c)  //To insert data into particular topic
     {

       cin>>name;
       id=c;
     }
     void display()
     {
       cout<<id<<" "<<name<<endl;
     }

};

/****************************************************************************************
		 Class that holds player details
		 intended to be written to file
****************************************************************************************/
class Player
{
  int playerno;
  char name[20];
  int score;
   public:
    int enter(); //int because returns playerno if not a new player
    void display(char ch[2])
    {
       cleardevice();
       outtextxy(200,220,"Playerno : ");
       sprintf(ch,"%d",playerno+1);
       outtextxy(300,220,ch);
       outtextxy(200,240,"Name: ");
       outtextxy(300,240,name);
       sprintf(ch,"%d",score);
       outtextxy(200,260,"Score : ");
       outtextxy(300,260,ch);
    }
    void score_inc()
    {
       score+=10;
    }
    void score_dec()
    {
       score-=5;
    }
    int getpno()
    {
       return playerno;
    }
    char *getpname()
    {
       return name;
    }
    int getscore()
    {
      return score;
     }


}p;

int P_check(char name[20])
{
   Player P1;
   ifstream fin("Player.dat",ios::binary);
   while(!fin.eof())
   {
      fin.read((char*)&P1,sizeof(P1));
      if(strcmpi(P1.getpname(),name)==0)
	 {
	   fin.close();
	   return P1.getpno();
	 }
   }
    fin.close();
    return -1;
}
/*void  gets_modified(char name[])
{
  int x=0;
  do       /* To prevent echo of input to screen and reroute
	       display of input through 'outtextxy' /
   {
     c=getch();
     if(c==8)   //To handle backspace
      {
	if(x==0)
	  continue;
	x--;
	sprintf(ch,"%c",name[x]);
	setcolor(BLACK);
	outtextxy(100+x*9,70,ch);
	setcolor(GREEN);
	continue;
      }
     else if(c==13) //checking for carriage return
     {
	 if(x==0)    //If no name is entered
	 {
	   setcolor(RED);
	   outtextxy(200,200,"Please enter your name properly");
	   delay(500);
	   setcolor(BLACK);
	   outtextxy(200,200,"Please enter your name properly");
	   setcolor(2);
	   continue;
	 }
	 else {
		name[x]='\0';//To terminate string 'name' with null character
		break;
	      }
     }
     name[x]=c;          //x is a global variable initialised to 0
     sprintf(ch,"%c",c);  /*ch also works as temporary buffer
			    to handle backspace/
     outtextxy(100+x*9,70,ch);
     x++;
   }while(x<sizeof(name));

}
*/
/****************************************************************************************
		      To enter name of player and
			 assign player number
****************************************************************************************/
int Player::enter()   //Member function to Class Player
{
   Player P;
   ifstream fin("Player.dat",ios::binary);
   int cnt=0;
   cleardevice();
   x=0;
   settextstyle(2,0,7);
   outtextxy(100,100,"Enter your name");
   do       // To prevent echo of input to screen and reroute
	      // display of input through 'outtextxy'
   {
     c=getch();
     if(c==8)   //To handle backspace
      {
	if(x==0)
	  continue;
	x--;
	sprintf(ch,"%c",name[x]);
	setcolor(BLACK);
	outtextxy(100+x*10,130,ch);
	setcolor(GREEN);
	continue;
      }
     else if(c==13) //checking for carriage return
     {
	 if(x==0)    //If no name is entered
	 {
	   setcolor(RED);
	   outtextxy(200,200,"Please enter your name properly");
	   delay(500);
	   setcolor(BLACK);
	   outtextxy(200,200,"Please enter your name properly");
	   setcolor(2);
	   continue;
	 }
	 else {
		name[x]='\0';//To terminate string 'name' with null character
		break;
	      }
     }
     name[x]=c;          //x is a global variable initialised to 0
     sprintf(ch,"%c",c);  /*ch also works as temporary buffer
			    to handle backspace*/
     outtextxy(100+x*10,130,ch);
     x++;
   }while(x<sizeof(name));

   int flag=P_check(name);
   /*cout<<flag;
   getch();
   exit(0);
   */
   if(flag!=-1)
     {
       playerno=flag;
       x=playerno*sizeof(Player);
       fin.seekg(x);
       fin.read((char*)this,sizeof(Player));  /*To store recognised player's
						 details to current working
						 object*/
       return flag;
     }

   score=0;
   ofstream fout("Player.dat",ios::binary|ios::ate);
   while(!fin.eof())
   {
     fin.read((char *)&P,sizeof(P));
       if(fin.eof())
	 break;
     cnt++;
   }
   fin.close();
   playerno=cnt;
   fout.write((char*)this,sizeof(Player));
   fout.close();
   return playerno;

}
//void player::display()
/**************************************************************************************
		  To accept a string(word) and control gameplay
***************************************************************************************/
int words(char ch[])
{
 int mistakes=0,flag=0,count=0,result=1;
 int size=strlen(ch);
 char p[20];

 strcpy(p,ch);
 outtextxy(150,70,"Input the letters");
 char c,chr[2];
 for(int i=0;i<size;++i)  //To display the number of spaces
  outtextxy(200+(20*i),200,"_");
 int user_inp=0;//Used to advance the cursor
 Timer t;
 t.start();
 for(i=0;i<size;)
    {
      t.stop();
      if(t.time()>20)
      {
	cleardevice();
	cout<<"TIME OUT!!!!!\n";
	getch();
	//result=0;
	return 0;
      }
      t.start();
      count=0;
      c=getch();                     //Recieving the letter
      c=tolower(c);
      ++user_inp;
      flag=0;
      sprintf(chr,"%c",c);
      outtextxy(40+(20*user_inp),40,chr);
      outtextxy(50+(20*user_inp),40,",");
      for(int j=0;j<size;++j)
	 if(c==p[j])               //Checking for a match
	   {
	     flag=1;
	     outtextxy(200+(20*j),198,chr);
	     count++;
	     p[j]='\n';//to exclude value from future consideration

	   }
      if(flag==1)
      {
	i+=count;

      }
      else
	if(flag==0)
       {
	  ++mistakes;
	  if(mistakes==1)
	     {
	      //setcolor(
	      outtextxy(400,100,"     *****      ");
	      outtextxy(400,115,"    * O O *     ");
	      outtextxy(400,125,"    *  ^  *     ");
	      outtextxy(400,135,"    * ___ *     ");
	      outtextxy(400,150,"     *****      ");
	     }

     else if(mistakes==2)
	     {
	      outtextxy(400,160,"      ***       ");
	      outtextxy(400,170,"      ***       ");
	      outtextxy(400,180,"      ***       ");
	      outtextxy(400,190,"      ***       ");
	      outtextxy(400,200,"      ***       ");
	      outtextxy(400,210,"      ***       ");
	      outtextxy(400,220,"      ***       ");
	      outtextxy(400,230,"      ***       ");
	     }

     else if(mistakes==3)
	     {
	      outtextxy(400,175,"     *          ");
	      outtextxy(400,179,"    **          ");
	      outtextxy(400,183,"   **           ");
	      outtextxy(400,187,"  **            ");
	      outtextxy(400,191," **             ");
	      outtextxy(400,195," *              ");
	     }
     else if(mistakes==4)
	     {
	      outtextxy(400,175,"         *      ");
	      outtextxy(400,179,"         **     ");
	      outtextxy(400,183,"          **    ");
	      outtextxy(400,187,"           **   ");
	      outtextxy(400,191,"            **  ");
	      outtextxy(400,195,"             *  ");
	     }

     else if(mistakes==5)
	     {
	      outtextxy(400,230,"     *          ");
	      outtextxy(400,234,"    **          ");
	      outtextxy(400,238,"   **           ");
	      outtextxy(400,242,"  **            ");
	      outtextxy(400,246," **             ");
	      outtextxy(400,250," *              ");
	     }

     else if(mistakes==6)
	     {
	      outtextxy(400,230,"         *      ");
	      outtextxy(400,234,"         **     ");
	      outtextxy(400,238,"          **    ");
	      outtextxy(400,242,"           **   ");
	      outtextxy(400,246,"            **  ");
	      outtextxy(400,250,"             *  ");
	      delay(500);
	      cleardevice();
	      randomize();
	      int rn=random(2); //For two alternate endings.
	      switch(rn)
	      {
	      case 0:
	       setcolor(WHITE);
	       circle(200,170,25);
	       circle(190,165,3);
	       circle(210,165,3);
	       arc(200,185,20,150,5);
	       line(200,195,200,210);

	       setfillstyle(8,WHITE);
	       bar(177,210,222,305);
	       line(177,230,150,270);
	       line(222,230,249,270);
	       line(177,305,155,365);
	       line(222,305,244,365);
	       setcolor(RED);
	       ellipse(200,155,0,360,30,50);
	       line(200,105,200,70);
	       line(200,70,280,70);
	       line(280,70,280,400);
	       line(120,400,300,400);
	       settextstyle(NULL,0,3);
	       outtextxy(330,250,"GAME OVER");
	       settextstyle(NULL,0,NULL);
	       break;
	      case 1:
		   cleardevice();
		   settextstyle(NULL,0,3);
		   setcolor(12);
		   outtextxy(210,40,"GAME OVER");
		   setcolor(RED);
		   settextstyle(NULL,0,NULL);
		   outtextxy(250,100,"     *****      ");
		   outtextxy(250,115,"    * O O *     ");
		   outtextxy(250,125,"    *  ^  *     ");
		   outtextxy(250,135,"    * ___ *     ");
		   outtextxy(250,150,"     *****      ");
		   outtextxy(250,160,"      ***       ");
		   outtextxy(250,170,"     *****      ");
		   outtextxy(250,180,"    *******     ");
		   outtextxy(250,190,"   ** *** **    ");
		   outtextxy(250,200,"  **  ***  **   ");
		   outtextxy(250,210," **   ***   **  ");
		   outtextxy(250,220,"*     ***     * ");
		   outtextxy(250,230,"      ***       ");
		   outtextxy(250,240,"      ***       ");
		   outtextxy(250,250,"      ***       ");
		   outtextxy(250,260,"      ***       ");
		   outtextxy(250,270,"     *****      ");
		   outtextxy(250,280,"    **   **     ");
		   outtextxy(250,290,"   **     **    ");
		   outtextxy(250,300,"  **       **   ");
		   outtextxy(250,310," **         **  ");
		   outtextxy(250,320,"*             * ");
		   outtextxy(400,225,"          ##    ");
		   outtextxy(400,230,"    #########          "   );
		   outtextxy(400,235,"    #########             ");
		   outtextxy(400,240,"          ##         ");
		   outtextxy(400,245,"          ##       ");
		   outtextxy(400,250,"          ##       ");
		   for(int k=0;k<16;++k)
		 {
		   outtextxy(400-(k*8),235,"   @                ");
		   setcolor(BLACK);
		   outtextxy(400-((k-4)*8),235,"@");
		   setcolor(RED);
		   if(k==0)
		     outtextxy(400,235,"    #");
		   delay(100);
		 }
		 setcolor(GREEN);

	       }
	      delay(500);
	      result=0;
	      break;
	     }


       }

	 }                       //End of main loop
   delay(1000);
   return result;
}



int genrand()
{  randomize();
   int r=random(10);
   /*do{
       r=random(10);
      if(ranck.flg=0)
       {
	ranck.rndchk[0]=r;
	break;
       }
      else
      {
	  for(int i=0,i<=ranck.pos,++i)
	    {
	      if(ranck.rndchk==r)
		break;

      else
      {   ranck.pos++;
	  ranck.rndchk[ranck.pos]=r;
	  break;
      }
   while(ranck.pos<
   */
   return r;
}
void getword(char word[],int r,char choice,int &err)
{ char tpcnm[15];
  Topic T;
  switch(choice)
    {
     case '1':strcpy(tpcnm,"Animals.dat");
	      break;
     case '2':strcpy(tpcnm,"Birds.dat");
	      break;
     case '3':strcpy(tpcnm,"Places.dat");
	      break;
     default : err=1;
	       return ;
    }
  ifstream fin(tpcnm,ios::binary);
  while(!fin.eof())
  {
     fin.read((char*)&T,sizeof(Topic)+1);
       if(fin.eof())
	 break;
     if(T.getid()==r)
	strcpy(word,T.getname());
  }
  fin.close();
}
void Modify(Player &P,int pno)
{
   Player P1;
   int p;
   fstream f("Player.dat",ios::binary|ios::in|ios::out);
   while(!f.eof())
   {
     p=f.tellp();
     f.read((char*)&P1,sizeof(P1));
      if(P1.getpno()==pno)
	{

	  f.seekp(p);
	  f.write((char*)&P,sizeof(P));
	  break;
	}
   }
   f.close();
}
/****************************************************************************************
			  Function to execute
			actual part of the game
****************************************************************************************/
void Game()
{
  Player P;
  char choice;
  char word[15];
  int pno=P.enter(),rndno,err=0;
  cleardevice();
  settextstyle(2,NULL,15);
  outtextxy(200,200,"LOADING.....");
  settextstyle(7,NULL,2);
  setcolor(BROWN);
  //setbkcolor(BROWN);
  delay(1000);
  do
  {
   cleardevice();
   outtextxy(200,200,"1. Animals");
   outtextxy(200,240,"2. Birds");
   outtextxy(200,280,"3. Places");
   outtextxy(180,70,"Enter your choice");
   choice=getch();
   if(choice==13)
      return;
   rndno=genrand();
   getword(word,rndno,choice,err);
  }while(err);
  cleardevice();
  settextstyle(NULL,NULL,0);
  setcolor(2);
  int words(char ar[]);//Function prototype
  int result=words(word);
  cleardevice();
  if(result==0)
  {
    outtextxy(220,200,"Better luck next time");
    P.score_dec();
  }
  else
  { //Smiley Face
   setcolor(YELLOW);
   settextstyle(1,0,5);
   outtextxy(200,100,"YOU WIN");
   setaspectratio(13000,10000);
   setcolor(BLACK);
   setfillstyle(1,YELLOW);
   fillellipse(290,240,50,50);
   setfillstyle(1,WHITE);
   fillellipse(270,225,5,5);
   fillellipse(310,225,5,5);
   setfillstyle(1,WHITE);
   for(int k=0;k<30;++k)
   { arc(290,255,270-(3*k),270+(3*k),20);
     delay(100);
   }
   settextstyle(NULL,NULL,0);
     P.score_inc();
  }

 getch();
setcolor(60);
cleardevice();
outtextxy(200,200,"Saving.....");
delay(500);
setcolor(2);
Modify(P,pno);
cleardevice();
P.display(ch);
getch();
}
void Hall_of_Fame()
{
  cleardevice();
  ifstream fin("Player.dat",ios::binary);
  Player Q,P[30];
  int cnt=0;        //1365
  while(!fin.eof())
  {
    fin.read((char *)&Q,sizeof(Player));
     P[cnt]=Q;
     if(fin.eof())
	break;
    cnt++;
  }
  int c=cnt;
  cleardevice();
  //Initiating Bubble Sort to arrange record in desc order of score.
  Player temp;
  for(int i=0;i<c-1;++i)
    for(int j=0;j<c-1-i;++j)
       if(P[j].getscore()<P[j+1].getscore())   //Arranging in desc. order NOT asc. order.
	{
	  temp=P[j];
	  P[j]=P[j+1];
	  P[j+1]=temp;
	}
  setcolor(RED);
  settextstyle(4,0,NULL);
  outtextxy(160,160,"THE HALL OF FAME");
  settextstyle(0,0,NULL);
  getch();
  for(i=0;i<c;++i)
    { P[i].display(ch);
      if(i==0)
	{
	   setcolor(BROWN);
	   settextstyle(7,0,3);
	  for(int j=0;j<4;++j)
	  {
	    outtextxy(200,150,"HIGHSCORE!!");
	    delay(300);
	    setcolor(BLACK);
	    outtextxy(200,150,"HIGHSCORE!!");
	    delay(300);
	    setcolor(BROWN);
	  }
	  settextstyle(0,0,NULL);
	  setcolor(RED);

	}
      delay(1500);
      if(kbhit())
       if(getch()==27)
	   main();
    }
  getch();
  setcolor(GREEN);
  settextstyle(0,0,NULL);

}
/***********************************************************************************************
			       Function for Modification of Topic data
************************************************************************************************/
void Administrator()
{
   //To add new data to a topic
   cleardevice();
   char tpcnm[10],ch;
   int cnt=0;
   cout<<"Enter topic to be modified\n";
   gets(tpcnm);
   strcat(tpcnm,".dat");
   ifstream fin(tpcnm,ios::binary);
   ofstream fout(tpcnm,ios::binary|ios::app);
   Topic T;
   cout<<"Reading initiated.....";
   getch();
   while(!fin.eof())
   {
     fin.read((char*)&T,sizeof(Topic)+1);
     if(fin.eof())
      break;
     cnt++;
   }
   cout<<"count = "<<cnt;
   getch();
   if(cnt<0||cnt>10)
    exit(0);
   do
   {
   cout<<"Enter new record\n";
   T.insname(cnt);
   fout.write((char*)&T,sizeof(Topic)+1);
   cnt++;
   cout<<"Do you wish to continue\n";
   cin>>ch;
   }	while(ch=='Y'||ch=='y');



}
void main()
{

   int gdriver=0,gmode;

   char choice,ch[2];//Menu choice
   //if(flag==1)
   initgraph(&gdriver,&gmode,"C:\\TC\\BGI");
   //flag=0;
   setaspectratio(13000,10000);

   do
    {
      cleardevice();
      setcolor(2);
      //setbkcolor(9);
      cleardevice();
      settextstyle(3,0,NULL);

      outtextxy(120,180,"WELCOME TO BE HANGED");
      outtextxy(180,240,"1.New game");
      outtextxy(180,280,"2.Hall of fame");
      outtextxy(180,320,"3.Exit");
      settextstyle(0,0,NULL);
      choice=getch();
      //sprintf(ch,"%c",choice);
      switch(choice)
	 {
	    case '1': Game();
		     break;
	    case '2': Hall_of_Fame();
		     break;
	    case '3'://setbkcolor(WHITE);
		     cleardevice();
		     setcolor(RED);
		     settextstyle(8,0,4);
		     outtextxy(50,200,"Thank you,Please play again!!");
		     //delay(2000);
		     getch();
		     exit(0);
	    case '7':Administrator();
		     break;
	    default :err_handl();
	 }

   }while(1);
}
int err_handl()
{
	 //Handling invalid input
	 setcolor(RED);
	 outtextxy(200,180,"Error!!Please enter a digit as per given menu..");
	 setcolor(2);
	 getch();
	 cleardevice;
	 return 0;
}