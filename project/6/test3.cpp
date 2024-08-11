#include<iostream>
#include<vector>

using namespace std;

class List{
public:
	vector<int> next;
	vector<int> key;
	vector<int> pre;
	int free = 0;
	int head = -1;
    int length = 0;
	
	List(int size){
		next = vector<int>(size);
		key = vector<int>(size);
		pre = vector<int>(size);
		for(int i=0;i<size-1;i++)
			next[i] = i + 1;
        next[size - 1] = -1;
	}
	
	bool add(int index,int val){
		if(free == -1)
			return false;
        length++;
		int obj = allocate_object();
        key[obj] = val;
        if(head == -1){
            head = obj;
            pre[obj] = -1;
            next[obj] = -1;
            return true;
        }
        int p = head;
        while(index > 0 && next[p] != -1){
            p = next[p];
            index--;
        }
        if(index > 0){
			next[p] = obj;
			pre[obj] = p;
			next[obj] = -1;
		}
		else{
			if(p == head){
				head = obj;
				next[head] = p;
				pre[p] = head;
			}
			else{
				next[obj] = p;
				pre[obj] = pre[p];
				next[pre[obj]] = obj;
				pre[p] = obj;
			}
		}
        return true;
	}

    void update(int index,int val){
        int p = head;
        while(index > 0){
            p = next[p];
            index--;
        }
        key[p] = val;
    }
	
	void remove(int index){
        length--;
		int p = head;
        while(index > 0){
            index--;
            p = next[p];
        }
        if(p == head){
            if(next[p] != -1)
                pre[next[p]] = -1;
            head = next[p];
        }
        else if(next[p] == -1){
            next[pre[p]] = -1;
        }
        else{
            next[pre[p]] = next[p];
            pre[next[p]] = pre[p];
        }
        free_obj(p);
	}

    int search(int index){
        int p = head;
        while(index > 0){
            p = next[p];
            index--;
        }
        return key[p];
    }

    void println(){
        int p = head;
        while(p != -1){
            cout << key[p] << ' ';
            p = next[p];
        }
		cout << endl;
    }

    void sortList(){
        int p = next[head];
        next[head] = -1;
        while(p != -1){
            int s = next[p];
            int t = head;
            while(next[t] != -1 && key[t] < key[p])
                t = next[t];
            if(key[t] < key[p]){
                next[t] = p;
                pre[p] = t;
                next[p] = -1;
            }
            else if(t == head){
                head = p;
                next[p] = t;
                pre[t] = p;
            }
            else{
                next[p] = t;
                pre[p] = pre[t];
                next[pre[p]] = p;
                pre[t] = p;
            }
            p = s;
        }
    }
	
private:
	int allocate_object(){
		if(free == -1)
			return -1;
		int obj = free;
		free = next[free];
		return obj;
	}
	
	int free_obj(int obj){
		next[obj] = free;
		free = obj;
	}
};

int main(){
	int n;
	cin >> n;
	List list(n);
    int type,index,val;
	for(int i=0;i<n;i++){
		cin >> type;
		if(type == 0){
			cin >> index;
			cin >> val;
			list.add(index,val);
		}
		else if(type == 1){
			cin >> index;
			list.remove(index);
		}
		else if(type == 2){
			cin >> index;
			cout << list.search(index) << endl;
		}
		else if(type == 3){
			cin >> index;
			cin >> val;
			list.update(index,val);
		}
		else
			list.sortList();
		if(type != 2)list.println();
	}
	return 0;
}