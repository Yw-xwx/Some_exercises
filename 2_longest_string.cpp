#include <iostream>
#include <string.h>
using std::cin;
using std::cout;
using std::endl;
int len1, len2;
#define N 100
char s1[N], s2[N];
int dp[N + 1][N + 1]; // dp[5][6]表示长度是5和6的两个字符串的最长公共子字符串的长度.

int main()
{
    cin >> s1 >> s2;
    len1 = strlen(s1);
    len2 = strlen(s2);
    //-------------------------
    memset(dp,0,sizeof(dp));
    int maximum = 1,index = 0;
    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            if (s1[i-1] == s2[j-1])//输入的字符串s1,s2的下标从0开始到len1-1,len2-1
            {
                dp[i][j] = dp[i - 1][j - 1] + 1; //如果遇到两个字符串内相同的字母,则相当于比他们短一截的字符串的最长公共子字符串+1
                if(maximum < dp[i][j])
                {
                    maximum = dp[i][j];
                    index = i-1;//随着向后遍历,找到的最长子字符串逐渐变长,index从公共子串的首个元素下标变成末尾元素下标
                } 
            }
        }
    }
    cout << maximum << endl;
    for(int i = index-maximum+1;i<=index;i++)//因此此处i从last-length开始,持续输出length个,例如length=3,last=4,从[2,4]
        cout << s1[i];
    return 0;
}