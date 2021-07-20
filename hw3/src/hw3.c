#include<stdio.h>
int main(void)
{
    int i, j, player=1, chess;                                   //player=1黑色  player=2白色
    int board[4][9]={0};                                             //沒放東西就是0 黑色是1 黑色連線是11 白色是2 白色連線是12
    printf("歡迎來到九子棋\n");
    Print(board);
    for(chess=9;chess>0;chess--)                                   //放置階段
    {
        Place(1,board);
        Print(board);
        Place(2,board);
        Print(board);
    }   
    while(1)                                                        //移動階段
    {
        Move(1,board);
        Print(board);
        if(End(2,board)==1) 
        {
            printf("黑色方勝利\n");
            break;
        }
        Move(2,board);
        Print(board);
        if(End(1,board)==1)
        {
            printf("白色方勝利\n");
            break;
        }
    }
    return 0;
}

/////////////////////////////判斷有沒有棋子連成一條線///////////////////////////////////////////
int Line(int board[4][9])
{
    int i, line=0;
    for(i=1;i<4;i++)
    {
        if(board[i][1]%10==board[i][2]%10 && board[i][1]%10==board[i][3]%10 && board[i][1]!=0 
        && (board[i][1]/10==0 || board[i][2]/10==0 || board[i][3]/10==0))
        {
            board[i][1]=board[i][1]%10+10;
            board[i][2]=board[i][2]%10+10;                                  //如果連成一線就換數字
            board[i][3]=board[i][3]%10+10;
            line=1;
        }
        else if(board[i][3]%10==board[i][4]%10 && board[i][3]%10==board[i][5]%10 && board[i][3]!=0 
        && (board[i][3]/10==0 || board[i][4]/10==0 || board[i][5]/10==0))
        {
            board[i][3]=board[i][3]%10+10;
            board[i][4]=board[i][4]%10+10;
            board[i][5]=board[i][5]%10+10;
            line=1;
        }
        else if(board[i][5]%10==board[i][6]%10 && board[i][5]%10==board[i][7]%10 && board[i][5]!=0 
        && (board[i][5]/10==0 || board[i][6]/10==0 || board[i][7]/10==0))
        {
            board[i][5]=board[i][5]%10+10;
            board[i][6]=board[i][6]%10+10;
            board[i][7]=board[i][7]%10+10;
            line=1;
        }
        else if(board[i][7]%10==board[i][8]%10 && board[i][7]%10==board[i][1]%10 && board[i][7]!=0 
        && (board[i][7]/10==0 || board[i][8]/10==0 || board[i][1]/10==0))
        {
            board[i][7]=board[i][7]%10+10;
            board[i][8]=board[i][8]%10+10;
            board[i][1]=board[i][1]%10+10;
            line=1;
        }
    }
    for(i=2;i<=8;i++)
    {
        if(board[1][i]%10==board[2][i]%10 && board[1][i]%10==board[3][i]%10 && board[1][i]!=0 
        && (board[1][i]/10==0 || board[2][i]/10==0 || board[3][i]/10==0))
        {
            board[1][i]=board[1][i]%10+10;
            board[2][i]=board[2][i]%10+10;
            board[3][i]=board[3][i]%10+10;
            line=1;
        }
        i++;
    }
    return line;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////// 
/*****************************************PRINT出棋盤********************************************************/   
int Print(int board[4][9])
{
    int i, j;
    char Pboard[4][9];        //print board
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 9; j++)
        {
            if(board[i][j]==0)
            Pboard[i][j]=' ';
            if(board[i][j]==1 || board[i][j]==11)
            Pboard[i][j]='@';
            if(board[i][j]==2 || board[i][j]==12)
            Pboard[i][j]='O';
        } 
    }
    printf("\n當前棋盤狀態:\n");
    printf("%c-----%c-----%c\n",Pboard[1][1],Pboard[1][2],Pboard[1][3]);
    printf("|     |     |\n");
    printf("| %c---%c---%c |\n",Pboard[2][1],Pboard[2][2],Pboard[2][3]);
    printf("| |   |   | |\n");
    printf("| | %c-%c-%c | |\n",Pboard[3][1],Pboard[3][2],Pboard[3][3]);
    printf("| | |   | | |\n");
    printf("%c-%c-%c   %c-%c-%c\n",Pboard[1][8],Pboard[2][8],Pboard[3][8],Pboard[3][4],Pboard[2][4],Pboard[1][4]);
    printf("| | |   | | |\n");
    printf("| | %c-%c-%c | |\n",Pboard[3][7],Pboard[3][6],Pboard[3][5]);
    printf("| |   |   | |\n");
    printf("| %c---%c---%c |\n",Pboard[2][7],Pboard[2][6],Pboard[2][5]);
    printf("|     |     |\n");
    printf("%c-----%c-----%c\n",Pboard[1][7],Pboard[1][6],Pboard[1][5]);
    return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////放置棋子////////////////////////////////////////////
