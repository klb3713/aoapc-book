#include<stdio.h>
#include<stdlib.h>
#include<string.h>
const int MAXN = 256;

typedef struct TNode{
  int have_value;
  int v;
  struct TNode* left, *right;
} Node;

Node* root;

Node* newnode() {
  Node* u = (Node*) malloc(sizeof(Node));
  if(u != NULL) {
    u->have_value = 0;
    u->left = u->right = NULL;
  }
  return u;
}

int failed;
void addnode(int v, char* s) {
  int n = strlen(s);
  Node* u = root;
  for(int i = 0; i < n; i++)
    if(s[i] == 'L') {
      if(u->left == NULL) u->left = newnode();
      u = u->left;
    } else if(s[i] == 'R') {
      if(u->right == NULL) u->right = newnode();
      u = u->right;
    }
  if(u->have_value) failed = 1;
  u->v = v;
  u->have_value = 1;
}

void remove_tree(Node* u) {
  if(u == NULL) return;
  remove_tree(u->left);
  remove_tree(u->right);
  free(u);
}

char s[MAXN + 10];
int read_input() {
  failed = 0;
  remove_tree(root);
  root = newnode();
  for(;;) {
    if(scanf("%s", s) != 1) return 0;
    if(!strcmp(s, "()")) break;
    int v;
    sscanf(&s[1], "%d", &v);
    addnode(v, strchr(s, ',')+1);
  }
  return 1;
}

int n, ans[MAXN];
int bfs() {
  int front = 0, rear = 1;
  Node* q[MAXN];
  q[0] = root;
  n = 0;
  while(front < rear) {
    Node* u = q[front++];
    if(!u->have_value) return 0;
    ans[n++] = u->v;
    if(u->left != NULL) q[rear++] = u->left;
    if(u->right != NULL) q[rear++] = u->right;
  }
  return 1;
}

int main() {
  while(read_input()) {
    if(!bfs()) failed = 1;
    if(failed) printf("not complete\n");
    else {
      for(int i = 0; i < n; i++) {
        if(i != 0) printf(" ");
        printf("%d", ans[i]);
      }
      printf("\n");
    }
  }
  return 0;
}
