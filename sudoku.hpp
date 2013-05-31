#ifndef SUDOKU_HPP_INCLUDED
#define SUDOKU_HPP_INCLUDED

#include <cassert>
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>

class sudoku {
    private:
    int tab[9][9];
    public:
    sudoku() {
        for(int j=0;j<9;j++)
            for(int i=0;i<81;i++)
                tab[j][i]=0;
    }
    sudoku(const std::string& file) {
        std::ifstream f(file.c_str());
        std::filebuf& buf = *f.rdbuf();
        size_t i =0;
        while (true)
        {
            char current = buf.sbumpc();
            if(current==EOF)
                throw new std::runtime_error("fichier invalide");
            else if(current >= '0' && current <='9') {
                get(i)=current-'0';
                i++;
            } else if(current == '*' || current == '.'
                || current == '_') {
                get(i)=0;
                i++;
            } else if(current == '#') {
                while(buf.sbumpc()!='\n') {}
            }
            if(i==81)
                break;
        }

    }
    int& get(size_t x,size_t y) {
        assert(y>=0 && y<9 && x>=0 && x<9);
        return tab[y][x];
    }
    int get(size_t x,size_t y) const {
        assert(y>=0 && y<9 && x>=0 && x<9);
        return tab[y][x];
    }
    int& get(size_t i) {
        assert(i/9>=0 && i/9<9 && i%9>=0 && i%9<9);
        return tab[i/9][i%9];
    }
    int get(size_t i) const {
        assert(i/9>=0 && i/9<9 && i%9>=0 && i%9<9);
        return tab[i/9][i%9];
    }
    int& get_by_squarre(size_t sn,size_t i) {
        assert(((sn/3)*3)+(i/3)>=0 && ((sn/3)*3)+(i/3)<9
        && ((sn%3)*3)+(i%3)>=0 && ((sn%3)*3)+(i%3)<9);
        //return get((((sn/3)*27)+((sn-((sn/3)*3))*3))+((i%3)+((i/3)*9)));
        return tab[((sn/3)*3)+(i/3)][((sn%3)*3)+(i%3)];
    }
    int get_by_squarre(size_t sn,size_t i) const {
        assert(((sn/3)*3)+(i/3)>=0 && ((sn/3)*3)+(i/3)<9
        && ((sn%3)*3)+(i%3)>=0 && ((sn%3)*3)+(i%3)<9);
        //return get((((sn/3)*27)+((sn-((sn/3)*3))*3))+((i%3)+((i/3)*9)));
        return tab[((sn/3)*3)+(i/3)][((sn%3)*3)+(i%3)];
    }
    static size_t squarre_by_position(size_t x,size_t y) {
        assert((y-(y%3))+(x/3)>=0 && (y-(y%3))+(x/3)<9);
        return ((y/3)*3)+(x/3);
    }
    static size_t place_in_squarre_by_position(size_t x,size_t y) {
        assert((y-(y%3))+(x/3)>=0 && (y-(y%3))+(x/3)<9);
        return ((y%3)*3)+(x%3);
    }
    bool test() {
        for(size_t j=0;j<9;j++) {
            int poss[9];
            for(size_t x=0;x<9;x++) {
                poss[x]=0;
            }
            for(size_t i=0;i<9;i++) {
                int value = get(i,j);
                if(value<0||value>9 || poss[value-1]==1) {
                    return false;
                }
                poss[value-1]=1;
            }
        }
        for(size_t i=0;i<9;i++) {
            int poss[9];
            for(size_t x=0;x<9;x++) {
                poss[x]=0;
            }
            for(size_t j=0;j<9;j++) {
                int value = get(i,j);
                if(poss[value-1]==1) {
                    return false;
                }
                poss[value-1]=1;
            }
        }
        for(size_t sn=0;sn<9;sn++) {
            int poss[9];
            for(size_t x=0;x<9;x++) {
                poss[x]=0;
            }
            for(size_t i=0;i<9;i++) {
                int value = get_by_squarre(sn,i);
                if(poss[value-1]==1) {
                    return false;
                }
                poss[value-1]=1;
            }
        }
        return true;
    }
};

inline std::ostream& operator << (std::ostream& s,const sudoku& sudo) {
    size_t i;
    size_t j;
    for(j=0;j<9;j++) {
        for(i=0;i<9;i++) {
            int value = sudo.get(i,j);
            if(value==0)
                s << "*";
            else
                s << value;
            if(i!=8 && i%3==2)
                s << "|";
        }
        s << std::endl;
        if(j!=8 && j%3==2)
            s <<"-----------"<< std::endl;
    }
    return s;
}


#endif // SUDOKU_HPP_INCLUDED
