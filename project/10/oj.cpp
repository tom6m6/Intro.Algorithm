#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;
int a[5121],f[5121];
int k1;
int search(int i,int len){
    int left=0;
    int right=len;
    int mid;
    while(left<right){
        mid=((left+right)/2);
        if(f[mid]>=a[i])right=mid;
        else left=mid+1;
    }
    return left;
}
int main(){
    cin>>k1;
    int n,k,m;
    for(int i=0;i<k1;i++){
        cin>>n;
        for(int j=1;j<=n;j++)cin>>a[j];
        f[1]=a[1];
        k=1;
        for(int j=2;j<=n;j++){
            if(a[j]>f[k])f[++k]=a[j];
            else{
                m=search(j,k);
                f[m]=a[j];
            }
        }
        cout<<k<<" ";
    }

    return 0;
}