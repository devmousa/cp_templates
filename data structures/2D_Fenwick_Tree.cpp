#include <bitstdc++.h>
using namespace std;

// 1-indexed 2D Fenwick Tree
template <typename T>
struct FenwickTree2D
{
  int n, m;
  vector<vector<T>> fen;
  FenwickTree(int _n, int _m)
  {
    n = _n;
    m = _m;
    fen.assign(n + 1, vector<T>(m + 1, 0));
  }
  void add(int x, int y, int val)
  {
    for (int xx = x; xx <= n; xx += xx & -xx)
      for (int yy = y; yy <= m; yy += yy & -yy)
        fen[xx][yy] += val;
  }
  T get(int x, int y)
  {
    T res = 0;
    for (int xx = x; xx > 0; xx -= xx & -xx)
      for (int yy = y; yy > 0; yy -= yy & -yy)
        res += fen[xx][yy];
    return res;
  }
  T get(int x1, int y1, int x2, int y2)
  {
    return get(x2, y2) - get(x2, y1 - 1) - get(x1 - 1, y2) + get(x1 - 1, y1 - 1);
  }
};

int main()
{
  // simple usage
  FenwickTree2D<long long> fen(10, 100);
  fen.add(0, 20, 33);
  fen.add(1, 3, 100);
  fen.add(0, 1, 10);
  // output = 133
  cout << fen.get(1, 2, 21, 21) << '\n';
}