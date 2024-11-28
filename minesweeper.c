/*Vasiliki Kounadi
AM: 2022202000102
dit20102@uop.gr*/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 20

void game(void);
void prep(void);
void makemove(void);
void victory(void);
void loss(void);
void recursive(int x, int y);
void wisdom(void);
void test(int x, int y);
void first_move (void);

int **arr, **hashtag, **flagboard;
int diff, lvl=1, match=0, count=1;
int win=0, lose=0;
int h1,h2, flag, check, pos1, pos2;
int buffaloes, total_buffaloes;
int z,m,n,i,j,x,y,a,b;
char letter;

int main (void)
{ 
  srand(time(NULL));
  prep(); //asks dimensions, difficulty
  return 0;
}

void game(void)
{
      if(diff == 1) 
        total_buffaloes = (m*n)/8;
      else if(diff == 2)
        total_buffaloes = (m*n)/7;
      else if(diff == 3)
        total_buffaloes = (m*n)/6;
      else if(diff == 4)
        total_buffaloes = (m*n)/5;

      //makes the closed # field
      hashtag = (int **) malloc(m * sizeof(int *));
      if(hashtag==NULL)
      {
          printf("memory error");
          exit(1);
      }
      for(z=0;z<m;z++)
      {
          hashtag[z]= (int *)malloc(n * sizeof(int));
          if(hashtag[z]==NULL)
          {
            printf("memory error");
            exit(1);
          }
      }
      
      //fills hashtag
        for(i=0;i<m;i++)
        {
          for(j=0;j<n;j++)
              hashtag[i][j]='#';
        }
      
      //makes the real field
      arr = (int **) malloc(m * sizeof(int *));
      if(arr==NULL)
      {
          printf("memory error");
          exit(1);
      }
      for(z=0;z<m;z++)
      {
          arr[z]= (int *)malloc(n * sizeof(int));
          if(arr[z]==NULL)
          {
            printf("memory error");
            exit(1);
          }
      }
      for(i=0;i<m;i++)
        {
          for(j=0;j<n;j++)
              arr[i][j]=0;
        }


      //fills arr with buffaloes
      buffaloes=0;
        while(buffaloes<= total_buffaloes)
        {
          i=rand()%m;
          j=rand()%n;
          if( arr[i][j] != '@')    //If statement that checks if there is a already there and doesn't place a mine if there is
          {
            arr[i][j] = '@';
            buffaloes++;
          }
        }
        total_buffaloes = buffaloes;
    //outs numbers or empty cell
      for(i=0;i<m;i++)
      {
        for(j=0;j<n;j++)
        {
          if(arr[i][j]!='@')
          {
            if(i-1>=0 && j-1>=0 && arr[i-1][j-1]=='@')
                arr[i][j]=1;
            if(j-1>=0 && arr[i][j-1]=='@')
                arr[i][j]++;
            if(i+1<m && j-1>=0 && arr[i+1][j-1]=='@')
                arr[i][j]++;
            if(i-1>=0 && arr[i-1][j]=='@')
                arr[i][j]++;
            if(i+1<m && arr[i+1][j]=='@')
                arr[i][j]++;
            if(i-1>=0 && j+1<n && arr[i-1][j+1]=='@')
                arr[i][j]++;
            if(j+1<n && arr[i][j+1]=='@')
                arr[i][j]++;
            if(i+1<m && j+1<n && arr[i+1][j+1]=='@')
                arr[i][j]++;
            //empty cells
            if(arr[i][j]==0)
                arr[i][j]='.';
          }
        }
      }

      //TEST prints real array 
      /*for(i=0;i<m;i++)
      {
        for(j=0;j<n;j++)
        {
          if(arr[i][j]=='@' || arr[i][j]=='.') 
            printf("%c  ",arr[i][j]);
          else
            printf("%d  ",arr[i][j]);
        }
        printf("\n");
      }
      printf("\n\n\n\n");*/
      
    first_move();

    //TEST prints real array 
      /*for(i=0;i<m;i++)
      {
        for(j=0;j<n;j++)
        {
          if(arr[i][j]=='@' || arr[i][j]=='.') 
            printf("%c  ",arr[i][j]);
          else
            printf("%d  ",arr[i][j]);
        }
        printf("\n");
      }
      printf("\n\n\n\n");*/

    //START
      while ( win!=1 || lose!=1) 
      {
        //prints field
        printf("    ");   //prints column numbers
        for(j=0;j<n;j++)
        {  
          if(j+1>9)//prints row number
            printf("%d ",j+1);
          else
            printf("%d  ", j+1);
        }
        printf("\n---");
        for(j=0;j<n;j++)
          {printf("---");}
        printf("\n");
        
        for(i=0;i<m;i++)
        {
          if(i+1>9)//prints row number
            printf("%d| ",i+1);
          else
            printf("%d | ",i+1);
          
          for(j=0;j<n;j++)
          {
            if(hashtag[i][j]>0 && hashtag[i][j]<9) 
              printf("%d  ",hashtag[i][j]);
            else
              printf("%c  ",hashtag[i][j]);
          }
            printf("\n");
        }
        printf("\n");

        printf("Level: %d\n", lvl);

        if(diff == 1)
          printf("Difficulty: Easy\n");
        else if(diff == 2)
          printf("Difficulty: Medium\n");
        else if(diff == 3)
          printf("Difficulty: Hard\n");
        else if(diff == 4)
          printf("Difficulty: Basicaly impossible\n");
        printf("Uncovered buffaloes: %d\n", buffaloes);
        printf("Make move: ");

        makemove();
      }
}

