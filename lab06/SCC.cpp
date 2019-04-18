#include <vector>
#include <iostream>
#include <fstream>
using namespace std;
//Please put this source code in the same directory with scc.in
//And do NOT change the file name.
/*
This function computes the number of Strongly Connected Components in a graph
Args:
    n: The number of nodes in the graph. The nodes are indexed as 0~n-1
    edge: The edges in the graph. For each element (a,b) in edge, it means
          there is a directed edge from a to b
          Notice that there may exists multiple edge and self-loop
Return:
    The number of strongly connected components in the graph.
*/

int sink;
bool *alive;
bool *visited;

void EXPLORE(int n,vector<pair<int,int>>& edge){
    visited[n]=true;
    for(int i=0;i<edge.size();i++){
        if(edge[i].first==n && !visited[edge[i].second] && !alive[edge[i].second]){
            EXPLORE(edge[i].second,edge);
        }
    }
    sink=n;
}

void REMOVE(int n,vector<pair<int,int>>& edge){
    alive[n]=true;
    for(int i=0;i<edge.size();i++){
        if(edge[i].first==n && !alive[edge[i].second]){
            REMOVE(edge[i].second,edge);
        }
    }
}

void DFS(int n,vector<pair<int,int>>& edge){
    for(int i=0;i<n;i++){
        visited[i]=false;
    }
    for(int i=0;i<n;i++){
        if(!visited[i] && !alive[i]){
            //cout<<"!";
            EXPLORE(i, edge);
        }
    }
}

int SCC(int n, vector<pair<int,int>>& edge) {

    int res=0;
    alive=new bool[n];
    visited=new bool[n];

    for(int i=0;i<n;i++){
        alive[i]=false;
    }

    vector<pair<int,int>> redge;
    int tmp3,tmp4;
    for(int i=0;i<edge.size();i++){
        tmp3=edge[i].first;
        tmp4=edge[i].second;
        redge.push_back(pair<int,int>(tmp4,tmp3));
    }

    for(int i=0;i<n;i++){
        DFS(n,redge);
        cout<<sink<<'\n';
        if(alive[sink]==false){
            res++;
        }
        REMOVE(sink,edge);
    }

    return res;
}
//Please do NOT modify anything in main(). Thanks!
int main()
{
    int m,n;
    vector<pair<int,int>> edge;
    ifstream fin;
    ofstream fout;
    fin.open("scc.in");
    fin>>n>>m;
    int tmp1,tmp2;
    for(int i=0;i<m;i++)
    {
        fin>>tmp1>>tmp2;
        edge.push_back(pair<int,int>(tmp1,tmp2));
    }
    fin.close();
    int ans=SCC(n,edge);
    fout.open("scc.out");
    fout<<ans<<'\n';
    fout.close();
    return 0;
}
