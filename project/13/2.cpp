#include <iostream>
#include <fstream>
#include <stack>
#include <cstring>
#include <map>
#define INF 100000005
using namespace std;
int graph[50][50], d[50], visit[50] = {0}, pre[50] = {0};
void find_path(int from, int to, int n){
    int flag = 0;
    for(int i = 0; i < n; i++) d[i] = INF;
    for(int i = 0; i < n; i++) visit[i] = 0;
    d[from] = 0;
    while (!flag){
        int min_dist = INF, min_idx = -1;
        for(int i = 0; i < n; i++){
            if (visit[i] == 0 && d[i] < min_dist){
                min_dist = d[i];
                min_idx = i;
            }
        }
        visit[min_idx] = 1;
        if(min_idx == to) break;
        for(int i = 0; i < n; i++){
            if (visit[i] == 0 && graph[min_idx][i] != INF){
                if(d[i] > d[min_idx] + graph[min_idx][i]) {
                    d[i] = d[min_idx] + graph[min_idx][i];
                    pre[i] = min_idx;
                }
            }
        }
        flag = 1;
        for (int i = 0; i < n; i++) {
            if (visit[i] == 0){
                flag = 0;
                break;
            }
        }
    }
}
int main() {
    ifstream fin("data.txt");
    stack<int> path;
    int tot_dist = 0;
    map<string, int> location_index;
    map<int, string> inv_location_index;
    int n = 0, start, mid, end;
    string start_city, mid_city, end_city;
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++) {
            graph[i][j] = INF;
            graph[j][i] = INF;
        }
    }

    while(!fin.eof()){
        string from, to;
        int from_index, to_index, distance, speed;
        fin>>from>>to>>distance>>speed;
        if (location_index.find(from) == location_index.end()){
            from_index = n;
            location_index[from] = from_index;
            inv_location_index[from_index] = from;
            n++;
        }
        else{
            from_index = location_index[from];
        }
        if (location_index.find(to) == location_index.end()){
            to_index = n;
            location_index[to] = to_index;
            inv_location_index[to_index] = to;
            n++;
        }
        else{
            to_index = location_index[to];
        }
        graph[from_index][to_index] = distance;
        graph[to_index][from_index] = distance;
    }
    start_city = "成都";
    mid_city = "理塘";
    end_city = "江达";
    start = location_index[start_city];
    mid = location_index[mid_city];
    end = location_index[end_city];
    find_path(mid, end, n);
    int cur = end;
    path.push(end);
    while(cur != mid){
        path.push(pre[cur]);
        cur = pre[cur];
    }
    tot_dist += d[end];
    find_path(start, mid, n);
    cur = pre[mid];
    path.push(pre[mid]);
    while(cur != start){
        path.push(pre[cur]);
        cur = pre[cur];
    }
    cout<<"Path:";
    while(!path.empty()){
        cout<<inv_location_index[path.top()];
        path.pop();
        if(!path.empty())cout<<">";
    }
    tot_dist += d[mid];
    cout<<endl;
    cout<<"Total: "<<tot_dist<<"km"<<endl;
    fin.close();
    return 0;
}
