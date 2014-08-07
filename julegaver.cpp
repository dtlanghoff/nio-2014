#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

struct iteminfo {
    int a, b;
    bool error;
};

struct iteminfo *alloc_presents(int *item, vector< vector<int> > edges, int current) {
    int m = item[current];
    int edge;
    vector<int> new_children;
    
    struct iteminfo *new_presents;
    struct iteminfo *child_presents;
    
    new_presents = new iteminfo;
    new_presents->a = 0;
    new_presents->b = 0;
    new_presents->error = false;
    
    if (m == 0)
        new_presents->a = 1;
    else
        new_presents->b = 1;
    
    for (unsigned int i = 0; i < edges[current].size(); i++) {
        edge = edges[current][i];
        if (item[edge] == m) {
            new_presents->error = true;
        }
        else if (item[edge] == -1) {
            item[edge] = m^1;
            new_children.push_back(edge);
        }
    }
    
    for (unsigned int i = 0; i < new_children.size(); i++) {
        child_presents = alloc_presents(item, edges, new_children[i]);
        if (child_presents->error) {
            new_presents->error = true;
            break;
        }
        else {
            new_presents->a += child_presents->a;
            new_presents->b += child_presents->b;
        }
    }
    
    return new_presents;
}

int main() {
    int npeople, current, neighbour, nneighbours;
    int books = 0;
    int considered = 0;
    bool found_root;  
    
    struct iteminfo *info;
    
    cin >> npeople;
    
    vector< vector<int> > edges(npeople, vector<int>(0));
    int item[npeople];
    
    for (int i = 0; i < npeople; i++) {
        item[i] = -1;
        cin >> nneighbours;
        for (int j = 0; j < nneighbours; j++) {
            cin >> neighbour;
            if (neighbour > i) {
                edges[i].push_back(neighbour);
            }
        }
    }
    
    do {
        current = 0;
        found_root = false;
        while (!found_root) {
            if (item[current] == -1) {
                found_root = true;
            }
            else {
                current++;
            }
        }
        item[current] = 0;
        info = alloc_presents(item, edges, current);
        if (info->error) {
            cout << 0 << endl;
            return 0;
        }
        books += max(info->a, info->b);
        considered += info->a + info->b;
    } while (considered < npeople);
    
    cout << books << endl;
    return 0;
}
