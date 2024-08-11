#include <cstring>
#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <fstream>
using namespace std;
vector <int> a,b;
struct Node {
    Node *left;
    Node *right;
    Node *parent;
    int val;
    Node(int val){
        this->left=nullptr;
        this->right=nullptr;
        this->val=val;
    }
};

struct Node1{
    Node1 *left,*right,*parent;
    int val,color;//0 black,1 red
    Node1(int val,int color){
        this->val=val;
        this->color=color;
        this->left=nullptr;
        this->right=nullptr;
        this->parent=nullptr;
    }
};

class BST {
public:
    Node *root;//根节点
    Node *prev = nullptr;//寻找前驱/后继时，保存前驱
    BST():root(nullptr){}
    ~BST() {destroy(root);}

    void destroy(Node *root) {
        if(root) {
            destroy(root->left);
            destroy(root->right);
            delete root;
            root=nullptr;
        }
    }

    bool insert(int val) {
        if (root==nullptr) {
            root = new Node(val);
            return true;
        }
        Node *cur = root;Node *prev = nullptr;
        while (cur!=nullptr) {
            prev = cur;
            if (cur->val < val) cur = cur->right;
            else if (cur->val > val) cur = cur->left;
            else return false;//没有相同的
        }
        Node* cur1 = new Node(val);
        if (prev->val < val) prev->right = cur1;
        else prev->left = cur1;
        cur1->parent=prev;
        return true;
    }

    Node *find(int val) {
        Node *cur = root;
        while (cur) {
            if (cur->val < val) cur = cur->right;
            else if (cur->val > val) cur = cur->left;
            else return cur;
        }
        return nullptr;
    }

    void PreOrder(Node *root) {
        if (root == nullptr) return;
        cout<<root->val<<' ';
        PreOrder(root->left);
        PreOrder(root->right);
    }

    void Inorder(Node *root) {
        if (root == nullptr) return;
        Inorder(root->left);
        cout<<root->val<<' ';
        Inorder(root->right);
    }
    void PostOrder(Node *root) {
        if (root == nullptr) return;
        PostOrder(root->left);
        PostOrder(root->right);
        cout<<root->val<<' ';
    }
    Node *getMax() {
        Node *cur = root;
        while (cur->right!=nullptr)cur = cur->right;
        return cur;
    }

    Node *getMin() {
        Node *cur = root;
        while (cur->left!=nullptr)cur = cur->left;
        return cur;
    }
    
    Node *GetPrev(Node *node){
        Node *ans=nullptr;
        if(node->left!=nullptr){
            Node *r = node->left;
            while(r->right!=nullptr)r=r->right;
            ans=r;
        }
        else{
            ans=node->parent;
            while((ans!=nullptr) && (node==ans->left)){
                node=ans;
                ans=ans->parent;
            }
        }
        return ans;
    }
    Node *GetSucc(Node *node){
        Node *ans=nullptr;
        if(node->right!=nullptr){
            Node *l = node->right;
            while(l->left!=nullptr)l=l->left;
            ans=l;
        }
        else{
            ans=node->parent;
            while((ans!=nullptr) && (node==ans->right)){
                node=ans;
                ans=ans->parent;
            }
        }
        return ans;
    }
};

class RBtree{
public:
    Node1 *root;
    RBtree():root(nullptr){}
    ~RBtree(){destroy(root);}

    void destroy(Node1 *root){
        if(root){
            destroy(root->left);
            destroy(root->right);
            delete root;
            root=nullptr;
        }
    }

    void Lrotate(Node1 *node){
        struct Node1 *noder=node->right;
        node->right=noder->left;
        if (noder->left)noder->left->parent=node;
        noder->parent=node->parent;
        if(node->parent){
            if (node==node->parent->left)node->parent->left=noder;
            else node->parent->right=noder;
        }
        noder->left=node;
        node->parent=noder;
    }

    void Rrotate(Node1 *node){
        Node1 *nodel=node->left;
        node->left=nodel->right;
        if (nodel->right)nodel->right->parent=node;
        nodel->parent = node->parent;
        if(node->parent) {
            if (node==node->parent->left)node->parent->left=nodel;
            else node->parent->right= nodel;
        }
        nodel->right=node;
        node->parent=nodel;
    }

    Node1 *Fix(Node1 *node){
        Node1 *tmp;
        while(node->parent && node->parent->color == 1){
            if(node->parent == node->parent->parent->left){
                tmp=node->parent->parent->right;
                if(tmp && tmp->color==1){
                    node->parent->color=0;
                    tmp->color=0;
                    node->parent->parent->color=1;
                    node=node->parent->parent;
                    if(!node->parent)node->color = 0;
                }
              else{
                    if (node==node->parent->right) {
                        node=node->parent;
                        Lrotate(node);
                    }
                    node->parent->color=0;
                    node->parent->parent->color=1;
                    Rrotate(node->parent->parent);
                }
            }else{
                tmp=node->parent->parent->left;
                if(tmp && tmp->color==1){
                    node->parent->color = 0;
                    tmp->color = 0;
                    node->parent->parent->color = 1;
                    node=node->parent->parent;
                    if(!node->parent)node->color = 0;
                }
                else {
                    if (node==node->parent->left) {
                        node=node->parent;
                        Rrotate(node);
                    }
                    node->parent->color=0;
                    node->parent->parent->color=1;
                    Lrotate(node->parent->parent);
                }
            }
        }
        tmp=node;
        while (tmp->parent)tmp=tmp->parent;
        tmp->color = 0;
        return tmp;
    }

