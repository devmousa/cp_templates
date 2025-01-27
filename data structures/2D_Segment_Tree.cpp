#include <bitstdc++.h>
using namespace std;

struct SegmentTree2D
{
  int n, m, to;
  int n2, m2;
  long long init;
  vector<vector<long long>> seg;
  vector<vector<int>> a;
  function<long long(long long, long long)> func;
  void build(int tr, int dr, int lc, int rc, int t1, int t2)
  {
    if (tr == dr)
    {
      if (lc == rc)
      {
        if (tr >= n2 or lc >= m2)
          return;
        seg[t1][t2] = a[tr][lc];
        return;
      }
      int md = (lc + rc) / 2;
      build(tr, dr, lc, md, t1, t2 * 2);
      build(tr, dr, md + 1, rc, t1, t2 * 2 + 1);
      seg[t1][t2] = func(seg[t1][t2 * 2], seg[t1][t2 * 2 + 1]);
      return;
    }
    int md = (tr + dr) / 2;
    build(tr, md, lc, rc, t1 * 2, t2);
    build(md + 1, dr, lc, rc, t1 * 2 + 1, t2);
    for (int i = 0; i < (int)seg[t1].size(); i++)
    {
      seg[t1][i] = func(seg[t1 * 2][i], seg[t1 * 2 + 1][i]);
    }
  }
  void initialization(vector<vector<int>> _a, long long _init, function<long long(long long, long long)> _func)
  {
    init = _init;
    func = _func;
    a = _a;
    n = (int)a.size();
    m = (int)a[0].size();
    n2 = n;
    m2 = m;

    n = 1 << (__lg(n - 1) + 1);
    m = 1 << (__lg(m - 1) + 1);
    a.resize(n);
    for (auto &i : a)
      i.resize(m);
    // cout << func(1, 1e9) << '\n';
    seg.assign(n * 2, vector<long long>(m * 2, init));
    build(0, n - 1, 0, m - 1, 1, 1);
  }
  void initialization(int _n, int _m, long long _init, function<long long(long long, long long)> _func)
  {
    init = _init;
    func = _func;
    n = _n;
    m = _m;
    n2 = n;
    m2 = m;

    n = 1 << (__lg(n - 1) + 1);
    m = 1 << (__lg(m - 1) + 1);
    a.resize(n);
    for (auto &i : a)
      i.resize(m);
    seg.assign(n * 2, vector<long long>(m * 2, init));
  }
  void update(int x, int y, int val, int tr, int dr, int lc, int rc, int t1, int t2)
  {
    if (tr == dr)
    {
      if (lc == rc)
      {
        to = t2;
        seg[t1][t2] = val;
        return;
      }
      int md = (lc + rc) / 2;
      if (y <= md)
        update(x, y, val, tr, dr, lc, md, t1, t2 * 2);
      else
        update(x, y, val, tr, dr, md + 1, rc, t1, t2 * 2 + 1);
      seg[t1][t2] = func(seg[t1][t2 * 2], seg[t1][t2 * 2 + 1]);
      return;
    }
    int md = (tr + dr) / 2;
    if (x <= md)
      update(x, y, val, tr, md, lc, rc, t1 * 2, t2);
    else
      update(x, y, val, md + 1, dr, lc, rc, t1 * 2 + 1, t2);
    for (int i = to; i > 0; i >>= 1)
      seg[t1][i] = func(seg[t1 * 2][i], seg[t1 * 2 + 1][i]);
  }
  void update(int x, int y, int val)
  {
    update(x, y, val, 0, n - 1, 0, m - 1, 1, 1);
  }
  long long query(int r1, int r2, int c1, int c2, int tr, int dr, int lc, int rc, int t1, int t2)
  {
    if (r2 < tr or dr < r1)
      return init;
    if (r1 <= tr and dr <= r2)
    {
      if (c2 < lc or rc < c1)
        return init;
      if (c1 <= lc and rc <= c2)
        return seg[t1][t2];
      int md = (lc + rc) / 2;
      return func(
          query(r1, r2, c1, c2, tr, dr, lc, md, t1, t2 * 2),
          query(r1, r2, c1, c2, tr, dr, md + 1, rc, t1, t2 * 2 + 1));
    }
    int md = (tr + dr) / 2;
    return func(
        query(r1, r2, c1, c2, tr, md, lc, rc, t1 * 2, t2),
        query(r1, r2, c1, c2, md + 1, dr, lc, rc, t1 * 2 + 1, t2));
  }
  long long query(int r1, int r2, int c1, int c2)
  {
    return query(r1, r2, c1, c2, 0, n - 1, 0, m - 1, 1, 1);
  }
};

int main()
{
  // simple usage
  // being lazy right now to write examples or change the code (altought it is easy lol)
  // it has to be more customizable, like adding a datatype to make it usable for complicated cases
  // and making it 2D Lazy Segment Tree
}