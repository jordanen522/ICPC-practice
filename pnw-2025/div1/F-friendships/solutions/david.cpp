#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;

int n, q;
const int MAXTOYS = 51;
const int MAXN = 400002;
int toys[MAXN];
int friendtoys[MAXN][MAXTOYS];
int global[MAXTOYS];
vector<int> adj[MAXN];

void query(int u) {
  if (adj[u].size() == n-1) {
    cout << -1 << '\n';
    return;
  }
  for(int j=MAXTOYS-1;j>=0;j--) {
    int nonfriendtoys = global[j] - friendtoys[u][j] - (j==toys[u]);
    if (nonfriendtoys) {
      cout << j << '\n';
      return;
    }
  }
}
int main(){
  cin.tie(0); ios_base::sync_with_stdio(0);
  cin >> n >> q;
  global[0] = n;
  for(int i=0;i<q;i++) {
    string op;
    int u;
    cin >> op;
    if (op == "F") {
      int v;
      cin >> u >> v;
      friendtoys[u][toys[v]]++;
      friendtoys[v][toys[u]]++;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }
    if (op == "A") {
      cin >> u;
      // fix contribution to neighbors and global
      for(int v: adj[u]) {
        friendtoys[v][toys[u]]--;
        friendtoys[v][toys[u]+1]++;
      }
      global[toys[u]]--;
      toys[u]++;
      assert(toys[u]<=50);
      global[toys[u]]++;
    }
    if (op == "Q") {
      cin >> u;
      query(u);
    }
  }
}
