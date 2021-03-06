#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> prognosis(n);
    
    bool charged = false;
    int profit = 0;
    
    for (int i = 0; i < n; i++)
        cin >> prognosis[i];
    
    for (int i = 0; i < (n-1); i++) {
        // kjøp kraft når prisen er på botn
        if (!charged && (prognosis[i+1] > prognosis[i])) {
            charged = true;
            profit -= prognosis[i];
        }
        // sel kraft når prisen er på topp
        else if (charged && (prognosis[i+1] < prognosis[i])) {
            charged = false;
            profit += prognosis[i];
       }
    }
    
    // sel attverande kraft om prisen er positiv
    if (charged && (prognosis[n-1] > 0))
        profit += prognosis[n-1]; 
    // fyll opp generatoren om prisen er negativ
    else if (!charged && (prognosis[n-1] < 0))
        profit -= prognosis[n-1]; 
    
    cout << (profit * 1000) << endl;
    
    return 0;
}
