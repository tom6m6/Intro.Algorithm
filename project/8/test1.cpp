#include <bits/stdc++.h>
using namespace std;

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

int main() {
    default_random_engine e;
    e.seed(time(NULL));
    uniform_int_distribution<int> u(1,66666666);
    for(int n=1000;n<=1000000;n*=10){
        BST bst2;
        //插入数据规模n
        vector<int> ins;//放插入值
        vector<int> que;//放查询值
        for(int i=0;i<n;i++)ins.push_back(u(e));
        for(int i=0;i<10*n;i++)que.push_back(u(e));
        for(int i=0;i<n;i++)bst2.insert(ins[i]);
        double startTime,endTime;
        for(int m=(n/10);m<=(n*10);m*=10){
            //查询数据规模m
            startTime=clock();
            for(int i=0;i<m;i++)bst2.find(que[i]);
            endTime=clock();
            cout<<"Insert Scale:"<<n<<" Query Scale:"<<m<<" Time Cost: "<<1000*(endTime-startTime) / CLOCKS_PER_SEC<<"ms"<<endl;
        }
    }
}
