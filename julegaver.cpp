#include <cstdio>
#include <vector>

using namespace std;

int connected_components(int* component, int vertex, int component_id,const int* edgeindex, 
                         const int* edge, int* colour, int current_colour, int npeople) {
  int count = 1;

  if (vertex == -1) {
    for (int i = 0; i < npeople; i++) {
      if (component[i] == 0) {
        vertex = i;
        break;
      }
    }
  }

  int start = edgeindex[vertex];
  int end = edgeindex[vertex+1];

  colour[vertex] = current_colour;
  component[vertex] = component_id;
  for (int i = start; i < end; i++) {
    int tail = edge[2*i+1];
    if (colour[tail] == current_colour)
      return -1;
    if (component[tail] == 0) {
      int c = connected_components(component, tail, component_id, edgeindex, edge,
                                   colour, current_colour^1, npeople);
      if (c != -1)
        count += c;
      else
        return -1;
    }
  }

  return count;
}

int main() {
  int n;
  scanf("%d", &n);

  int* component = new int[n]();
  int* colour = new int[n]();
  int* edgeindex = new int[n+1]();
  int* edge = new int[799800]();

  int edgeoffset = 0;
  for (int i = 0; i < n; i++) {
    int b, m;
    scanf("%d", &m);
    edgeindex[i] = edgeoffset;
    for (int j = 0; j < m; j++) {
      scanf("%d", &b);
      edge[2*(edgeoffset+j)] = i;
      edge[2*(edgeoffset+j)+1] = b;
    }
    edgeoffset += m;
  }

  edgeindex[n] = edgeoffset;

  int count = 0, ncomponents = 0;
  for (int component_id = 1; ; component_id++) {
    int c = connected_components(component, -1, component_id, edgeindex, edge, colour, 2, n);
    if (c == -1) {
      printf("0\n");
      return 0;
    }
    count += c;
    if (count == n) {
      ncomponents = component_id;
      break;
    }
  }

  int* coloursum = new int[2*ncomponents]();
  for (int i = 0; i < n; i++)
    coloursum[((component[i]-1)<<1)|(colour[i]^2)]++;

  int gifts = 0;
  for (int i = 0; i < ncomponents; i++)
    gifts += max(coloursum[i<<1], coloursum[(i<<1)|1]);

  printf("%d\n", gifts);

  return 0;
}
