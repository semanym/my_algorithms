#include<bits/stdc++.h>
using namespace std;
using ll=long long;
inline int read()
{
    char c = getchar();int x = 0,s = 1;
    while(c < '0' || c > '9') {if(c == '-') s = -1;c = getchar();}//æ˜¯ç¬¦å·
    while(c >= '0' && c <= '9') {x = x*10 + c -'0';c = getchar();}//æ˜¯æ•°å­—
    return x*s;
}

inline int read() {
    int x = 0, w = 1;
    char ch = 0;
    while (ch < '0' || ch > '9') {  
        if (ch == '-') w = -1;        
        ch = getchar();               
    }
    while (ch >= '0' && ch <= '9') {  
        x = x * 10 + (ch - '0');  
        ch = getchar();  
    }
    return x * w;  
}

inline ll readL()
{
    char c = getchar();
    ll x = 0, s = 1;
    while (c < '0' || c > '9')
    {
        if (c == '-')
            s = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        x = x * 10 + c - '0';
        c = getchar();
    }
    return x * s;
}


void write(int x) {
  static int sta[35];
  int top = 0;
  do {
    sta[top++] = x % 10, x /= 10;
  } while (x);
  while (top) putchar(sta[--top] + 48);  // 48 ÊÇ '0'
}

// ÉùÃ÷ template Àà,ÒªÇóÌá¹©ÊäÈëµÄÀàĞÍT,²¢ÒÔ´ËÀàĞÍ¶¨ÒåÄÚÁªº¯Êı read()
template <typename T>
T read() {
  T sum = 0, fl = 1;  // ½« sum,fl ºÍ ch ÒÔÊäÈëµÄÀàĞÍ¶¨Òå
  int ch = getchar();
  for (; !isdigit(ch); ch = getchar())
    if (ch == '-') fl = -1;
  for (; isdigit(ch); ch = getchar()) sum = sum * 10 + ch - '0';
  return sum * fl;
}

a = read<int>();
b = read<long long>();
c = read<__int128>();

