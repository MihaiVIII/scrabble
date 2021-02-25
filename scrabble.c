#include <stdio.h>
#include <string.h>
#include "scrabble.h"

void print_board(char gameboard[15][15])
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0;j < 15 ;j++)
        {
            printf("%c ",gameboard[i][j]);
        }
        printf("\n");
    }
}


void game_board_build(char a[15][15]) 
{
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
        {
            a[i][j] = '.';
        }
    }
}


void wrt_word_x(char a[15][15],int x,int y,char w[20])
{   int i = 0;
    for (int j = y; j < (int)strlen(w) + y ; j++)
    {
        a[x][j] = w[i];
        i++;
    }
}

void wrt_word_y(char a[15][15],int x,int y,char w[20])
{   int i = 0;
    for (int j = x; j < (int)strlen(w) + x ; j++)
    {
        a[j][y] = w[i];
        i++;
    }
}

void wrt_word_d(char a[15][15],int x,int y,int d,char w[20])
{   
    if (d == 0)
    {
        wrt_word_x(a,x,y,w);
    }
    else
    {
        wrt_word_y(a,x,y,w);
    }
    
}

void wrt_word_i(char a[15][15],int i,char w[20])
{   
    if (i > 1000)
    {
        wrt_word_d(a,i/1000%100,i/10%100,i%10,w);
    } 
}

void split(char w[30],int *x,int *y,int *d)
{
    *x = 0;
    *y = 0;
    *d = 0;
    int i = 0;
    
    while (w[i] != ' ')
    {
        *x = (*x) * 10 + w[i]-48;
        i++;
    }
    i++;
    while (w[i] != ' ' )
    {
        *y = (*y)*10 + w[i]-48;
        i++;
    }
    i++;
    while (w[i] != ' ' )
    {
        *d = (*d)*10 + w[i]-48;
        i++;
    }
    i++;

    
    strcpy(w,w + i);
    w[strlen(w)-1] = 0;
}

int count_score(int x,char w[30])
{
    for(int i = 0;i < (int)(strlen (w)); i++ )
    {
        if (strchr("AEILNORSTU",w[i]))
        {
            x = x + 1;
        }
        if (strchr("DG",w[i]))
        {
            x = x + 2;
        }
        if (strchr("BCMP",w[i]))
        {
            x = x + 3;
        }
        if (strchr("FHVWY",w[i]))
        {
            x = x + 4;
        }
        if (strchr("K",w[i]))
        {
            x = x + 5;
        }
        if (strchr("JX",w[i]))
        {
            x = x + 8;
        }
        if (strchr("QZ",w[i]))
        {
            x = x + 10;
        }
    }
    return x;
}



int check_bonus1(int p,char w[30],int x,int y,int d)
{
    if (d == 0)
    {  
        for(int j = y; j < y + (int)(strlen(w)); j++ )
        {   
            
            if( bonus_board[x][j] == 1)                            
            {

                p = p *2;
            } 
        }   
    }
    else
    {
        for(int i = x; i < x + (int)(strlen(w)); i++ )
        {
            if( bonus_board[i][y] == 1)                            
            {
                p = p *2;
            } 
        }
    }
    
    return p;
}

int check_bonus2(int p,char w[30],int x,int y,int d)
{
    if (d == 0)
    {  
        for(int j = y; j < y + (int)(strlen(w)); j++ )
        {   
            
            if( bonus_board[x][j] == 2)                            
            {
                
                p = p *3;
            } 
        }   
    }
    else
    {
        for(int i = x; i < x + (int)(strlen(w)); i++ )
        {
            if( bonus_board[i][y] == 2)                            
            {
                p = p *3;
            } 
        }
    }
    
    return p;
}

int count_all_score(char w[30], char xx[4],char yy[4],int x,int y,int d)
{
    int p = count_score(0,w);
    if(strstr(w,xx))
    {   
        p = check_bonus1(p,w,x,y,d);
    }
    if(strcmp(w + (strlen(w)-2),yy) == 0)
    {   
        p = check_bonus2(p,w,x,y,d);
    }
    return p;
}

