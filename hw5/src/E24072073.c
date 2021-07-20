#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char *argv[])
{
    int i, j, k, a, b, row, column, size, mycolor, oppocolor, four=0, brk=0, end=0, horiwhichline=0, vertwhichline=0;             //黃色是1 棕色是2
    int oppocanlinebackslash=0, oppocanlineslash=0, oppocanlinevert=0, oppocanlinehori=0; 
    int icanlinebackslash=0, icanlineslash=0, icanlinevert=0, icanlinehori=0;     
    int board[5][5][5]={0}, boardcolor[5][5]={0}, boardsize[5][5]={0}, chess[3][3]={0}, underboardcolor[5][5]={0}, underboardsize[5][5]={0};
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
    for(i=i+1;i<500;i++)                                         //存棋盤我方棋子   
    {
        if(data[i]=='(')          
        {
            row=data[i+1]-48;
            column=data[i+3]-48;
            size=data[i+5]-48;
            board[row][column][size]=mycolor; 
        }
        else if(data[i]=='B' || data[i]=='Y')
        {
            break;
        }
    }
    for(i=i+1;i<500;i++)                                        //存棋盤對方棋子   
    {
        if(data[i]=='(')
        {
            row=data[i+1]-48;
            column=data[i+3]-48;
            size=data[i+5]-48;
            board[row][column][size]=oppocolor;
        }
        else if(data[i]=='B' || data[i]=='Y')
        {
            break;
        }
    }
    for(i=i+1;i<500;i++)                                          //存手上還有多少棋子
    {
        if(data[i]=='(')
        {
            chess[mycolor][0]=data[i+1]-48;  
            chess[mycolor][1]=data[i+3]-48;
            chess[mycolor][2]=data[i+5]-48;
            break;
        }
    }
    for(i=i+1;i<500;i++)                                          //存對方手上還有多少棋子
    {
        if(data[i]=='(')
        {
            chess[oppocolor][0]=data[i+1]-48;
            chess[oppocolor][1]=data[i+3]-48;
            chess[oppocolor][2]=data[i+5]-48;
            break;
        }
    }
    for(i=1;i<5;i++)                                               //把棋盤分成顏色棋盤跟大小, 都只存該格最上方的棋子(肉眼看的到的)
    {
        for(j=1;j<5;j++)
        {
            for(k=4;k>0;k--)
            {
                if(board[i][j][k]!=0)
                {
                    boardcolor[i][j]=board[i][j][k];
                    boardsize[i][j]=k;
                    break;
                }
            }
        }
    }
    
    ///////////////判斷自己有沒有快要連線的地方/////////////////////////
    //////////////////////////
    //////////進攻/////////////
    //////////////////////////                                
        for(j=1;j<5;j++)                                         //判斷斜線
        {
            if(boardcolor[5-j][j]==oppocolor && boardsize[5-j][j]==4)
            {
                icanlineslash=0;
                break;
            }
            if(boardcolor[5-j][j]==mycolor)
            {
                icanlineslash++;
            }
        }
    if(icanlineslash==3)                                         //(進攻斜線)
    {
        for(j=1;j<5;j++)
        {
            if(boardsize[5-j][j]!=4 && boardcolor[5-j][j]!=mycolor)
            {
               break; 
            }
        }
        for(k=0;k<3;k++)
        {
            if(j==5) break;
            if(boardsize[5-j][j]==0 && chess[mycolor][k]!=0)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",5-j,j,chess[mycolor][k]);
                return 0;
            }
            else
            {
               for(a=4;a>0;a--)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[5-j][j] && (a+b)!=5)
                        {
                            underchess(a,b,boardsize[a][b],5-j,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)!=4)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,5-j,j);
                                return 0;
                            }
                        }
                    }
                } 
            }
        }
    }
    
        for(j=1;j<5;j++)                                                  //判斷反斜線
        {
            if(boardcolor[j][j]==oppocolor && boardsize[j][j]==4)
            {
                icanlinebackslash=0;
                break;
            }
            if(boardcolor[j][j]==mycolor)
            {
                icanlinebackslash++;
            }
        }
    if(icanlinebackslash==3)                                          //(進攻反斜線))
    {
        for(j=1;j<5;j++)
        {
            if(boardsize[j][j]!=4 && boardcolor[j][j]!=mycolor)
            {
               break; 
            }
        }
        for(k=0;k<3;k++)
        {
            if(j==5) break;
            if(boardsize[j][j]==0 && chess[mycolor][k]!=0)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",j,j,chess[mycolor][k]);
                return 0;
            }
            else
            {
               for(a=1;a<5;a++)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[j][j] && a!=b)
                        {
                            underchess(a,b,boardsize[a][b],j,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)!=4)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,j);
                                return 0;
                            }
                        }
                    }
                } 
            }
        }
    }
    ////////////////////////////////////
        for(i=1;i<5;i++)                                           //判斷水平
        {
            icanlinehori=0;
            for(j=1;j<5;j++)
            {
                if(boardcolor[i][j]==oppocolor && boardsize[i][j]==4)
                {
                    icanlinehori=0;
                    break;
                }
                if(boardcolor[i][j]==mycolor)
                {
                    icanlinehori++;
                }
            }
            if(icanlinehori==3) 
            {
                horiwhichline=i;
                break;
            }
        }
    if(icanlinehori==3)                         //(水平)
    {
        for(j=1;j<5;j++)
        {
            if(boardsize[horiwhichline][j]!=4 && boardcolor[horiwhichline][j]!=mycolor)
            {
               break; 
            }
        }
        for(k=0;k<3;k++)
        {
            if(j==5) break;
            if(boardsize[horiwhichline][j]==0 && chess[mycolor][k]!=0)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",horiwhichline,j,chess[mycolor][k]);
                return 0;
            }
            else
            {
               for(a=4;a>0;a--)
                {
                    for(b=4;b>0;b--)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[horiwhichline][j] && a!=horiwhichline)
                        {
                            underchess(a,b,boardsize[a][b],horiwhichline,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)!=4)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,j);
                                return 0;
                            }
                        }
                    }
                } 
            }
        }
    }
        /////////////////////////////////
        for(i=1;i<5;i++)                                    //判斷垂直
        {
            icanlinevert=0;
            for(j=1;j<5;j++)
            {
                if(boardcolor[j][i]==oppocolor && boardsize[j][i]==4)
                {
                    icanlinevert=0;
                    break;
                }
                if(boardcolor[j][i]==mycolor)
                {
                    icanlinevert++;
                }
            }
            if(icanlinevert==3) 
            {
                vertwhichline=i;
                break;
            }
        }
    if(icanlinevert==3)                                      //(垂直)
    {
        for(j=4;j>0;j--)
        {
            if(boardsize[j][vertwhichline]!=4 && boardcolor[j][vertwhichline]!=mycolor)
            {
               break; 
            }
        }
        for(k=0;k<3;k++)
        {
            if(j==0) break;
            if(boardsize[j][vertwhichline]==0 && chess[mycolor][k]!=0)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",j,vertwhichline,chess[mycolor][k]);
                return 0;
            }
            else
            {
               
                for(b=4;b>0;b--)
                {
                    for(a=1;a<5;a++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[j][vertwhichline] && b!=vertwhichline)
                        {
                            underchess(a,b,boardsize[a][b],j,vertwhichline,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)!=4)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,vertwhichline);
                                return 0;
                            }
                        }
                    }
                } 
            }
        }
    }
    while(1)                                    //判斷對手有沒有快要連線的地方
    {
        //判斷左下到右上的斜線
        for(j=1;j<5;j++)                            
        {
            if(boardcolor[5-j][j]==mycolor && boardsize[5-j][j]==4)
            {
                oppocanlineslash=0;
                break;
            }
            if(boardcolor[5-j][j]==oppocolor)
            {
                oppocanlineslash++;
            }
        }
        if(oppocanlineslash==3) break;
        //判斷左上到右下的斜線
        for(j=1;j<5;j++)
        {
            if(boardcolor[j][j]==mycolor && boardsize[j][j]==4)
            {
                oppocanlinebackslash=0;
                break;
            }
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
                if(boardcolor[i][j]==mycolor && boardsize[i][j]==4)
                {
                    oppocanlinehori=0;
                    break;
                }
                if(boardcolor[i][j]==oppocolor)
                {
                    oppocanlinehori++;
                }
            }
            if(oppocanlinehori==3) 
            {
                horiwhichline=i;
                break;
            }
        }
        //判斷垂直
        for(i=1;i<5;i++)
        {
            oppocanlinevert=0;
            for(j=1;j<5;j++)
            {
                if(boardcolor[j][i]==mycolor && boardsize[j][i]==4)
                {
                    oppocanlinevert=0;
                    break;
                }
                if(boardcolor[j][i]==oppocolor)
                {
                    oppocanlinevert++;
                }
            }
            if(oppocanlinevert==3) 
            {
                vertwhichline=i;
                break;
            }
        }
        break;
    }
    
    ///////////////////////////////////////////////////
    ///////////////////////////防守////////////////////
    //////////////////////////////////////////////////

    if(oppocanlineslash==3)                                     ////////////////////////////////(斜線)
    {
        for(i=1;i<4;i++)
        {
            for(k=0;k<3;k++)
            {
                for(j=4;j>0;j--)
                {
                    if(chess[mycolor][k]==boardsize[5-j][j]+i && boardcolor[5-j][j]==oppocolor)
                    {
                        afterputchess(mycolor,chess[mycolor][k],5-j,j,board,underboardcolor,underboardsize);
                        if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                        {
                            fprintf(fPtr, "Put\n(%d,%d,%d)",5-j,j,chess[mycolor][k]);
                            return 0;
                        }
                    }
                }
            }
        }
        for(i=1;i<4;i++) 
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    for(j=4;j>0;j--)
                    {
                        if(boardsize[a][b]==boardsize[5-j][j]+i && boardcolor[a][b]==mycolor && boardcolor[5-j][j]==oppocolor && board[a][b][boardsize[a][b]-1]!=oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],5-j,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,5-j,j);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
        for(i=1;i<4;i++) 
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    for(j=4;j>0;j--)
                    {
                        if(boardsize[a][b]==boardsize[5-j][j]+i && boardcolor[a][b]==mycolor && boardcolor[5-j][j]==oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],5-j,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,5-j,j);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    
        ////如果那排有空格
        for(j=4;j>0;j--)
        {
            if(boardcolor[5-j][j]!=oppocolor)
            {
               break; 
            }
        }
        for(k=2;k>=0;k--)
        {
            if(j==0) break;
            if(chess[mycolor][k]==4)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",5-j,j,4);
                return 0;
            }
            else
            {
                for(b=4;b>0;b--)
                {
                    for(a=1;a<5;a++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && board[a][b][3]!=oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],5-j,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,5-j,j);
                                return 0;
                            }
                        }
                    }
                } 
                for(b=4;b>0;b--)
                {
                    for(a=1;a<5;a++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]==4)
                        {
                            underchess(a,b,boardsize[a][b],5-j,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,5-j,j);
                                return 0;
                            }
                        }
                    }
                } 
            }
        }
    }
    
    if(oppocanlinebackslash==3)                        ///////////////////////////////(防守反斜線)
    {
        for(i=1;i<4;i++)
        {
            for(k=0;k<3;k++)
            {
                for(j=4;j>0;j--)
                {
                    if(chess[mycolor][k]==boardsize[j][j]+i && boardcolor[j][j]==oppocolor)
                    {
                        afterputchess(mycolor,chess[mycolor][k],j,j,board,underboardcolor,underboardsize);
                        if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                        {
                            fprintf(fPtr, "Put\n(%d,%d,%d)",j,j,chess[mycolor][k]);
                            return 0;
                        }
                    }
                }
            }
        }
        for(i=1;i<4;i++) 
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    for(j=4;j>0;j--)
                    {
                        if(boardsize[a][b]==boardsize[j][j]+i && boardcolor[a][b]==mycolor && boardcolor[j][j]==oppocolor && board[a][b][boardsize[a][b]-1]!=oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],j,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,j);
                                return 0;
                            } 
                        }
                    }
                }
            }
        }
        for(i=1;i<4;i++) 
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    for(j=4;j>0;j--)
                    {
                        if(boardsize[a][b]==boardsize[j][j]+i && boardcolor[a][b]==mycolor && boardcolor[j][j]==oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],j,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,j);
                                return 0;
                            } 
                        }
                    }
                }
            }
        }
    
        ////如果那排有空格
        for(j=4;j>0;j--)
        {
            if(boardcolor[j][j]!=oppocolor)
            {
               break; 
            }
        }
        for(k=2;k>=0;k--)
        {
            if(j==0) break;
            if(chess[mycolor][k]==4)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",j,j,4);
                return 0;
            }
            else
            {
                for(b=4;b>0;b--)
                {
                    for(a=1;a<5;a++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && board[a][b][3]!=oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],j,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,j);
                                return 0;
                            }
                        }
                    }
                } 
                for(b=4;b>0;b--)
                {
                    for(a=1;a<5;a++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]==4)
                        {
                            underchess(a,b,boardsize[a][b],j,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,j);
                                return 0;
                            }
                        }
                    }
                } 
            }
        }
    }
    if(oppocanlinehori==3)                            /////////////////////////////////(防守水平)
    {
        //如果那排有敵人非4
        for(i=1;i<4;i++)
        {
            for(k=0;k<3;k++)
            {
                for(j=4;j>0;j--)
                {
                    if(chess[mycolor][k]==boardsize[horiwhichline][j]+i && boardcolor[horiwhichline][j]==oppocolor)
                    {
                        afterputchess(mycolor,chess[mycolor][k],horiwhichline,j,board,underboardcolor,underboardsize);
                        if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                        {
                            fprintf(fPtr, "Put\n(%d,%d,%d)",horiwhichline,j,chess[mycolor][k]);
                            return 0;
                        }
                    }
                }
            }
        }
        for(i=1;i<4;i++) 
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    for(j=4;j>0;j--)
                    {
                        if(boardsize[a][b]==boardsize[horiwhichline][j]+i && boardcolor[a][b]==mycolor && 
                           boardcolor[horiwhichline][j]==oppocolor && board[a][b][boardsize[a][b]-1]!=oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],horiwhichline,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,j);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
        for(i=1;i<4;i++) 
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    for(j=4;j>0;j--)
                    {
                        if(boardsize[a][b]==boardsize[horiwhichline][j]+i && boardcolor[a][b]==mycolor && boardcolor[horiwhichline][j]==oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],horiwhichline,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,j);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    
        ////如果那排有空格
        for(j=4;j>0;j--)
        {
            if(boardcolor[horiwhichline][j]!=oppocolor)
            {
               break; 
            }
        }
        for(k=2;k>=0;k--)
        {
            if(j==0) break;
            if(chess[mycolor][k]==4)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",horiwhichline,j,4);
                return 0;
            }
            else
            {
                for(b=4;b>0;b--)
                {
                    for(a=1;a<5;a++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && board[a][b][3]!=oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],horiwhichline,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,j);
                                return 0;
                            }
                        }
                    }
                } 
                for(b=4;b>0;b--)
                {
                    for(a=1;a<5;a++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]==4)
                        {
                            underchess(a,b,boardsize[a][b],horiwhichline,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,j);
                                return 0;
                            }
                        }
                    }
                } 
            }
        }
    }
    if(oppocanlinevert==3)                                                      //(防守垂直))
    {
        //如果那排有敵人非4
        for(i=1;i<4;i++)
        {
            for(k=0;k<3;k++)
            {
                for(j=4;j>0;j--)
                {
                    if(chess[mycolor][k]==boardsize[j][vertwhichline]+i && boardcolor[j][vertwhichline]==oppocolor)
                    {
                        afterputchess(mycolor,chess[mycolor][k],j,vertwhichline,board,underboardcolor,underboardsize);
                        if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                        {
                            fprintf(fPtr, "Put\n(%d,%d,%d)",j,vertwhichline,chess[mycolor][k]);
                            return 0;
                        }
                    }
                }
            }
        }
        for(i=1;i<4;i++) 
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    for(j=4;j>0;j--)
                    {
                        if(boardsize[a][b]==boardsize[j][vertwhichline]+i && boardcolor[a][b]==mycolor && 
                           boardcolor[j][vertwhichline]==oppocolor && board[a][b][boardsize[a][b]-1]!=oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],j,vertwhichline,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,vertwhichline);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
        for(i=1;i<4;i++) 
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    for(j=4;j>0;j--)
                    {
                        if(boardsize[a][b]==boardsize[j][vertwhichline]+i && boardcolor[a][b]==mycolor && boardcolor[j][vertwhichline]==oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],j,vertwhichline,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,vertwhichline);
                                return 0;
                            }
                        }
                    }
                }
            }
        }

        ////如果那排有空格
        for(j=4;j>0;j--)
        {
            if(boardcolor[j][vertwhichline]!=oppocolor)
            {
               break; 
            }
        }
        for(k=2;k>=0;k--)
        {
            if(j==0) break;
            if(chess[mycolor][k]==4)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",j,vertwhichline,4);
                return 0;
            }
            else
            {
                for(b=4;b>0;b--)
                {
                    for(a=1;a<5;a++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && board[a][b][3]!=oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],j,vertwhichline,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,vertwhichline);
                                return 0;
                            }
                        }
                    }
                } 
                for(b=4;b>0;b--)
                {
                    for(a=1;a<5;a++)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]==4)
                        {
                            underchess(a,b,boardsize[a][b],j,vertwhichline,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,vertwhichline);
                                return 0;
                            }
                        }
                    }
                } 
            }
        }
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////進攻2線/////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for(i=1;i<5;i++)                             ////////////////////判斷斜線加垂直
    {
        icanlinevert=0;   
        icanlineslash=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[j][i]==oppocolor && boardsize[j][i]==4) || (boardcolor[5-j][j]==oppocolor && boardsize[5-j][j]==4))
            {
                icanlineslash=0;
                icanlinevert=0;
                break;
            }
            if(boardcolor[j][i]==mycolor && j+i!=5)
            {
                icanlinevert++;
            }
            if(boardcolor[5-j][j]==mycolor && j!=i)
            {
                icanlineslash++;
            }
        }
        if(icanlinevert==2 && icanlineslash==2)
        {
            vertwhichline=i;
            break;
        }
    }

    if(icanlineslash==2 && icanlinevert==2)           //進攻斜線加垂直
    {
        printf("1");
        for(k=0;k<3;k++)
        {
            if(chess[mycolor][k]==4 && boardsize[5-vertwhichline][vertwhichline]==0)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",5-vertwhichline,vertwhichline,4);
                return 0;
            }
        }
        for(b=4;b>0;b--)
        {
            for(a=1;a<5;a++)
            {
                if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && b!=vertwhichline && a+b!=5)
                {
                    underchess(a,b,boardsize[a][b],5-vertwhichline,vertwhichline,board,underboardcolor,underboardsize);
                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                    {
                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,5-vertwhichline,vertwhichline);
                        return 0;
                    }
                }
            }
        }
    }
    ////////////////////////////////////////////
    for(i=1;i<5;i++)                                    ////////////////////判斷斜線加水平
    {
        icanlinehori=0;  
        icanlineslash=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[i][j]==oppocolor && boardsize[i][j]==4) || (boardcolor[j][5-j]==oppocolor && boardsize[j][5-j]==4))
            {
                icanlineslash=0;
                icanlinehori=0;
                break;
            }
            if(boardcolor[i][j]==mycolor && j+i!=5)
            {
                icanlinehori++;
            }
            if(boardcolor[j][5-j]==mycolor && j!=i)
            {
                icanlineslash++;
            }
        }
        if(icanlinehori==2 && icanlineslash==2)
        {
            horiwhichline=i;
            break;
        }
    }

    if(icanlineslash==2 && icanlinehori==2)           //進攻斜線加水平
    {
        printf("\n2");
        for(k=0;k<3;k++)
        {
            if(chess[mycolor][k]==4 && boardsize[horiwhichline][5-horiwhichline]==0)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",horiwhichline,5-horiwhichline,4);
                return 0;
            }
        }
        for(a=1;a<5;a++)
        {
            for(b=4;b>0;b--)
            {
                if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && a!=horiwhichline && a+b!=5)
                {
                    underchess(a,b,boardsize[a][b],horiwhichline,5-horiwhichline,board,underboardcolor,underboardsize);
                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                    {
                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,5-horiwhichline);
                        return 0;
                    }
                }
            }
        }
    }
    
    ////////////////////////////////////////////
    for(i=1;i<5;i++)                                   ////////////////////判斷進攻反斜線加垂直
    {
        icanlinevert=0;        
        icanlinebackslash=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[j][i]==oppocolor && boardsize[j][i]==4) || (boardcolor[j][j]==oppocolor && boardsize[j][j]==4))
            {
                icanlinebackslash=0;
                icanlinevert=0;
                break;
            }
            if(boardcolor[j][i]==mycolor && j!=i)
            {
                icanlinevert++;
            }
            if(boardcolor[j][j]==mycolor && j!=i)
            {
                icanlinebackslash++;
            }
        }
        if(icanlinevert==2 && icanlinebackslash==2)
        {
            vertwhichline=i;
            break;
        }
    }

    if(icanlinebackslash==2 && icanlinevert==2)           ////////////////////進攻反斜線加垂直
    {
        printf("3");
        for(k=0;k<3;k++)
        {
            if(chess[mycolor][k]==4 && boardsize[vertwhichline][vertwhichline]==0)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",vertwhichline,vertwhichline,4);
                return 0;
            }
        }
        for(b=4;b>0;b--)
        {
            for(a=1;a<5;a++)
            {
                if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && b!=vertwhichline && a!=b)
                {
                    underchess(a,b,boardsize[a][b],vertwhichline,vertwhichline,board,underboardcolor,underboardsize);
                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                    {
                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,vertwhichline,vertwhichline);
                        return 0;
                    }
                }
            }
        }
    }
    ////////////////////////////////////////////
    for(i=1;i<5;i++)                                        ////////////////////判斷進攻反斜線加水平
    {
        icanlinehori=0;        
        icanlinebackslash=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[i][j]==oppocolor && boardsize[i][j]==4) || (boardcolor[j][j]==oppocolor && boardsize[j][j]==4))
            {
                icanlinebackslash=0;
                icanlinehori=0;
                break;
            }
            if(boardcolor[i][j]==mycolor && j!=i)
            {
                icanlinehori++;
            }
            if(boardcolor[j][j]==mycolor && j!=i)
            {
                icanlinebackslash++;
            }
        }
        if(icanlinehori==2 && icanlinebackslash==2)
        {
            horiwhichline=i;
            break;
        }
    }

    if(icanlinebackslash==2 && icanlinehori==2)           ////////////////////進攻反斜線加水平
    {
        printf("4");
        for(k=0;k<3;k++)
        {
            if(chess[mycolor][k]==4 && boardsize[horiwhichline][horiwhichline]==0)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",horiwhichline,horiwhichline,4);
                return 0;
            }
        }
        for(a=1;a<5;a++)
        {
            for(b=4;b>0;b--)
            {
                if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && a!=horiwhichline && a!=b)
                {
                    underchess(a,b,boardsize[a][b],horiwhichline,horiwhichline,board,underboardcolor,underboardsize);
                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                    {
                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,horiwhichline);
                        return 0;
                    }
                }
            }
        }
    }
    ////////////////////////////////////////////
    brk=0;
    for(i=1;i<5;i++)                                      ////////////////////判斷進攻垂直加水平
    {
        if(brk==1) break;
        for(j=1;j<5;j++)
        {
            icanlinehori=0;     
            icanlinevert=0;
            for(k=1;k<5;k++)
            {
                if((boardcolor[i][k]==oppocolor && boardsize[i][k]==4) || (boardcolor[k][j]==oppocolor && boardsize[k][j]==4))
                {
                    icanlinevert=0;
                    icanlinehori=0;
                    break;
                }
                if(boardcolor[i][k]==mycolor && k!=j)
                {
                    icanlinehori++;
                }
                if(boardcolor[k][j]==mycolor && i!=k)
                {
                    icanlinevert++;
                }
            }
            if(icanlinehori==2 && icanlinevert==2)
            {
                horiwhichline=i;
                vertwhichline=j;
                brk=1;
                break;
            }
        }
        if(brk==1) break;
    }

    if(icanlinevert==2 && icanlinehori==2)           ////////////////////進攻垂直加水平
    {
        printf("5");
        for(k=0;k<3;k++)
        {
            if(chess[mycolor][k]==4 && boardsize[horiwhichline][vertwhichline]==0)
            {
                fprintf(fPtr, "Put\n(%d,%d,%d)",horiwhichline,vertwhichline,4);
                return 0;
            }
        }
        for(a=1;a<5;a++)
        {
            for(b=4;b>0;b--)
            {
                if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && a!=horiwhichline && b!=vertwhichline)
                {
                    underchess(a,b,boardsize[a][b],horiwhichline,vertwhichline,board,underboardcolor,underboardsize);
                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                    {
                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,vertwhichline);
                        return 0;
                    }
                }
            }
        }
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////防守2線/////////////////////////////////////////////////////////////////////////
    
    for(i=1;i<5;i++)                             ////////////////////判斷防守斜線加垂直
    {
        oppocanlinevert=0;   
        oppocanlineslash=0;
        four=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[j][i]==mycolor && boardsize[j][i]==4) || (boardcolor[5-j][j]==mycolor && boardsize[5-j][j]==4))
            {
                oppocanlineslash=0;
                oppocanlinevert=0;
                four=0;
                break;
            }
            if(boardcolor[j][i]==oppocolor && j+i!=5)
            {
                oppocanlinevert++;
                if(boardsize[j][i]==4)  four++;
            }
            if(boardcolor[5-j][j]==oppocolor && j!=i)
            {
                oppocanlineslash++;
                if(boardsize[5-j][j]==4)  four++;
            }
        }
        if(oppocanlinevert==2 && oppocanlineslash==2 && four!=3)
        {
            vertwhichline=i;
            break;
        }
    }
    if(oppocanlineslash==2 && oppocanlinevert==2 && four!=3)           //防守斜線加垂直
    {
        
        for(i=1;i<4;i++)                                //亂擋一個
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    for(j=1;j<5;j++)
                    {
                        if((boardsize[a][b]==boardsize[5-j][j]+i && boardcolor[a][b]==mycolor && boardcolor[5-j][j]==oppocolor) ||
                           (boardsize[a][b]==boardsize[j][vertwhichline]+i && boardcolor[a][b]==mycolor && boardcolor[j][vertwhichline]==oppocolor))
                        {
                            if(boardsize[a][b]==boardsize[5-j][j]+i && boardcolor[a][b]==mycolor && boardcolor[5-j][j]==oppocolor)
                            {
                                underchess(a,b,boardsize[a][b],5-j,j,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,5-j,j);
                                    return 0;
                                }
                            }
                            if(boardsize[a][b]==boardsize[j][vertwhichline]+i && boardcolor[a][b]==mycolor && boardcolor[j][vertwhichline]==oppocolor)
                            {
                                underchess(a,b,boardsize[a][b],j,vertwhichline,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,vertwhichline);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        for(i=3;i>0;i--)                            //4擺交集
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && boardsize[5-vertwhichline][vertwhichline]!=4 && board[a][b][i]!=oppocolor)
                    {
                        underchess(a,b,boardsize[a][b],5-vertwhichline,vertwhichline,board,underboardcolor,underboardsize);
                        if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                        {
                            fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,5-vertwhichline,vertwhichline);
                            return 0;
                        }
                    }
                }
            }
        }
        for(i=3;i>0;i--)                            //4擺其他格
        {
            for(j=4;j>0;j--)
            {
                if(boardcolor[5-j][j]==0 || boardcolor[j][vertwhichline]==0)
                {
                    for(b=4;b>0;b--)
                    {
                        for(a=1;a<5;a++)
                        {
                            if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && board[a][b][i]!=oppocolor)
                            {
                                if(boardcolor[5-j][j]==0)
                                {
                                    underchess(a,b,boardsize[a][b],5-j,j,board,underboardcolor,underboardsize);
                                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                    {
                                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,5-j,j);
                                        return 0;
                                    }
                                }
                                if(boardcolor[j][vertwhichline]==0)
                                {
                                    underchess(a,b,boardsize[a][b],j,vertwhichline,board,underboardcolor,underboardsize);
                                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                    {
                                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,vertwhichline);
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                } 
            }
        }
    }
    ////////////////////////////////////////////
    for(i=1;i<5;i++)                                    ////////////////////判斷防守斜線加水平
    {
        oppocanlinehori=0;  
        oppocanlineslash=0;
        four=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[i][j]==mycolor && boardsize[i][j]==4) || (boardcolor[j][5-j]==mycolor && boardsize[j][5-j]==4))
            {
                oppocanlineslash=0;
                oppocanlinehori=0;
                four=0;
                break;
            }
            if(boardcolor[i][j]==oppocolor && j+i!=5)
            {
                oppocanlinehori++;
                if(boardsize[i][j]==4)  four++;
            }
            if(boardcolor[j][5-j]==oppocolor && j!=i)
            {
                oppocanlineslash++;
                if(boardsize[j][5-j]==4)  four++;
            }
        }
        if(oppocanlinehori==2 && oppocanlineslash==2 && four!=3)
        {
            horiwhichline=i;
            break;
        }
    }

    if(oppocanlineslash==2 && oppocanlinehori==2 && four!=3)           //防守斜線加水平
    {
        for(i=1;i<4;i++)                                //亂擋一個
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    for(j=4;j>0;j--)
                    {
                        if((boardsize[a][b]==boardsize[horiwhichline][j]+i && boardcolor[a][b]==mycolor && boardcolor[horiwhichline][j]==oppocolor) ||
                           (boardsize[a][b]==boardsize[j][5-j]+i && boardcolor[a][b]==mycolor && boardcolor[j][5-j]==oppocolor))
                        {
                            if(boardsize[a][b]==boardsize[horiwhichline][j]+i && boardcolor[a][b]==mycolor && boardcolor[horiwhichline][j]==oppocolor)
                            {
                                underchess(a,b,boardsize[a][b],horiwhichline,j,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,j);
                                    return 0;
                                }
                            }
                            if(boardsize[a][b]==boardsize[j][5-j]+i && boardcolor[a][b]==mycolor && boardcolor[j][5-j]==oppocolor)
                            {
                                underchess(a,b,boardsize[a][b],j,5-j,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,5-j);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        for(i=3;i>0;i--)                            //4擺交集
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && boardsize[horiwhichline][5-horiwhichline]!=4 && board[a][b][i]!=oppocolor)
                    {
                        underchess(a,b,boardsize[a][b],horiwhichline,5-horiwhichline,board,underboardcolor,underboardsize);
                        if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                        {
                            fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,5-horiwhichline);
                            return 0;
                        }
                    }
                }
            }
        }
        for(i=3;i>0;i--)                            //4擺其他格
        {
            for(j=1;j<5;j++)
            {
                if(boardcolor[horiwhichline][j]==0 || boardcolor[j][5-j]==0)
                {
                    for(b=4;b>0;b--)
                    {
                        for(a=1;a<5;a++)
                        {
                            if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && board[a][b][i]!=oppocolor)
                            {
                                if(boardcolor[horiwhichline][j]==0)
                                {
                                    underchess(a,b,boardsize[a][b],horiwhichline,j,board,underboardcolor,underboardsize);
                                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                    {
                                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,j);
                                        return 0;
                                    }
                                }
                                if(boardcolor[j][5-j]==0)
                                {
                                    underchess(a,b,boardsize[a][b],j,5-j,board,underboardcolor,underboardsize);
                                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                    {
                                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,5-j);
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                } 
            }
        }
    }
    
    ////////////////////////////////////////////
    for(i=1;i<5;i++)                                   ////////////////////判斷防守反斜線加垂直
    {
        oppocanlinevert=0;        
        oppocanlinebackslash=0;
        four=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[j][i]==mycolor && boardsize[j][i]==4) || (boardcolor[j][j]==mycolor && boardsize[j][j]==4))
            {
                oppocanlinebackslash=0;
                oppocanlinevert=0;
                four=0;
                break;
            }
            if(boardcolor[j][i]==oppocolor && j!=i)
            {
                oppocanlinevert++;
                if(boardsize[j][i]==4)  four++;
            }
            if(boardcolor[j][j]==oppocolor && j!=i)
            {
                oppocanlinebackslash++;
                if(boardsize[j][j]==4)  four++;
            }
        }
        if(oppocanlinevert==2 && oppocanlinebackslash==2 && four!=3)
        {
            vertwhichline=i;
            break;
        }
    }
    
    if(oppocanlinebackslash==2 && oppocanlinevert==2 && four!=3)           ////////////////////防守反斜線加垂直
    {
        for(i=1;i<4;i++)                                //亂擋一個
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    for(j=4;j>0;j--)
                    {
                        if((boardsize[a][b]==boardsize[j][j]+i && boardcolor[a][b]==mycolor && boardcolor[j][j]==oppocolor) ||
                           (boardsize[a][b]==boardsize[j][vertwhichline]+i && boardcolor[a][b]==mycolor && boardcolor[j][vertwhichline]==oppocolor))
                        {
                            if(boardsize[a][b]==boardsize[j][j]+i && boardcolor[a][b]==mycolor && boardcolor[j][j]==oppocolor)
                            {
                                underchess(a,b,boardsize[a][b],j,j,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,j);
                                    return 0;
                                }
                            }
                            if(boardsize[a][b]==boardsize[j][vertwhichline]+i && boardcolor[a][b]==mycolor && boardcolor[j][vertwhichline]==oppocolor)
                            {
                                underchess(a,b,boardsize[a][b],j,vertwhichline,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,vertwhichline);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        for(i=3;i>0;i--)                            //4擺交集
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && boardsize[vertwhichline][vertwhichline]!=4 && board[a][b][i]!=oppocolor)
                    {
                        underchess(a,b,boardsize[a][b],vertwhichline,vertwhichline,board,underboardcolor,underboardsize);
                        if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                        {
                            fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,vertwhichline,vertwhichline);
                            return 0;
                        }
                    }
                }
            }
        }
        for(i=3;i>0;i--)                            //4擺其他格
        {
            for(j=1;j<5;j++)
            {
                if(boardcolor[j][j]==0 || boardcolor[j][vertwhichline]==0)
                {
                    for(b=4;b>0;b--)
                    {
                        for(a=1;a<5;a++)
                        {
                            if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && board[a][b][i]!=oppocolor)
                            {
                                if(boardcolor[j][j]==0)
                                {
                                    underchess(a,b,boardsize[a][b],j,j,board,underboardcolor,underboardsize);
                                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                    {
                                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,j);
                                        return 0;
                                    }
                                }
                                if(boardcolor[j][vertwhichline]==0)
                                {
                                    underchess(a,b,boardsize[a][b],j,vertwhichline,board,underboardcolor,underboardsize);
                                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                    {
                                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,vertwhichline);
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                } 
            }
        }
    }
    ////////////////////////////////////////////
    for(i=1;i<5;i++)                                        ////////////////////判斷防守反斜線加水平
    {
        oppocanlinehori=0;        
        oppocanlinebackslash=0;
        four=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[i][j]==mycolor && boardsize[i][j]==4) || (boardcolor[j][j]==mycolor && boardsize[j][j]==4))
            {
                oppocanlinebackslash=0;
                oppocanlinehori=0;
                four=0;
                break;
            }
            if(boardcolor[i][j]==oppocolor && j!=i)
            {
                oppocanlinehori++;
                if(boardsize[i][j]==4)  four++;
            }
            if(boardcolor[j][j]==oppocolor && j!=i)
            {
                oppocanlinebackslash++;
                if(boardsize[j][j]==4)  four++;
            }
        }
        if(oppocanlinehori==2 && oppocanlinebackslash==2 && four!=3)
        {
            horiwhichline=i;
            break;
        }
    }

    if(oppocanlinebackslash==2 && oppocanlinehori==2 && four!=3)           ////////////////////防守反斜線加水平
    {
        for(i=1;i<4;i++)                                //亂擋一個
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    for(j=4;j>0;j--)
                    {
                        if((boardsize[a][b]==boardsize[horiwhichline][j]+i && boardcolor[a][b]==mycolor && boardcolor[horiwhichline][j]==oppocolor) ||
                           (boardsize[a][b]==boardsize[j][j]+i && boardcolor[a][b]==mycolor && boardcolor[j][j]==oppocolor))
                        {
                            if(boardsize[a][b]==boardsize[horiwhichline][j]+i && boardcolor[a][b]==mycolor && boardcolor[horiwhichline][j]==oppocolor)
                            {
                                underchess(a,b,boardsize[a][b],horiwhichline,j,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,j);
                                    return 0;
                                }
                            }
                            if(boardsize[a][b]==boardsize[j][j]+i && boardcolor[a][b]==mycolor && boardcolor[j][j]==oppocolor)
                            {
                                underchess(a,b,boardsize[a][b],j,j,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,j);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        for(i=3;i>0;i--)                            //4擺交集
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && boardsize[horiwhichline][horiwhichline]!=4 && board[a][b][i]!=oppocolor)
                    {
                        underchess(a,b,boardsize[a][b],horiwhichline,horiwhichline,board,underboardcolor,underboardsize);
                        if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                        {
                            fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,horiwhichline);
                            return 0;
                        }
                    }
                }
            }
        }
        for(i=3;i>0;i--)                            //4擺其他格
        {
            for(j=1;j<5;j++)
            {
                if(boardcolor[horiwhichline][j]==0 || boardcolor[j][j]==0)
                {
                    for(b=4;b>0;b--)
                    {
                        for(a=1;a<5;a++)
                        {
                            if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && board[a][b][i]!=oppocolor)
                            {
                                if(boardcolor[horiwhichline][j]==0)
                                {
                                    underchess(a,b,boardsize[a][b],horiwhichline,j,board,underboardcolor,underboardsize);
                                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                    {
                                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,j);
                                        return 0;
                                    }
                                }
                                if(boardcolor[j][j]==0)
                                {
                                    underchess(a,b,boardsize[a][b],j,j,board,underboardcolor,underboardsize);
                                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                    {
                                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,j);
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                } 
            }
        }
    }
    ////////////////////////////////////////////
    brk=0;
    for(i=1;i<5;i++)                                      ////////////////////判斷防守垂直加水平
    {
        if(brk==1) break;
        for(j=1;j<5;j++)
        {
            oppocanlinehori=0;     
            oppocanlinevert=0;
            four=0;
            for(k=1;k<5;k++)
            {
                if((boardcolor[i][k]==mycolor && boardsize[i][k]==4) || (boardcolor[k][j]==mycolor && boardsize[k][j]==4))
                {
                    oppocanlinevert=0;
                    oppocanlinehori=0;
                    four=0;
                    break;
                }
                if(boardcolor[i][k]==oppocolor && k!=j)
                {
                    oppocanlinehori++;
                    if(boardsize[i][k]==4)  four++;
                }
                if(boardcolor[k][j]==oppocolor && i!=k)
                {
                    oppocanlinevert++;
                    if(boardsize[k][j]==4)  four++;
                }
            }
            if(oppocanlinehori==2 && oppocanlinevert==2 && four!=3)
            {
                horiwhichline=i;
                vertwhichline=j;
                brk=1;
                break;
            }
        }
        if(brk==1) break;
    }

    if(oppocanlinevert==2 && oppocanlinehori==2 && four!=3)           ////////////////////防守垂直加水平
    {
        for(i=1;i<4;i++)                                //亂擋一個
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    for(j=4;j>0;j--)
                    {
                        if((boardsize[a][b]==boardsize[horiwhichline][j]+i && boardcolor[a][b]==mycolor && boardcolor[horiwhichline][j]==oppocolor) ||
                           (boardsize[a][b]==boardsize[j][vertwhichline]+i && boardcolor[a][b]==mycolor && boardcolor[j][vertwhichline]==oppocolor))
                        {
                            if(boardsize[a][b]==boardsize[horiwhichline][j]+i && boardcolor[a][b]==mycolor && boardcolor[horiwhichline][j]==oppocolor)
                            {
                                underchess(a,b,boardsize[a][b],horiwhichline,j,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,j);
                                    return 0;
                                }
                            }
                            else if(boardsize[a][b]==boardsize[j][vertwhichline]+i && boardcolor[a][b]==mycolor && boardcolor[j][vertwhichline]==oppocolor)
                            {
                                underchess(a,b,boardsize[a][b],j,vertwhichline,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,vertwhichline);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        for(i=3;i>0;i--)                            //4擺交集
        {
            for(b=4;b>0;b--)
            {
                for(a=1;a<5;a++)
                {
                    if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && boardsize[horiwhichline][vertwhichline]!=4 && board[a][b][i]!=oppocolor)
                    {
                        underchess(a,b,boardsize[a][b],horiwhichline,vertwhichline,board,underboardcolor,underboardsize);
                        if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                        {
                            fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,vertwhichline);
                            return 0;
                        }
                    }
                }
            }
        }
        for(i=3;i>0;i--)                            //4擺其他格
        {
            for(j=1;j<5;j++)
            {
                if(boardcolor[horiwhichline][j]==0 || boardcolor[j][vertwhichline]==0)
                {
                    for(b=4;b>0;b--)
                    {
                        for(a=1;a<5;a++)
                        {
                            if(boardcolor[a][b]==mycolor && boardsize[a][b]==4 && board[a][b][i]!=oppocolor)
                            {
                                if(boardcolor[horiwhichline][j]==0)
                                {
                                    underchess(a,b,boardsize[a][b],horiwhichline,j,board,underboardcolor,underboardsize);
                                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                    {
                                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,j);
                                        return 0;
                                    }
                                }
                                if(boardcolor[j][vertwhichline]==0)
                                {
                                    underchess(a,b,boardsize[a][b],j,vertwhichline,board,underboardcolor,underboardsize);
                                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                    {
                                        fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,vertwhichline);
                                        return 0;
                                    }
                                }
                            }
                        }
                    }
                } 
            }
        }
    }
    ///////////////////////////擋連線但有我的4的/////////////////////////////////////////////////////////////////////////
    oppocanlineslash=0;
    oppocanlinebackslash=0;
    oppocanlinevert=0;
    oppocanlinehori=0;
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
        if(oppocanlineslash==3) break;
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
                horiwhichline=i;
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
                vertwhichline=i;
                break;
            }
        }
        break;
    }
    if(oppocanlineslash==3)                                     ////////////////////////////////(斜線)
    {
        for(k=0;k<3;k++)
        {
            for(j=1;j<5;j++)
            {
                if(chess[mycolor][k]==boardsize[5-j][j]+1 && boardcolor[5-j][j]==oppocolor)
                {
                    afterputchess(mycolor,chess[mycolor][k],5-j,j,board,underboardcolor,underboardsize);
                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",5-j,j,chess[mycolor][k]);
                        return 0;
                    }
                }
            }
        }
    }
    if(oppocanlinebackslash==3)                                     ////////////////////////////////(反斜線)
    {
        for(k=0;k<3;k++)
        {
            for(j=4;j>0;j--)
            {
                if(chess[mycolor][k]==boardsize[j][j]+1 && boardcolor[j][j]==oppocolor)
                {
                    afterputchess(mycolor,chess[mycolor][k],j,j,board,underboardcolor,underboardsize);
                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",j,j,chess[mycolor][k]);
                        return 0;
                    }
                }
            }
        }
    }
    if(oppocanlinevert==3)                                     ////////////////////////////////(垂直)
    {
        for(k=0;k<3;k++)
        {
            for(j=4;j>0;j--)
            {
                if(chess[mycolor][k]==boardsize[j][vertwhichline]+1 && boardcolor[j][vertwhichline]==oppocolor)
                {
                    afterputchess(mycolor,chess[mycolor][k],j,vertwhichline,board,underboardcolor,underboardsize);
                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",j,vertwhichline,chess[mycolor][k]);
                        return 0;
                    }
                }
            }
        }
    }
    if(oppocanlinehori==3)                                     ////////////////////////////////(水平)
    {
        for(k=0;k<3;k++)
        {
            for(j=4;j>0;j--)
            {
                if(chess[mycolor][k]==boardsize[horiwhichline][j]+1 && boardcolor[horiwhichline][j]==oppocolor)
                {
                    afterputchess(mycolor,chess[mycolor][k],horiwhichline,j,board,underboardcolor,underboardsize);
                    if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",horiwhichline,j,chess[mycolor][k]);
                        return 0;
                    }
                }
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    for(i=4;i>0;i--)                            //3蓋2
    {
        for(j=1;j<5;j++)
        {
            if(boardcolor[i][j]==oppocolor && boardsize[i][j]==2)
            {
                for(a=1;a<5;a++)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==mycolor &&  boardsize[a][b]==3
                        && board[a][b][boardsize[a][b]-1]!=oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],i,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,j);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    for(i=4;i>0;i--)                            //4蓋3
    {
        for(j=1;j<5;j++)
        {
            if(boardcolor[i][j]==oppocolor && boardsize[i][j]==3)
            {
                for(a=1;a<5;a++)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==mycolor &&  boardsize[a][b]==4
                        && board[a][b][boardsize[a][b]-1]!=oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],i,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,j);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    
    
    ///////////////創造2線/////////////////
    //////////////////////////////////////
    for(i=1;i<5;i++)                             ////////////////////判斷斜線加垂直=3
    {
        icanlinevert=0;   
        icanlineslash=0;
        four=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[j][i]==oppocolor && boardsize[j][i]==4) || (boardcolor[5-j][j]==oppocolor && boardsize[5-j][j]==4))
            {
                icanlineslash=0;
                icanlinevert=0;
                break;
            }
            if(boardcolor[j][i]==mycolor && j+i!=5)
            {
                icanlinevert++;
                if(boardsize[j][i]==4)  four++;
            }
            if(boardcolor[5-j][j]==mycolor && j!=i)
            {
                icanlineslash++;
                if(boardsize[5-j][j]==4)  four++;
            }
        }
        if(icanlinevert+icanlineslash==3 && four!=3)
        {
            vertwhichline=i;
            break;
        }
    }

    if(icanlinevert==1 && icanlineslash==2 && four!=3)                                       //創造斜線加垂直(垂直)
    {
        for(i=1;i<5;i++)
        {
            if(boardcolor[i][vertwhichline]!=mycolor && i+vertwhichline!=5)
            {
                for(k=2;k>=0;k--)
                {
                    if(chess[mycolor][k]!=0 && boardcolor[i][vertwhichline]==0 && !(four==2 && chess[mycolor][k]==4))
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",i,vertwhichline,chess[mycolor][k]);
                        return 0;
                    }
                }
                for(b=4;b>0;b--)
                {
                    for(a=4;a>0;a--)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[i][vertwhichline] && b!=vertwhichline && a+b!=5 && !(four==2 && boardsize[a][b]==4))
                        {
                            underchess(a,b,boardsize[a][b],i,vertwhichline,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                printf("2");
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,vertwhichline);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
        
    }
    if(icanlineslash==1 && icanlinevert==2 && four!=3)                                       //創造斜線加垂直(斜線)
    {
        
        for(i=4;i>0;i--)
        {
            if(boardcolor[5-i][i]!=mycolor && i!=vertwhichline)
            {
                for(k=2;k>=0;k--)
                {
                    if(chess[mycolor][k]!=0 && boardcolor[5-i][i]==0 && !(four==2 && chess[mycolor][k]==4))
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",5-i,i,chess[mycolor][k]);
                        return 0;
                    }
                }
                for(b=4;b>0;b--)
                {
                    for(a=4;a>0;a--)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[5-i][i] && b!=vertwhichline && a+b!=5 && !(four==2 && boardsize[a][b]==4))
                        {
                            underchess(a,b,boardsize[a][b],5-i,i,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,5-i,i);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    ////////////////////////////////////////////
    for(i=1;i<5;i++)                                    ////////////////////判斷斜線加水平=3
    {
        icanlinehori=0;  
        icanlineslash=0;
        four=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[i][j]==oppocolor && boardsize[i][j]==4) || (boardcolor[j][5-j]==oppocolor && boardsize[j][5-j]==4))
            {
                icanlineslash=0;
                icanlinehori=0;
                break;
            }
            if(boardcolor[i][j]==mycolor && j+i!=5)
            {
                icanlinehori++;
                if(boardsize[i][j]==4)  four++;
            }
            if(boardcolor[j][5-j]==mycolor && j!=i)
            {
                icanlineslash++;
                if(boardsize[j][5-j]==4)  four++;
            }
        }
        if(icanlinehori+icanlineslash==3 && four!=3)
        {
            horiwhichline=i;
            break;
        }
    }

    if(icanlinehori==1 && icanlineslash==2 && four!=3)                                           //創造斜線加水平(水平)
    {
        for(i=1;i<5;i++)
        {
            if(boardcolor[horiwhichline][i]!=mycolor && i+horiwhichline!=5)
            {
                for(k=2;k>=0;k--)
                {
                    if(chess[mycolor][k]!=0 && boardcolor[horiwhichline][i]==0 && !(four==2 && chess[mycolor][k]==4))
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",horiwhichline,i,chess[mycolor][k]);
                        return 0;
                    }
                }
                for(b=4;b>0;b--)
                {
                    for(a=4;a>0;a--)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[horiwhichline][i] && a!=horiwhichline && a+b!=5 && !(four==2 && boardsize[a][b]==4))
                        {
                            underchess(a,b,boardsize[a][b],horiwhichline,i,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,i);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }

    if(icanlineslash==1 && icanlinehori==2 && four!=3)                                          //創造斜線加水平(斜線)
    {
        for(i=4;i>0;i--)
        {
            if(boardcolor[i][5-i]!=mycolor && i!=horiwhichline)
            {
                for(k=2;k>=0;k--)
                {
                    if(chess[mycolor][k]!=0 && boardcolor[i][5-i]==0 && !(four==2 && chess[mycolor][k]==4))
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",i,5-i,chess[mycolor][k]);
                        return 0;
                    }
                }
                for(b=4;b>0;b--)
                {
                    for(a=4;a>0;a--)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[i][5-i] && a!=horiwhichline && a+b!=5 && !(four==2 && boardsize[a][b]==4))
                        {
                            underchess(a,b,boardsize[a][b],i,5-i,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,5-i);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    
    for(i=1;i<5;i++)                             ////////////////////判斷反斜線加垂直=3
    {
        icanlinevert=0;   
        icanlinebackslash=0;
        four=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[j][i]==oppocolor && boardsize[j][i]==4) || (boardcolor[j][j]==oppocolor && boardsize[j][j]==4))
            {
                icanlinebackslash=0;
                icanlinevert=0;
                break;
            }
            if(boardcolor[j][i]==mycolor && j!=i)
            {
                icanlinevert++;
                if(boardsize[j][i]==4)  four++;
            }
            if(boardcolor[j][j]==mycolor && j!=i)
            {
                icanlinebackslash++;
                if(boardsize[j][j]==4)  four++;
            }
        }
        if(icanlinevert+icanlinebackslash==3 && four!=3)
        {
            vertwhichline=i;
            break;
        }
    }

    if(icanlinevert==1 && icanlinebackslash==2 && four!=3)                                             //創造反斜線加垂直(垂直)
    {
        for(i=1;i<5;i++)
        {
            if(boardcolor[i][vertwhichline]!=mycolor && i!=vertwhichline)
            {
                for(k=2;k>=0;k--)
                {
                    if(chess[mycolor][k]!=0 && boardcolor[i][vertwhichline]==0 && !(four==2 && chess[mycolor][k]==4))
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",i,vertwhichline,chess[mycolor][k]);
                        return 0;
                    }
                }
                for(b=4;b>0;b--)
                {
                    for(a=4;a>0;a--)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[i][vertwhichline] && b!=vertwhichline && a!=b && !(four==2 && boardsize[a][b]==4))
                        {
                            underchess(a,b,boardsize[a][b],i,vertwhichline,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,vertwhichline);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    if(icanlinebackslash==1 && icanlinevert==2 && four!=3)                                          //創造反斜線加垂直(反斜線)
    {
        for(i=4;i>0;i--)
        {
            if(boardcolor[i][i]!=mycolor && i!=vertwhichline)
            {
                for(k=2;k>=0;k--)
                {
                    if(chess[mycolor][k]!=0 && boardcolor[i][i]==0 && !(four==2 && chess[mycolor][k]==4))
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",i,i,chess[mycolor][k]);
                        return 0;
                    }
                }
                for(b=4;b>0;b--)
                {
                    for(a=4;a>0;a--)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[i][i] && b!=vertwhichline && a!=b && !(four==2 && boardsize[a][b]==4))
                        {
                            underchess(a,b,boardsize[a][b],i,i,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,i);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    ////////////////////////////////////////////
    for(i=1;i<5;i++)                                    ////////////////////判斷反斜線加水平=3
    {
        icanlinehori=0;  
        icanlinebackslash=0;
        four=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[i][j]==oppocolor && boardsize[i][j]==4) || (boardcolor[j][j]==oppocolor && boardsize[j][j]==4))
            {
                icanlinebackslash=0;
                icanlinehori=0;
                break;
            }
            if(boardcolor[i][j]==mycolor && j!=i)
            {
                icanlinehori++;
                if(boardsize[i][j]==4)  four++;
            }
            if(boardcolor[j][j]==mycolor && j!=i)
            {
                icanlinebackslash++;
                if(boardsize[j][j]==4)  four++;
            }
        }
        if(icanlinehori+icanlinebackslash==3 && four!=3)
        {
            horiwhichline=i;
            break;
        }
    }

    if(icanlinehori==1 && icanlinebackslash==2 && four!=3)                                               //創造反斜線加水平(水平)
    {
        for(i=1;i<5;i++)
        {
            if(boardcolor[horiwhichline][i]!=mycolor && i!=horiwhichline)
            {
                for(k=2;k>=0;k--)
                {
                    if(chess[mycolor][k]!=0 && boardcolor[horiwhichline][i]==0 && !(four==2 && chess[mycolor][k]==4))
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",horiwhichline,i,chess[mycolor][k]);
                        return 0;
                    }
                }
                for(b=4;b>0;b--)
                {
                    for(a=4;a>0;a--)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[horiwhichline][i] && a!=horiwhichline && a!=b && !(four==2 && boardsize[a][b]==4))
                        {
                            underchess(a,b,boardsize[a][b],horiwhichline,i,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,i);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }

    if(icanlinebackslash==1 && icanlinehori==2 && four!=3)                                        //創造反斜線加水平(反斜線)
    {
        for(i=1;i<5;i++)
        {
            if(boardcolor[i][i]!=mycolor && i!=horiwhichline)
            {
                for(k=2;k>=0;k--)
                {
                    if(chess[mycolor][k]!=0 && boardcolor[i][i]==0 && !(four==2 && chess[mycolor][k]==4))
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",i,i,chess[mycolor][k]);
                        return 0;
                    }
                }
                for(b=4;b>0;b--)
                {
                    for(a=4;a>0;a--)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[i][i] && a!=horiwhichline && a!=b && !(four==2 && boardsize[a][b]==4))
                        {
                            underchess(a,b,boardsize[a][b],i,i,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,i);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    ////////////////////////////////////////////
    brk=0;
    for(i=1;i<5;i++)                                    ////////////////////判斷垂直加水平=3
    {
        if(brk==1) break;
        for(j=1;j<5;j++)
        {
            icanlinehori=0;  
            icanlinevert=0;
            four=0;
            for(k=1;k<5;k++)
            {
                if((boardcolor[i][k]==oppocolor && boardsize[i][k]==4) || (boardcolor[k][j]==oppocolor && boardsize[k][j]==4))
                {
                    icanlinevert=0;
                    icanlinehori=0;
                    break;
                }
                if(boardcolor[i][k]==mycolor && j!=k)
                {
                    icanlinehori++;
                    if(boardsize[i][k]==4)  four++;
                }
                if(boardcolor[k][j]==mycolor && k!=i)
                {
                    icanlinevert++;
                    if(boardsize[k][j]==4)  four++;
                }
            }
            if(icanlinehori+icanlinevert==3 && four!=3)
            {
                horiwhichline=i;
                vertwhichline=j;
                brk=1;
                break;
            }
        } 
        if(brk==1) break;
    }

    if(icanlinehori==1 && icanlinevert==2 && four!=3)                                                      //創造垂直加水平(水平)
    {
        for(i=1;i<5;i++)
        {
            if(boardcolor[horiwhichline][i]!=mycolor && i!=vertwhichline)
            {
                for(k=2;k>=0;k--)
                {
                    if(chess[mycolor][k]!=0 && boardcolor[horiwhichline][i]==0 && !(four==2 && chess[mycolor][k]==4))
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",horiwhichline,i,chess[mycolor][k]);
                        return 0;
                    }
                }
                for(b=4;b>0;b--)
                {
                    for(a=4;a>0;a--)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[horiwhichline][i] 
                        && a!=horiwhichline && b!=vertwhichline && !(four==2 && boardsize[a][b]==4))
                        {
                            underchess(a,b,boardsize[a][b],horiwhichline,i,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,i);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }

    if(icanlinevert==1 && icanlinehori==2 && four!=3)                                                 //創造垂直加水平(垂直)
    {
        for(i=1;i<5;i++)
        {
            if(boardcolor[i][vertwhichline]!=mycolor && i!=horiwhichline)
            {
                for(k=2;k>=0;k--)
                {
                    if(chess[mycolor][k]!=0 && boardcolor[i][vertwhichline]==0 && !(four==2 && chess[mycolor][k]==4))
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",i,vertwhichline,chess[mycolor][k]);
                        return 0;
                    }
                }
                for(b=4;b>0;b--)
                {
                    for(a=4;a>0;a--)
                    {
                        if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[i][vertwhichline] 
                        && a!=horiwhichline && b!=vertwhichline && !(four==2 && boardsize[a][b]==4))
                        {
                            underchess(a,b,boardsize[a][b],i,vertwhichline,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,vertwhichline);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    

    for(i=4;i>0;i--)                            //亂蓋比自己小1的
    {
        for(j=1;j<5;j++)
        {
            if(boardcolor[i][j]==oppocolor)
            {
                for(a=1;a<5;a++)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==mycolor &&  boardsize[a][b]==boardsize[i][j]+1
                        && board[a][b][boardsize[a][b]-1]!=oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],i,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,j);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    ///////////////////////////////////////////讓4連線//////////////////////////////////////////////////////
    icanlineslash=0;
    icanlinebackslash=0;
    icanlinevert=0;
    icanlinehori=0;
    for(j=1;j<5;j++)                                         //判斷4斜線
    {
        if(boardcolor[5-j][j]==oppocolor && boardsize[5-j][j]==4 && board[5-j][j][3]==mycolor)
        {
            icanlineslash=0;
            break;
        }
        if(boardcolor[5-j][j]==mycolor && boardsize[5-j][j]==4)
        {
            icanlineslash++;
        }
    }
    if(icanlineslash==2)                                         //(創造4斜線)
    {
        for(k=0;k<3;k++)
        {
            for(j=1;j<5;j++)
            {
                if(boardsize[5-j][j]==0 && chess[mycolor][k]==4)
                {
                    fprintf(fPtr, "Put\n(%d,%d,%d)",5-j,j,chess[mycolor][k]);
                    return 0;
                }
            }
        }
    }
    
    for(j=1;j<5;j++)                                                  //判斷4反斜線
    {
        if(boardcolor[j][j]==oppocolor && boardsize[j][j]==4 && board[j][j][3]==mycolor)
        {
            icanlinebackslash=0;
            break;
        }
        if(boardcolor[j][j]==mycolor && boardsize[j][j]==4)
        {
            icanlinebackslash++;
        }
    }
    if(icanlinebackslash==2)                                         //(創造4反斜線)
    {
        for(k=0;k<3;k++)
        {
            for(j=1;j<5;j++)
            {
                if(boardsize[j][j]==0 && chess[mycolor][k]==4)
                {
                    fprintf(fPtr, "Put\n(%d,%d,%d)",j,j,chess[mycolor][k]);
                    return 0;
                }
            }
        }
    }
    ////////////////////////////////////
        for(i=1;i<5;i++)                                           //判斷4水平
        {
            icanlinehori=0;
            for(j=1;j<5;j++)
            {
                if(boardcolor[i][j]==oppocolor && boardsize[i][j]==4 && board[i][j][3]==mycolor)
                {
                    icanlinehori=0;
                    break;
                }
                if(boardcolor[i][j]==mycolor && boardsize[i][j]==4)
                {
                    icanlinehori++;
                }
            }
            if(icanlinehori==2) 
            {
                horiwhichline=i;
                break;
            }
        }
    if(icanlinehori==2)                                         //(創造4水平)
    {
        for(k=0;k<3;k++)
        {
            for(j=1;j<5;j++)
            {
                if(boardsize[horiwhichline][j]==0 && chess[mycolor][k]==4)
                {
                    fprintf(fPtr, "Put\n(%d,%d,%d)",horiwhichline,j,chess[mycolor][k]);
                    return 0;
                }
            }
        }
    }
        /////////////////////////////////
        for(i=1;i<5;i++)                                    //判斷4垂直
        {
            icanlinevert=0;
            for(j=1;j<5;j++)
            {
                if(boardcolor[j][i]==oppocolor && boardsize[j][i]==4 && board[j][i][3]==mycolor)
                {
                    icanlinevert=0;
                    break;
                }
                if(boardcolor[j][i]==mycolor && boardsize[j][i]==4)
                {
                    icanlinevert++;
                }
            }
            if(icanlinevert==2) 
            {
                vertwhichline=i;
                break;
            }
        }
    if(icanlinevert==2)                                         //(創造4垂直)
    {
        for(k=0;k<3;k++)
        {
            for(j=4;j>0;j--)
            {
                if(boardsize[j][vertwhichline]==0 && chess[mycolor][k]==4)
                {
                    fprintf(fPtr, "Put\n(%d,%d,%d)",j,vertwhichline,chess[mycolor][k]);
                    return 0;
                }
            }
        }
    }

    ///////////////////////////
    if(1)                    //放4
    {
        for(i=0;i<3;i++)
        {
            if(chess[mycolor][i]==4)
            {
                for(b=3;b<5;b++)
                {
                    for(a=2;a>0;a--)
                    {
                        if(boardcolor[a][b]==0)
                        {
                            fprintf(fPtr, "Put\n(%d,%d,%d)",a,b,chess[mycolor][i]);
                            return 0;
                        }
                    }
                }
                for(a=3;a<5;a++)
                {
                    for(b=2;b>0;b--)
                    {
                        if(boardcolor[a][b]==0)
                        {
                            fprintf(fPtr, "Put\n(%d,%d,%d)",a,b,chess[mycolor][i]);
                            return 0;
                        }
                    }
                }
                for(b=1;b<5;b++)
                {
                    for(a=1;a<5;a++)
                    {
                        if(boardcolor[a][b]==0)
                        {
                            fprintf(fPtr, "Put\n(%d,%d,%d)",a,b,chess[mycolor][i]);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    ///////////////////////////////////////////讓2跟4連線//////////////////////////////////////////////////////
    if(cantmove3(chess, board, boardsize, boardcolor, oppocolor)==0)
    {
        icanlineslash=0;
        icanlinebackslash=0;
        icanlinevert=0;
        icanlinehori=0;
        for(j=1;j<5;j++)                                         //判斷24斜線
        {
            if(boardcolor[5-j][j]==oppocolor && boardsize[5-j][j]==4)
            {
                icanlineslash=0;
                break;
            }
            if(boardcolor[5-j][j]==mycolor && (boardsize[5-j][j]==4 || boardsize[5-j][j]==2))
            {
                icanlineslash++;
            }
        }
        if(icanlineslash==2)                                         //(創造24斜線)
        {
            for(k=0;k<3;k++)
            {
                for(j=1;j<5;j++)
                {
                    if(boardsize[5-j][j]==0 && chess[mycolor][k]==2)
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",5-j,j,chess[mycolor][k]);
                        return 0;
                    }
                }
            }
            for(j=1;j<5;j++)
            {
                for(a=4;a>0;a--)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==mycolor && (boardsize[a][b]==4 || boardsize[a][b]==2) && boardcolor[5-j][j]!=mycolor && 
                           boardcolor[a][b]>boardsize[5-j][j] && board[a][b][3]!=oppocolor && (a+b)!=5)
                        {
                            underchess(a,b,boardsize[a][b],5-j,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,5-j,j);
                                return 0;
                            }
                        }
                    }
                } 
            } 
        }
        
        for(j=1;j<5;j++)                                                  //判斷24反斜線
        {
            if(boardcolor[j][j]==oppocolor && boardsize[j][j]==4)
            {
                icanlinebackslash=0;
                break;
            }
            if(boardcolor[j][j]==mycolor && (boardsize[j][j]==4 || boardsize[j][j]==2))
            {
                icanlinebackslash++;
            }
        }
        if(icanlinebackslash==2)                                         //(創造24反斜線)
        {
            for(k=0;k<3;k++)
            {
                for(j=1;j<5;j++)
                {
                    if(boardsize[j][j]==0 && chess[mycolor][k]==2)
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",j,j,chess[mycolor][k]);
                        return 0;
                    }
                }
            }
            for(j=4;j>0;j--)
            {
                for(a=4;a>0;a--)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==mycolor && (boardsize[a][b]==4 || boardsize[a][b]==2) && boardcolor[j][j]!=mycolor && 
                           boardcolor[a][b]>boardsize[j][j] && board[a][b][3]!=oppocolor && a!=b)
                        {
                            underchess(a,b,boardsize[a][b],j,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,j);
                                return 0;
                            }
                        }
                    }
                } 
            }
        }
        ////////////////////////////////////
            for(i=1;i<5;i++)                                           //判斷24水平
            {
                icanlinehori=0;
                for(j=1;j<5;j++)
                {
                    if(boardcolor[i][j]==oppocolor && boardsize[i][j]==4)
                    {
                        icanlinehori=0;
                        break;
                    }
                    if(boardcolor[i][j]==mycolor && (boardsize[i][j]==4 || boardsize[i][j]==2))
                    {
                        icanlinehori++;
                    }
                }
                if(icanlinehori==2) 
                {
                    horiwhichline=i;
                    break;
                }
            }
        if(icanlinehori==2)                                         //(創造4水平)
        {
            for(k=0;k<3;k++)
            {
                for(j=1;j<5;j++)
                {
                    if(boardsize[horiwhichline][j]==0 && chess[mycolor][k]==2)
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",horiwhichline,j,chess[mycolor][k]);
                        return 0;
                    }
                }
            }
            for(j=1;j<5;j++)
            {
                for(a=4;a>0;a--)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==mycolor && (boardsize[a][b]==4 || boardsize[a][b]==2) && boardcolor[horiwhichline][j]!=mycolor && 
                           boardcolor[a][b]>boardsize[horiwhichline][j] && board[a][b][3]!=oppocolor && a!=horiwhichline)
                        {
                            underchess(a,b,boardsize[a][b],horiwhichline,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,j);
                                return 0;
                            }
                        }
                    }
                } 
            }
        }
            /////////////////////////////////
            for(i=1;i<5;i++)                                    //判斷24垂直
            {
                icanlinevert=0;
                for(j=1;j<5;j++)
                {
                    if(boardcolor[j][i]==oppocolor && boardsize[j][i]==4)
                    {
                        icanlinevert=0;
                        break;
                    }
                    if(boardcolor[j][i]==mycolor && (boardsize[j][i]==4 || boardsize[j][i]==4))
                    {
                        icanlinevert++;
                    }
                }
                if(icanlinevert==2) 
                {
                    vertwhichline=i;
                    break;
                }
            }
        if(icanlinevert==2)                                         //(創造24垂直)
        {
            for(k=0;k<3;k++)
            {
                for(j=4;j>0;j--)
                {
                    if(boardsize[j][vertwhichline]==0 && chess[mycolor][k]==2)
                    {
                        fprintf(fPtr, "Put\n(%d,%d,%d)",j,vertwhichline,chess[mycolor][k]);
                        return 0;
                    }
                }
            }
            for(j=1;j<5;j++)
            {
                for(a=4;a>0;a--)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==mycolor && (boardsize[a][b]==4 || boardsize[a][b]==2) && boardcolor[j][vertwhichline]!=mycolor && 
                           boardcolor[a][b]>boardsize[j][vertwhichline] && board[a][b][3]!=oppocolor && b!=vertwhichline)
                        {
                            underchess(a,b,boardsize[a][b],j,vertwhichline,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,vertwhichline);
                                return 0;
                            }
                        }
                    }
                } 
            }
            
        }
    }
    if(chess[mycolor][0]==3)
    {
        for(a=3;a<5;a++)
        {
            for(b=1;b<3;b++)
            {
                if(boardcolor[a][b]==0)
                {
                    fprintf(fPtr, "Put\n(%d,%d,%d)",a,b,chess[mycolor][0]);
                    return 0;
                }
            }
        }
    }
    for(i=0;i<3;i++)
    {
        if((cantmove3(chess, board, boardsize, boardcolor, oppocolor)!=2 && chess[mycolor][i]==2) || 
           (cantmove2(chess, board, boardsize, boardcolor, oppocolor)!=2 && chess[mycolor][i]==1))
        {
            for(a=1;a<5;a++)
            {
                for(b=4;b>0;b--)
                {
                    if(boardcolor[a][b]==0)
                    {
                        afterputchess(mycolor,chess[mycolor][i],a,b,board,underboardcolor,underboardsize);
                        if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                        {
                            fprintf(fPtr, "Put\n(%d,%d,%d)",a,b,chess[mycolor][i]);
                            return 0;
                        }
                    }
                }
            }
        }
    }
    //////////////////有策略地放棋/////////////////////
    int vert4, hori4, slash4, backslash4;
        for(a=0;a<3;a++)
        {
            if(chess[mycolor][a]==3)
            {
                for(j=1;j<5;j++)
                {
                    for(i=4;i>0;i--)
                    {
                        if(boardsize[i][j]==0)
                        {
                            if(j+i==5 || j==i)                  //判斷跟斜線的關係
                            {
                                hori4=0;
                                vert4=0;
                                slash4=0;
                                backslash4=0;
                                for(k=4;k>0;k--)
                                {
                                    if(boardsize[k][k]==4 && boardcolor[k][k]==oppocolor)
                                    {
                                        backslash4=1;
                                    }
                                    if(boardsize[5-k][k]==4 && boardcolor[5-k][k]==oppocolor)
                                    {
                                        slash4=1;
                                    }
                                    if(boardsize[i][k]==4 && boardcolor[i][k]==oppocolor)
                                    {
                                        hori4=1;
                                    }
                                    if(boardsize[k][j]==4 && boardcolor[k][j]==oppocolor)
                                    {
                                        vert4=1;
                                    }
                                }
                                    if((hori4==0 && vert4==0 && slash4==0) || (hori4==0 && vert4==0 && backslash4==0))
                                    {
                                        afterputchess(mycolor,chess[mycolor][a],i,j,board,underboardcolor,underboardsize);
                                        if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                        {
                                            fprintf(fPtr, "Put\n(%d,%d,%d)",i,j,chess[mycolor][a]);
                                            return 0;
                                        }
                                    }
                            }
                            hori4=0;
                            vert4=0;
                            for(k=4;k>0;k--)
                            {
                                if(boardsize[i][k]==4 && boardcolor[i][k]==oppocolor)
                                {
                                    hori4=1;
                                }
                                if(boardsize[k][j]==4 && boardcolor[k][j]==oppocolor)
                                {
                                    vert4=1;
                                }
                            }
                            if(hori4==0 && vert4==0)
                            {
                                afterputchess(mycolor,chess[mycolor][a],i,j,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                {
                                    fprintf(fPtr, "Put\n(%d,%d,%d)",i,j,chess[mycolor][a]);
                                    return 0; 
                                }
                            }
                        }
                    }
                }
            }
        }

        for(a=0;a<3;a++)
        {
            if(chess[mycolor][a]!=0)
            {
                for(j=1;j<5;j++)
                {
                    for(i=4;i>0;i--)
                    {
                        if(boardcolor[i][j]!=mycolor)
                        {
                            if(j+i==5 || j==i)                  //判斷跟斜線的關係
                            {
                                hori4=0;
                                vert4=0;
                                slash4=0;
                                backslash4=0;
                                for(k=4;k>0;k--)
                                {
                                    if(boardsize[k][k]==4 && boardcolor[k][k]==oppocolor)
                                    {
                                        backslash4=1;
                                    }
                                    if(boardsize[5-k][k]==4 && boardcolor[5-k][k]==oppocolor)
                                    {
                                        slash4=1;
                                    }
                                    if(boardsize[i][k]==4 && boardcolor[i][k]==oppocolor)
                                    {
                                        hori4=1;
                                    }
                                    if(boardsize[k][j]==4 && boardcolor[k][j]==oppocolor)
                                    {
                                        vert4=1;
                                    }
                                }
                                if(hori4==0 && vert4==0 && slash4==0)
                                {
                                    for(k=4;k>0;k--)
                                    {
                                        if(boardsize[5-k][k]==0 && k!=j)
                                        {
                                            afterputchess(mycolor,chess[mycolor][a],5-k,k,board,underboardcolor,underboardsize);
                                            if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                            {
                                                fprintf(fPtr, "Put\n(%d,%d,%d)",5-k,k,chess[mycolor][a]);
                                                return 0;
                                            }
                                        }
                                        if(boardsize[i][k]==0 && k!=j)
                                        {
                                            afterputchess(mycolor,chess[mycolor][a],i,k,board,underboardcolor,underboardsize);
                                            if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                            {
                                                fprintf(fPtr, "Put\n(%d,%d,%d)",i,k,chess[mycolor][a]);
                                                return 0;
                                            }
                                        }
                                        if(boardsize[k][j]==0 && k!=i)
                                        {
                                            afterputchess(mycolor,chess[mycolor][a],k,j,board,underboardcolor,underboardsize);
                                            if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                            {
                                                fprintf(fPtr, "Put\n(%d,%d,%d)",k,j,chess[mycolor][a]);
                                                return 0;
                                            }
                                        }
                                    }
                                }
                                if(hori4==0 && vert4==0 && backslash4==0)
                                {
                                    for(k=4;k>0;k--)
                                    {
                                        if(boardsize[k][k]==0 && k!=j)
                                        {
                                            afterputchess(mycolor,chess[mycolor][a],k,k,board,underboardcolor,underboardsize);
                                            if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                            {
                                                fprintf(fPtr, "Put\n(%d,%d,%d)",k,k,chess[mycolor][a]);
                                                return 0;
                                            }
                                        }
                                        if(boardsize[i][k]==0 && k!=i)
                                        {
                                            afterputchess(mycolor,chess[mycolor][a],i,k,board,underboardcolor,underboardsize);
                                            if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                            {
                                                fprintf(fPtr, "Put\n(%d,%d,%d)",i,k,chess[mycolor][a]);
                                                return 0;
                                            }
                                        }
                                        if(boardsize[k][j]==0 && k!=j)
                                        {
                                            afterputchess(mycolor,chess[mycolor][a],k,j,board,underboardcolor,underboardsize);
                                            if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                            {
                                                fprintf(fPtr, "Put\n(%d,%d,%d)",k,j,chess[mycolor][a]);
                                                return 0;
                                            }
                                        }
                                    }
                                }
                                if(vert4==0 && slash4==0)
                                {
                                    for(k=1;k<5;k++)
                                    {
                                        if(boardsize[5-k][k]==0 && k!=j)
                                        {
                                            afterputchess(mycolor,chess[mycolor][a],5-k,k,board,underboardcolor,underboardsize);
                                            if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                            {
                                                fprintf(fPtr, "Put\n(%d,%d,%d)",5-k,k,chess[mycolor][a]);
                                                return 0;
                                            }
                                        }
                                        if(boardsize[k][j]==0 && k+j!=5)
                                        {
                                            afterputchess(mycolor,chess[mycolor][a],k,j,board,underboardcolor,underboardsize);
                                            if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                            {
                                                fprintf(fPtr, "Put\n(%d,%d,%d)",k,j,chess[mycolor][a]);
                                                return 0;
                                            }
                                        }
                                    }
                                }
                                if(hori4==0 && slash4==0)
                                {
                                    for(k=1;k<5;k++)
                                    {
                                        if(boardsize[5-k][k]==0 && 5-k!=j)
                                        {
                                            afterputchess(mycolor,chess[mycolor][a],5-k,k,board,underboardcolor,underboardsize);
                                            if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                            {
                                                fprintf(fPtr, "Put\n(%d,%d,%d)",5-k,k,chess[mycolor][a]);
                                                return 0;
                                            }
                                        }
                                        if(boardsize[i][k]==0 && k+i!=5)
                                        {
                                            afterputchess(mycolor,chess[mycolor][a],i,k,board,underboardcolor,underboardsize);
                                            if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                            {
                                                fprintf(fPtr, "Put\n(%d,%d,%d)",i,k,chess[mycolor][a]);
                                                return 0;
                                            }
                                        }
                                    }
                                }
                                if(vert4==0 && backslash4==0)
                                {
                                    for(k=4;k>0;k--)
                                    {
                                        if(boardsize[k][k]==0 && k!=j)
                                        {
                                            afterputchess(mycolor,chess[mycolor][a],k,k,board,underboardcolor,underboardsize);
                                            if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                            {
                                                fprintf(fPtr, "Put\n(%d,%d,%d)",k,k,chess[mycolor][a]);
                                                return 0;
                                            }
                                        }
                                        if(boardsize[k][j]==0 && k!=j)
                                        {
                                            afterputchess(mycolor,chess[mycolor][a],k,j,board,underboardcolor,underboardsize);
                                            if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                            {
                                                fprintf(fPtr, "Put\n(%d,%d,%d)",k,j,chess[mycolor][a]);
                                                return 0;
                                            }
                                        }
                                    }
                                }
                                if(hori4==0 && backslash4==0)
                                {
                                    for(k=4;k>0;k--)
                                    {
                                        if(boardsize[k][k]==0 && k!=i)
                                        {
                                            afterputchess(mycolor,chess[mycolor][a],k,k,board,underboardcolor,underboardsize);
                                            if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                            {
                                                fprintf(fPtr, "Put\n(%d,%d,%d)",k,k,chess[mycolor][a]);
                                                return 0;
                                            }
                                        }
                                        if(boardsize[i][k]==0 && k!=i)
                                        {
                                            afterputchess(mycolor,chess[mycolor][a],i,k,board,underboardcolor,underboardsize);
                                            if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                            {
                                                fprintf(fPtr, "Put\n(%d,%d,%d)",i,k,chess[mycolor][a]);
                                                return 0;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
                for(j=1;j<5;j++)
                {
                    for(i=4;i>0;i--)
                    {
                        if(boardsize[i][j]!=mycolor)
                        {
                            hori4=0;
                            vert4=0;
                            for(k=4;k>0;k--)
                            {
                                if(boardsize[i][k]==4 && boardcolor[i][k]==oppocolor)
                                {
                                    hori4=1;
                                }
                                if(boardsize[k][j]==4 && boardcolor[k][j]==oppocolor)
                                {
                                    vert4=1;
                                }
                            }
                            if(hori4==0 && vert4==0)
                            {
                                for(k=4;k>0;k--)
                                {
                                    if(boardsize[i][k]==0 && k!=j)
                                    {
                                        afterputchess(mycolor,chess[mycolor][a],i,k,board,underboardcolor,underboardsize);
                                        if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                        {
                                            fprintf(fPtr, "Put\n(%d,%d,%d)",i,k,chess[mycolor][a]);
                                            return 0;
                                        }
                                    }
                                    if(boardsize[k][j]==0 && k!=i)
                                    {
                                        afterputchess(mycolor,chess[mycolor][a],k,j,board,underboardcolor,underboardsize);
                                        if(oppocanline(underboardcolor,underboardsize,mycolor,oppocolor)<1)
                                        {
                                            fprintf(fPtr, "Put\n(%d,%d,%d)",k,j,chess[mycolor][a]);
                                               return 0;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    ///////////////////////////////////////////創造單線//////////////////////////////////////////////////////
    icanlineslash=0;
    icanlinebackslash=0;
    icanlinevert=0;
    icanlinehori=0;
    for(j=1;j<5;j++)                                         //判斷斜線
    {
        if(boardcolor[5-j][j]==oppocolor && boardsize[5-j][j]==4)
        {
            icanlineslash=0;
            break;
        }
        if(boardcolor[5-j][j]==mycolor)
        {
            icanlineslash++;
        }
    }
    if(icanlineslash==2)                                         //(進攻斜線)
    {
        for(k=0;k<3;k++)
        {
            for(j=1;j<5;j++)
            {
                if(boardsize[5-j][j]==0 && chess[mycolor][k]!=0)
                {
                    fprintf(fPtr, "Put\n(%d,%d,%d)",5-j,j,chess[mycolor][k]);
                    return 0;
                }
            }
        }
    }
    
    for(j=1;j<5;j++)                                                  //判斷反斜線
    {
        if(boardcolor[j][j]==oppocolor && boardsize[j][j]==4)
        {
            icanlinebackslash=0;
            break;
        }
        if(boardcolor[j][j]==mycolor)
        {
            icanlinebackslash++;
        }
    }
    if(icanlinebackslash==2)                                         //(進攻反斜線)
    {
        for(k=0;k<3;k++)
        {
            for(j=1;j<5;j++)
            {
                if(boardsize[j][j]==0 && chess[mycolor][k]!=0)
                {
                    fprintf(fPtr, "Put\n(%d,%d,%d)",j,j,chess[mycolor][k]);
                    return 0;
                }
            }
        }
    }
    ////////////////////////////////////
        for(i=1;i<5;i++)                                           //判斷水平
        {
            icanlinehori=0;
            for(j=1;j<5;j++)
            {
                if(boardcolor[i][j]==oppocolor && boardsize[i][j]==4)
                {
                    icanlinehori=0;
                    break;
                }
                if(boardcolor[i][j]==mycolor)
                {
                    icanlinehori++;
                }
            }
            if(icanlinehori==2) 
            {
                horiwhichline=i;
                break;
            }
        }
    if(icanlinehori==2)                                         //(進攻水平)
    {
        for(k=0;k<3;k++)
        {
            for(j=1;j<5;j++)
            {
                if(boardsize[horiwhichline][j]==0 && chess[mycolor][k]!=0)
                {
                    fprintf(fPtr, "Put\n(%d,%d,%d)",horiwhichline,j,chess[mycolor][k]);
                    return 0;
                }
            }
        }
    }
        /////////////////////////////////
        for(i=1;i<5;i++)                                    //判斷垂直
        {
            icanlinevert=0;
            for(j=1;j<5;j++)
            {
                if(boardcolor[j][i]==oppocolor && boardsize[j][i]==4)
                {
                    icanlinevert=0;
                    break;
                }
                if(boardcolor[j][i]==mycolor)
                {
                    icanlinevert++;
                }
            }
            if(icanlinevert==2) 
            {
                vertwhichline=i;
                break;
            }
        }
    if(icanlinevert==2)                                         //(創造垂直)
    {
        for(k=0;k<3;k++)
        {
            for(j=1;j<5;j++)
            {
                if(boardsize[j][vertwhichline]==0 && chess[mycolor][k]!=0)
                {
                    fprintf(fPtr, "Put\n(%d,%d,%d)",j,vertwhichline,chess[mycolor][k]);
                    return 0;
                }
            }
        }
    }
    ///////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //123擺空的位置
    if(1)
    {
        for(i=0;i<3;i++)
        {
            if(chess[mycolor][i]==3)
            {
                for(a=3;a<5;a++)
                {
                    for(b=3;b<5;b++)
                    {
                        if(boardcolor[a][b]==0)
                        {
                            fprintf(fPtr, "Put\n(%d,%d,%d)",a,b,chess[mycolor][i]);
                            return 0;
                        }
                    }
                }
                for(b=2;b>0;b--)
                {
                    for(a=2;a>0;a--)
                    {
                        if(boardcolor[a][b]==0)
                        {
                            fprintf(fPtr, "Put\n(%d,%d,%d)",a,b,chess[mycolor][i]);
                            return 0;
                        }
                    }
                }
                for(a=4;a>0;a--)
                {
                    for(b=4;b>0;b--)
                    {
                        if(boardcolor[a][b]==0)
                        {
                            fprintf(fPtr, "Put\n(%d,%d,%d)",a,b,chess[mycolor][i]);
                            return 0;
                        }
                    }
                }
            } 
        }
        for(i=0;i<3;i++)
        {
            if(chess[mycolor][i]!=0)
            {
                for(a=4;a>0;a--)
                {
                    for(b=2;b<4;b++)
                    {
                        if(boardcolor[a][b]==0)
                        {
                            fprintf(fPtr, "Put\n(%d,%d,%d)",a,b,chess[mycolor][i]);
                            return 0;
                        }
                    }
                }
                for(a=3;a>1;a--)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==0)
                        {
                            fprintf(fPtr, "Put\n(%d,%d,%d)",a,b,chess[mycolor][i]);
                            return 0;
                        }
                    }
                }
                for(b=1;b<5;b++)
                {
                    for(a=4;a>0;a--)
                    {
                        if(boardcolor[a][b]==0)
                        {
                            fprintf(fPtr, "Put\n(%d,%d,%d)",a,b,chess[mycolor][i]);
                            return 0;
                        }
                    }
                }
            } 
        }
    }
    /////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////創造單線//////////////////////////////////////////////////////
    icanlineslash=0;
    icanlinebackslash=0;
    icanlinevert=0;
    icanlinehori=0;
    for(j=1;j<5;j++)                                         //判斷斜線
    {
        if(boardcolor[5-j][j]==mycolor)
        {
            icanlineslash++;
        }
    }
    if(icanlineslash==2)                                         //(進攻斜線)
    {
        for(j=1;j<5;j++)
        {
            for(a=4;a>0;a--)
            {
                for(b=1;b<5;b++)
                {
                    if(boardcolor[a][b]==mycolor && boardsize[a][b]==boardsize[5-j][j]+2 
                    && board[a][b][boardsize[a][b]-1]!=oppocolor && board[a][b][boardsize[a][b]-2]!=oppocolor && (a+b)!=5)
                    {
                        underchess(a,b,boardsize[a][b],5-j,j,board,underboardcolor,underboardsize);
                        if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                        {
                            fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,5-j,j);
                            return 0;
                        }
                    }
                }
            } 
        }
    }
    
        for(j=1;j<5;j++)                                                  //判斷反斜線
        {
            if(boardcolor[j][j]==mycolor)
            {
                icanlinebackslash++;
            }
        }
    if(icanlinebackslash==2)                                         //(進攻反斜線)
    {
        for(j=1;j<5;j++)
        {
            for(a=4;a>0;a--)
            {
                for(b=1;b<5;b++)
                {
                    if(boardcolor[a][b]==mycolor && boardsize[a][b]==boardsize[j][j]+2 
                    && board[a][b][boardsize[a][b]-1]!=oppocolor && board[a][b][boardsize[a][b]-2]!=oppocolor && a!=b)
                    {
                        underchess(a,b,boardsize[a][b],j,j,board,underboardcolor,underboardsize);
                        if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                        {
                            fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,j);
                            return 0;
                        }
                    }
                }
            } 
        }
    }
    ////////////////////////////////////
        for(i=1;i<5;i++)                                           //判斷水平
        {
            icanlinehori=0;
            for(j=1;j<5;j++)
            {
                if(boardcolor[i][j]==mycolor)
                {
                    icanlinehori++;
                }
            }
            if(icanlinehori==2) 
            {
                horiwhichline=i;
                break;
            }
        }
    if(icanlinehori==2)                                         //(進攻水平)
    {
        for(j=1;j<5;j++)
        {
            for(a=4;a>0;a--)
            {
                for(b=1;b<5;b++)
                {
                    if(boardcolor[a][b]==mycolor && boardsize[a][b]==boardsize[horiwhichline][j]+2 
                    && board[a][b][boardsize[a][b]-1]!=oppocolor && board[a][b][boardsize[a][b]-2]!=oppocolor && a!=horiwhichline)
                    {
                        underchess(a,b,boardsize[a][b],horiwhichline,j,board,underboardcolor,underboardsize);
                        if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                        {
                            fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,horiwhichline,j);
                            return 0;
                        }
                    }
                }
            } 
        }
    }
        /////////////////////////////////
        for(i=1;i<5;i++)                                    //判斷垂直
        {
            icanlinevert=0;
            for(j=1;j<5;j++)
            {
                if(boardcolor[j][i]==mycolor)
                {
                    icanlinevert++;
                }
            }
            if(icanlinevert==2) 
            {
                vertwhichline=i;
                break;
            }
        }
    if(icanlinevert==2)                                         //(創造垂直)
    {
        for(j=1;j<5;j++)
        {
            for(a=4;a>0;a--)
            {
                for(b=1;b<5;b++)
                {
                    if(boardcolor[a][b]==mycolor && boardsize[a][b]==boardsize[j][vertwhichline]+2 
                    && board[a][b][boardsize[a][b]-1]!=oppocolor && board[a][b][boardsize[a][b]-2]!=oppocolor && b!=vertwhichline)
                    {
                        underchess(a,b,boardsize[a][b],j,vertwhichline,board,underboardcolor,underboardsize);
                        if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                        {
                            fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,j,vertwhichline);
                            return 0;
                        }
                    }
                }
            } 
        }
    }
    for(i=1;i<5;i++)                            //亂蓋比自己小的
    {
        for(j=4;j>0;j--)
        {
            if(boardcolor[i][j]==oppocolor)
            {
                for(a=1;a<5;a++)
                {
                    for(b=1;b<5;b++)
                    {
                        if(boardcolor[a][b]==mycolor &&  boardsize[a][b]>boardsize[i][j]
                        && board[a][b][1]!=oppocolor && board[a][b][2]!=oppocolor && board[a][b][3]!=oppocolor && board[a][b][4]!=oppocolor)
                        {
                            underchess(a,b,boardsize[a][b],i,j,board,underboardcolor,underboardsize);
                            if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                            {
                                fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,j);
                                return 0;
                            }
                        }
                    }
                }
            }
        }
    }
    srand(time(NULL));
    k=rand()%5;
    printf("k=%d",k);
    if(k==0)
    {
        for(i=4;i>0;i--)                            //亂蓋0
        {
            for(j=4;j>0;j--)
            {
                if(boardcolor[i][j]!=mycolor)
                {
                    for(b=1;b<5;b++)
                    {
                        for(a=1;a<5;a++)
                        {
                            if(boardcolor[a][b]==mycolor && boardsize[a][b]==boardsize[i][j]+1)
                            {
                                underchess(a,b,boardsize[a][b],i,j,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,j);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }  
    if(k==1)
    {
        for(j=4;j>0;j--)                            //亂蓋1
        {
            for(i=4;i>0;i--)
            {
                if(boardcolor[i][j]!=mycolor)
                {
                    for(a=1;a<5;a++)
                    {
                        for(b=4;b>0;b--)
                        {
                            if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[i][j] && board[a][b][boardsize[a][b]-1]!=oppocolor)
                            {
                                underchess(a,b,boardsize[a][b],i,j,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,j);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(k==2)
    {
        for(i=1;i<5;i++)                            //亂蓋2
        {
            for(j=4;j>0;j--)
            {
                if(boardcolor[i][j]!=mycolor)
                {
                    for(b=4;b>0;b--)
                    {
                        for(a=4;a>0;a--)
                        {
                            if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[i][j] && board[a][b][boardsize[a][b]-1]!=oppocolor)
                            {
                                underchess(a,b,boardsize[a][b],i,j,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,j);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(k==3)
    {
        for(j=1;j<5;j++)                            //亂蓋3
        {
            for(i=1;i<5;i++)
            {
                if(boardcolor[i][j]!=mycolor)
                {
                    for(b=4;b>0;b--)
                    {
                        for(a=1;a<5;a++)
                        {
                            if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[i][j] && board[a][b][boardsize[a][b]-1]!=oppocolor)
                            {
                                underchess(a,b,boardsize[a][b],i,j,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,j);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    if(k==4)
    {
        for(j=1;j<5;j++)                            //亂蓋4
        {
            for(i=4;i>0;i--)
            {
                if(boardcolor[i][j]!=mycolor)
                {
                    for(b=4;b>0;b--)
                    {
                        for(a=1;a<5;a++)
                        {
                            if(boardcolor[a][b]==mycolor && boardsize[a][b]>boardsize[i][j] && board[a][b][boardsize[a][b]-1]!=oppocolor)
                            {
                                underchess(a,b,boardsize[a][b],i,j,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,j);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for(k=1;k<4;k++)
    {
        for(i=1;i<5;i++)
        {
            for(j=4;j>0;j--)
            {
                if(boardcolor[i][j]!=mycolor)
                {
                    for(b=4;b>0;b--)
                    {
                        for(a=4;a>0;a--)
                        {
                            if(boardcolor[a][b]==mycolor &&  boardsize[a][b]==boardsize[i][j]+k)
                            {
                                underchess(a,b,boardsize[a][b],i,j,board,underboardcolor,underboardsize);
                                if(oppocanline(underboardcolor,underboardsize,oppocolor,mycolor)==0)
                                {
                                    fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,j);
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    for(i=4;i>0;i--)        //亂亂蓋
    {
        for(j=1;j<5;j++)
        {
            if(boardcolor[i][j]!=mycolor)
            {
                for(b=4;b>0;b--)
                {
                    for(a=1;a<5;a++)
                    {
                        if(boardcolor[a][b]==mycolor &&  boardsize[a][b]>boardsize[i][j])
                        {
                            fprintf(fPtr, "Move\n(%d,%d)\n(%d,%d)",a,b,i,j);
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

///////////////////////////////////////////////
/////////////找自己可以拿來用的棋////////////////
///////////////////////////////////////////////
int findchess(int boardcolor[5][5], int boardsize[5][5], int chess[3][3], int color, int elsecolor)
{
    int i, j;
}
////////////////////////////////////////////
//////看拿起來之後長怎樣(再測試會不會死)///////
////////////////////////////////////////////
int afterputchess(int mycolor, int size, int afterrow, int aftercolumn, int board[5][5][5], int underboardcolor[5][5] , int underboardsize[5][5])
{
    int i, j, k;
    for(i=1;i<5;i++)
    {
        for(j=1;j<5;j++)
        {
            underboardcolor[i][j]=0;
            underboardsize[i][j]=0;
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
                    underboardcolor[i][j]=board[i][j][k];                //把棋盤分成顏色棋盤跟大小, 都只存該格最上方的棋子(肉眼看的到的)
                    underboardsize[i][j]=k;
                    break;
                }
            }
        }
    }
    underboardcolor[afterrow][aftercolumn]=mycolor;   
    underboardsize[afterrow][aftercolumn]=size;
}
int underchess(int row, int column, int size, int afterrow, int aftercolumn, int board[5][5][5], int underboardcolor[5][5] , int underboardsize[5][5])
{
    int i, j, k;
    for(i=1;i<5;i++)
    {
        for(j=1;j<5;j++)
        {
            underboardcolor[i][j]=0;
            underboardsize[i][j]=0;
        }
    }
    for(i=1;i<5;i++)
    {
        for(j=1;j<5;j++)
        {
            for(k=4;k>0;k--)
            {
                if(board[i][j][k]!=0 && !(i==row && j==column && k==size))
                {
                    underboardcolor[i][j]=board[i][j][k];                //把棋盤分成顏色棋盤跟大小, 都只存該格最上方的棋子(肉眼看的到的)
                    underboardsize[i][j]=k;
                    break;
                }
            }
        }
    }
    underboardcolor[afterrow][aftercolumn]=board[row][column][size];   
    underboardsize[afterrow][aftercolumn]=size;
    printf("\n\n%d,%d,%d,%d,%d\n\n",row,column,size,afterrow,aftercolumn);
    for (i = 1; i < 5; i++)
    {
        for (j = 1; j < 5; j++)
        {
            printf("%d",underboardsize[i][j]);
        }
        printf("\n");
    }
    for (i = 1; i < 5; i++)
    {
        for (j = 1; j < 5; j++)
        {
            printf("%d",underboardcolor[i][j]);
        }
        printf("\n");
    }
}
//////////////////////////////////////////
/////////////看有沒有快連線////////////////
//////////////////////////////////////////
int oppocanline(int boardcolor[5][5], int boardsize[5][5], int oppocolor, int mycolor)
{
    int a, b, c, d, e;
    a=slashline(boardcolor,boardsize,oppocolor,mycolor);
    b=backslashline(boardcolor,boardsize,oppocolor,mycolor);
    c=vertline(boardcolor,boardsize,oppocolor,mycolor);
    d=horiline(boardcolor,boardsize,oppocolor,mycolor);
    e=twoline(boardcolor,boardsize,oppocolor,mycolor);
    printf("a=%d\nb=%d\nc=%d\nd=%d\ne=%d\n",a,b,c,d,e);
    if(a==4 || b==4 || c==4 || d==4)
    {
        return 4;
    }
    else if(a!=0 || b!=0 || c!=0 || d!=0)
    {
        return 1;
    }
    else if(e==-1)
    {
        return -1;
    }
    else
    {
        return 0;
    }
    

}
int slashline(int boardcolor[5][5], int boardsize[5][5], int color, int elsecolor)
{
    int canlineslash=0, j;
    for(j=1;j<5;j++)
    {
        if(boardcolor[5-j][j]==elsecolor && boardsize[5-j][j]==4)
        {
            canlineslash=0;
            break;
        }
        if(boardcolor[5-j][j]==color)
        {
            canlineslash++;
        }
    }
    if(canlineslash>=3) 
        return canlineslash;
    else 
        return 0;
}

int backslashline(int boardcolor[5][5], int boardsize[5][5], int color, int elsecolor)
{
    int canlinebackslash=0, j;
    for(j=1;j<5;j++)
    {
        if(boardcolor[j][j]==elsecolor && boardsize[j][j]==4)
        {
            canlinebackslash=0;
            break;
        }
        if(boardcolor[j][j]==color)
        {
            canlinebackslash++;
        }
    }
    if(canlinebackslash>=3) 
        return canlinebackslash;
    else 
        return 0;
}

int horiline(int boardcolor[5][5], int boardsize[5][5], int color, int elsecolor)
{
    int canlinehori, i, j;
    for(i=1;i<5;i++)
    {
        canlinehori=0;
        for(j=1;j<5;j++)
        {
            if(boardcolor[i][j]==elsecolor && boardsize[i][j]==4)
            {
                canlinehori=0;
                break;
            }
            if(boardcolor[i][j]==color)
            {
                canlinehori++;
            }
        }
        if(canlinehori==4) 
        {
            return canlinehori;
        }
    }
    for(i=1;i<5;i++)
    {
        canlinehori=0;
        for(j=1;j<5;j++)
        {
            if(boardcolor[i][j]==elsecolor && boardsize[i][j]==4)
            {
                canlinehori=0;
                break;
            }
            if(boardcolor[i][j]==color)
            {
                canlinehori++;
            }
        }
        if(canlinehori>=3) 
        {
            return canlinehori;
        }
    }
    return 0;
}

int vertline(int boardcolor[5][5], int boardsize[5][5], int color, int elsecolor)
{
    int canlinevert, i, j;
    for(i=1;i<5;i++)
    {
        canlinevert=0;
        for(j=1;j<5;j++)
        {
            if(boardcolor[j][i]==elsecolor && boardsize[j][i]==4)
            {
                canlinevert=0;
                break;
            }
            if(boardcolor[j][i]==color)
            {
                canlinevert++;
            }
        }
        if(canlinevert==4) 
        {
            return canlinevert;
        }
    }
    for(i=1;i<5;i++)
    {
        canlinevert=0;
        for(j=1;j<5;j++)
        {
            if(boardcolor[j][i]==elsecolor && boardsize[j][i]==4)
            {
                canlinevert=0;
                break;
            }
            if(boardcolor[j][i]==color)
            {
                canlinevert++;
            }
        }
        if(canlinevert>=3) 
        {
            return canlinevert;
        }
    }
    return 0;
}
int twoline(int boardcolor[5][5], int boardsize[5][5], int oppocolor, int mycolor)
{
    int i, j, k, a, b, oppocanlinevert, oppocanlinehori, oppocanlineslash, oppocanlinebackslash, four;
    for(i=1;i<5;i++)                             ////////////////////判斷防守斜線加垂直
    {
        oppocanlinevert=0;   
        oppocanlineslash=0;
        four=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[j][i]==mycolor && boardsize[j][i]==4) || (boardcolor[5-j][j]==mycolor && boardsize[5-j][j]==4))
            {
                oppocanlineslash=0;
                oppocanlinevert=0;
                four=0;
                break;
            }
            if(boardcolor[j][i]==oppocolor && j+i!=5)
            {
                oppocanlinevert++;
                if(boardsize[j][i]==4)  four++;
            }
            if(boardcolor[5-j][j]==oppocolor && j!=i)
            {
                oppocanlineslash++;
                if(boardsize[5-j][j]==4)  four++;
            }
        }
        if(oppocanlinevert==2 && oppocanlineslash==2 && four!=3)
        {
            return -1;
        }
    }

    ////////////////////////////////////////////
    for(i=1;i<5;i++)                                    ////////////////////判斷防守斜線加水平
    {
        oppocanlinehori=0;  
        oppocanlineslash=0;
        four=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[i][j]==mycolor && boardsize[i][j]==4) || (boardcolor[j][5-j]==mycolor && boardsize[j][5-j]==4))
            {
                oppocanlineslash=0;
                oppocanlinehori=0;
                four=0;
                break;
            }
            if(boardcolor[i][j]==oppocolor && j+i!=5)
            {
                oppocanlinehori++;
                if(boardsize[i][j]==4)  four++;
            }
            if(boardcolor[j][5-j]==oppocolor && j!=i)
            {
                oppocanlineslash++;
                if(boardsize[j][5-j]==4)  four++;
            }
        }
        if(oppocanlinehori==2 && oppocanlineslash==2 && four!=3)
        {
            return -1;
        }
    }

    ////////////////////////////////////////////
    for(i=1;i<5;i++)                                   ////////////////////判斷防守反斜線加垂直
    {
        oppocanlinevert=0;        
        oppocanlinebackslash=0;
        four=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[j][i]==mycolor && boardsize[j][i]==4) || (boardcolor[j][j]==mycolor && boardsize[j][j]==4))
            {
                oppocanlinebackslash=0;
                oppocanlinevert=0;
                four=0;
                break;
            }
            if(boardcolor[j][i]==oppocolor && j!=i)
            {
                oppocanlinevert++;
                if(boardsize[j][i]==4)  four++;
            }
            if(boardcolor[j][j]==oppocolor && j!=i)
            {
                oppocanlinebackslash++;
                if(boardsize[j][j]==4)  four++;
            }
        }
        if(oppocanlinevert==2 && oppocanlinebackslash==2 && four!=3)
        {
            return -1;
        }
    }

    ////////////////////////////////////////////
    for(i=1;i<5;i++)                                        ////////////////////判斷防守反斜線加水平
    {
        oppocanlinehori=0;        
        oppocanlinebackslash=0;
        four=0;
        for(j=1;j<5;j++)
        {
            if((boardcolor[i][j]==mycolor && boardsize[i][j]==4) || (boardcolor[j][j]==mycolor && boardsize[j][j]==4))
            {
                oppocanlinebackslash=0;
                oppocanlinehori=0;
                four=0;
                break;
            }
            if(boardcolor[i][j]==oppocolor && j!=i)
            {
                oppocanlinehori++;
                if(boardsize[i][j]==4)  four++;
            }
            if(boardcolor[j][j]==oppocolor && j!=i)
            {
                oppocanlinebackslash++;
                if(boardsize[j][j]==4)  four++;
            }
        }
        if(oppocanlinehori==2 && oppocanlinebackslash==2 && four!=3)
        {
            return -1;
        }
    }

    ////////////////////////////////////////////
    for(i=1;i<5;i++)                                      ////////////////////判斷防守垂直加水平
    {
        for(j=1;j<5;j++)
        {
            oppocanlinehori=0;     
            oppocanlinevert=0;
            four=0;
            for(k=1;k<5;k++)
            {
                if((boardcolor[i][k]==mycolor && boardsize[i][k]==4) || (boardcolor[k][j]==mycolor && boardsize[k][j]==4))
                {
                    oppocanlinevert=0;
                    oppocanlinehori=0;
                    four=0;
                    break;
                }
                if(boardcolor[i][k]==oppocolor && k!=j)
                {
                    oppocanlinehori++;
                    if(boardsize[i][k]==4)  four++;
                }
                if(boardcolor[k][j]==oppocolor && i!=k)
                {
                    oppocanlinevert++;
                    if(boardsize[k][j]==4)  four++;
                }
            }
            if(oppocanlinehori==2 && oppocanlinevert==2 && four!=3)
            {
                return -1;
            }
        }
    }
    return 0;
}
int cantmove3(int chess[3][3], int board[5][5][5], int boardsize[5][5], int boardcolor[5][5], int oppocolor)
{
    int exist3=0, i, j;
    for(i=1;i<5;i++)
    {
        for(j=1;j<5;j++)
        {
            if(boardcolor[i][j]==oppocolor && boardsize[i][j]==3)
            {

                exist3=1;
            }
        }
    }
    if(exist3==0 && chess[oppocolor][2]>=3)
    {
        return 1;                                                       //0就是沒3號棋 1是手上有 2是場上有
    }
    if(exist3==0 && chess[oppocolor][2]<3)
    {
        return 0;
    }
    if(exist3=1)
    {
        return 2;
    }
}
int cantmove2(int chess[3][3], int board[5][5][5], int boardsize[5][5], int boardcolor[5][5], int oppocolor)
{
    int exist2=0, i, j;
    for(i=1;i<5;i++)
    {
        for(j=1;j<5;j++)
        {
            if(boardcolor[i][j]==oppocolor && boardsize[i][j]==2)
            {

                exist2=1;
            }
        }
    }
    if(exist2==0 && chess[oppocolor][2]>=2)
    {
        return 1;                                                       //0就是沒2號棋 1是手上有 2是場上有
    }
    if(exist2==0 && chess[oppocolor][2]<2)
    {
        return 0;
    }
    if(exist2=1)
    {
        return 2;
    }
}