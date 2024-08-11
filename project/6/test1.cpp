#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class MultiArrayObject {
private:
    vector<int> data;  // 存储元素的数组
    vector<int> next;  // 存储每个元素的下一个节点的索引
    int head;          // 链表头指针

public:
    MultiArrayObject() {
        head = -1;
    }

    // 在指定位置插入元素
    void insert(int index, int val) {
        if (index < 0 || index > data.size()) {
            return;
        }
        data.insert(data.begin() + index, val);
        next.insert(next.begin() + index, -1);
        if (index == 0) {
            next[index] = head;
            head = index;
        } else {
            next[index - 1] = index;
            next[index] = next[index - 1];
        }
    }

    // 删除指定位置的元素
    void remove(int index) {
        if (index < 0 || index >= data.size()) {
            return;
        }
        if (index == head) {
            head = next[index];
        } else {
            int curr = head;
            while (next[curr] != index) {
                curr = next[curr];
            }
            next[curr] = next[index];
        }
        data.erase(data.begin() + index);
        next.erase(next.begin() + index);
    }

    // 获取指定位置的元素
    int get(int index) {
        if (index < 0 || index >= data.size()) {
            return -1;
        }
        return data[index];
    }

    // 修改指定位置的元素
    void set(int index, int val) {
        if (index < 0 || index >= data.size()) {
            return;
        }
        data[index] = val;
    }

    // 对链表进行选择排序
    void selectionSort() {
        int i, j, min_idx;
        for (i = 0; i < data.size() - 1; i++) {
            min_idx = i;
            for (j = i + 1; j < data.size(); j++) {
                if (data[j] < data[min_idx]) {
                    min_idx = j;
                }
            }
            if (min_idx != i) {
                int temp = data[i];
                data[i] = data[min_idx];
                data[min_idx] = temp;

                int next_temp = next[i];
                next[i] = next[min_idx];
                next[min_idx] = next_temp;
            }
        }
    }
};

int main() {
    int N, op, pos, val;
    cin >> N;
    MultiArrayObject obj;
    for (int i = 0; i < N; i++) {
        cin >> op;
        switch (op) {
            case 0:  // 增加（插入）
                cin >> pos >> val;
                obj.insert(pos, val);
                for(int j=0;i<obj.data.size();i++)cout<<obj[j]<<" ";
                break;
            case 1:  // 删除
                cin >> pos;
                obj.remove(pos);
                for(int j=0;i<obj.data.size();i++)cout<<obj[j]<<" ";
                break;
            case 2:  // 查找
                cin >> pos;
                cout << obj.get(pos) << endl;
                for(int j=0;i<obj.data.size();i++)cout<<obj[j]<<" ";
                break;
            case 3:  // 修改
                cin >> pos >> val;
                obj.set(pos, val);
                for(int j=0;i<obj.data.size();i++)cout<<obj[j]<<" ";
                break;
            case 4:  // 排序
                obj.selectionSort();
                for(int j=0;i<obj.data.size();i++)cout<<obj[j]<<" ";
                break;

        }
    }
}