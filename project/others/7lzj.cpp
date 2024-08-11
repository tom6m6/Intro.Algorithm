#include<iostream>
#include<vector>
#include<unordered_set>

using namespace std;

vector<int> create(int N){
    srand((unsigned)time(NULL));
    unordered_set<int> set;
    vector<int> arr(N);
    int low = -0x7fffffff;
    int high = 0x7fffffff;
    int i = 0;
    while(i < N){
        int num = rand() % (high - low + 1) + low;
        if(set.find(num) != set.end())
            continue;
        set.insert(num);
        arr[i++] = num;
    }
    return arr;
}

class HashTable{
public:
    HashTable(int N){
        size = N;
        arr = vector<int>(size,-0x7fffffff-1);
    }

    void insert(int num){
        int index = hashCode(num);
        if(arr[index] == -0x7fffffff-1){
            arr[index] = num;
            return;
        }
        int i = (index + 1) % size;
        while(arr[i] == -0x7fffffff-1 && i != index)
            i = (i + 1) % size;
        if(i == index){
            cout << "哈希表满了" << endl;
            return;
        }
        arr[i] = num;
    }

    bool search(int num){
        int index = hashCode(num);
        if(arr[index] == num)
            return true;
        else if(arr[index] == -0x7fffffff-1)
            return false;
        int i = (index + 1) % size;
        while(arr[i] != -0x7fffffff-1 && i != index)
            i = (i + 1) % size;
        if(arr[i] != num)
            return false;
        return true;
    }

private:
    int size;
    vector<int> arr;
    int hashCode(int key){
        return key % size;
    }
};

int main(){
    cout << (-10 % 3);
}