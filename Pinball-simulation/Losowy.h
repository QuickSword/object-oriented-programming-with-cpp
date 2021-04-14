//
// Created by Asia on 14.04.2021.
//

class Losowy: public Odbijacz{
public:
    Losowy(int, int, int, int);
    void collide(vector<shared_ptr<struct Kulka>>&, int) override;
};

Losowy::Losowy(int unnamed, int unnamed1, int unnamed2, int unnamed3) : Odbijacz(unnamed, unnamed1, unnamed2, unnamed3){
    type='L';
}

void Losowy::collide(vector<shared_ptr<struct Kulka>>& k, int ind) {
    int r = rand()%8+1;
    switch(r){
        case 1:
            k[ind]->change_direction("N");
            break;
        case 2:
            k[ind]->change_direction("NE");
            break;
        case 3:
            k[ind]->change_direction("NW");
            break;
        case 4:
            k[ind]->change_direction("S");
            break;
        case 5:
            k[ind]->change_direction("SE");
            break;
        case 6:
            k[ind]->change_direction("SW");
            break;
        case 7:
            k[ind]->change_direction("E");
            break;
        case 8:
            k[ind]->change_direction("W");
            break;
        default:
            exit(3);
    }
}
