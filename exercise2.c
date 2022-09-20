/*
    give a string,output its order
    In the string,every character a-z can only appear one time
*/
#include <stdio.h>

int change(char ch);                  //把字符ch转化成数字,a-1,b-2,……,z-26.
int amount_begin(int begin, int len); //计算以字符begin开头的长度是len的字符串个数
int amount_len(int len);              //进而计算长度是len的字符串个数

int main()
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int n;
    char s1[6];
    int len = 0;
    fscanf(in, "%d %s", &n, s1);
    // there is no need to initialize the array s1
    // because it will automatically add '\0' when fscanf
    // we can just utilize this end character to know the length of s1
    int i;
    for (i = 0;; i++)
    {
        if (s1[i] == 0)
            break;
        len++;
    }
    int order = 0;
    int j = 0;
    for (j = 1; j < len; j++) //长度比目标字符串短的字符串个数
    {//例如cgkz,计算长度是1,2,3的字符串个数
        order += amount_len(j);
    }
    for (j = 1;j<change(s1[0]);j++) //和目标字符串一样长但是首字母更小的字符串个数
    {//例如cgkz,计算以a---和b---
        order += amount_begin(j,len);
    }
    int former = change(s1[0]);
    for (j = 1; j < len; j++) //和目标字符串一样长并且首字母相同的字符串个数(除首字母外,后续字母更小)
    {//例如cgkz,计算c---时,依次计算cd--,ce--,cf--,cg--
     //其中,g--要分为gk_和g[h-j]_
        int now = change(s1[j]);//当前字母now,依次是g,k,z
        int length = len-j;//当前的剩余字符串长度length,依次是3,2,1
        int k;
        for(k = former + 1;k < now;k++)//当前填写的字母应该从比前一个字母大1个开始,直到等于当前字母减一
        {
            order += amount_begin(k,length);//依次加上,以当前填写的字母为起始,以当前剩余字符串长度为长度的字符串个数
        }
        former = now;//更新前一个字母
    }
    fprintf(out,"%d",order+1);//order是比当前字符串小的字符串个数,加上1才是当前字符串的序号
    fclose(in);
    fclose(out);
    return 0;
}

int change(char x)
{
    return x - 'a' + 1;
}

int amount_begin(int x, int len)
{
    if (len == 1)
        return 1; //长度是1,并且以字母x开头的字符串只有1个
    int sum = 0;
    int index = x;
    for (index = x + 1; index <= 26; index++)
    {
        sum += amount_begin(index, len - 1); //递归计算,以当前首字母的下一个字母开头,长度短1的字符串个数
    }
    return sum;
}

int amount_len(int len)
{
    if(len <= 0)
        return 0;
    int sum = 0;
    int i = 0;
    for (i = 1; i <= 26; i++)
    {
        sum += amount_begin(i, len);
    }
    return sum;
}