int check_board(char gm[15][15],char w[20],int l,int x,int y)
{
    for (int i = x; i < 15; i++)
    {
        for (int j = y; j < 15; j++)
        {
            if(gm[i][j] == w[0])
            {   
                if( j + (int)strlen(w) - 1 < 15)
                {
                    int k = 0;
                    for (int a = j + 1; a < j + (int)strlen(w) ; a++)
                    {   
                        if( gm[i][a] != '.' )
                        {
                        k = 1;
                        break;
                        }
                    }
                    if (k == 0)
                    { 
                        return 100000 + i * 1000 + j *10;
                    }
                    
                }
                if( i + (int)strlen(w) -1 < 15)
                {
                    int k = 0;
                    for (int a = i +1 ; a < i + (int)strlen(w) ; a++)
                    {   
                        if( gm[a][j] != '.' )
                        {
                        k = 1;
                        break;
                        }
                    }
                        if (k == 0)
                    {
                        return 100001 + i *1000 + j *10;
                    }
                }
            }
        }
        y = 0;
    }
    return l;
}

void find_word(char gm[15][15],char a[20][NUM_WORDS],int n)
{
    char w[20]; 
    for (int i = 0; i < NUM_WORDS; i++)
    {
        int k = 0;
        for(int j = 0; j < n; j++) 
        {
            if (strcmp(words[i],a[j]) == 0)
            {
                k = 1;
                break;
            }
        }
        if (k == 0)
        {
            strcpy(w,words[i]);
            i = check_board(gm,w,i,0,0);
            
            wrt_word_i(gm,i,w);
        }
    }   
}



int optim_word(char gm[15][15],char a[100][100],int n,char xx[4],char yy[4])
{
    char w[20]; 
    int imax = -1,pmax = 0,c = 0,p;
    for (int i = 0; i < NUM_WORDS; i++)
    {   
        int k = -2; p = 0;
        for(int j = 0; j < n; j++) 
        {
            if (strcmp(words[i],a[j]) == 0)
            {
                k = 1;
                break;
            }
        }
        if (k == -2)
        {
            int x = 0,y = 0;
            while( k!= i)
            {   
                strcpy(w,words[i]);
                k = check_board(gm,w,i,x,y);
                if (k != i)
                {
                    p = count_all_score(w,xx,yy,k/1000%100,k/10%100,k%10);
                    x = k/1000%100;
                    y = k/10%100 + 1;
                }
                if(p > pmax)
                {
                    imax = i;
                    pmax = p;
                    c = k;    
                }
                else
                {
                    if(p == pmax && c/10 > k/10 && k >= 100000)
                    {
                        imax = i;
                        pmax = p;
                        c = k; 
                    }
                }
            }
        }
    }
    if(imax != -1)
    {   
        strcpy(a[n],words[imax]);
        wrt_word_i(gm,c,words[imax]);
    }
return pmax;
}

void main_game(char game_board[15][15])
{
    int n = 0,x,y,d,p1 = 0,p2 = 0;
    char xx[4],yy[4],w[30],a[100][NUM_WORDS];

    printf("Type double string:(XX)\n");
    fgets(xx,4,stdin);

    printf("Type triple string:(YY)\n");
    fgets(yy,4,stdin);

    printf("Type number of rounds:\n");
    fgets(w,30,stdin);
   
    xx[2] = 0;
    yy[2] = 0;
    
    while (strlen(w) > 1)
    {
       n = n*10 + w[0]-48;
       strcpy(w,w+1);
    }

    for (int k = 0; k < n; k++)
    {  
        char w[30];
        printf("Type word preceded by coordonates:(x,y,d)\n");
        fgets(w,30,stdin);
        split(w,&x,&y,&d);
        strcpy(a[2*k],w);

        wrt_word_d(game_board,x,y,d,w);
        
        p1 = p1 + count_all_score(w,xx,yy,x,y,d);
        p2 = p2 + optim_word(game_board,a,2 * k + 1,xx,yy);
        print_board(game_board);
        printf("Player1 = %d SCORE\nPlayer2 = %d SCORE\n",p1,p2);
    }
    
   
    
   if (p1 > p2)
   {
        printf("Player 1 Won!\n");
   }
   else
   {
        printf("Player 2 Won!\n");
   }

   
   
}

int main()
{
    char game_board[15][15],w[30];
    game_board_build(game_board);
    main_game(game_board);
        
    return 0;
}