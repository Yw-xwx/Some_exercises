#include <stdio.h>

double minx(int n, double *arr); // find minimum in the arr with length=n
double maxx(int n, double *arr); // find maximum in the arr with length=n

int main()
{
    FILE *in = fopen("input.txt", "r");
    FILE *out = fopen("output.txt", "w");
    int n;
    fscanf(in, "%d", &n);
    double location[n];        //记录n个数字在数轴上的位置坐标值
    double min_ = 0, max_ = 0; // the minimum and maximum in the array
    int i = 0;
    for (; i < n; i++)
        fscanf(in, "%lf", location + i);
    //-----------------------------------
    //把n-1个数字,除了最小值,放到n个桶里
    //由于桶比数字个数多,肯定会有至少一个空桶
    //n个桶有n-1个间距,按照(最大-最小)/(n-1)计算出平均间距
    //这样,最大间隔肯定发生在桶和桶之间,而不是桶内
    //尤其是空桶的两侧
    min_ = minx(n, location);
    max_ = maxx(n, location);
    int count[n];                   //每个桶内,数字的个数
    double largest[n], smallest[n]; //设置了n个桶,桶内都有最小最大值
    for (i = 0; i < n; i++)
    {
        count[i] = 0; //每个桶内初始都没有数字
        largest[i] = min_;
        smallest[i] = max_;
    }
    for (i = 0; i < n; i++)
    {
        if (location[i] == min_)                               //最小值对应的bucket是0,本应把最小值放入桶0中,但此处未考虑;
            continue;                                          //最大值对应的bucket是n-1,会被放入最后一个桶(第n个桶).
        double between = (location[i] - min_) / (max_ - min_); // get the index_in_the_bucket of each number
        int bucket = between * (n - 1);                        // 如果直接写成(n-1)*(l[i]-min)/(max-min),乘积太大;
                                                               // 如果写成先除以再相乘,过不去leetcode样例,除法还是应该用double.
        count[bucket]++;                                       // the count of its bucket ++
        if (location[i] < smallest[bucket])
            smallest[bucket] = location[i]; //更新每个桶的最小值
        if (location[i] > largest[bucket])
            largest[bucket] = location[i]; //更新每个桶的最大值
    }
    double max_distance = 0; // output max distance
    double left = largest[0];
    for (i = 1; i < n; i++)
    {
        if (count[i])
        {
            if (max_distance < smallest[i] - left) //每个桶的最小值也就是左端点,和上一个桶的右端点作差得到当前间距
                max_distance = smallest[i] - left;
            left = largest[i]; //更新当前桶的右端点,作为待计算间隔的区间左端点
        }
    }
    //-----------------------------------
    fprintf(out, "%.2lf", max_distance);
    fclose(in);
    fclose(out);
    return 0;
}

double minx(int n, double *arr) // find minimum in the arr with length=n
{
    double minimum = arr[0];
    int i_min = 1;
    for (; i_min < n; i_min++)
    {
        if (arr[i_min] < minimum)
            minimum = arr[i_min];
    }
    return minimum;
}

double maxx(int n, double *arr) // find maxinum in the arr with length=n
{
    double maximum = arr[0];
    int i_max = 1;
    for (; i_max < n; i_max++)
    {
        if (arr[i_max] > maximum)
            maximum = arr[i_max];
    }
    return maximum;
}