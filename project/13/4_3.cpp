#include <iostream>
#include <fstream>
#include <stack>
#include <cstring>
#include <map>
#define INF 100000005
using namespace std;
int graph_dist[50][50], visit[50] = {0}, pre[50] = {0};
double graph[50][50],d[50];
void find_path(int from, int to, int n){
    int flag = 0;
    for(int i = 0; i < n; i++) d[i] = INF;
    for(int i = 0; i < n; i++) visit[i] = 0;
    d[from] = 0;
    while (!flag){
        double min_dist = INF;
        int min_idx = -1;
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
    stack<int> path_1, path_2;
    double tot_time_1 = 0.0, tot_time_2 = 0.0;
    int tot_dist_1 = 0, tot_dist_2 = 0;
    map<string, int> location_index;
    map<int, string> inv_location_index;
    int n = 0, start, mid_1, mid_2, end;
    string start_city, mid_city_1, mid_city_2, end_city;
    for(int i = 0; i < 50; i++){
        for(int j = 0; j < 50; j++) {
            graph[i][j] = INF;
            graph[j][i] = INF;
            graph_dist[i][j] = INF;
            graph_dist[j][i] = INF;
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
        graph[from_index][to_index] = (double)distance / speed;
        graph[to_index][from_index] = (double)distance / speed;
        graph_dist[from_index][to_index] = distance;
        graph_dist[to_index][from_index] = distance;
    }
    start_city = "成都";
    mid_city_1 = "理塘";
    mid_city_2 = "道孚";
    end_city = "江达";
    start = location_index[start_city];
    mid_1 = location_index[mid_city_1];
    mid_2 = location_index[mid_city_2];
    end = location_index[end_city];
    //Find path 1
    find_path(mid_1, end, n);
    int cur = end;
    path_1.push(end);
    while(cur != mid_1){
        path_1.push(pre[cur]);
        tot_dist_1 += graph_dist[cur][pre[cur]];
        cur = pre[cur];
    }
    tot_time_1 += d[end];
    find_path(start, mid_1, n);
    cur = pre[mid_1];
    path_1.push(pre[mid_1]);
    while(cur != start){
        path_1.push(pre[cur]);
        tot_dist_1 += graph_dist[cur][pre[cur]];
        cur = pre[cur];
    }
    tot_dist_1 += graph_dist[mid_1][pre[mid_1]];
    tot_time_1 += d[mid_1];
    //Find path 2
    find_path(mid_2, end, n);
    cur = end;
    path_2.push(end);
    while(cur != mid_2){
        path_2.push(pre[cur]);
        tot_dist_2 += graph_dist[cur][pre[cur]];
        cur = pre[cur];
    }
    tot_time_2 += d[end];
    find_path(start, mid_2, n);
    cur = pre[mid_2];
    path_2.push(pre[mid_2]);
    while(cur != start){
        path_2.push(pre[cur]);
        tot_dist_2 += graph_dist[cur][pre[cur]];
        cur = pre[cur];
    }
    tot_dist_2 += graph_dist[mid_2][pre[mid_2]];
    tot_time_2 += d[mid_2];

    if(tot_time_1 <= tot_time_2){
        cout<<"途径 理塘"<<endl;
        cout<<"Path:";
        while(!path_1.empty()){
            int p = path_1.top();
            cout<<inv_location_index[p];
            path_1.pop();
            if(!path_1.empty())cout<<">";
        }
        cout<<endl;
        cout<<"Total Time: "<<tot_time_1<<"h"<<endl;
        cout<<"Total Dist: "<<tot_dist_1<<"km"<<endl;
    }
    else{
        cout<<"途径 道孚"<<endl;
        cout<<"Path:";
        while(!path_2.empty()){
            int p = path_2.top();
            cout<<inv_location_index[p];
            path_2.pop();
            if(!path_2.empty())cout<<">";
        }
        cout<<endl;
        cout<<"Total Time: "<<tot_time_2<<"h"<<endl;
        cout<<"Total Dist: "<<tot_dist_2<<"km"<<endl;
    }
    fin.close();
    return 0;
}