void makemove(void)
{
  do //reads letter-command
  {
    while((letter = getchar()) != '\n');     
    scanf("%c", &letter);
    if((letter!='s')&& (letter!='S')&& (letter!='b')&& (letter!='B')&& (letter!='h')&& (letter!='H')&& (letter!='w')&& (letter!='W'))
      printf("Invalid command. Please try again\nMake move: ");
  }while(letter!='s'&& letter!='S'&& letter!='b'&& letter!='B'&& letter!='h'&& letter!='H'&& letter!='w'&& letter!='W');
  count++;

  //SHOW
  if(letter=='s'|| letter=='S')
  {
    do //reads numbers
    {
      scanf("%d %d", &x, &y);
      if(x>m || y>n || x<0 || y<0)
      {
        printf("Invalid cell. Please try again\nMake move: ");
        do //reads letter-command
        {
          while((letter = getchar()) != '\n');     
          scanf("%c", &letter);
          if((letter!='s')&& (letter!='S'))
            printf("Command doesn't match 'show'(s/S). Please try again\nMake move: ");
        }while(letter!='s'&& letter!='S');
      }
      else if(hashtag[x-1][y-1]!='#' && hashtag[x-1][y-1]!='*')
      {
        printf("Cell already opened. Please try again\nMake move: ");
        do //reads letter-command
        {
          while((letter = getchar()) != '\n');     
          scanf("%c", &letter);
          if((letter!='s')&& (letter!='S'))
            printf("Command doesn't match 'show'(s/S). Please try again\nMake move: ");
        }while(letter!='s'&& letter!='S');
      }
      else
        break;
    }while(x>m || y>n || x<0 || y<0 || hashtag[x-1][y-1]!='#');


    if(hashtag[x-1][y-1]=='*' && arr[x-1][y-1]!='@') //if replace bell
        buffaloes++;

    if(arr[x-1][y-1]=='@')  //use -1 so that array matches command
    {
      lose=1;
      loss();
    }
    else if (arr[x-1][y-1]=='.')//recursive function
    {
      recursive(x-1, y-1);
    }
    else      
      hashtag[x-1][y-1]=arr[x-1][y-1];



    match=0;//check victory
    for (i=0;i<m;i++) 
    {
      for(j=0;j<n;j++)
      {
        if (hashtag[i][j]==arr[i][j])
          match++;
      }
    }
    if (match==((m*n)-total_buffaloes))
    {
      win=1;
      victory();
    }

    printf("\n\n\n\n"); //down for next move
  }


  //BELL
  else if(letter=='b' || letter=='B')
  {
    do //reads numbers
    {
      scanf("%d %d", &x, &y);
      if(x>m || y>n || x<0 || y<0)
      {
        printf("Invalid cell. Please try again\nMake move: ");
        do //reads letter-command
        {
          while((letter = getchar()) != '\n');     
          scanf("%c", &letter);
          if((letter!='b')&& (letter!='B'))
            printf("Command doesn't match 'bell'(b/B). Please try again\nMake move: ");
        }while(letter!='b'&& letter!='B');
      }
      else if(hashtag[x-1][y-1]!='#' && hashtag[x-1][y-1]!='*')
      {
        printf("Cell already opened. Please try again\nMake move: ");
        do //reads letter-command
        {
          while((letter = getchar()) != '\n');     
          scanf("%c", &letter);
          if((letter!='b')&& (letter!='B'))
            printf("Command doesn't match 'bell'(b/B). Please try again\nMake move: ");
        }while(letter!='b'&& letter!='B');
      }
      else if(hashtag[x-1][y-1]=='*')
      {
        printf("Cell already marked with bell. Please try again\nMake move: ");
        do //reads letter-command
        {
          while((letter = getchar()) != '\n');     
          scanf("%c", &letter);
          if((letter!='b')&& (letter!='B'))
            printf("Command doesn't match 'bell'(b/B). Please try again\nMake move: ");
        }while(letter!='b'&& letter!='B');
      }
      else
        break;
    }while(x>m || y>n || x<0 || y<0 || hashtag[x-1][y-1]!='#');
    

    hashtag[x-1][y-1]='*';
    buffaloes--;

    match=0;//check victory
    for (i=0;i<m;i++) 
    {
      for(j=0;j<n;j++)
      {
        if (hashtag[i][j]==arr[i][j])
          match++;
      }
    }
    if (match==((m*n)-total_buffaloes))
    {
      win=1;
      victory();
    }

    printf("\n\n\n\n"); //down for next move
  }
  
  
  //HELP
  else if(letter=='h' || letter=='H')
  {
    printf("\n\n\n\n"); //down for next move
    for (i=0;i<m;i++)
    {
      for(j=0;j<n;j++)
      {
        if ((arr[i][j]!='@') && (hashtag[i][j]=='#')) //second condition for not opened yet
        {
          h1=i+1;
          h2=j+1;
          break;
        }
      }
    }
    printf("\n~~ HELP: Try stepping on cell %d,%d ~~\n", h1,h2);
  }
  
  
  //WISDOM
  else if(letter=='w' || letter=='W')
  {
    wisdom();
  }
}

