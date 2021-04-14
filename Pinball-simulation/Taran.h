//
// Created by Asia on 05.04.2021.
//

#ifndef UNTITLED13_TARAN_H
#define UNTITLED13_TARAN_H


class Taran : public Kulka{
public:
    Taran(int, int, int, int);
    void move() override;
    void collide(vector<shared_ptr<struct Kulka>>&, int) override;
    void collide2(vector<shared_ptr<struct Odbijacz>>&, int) override;
};

Taran::Taran(int _n, int _m, int _nmax, int _mmax) : Kulka(_n, _m, _nmax, _mmax) {
    type = 'T';
}

void Taran::move() {
    Kulka::move();
}

void Taran::collide(vector<shared_ptr<struct Kulka>> & kulki, int ind) {
    this->swap_velocities(kulki[ind]);
    kulki.erase(kulki.begin()+ind);
}

void Taran::collide2(vector<shared_ptr<struct Odbijacz>> & odbijacze, int ind) {
    odbijacze.erase(odbijacze.begin()+ind);
}


#endif //UNTITLED13_TARAN_H
