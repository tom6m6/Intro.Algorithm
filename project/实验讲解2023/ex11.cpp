// References: https://blog.csdn.net/qq_43777729/article/details/103700382
// 里面的内容我记得有一定的问题（可能，记不清了）

#include <iostream>
#include <string>
#include <queue>   //其实也可以不用这个，队列的实现很简单
#include <iomanip> //用来控制格式化字符串的
using namespace std;

int sum = 0;     // 总长度
int sum_num = 0; // 总个数

class node
{
public:
    node(string con, int wht, node *left, node *right, string co) // 构造函数，c中没有构造函数，可以定义一个普通函数达到类似的效果
    {
        content = con;
        weight = wht;
        leftchild = left;
        rightchild = right;
        code = co;
    }
    string content;   // 字符
    int weight;       // 权重（频数，就是字符出现的个数）
    node *leftchild;  // 左孩子
    node *rightchild; // 右孩子
    string code;      // 编码完的code
};

void insertion_sort(node **array, int low, int high)
// 直接插入排序
// 不是最优解，只是简单，所以偷懒了一下。
// 堆应该更优
{
    for (int i = low + 1; i < high; i++)
    {
        node *tem = array[i];
        int j = i - 1;

        // 后面改成算平均长度了以后就不用考虑那些特殊情况了。
        while (j >= low && (array[j]->weight > tem->weight))
        // while(j >= low && array[j]->weight > tem->weight)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = tem;
    }
}

// 用来创建哈夫曼树的，s是字符，w是权重，n是字符个数，array是指针数组，用来保存结果
void create_huffman_tree(string *s, int *w, int n, node **array)
{
    // 创建原始的节点
    for (int i = 0; i < n; i++)
    {
        array[i] = new node(s[i], w[i], NULL, NULL, "");
    }
    // 保证优先队列，插入排序效率不高。堆应该更好
    insertion_sort(array, 0, n);
    int p = 0;
    while (p != n - 1)
    {
        // 选出最小的两个节点，合并成一个新的节点
        node *min_1 = array[p];     // 第一个最小的节点，而且第一个比下面的min_2更小（或者相等）
        node *min_2 = array[p + 1]; // 第二个最小的节点
        node *new_node;
        new_node = new node("", min_1->weight + min_2->weight, min_1, min_2, ""); // 创建新节点，小的在左子树，大的在右子树。
        // 因为后面改成了算平均长度，所以这里也不用考虑特殊情况了。
        array[p + 1] = new_node; // 把新节点放到数组里面，直接放进去就行了，因为后面反正是优先队列，会排序。
        p = p + 1;               // p指向下一个位置
        insertion_sort(array, 0, n);
        // 这种放法的话，数组最后一个元素一定是根节点后面只需要从最后一个元素开始遍历就行了。
        // 这里的array数组只是为了存储创建完的节点在哪。节点之前的关系并不通过这个array来维护，而是通过节点里面的那些字段来维护的。储存了所有的合成的节点。
    }
}

void create_huffman_code(node *p)
{
    // 这里是用队列来做的，其实也可以用二叉树的普通遍历方法来做
    // 队列保证了从上往下遍历，且所有节点都能遍历到。
    queue<node *> nq;
    nq.push(p); // 进队列
    while (nq.size() != 0)
    {
        node *cur = nq.front();
        nq.pop(); // 出队列
        node *l = cur->leftchild;
        node *r = cur->rightchild;

        // if (l != NULL && r != NULL && l->content == r->content && l->weight == r->weight)
        // {
        //     cout << "error" << endl;
        // }

        // 没到头就加编码
        if (l != NULL)
        {
            l->code = cur->code + "0";
            nq.push(l);
        }
        if (r != NULL)
        {
            r->code = cur->code + "1";
            nq.push(r);
        }

        // 到头了就累计字符长度和字符个数
        if (l == NULL && r == NULL)
        {
            sum += cur->weight * cur->code.length();
            sum_num += cur->weight;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    node **array = (node **)malloc(sizeof(node *) * n);
    string *s = new string[n];
    int *w = new int[n];
    // 输入
    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        cin >> w[i];
    }

    // 创建哈夫曼树
    create_huffman_tree(s, w, n, array);
    // 计算编码
    create_huffman_code(array[n - 1]);
    // 输出
    cout << fixed << setprecision(2) << (double)sum / sum_num << endl;

    free(array);
    delete[] s;
    delete[] w;
}