// LA3401/UVa1352 Colored Cubes: table maker
// Rujia Liu

#include<cstdio>
#include<cstring>

int left[] = {4, 0, 2, 3, 5, 1};
int up[] = {2, 1, 5, 0, 4, 3};

// °´ÕÕÅÅÁĞTĞı×ª×ËÌ¬p
void rot(int* T, int* p) {
  int q[6];
  memcpy(q, p, sizeof(q));
  for(int i = 0; i < 6; i++) p[i] = T[q[i]];
}

void enumerate_permutations() {
  int p0[6] = {0, 1, 2, 3, 4, 5};
  printf("int dice24[24][6] = {\n");
  for(int i = 0; i < 6; i++) {
    int p[6];
    memcpy(p, p0, sizeof(p0));
    if(i == 0) rot(up, p);
    if(i == 1) { rot(left, p); rot(up, p); }
    if(i == 3) { rot(up, p); rot(up, p); }
    if(i == 4) { rot(left, p); rot(left, p); rot(left, p); rot(up, p); }
    if(i == 5) { rot(left, p); rot(left, p); rot(up, p); }
    for(int j = 0; j < 4; j++) {
      printf("{%d, %d, %d, %d, %d, %d},\n", p[0], p[1], p[2], p[3], p[4], p[5]);
      rot(left, p);
    }
  }
  printf("};\n");
}

int main() {
  enumerate_permutations();
  return 0;
}
