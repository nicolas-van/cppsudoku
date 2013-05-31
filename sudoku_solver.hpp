#ifndef SUDOKU_SOLVER_HPP_INCLUDED
#define SUDOKU_SOLVER_HPP_INCLUDED

#include "sudoku.hpp"
#include <set>

struct sudoku_solver {
    sudoku& sudo;
    unsigned int max_to_guess;
    unsigned int nbr_suppos;
    unsigned int max_suppos;
    explicit sudoku_solver(sudoku& s,unsigned int max=9):sudo(s),max_to_guess(max)
    ,nbr_suppos(0),max_suppos(0) {}
    bool exec();
};

#endif // SUDOKU_SOLVER_HPP_INCLUDED
