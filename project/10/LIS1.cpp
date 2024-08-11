#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#define MAXN 10000000
using namespace std;
int num[(1024*1024)+10],dp[(1024*1024)+10],F[(1024*1024)+10];
struct tree{
    int val,id;
    bool operator < (tree x){
        if(val==x.val)return id>x.id;
        else return val<x.val; 
    }
}a[(1024*1024)+10];
void add(int x,int y,int n){
    for(;x<=n;x+=x&-x)F[x]=max(F[x],y);
}
int ask(int x){
    int ans=0;
    for(;x>=1;x-=x&-x)ans=max(ans,F[x]);
    return ans;
}
int main(){
    srand(time(NULL));
    double startTime,endTime;
    for(int i=1;i<=(1024*1024);i++)num[i]=(double)rand()/RAND_MAX * (MAXN)+1;

    //贪心+二分搜索
    for(int n=128;n<=(1024*1024);n*=2){
        int ans;
        for(int i=1;i<=n;i++)F[i]=0;
        startTime=clock();
        F[1]=num[1];ans=1;
        for(int j=2;j<=n;j++){
            if(num[j]>F[ans])F[++ans]=num[j];
            else{
                int left=0,right=ans,mid;
                while(left<right){
                    mid=((left+right)/2);
                    if(F[mid]>=num[j])right=mid;
                    else left=mid+1;
                }
                F[left]=num[j];
            }
        }
        endTime=clock();
        cout<<"Scale: "<<n<<" Time cost:"<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;
    }
    cout<<endl;
    //树状数组优化
    for(int n=128;n<=(1024*1024);n*=2){
        int ans;
        for(int i=1;i<=n;i++){
            a[i].val=num[i];
            a[i].id=i;
        }
        for(int i=1;i<=n;i++)F[i]=0;
        startTime=clock();

        sort(a+1,a+n+1);
        for(int i=1;i<=n;i++){
            add(a[i].id,ask(a[i].id)+1,n);
        }
        ans=ask(n);

        endTime=clock();
        cout<<"Scale: "<<n<<" Time cost:"<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;
    }

    cout<<endl;
    //朴素动态规划
    for(int n=128;n<=(1024*1024);n*=2){
        int ans;
        for(int i=1;i<=n;i++)dp[i]=1;
        startTime=clock();
        for(int i=1;i<=n;i++){
            for(int j=1;j<i;j++){
                if(num[j]<num[i]){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }
            ans=max(ans,dp[i]);
        }
        endTime=clock();
        cout<<"Scale: "<<n<<" Time cost:"<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;
    }

}