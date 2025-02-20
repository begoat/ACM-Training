#include <cmath>
#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

const int MAXN = 200;
const double EPS = 1e-10;
const double INF = 1e99;

struct Point {
  double x, y;
  Point() { }
  Point(double x, double y) : x(x), y(y) { }
  double abs() const { return hypot(x, y); }
  Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
  Point operator-(const Point& o) const { return Point(x - o.x, y - o.y); }
  Point operator*(const double o) const { return Point(x * o, y * o); }
  double operator*(const Point& o) const { return x * o.y - y * o.x; }
};

double intersection(const Point& u1, const Point& u2, const Point& v1, const Point& v2) {
  // return u1 + (u2 - u1) * (((u1 - v1) * (v1 - v2)) / ((u1 - u2) * (v1 - v2)));
  double a = (u1 - v1) * (v1 - v2);
  double b = (u1 - u2) * (v1 - v2);
  if (fabs(b) < EPS) {
    return INF;
  } else {
    a /= b;
    return a < 1 - EPS ? INF : a - 1;
  }
}

Point p[MAXN], q[MAXN];

double dis(const Point& u1, const Point& u2) {
  double ret = INF;
  for (int i = 0; i < 4; ++i) {
    ret = min(ret, intersection(u1, u2, q[i], q[i + 1]));
  }
  return ret;
}

double dp[MAXN][MAXN];

double gao(int n, int l, int r) {
  double& ret = dp[l][r];
  if (ret >= 0) {
    return ret;
  } else if (l == r) {
    return ret = 0;
  } else {
    ret = INF;
    if (r < l) {
      r += n;
    }
    for (int m = l; m < r; ++m) {
      const Point& p1 = p[m % n];
      const Point& p2 = p[(m + 1) % n];
      double left = min(dis(p2, p1), intersection(p2, p1, p[(l + n - 1) % n], p[l % n]));
      double right = min(dis(p1, p2), intersection(p1, p2, p[r % n], p[(r + 1) % n]));
      ret = min(ret, (p2 - p1).abs() * (1 + left + right) +
        gao(n, l, m % n) + gao(n, (m + 1) % n, r % n));
    }
    // printf("gao[%d][%d] = %lf\n", l, r, ret);
    return ret;
  }
}

int main() {
  int n, w, h;
  double ans;
  int maxw = 0, maxh = 0, maxn = 0;

  while (scanf("%d%d%d", &n, &w, &h) != EOF) {
    q[0] = Point(0, 0);
    q[1] = Point(w, 0);
    q[2] = Point(w, h);
    q[3] = Point(0, h);
    q[4] = q[0];
    maxn = max(maxn, n);
    maxw = max(maxw, w);
    maxh = max(maxh, h);
    for (int i = 0; i < n; ++i) {
      scanf("%lf%lf", &p[i].x, &p[i].y);
      assert(0.5 < p[i].x && p[i].x < w - 0.5 && 0.5 < p[i].y && p[i].y < h - 0.5);
    }
    p[n] = p[0];

    fill(dp[0], dp[n], -1.0);
    ans = INF;
    for (int i = 0; i < n; ++i) {
      double tmp = 1 + dis(p[i + 1], p[i]) + dis(p[i], p[i + 1]);
      tmp *= (p[i + 1] - p[i]).abs();
      tmp += gao(n, (i + 1) % n, i);
      // printf("%lf\n", tmp);
      ans = min(ans, tmp);
    }
    printf("%.6lf\n", ans);
  }

  return 0;
}

