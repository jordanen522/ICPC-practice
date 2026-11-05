#include<cstdio>
#include<vector>
#include<queue>
using namespace std;
using ll = long long;
const ll inf = 1LL<<50;
int n;
struct edge
{
    int a, b;
    ll d;
    bool is_cycle;
    edge(){}
    edge(int a, int b, ll d):a(a),b(b),d(d),is_cycle(false){}
};
vector<edge> edges;
vector<vector<int>> adj;
vector<int> cycle_nodes;
vector<ll> rdist; // distance from each root
vector<ll> u1dist, u2dist; // distance measured from tree diameter endpoints
vector<int> pedge; // parent edge from each subtree
vector<ll> mdist;
void find_cycle()
{
    vector<int> depth(n, -1);
    vector<int> parent(n, -1);
    vector<int> parent_edge(n, -1);
    queue<int> q;
    q.push(0);
    depth[0] = 0;
    while(!q.empty())
    {
        int cur = q.front(); q.pop();
        for(int ei: adj[cur])
        {
            int nxt = edges[ei].a ^ edges[ei].b ^ cur;
            if(parent_edge[cur] == ei) continue;
            if(parent_edge[nxt] == -1)
            {
                parent_edge[nxt] = ei;
                parent[nxt] = cur;
                depth[nxt] = depth[cur]+1;
                q.push(nxt);
            }
            else
            {
                edges[ei].is_cycle = true;
                vector<int> alt_path;
                int c1 = cur, c2 = nxt;
                while(depth[c1] > depth[c2])
                {
                    edges[parent_edge[c1]].is_cycle = true;
                    cycle_nodes.push_back(c1);
                    c1 = parent[c1];
                }
                while(depth[c1] < depth[c2])
                {
                    edges[parent_edge[c2]].is_cycle = true;
                    alt_path.push_back(c2);
                    c2 = parent[c2];
                }
                while(c1 != c2)
                {
                    edges[parent_edge[c1]].is_cycle = edges[parent_edge[c2]].is_cycle = true;
                    cycle_nodes.push_back(c1);
                    alt_path.push_back(c2);
                    c1 = parent[c1];
                    c2 = parent[c2];
                }
                // c1==c2 is common ancestor
                cycle_nodes.push_back(c1);
                while(alt_path.size())
                {
                    cycle_nodes.push_back(alt_path.back());
                    alt_path.pop_back();
                }
                return;
            }
        }
    }
}
void process_subtree(int r, vector<int>& q)
{
    auto bfs = [&](int r, vector<ll>& dist)
    {
        q.clear();
        q.push_back(r); dist[r]=0;
        int u=r; // index of farthest node from r
        for(int hd=0;hd<q.size();hd++)
        {
            int cur = q[hd];
            if(dist[cur] > dist[u]) u=cur;
            for(int ei: adj[cur])
            {
                if(edges[ei].is_cycle) continue;
                int nxt = edges[ei].a ^ edges[ei].b ^ cur;
                if(dist[nxt] != -1) continue;
                dist[nxt] = dist[cur] + edges[ei].d;
                pedge[nxt] = ei;
                q.push_back(nxt);
            }
        }
        return u;
    };
    int u1 = bfs(r, rdist);
    for(int i=q.size()-1;i>=0;i--)
    {
        int cur = q[i];
        if(pedge[cur]!=-1)
        {
            int par=edges[pedge[cur]].a ^ edges[pedge[cur]].b ^ cur;
            mdist[par] = max(mdist[par], mdist[cur] + edges[pedge[cur]].d);
        }
    }
    int u2 = bfs(u1, u1dist);
    bfs(u2, u2dist);
}
ll getmax(const vector<ll>& tree, int sp, int L, int R)
{
    ll res = -inf;
    L+=sp; R+=sp;
    while(L<=R)
    {
        if((L%2)==1) res = max(res, tree[L++]);
        if((R%2)==0) res = max(res, tree[R--]);
        L>>=1; R>>=1;
    }
    return res;
}
int main()
{
    scanf("%d", &n);
    adj.resize(n);
    for(int i=1;i<=n;i++)
    {
        int a, b; ll d; scanf("%d%d%lld", &a, &b, &d);
        a--; b--;
        edges.emplace_back(a, b, d);
        adj[a].push_back(edges.size()-1);
        adj[b].push_back(edges.size()-1);
    }

    find_cycle();
    int C = cycle_nodes.size();

    pedge.resize(n, -1);
    rdist.resize(n, -1);
    u1dist.resize(n, -1);
    u2dist.resize(n, -1);
    mdist.resize(n, 0);

    // compute internal tree distances
    vector<vector<int>> node_groups(C);
    for(int i=0;i<C;i++)
    {
        int r = cycle_nodes[i];
        process_subtree(r, node_groups[i]);
    }

    vector<ll> cycle_edge_length;
    for(int i=0;i<C;i++)
    {
        int cur = cycle_nodes[i];
        int nxt = cycle_nodes[(i+1)%C];
        for(int ei: adj[cur])
        {
            auto &e = edges[ei];
            if((e.a==cur && e.b==nxt) || (e.b==cur && e.a==nxt)) {
                cycle_edge_length.push_back(e.d); break;
            }
        }
    }

    // segtree
    vector<ll> rsum{0};
    int sp=1;
    while(sp<C*3) sp<<=1;
    for(int i=0;i<C*3;i++)
        rsum.push_back(rsum.back() + cycle_edge_length[i%C]);
    vector<ll> ltree(sp*2, -inf), rtree(sp*2, -inf);
    for(int i=0;i<C*3;i++)
    {
        ll nd = mdist[cycle_nodes[i%C]];
        ltree[sp+i] = nd-rsum[i];
        rtree[sp+i] = nd+rsum[i];
    }
    for(int i=sp-1;i>=1;i--)
    {
        ltree[i] = max(ltree[i*2], ltree[i*2+1]);
        rtree[i] = max(rtree[i*2], rtree[i*2+1]);
    }
    vector<ll> ext_maxpath(C, -inf);
    for(int c=0, L=0, mid=C;c<C;c++, mid++)
    {
        while(rsum[mid]-rsum[L] >= rsum[L+C]-rsum[mid]) L++;
        ll lmax = getmax(ltree, sp, L, mid-1)+rsum[mid];
        ll rmax = getmax(rtree, sp, mid+1, L+C-1)-rsum[mid];
        ext_maxpath[c] = max(lmax, rmax);
    }

    // combine answers
    vector<ll> ans(n);
    for(int c=0;c<C;c++)
        for(int v: node_groups[c])
            ans[v] = max(max(u1dist[v], u2dist[v]), max(mdist[v], ext_maxpath[c]+rdist[v]));
    for(int i=0;i<n;i++)
        printf("%lld ", ans[i]);
    printf("\n");
    return 0;
}
