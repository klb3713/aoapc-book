// UVa10361 Automatic Poetry
// Rujia Liu
#include<cstdio>
#include<cstring>
const int maxn = 200;
char line1[maxn], line2[maxn];
int len1, len2;

// 打印第一行的位置from到to的字符
void print1(int from, int to) {
  for(int i = from; i <= to; i++)
    printf("%c", line1[i]);
}

int main() {
  int T;
  scanf("%d\n", &T);
  while(T--) {
    fgets(line1, maxn, stdin);
    fgets(line2, maxn, stdin);
    len1 = strlen(line1)-1;
    len2 = strlen(line2)-1;
    int p1, q1, p2, q2;
    for(p1 = 0; line1[p1] != '<'; p1++);
    for(p2 = p1+1; line1[p2] != '<'; p2++);
    for(q1 = 0; line1[q1] != '>'; q1++);
    for(q2 = q1+1; line1[q2] != '>'; q2++);

    // 第一行
    for(int i = 0; i < len1; i++)
      if(line1[i] != '<' && line1[i] != '>') printf("%c", line1[i]);
    printf("\n");

    // 第二行...之前的部分
    for(int i = 0; i < len2-3; i++)
      printf("%c", line2[i]);

    print1(p2+1, q2-1);   // s4
    print1(q1+1, p2-1);   // s3
    print1(p1+1, q1-1);   // s2
    print1(q2+1, len1-1); // s5
    printf("\n");
  }
  return 0;
}
