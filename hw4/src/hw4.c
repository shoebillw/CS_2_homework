#include<stdio.h>
int main(int argc, char *argv[])
{
    int i, j, k, a, b, row, column, size, mycolor, oppocolor, end=0, whichline=0;             //黃色是1 棕色是2
    int oppocanlinebackslash=0, oppocanlineslash=0, oppocanlinevert=0, oppocanlinehori=0;     
    int board[5][5][5]={0}, boardcolor[5][5]={0}, boardsize[5][5]={0}, chess[3][3]={0};
    FILE *fPtr;
    char data[500]={'\0'};
    fPtr=fopen(argv[1],"r");
    for(i=0;i<500;i++)                                          //讀檔
    {
        fscanf(fPtr , " %c " , &data[i]);
    }
    fclose(fPtr);
    fPtr=fopen(argv[3],"w");

    for(i=17;i<500;i++)                                         //分析檔案分類存入變數中
    {
        if(data[i]=='Y')                        //判斷我方顏色
        {
            mycolor=1;
            oppocolor=2;
            break;
        }
        else if(data[i]=='B')
        {
            mycolor=2;
            oppocolor=1;
            break;
        }
    }
    for(i=i+1;i<500;i++)
    {
        if(data[i]=='(')          
        {
            row=data[i+1]-48;
            column=data[i+3]-48;
            size=data[i+5]-48;
            board[row][column][size]=mycolor;            //存棋盤我方棋子   
        }
        else if(data[i]=='B' || data[i]=='Y')
        {
            break;
        }
    }
    for(i=i+1;i<500;i++)
    {
        if(data[i]=='(')
        {
            row=data[i+1]-48;
            column=data[i+3]-48;
            size=data[i+5]-48;
            board[row][column][size]=oppocolor;           //存棋盤對方棋子   
        }
        else if(data[i]=='B' || data[i]=='Y')
        {
            break;
        }
    }
    for(i=i+1;i<500;i++)
    {
        if(data[i]=='(')
        {
            chess[mycolor][0]=data[i+1]-48;                     //存手上還有多少棋子
            chess[mycolor][1]=data[i+3]-48;
            chess[mycolor][2]=data[i+5]-48;
            break;
        }
    }
    for(i=i+1;i<500;i++)
    {
        if(data[i]=='(')
        {
            chess[oppocolor][0]=data[i+1]-48;                   //存對方手上還有多少棋子
            chess[oppocolor][1]=data[i+3]-48;
            chess[oppocolor][2]=data[i+5]-48;
            break;
        }
    }
    for(i=1;i<5;i++)
    {
        for(j=1;j<5;j++)
        {
            for(k=4;k>0;k--)
            {
                if(board[i][j][k]!=0)
                {
                    boardcolor[i][j]=board[i][j][k];                //把棋盤分成顏色棋盤跟大小, 都只存該格最上方的棋子(肉眼看的到的)
                    boardsize[i][j]=k;
                    break;
                }
            }
        }
    }
   while(1)                                    //判斷對手有沒有快要連線的地方
    {
        //判斷左下到右上的斜線
        for(j=1;j<5;j++)                            
        {
            if(boardcolor[5-j][j]==oppocolor)
            {
                oppocanlineslash++;
            }
        }
        if(oppocanlineslash==3) break;;
        //判斷左上到右下的斜線
        for(j=1;j<5;j++)
        {
            if(boardcolor[j][j]==oppocolor)
            {
                oppocanlinebackslash++;
            }
        }
        if(oppocanlinebackslash==3) break;
        //判斷水平
        for(i=1;i<5;i++)
        {
            oppocanlinehori=0;
            for(j=1;j<5;j++)
            {
                if(boardcolor[i][j]==oppocolor)
                {
                    oppocanlinehori++;
                }
            }
            if(oppocanlinehori==3) 
            {
                whichline=i;
                break;
            }
        }
        //判斷垂直
        for(i=1;i<5;i++)
        {
            oppocanlinevert=0;
            for(j=1;j<5;j++)
            {
                if(boardcolor[j][i]==oppocolor)
                {
                    oppocanlinevert++;
                }
            }
            if(oppocanlinevert==3) 
            {
                whichline=i;
                break;
            }
        }
        break;
    }
    //如果對方快要連線就擋(看那排沒有)
    if(oppocanlinevert==3)                                      //(垂直)
    {
        for(j=1;j<5;j++)
        {
            if(boardsize[j][whichline]!=4)
            {
               break; 
            }
        }
        for(k=0;k<3;k++)
        {
            if(chess[mycolor][k]==4)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",j,whichline,4);
                return 0;
            }
            else
            {
               for(a=1;a<5;a++)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && a!=j && b!=whichline)
                        {
                            fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,whichline);
                            return 0;
                        }
                    }
                } 
            }
        }
    }
    else if(oppocanlinehori==3)                         //(水平)
    {
        for(j=1;j<5;j++)
        {
            if(boardsize[whichline][j]!=4)
            {
               break; 
            }
        }
        for(k=0;k<3;k++)
        {
            if(chess[mycolor][k]==4)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",whichline,j,4);
                return 0;
            }
            else
            {
               for(a=1;a<5;a++)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && a!=whichline && b!=j)
                        {
                            fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,whichline,j);
                            return 0;
                        }
                    }
                } 
            }
        }
    }
    else if(oppocanlineslash==3)                            //(右上到左下斜線)
    {
        for(j=1;j<5;j++)
        {
            if(boardsize[5-j][j]!=4)
            {
               break; 
            }
        }
        for(k=0;k<3;k++)
        {
            if(chess[mycolor][k]==4)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",5-j,j,4);
                return 0;
            }
            else
            {
               for(a=1;a<5;a++)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && a!=5-j && b!=j)
                        {
                            fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,5-j,j);
                            return 0;
                        }
                    }
                } 
            }
        }
    }
    else if(oppocanlinebackslash==3)            //(左上到右下斜線))
    {
        for(j=1;j<5;j++)
        {
            if(boardsize[j][j]!=4)
            {
               break; 
            }
        }
        for(k=0;k<3;k++)
        {
            if(chess[mycolor][k]==4)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",j,j,4);
                return 0;
            }
            else
            {
               for(a=1;a<5;a++)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && a!=j && b!=j)
                        {
                            fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,j);
                            return 0;
                        }
                    }
                } 
            }
        }
    }
    else                    //如果對方沒有快要連線, 就在空的地方擺棋子
    {
        for(i=0;i<3;i++)
        {
            if(chess[mycolor][i]!=0)
            {
                for(a=1;a<5;a++)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==0)
                        {
                            k=chess[mycolor][i];
                            fprintf(fPtr, "Put\n(%d,%d,%d)",a,b,k);
                            return 0;
                        }
                    }
                }
            } 
        }
    }
    fclose(fPtr);
    return 0;
}