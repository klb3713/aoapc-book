// UVa11988 Broken Keyboard (a.k.a. Beiju Text)
// 陈锋
#include <cstring>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <vector>

using namespace std;
struct ListNode
{
    char c;
    ListNode* next;
};

ListNode MEM[100000 + 10], *mem_next, *head, *tail, *insPos;

int main()
{    
    while(true)
    {
        char c;
        mem_next = MEM + 1;
        head = MEM;
        head -> next = NULL;
        tail = head;
        insPos = tail;
        while(true)
        {
            c = getchar();
            if(c == '\n') break;
            if(c == EOF) return 0;
            
            if(c == '[') insPos = head;
            else if(c == ']') insPos = tail;
            else 
            {
                ListNode* newNode = mem_next++;
                newNode->c = c;
                newNode->next = insPos->next;                
                insPos->next = newNode;
                insPos = newNode;
                if(tail->next != NULL) tail = insPos;
            }
        }
        
        ListNode* cur = head->next;
        while(cur != NULL)
        {
            putchar(cur->c);
            cur=cur->next;
        }
        puts("");
    }
    return 0;
}
