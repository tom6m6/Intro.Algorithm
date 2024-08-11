#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <vector>
using namespace std;
#define MAXN 10000000
vector<int>num;
int main(){
    int tmp;
    num.push_back(0);
    for(int i=1;i<=(1024*1024);i++){
        tmp=(double)rand()/RAND_MAX * (MAXN)+1;
        num.push_back(tmp);
    }
    srand(time(NULL));
    double startTime,endTime;
    for(int n=128;n<=(1024*1024);n*=4){
        vector<int> F;
        int ans;
        startTime=clock();
        F.push_back(0);
        F.push_back(num[1]);
        ans=1;
        for(int j=2;j<=n;j++){
            if(num[j]>F[ans]){
                ++ans;
                F.push_back(num[j]);
            }else{
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
    /*
    for(int n=128;n<=(1024*1024);n*=4){
        vector<int> num,dp;
        int tmp,ans=0;
        for(int i=0;i<n;i++){
            tmp=(double)rand()/RAND_MAX * (MAXN)+1;
            num.push_back(tmp);
        }
        startTime=clock();
        for(int i=0;i<n;i++){
            dp.push_back(1);
            for(int j=0;j<i;j++){
                if(num[j]<num[i]){
                    dp[i]=max(dp[i],dp[j]+1);
                }
            }
            ans=max(ans,dp[i]);
        }
        endTime=clock();
        cout<<"Scale: "<<n<<" Time cost:"<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;
    }
    */
}