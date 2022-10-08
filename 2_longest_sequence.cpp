/*
    最长公共子序列,区别最长公共子串,是可以拆分原字符串,但不能改变原字符串内的字符前后顺序.
    给定两个字符串,例如abcde和bcde----bcd是一个公共子序列,但bcde才是最长公共子序列,
                      abcde和bcfda----bcd是最长公共子序列
*/
#include <iostream>
#include <string.h>
using std::cin;
using std::cout;

int len1, len2;
#define N 100
char s1[N], s2[N];
int dp[N + 1][N + 1]; // dp[5][6]表示长度是5和6的两个字符串的最长公共子序列的长度.
int type[N + 1][N + 1];

void max_length()
{
    memset(dp,0,sizeof(dp));
    memset(type,0,sizeof(type));
    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            if (s1[i-1] == s2[j-1])//输入的字符串s1,s2的下标从0开始到len1-1,len2-1
            {
                dp[i][j] = dp[i - 1][j - 1] + 1; //如果遇到两个字符串内相同的字母,则相当于比他们短一截的字符串的最长公共子序列+1
                type[i][j] = 1;
            }
            else
            {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? (dp[i - 1][j]) : (dp[i][j - 1]);
                type[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? (2) : (3);
            }
        }
    }
}

void print_sequence(int i,int j)
{
    if(i == 0 || j == 0)
        return;
    if(type[i][j] == 1)
    {
        print_sequence(i-1,j-1);
        cout << s1[i-1];
    }
    else if(type[i][j] == 2)
    //abc---bce,dp[3][2]=2,dp[2][3]=1,type[3][3]=2
        print_sequence(i-1,j);
    else
        print_sequence(i,j-1);
}

int main()
{
    cin >> s1 >> s2;
    len1 = strlen(s1);
    len2 = strlen(s2);
    //-------------------------
    max_length();
    cout << dp[len1][len2] << std::endl; //输出s1,s2的最长公共子序列的长度
    print_sequence(len1,len2);//输出s1,s2的最长公共子序列字符串
    return 0;
}