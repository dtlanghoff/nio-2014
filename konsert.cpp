#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

int cost(const vector<int>& x, const vector<int>& y, const vector<int>& b, int src, int dest) {
  if (src == 0)
    return abs(x[dest]) + abs(y[dest]) + b[dest];
  else
    return abs(x[src]-x[dest]) + abs(y[src]-y[dest]) + b[dest];
}

int main() {
  int k = 0;
  int n, t;
  cin >> n >> t;

  vector<int> x(n), y(n), b(n);
  for (int i = 1; i <= n; i++)
    cin >> x[i] >> y[i] >> b[i];

  vector< vector<int> > dp(n+1, vector<int>(n+1));

  for (int s = 1; s <= n; s++) {
    dp[1][s] = cost(x, y, b, 0, s);
    if (dp[1][s] <= t)
      k = 1;
  }

  for (int l = 2; l <= n; l++) {
    for (int s = l; s <= n; s++) {
      int m = numeric_limits<int>::max();
      for (int n = l-1; n < s; n++)
        m = min(m, dp[l-1][n] + cost(x, y, b, n, s));
      dp[l][s] = m;
      if (dp[l][s] <= t)
        k = l;
    }
  }

  cout << k << endl;

  return 0;
}
