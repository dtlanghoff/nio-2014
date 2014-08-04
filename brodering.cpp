#include <iostream>
#include <vector>

using namespace std;

int main() {
    int ncol, nrow, ninstr;
    cin >> ncol >> nrow >> ninstr;
    
    int length(ninstr);
    char colour(ninstr);
    vector< vector<char> > image(nrow, vector<char>(ncol));
    int row = 0, col = 0;
    
    for (int i = 0; i < ninstr; i++) {
        cin >> length >> colour;
        for (int j = 0; j < length; j++) {
            image[row][col] = colour;
            if (col == ((row%2 == 0) ? (ncol-1) : 0))
                row++;
            else
                col += (row%2 == 0) ? 1 : -1;
        }
    }
    
    for (int row = 0; row < nrow; row++) {
        for (int col = 0; col < ncol; col++) {
            cout << image[row][col];
        }
        cout << endl;
    }
    
    return 0;
}
