#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string.h>
#include <vector>
#define MAXN 1000010
#define MAXM 100001000
using namespace std;
int n;
vector <int> a;
vector <int> b;
int main(){
    srand(time(NULL));
    cin>>n;
    ofstream fout1("randkey.txt");
    ofstream fout2("randop.txt");
    for(int i=0;i<MAXN;i++)a.push_back(i);
    random_shuffle(a.begin(),a.end());
    for(int i=0;i<n;i++){fout1<<a[i]<<" ";}
    for(int i=0;i<n;i++){fout2<<(rand() % 2)<<endl;}

    fout1.close();
    fout2.close();
    return 0;
}