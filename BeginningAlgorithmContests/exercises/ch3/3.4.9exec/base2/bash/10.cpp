#include<fstream>
#include<ctime>
#include<cstdlib>
using namespace std;
ofstream fout("10.in");
ofstream fouta("10.outa");
int main()
{
   srand(time(NULL));
   int b,n;
   b=rand()%8+2;
   n=rand()%1000000;
   fout << b << " " << n;
   fouta << n << endl;
   return 0;
}
