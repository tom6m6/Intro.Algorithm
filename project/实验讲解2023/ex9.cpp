#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include <random>
#include <cmath>
#include <ctime>

struct TreeNode // 二叉树节点
{
    int val;
    bool color; // 红黑树的颜色，true为红色，false为黑色
    struct TreeNode *left;
    struct TreeNode *right;
    struct TreeNode *parent; // 父节点

    // TreeNode(int x) : val(x), color(true),
    //                   left(NIL), right(NIL), parent(NIL) {} // 构造函数，别忘记初始化
    // c++ 用NILptr 更为合适
    // c 中没有构造函数，只能用初始化列表，用原始方法初始化即可
};

TreeNode *NIL; // 哨兵节点，所有叶子节点都指向它，！还有根节点的父也指向他

TreeNode *createNode(int val)
{
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val = val;
    node->color = true;
    node->left = NIL;
    node->right = NIL;
    node->parent = NIL;
    return node;
}

// long long count = 0; // 计数器，用于统计旋转次数

TreeNode *leftRotate(TreeNode *root, TreeNode *x) // 左旋，翻转会改变根节点，所以返回根节点
{
    // count++; // 旋转次数加一

    TreeNode *y = x->right; // 设置y
    x->right = y->left;     // 将y的左孩子设为x的右孩子
    if (y->left != NIL)     // 如果y的左孩子非空，将y的左孩子的父节点设为x
    {
        y->left->parent = x;
    }
    y->parent = x->parent; // 将x的父节点设为y的父节点
    if (x->parent == NIL)  // 如果x的父节点为空，则将y设为根节点
    {
        root = y;
    }
    else if (x == x->parent->left) // 如果x是其父节点的左孩子，则将y设为x的父节点的左孩子
    {
        x->parent->left = y;
    }
    else // 如果x是其父节点的右孩子，则将y设为x的父节点的右孩子
    {
        x->parent->right = y;
    }
    y->left = x;   // 将x设为y的左孩子
    x->parent = y; // 将x的父节点设为y

    return root;
}

TreeNode *rightRotate(TreeNode *root, TreeNode *y) // 右旋，翻转会改变根节点，所以返回根节点
{
    // count++; // 旋转次数加一

    TreeNode *x = y->left; // 设置x
    y->left = x->right;    // 将x的右孩子设为y的左孩子
    if (x->right != NIL)   // 如果x的右孩子非空，将x的右孩子的父节点设为y
    {
        x->right->parent = y;
    }
    x->parent = y->parent; // 将y的父节点设为x的父节点
    if (y->parent == NIL)  // 如果y的父节点为空，则将x设为根节点
    {
        root = x;
    }
    else if (y == y->parent->left) // 如果y是其父节点的左孩子，则将x设为y的父节点的左孩子
    {
        y->parent->left = x;
    }
    else // 如果y是其父节点的右孩子，则将x设为y的父节点的右孩子
    {
        y->parent->right = x;
    }
    x->right = y;  // 将y设为x的右孩子
    y->parent = x; // 将y的父节点设为x

    return root;
}

TreeNode *RBInsertFixup(TreeNode *root, TreeNode *z) // 插入修复，翻转会改变根节点，所以返回根节点
{
    // 这个就是按照PPT中的伪代码实现的。
    while (z->parent->color) // 因属性4被违反，所以要进行修复，循环直至z的父节点为黑色，见PPT20-22页
    {
        if (z->parent == z->parent->parent->left) // PPT 中第 1-3 种情况
        {
            TreeNode *y = z->parent->parent->right;
            if (y->color) // PPT 中第 1 种情况
            {
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                z = z->parent->parent;
            }
            else // PPT 中第 2-3 种情况
            {
                if (z == z->parent->right) // PPT 中第 2 种情况
                {
                    // 第二种情况就转换成第三种情况进行处理
                    z = z->parent;
                    root = leftRotate(root, z);
                } // PPT 中第 3 种情况
                z->parent->color = false;
                z->parent->parent->color = true;
                root = rightRotate(root, z->parent->parent);
            }
        }
        else // PPT 中第 4-6 种情况
        {
            TreeNode *y = z->parent->parent->left;
            if (y->color)
            {
                z->parent->color = false;
                y->color = false;
                z->parent->parent->color = true;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    root = rightRotate(root, z);
                }
                z->parent->color = false;
                z->parent->parent->color = true;
                root = leftRotate(root, z->parent->parent);
            }
        }
    }
    root->color = false;

    return root;
}

TreeNode *RBInsert(TreeNode *root, int val) // 插入节点
{
    TreeNode *y = NIL;
    TreeNode *x = root;

    while (x != NIL) // 找到插入位置
    {
        y = x;
        if (val < x->val)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }

    // 生成新节点并插入
    TreeNode *z = createNode(val); // 初始化新插入的节点，默认为红色，值为val，父母孩子都是NIL，（这是c++的写法，c中的话变成实例化结构体，然后进行初始化）
    z->parent = y;                 // 设置新节点的父节点
    if (y == NIL)                  // 如果y为空，说明树为空，直接将z设为根节点
    {
        root = z;
    }
    else if (z->val < y->val) // 如果z的值小于y的值，说明z是y的左孩子
    {
        y->left = z;
    }
    else // 如果z的值大于y的值，说明z是y的右孩子
    {
        y->right = z;
    }

    // 插入修复
    root = RBInsertFixup(root, z);

    return root;
}

void inOrder(TreeNode *root) // 中序遍历
{
    if (root == NIL)
    {
        return;
    }
    inOrder(root->left);
    // printf("%d ", root->val);
    if (root->color)
    {
        printf("R"); // 这里直接输出了颜色了
    }
    else
    {
        printf("B");
    }
    inOrder(root->right);
}

int RBHeight(TreeNode *root) // 计算红黑树的高度
{
    if (root == NIL)
    {
        return 0;
    }
    int leftHeight = RBHeight(root->left);
    int rightHeight = RBHeight(root->right);
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

int main()
{

    TreeNode NilNode = {
        0,
        false,
        NULL,
        NULL,
        NULL};

    NIL = &NilNode;
    // Tips: 不使用NIL而使用NULL的话，按照课本上的伪代码写会出现空指针异常，表面上的报错就是段错误（segmentation fault）
    // 也可以使用NULL，但是要在那些调用指针的时候要注意判断指针是否为空

    int N;
    scanf("%d", &N);

    int v;
    TreeNode *root = NIL;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &v);
        root = RBInsert(root, v);
    }

    inOrder(root);

    // std::mt19937 gen(time(NULL));
    // std::uniform_int_distribution<> dis(0, RAND_MAX);

    // int n = pow(10, 6);
    // TreeNode *root = NIL;
    // int *data = new int[n];  // 随机
    // int *data2 = new int[n]; // 顺序
    // for (int i = 0; i < n; i++)
    // {
    //     data[i] = dis(gen);
    //     data2[i] = n - i;
    // }

    // clock_t start, end;
    // start = clock();
    // for (int i = 0; i < n; i++)
    // {
    //     // root = RBInsert(root, data[i]);
    //     // root = RBInsert(root, data2[i]);
    // }
    // end = clock();
    // printf("insert time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
    // // printf("height: %d\n", RBHeight(root));
    // // printf("rotate num: %lld\n", count);

    // delete[] data;
    // delete[] data2;

    return 0;
}
