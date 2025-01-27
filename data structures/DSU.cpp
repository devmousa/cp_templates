#include <bitstdc++.h>
using namespace std;

struct DSU
{
  int n;
  vector<int> par, sz;
  DSU(int _n)
  {
    n = _n;
    par.resize(n);
    sz.assign(n, 1);
    for (int i = 0; i < n; i++)
      par[i] = i;
  }
  int find(int u)
  {
    if(par[u] == u)
      return u;
    return par[u] = find(par[u]);
  }
  bool same(int u, int v)
  {
    return find(u) == find(v);
  }
  bool unite(int u, int v)
  {
    u = find(u);
    v = find(v);
    // not united
    if (u == v)
      return false;
    if (sz[u] > sz[v])
      swap(u, v);
    sz[v] += sz[u];
    par[u] = v;
    // united
    return true;
  }
};

int main()
{
  // simple usage
  DSU a(5);
  a.unite(0, 1);
  if(a.same(0, 2))
    cout << "0 and 2 are in the same group\n";
  a.unite(2, 4);
  if(a.same(2, 4))
    cout << "2 and 4 are in the same group\n";
  if(a.unite(1, 3))
    cout << "1 and 3 got united\n";
  if(not a.unite(0, 1))
    cout << "0 and 1 are already united!\n";
}