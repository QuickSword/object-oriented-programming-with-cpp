//
// Created by Asia on 14.04.2021.
//

class Zjadajacy: public Odbijacz{
public:
    Zjadajacy(int, int, int, int);
    void collide(vector<shared_ptr<struct Kulka>>&, int) override;

};

Zjadajacy::Zjadajacy(int unnamed, int unnamed1, int unnamed2, int unnamed3) : Odbijacz(unnamed, unnamed1, unnamed2, unnamed3) {
    type='Z';
}

void Zjadajacy::collide(vector<shared_ptr<struct Kulka>>& kulki, int i) {
    kulki.erase(kulki.begin()+i);
}