int Place(int player,int board[4][9])                                              
{
    while(1)
    {
        if(player==1) printf("\n黑方玩家放置棋子\n");
        if(player==2) printf("\n白方玩家放置棋子\n");
        int square, point;                                  //方框座標,節點座標
        char input[6];
        scanf("%s",input);
        if(input[0]=='m') 
        {
            printf("放置階段尚未結束,請勿輸入移動指令\n");
            continue;
        }
        else if(input[0]!='p' || input[1]!='-' || input[3]!='-' || input[5]!='\0')
        {
            printf("錯誤的放置指令格式,請重新輸入\n");
            continue;
        }
        else if(input[2]<=48 || input[2]>51 || input[4]<=48 || input[4]>56)
        {
            printf("輸入的座標不存在,請重新輸入\n");
            continue;
        }
        else
        {
            square=input[2]-48;
            point=input[4]-48;
            if(board[square][point]!=0)
            {
                printf("此座標點已有其他棋子,請重新輸入\n");
                continue;
            }
            else
            {
                board[square][point]=player;                        //放下後判斷有沒有連成一線
                if(Line(board)==1)
                {
                    if(player==1) Remove(2,board);
                    else if(player==2) Remove(1,board);
                }
            }
        }
        break;
    }
    return 0;
}
////////////////////////////////移動棋子/////////////////////////////////////////////////
int Move(int player,int board[4][9])
{
    while(1)
    {
        if(player==1) printf("\n黑方玩家移動棋子\n");
        if(player==2) printf("\n白方玩家移動棋子\n");
        int square, point, movesquare, movepoint, i, j;                                  //方框座標,節點座標
        char input[10];
        scanf("%s",input);
        if(input[0]!='m' || input[1]!='-' || input[3]!='-' || input[5]!=',' || input[7]!='-' || input[9]!='\0')
        {
            printf("錯誤的移動指令格式,請重新輸入\n");
            continue;
        }
        else if(input[2]<=48 || input[2]>51 || input[4]<=48 || input[4]>56 || input[6]<=48 || input[6]>51 || input[8]<=48 || input[8]>56)
        {
            printf("輸入的座標不存在,請重新輸入\n");
            continue;
        }
        else
        {
            square=input[2]-48;
            point=input[4]-48;
            movesquare=input[6]-48;
            movepoint=input[8]-48;
            if(board[square][point]==0)
            {
                printf("此座標點沒有棋子,請重新輸入\n");
                continue;
            }
            else if(board[square][point]%10!=player)
            {
                printf("此點為對方的棋子,不可移動,請重新輸入\n");
                continue;
            }
            else if(board[movesquare][movepoint]!=0)
            {
                printf("移動的目的地已有棋子,請重新輸入\n");
                continue;
            }
            else
            {   
                int end=0, remain=0;
                for(i=1;i<4;i++)
                {
                    for(j=1;j<9;j++)
                    {
                        if(board[i][j]%10==player)
                        {
                            remain++;
                        }
                    }
                }
                if(remain==3)
                {
                    board[square][point]=0;
                    board[movesquare][movepoint]=player;
                }
                else
                {
                    if(point==movepoint && point%2==0 &&( square-movesquare==1 || square-movesquare==-1))         //判斷能不能走
                    {
                        board[square][point]=0;
                        board[movesquare][movepoint]=player;
                    }
                    else if(square==movesquare &&( point-movepoint==1 || point-movepoint==-1 || point-movepoint==7 || point-movepoint==-7))
                    {
                        board[square][point]=0;
                        board[movesquare][movepoint]=player;
                    }
                    else 
                    {
                        printf("請照著棋盤直線移動,請重新輸入\n");
                        continue;
                    }
                    if(Line(board)==1)                                                      //移動後判斷有沒有連成一線
                    {
                        if(player==1) Remove(2,board);
                        else if(player==2) Remove(1,board);
                    }
                }   
            }
        }
        break;
    }
    return 0;
}
/////////////////////移除棋子//////////////////////////////////////
int Remove(int opposite,int board[4][9])
{
    while(1)
    {
        if(opposite==1) printf("\n連成一線,請移除一顆黑棋\n");
        if(opposite==2) printf("\n連成一線,請移除一顆白棋\n");
        int square, point, i, j, allline=0;                                  //方框座標,節點座標,allline全部都有連成一線
        char input[6];
        scanf("%s",input);
        if(input[0]!='r' || input[1]!='-' || input[3]!='-' || input[5]!='\0')
        {
            printf("錯誤的移除指令格式,請重新輸入\n");
            continue;
        }
        else if(input[2]<=48 || input[2]>51 || input[4]<=48 || input[4]>56)
        {
            printf("輸入的座標不存在,請重新輸入\n");
            continue;
        }
        else
        {
            square=input[2]-48;
            point=input[4]-48;
            if(board[square][point]==0)
            {
                printf("輸入的座標沒有棋子,請重新輸入\n");
                continue;
            }
            else if(board[square][point]%10!=opposite)
            {
                printf("輸入的座標上是己方的棋子,請重新輸入\n");
                continue;
            }
            else
            {
                for(i=0;i<4;i++)
                {
                    for(j=0;j<9;j++)
                    {
                        if(board[square][point]==opposite)
                        {
                            allline=0;
                        }
                    }
                }
                if(allline==1)
                {
                    board[square][point]=0;
                }
                else if(allline==0)
                {
                    if(board[square][point]==opposite)
                    {
                        board[square][point]=0;
                    }
                    else
                    {
                        printf("不可移除連成一線的棋子,請重新輸入\n");
                        continue;
                    }
                }
            }
        }
        break;
    }
    return 0;
}
///////////////////////////////判斷是否結束//////////////////////////////////
int End(int opposite,int board[4][9])
{
    int end=0, remain=0, i, j;
    for(i=0;i<4;i++)
    {
        for(j=0;j<9;j++)
        {
            if(board[i][j]%10==opposite)
            {
                remain++;
            }
        }
    }
    if(remain<3)
    {
        end=1;
    }
    return end;
}