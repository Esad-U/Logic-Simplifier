#include <iostream>
#include <stdio.h>
#include <math.h>
#include "Simplifier.h"

using namespace std;

int main()
{
    int varNum, index;
    string vars;
    vector<int> indexes;
    cout << "------ Logic Function Simplifier ------" << endl;
    cout << "This program simplifies a logic function in SoP form." << endl;
    cout << "How many variables?: ";
    cin >> varNum;
    cout << "Enter variables with no spaces between: ";
    cin >> vars;
    cout << "Enter minterm indexes one by one (-1 to quit): " << endl;
    for(int i = 0;i < pow(2,varNum);i++) {
        cin >> index;
        if(index == -1)
            break;
        indexes.push_back(index);
    }
    Simplifier *simp = new Simplifier(varNum, vars);
    simp->simplify(indexes);
    delete simp;
    return EXIT_SUCCESS;
}