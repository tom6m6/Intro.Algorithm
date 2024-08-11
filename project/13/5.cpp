#include <iostream>
#include <fstream>
#include <stack>
#include <cstring>
#include <map>
#include <ctime>
#define INF 100000005
using namespace std;
int graph[50][50], d1[50], d2[50], visit_1[50], visit_2[50], pred_1[50] = {0}, pred_2[50] = {0}, inter_idx;
void find_path(int from, int to, int n){
    int flag = 0;
    for(int i = 0; i < n; i++) d1[i] = INF;
    for(int i = 0; i < n; i++) d2[i] = INF;
    for(int i = 0; i < n; i++) visit_1[i] = 0;
    for(int i = 0; i < n; i++) visit_2[i] = 0;
    d1[from] = 0;
    d2[to] = 0;
    while (!flag){
        int min_dist_1 = INF, min_dist_2 = INF, min_idx_1 = -1, min_idx_2 = -1;
        for(int i = 0; i < n; i++){
            if (visit_1[i] == 0 && d1[i] < min_dist_1){
                min_dist_1 = d1[i];
                min_idx_1 = i;
            }
        }
        visit_1[min_idx_1] = 1;

        for(int i = 0; i < n; i++){
            if (visit_2[i] == 0 && d2[i] < min_dist_2){
                min_dist_2 = d2[i];
                min_idx_2 = i;
            }
        }
        visit_2[min_idx_2] = 1;

        if(visit_1[min_idx_2] == 1 || visit_2[min_idx_1] == 1) {
            inter_idx = visit_1[min_idx_2] ? min_idx_2 : min_idx_1;
            break;
        }
        if(min_idx_1 == to || min_idx_2 == from) break;
        for(int i = 0; i < n; i++){
            if (visit_1[i] == 0 && graph[min_idx_1][i] != INF){
                if(d1[i] > d1[min_idx_1] + graph[min_idx_1][i]) {
                    d1[i] = d1[min_idx_1] + graph[min_idx_1][i];
                    pred_1[i] = min_idx_1;
                }
            }
        }
        for(int i = 0; i < n; i++){
            if (visit_2[i] == 0 && graph[min_idx_2][i] != INF){
                if(d2[i] > d2[min_idx_2] + graph[min_idx_2][i]) {
                    d2[i] = d2[min_idx_2] + graph[min_idx_2][i];
                    pred_2[i] = min_idx_2;
                }
            }
        }
        flag = 1;
        for (int i = 0; i < n; i++) {
            if (visit_1[i] == 0 || visit_2[i] == 0){
                flag = 0;
                break;
            }
        }
    }
}
int main() {
    double startTime,endTime;
    ifstream fin("data.txt");
    stack<int> path;
    map<string, int> location_index;
    map<int, string> inv_location_index;
    int n = 0, start, end, flag = 0, tot_dist = 0;
    string start_city, end_city;
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
    end_city = "江达";
    start = location_index[start_city];
    end = location_index[end_city];

    //startTime=clock();
    find_path(start, end, n);
    //endTime=clock();
    //cout<<"It takes "<<1000000*(endTime-startTime) / CLOCKS_PER_SEC<<"微秒"<<endl;

    int cur = inter_idx;
    path.push(inter_idx);
    while(cur != start){
        path.push(pred_1[cur]);
        cur = pred_1[cur];
    }
    tot_dist += d1[inter_idx];
    cout<<"Path:";
    while(!path.empty()) {
        cout << inv_location_index[path.top()];
        if(!path.empty())cout<<">";
        path.pop();
    }
    cur = inter_idx;
    while(cur != end){
        cout<<inv_location_index[pred_2[cur]];
        if(pred_2[cur]!=end)cout<<">";
        cur = pred_2[cur];
    }
    tot_dist += d2[inter_idx];
    cout<<endl;
    cout<<"Total: "<<tot_dist<<"km"<<endl;
    fin.close();

    return 0;
}
