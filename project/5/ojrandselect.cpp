#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;
int a[4500006];
int n,i;
void swap(int *m, int *n){
    int tmp;
    tmp = *m;
    *m = *n;
    *n = tmp;
}
int partition(int p, int r){
    int x = a[r];
    int i = p-1;
    for(int j = p;j < r; j++){
        if(a[j] <= x){
            i = i + 1;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i+1], &a[r]);
    return i + 1;
}
int random_partition(int p, int r){
    int t = p + rand() % (r - p + 1);
    swap(&a[t], &a[r]);
    return partition(p, r);
}
int random_select(int p, int r, int i){
    if(p == r) return a[p];
    int pivot = random_partition(p, r);
    int k = pivot - p + 1;
    if(i == k) return a[pivot];
    else if(i < k) return random_select(p, pivot - 1, i);
    else return random_select(pivot + 1, r, i - k);
}
int main(){
    srand(time(NULL));
    
    cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    cout<<random_select(0,n-1,n/2)<<endl;

    return 0;
}