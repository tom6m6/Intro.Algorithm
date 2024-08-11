#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct TreeNode // 二叉树节点
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    // 父节点？

    TreeNode(int x) : val(x), left(NULL), right(NULL) {} // 构造函数，别忘记初始化
    // c++ 用nullptr 更为合适
    // c 中没有构造函数，只能用初始化列表，用原始方法初始化即可
};

// 因为给的是序列，所以可以不用比较大小，直接按照序列采用递归的方法平铺过去，也是可以的。
// 因为序列给的也是从上到下的，从左到右的，建完上一层才会有下一层，所以直接平铺赋值过去和用普通建树的方法结果是一样的。
// 我这里采用了最简单的普通的建树的方法。效率不高，但是比较容易理解
// 可以按照课本上的循环写法，效率更高些
TreeNode *insert(TreeNode *root, int val) // 插入节点
{
    if (root == NULL) // 如果根节点为空，直接插入
    {
        root = new TreeNode(val); // 可以变成c中的实例化结构体，然后初始化
        return root;
    }
    if (val < root->val) // 如果小于根节点，插入左子树
    {
        root->left = insert(root->left, val);
    }
    else // 如果大于根节点，插入右子树
    {
        root->right = insert(root->right, val);
    }
    return root;
}

void preOrder(TreeNode *root) // 前序遍历
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->val);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(TreeNode *root) // 中序遍历
{
    if (root == NULL)
    {
        return;
    }
    inOrder(root->left);
    printf("%d ", root->val);
    inOrder(root->right);
}

void postOrder(TreeNode *root) // 后序遍历
{
    if (root == NULL)
    {
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%d ", root->val);
}

TreeNode *treeMaxinum(TreeNode *root) // 找最大值
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->right == NULL)
    {
        return root;
    }
    treeMaxinum(root->right);
}

TreeNode *treeMininum(TreeNode *root) // 找最小值
{
    if (root == NULL)
    {
        return NULL;
    }
    if (root->left == NULL)
    {
        return root;
    }
    treeMininum(root->left);
}

TreeNode *treeSearch(TreeNode *root, int val) // 查找节点
{
    if (root == NULL || root->val == val)
    {
        return root;
    }
    if (val < root->val)
    {
        return treeSearch(root->left, val);
    }
    else
    {
        return treeSearch(root->right, val);
    }
}

// TreeNode *TreePredecessor(TreeNode *root, int val) // 查找前驱
// {
//     TreeNode *res = TreeSearch(root, val); // 查找节点
//     if (res == NULL)
//     {
//         return NULL;
//     }
//     if (res->left != NULL) // 如果左子树不为空，那么前驱就是左子树的最大值
//     {
//         return TreeMaxinum(res->left);
//     }
//     TreeNode *pre = NULL;
//     // 如果左子树为空，那么就是从根节点到这个节点的路径上，最后一个比这个节点小的节点
//     // 也可以按照课本上的那种判断是否是左子树的方法，找第一个右子树上来的节点，那种方法要记录父节点，区别就在于一个是正向，一个是反向。实际上一样的。
//     // 其实在这种方法中，在找最后一个比查找值小的节点时已经在遍历了，所以其实不需要最开始的那个查找
//     while (root != NULL)
//     {
//         if (root->val < val)
//         {
//             pre = root; // 记录最后一个比查找值小的节点
//             root = root->right;
//         }
//         else if (root->val > val)
//         {
//             root = root->left;
//         }
//         else
//         {
//             break;
//         }
//     }
//     return pre;
// }

// 改写版本
TreeNode *treePredecessor(TreeNode *root, int val) // 查找前驱
{
    TreeNode *pre = NULL;
    // 如果左子树为空，那么就是从根节点到这个节点的路径上，最后一个比这个节点小的节点
    // 因为给的是值，而不是节点，所以反正要遍历一次，所以可能这样更快一些。还是遍历了一次，还不用储存父节点(节省了一个查找的过程)

    while (root != NULL)
    {
        if (root->val < val)
        {
            pre = root; // 记录最后一个比查找值小的节点
            root = root->right;
        }
        else if (root->val > val)
        {
            root = root->left;
        }
        else
        {
            break;
        }
    }

    if (root == NULL)
    {
        return NULL;
    }

    if (root->left != NULL) // 如果左子树不为空，那么前驱就是左子树的最大值
    {
        return treeMaxinum(root->left);
    }

    return pre;
}

// 原版
TreeNode *treeSuccessor(TreeNode *root, int val) // 查找后继
{
    TreeNode *res = treeSearch(root, val); // 查找节点
    if (res == NULL)
    {
        return NULL;
    }
    if (res->right != NULL) // 如果右子树不为空，那么后继就是右子树的最小值
    {
        return treeMininum(res->right);
    }
    TreeNode *suc = NULL; // 如果右子树为空，那么就是从根节点到这个节点的路径上，最后一个比这个节点大的节点
    while (root != NULL)
    {
        if (root->val < val)
        {
            root = root->right;
        }
        else if (root->val > val)
        {
            suc = root; // 记录最后一个比查找值大的节点
            root = root->left;
        }
        else
        {
            break;
        }
    }
    return suc;
}

int main()
{
    char import_str[1000];
    scanf("%s", import_str); // 读入字符串

    // 开始建树

    char *v_str;
    // strtok 用于分割字符串, 第一个参数是输入的字符串，第二个参数是分隔符号。返回分割后的字符串
    // strtok 会修改输入的字符串，要注意！！！
    // strtok 会把第一个字符串保存到一个静态缓冲区，然后后面再次调用这个函数的时候会沿用静态缓冲区的内容
    // 第一个参数为NULL的话就不会修改静态缓冲区的内容，而是沿用上一次的内容
    v_str = strtok(import_str, ","); // 用逗号分割字符串
    TreeNode *root = NULL;           // 根节点
    while (v_str != NULL)            // 遍历字符串
    {
        if (strcmp(v_str, "null") == 0) // 不能直接用 == , 否则变成的比较指针地址
        {
            v_str = strtok(NULL, ","); // 更新至下一个被分割的字符串
            continue;
        }

        int val = atoi(v_str);     // 字符串转换为整数
        root = insert(root, val);  // 插入节点
        v_str = strtok(NULL, ","); // 更新至下一个被分割的字符串
    }

    // 前序遍历
    preOrder(root);
    printf("\n");

    TreeNode *res;

    // 找最小值
    res = treeMininum(root);
    printf("%d\n", res->val);

    // 找最大值
    res = treeMaxinum(root);
    printf("%d\n", res->val);

    // 查找是否存在
    int n;
    scanf("%d", &n); // 读入要查找的值的个数

    for (int i = 0; i < n; i++)
    {
        int val;
        scanf("%d", &val);           // 读入要查找的值
        res = treeSearch(root, val); // 查找节点
        if (res == NULL)
        {
            printf("no\n");
        }
        else
        {
            printf("yes\n");
        }
    }

    int m;
    scanf("%d", &m); // 读入要查找的前驱和后继的个数
    for (int i = 0; i < m; i++)
    {
        int val;
        scanf("%d", &val); // 读入要查找的值

        TreeNode *pre = treePredecessor(root, val); // 查找前驱
        printf("%d\n", pre->val);

        TreeNode *suc = treeSuccessor(root, val); // 查找后继
        printf("%d\n", suc->val);
    }

    return 0;
}