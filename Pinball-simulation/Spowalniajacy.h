//
// Created by Asia on 14.04.2021.
//

class Spowalniajacy: public Odbijacz{
public:
    Spowalniajacy(int, int, int, int);
    void collide(vector<shared_ptr<struct Kulka>>&, int) override;

};

Spowalniajacy::Spowalniajacy(int unnamed, int unnamed1, int unnamed2, int unnamed3) : Odbijacz(unnamed, unnamed1, unnamed2, unnamed3){
    type='S';
}

void Spowalniajacy::collide(vector<shared_ptr<struct Kulka>>& kulki, int ind) {
    kulki[ind]->change_velocity(type);
}

