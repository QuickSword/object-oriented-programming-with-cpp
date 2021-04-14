//
// Created by Asia on 14.04.2021.
//

class Ukosny: public Odbijacz{
public:
    Ukosny(int, int, int, int, char);
    void collide(vector<shared_ptr<struct Kulka>>&, int) override;
};

Ukosny::Ukosny(int unnamed, int unnamed1, int unnamed2, int unnamed3, char _type) : Odbijacz(unnamed, unnamed1, unnamed2, unnamed3) {
    type=_type;
}

void Ukosny::collide(vector<shared_ptr<struct Kulka>>& k, int ind) {
    char direct;
    if(type=='u') {
        if(k[ind]->get_direction()=="SW") {
            k[ind]->change_direction("NE");
        }else if(k[ind]->get_direction()=="NE"){
            k[ind]->change_direction("SW");
        }else if(k[ind]->get_direction()=="S"){
            k[ind]->change_direction("E");
        }else if(k[ind]->get_direction()=="N"){
            k[ind]->change_direction("W");
        }else if(k[ind]->get_direction()=="SE"){
            k[ind]->change_direction("NW");
        }else if(k[ind]->get_direction()=="NW"){
            k[ind]->change_direction("SE");
        }
    }else if(type=='U'){
        if(k[ind]->get_direction()=="SW") {
            k[ind]->change_direction("NE");
        }else if(k[ind]->get_direction()=="NE"){
            k[ind]->change_direction("SW");
        }else if(k[ind]->get_direction()=="S"){
            k[ind]->change_direction("W");
        }else if(k[ind]->get_direction()=="N"){
            k[ind]->change_direction("E");
        }else if(k[ind]->get_direction()=="SE"){
            k[ind]->change_direction("NW");
        }else if(k[ind]->get_direction()=="NW"){
            k[ind]->change_direction("SE");
        }
    }

}

