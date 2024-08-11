#include <iostream>
#include <fstream>
#include <cmath>
#include <cstring>
#define R 6371.004 //平均半径
#define SUP 100000000
using namespace std;
struct city{
    string name;
    double longitude,latitude;
};
struct edge{
    int from,to;
    double val;
};
double rad(double angle){return angle * M_PI / 180;}
double earth_dist(city *pos_a, city *pos_b){
    double long_a = rad(pos_a->longitude);double lat_a = rad(pos_a->latitude);
    double long_b = rad(pos_b->longitude);double lat_b = rad(pos_b->latitude);
    double c = sin(lat_a) * sin(lat_b) + cos(lat_a) * cos(lat_b) * cos(long_b - long_a);
    return R * acos(c);
}
city c[50];
double graph[50][50] = {SUP};
int visit[50] = {0};
int n = 0;
edge choose[50], low_cost[50];
int main() {
    int xi_ning_idx, zheng_zhou_idx,hang_zhou_idx, chang_sha_idx;
    ifstream fin("data.txt");
    while (!fin.eof()){
        fin>>c[n].name>>c[n].longitude>>c[n].latitude;
        if (c[n].name == "西宁市") xi_ning_idx = n;
        else if (c[n].name == "郑州市") zheng_zhou_idx = n;
        else if (c[n].name == "杭州市") hang_zhou_idx = n;
        else if (c[n].name == "长沙市") chang_sha_idx = n;
        n++;
    }
    fin.close();
    //Build
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i == j) graph[i][j] = 0;
            else {
                double dist = earth_dist(&c[i], &c[j]);
                graph[i][j] = dist;graph[j][i] = dist;
            }
        }
    }
    int last_vis;
    int cnt=0;int flag=0;
    for(int i = 0; i < n; i++)low_cost[i] = {-1, -1, SUP};
    choose[0].from = xi_ning_idx;
    choose[0].to = zheng_zhou_idx;
    choose[0].val = graph[xi_ning_idx][zheng_zhou_idx];
    ++cnt;
    visit[xi_ning_idx] = 1;
    visit[zheng_zhou_idx] = 1;
    last_vis = xi_ning_idx;
    for(int i = 0; i < n; i++){
        if(visit[i] == 0 && graph[last_vis][i] < low_cost[i].val){
            low_cost[i].from = last_vis;
            low_cost[i].to = i;
            low_cost[i].val = graph[last_vis][i];
        }
    }
    last_vis = zheng_zhou_idx;
    while (!flag){
        flag = 1;
        //Update
        for(int i = 0; i < n; i++){
            if(visit[i] == 0 && graph[last_vis][i] < low_cost[i].val){
                low_cost[i].from = last_vis;
                low_cost[i].to = i;
                low_cost[i].val = graph[last_vis][i];
            }
        }
        int min_edge_idx = -1;
        double min_edge_dist = SUP;
        //Search
        for (int i = 0; i < n; i++) {
            if(low_cost[i].val != -1.0 && low_cost[i].val < min_edge_dist){
                min_edge_dist = low_cost[i].val;
                min_edge_idx = i;
            }
        }
        choose[cnt] = low_cost[min_edge_idx];
        visit[min_edge_idx] = 1;
        low_cost[min_edge_idx] = {-1, -1, -1.0};
        last_vis = min_edge_idx;
        cnt++;
        //特判
        if(last_vis == hang_zhou_idx && visit[chang_sha_idx] == 0){
            choose[cnt].from = hang_zhou_idx;
            choose[cnt].to = chang_sha_idx;
            choose[cnt].val = graph[hang_zhou_idx][chang_sha_idx];
            visit[chang_sha_idx] = 1;
            low_cost[chang_sha_idx] = {-1, -1, -1.0};
            for(int i = 0; i < n; i++){
                if(visit[i] == 0 && graph[last_vis][i] < low_cost[i].val){
                    low_cost[i].from = last_vis;
                    low_cost[i].to = i;
                    low_cost[i].val = graph[last_vis][i];
                }
            }
            cnt++;
            last_vis = chang_sha_idx;
        }
        else if(last_vis == chang_sha_idx && visit[hang_zhou_idx] == 0){
            choose[cnt].from = chang_sha_idx;
            choose[cnt].to = hang_zhou_idx;
            choose[cnt].val = graph[chang_sha_idx][hang_zhou_idx];
            visit[hang_zhou_idx] = 1;
            low_cost[hang_zhou_idx] = {-1, -1, -1.0};
            for(int i = 0; i < n; i++){
                if(visit[i] == 0 && graph[last_vis][i] < low_cost[i].val){
                    low_cost[i].from = last_vis;
                    low_cost[i].to = i;
                    low_cost[i].val = graph[last_vis][i];
                }
            }
            cnt++;
            last_vis = hang_zhou_idx;
        }
        for(int i = 0; i < n; i++){
            if(visit[i] == 0){
                flag = 0;
                break;
            }
        }
    }
    double sum = 0.0;
    for(int i = 0; i < cnt; i++){
        cout<<c[choose[i].from].name<<"<>"<<c[choose[i].to].name<<" "<<choose[i].val<<"KM"<<endl;
        sum += choose[i].val;
    }
    /*
    for(int i = 0; i < cnt; i++){
        cout<<"('"<<c[choose[i].from].name<<"','"<<c[choose[i].to].name<<"',"<<choose[i].val<<"),"<<endl;
    }
    */
    cout<<"SUM LEN: "<<sum<<"km"<<endl;
    return 0;
}
