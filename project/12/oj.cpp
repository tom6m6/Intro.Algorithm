#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 1000000
struct Edge{
    int from,to,val;
}edge[MAXN];
int m,n;
int father[MAXN];
bool cmp(Edge x,Edge y){
    return x.val<y.val;
}
int find(int x){
    //有路径压缩的查询
    if(father[x]!=x)father[x]=find(father[x]);
    return father[x];
}
int main(){
    cin>>n>>m;
    for(int i=0;i<m;i++)cin>>(edge[i].from)>>(edge[i].to)>>(edge[i].val);
    
    
    //kruskal
    int ans=0,cnt=0;
    for(int i=1;i<=n;i++)father[i]=i;
    sort(edge,edge+m,cmp);
    int x,y;
    for(int i=0;i<m;i++){
        x=edge[i].from;y=edge[i].to;
        if(find(x)!=find(y)){
            father[find(x)]=find(y);
            ans+=edge[i].val;
            ++cnt;
            if(cnt==n-1)break;
        }
    }
    if(cnt==n-1)cout<<ans;
    return 0;
}