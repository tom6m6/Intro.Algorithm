#include <cstring>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <fstream>
#define INF 0x7fffffff
#define MAXN 10000000
using namespace std;
int Hash_table[MAXN];
int table2[MAXN];
vector<int> a,b;
int num;
int find(int x) {
    int t=(x%MAXN+MAXN)%MAXN,k=1;
    while(Hash_table[t]!= INF && Hash_table[t]!=x) {
        t=(x%MAXN+k+MAXN)%MAXN;
        k++;
    }
    return t;
}
int find1(int x) {
    int t=(x%MAXN+MAXN)%MAXN,k=1;
    while(Hash_table[t]!= INF && Hash_table[t]!=x) {
        t=(x%MAXN+2*k*k+MAXN)%MAXN;
        k++;
    }
    return t;
}
int find2(int x){
    for(int i=0;i<num;i++)if(table2[i]==x)return i;
    return INF;
}
int main(){
    int m;
    for(int i=0;i<10000010;i++)a.push_back(i);
    for(int i=0;i<10000010;i++)b.push_back(i);
    cout<<"Hash Table MAX Size:"<<MAXN<<endl;
    //开放寻址法(线性)
    m=0;
    for (int i=0;i<MAXN;i++)Hash_table[i]=INF;
    for(int n=1000000,i=0;i<9;i++){
        m+=n;
        cout<<"Scale:"<<n<<"Proportion:"<<((double) m/MAXN)<<endl;
        
        random_shuffle(a.begin(),a.end());random_shuffle(b.begin(),b.end());
        double startTime,endTime;
        startTime=clock();
        for(int i=0;i<n;i++)Hash_table[find(a[i])]=a[i];
        endTime=clock();
        cout<<"Insert"<<n<<"Time cost:"<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;
        startTime=clock();
        for(int i=0;i<n;i++)find(b[i]);
        endTime=clock();
        cout<<"Query"<<n<<"Time cost:"<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;
    }


    
    //开放寻址法(二次)
    m=0;
    for (int i=0;i<MAXN;i++)Hash_table[i]=INF;
    for(int n=1000000,i=0;i<9;i++){
        m+=n;
        cout<<"Scale:"<<n<<"Proportion:"<<((double) m/MAXN)<<endl;
        for (int i=0;i<MAXN;i++)Hash_table[i]=INF;
        random_shuffle(a.begin(),a.end());random_shuffle(b.begin(),b.end());

        double startTime,endTime;
        startTime=clock();
        for(int i=0;i<n;i++)Hash_table[find1(a[i])]=a[i];
        endTime=clock();
        cout<<"Insert"<<n<<"Time cost:"<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;
        startTime=clock();
        for(int i=0;i<n;i++)find1(b[i]);
        endTime=clock();
        cout<<"Query"<<n<<"Time cost:"<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;
    }


    //顺序访问
    m=0;num=0;
    for (int i=0;i<MAXN;i++)table2[i]=INF;
    for(int n=1000000,i=0;i<9;i++){
        m+=n;
        cout<<"Scale:"<<n<<"Proportion:"<<((double) m/MAXN)<<endl;
        random_shuffle(a.begin(),a.end());random_shuffle(b.begin(),b.end());
        double startTime,endTime;
        startTime=clock();
        for(int i=0;i<n;i++)table2[num++]=a[i];
        endTime=clock();
        cout<<"Insert"<<n<<"Time cost:"<<1000*((double)endTime-(double)startTime ) / CLOCKS_PER_SEC<<"ms"<<endl;
        startTime=clock();
        for(int i=0;i<n;i++)find2(b[i]);
        endTime=clock();
        cout<<"Query"<<n<<"Time cost:"<<1000*((double)endTime-(double)startTime ) / CLOCKS_PER_SEC<<"ms"<<endl;
    }
    return 0;
}