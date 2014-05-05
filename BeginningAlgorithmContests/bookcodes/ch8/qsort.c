#include <stdio.h>

void swap(int *i, int *j) {
    int temp = *i;
    *i = *j;
    *j = temp;
}

void qsort(int *a, int l, int r) {
    if(l >= r)
        return;
    int i, m=l;
    for(i=l+1; i<=r; i++)
        if(a[i]<a[l])
            swap(&a[i], &a[++m]);
    swap(&a[l], &a[m]);
    qsort(a, l, m-1);
    qsort(a, m+1, r);
}

int main()
{
    int a[] = {2,5,1,3,7,0,9,4};
    qsort(a, 0, 7);

    return 0;
}