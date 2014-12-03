#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int nearest(vector<int>& h, int p) {
  int a = 0, b = h.size()-1;
  while (b-a > 1) {
    int c = (b+a) / 2;
    if (h[c] > p)
      b = c;
    else
      a = c;
  }
  return min(abs(h[a]-p), abs(h[b]-p));
}

int main() {
  int n, t;
  cin >> n >> t;

  vector<int> p(n);
  for (int i = 0; i < n; i++)
    cin >> p[i];
  sort(p.begin(), p.end());

  int a;
  for (int i = 0; i < t; i++) {
    cin >> a;
    cout << nearest(p, a) << endl;
  }

  return 0;
}
