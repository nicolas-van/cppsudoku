
#include <iostream>
#include "sudoku_solver.hpp"

using namespace std;

int main()
{
    sudoku sudo("sudoku.txt");
    sudoku_solver solver(sudo);
    if(solver.exec()) {
        cout << "le sudoku est correct:" << endl << sudo;
        if(sudo.test())
            cout << "deuxieme verification correcte" << endl;
        else
            cout << "deuxieme verification incorrecte" << endl;
    } else
        cout << "le sudoku est incorrect:" << endl << sudo;
    cout << "cette conclusion a necessite "<<solver.nbr_suppos<<" suppositions"<<endl;
    cout << "la plus grosse supposition portait sur "<<solver.max_suppos<<" possibilites"<<endl;

    return 0;
}