void victory (void)
{
  printf("\n\n\n\n");
  //prints field
    printf("    ");   //prints column numbers
    for(j=0;j<n;j++)
    {  
      if(j+1>9)//prints row number
        printf("%d ",j+1);
      else
        printf("%d  ", j+1);
    }
    printf("\n---");
    for(j=0;j<n;j++)
      {printf("---");}
    printf("\n");
      
    for(i=0;i<m;i++)
    {
      if(i+1>9)//prints row number
        printf("%d| ",i+1);
      else
        printf("%d | ",i+1);
        
      for(j=0;j<n;j++)
      {
        if(arr[i][j]>0 && arr[i][j]<9) 
          printf("%d  ",arr[i][j]);
        else
          printf("%c  ",arr[i][j]);
      }
        printf("\n");
    }
    printf("\n");

    win=0;

    for(i=0;i<n;i++)//frees arrays from malloc
      free(arr[i]);
    free(arr);

    for(i=0;i<n;i++)
      free(hashtag[i]);
    free(hashtag);       
  
    printf("\n\n***CONGRATULATIONS!! You have won level %d!***",lvl);
    printf("\nMoves made: %d\n\n\n", count);
    count=1;
    
    lvl++;
    printf("Moving on to level %d...\n\n",lvl);

    m++;//makes new field
    n++;
    if (m==MAX+1 || n==MAX+1) //since 30x30 is maximum field
    {
      printf("\n\n***CONGRATULATIONS!! You have won the full game!***\n\n");
      exit(1);
    }
      

    game();
}