    void insert(Node1 *node){
        Node1 *x,*y,*nroot;
        x=this->root;
        while(x){
            y=x;
            if(node->val<x->val)x=x->left;
            else x=x->right;
        }
        node->parent=y;
        if(node->val < y->val)y->left=node;
        else y->right=node;
        node->color = 1;
        this->root=Fix(node);
    }

    void Inorder(Node1 *r) {
        if (r == nullptr) return;
        Inorder(r->left);
        if(r->color)cout<<"R";
        else cout<<"B";
        Inorder(r->right);
    }

    Node1 *find(int val){
        Node1 *cur = root;
        while(cur){
            if(cur->val < val)cur = cur->right;
            else if(cur->val > val) cur = cur->left;
            else return cur;
        }
        return nullptr;
    }

};


int main(){
    for(int i=0;i<10000000;i++){
        a.push_back(i);
        b.push_back(i);
    }

    for(int n=100;n<=1000000;n*=10){
        random_shuffle(a.begin(),a.end());
        RBtree rbtree1;
        double startTime,endTime;
        startTime=clock();
        Node1 *tmp1=new Node1(a[0],0);rbtree1.root=tmp1;
        for(int i=1;i<n;i++){
            Node1 *tmp2 =new Node1(a[i],1);
            rbtree1.insert(tmp2);
        }
        endTime=clock();
        cout<<"RBTree Insert"<<n<<" Time:"<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;
    }

    cout<<endl<<"Random Case:"<<endl;

    for(int n=100;n<=1000000;n*=10){
        random_shuffle(a.begin(),a.end());
        random_shuffle(b.begin(),b.end());
        BST bst1;
        double startTime,endTime;
        startTime=clock();
        for(int i=0;i<n;i++)bst1.insert(a[i]);
        endTime=clock();
        cout<<"Normal BST Insert "<<n<<" Time:"<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;

        
        for(int m=(n/10);m<=n*10;m*=10){
            //查询的数量为m 10% 100% 1000%
            startTime=clock();
            for(int i=0;i<m;i++)bst1.find(b[i]);
            endTime=clock();
            cout<<"Normal BST Search "<<m<<" in "<<n<<" Time: "<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;

        }
    }
    
    cout<<endl;

    for(int n=100;n<=1000000;n*=10){
        random_shuffle(a.begin(),a.end());
        random_shuffle(b.begin(),b.end());
        RBtree rbtree2;
        double startTime,endTime;
        startTime=clock();
        Node1 *tmp1=new Node1(a[0],0);rbtree2.root=tmp1;
        for(int i=1;i<n;i++){
            Node1 *tmp2 =new Node1(a[i],1);
            rbtree2.insert(tmp2);
        }
        endTime=clock();
        cout<<"RBTree Insert "<<n<<" Time:"<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;

        
        for(int m=(n/10);m<=n*10;m*=10){
            //查询的数量为m 10% 100% 1000%
            startTime=clock();
            for(int i=0;i<m;i++)rbtree2.find(b[i]);
            endTime=clock();
            cout<<"RBTree Search "<<m<<" in "<<n<<" Time: "<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;

        }
    }

    cout<<endl<<"Increase Case:"<<endl;

    for(int n=100;n<=1000000;n*=10){
        random_shuffle(a.begin(),a.end());
        random_shuffle(b.begin(),b.end());
        sort(a.begin(),a.begin()+n);
        RBtree rbtree2;
        double startTime,endTime;
        startTime=clock();
        Node1 *tmp1=new Node1(a[0],0);rbtree2.root=tmp1;
        for(int i=1;i<n;i++){
            Node1 *tmp2 =new Node1(a[i],1);
            rbtree2.insert(tmp2);
        }
        endTime=clock();
        cout<<"RBTree Insert "<<n<<" Time:"<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;

        
        for(int m=(n/10);m<=n*10;m*=10){
            //查询的数量为m 10% 100% 1000%
            startTime=clock();
            for(int i=0;i<m;i++)rbtree2.find(b[i]);
            endTime=clock();
            cout<<"RBTree Search "<<m<<" in "<<n<<" Time: "<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;

        }
    }

    cout<<endl;

    for(int n=100;n<=100000;n*=10){
        random_shuffle(a.begin(),a.end());
        random_shuffle(b.begin(),b.end());

        sort(a.begin(),a.begin()+n);

        BST bst1;
        double startTime,endTime;
        startTime=clock();
        for(int i=0;i<n;i++)bst1.insert(a[i]);
        endTime=clock();
        cout<<"Normal BST Insert "<<n<<" Time:"<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;

        
        for(int m=(n/10);m<=n*10;m*=10){
            //查询的数量为m 10% 100% 1000%
            startTime=clock();
            for(int i=0;i<m;i++)bst1.find(b[i]);
            endTime=clock();
            cout<<"Normal BST Search "<<m<<" in "<<n<<" Time: "<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;

        }
    }
    
    return 0;

}