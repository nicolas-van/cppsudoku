#include "sudoku_solver.hpp"
#include <iostream>
#include <fstream>

using namespace std;

class possibilities {
    bool tab[9];
    unsigned int nbr_poss;
    public:
    possibilities() {
        nbr_poss=0;
        for(int i=1;i<=9;i++) {
            tab[i-1]=false;
        }
    }
    possibilities(const sudoku& sudo,size_t x,size_t y) {
        build(sudo,x,y);
    }
    void build(const sudoku& sudo,size_t i,size_t j) {
        for(int x=1;x<=9;x++)
            tab[x-1]=true;
        for(int x=0;x<9;x++) {
            int value = sudo.get(x,j);
            if(value!=0)
                tab[value-1]=false;
        }
        for(int y=0;y<9;y++) {
            int value = sudo.get(i,y);
            if(value!=0)
                tab[value-1]=false;
        }
        size_t sn=sudoku::squarre_by_position(i,j);
        for(size_t x=0;x<9;x++) {
            int value = sudo.get_by_squarre(sn,x);
            if(value!=0)
                tab[value-1]=false;
        }
        unsigned int nbr=0;
        for(size_t x=1;x<=9;x++)
            if((*this)[x])
                nbr++;
        nbr_poss=nbr;
    }
    bool operator [](int i)const {
        assert(i>=1 && i<=9);
        return tab[i-1];
    }
    void set(int i,bool v) {
        assert(i>=1 && i<=9);
        tab[i-1] = v;
        if(tab[i-1]==true)
            if(v==false)
                nbr_poss--;
        else
            if(v==true)
                nbr_poss++;
    }
    unsigned int get_nbr_poss() {
        return nbr_poss;
    }
};

bool sudoku_solver::exec() {

    while(true) {
        bool finded0=false;
        bool resolved0=false;
        for(size_t j=0;j<9;j++) {
            for(size_t i=0;i<9;i++) {
                int current = sudo.get(i,j);
                if(current == 0) {
                    finded0=true;
                    possibilities poss(sudo,i,j);
                    unsigned int nbr=poss.get_nbr_poss();
                    if(nbr==0)
                        return false;
                    if(nbr==1) {
                        for(int x=1;x<=9;x++) {
                            if(poss[x] == true) {
                                sudo.get(i,j)=x;
                                resolved0=true;
                                break;
                            }
                        }
                        assert(resolved0);
                    }
                }
            }
        }
        if(finded0==false)
            return true;
        if(resolved0==false)
            break;
    }

    for(unsigned int nbr=2;nbr<=max_to_guess;nbr++) {
        for(size_t j=0;j<9;j++) {
            for(size_t i=0;i<9;i++) {
                int current = sudo.get(i,j);
                if(current == 0) {
                    possibilities poss(sudo,i,j);
                    if(poss.get_nbr_poss()==(nbr>9?9:nbr)) {
                        max_suppos=nbr;
                        for(int x=1;x<=9;x++) {
                            if(poss[x] == true) {
                                sudoku sudo2 = sudo;
                                sudo2.get(i,j)=x;
                                sudoku_solver solver2(sudo2);
                                solver2.max_to_guess=nbr-1;
                                if(solver2.exec()) {
                                    sudo=sudo2;
                                    nbr_suppos=solver2.nbr_suppos+1;
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}