void loss (void)
{
    printf("\n\n\n\n\n\n");
    //prints field
    printf("    ");   //prints column numbers
    for(j=0;j<n;j++)
    {  
      if(j+1>9)//prints row number
        printf("%d ",j+1);
      else
        printf("%d  ", j+1);
    }
    printf("\n---");
    for(j=0;j<n;j++)
      {printf("---");}
    printf("\n");
      
    for(i=0;i<m;i++)
    {
      if(i+1>9)//prints row number
        printf("%d| ",i+1);
      else
        printf("%d | ",i+1);
        
      for(j=0;j<n;j++)
      {
        if(arr[i][j]>0 && arr[i][j]<9) 
          printf("%d  ",arr[i][j]);
        else
          printf("%c  ",arr[i][j]);
      }
        printf("\n");
    }
    printf("\n");

    lose=0;
    printf("\n\n---SORRY! You lost...---");
    printf("\nMoves made: %d\n\n\n", count);

    for(i=0;i<n;i++)
      free(arr[i]);
    free(arr);

    for(i=0;i<n;i++)
      free(hashtag[i]);
    free(hashtag);
    exit(1);
}

void prep(void)
{
  printf("\n\nWELCOME TO MINESWEEPER!\n\n");
  do
  {
    printf("--Enter the dimensions of the jungle (MAX 20x20)--\n");//reads dimensions
    printf("Horizontal squares: ");
    scanf("%d", &m);
    printf("Vertical squares: ");
    scanf("%d", &n);
    if(m>MAX||n>MAX||m<1||n<1) //maximum size is 30x30
    {
      printf("You have surpassed the jungle's maximum dimensions\nPlease try again\n\n");
    }
  }while(m>MAX||n>MAX||m<1||n<1);

  //set diificulty
  do
  {
    printf("\n--Set you difficulty--");
    printf("\nPress 1 for Easy");
    printf("\nPress 2 for Medium");
    printf("\nPress 3 for Hard");
    printf("\nPress 4 for Basically Unbeatable\nType here: ");
    scanf("%d", &diff);
    if(diff != 1 && diff != 2 && diff != 3 && diff != 4)
      printf("You haven't entered a valid difficylty level\nPlease try again\n\n");
  }while(diff != 1 && diff != 2 && diff != 3 && diff != 4);
  printf("\n\n\n\n");
  game(); //calls for malloc arrays and play
}

void wisdom (void)
{
  flagboard = (int **) malloc(m * sizeof(int *));
  if(flagboard==NULL)
  {
      printf("memory error");
      exit(1);
  }
  for(z=0;z<m;z++)
  {
      flagboard[z]= (int *)malloc(n * sizeof(int));
      if(flagboard[z]==NULL)
      {
        printf("memory error");
        exit(1);
      }
  }
      
  for(i=0; i<m; i++)
  {
    for(j=0; j<n; j++)
      flagboard[i][j]=0;
  }

  flag = 0;
  check = 0;
  for(i=0; i<m; i++)
  {
    for(j=0; j<n; j++)
    {
      for(a=0; a<m; a++)
      {
        for(b=0; b<n; b++)
          flagboard[a][b]=0;
      }
      test(i,j);
    
        if(check<flag)
        {
          check = flag;
          pos1 = i+1;
          pos2 = j+1;
          
        }
      flag = 0;
      }
    }

  if(check==0)//if done for . open numbers
  {
    printf("\n\n\n\n"); //down for next move
    for (i=0;i<m;i++)
    {
      for(j=0;j<n;j++)
      {
        if ((arr[i][j]!='@') && (hashtag[i][j]=='#')) //second condition for not opened yet
        {
          pos1=i+1;
          pos2=j+1;
          break;
        }
      }
    }
    printf("\n~~ WISDOM: Try stepping on cell %d,%d ~~\n", pos1,pos2);
  }
  else
  {
    printf("\n\n\n\n");
    printf("\n~~ WISDOM: Try stepping on cell %d,%d ~~\n", pos1,pos2);
  }

  for(i=0;i<n;i++)
    free(flagboard[i]);
  free(flagboard);
}

