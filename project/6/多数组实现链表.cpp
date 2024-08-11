#include<iostream>
#include<vector>
using namespace std;
class List{
    public:
	    vector<int> next;
	    vector<int> key;
	    vector<int> prev;
	    int free=0;
	    int head=-1;
        int len=0;
	
	    List(int size){
		    next=vector<int>(size);
		    key=vector<int>(size);
		    prev=vector<int>(size);
		    for(int i=0;i<size;i++)next[i]=i+1;
            next[size-1]=-1;
	    }
        int allocate(){
		    if(free == -1)return -1;
		    int obj = free;
		    free = next[free];
		    return obj;
	    }
	    void add(int index,int val){
		    if(free==-1)return;
            len++;
		    int obj=allocate();
            key[obj]=val;
            if(head==-1){
                head=obj;
                prev[obj]=-1;
                next[obj]=-1;
                return;
            }
            int p = head;
            while(index>0 && next[p]!=-1){p=next[p];index--;}
            if(index > 0){
			    next[p]=obj;
			    prev[obj]=p;
			    next[obj]=-1;
	        }else{
			    if(p==head){
				    head=obj;
				    next[head]=p;
				    prev[p]=head;
			    }else{
				    next[obj]=p;
				    prev[obj]=prev[p];
				    next[prev[obj]]=obj;
				    prev[p]=obj;
			    }
		    }
            return;
	    }
        void update(int index,int val){
            int p = head;
            while(index>0){p=next[p];index--;}
            key[p] = val;
        }
	
	    void remove(int index){
            len--;
		    int p=head;
            while(index>0){p = next[p];index--;}
            if(p==head){
                if(next[p]!=-1)prev[next[p]]=-1;
                head = next[p];
            }else if(next[p]==-1){
                next[prev[p]]=-1;
            }else{
                next[prev[p]]=next[p];
                prev[next[p]]=prev[p];
            }
            free1(p);
	    }
        void free1(int obj){
		    next[obj]=free;
		    free=obj;
	    }

        int search(int index){
            int p=head;
            while(index > 0){p = next[p];index--;}
            return key[p];
        }
        void print1(){
            int p=head;
            while(p!=-1){
                cout<<key[p]<<" ";
                p=next[p];
            }
		    cout<<endl;
        }

        void sort1(){
            int p=next[head];
            next[head]=-1;
            while(p!=-1){
                int tmp=next[p];
                int t=head;
                while(next[t] != -1 && key[t] < key[p])t=next[t];
                if(key[t]<key[p]){
                    next[t]=p;
                    prev[p]=t;
                    next[p]=-1;
                }else if(t == head){
                    next[p]=t;
                    prev[t]=p;
                    head=p;
                }else{
                    next[p] = t;
                    prev[p] = prev[t];
                    next[prev[p]] = p;
                    prev[t] = p;
                }
                p=tmp;
            }
        }
};
int n;
int main(){
	cin>>n;
	List list(n);
    int type,index,val;
	for(int i=0;i<n;i++){	
		cin>>type;
		if(type==0){
			cin>>index>>val;
			list.add(index,val);
		}
		else if(type==1){
			cin>>index;
			list.remove(index);
		}
		else if(type==2){
			cin>>index;
			cout<<list.search(index)<<" "<< endl;
		}
		else if(type==3){
			cin>>index>>val;
			list.update(index,val);
		}
		else if(type == 4)list.sort1();
			
		if(type!=2)list.print1();
	}
	return 0;
}
