//
// Created by Asia on 05.04.2021.
//

#ifndef UNTITLED13_ZWYKLA_H
#define UNTITLED13_ZWYKLA_H


class Zwykla : public Kulka{
public:
    Zwykla(int, int, int, int);
    ~Zwykla()=default;
    void move() override;
};

Zwykla::Zwykla(int _n, int _m, int _nmax, int _mmax) : Kulka(_n, _m, _nmax, _mmax) {
    type = 'Z';
}

void Zwykla::move() {
    Kulka::move();
}


#endif //UNTITLED13_ZWYKLA_H
