//-std=c99 or g++
//输入 标准型 线性规划，输出目标函数最优解
//输入格式:
/*
 第一行两个整数n, m，表示n个自变量，m个约束
 第二行n个正数，表示目标函数自变量前的系数
 接下来m行，每行n+1个整数
     前n个正数描述了这个约束的自变量前的系数，最后一个正数描述了这个约束 <=号 右边的数值
 例: 
 输入(讲义里面讲单纯形法时用的例子):
 3 3 
 3 1 2
 1 1 3 30
 2 2 5 24
 4 1 2 36
 输出:
 28.00000000
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <math.h>
#include <ctype.h>
#define MAXN 50  
#define MAXM 50
//MAXN是变量数的上限，MAXM是约束条件数的上限
const double eps = 1e-9;
int dcmp(double x)
{
    if(x < -eps)return -1;
    else if(x > eps)return 1;
    else return 0;
}
void swap(int *a, int *b)
{
    int c = *a;
    *a = *b;
    *b = c;
}
int n, m; //n个变量，m个约束条件
double A[MAXN][MAXM];
int base[MAXN+MAXM], unbase[MAXM+MAXN]; //基本变量与非基本变量
void pivot(int x, int y) //转轴
{
    swap(base+x, unbase+y);
    double k = A[x][y];
    A[x][y] = 1.0;  //前面系数直接变成1.0
    for(int i = 0; i <= n; i++)A[x][i] /= k; //这一行都约掉k
    for(int i = 0; i <= m; i++)  //替换
    {
        if(i != x && dcmp(k = A[i][y]) /* */)
        {
            A[i][0] += (i?-1:1)*k*A[x][0];
            A[i][y] = 0;
            for(int j = 1; j <= n; j++)
                A[i][j] -= k*A[x][j];
        }            
    }
}
int init_simplex()
{
    for(int i = 1; i <= n; i++)unbase[i] = i;  //最开始的n个非基本变量
    for(int i = 1; i <= m; i++)base[i] = n+i; //额外的m个松弛变量
    for(int x = 0, y = 0; ; x = y = 0)
    {
        for(int i = 1; i <= m; i++)
            if(dcmp(A[i][0]) < 0)x = i;
        if(!x)return 1;
        for(int i = 1; i <= n; i++)
            if(dcmp(A[x][i]) < 0)y = i;
        if(!y)return 0; //发现存在b(i) < 0而变量前系数 都大于等于0(注意是 全都 大于等于0)
                       //由于变量具有非负约束，此时整个约束系统无解。
        pivot(x, y);
    }
}
int simplex()
{
    if(!init_simplex())return 0;
    for(int x = 0, y = 0; ; x = y = 0)
    {
        for(int i = 1; i <= n; i++)
            if(dcmp(A[0][i]) > 0)  //找到一个目标函数里前面系数为正数的一个变量
            {                // _______/
                y = i;      //
                break;     //
            }             //
        if(!y)return 1;  //若找不到说明已经找到最优解，返回
        double inf = 1e15;
        for(int i = 1; i <= m; i++)  //找到对y约束最紧的变量
        {
            double t = A[i][0]/A[i][y];
            if(dcmp(A[i][y]) > 0 && (!x || t < inf))
            {
                inf = t;
                x = i;
            }
        }
        if(!x)return -1; //无法约束y,此时整个目标函数发散
        pivot(x, y);
    }
}
void test()
{
    freopen("test_data.txt", "r", stdin);  //这个文件里面就是讲义里面的例子。
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; i++)
        scanf("%lf", A[0]+i);  //A[0]存目标函数，因此最后A[0][0]为目标函数最大值
    for(int i = 1; i <= m; scanf("%lf", A[i++])) //b(i)存到A[i][0]里
        for(int j = 1; j <= n; j++)scanf("%lf", A[i]+j);
    switch(simplex())
    {
        case 1:
            printf("%.8lf\n", A[0][0]);
        break;
        case 0:
            puts("No solution");
        break;
        case -1:
            puts("Infinity");
        break;
    }
}
int main()
{
    test();
    return 0;
}