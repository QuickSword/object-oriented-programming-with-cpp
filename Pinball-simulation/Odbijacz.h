//
// Created by Asia on 14.04.2021.
//

class Odbijacz{
protected:
    int n, m;
    char type{};
    int nmax, mmax;
public:
    Odbijacz(int, int, int, int);
    virtual void collide(vector<shared_ptr<struct Kulka>>&, int);
    virtual int getn();
    virtual int getm();
    virtual char get_type();
};

Odbijacz::Odbijacz(int _n, int _m, int _nmax, int _mmax) {
    n=_n; m=_m;
    nmax=_nmax; mmax=_mmax;
}


void Odbijacz::collide(vector<shared_ptr<struct Kulka>>&, int) {

}

int Odbijacz::getn() {
    return n;
}

int Odbijacz::getm() {
    return m;
}

char Odbijacz::get_type() {
    return type;
}
