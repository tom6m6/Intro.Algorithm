#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;
struct Node{
    Node *left,*right,*parent;
    int val,color;//0 black,1 red
    Node(int val,int color){
        this->val=val;
        this->color=color;
        this->left=nullptr;
        this->right=nullptr;
        this->parent=nullptr;
    }
};
class RBtree{
public:
    Node *root;
    RBtree():root(nullptr){}
    ~RBtree(){destroy(root);}

    void destroy(Node *root){
        if(root){
            destroy(root->left);
            destroy(root->right);
            delete root;
            root=nullptr;
        }
    }

    void Lrotate(Node *node){
        struct Node *noder=node->right;
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

    void Rrotate(Node *node){
        Node *nodel=node->left;
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

    Node *Fix(Node *node){
        Node *tmp;
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

    void insert(Node *node){
        Node *x,*y,*nroot;
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

    void Inorder(Node *r) {
        if (r == nullptr) return;
        Inorder(r->left);
        if(r->color)cout<<"R";
        else cout<<"B";
        Inorder(r->right);
    }

    Node *find(int val){
        Node *cur = root;
        while(cur){
            if(cur->val < val)cur = cur->right;
            else if(cur->val > val) cur = cur->left;
            else return cur;
        }
        return nullptr;
    }

};


RBtree rbtree1;
int main(){
    int tmp,n;
    cin>>n;
    cin>>tmp;Node *tmp1=new Node(tmp,0);rbtree1.root=tmp1;
    n--;
    for(int i=0;i<n;i++){
        cin>>tmp;
        Node *tmp2 =new Node(tmp,1);
        rbtree1.insert(tmp2);
    }
    rbtree1.Inorder(rbtree1.root);
    return 0;
}