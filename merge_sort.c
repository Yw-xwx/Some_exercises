//this is designed for showing merge_sort

//Be care:
//when merge two smaller arrays have ordered together into a bigger one
//first use array 'temp' to contain the elements one by one
//then copy the value in 'temp' to the original array
//!!!  NOT  arr[i++] = temp[i++]
//!!!  BUT  arr[left+(i++)] = temp[i++]

#include <stdio.h>

void merge(int arr[],int left,int mid,int right)
{//merge two arrays:  [left,mid] & [mid+1,right] => [left,right]
    int whole_size = right-left+1;//left=0,mid=3,it has 4 elements
    int temp[whole_size];
    int s1 = left;
    int s2 = mid+1;
    int temp_index = 0;
    while(s1 <= mid && s2 <= right)//don't know left.length == right.length
    {
        if(arr[s1] < arr[s2])
            temp[temp_index++] = arr[s1++];
        else
            temp[temp_index++] = arr[s2++];
    }
    while(s1 <= mid)
        temp[temp_index++] = arr[s1++];
    while(s2 <= right)
        temp[temp_index++] = arr[s2++];//两个小的有序数组剩下没有合并进大数组的元素也进入其中
    for(temp_index = 0;temp_index < whole_size;temp_index++)
        arr[temp_index+left] = temp[temp_index];//arr[left + (i++)]很关键
}

void my_merge_sort(int arr[],int left,int right)
{
    if(left < right)
    {
        int mid = left+(right-left)/2;
        my_merge_sort(arr,left,mid);//左半部分排序
        my_merge_sort(arr,mid+1,right);//右半部分排序
        merge(arr,left,mid,right);//合并两个有序部分成一个大的有序部分
    }
}

int main()
{
    int n;
    scanf("%d",&n);
    int arr[n];
    int i = 0;
    for(;i < n;i++)
        scanf("%d",arr+i);
    my_merge_sort(arr,0,n-1);
    for(i = 0 ;i < n;i++)
        printf("%d ",arr[i]);
    return 0;
}