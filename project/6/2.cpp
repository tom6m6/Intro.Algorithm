#include<iostream>
using namespace std;
class Node{
    //双向链表的节点
    public:
        int data;
        Node * Next;Node * Prev;
};
 
class List{
    //双向链表本身
public:
    Node *Head;Node *Tail;
    int length;
    List(int length){
        //创建
        this->length=length;
        Head=new Node();
        Head->Prev=NULL;
        Tail=Head;

        for(int i=0;i<length;i++){
            Node *tmp=new Node();
            cin>>tmp->data;
            tmp->Next=NULL;
            tmp->Prev=Tail;
            Tail->Next=tmp;
            Tail=tmp;
        }

    }
    
    ~List(){ //析构函数，销毁时用
        Node *q;
        Node *p=Head->Next;
        while(p!=NULL){
            q=p;
            p=p->Next;
            delete q;
        }
        p=NULL;q=NULL;
    }

    void add(int val,int index){
        Node *p=Head->Next;
        if(index>length||index<=0)return;
        for(int i=0;i<index-1;i++)p=p->Next;
        Node * tmp=new Node();
        tmp->data=val;
        tmp->Next=p;
        tmp->Prev=p->Prev;
        p->Prev->Next=tmp;
        p->Prev=tmp;
        length++;
    }
    


    void update(int val,int index){
        //修改
        Node * p=Head->Next;
        if(index>length||index<=0)return;
        for(int i=0;i<index-1;i++)p=p->Next;
        p->data=val;
    }

    void remove(int index){
        //删除
        Node * p=Head->Next;
        if(index>length||index<=0)return;
        for(int i=0;i<index-1;i++)p=p->Next;
        p->Prev->Next=p->Next;
        p->Next->Prev=p->Prev;
        delete p;
        length--;
    }
    
    int search(int index){
        //查找
        Node * p=Head->Next;
        if(index>length||index<=0)return 0;
        for(int i=0;i<index-1;i++)p=p->Next;
        return p->data;
    }

    void sort1(){
        //插入排序
        if(Head->Next==NULL||Head->Next->Next==NULL)return;
        Node * p2=Head->Next->Next;
        Node * p1=Head;
        Head->Next->Next=NULL;
        while(p2){
            Node * p3=p2->Next;
            while(p1->Next){
                if(p2->data<p1->Next->data){
                    p2->Next=p1->Next;
                    p2->Prev=p1;
                    p1->Next->Prev=p2;
                    p1->Next=p2;
                    break;
                }
                p1=p1->Next;
            }
            if(p1->Next==NULL){
                p2->Next=NULL;
                p2->Prev=p1;
                p1->Next=p2;
            }
            p2=p3;
        }
        
        Node * pt=Head;
        while(pt->Next)pt=pt->Next;
        Tail=pt;
    }

    void print1(){
        Node * p=Head->Next;
        while(p!=NULL){
            cout<<p->data<<" ";
            p=p->Next;
        }
        cout<<endl;
    }
    
    /*
    void sort2(){
        //冒泡排序
        Node * p=new Node();
        Node * q=new Node();
        int tmp;
        for(p=Head->Next;p->Next!=NULL;p=p->Next)
        {
            for(q=p->Next;q!=NULL;q=q->Next)
            {
                if(q->data<p->data)
                {
                    tmp=q->data;
                    q->data=p->data;
                    p->data=tmp;
                }
            }
        }
    }
    */
};

int n;
int main(){
    cin>>n;
    List list(n);
    list.sort1();
    list.print1();
    return 0;
}