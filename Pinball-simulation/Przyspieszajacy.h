//
// Created by Asia on 14.04.2021.
//

class Przyspieszajacy: public Odbijacz{
public:
    Przyspieszajacy(int, int, int, int);
    void collide(vector<shared_ptr<struct Kulka>>&, int) override;
};

Przyspieszajacy::Przyspieszajacy(int unnamed, int unnamed1, int unnamed2, int unnamed3) : Odbijacz(unnamed, unnamed1, unnamed2, unnamed3){
    type='P';
}

void Przyspieszajacy::collide(vector<shared_ptr<struct Kulka>>& kulki, int ind) {
    kulki[ind]->change_velocity(type);
}
