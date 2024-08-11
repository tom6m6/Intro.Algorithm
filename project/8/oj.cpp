#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
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
    string str;
    BST bst1;
    cin>>str;
    char *s = const_cast<char*>(str.c_str());
    char *delim;
    delim = strtok(s, ",");
    while (delim != NULL){
        if (strcmp(delim,"null")!=0) {
            int t = atoi(delim);
            bst1.insert(t);
        }
        delim = strtok(NULL, ",");
    }

    bst1.PreOrder(bst1.root);
    cout<<endl;
    cout<<bst1.getMin()->val<<endl<<bst1.getMax()->val<<endl;
    int n;
    cin>>n;
    while (n--) {
        int t; cin>>t;
        if (bst1.find(t) == nullptr) cout<<"no"<<endl;
        else cout<<"yes"<<endl;
    }
    int m;
    cin>>m;
    while (m--) {
		int t; cin>>t;
        Node *node1 = bst1.find(t);
        if(node1!=nullptr){
            Node *node2=bst1.GetPrev(node1);
            Node *node3=bst1.GetSucc(node1);
            if(node2!=nullptr)cout<<node2->val<<endl;
            if(node3!=nullptr)cout<<node3->val<<endl;
        }
    }
    return 0;
}
