//
// Created by Asia on 05.04.2021.
//

#ifndef UNTITLED13_KULKA_H
#define UNTITLED13_KULKA_H


class Kulka{
protected:
    int n, m;
    char type;
    int mmax, nmax;
    int velocity;
    //N, S, E, W, NE, NW, SE, SW
    string direction;
public:
    Kulka(int, int, int, int);
    Kulka()=default;
    ~Kulka()=default;
    virtual void move();
    virtual void change_direction(string);
    virtual char get_type();
    virtual int get_nmax();
    virtual int get_mmax();
    virtual string get_direction();
    virtual void change_velocity(char);
    virtual Kulka& swap_directions(shared_ptr<Kulka>&);
    virtual Kulka& swap_velocities(shared_ptr<Kulka>&);
    virtual void collide(vector<shared_ptr<struct Kulka>> &, int);
    virtual void collide2(vector<shared_ptr<struct Odbijacz>>&, int);
    virtual int getn();
    virtual int getm();
    virtual int get_velocity();
    virtual unsigned int get_time() const;
};

Kulka::Kulka(int _n, int _m, int _nmax, int _mmax) {
    n=_n; m=_m;
    nmax=_nmax; mmax=_mmax;
    velocity = 1; //1 tura 1 pole
    if(m==0 && n==0) {
        direction = "SE";
    }else if(m==0 && n==nmax){
        direction = "NE";
    }else if(n!=nmax && n!=0 && m==0) {
        direction = "E";
    }else if(n==0 && m==mmax){
        direction = "SW";
    }else if(n==0 && m!=mmax && m!=0) {
        direction = "S";
    }else if(n==nmax && m==mmax) {
        direction = "NW";
    }else if(n==nmax && m!=mmax && m!=0) {
        direction = "N";
    }else if(n!=nmax && n!=0 && m==mmax) {
        direction = "W";
    }else {
        exit(8);
    }
}

void Kulka::move() {
    if(direction == "SE") {
        n++;
        m++;
    }else if(direction == "SW"){
        n++;
        m--;
    }else if(direction == "S") {
        n++;
    }else if(direction == "NE"){
        n--;
        m++;
    }else if(direction == "E") {
        m++;
    }else if(direction == "NW") {
        m--;
        n--;
    }else if(direction == "N") {
        n--;
    }else if(direction == "W") {
        m--;
    }
}

void Kulka::change_direction(string _type) {
    direction=_type;
}

char Kulka::get_type() {
    return type;
}

int Kulka::get_nmax() {
    return nmax;
}

int Kulka::get_mmax() {
    return mmax;
}

string Kulka::get_direction() {
    return direction;
}

void Kulka::change_velocity(char s) {
    if(s=='S'){
        velocity++;
    }else{
        if(velocity==1){ //nie mozna szybciej
            return;
        }else{
            velocity--;
        }
    }
}

Kulka &Kulka::swap_velocities(shared_ptr<Kulka>& k){
    swap(velocity, k->velocity);
    return *this;
}

Kulka &Kulka::swap_directions(shared_ptr<Kulka>& k) {
    swap(direction, k->direction);
    return *this;
}

void Kulka::collide(vector<shared_ptr<struct Kulka>> &kulki, int ind) {
    this->swap_directions(kulki[ind]);
    this->swap_velocities(kulki[ind]);
}

int Kulka::getn() {
    return n;
}

int Kulka::getm() {
    return m;
}

int Kulka::get_velocity() {
    return velocity;
}

unsigned int Kulka::get_time() const {
    return 0;
}


void Kulka::collide2(vector<shared_ptr<struct Odbijacz>> &, int) {
    return;
}



#endif //UNTITLED13_KULKA_H
