#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct SegmentTree
{
  int n;
  vector<int> a;
  vector<T> seg;
  T combine(int a, int b)
  {
    return max(a, b);
  }
  void build(int l, int r, int v)
  {
    if (l == r)
    {
      seg[v] = a[l];
      return;
    }
    int md = (l + r) / 2;
    build(l, md, v * 2);
    build(md + 1, r, v * 2 + 1);
    seg[v] = combine(seg[v * 2], seg[v * 2 + 1]);
  }
  SegmentTree(vector<int> b)
  {
    n = SZ(b);
    a = b;
    seg.resize(n * 4);
    build(0, n - 1, 1);
  }
  void update(int idx, int val, int tl, int tr, int v)
  {
    if (tl == tr)
    {
      seg[v] = val;
      return;
    }
    int md = (tl + tr) / 2;
    if (md >= idx)
    {
      update(idx, val, tl, md, v * 2);
    }
    else
    {
      update(idx, val, md + 1, tr, v * 2 + 1);
    }
    seg[v] = combine(seg[v * 2], seg[v * 2 + 1]);
  }
  void update(int idx, T val)
  {
    update(idx, val, 0, n - 1, 1);
  }
  T query(int l, int r, int tl, int tr, int v)
  {
    if (tr < l or r < tl)
    {
      return 0;
    }
    if (l <= tl and tr <= r)
    {
      return seg[v];
    }
    int md = (tl + tr) / 2;
    return combine(query(l, r, tl, md, v * 2), query(l, r, md + 1, tr, v * 2 + 1));
  }
  T query(int l, int r)
  {
    return query(l, r, 0, n - 1, 1);
  }
};

int main()
{
    // no use for now
}