#include <cstdio>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#define MAXN 1000006
using namespace std;
int n,m,t;
//t=0 随机取值 t=1顺序递增 t=2顺序递减
int a[MAXN];
bool cmp(int a,int b){
    return b<a;
}
int main(){
    srand(time(NULL));
    cin>>n>>m>>t;
    ofstream fout1("data.txt");
    fout1<<n<<endl;
    for(int i=0;i<n;i++)a[i]=(double)rand()/RAND_MAX * (m)+1;

    if(t==1)sort(a,a+n);
    else if(t==2)sort(a,a+n,cmp);

    for(int i=0;i<n;i++)fout1<<a[i]<<" ";

    fout1.close();
    return 0;
}