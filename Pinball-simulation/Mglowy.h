//
// Created by Asia on 14.04.2021.
//

class Mglowy: public Odbijacz{
public:
    Mglowy(int, int, int, int);
    void collide(vector<shared_ptr<struct Kulka>>&, int) override;
};

Mglowy::Mglowy(int unnamed, int unnamed1, int unnamed2, int unnamed3) : Odbijacz(unnamed, unnamed1, unnamed2, unnamed3) {
    type='M';
}

void Mglowy::collide(vector<shared_ptr<struct Kulka>>& kulki, int ind) { }
