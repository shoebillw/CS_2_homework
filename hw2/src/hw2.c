#include<stdio.h>
int main(void)
{
    printf("歡迎來到海戰棋\n");
    int board[2][8][8]={0};    
    int round=0,end=0;                                //甲玩家round==0 ,乙玩家round==1
    Print(round,board);
    Place(round,board,3);
    Place(round,board,2);
    Place(round,board,1);
    round=1;
    Print(round,board);
    Place(round,board,3);
    Place(round,board,2);
    Place(round,board,1);
    round=0;
    do
    {
        if(round==0) printf("甲玩家的回合\n");
        if(round==1) printf("乙玩家的回合\n");
        if(round==0) {round=1;}
        else if(round==1) {round=0;}
        Record(round,board);
        Atk(round,board);
        end=End(round,board);
    }while(end==0);
    if(round==0) printf("乙玩家獲勝\n");
    if(round==1) printf("甲玩家獲勝\n");
    return 0;   
}
int Atk(int round,int board[2][8][8])
{
    while(1)
    {
        int column, row, target, i, j, shipwreck;
        char input[4]={'\0'};
        printf("請輸入攻擊指令\n");
        scanf("%s",input);
        if(input[0]>='A' && input[0]<='G' && input[1]=='-' && input[2]>='1' && input[2]<='7' && input[3]=='\0')
        {
            column=input[2]-48;
            row=input[0]-64;
            if(board[round][row][column]==4 || board[round][row][column]==5)
            {
                printf("此區域已被轟炸過,請重新輸入\n");
                continue;
            }
            else if(board[round][row][column]>=1 && board[round][row][column]<=3)
            {
                target=board[round][row][column];                                   //target表示擊中的船種
                board[round][row][column]=4;
                shipwreck=1;                                                        //判斷是否沉船
                for(i=1;i<8;i++)
                {
                    for(j=1;j<8;j++)
                    {
                        if(board[round][i][j]==target)                               //擊中或擊沉:判斷場上還有沒有1
                        {
                            shipwreck=0;
                        }
                    }
                }
                if(shipwreck==1)
                {
                    if(target==1) printf("此次轟炸擊沉了驅逐艦\n\n"); 
                    if(target==2) printf("此次轟炸擊沉了巡洋艦\n\n"); 
                    if(target==3) printf("此次轟炸擊沉了戰艦\n\n"); 
                } 
                else if(shipwreck==0)
                {
                    if(target==1) printf("此次轟炸擊中了驅逐艦\n\n"); 
                    if(target==2) printf("此次轟炸擊中了巡洋艦\n\n"); 
                    if(target==3) printf("此次轟炸擊中了戰艦\n\n"); 
                }                       
            }
            else
            {
                board[round][row][column]=5; 
                printf("此次轟炸沒有擊中任何軍艦\n\n");
            }
        }
        else
        {
            printf("錯誤的指令,請重新輸入\n");
            continue;
        }
        break;
    }
    return 0;
}
int End(int round,int board[2][8][8])                                       //判斷是否結束:看場上還有沒有123
{
    int endd=1, i, j;
    for(i=1;i<8;i++)
    {
        for(j=1;j<8;j++)
        {
            if(board[round][i][j]>=1 && board[round][i][j]<=3) 
            {
                endd=0;
            }
        }
    }
    return endd;
}
int Record(int round,int board[2][8][8])                                     //print出紀錄棋盤畫面
{
    int i, j;
    char rowEng;
    rowEng='A';
    if(round==1) printf("甲玩家紀錄棋盤畫面如下\n 1234567\n");
    if(round==0) printf("乙玩家紀錄棋盤畫面如下\n 1234567\n");
    for(i=1;i<8;i++)
    {
        printf("%c",rowEng++);
        for(j=1;j<8;j++)
        {
            if(board[round][i][j]>=0 && board[round][i][j]<=3)                                  
            printf(".");
            else if(board[round][i][j]==4)                              //O代表擊中
            printf("O");
            else if(board[round][i][j]==5)                              //X代表未擊中
            printf("X");
        }
           printf("\n");
    }
    printf("\n");
    return 0;
}
int Print(int round,int board[2][8][8])                                     //print出軍艦棋盤畫面
{
    int i, j;
    char rowEng;
    rowEng='A';
    if(round==0) printf("甲玩家軍艦棋盤畫面如下\n 1234567\n");
    if(round==1) printf("乙玩家軍艦棋盤畫面如下\n 1234567\n");
    for(i=1;i<8;i++)
    {
        printf("%c",rowEng++);
        for(j=1;j<8;j++)
        {
            if(board[round][i][j]==0)                                   // ~ 代表海浪
            printf("~");
            else if(board[round][i][j]==3)                              //3代表戰艦 Battleship
            printf("B");
            else if(board[round][i][j]==2)                              //2代表巡洋艦 Cruiser
            printf("C");
            else if(board[round][i][j]==1)                              //1代表驅逐艦 Destroyer
            printf("D");
        }
           printf("\n");
    }
    printf("\n");
    return 0;
}
int Place(int round, int board[2][8][8], int ship)                                                                  //部署戰艦位置 
{
    while(1)
    {
        if(ship==3) printf("請輸入戰艦的部署指令\n");
        if(ship==2) printf("請輸入巡洋艦的部署指令\n");
        if(ship==1) printf("請輸入驅逐艦的部署指令\n");
        char cmd[8]={'\0'};                                                                                             //把指令歸零
        int vert, hori, row, column, i, overlap=0;
        scanf("%s",cmd);
        hori=(cmd[0]==cmd[4] && (cmd[6]-cmd[2]==ship || cmd[2]-cmd[6]==ship) && cmd[0]>='A' && cmd[0]<='G' &&                          //船是否放橫的
              cmd[2]>='1' && cmd[2]<='7' && cmd[6]>='1' && cmd[6]<='7' && cmd[1]==cmd[5] && cmd[1]=='-' && cmd[3]==',' && cmd[7]=='\0');
        vert=(cmd[2]==cmd[6] && (cmd[0]-cmd[4]==ship || cmd[4]-cmd[0]==ship) && cmd[0]>='A' && cmd[0]<='G' &&                          //船是否放直的
              cmd[4]>='A' && cmd[4]<='G' && cmd[6]>='1' && cmd[6]<='7' && cmd[1]==cmd[5] && cmd[1]=='-' && cmd[3]==',' && cmd[7]=='\0');
        if(hori)
        {
            row=cmd[0]-64;
            if(cmd[6]>cmd[2])
            column=cmd[2]-48;
            else
            column=cmd[6]-48;
            for(i=0;i<=ship;i++)
            {
                if(board[round][row][column+i]!=0)
                overlap=1;
            }
            if(overlap==0)                                  //判斷是否有擺放船隻重疊
            {
                for(i=0;i<=ship;i++)
                {
                    board[round][row][column+i]=ship;
                }
                Print(round,board);
            }
            else
            {
                printf("軍艦不可重疊,請重新輸入\n");
                continue;
            }
        }
        else if(vert)
        {
            column=cmd[2]-48;
            if(cmd[4]>cmd[0])
            row=cmd[0]-64;
            else
            row=cmd[4]-64;
            for(i=0;i<=ship;i++)
            {
                if(board[round][row+i][column]!=0)
                overlap=1;
            }
            if(overlap==0)                                                  //判斷是否有擺放船隻重疊
            {
                for(i=0;i<=ship;i++)
                {
                    board[round][row+i][column]=ship;
                }
                Print(round,board);
            }
            else
            {
                printf("軍艦不可重疊,請重新輸入\n");
                continue;
            }
        }
        else
        {
            printf("指令錯誤,請重新輸入\n");
            continue;
        }
        break;
    }
    return 0;
}