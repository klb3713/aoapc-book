// LA3135 Argus
// Rujia Liu
#include<cstdio>
#include<queue>
using namespace std;

// 优先队列中的元素
struct Item { 
  int QNum, Period, Time;
  // 重要！优先级比较函数。优先级高的先出队
  bool operator < (const Item& a) const { // 这里的const必不可少，请读者注意
    return Time > a.Time || (Time == a.Time && QNum > a.QNum);
  }
};

int main() {
  priority_queue<Item> pq;
  char s[20];

  while(scanf("%s", s) && s[0] != '#'){
    Item item;
    scanf("%d%d", &item.QNum, &item.Period);
    item.Time = item.Period; // 初始化“下一次事件的时间”为它的周期
    pq.push(item); 
  }

  int K;
  scanf("%d" , &K);
  while(K--) {    
    Item r = pq.top(); // 取下一个事件
    pq.pop();
    printf("%d\n" , r.QNum);    
    r.Time += r.Period; // 更新该触发器的“下一个事件”的时间 
    pq.push(r); // 重新插入优先队列
  }
  return 0;
}
