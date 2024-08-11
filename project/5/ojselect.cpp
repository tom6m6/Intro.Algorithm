#include<iostream>
#include<fstream>
#include<cstdlib>
#include<ctime>
using namespace std;
int a[4500006];
int n, i;
struct I2D{
    int index;
    int value;
};
void swap(int *m, int *n){
    int tmp;
    tmp = *m;
    *m = *n;
    *n = tmp;
}
int partition(int p, int r, int pivot){
    int x = a[pivot];
    int i = p-1;
    for(int j = p;j <= r; j++){
        if(a[j] <= x){
            i = i + 1;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i], &a[pivot]);
    return i;
}
void insert_sort(int l, int r){
    int key, j;
    for(int i = l; i <= r; i++){
        key = a[i];
        j = i - 1;
        while(j >= l && a[j] > key){
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}
I2D select(int p, int r, int i){
    if(r - p < 140){
        insert_sort(p, r);
        I2D pack;
        pack.index = p + i - 1;
        pack.value = a[p + i - 1];
        return pack;
    }
    for(int u = 0; u <= (r - p) / 5; u++){
        if(p + u * 5 + 4 > r){
            insert_sort(p + u * 5, r);
            int mid = p + 5 * u + (r - (p + 5 * u)) / 2;
            swap(&a[mid], &a[p + u]);
        }
        else{
            insert_sort(p + u * 5, p + u * 5 + 4);
            int mid = p + 5 * u + 2;
            swap(&a[mid], &a[p + u]);
        }
    }
    I2D tmpPack = select(p, p + (r - p) / 5, ((r - p) / 5 + 1) / 2);
    int tmp = tmpPack.index;
    int pivot = partition(p, r, tmp);
    int k = pivot - p + 1;
    if(i == k) {
        I2D subPack;
        subPack.index = pivot;
        subPack.value = a[pivot];
        return subPack;
    }
    else if(i < k) return select(p, pivot - 1, i);
    else return select(pivot + 1, r, i - k);
}
int main(){
    srand(time(NULL));
    int n, i;
    cin>>n;
    for(int i=0;i<n;i++)cin>>a[i];
    I2D result = select(0, n-1, n/2);
    cout<<result.value<<endl;

    return 0;
}