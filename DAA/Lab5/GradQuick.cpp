#include <string.h>
#include <queue>
#include <stdio.h>
using namespace std;
int main(){
  int n= 9;
  int how_many_out[n]= {0, 1, 2, 0, 1, 0, 2, 0, 2};
  int adjList[][n]= {
    {},
    {2},
    {3, 7},
    {},
    {5},
    {},
    {4, 5},
    {},
    {1, 3}
  };
  int how_many_in[n]={0};
  for (int i=0; i<n; ++i)
    for(int j=0; j<how_many_out[i]; ++j)
      how_many_in[adjList[i][j]]++;
  queue<int> q;
  for (int i=0; i<n; ++i)
    if(how_many_in[i] == 0)
      q.push(i);
  int u, v, semesters=0;
  while(q.size()){
    int qn=q.size();
    for(int k=0; k<qn; ++k){
      u= q.front();
      q.pop();
      for(int i=0; i<how_many_out[u]; ++i){
        v= adjList[u][i];
        how_many_in[v]--;
        if(how_many_in[v] == 0)
          q.push(v);
      }
    }
    semesters++;
  }
  printf("%d\n", semesters);
}
