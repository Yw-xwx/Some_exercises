/*
    左右指针,主要用于解决时间复杂度问题,从O(n^2)优化为O(n)
    下面举出了几个例子:
    1.最少救援船问题:   孤岛上有n个人,给出各自的体重(已经升序排列),以及救援船的载重限额(最多2人),求出最少船数.
        双指针,一个从头,一个从尾开始,在相遇之前,每个人都肯定需要一艘船,或独自乘坐,或与人共享.
        如果最重和最轻搭配不超载,则i++,j--下一步处理第二轻和第二重,
        否则最重的独享,j--,下一步考虑最轻和第二重搭配.
        直到两指针相互越过(i > j),当指向正中间的那一个人(i = j)时也需要一艘船

    2.两数之和问题:     给出一升序排列的序列,一个目标sum,返回和为sum的两个数的index(index from 1)
    3.3数之和问题:      给出一升序排列的序列,找出三个和是0的数的下标(index from 1)
    4.3数之和最接近问题: 给出一升序排列的序列,一个目标sum,找出三个和与sum最接近的数字,输出他们的和
*/

#include <stdio.h>
int n;          // the length of the array
int array[100]; // array
int least_boat(int limit)
{
    int ans = 0;
    int i_boat = 0;
    int j_boat = n - 1;
    while (i_boat <= j_boat)
    {
        ans++;
        if (array[i_boat] + array[j_boat] <= limit)
            i_boat++;
        j_boat--;
    }
    return ans;
}

int two_number(int target)
{
    int index_1 = -1, index_2 = -1;
    int left = 0, right = n - 1;
    while (left < right)
    {
        if (array[left] + array[right] > target)
            right--;
        else if (array[left] + array[right] < target)
            left++;
        else
        {
            index_1 = left;
            index_2 = right;
            break;
        }
    }
    if (index_1 + index_2 == -2)
        return 0;
    else
    {
        printf("index1=%d,index2=%d", index_1 + 1, index_2 + 1);
        return 1;
    }
}

int three_number()
{
    int i_three = 0;
    if (array[0] >= 0)
        return 0; //递增的数组,起始元素大于等于0则
    for (; i_three < n; i_three++)
    {
        int target = 0 - array[i_three];
        if (two_number(target))
        {
            printf(",index3=%d", i_three + 1);
            return 1;
        }
    }
    return 0;
}

int my_abs(int x)
{
    if (x < 0)
        return 0 - x;
    return x;
}

void three_number_almost(int target)
{
    int index1 = -1, index2 = -1, index3 = -1;
    int nearest_sum = array[0] + array[1] + array[2];
    int i_almost = 0;

    for (; i_almost < n; i_almost++)
    {
        int left_almost = i_almost+1, right_almost = n - 1;
        while (left_almost < right_almost)
        {
            int temp_sum = array[left_almost] + array[right_almost] + array[i_almost];
            if (temp_sum == target)
            {
                nearest_sum = temp_sum;
                break;
            }
            if (my_abs(nearest_sum - target) > my_abs(temp_sum - target))
                nearest_sum = temp_sum;
            if (temp_sum < target)
            {
                int lefft = left_almost+1;
                while (lefft < right_almost && array[left_almost] == array[lefft])
                    lefft++;
                left_almost = lefft;
            }
            else
            {
                int rright = right_almost-1;
                while(rright > left_almost && array[rright] == array[right_almost])
                    rright--;
                right_almost = rright;
            }
        }
    }
    printf("nearest sum=%d", nearest_sum);
}

int main()
{
    printf("Input the length of the array:");
    scanf("%d", &n);
    printf("Input the elements in the array:");
    int i;
    for (i = 0; i < n; i++)
        scanf("%d", array + i);
    printf("Input the problem you want to test:1-boat,2-TwoIndex,3-ThreeIndex,4-ThreeIndexAlmost:");
    int problem;
    scanf("%d", &problem);
    switch (problem)
    {
    case 1:
        int limit;
        printf("Input the weight limit of boat:");
        scanf("%d", &limit);
        printf("%d", least_boat(limit));
        break;
    case 2:
        int target;
        // int target = 3;------error:cross initialization of 'int target'
        // target = 3;-------ok,definition of target and value assignment respectively
        printf("Input the target of your sum:");
        scanf("%d", &target);
        if (!two_number(target))
            printf("Can't find");
        break;
    case 3:
        if (!three_number())
            printf("Can't find");
        break;
    case 4:
        printf("Input the target of your sum:");
        scanf("%d", &target); //'target' has been definited before,here I use it directly
        three_number_almost(target);
        break;
    default:
        break;
    }
    return 0;
}
