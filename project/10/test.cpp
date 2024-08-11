#include <iostream>
using namespace std;
int num[10086],F[10086];
int main(){
    int T;
    cin>>T;
    while(T--){
            int n,ans;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>num[i];
    for(int i=1;i<=n;i++)F[i]=0;
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
    cout<<ans<<" ";
    }
    return 0;
}