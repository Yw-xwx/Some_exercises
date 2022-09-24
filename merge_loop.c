#include <stdio.h>

//the same 'merge' function as recursion
void merge(int arr[], int left, int mid, int right)
{                                      // merge two arrays:  [left,mid] & [mid+1,right] => [left,right]
    int whole_size = right - left + 1; // left=0,mid=3,it has 4 elements
    int temp[whole_size];
    int s1 = left;
    int s2 = mid + 1;
    int temp_index = 0;
    while (s1 <= mid && s2 <= right) // don't know left.length == right.length
    {
        if (arr[s1] < arr[s2])
            temp[temp_index++] = arr[s1++];
        else
            temp[temp_index++] = arr[s2++];
    }
    while (s1 <= mid)
        temp[temp_index++] = arr[s1++];
    while (s2 <= right)
        temp[temp_index++] = arr[s2++]; //两个小的有序数组剩下没有合并进大数组的元素也进入其中
    for (temp_index = 0; temp_index < whole_size; temp_index++)
        arr[temp_index + left] = temp[temp_index]; // arr[left + (i++)]很关键
}

void solve(int a[], int size, int length)
{ // size is the length of the small array each time
    // length is the length of the original array
    while (size <= length)
    {
        int i_solve = 0;
        for (; i_solve < length; i_solve += 2 * size)
        {
            int left = i_solve;
            int mid = size + i_solve - 1;
            int right = size * 2 + i_solve - 1;
            if (mid >= length)
                mid = length - 1;
            if (right >= length)
                right = length - 1;
            merge(a, left, mid, right);
        }
        size *= 2;
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int a[n];
    int i = 0;
    for (; i < n; i++)
        scanf("%d", a + i);
    solve(a, 1, n);
    for (i = 0; i < n; i++)
        printf("%d ", a[i]);
    return 0;
}