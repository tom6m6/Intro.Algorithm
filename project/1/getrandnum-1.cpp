#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
bool cmp(int a, int b){return b < a;}
int n,s,t,type,a[1000000+666];
int main() {
    srand(time(0));
    cin>>n>>s>>t>>type;
    ofstream fout("randnum.txt");
    for(int i = 0; i < n; i++)a[i] = s + rand() % (t-s+1);
    if(type == 1)sort(a, a + n);
    else if(type == 2)sort(a, a + n, cmp);
    for(int w = 0; w < n; w++)fout<<a[w]<<" ";
    fout.close();
    return 0;
}