void test(int x, int y)
{
  if(arr[x][y]!='@' && hashtag[x][y]=='#')
  {
    flag++;

    if(arr[x][y]=='.') //checks if current position containes a dot for the recursion
    {
      flagboard[x][y]=1;
      if (x > 0)
      {
        if (y > 0)
        {
          if(flagboard[x-1][y-1]==0  && hashtag[x-1][y-1]=='#')
            test(x - 1, y - 1);
        } 
        if (x < m-1)
        {
            if(flagboard[x-1][y+1]==0 && hashtag[x-1][y+1]=='#')
              test(x - 1, y + 1);
        }
        if(flagboard[x-1][y]==0 && hashtag[x-1][y]=='#')
          test(x - 1, y);
      }
      if (y > 0)
      {
        if(flagboard[x][y-1]==0 && hashtag[x][y-1]=='#')
          test(x, y - 1);
      }
      if (y < n-1)
      {
        if(flagboard[x][y+1]==0 && hashtag[x][y+1]=='#')
          test(x, y + 1);
      }
      if (x < m-1) 
      {
        if (y > 0)
        {
          if(flagboard[x+1][y-1]==0 && hashtag[x+1][y-1]=='#')
            test(x + 1, y - 1);
        }
        if (y < n-1)
        {
          if(flagboard[x+1][y+1]==0 && hashtag[x+1][y+1]=='#')
            test(x + 1, y + 1);

          if(flagboard[x+1][y]==0 && hashtag[x+1][y]=='#')
            test(x + 1, y);
        }
      }
    }
  }
}

void recursive(int x, int y)
{
  hashtag[x][y]=arr[x][y];
  if(arr[x][y]=='.') //checks if current position containes a dot for the recursion
  {
    if (x > 0)
    {
      if (y > 0)
      {
        if (hashtag[x-1][y-1]=='#')
          recursive(x - 1, y - 1);
      } 
      if (y < n-1)
      {
          if (hashtag[x-1][y+1]=='#')
            recursive(x - 1, y + 1);
      }
      if (hashtag[x - 1][y]=='#')
        recursive(x - 1, y);
    }
    if (y > 0)
    {
      if (hashtag[x][y - 1]=='#')
        recursive(x, y - 1);
    }
    if (y < n-1)
    {
      if (hashtag[x][y + 1]=='#')
        recursive(x, y + 1);
    }
    if (x < m-1) 
    {
      if (y > 0)
      {
        if (hashtag[x + 1][y - 1]=='#')
          recursive(x + 1, y - 1);
      }
      if (y < n-1)
      {
        if (hashtag[x + 1][y + 1]=='#')
          recursive(x + 1, y + 1);
      }
        if (hashtag[x + 1][y]=='#')
          recursive(x + 1, y);
      
    }
  }
}

