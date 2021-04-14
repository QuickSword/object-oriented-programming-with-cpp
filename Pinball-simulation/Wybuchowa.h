//
// Created by Asia on 05.04.2021.
//

#ifndef UNTITLED13_WYBUCHOWA_H
#define UNTITLED13_WYBUCHOWA_H

class Wybuchowa : public Kulka{
private:
    unsigned int detonation_time;
public:
    Wybuchowa(int, int, int, int, unsigned int);
    ~Wybuchowa()=default;
    unsigned int get_time() const override;
    void move() override;
    void collide(vector<shared_ptr<struct Kulka>>&, int) override;
    void collide2(vector<shared_ptr<struct Odbijacz>>&, int) override;
};

Wybuchowa::Wybuchowa(int _n, int _m, int _nmax, int _mmax, unsigned int time) : Kulka(_n, _m, _nmax, _mmax) {
    type = 'W';
    detonation_time=time;
}

void Wybuchowa::move() {
    if(detonation_time!=0) {
        Kulka::move();
        detonation_time--;
    }else
        return;
}

unsigned int Wybuchowa::get_time() const {
    return detonation_time;
}


void Wybuchowa::collide(vector<shared_ptr<struct Kulka>> & kulki, int ind) {
    if(detonation_time==0)
        kulki.erase(kulki.begin()+ind);
    else
        Kulka::collide(kulki, ind);
}

void Wybuchowa::collide2(vector<shared_ptr<struct Odbijacz>> & odbijacze, int ind) {
    if(detonation_time==0)
        odbijacze.erase(odbijacze.begin()+ind);
}



#endif //UNTITLED13_WYBUCHOWA_H
