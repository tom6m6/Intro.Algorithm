class MultiArrayObject:
    def __init__(self):
        self.data = []  # 存储元素的数组
        self.next = []  # 存储每个元素的下一个节点的索引
        self.head = -1  # 链表头指针

    # 在指定位置插入元素
    def insert(self, index, val):
        if index < 0 or index > len(self.data):
            return
        self.data.insert(index, val)
        self.next.insert(index, -1)
        if index == 0:
            self.next[index] = self.head
            self.head = index
        else:
            self.next[index - 1] = index
            self.next[index] = self.next[index - 1]

    # 删除指定位置的元素
    def remove(self, index):
        if index < 0 or index >= len(self.data):
            return
        if index == self.head:
            self.head = self.next[index]
        else:
            curr = self.head
            while self.next[curr] != index:
                curr = self.next[curr]
            self.next[curr] = self.next[index]
        self.data.pop(index)
        self.next.pop(index)

    # 获取指定位置的元素
    def get(self, index):
        if index < 0 or index >= len(self.data):
            return -1
        return self.data[index]

    # 修改指定位置的元素
    def set(self, index, val):
        if index < 0 or index >= len(self.data):
            return
        self.data[index] = val

    # 对链表进行选择排序
    def selection_sort(self):
        for i in range(len(self.data) - 1):
            min_idx = i
            for j in range(i + 1, len(self.data)):
                if self.data[j] < self.data[min_idx]:
                    min_idx = j
            if min_idx != i:
                self.data[i], self.data[min_idx] = self.data[min_idx], self.data[i]
                self.next[i], self.next[min_idx] = self.next[min_idx], self.next[i]

# 主程序
N = int(input())
obj = MultiArrayObject()
for i in range(N):
    op = list(map(int, input().split()))
    if op[0] == 0:
        pos, val = op[1], op[2]
        obj.insert(pos, val)
        for j in range(len(obj.data)):
            print(obj.data[j],end=" ")
    elif op[0] == 1:
        pos = op[1]
        obj.remove(pos)
        for j in range(len(obj.data)):
            print(obj.data[j],end=" ")
    elif op[0] == 2:
        pos = op[1]
        print(obj.get(pos))
        for j in range(len(obj.data)):
            print(obj.data[j],end=" ")
    elif op[0] == 3:
        pos, val = op[1], op[2]
        obj.set(pos, val)
        for j in range(len(obj.data)):
            print(obj.data[j],end=" ")
    elif op[0] == 4:
        obj.selection_sort()
        for j in range(len(obj.data)):
            print(obj.data[j],end=" ")