void first_move (void)
{
  //prints array full of # for the first time
  printf("    ");   //prints column numbers
  for(j=0;j<n;j++)
  {  
    if(j+1>9)//prints row number
      printf("%d ",j+1);
    else
      printf("%d  ", j+1);
  }
  printf("\n---");
  for(j=0;j<n;j++)
    {printf("---");}
  printf("\n");
        
  for(i=0;i<m;i++)
  {
    if(i+1>9)//prints row number
      printf("%d| ",i+1);
    else
      printf("%d | ",i+1);
          
    for(j=0;j<n;j++)
    {
      if(hashtag[i][j]>0 && hashtag[i][j]<9) 
        printf("%d  ",hashtag[i][j]);
      else
        printf("%c  ",hashtag[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  printf("Level: %d\n", lvl);

  if(diff == 1)
    printf("Difficulty: Easy\n");
  else if(diff == 2)
    printf("Difficulty: Medium\n");
  else if(diff == 3)
    printf("Difficulty: Hard\n");
  else if(diff == 4)
  printf("Difficulty: Basicaly impossible\n");
  printf("Uncovered buffaloes: %d\n", buffaloes);
  printf("Make move: ");

  do //reads letter-command
  {
    while((letter = getchar()) != '\n');  //made by tselikas 3ochapter   
    scanf("%c", &letter);
    if((letter!='s')&& (letter!='S')&& (letter!='b')&& (letter!='B')&& (letter!='h')&& (letter!='H')&& (letter!='w')&& (letter!='W'))
      printf("Invalid command. Please try again\nMake move: ");
  }while(letter!='s'&& letter!='S'&& letter!='b'&& letter!='B'&& letter!='h'&& letter!='H'&& letter!='w'&& letter!='W');

//MAKE MOVE BUT IF SHOW AND @ IT CHANGES THE FIELD
  //SHOW
  if(letter=='s'|| letter=='S')
  {
    do //reads numbers
    {
      scanf("%d %d", &x, &y);
      if(x>m || y>n || x<0 || y<0)
      {
        printf("Invalid cell. Please try again\nMake move: ");
        do //reads letter-command
        {
          while((letter = getchar()) != '\n');     
          scanf("%c", &letter);
          if((letter!='s')&& (letter!='S'))
            printf("Command doesn't match 'show'(s/S). Please try again\nMake move: ");
        }while(letter!='s'&& letter!='S');
      }
      else if(hashtag[x-1][y-1]!='#' && hashtag[x-1][y-1]!='*')
      {
        printf("Cell already opened. Please try again\nMake move: ");
        do //reads letter-command
        {
          while((letter = getchar()) != '\n');     
          scanf("%c", &letter);
          if((letter!='s')&& (letter!='S'))
            printf("Command doesn't match 'show'(s/S). Please try again\nMake move: ");
        }while(letter!='s'&& letter!='S');
      }
      else
        break;
    }while(x>m || y>n || x<0 || y<0 || hashtag[x-1][y-1]!='#');


    if(arr[x-1][y-1]=='@')  //use -1 so that array matches command
    {   
        //fills arr with buffaloes
        buffaloes=0;
        for (i=0;i<m;i++) 
        {
          for(j=0;j<n;j++)
            arr[i][j]=0;
        }
        i=j=0;
        while(buffaloes< total_buffaloes) //after testing <= should be just <, there was always 1 extra buffalo
        {
          i=rand()%m;
          j=rand()%n;
          if(i==x-1 && j==y-1)
          {
            i=rand()%m;
            j=rand()%n;
          }
          if( arr[i][j] != '@')    //If statement that checks if there is a already there and doesn't place a mine if there is
          {
            arr[i][j] = '@';
            buffaloes++;
          }
        }
        total_buffaloes = buffaloes;
    //outs numbers or empty cell
      for(i=0;i<m;i++)
      {
        for(j=0;j<n;j++)
        {
          if(arr[i][j]!='@')
          {
            if(i-1>=0 && j-1>=0 && arr[i-1][j-1]=='@')
                arr[i][j]=1;
            if(j-1>=0 && arr[i][j-1]=='@')
                arr[i][j]++;
            if(i+1<m && j-1>=0 && arr[i+1][j-1]=='@')
                arr[i][j]++;
            if(i-1>=0 && arr[i-1][j]=='@')
                arr[i][j]++;
            if(i+1<m && arr[i+1][j]=='@')
                arr[i][j]++;
            if(i-1>=0 && j+1<n && arr[i-1][j+1]=='@')
                arr[i][j]++;
            if(j+1<n && arr[i][j+1]=='@')
                arr[i][j]++;
            if(i+1<m && j+1<n && arr[i+1][j+1]=='@')
                arr[i][j]++;
            //empty cells
            if(arr[i][j]==0)
                arr[i][j]='.';
          }
        }
      }
    hashtag[x-1][y-1]=arr[x-1][y-1];
    if(hashtag[x-1][y-1]=='.')
      recursive(x-1, y-1);
    }
    else if (arr[x-1][y-1]=='.')//recursive function
    {
      recursive(x-1, y-1);
    }
    else
      hashtag[x-1][y-1]=arr[x-1][y-1];

    match=0;//check victory
    for (i=0;i<m;i++) 
    {
      for(j=0;j<n;j++)
      {
        if (hashtag[i][j]==arr[i][j])
          match++;
      }
    }
    if (match==((m*n)-total_buffaloes))
    {
      win=1;
      victory();
    }

    printf("\n\n\n\n"); //down for next move
  }


  //BELL
  else if(letter=='b' || letter=='B')
  {
    do //reads numbers
    {
      scanf("%d %d", &x, &y);
      if(x>m || y>n || x<0 || y<0)
      {
        printf("Invalid cell. Please try again\nMake move: ");
        do //reads letter-command
        {
          while((letter = getchar()) != '\n');     
          scanf("%c", &letter);
          if((letter!='b')&& (letter!='B'))
            printf("Command doesn't match 'bell'(b/B). Please try again\nMake move: ");
        }while(letter!='b'&& letter!='B');
      }
      else if(hashtag[x-1][y-1]!='#' && hashtag[x-1][y-1]!='*')
      {
        printf("Cell already opened. Please try again\nMake move: ");
        do //reads letter-command
        {
          while((letter = getchar()) != '\n');     
          scanf("%c", &letter);
          if((letter!='b')&& (letter!='B'))
            printf("Command doesn't match 'bell'(b/B). Please try again\nMake move: ");
        }while(letter!='b'&& letter!='B');
      }
      else if(hashtag[x-1][y-1]=='*')
      {
        printf("Cell already marked with bell. Please try again\nMake move: ");
        do //reads letter-command
        {
          while((letter = getchar()) != '\n');     
          scanf("%c", &letter);
          if((letter!='b')&& (letter!='B'))
            printf("Command doesn't match 'bell'(b/B). Please try again\nMake move: ");
        }while(letter!='b'&& letter!='B');
      }
      else
        break;
    }while(x>m || y>n || x<0 || y<0 || hashtag[x-1][y-1]!='#');
    

    hashtag[x-1][y-1]='*';
    buffaloes--;

    match=0;//check victory
    for (i=0;i<m;i++) 
    {
      for(j=0;j<n;j++)
      {
        if (hashtag[i][j]==arr[i][j])
          match++;
      }
    }
    if (match==((m*n)-total_buffaloes))
    {
      win=1;
      victory();
    }

    printf("\n\n\n\n"); //down for next move

  }
  
  //HELP
  else if(letter=='h' || letter=='H')
  {
    printf("\n\n\n\n"); //down for next move
    for (i=0;i<m;i++)
    {
      for(j=0;j<n;j++)
      {
        if ((arr[i][j]!='@') && (hashtag[i][j]=='#')) //second condition for not opened yet
        {
          h1=i+1;
          h2=j+1;
          break;
        }
      }
    }
    printf("\n~~ HELP: Try stepping on cell %d,%d ~~\n", h1,h2);
  }
  
  
  //WISDOM
  else if(letter=='w' || letter=='W')
  {
    wisdom();
  }

}