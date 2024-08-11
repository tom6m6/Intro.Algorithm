#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
int s=0,t=100000000;
int main(){
    ofstream fout("data.txt");
    int n;
    srand(time(NULL));
    cin>>n;fout<<n;
    fout<<endl;
    int tmp;
    for(int i=1;i<=n;i++){
        tmp=((rand())*(rand()))%(t-s+1);
        fout<<tmp<<" ";
    }
    fout.close();
    return 0;
}