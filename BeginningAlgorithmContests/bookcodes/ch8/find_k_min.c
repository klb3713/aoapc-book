#include <stdio.h>
#include <stdlib.h>

void swap(int *i, int *j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}

int find_k_min(int *a, int l, int r, int k) {
    if(l > r || k>r-l+1)
        exit(-1);
    if(l==r && k==1)
        return a[l];
    int i, m=l;
    for(i=l+1; i<=r; i++)
        if(a[i]<a[l])
            swap(&a[i], &a[++m]);
    swap(&a[l], &a[m]);

    if(m-l+1 == k)
        return a[m];
    else if(m-l+1 > k)
        return find_k_min(a, l, m-1, k);
    else
        return find_k_min(a, m+1, r, k-(m-l+1));
}

int main()
{
    int a[] = {2,5,1,3,7,0,6,9,4,8};
    int res = find_k_min(a, 0, 9, 4);
    printf("%d\n", res);

    return 0;
}