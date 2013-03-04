// LA2727/UVa1024 A Linking Loader
// Rujia Liu
#include<cstdio>
#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<set>
#include<algorithm>
using namespace std;

struct Module {
  int base;
  map<string, int> def;
  map<string, bool> multiple;
  vector<string> ref;
  vector<int> code;
};

vector<Module> mods;
vector<string> syms;

string readsym() {
  string s;
  cin >> s;
  syms.push_back(s);
  return s;
}

int readhex() {
  string s;
  cin >> s;
  if(s == "$") return -1;
  int x;
  sscanf(s.c_str(), "%x", &x);
  return x;
}

bool read_module(int& base) {
  Module mod;
  mod.base = base;
  string s;
  while(cin >> s) {
    if(s == "$") return false;
    if(s == "Z") {
      mods.push_back(mod);
      return true;
    }
    if(s == "D") {
      string sym = readsym();
      int addr = readhex();
      if(mod.def.count(sym)) mod.multiple[sym] = true; else mod.def[sym] = addr;
    }
    if(s == "E") mod.ref.push_back(readsym());
    if(s == "C") {
      int sz = readhex();
      base += sz;
      while(sz--) mod.code.push_back(readhex());
    }
  }
}

map<string, int> addr;
map<string, bool> multiple;

void findsym(string sym, int& hi, int& lo) {
  hi = addr[sym] >> 8;
  lo = addr[sym] & 0xff;
}

void solve() {
  sort(syms.begin(), syms.end());
  syms.erase(unique(syms.begin(), syms.end()), syms.end());
  addr.clear();
  multiple.clear();

  // decide sym positions
  int msz = mods.size();
  int ssz = syms.size();
  for(int i = 0; i < ssz; i++) {
    string sym = syms[i];
    addr[sym] = 0; // 'default address' when filling the blanks
    multiple[sym] = false;
    for(int j = 0; j < msz; j++) {
      if(mods[j].def.count(sym)) {
        if(addr[sym] == 0)
          addr[sym] = mods[j].def[sym] + mods[j].base;
        else
          multiple[sym] = true;
        if(mods[j].multiple.count(sym)) multiple[sym] = true;
      }
    }
  }

  // fill the code blanks
  int checksum = 0;
  for(int i = 0; i < msz; i++) {
    int csz = mods[i].code.size();
    for(int j = 0; j < csz; j++) {
      if(mods[i].code[j] == -1) {
        string sym = mods[i].ref[mods[i].code[j+1]];
        findsym(sym, mods[i].code[j], mods[i].code[j+1]);
      }
      int h = checksum >> 15;
      checksum = ((checksum << 1) + h + mods[i].code[j]) & 0xffff;
    }
  }

  // print the answer
  printf("checksum = %04X\n", checksum);
  printf(" SYMBOL   ADDR\n");
  printf("--------  ----\n");
  for(int i = 0; i < ssz; i++) {
    string sym = syms[i];
    printf("%s", sym.c_str());
    for(int j = 0; j < 10 - sym.length(); j++) printf(" ");
    if(addr[sym] == 0) printf("????");
    else {
      printf("%04X", addr[sym]);
      if(multiple[sym]) printf(" M");
    }
    printf("\n");
  }
}

bool read_case() {
  int base = 0x100;
  mods.clear();
  syms.clear();
  while(read_module(base));
  if(mods.empty()) return false;
  return true;
}

int main() {
  int kase = 0;
  while(read_case()) {
    if(kase) printf("\n");
    printf("Case %d: ", ++kase);
    solve();
  }
  return 0;
}
