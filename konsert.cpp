#include <cstdlib>
#include <iostream>

using namespace std;

struct concert {
    int x;
    int y;
    int ticket;
    struct concert *next;
};

int distance(struct concert *src, struct concert *dst) {
    return abs(src->x - dst->x) + abs(src->y - dst->y);
}

int withcost(struct concert *curr) {
    struct concert *a, *b;
    a = curr->next;
    b = a->next;
    
    return distance(curr, a) + distance(a, b) + a->ticket;
}

int skipcost(struct concert *curr) {
    struct concert *b;
    b = curr->next->next;
    
    return distance(curr, b);
}

int skiplast(struct concert *curr) {
    struct concert *a;    
    a = curr->next;
    
    return distance(curr, a) + a->ticket;
}

int solve(struct concert *origin, int n, int budget) {
    struct concert *maxnode;
    struct concert *curr;
    int maxval, val, sum;
    
    sum = 0;    
    curr = origin;
    for (int i = 0; i < n; i++) {
        sum += distance(curr, curr->next) + curr->next->ticket;
        curr = curr->next;
    }
    
    if (sum <= budget)
        return n;
    
    if (n == 1)
        return 0;
    
    maxval = 0;
    curr = origin;
    for (int i = 0; i < (n-1); i++) {
        val = withcost(curr) - skipcost(curr);
        if (val > maxval) {
            maxnode = curr;
            maxval = val;
        }
        curr = curr->next;
    }
    
    if (skiplast(curr) <= maxval)
        maxnode->next = maxnode->next->next;
    
    return solve(origin, n - 1, budget);
}

int main() {
    int nconcerts, budget;
    cin >> nconcerts >> budget;
    
    int x, y, ticket;
    
    struct concert *origin;
    struct concert *prev;
    struct concert *curr;
    origin = new concert;
    origin->x = 0;
    origin->y = 0;
    prev = origin;
    
    for (int i = 0; i < nconcerts; i++) {
        cin >> x >> y >> ticket;
        
        curr = new concert;
        prev->next = curr;
        prev = curr;
        curr->x = x;
        curr->y = y;
        curr->ticket = ticket;
    }
    
    cout << solve(origin, nconcerts, budget) << endl;
    
    return 0;
}
