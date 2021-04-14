//
// Created by Asia on 14.04.2021.
//

class Surface{
private:
    int n,m;
    int turns;
    char **board;
public:
    vector <shared_ptr<Kulka>> kulki;
    vector <shared_ptr<Odbijacz>> odbijacze;
    explicit Surface();
    ~Surface();
    int get_mmax() const; //szerokosc
    int get_nmax() const; //wysokosc
    int get_turns() const; //liczba tur
    void simulation();
    void update();
    void check_collisions(vector <int>&, vector <shared_ptr<Kulka>>&);
    void check_collisions2(vector <int>&);
    void przesun_zwolniony(vector<int>&, shared_ptr<Kulka>&, int);
    void print(const char string1[19]) {
        for(int i=0; i<(n+2);i++) {
            for(int j=0; j<(m+2); j++) {
                cout << board[i][j];
            }
            cout << endl;
        }
    }
};



Surface::Surface() {
    //wczytywanie pliku...
    char ch;
    string line;
    string token;
    int i=0, j=0;
    fstream infile;
    infile.open("board2");
    getline(infile, line);
    istringstream iss(line);
    getline(iss, token, ' ');
    turns = atoi(token.c_str());

    getline(iss, token, ' ');
    m = atoi(token.c_str());

    getline(iss, token, ' ');
    n = atoi(token.c_str());

    if(n==0 || m==0 || turns==0) {
        cout << "Wpisano 0 lub znak" << endl;
        exit(1);
    }

    board = new char*[n+2];
    for(int i=0; i<(n+2); i++) {
        board[i] = new char[m+2];
    }
    for(int i=0; i<(n+2); i++) {
        for(int j=0; j<(m+2); j++) {
            board[i][j]= ' ';
        }
    }

    while(infile >> noskipws >> ch) {
        if(ch!='\n') {
            if(i==0 || j==0 || i==(m+1) || j==(n+1)) {
                switch ( ch )
                {
                    case 'Z':
                        kulki.push_back(make_shared<Zwykla>(j, i, n+1, m+1));
                        board[j][i]= ch;
                        break;
                    case 'T':
                        kulki.push_back(make_shared<Taran>(j, i, n+1, m+1));
                        board[j][i]= ch;
                        break;
                    case 'W':
                        kulki.push_back(make_shared<Wybuchowa>(j, i, n+1, m+1, rand() % turns + 1));
                        board[j][i]= ch;
                        break;
                    case ' ':
                        break;
                    default:
                        cout << "Nieznana kulka!/Bledne dane w pliku!"  << endl;
                        exit(1);
                }
            }else {
                if(i>m+1 || j>n+1) {
                    if(i!='\n') {
                        cout << "Nieprawidlowa plansza! - na szerokosc" << endl;
                        exit(1);
                    }else if(j>i+1){
                        cout << "Nieprawidlowa plansza! - na wysokosc" << endl;
                        exit(1);
                    }
                }
                switch ( ch )
                {
                    case 'u':
                        odbijacze.push_back(make_shared<Ukosny>(j, i, n+1, m+1, 'u'));
                        board[j][i]= ch;
                        break;
                    case 'U':
                        odbijacze.push_back(make_shared<Ukosny>(j, i, n+1, m+1, 'U'));
                        board[j][i]= ch;
                        break;
                    case 'L':
                        odbijacze.push_back(make_shared<Losowy>(j, i, n+1, m+1));
                        board[j][i]= ch;
                        break;
                    case 'Z':
                        odbijacze.push_back(make_shared<Zjadajacy>(j, i, n+1, m+1));
                        board[j][i]= ch;
                        break;
                    case 'S':
                        odbijacze.push_back(make_shared<Spowalniajacy>(j, i, n+1, m+1));
                        board[j][i]= ch;
                        break;
                    case 'M':
                        odbijacze.push_back(make_shared<Mglowy>(j, i, n+1, m+1));
                        board[j][i]= ch;
                        break;
                    case 'P':
                        odbijacze.push_back(make_shared<Przyspieszajacy>(j, i, n+1, m+1));
                        board[j][i]= ch;
                        break;
                    case ' ':
                        break;
                    default:
                        cout << "Nieznany odbijacz!"  << endl;
                        exit(1);
                }
            }
            i++;
        }else {
            j++;
            i=0;
        }
    }
    infile.close();
}

int Surface::get_mmax() const {
    return m;
}

int Surface::get_nmax() const {
    return n;
}

int Surface::get_turns() const {
    return turns;
}

void Surface::simulation() {
    unsigned int time = turns;
    vector <shared_ptr<Kulka>> out; //chcemy wiedziec jakie kulki wypadly i w ktorym miejscu
    vector <int> timer;
    for(int i=0; i<kulki.size(); i++) {
        timer.push_back(kulki[i]->get_velocity()); // do odmierzania czasu dla kulek zwolnionych odbijaczem
    }
    while(time!=0){
        time--;
        for(int k=0; k<kulki.size(); k++) {
            if(kulki[k]->get_type()=='W' && kulki[k]->get_time()==0) {
                kulki.erase(kulki.begin()+k);
                timer.erase(timer.begin()+k);
                cout << "Wybuch kulki!" << endl;
                k--;
                continue;
            }
            if(timer[k]>1) {
                przesun_zwolniony(timer, kulki[k], k);
                continue;
            }
            kulki[k]->move();
            timer[k]=kulki[k]->get_velocity();
        }
        check_collisions(timer, out); // obsluga odbijaczy
        check_collisions2(timer); //obsluga kulek

        cout << "Tura: " << turns-time << endl;
        for(int k=0; k<kulki.size(); k++) { // drukowanie pozycji kulek
            cout << k+1 << ". " << kulki[k]->getm() << " " << kulki[k]->getn() << "\t v = "<< kulki[k]->get_velocity();
            if(kulki[k]->get_type()=='W') {
                cout << "\t time = " << kulki[k]->get_time();
            }
            cout << endl;
        }

        this->update();

        for(int k=0; k<kulki.size();) {
            if((kulki[k]->getm()+1)==(m+2) || (kulki[k]->getn()+1)==(n+2) || kulki[k]->getm()==0 || kulki[k]->getn()==0) {
                out.push_back( kulki[k]);
                kulki.erase(kulki.begin()+k);
                timer.erase(timer.begin()+k);
                this->update();
                continue;
            }
            k++;
            this->update();
        }
        printf("------------------------------------------------------ \n");
        this->print(nullptr);
        if(kulki.empty()) {// gdy nie ma juz kulek na planszy
            cout << "Nie ma juz kulek na planszy!" << endl;
            cout << "Pozostaly czas: " << time << " tur(y/a)." << endl;
            cout << "Kulki, ktore wypadly: " << endl;
            for(int i=0; i<out.size(); i++) {
                cout << i+1 << ". m = " << out[i]->getm() << ", n = " << out[i]->getn() << endl;
            }
            return;
        }

        printf("------------------------------------------------------ \n");
    }
    if(!out.empty()) {
        cout << "Kulki, ktore wypadly: " << endl;
        for (int i = 0; i < out.size(); i++) {
            cout << i + 1 << ". m = " << out[i]->getm() << ", n = " << out[i]->getn() << endl;
        }
    }
}

void Surface::update() {
    char c;
    for(int i=0; i<(n+2); i++) {
        for(int j=0; j<(m+2); j++) {
            board[i][j]= ' ';
        }
    }
    for(int k=0; k<odbijacze.size();k++) {
        c = odbijacze[k]->get_type();
        if (c == 'U' || c == 'u' || c == 'L' || c == 'Z' || c == 'S' || c == 'M' || c == 'P')
            board[odbijacze[k]->getn()][odbijacze[k]->getm()] = c;
    }
    c=' ';
    for(int k=0; k<kulki.size();k++) {
        c = kulki[k]->get_type();
        if (c == 'Z' || c == 'W' || c == 'T')
            board[kulki[k]->getn()][kulki[k]->getm()] = c;
    }
}

void Surface::check_collisions(vector <int>& time, vector <shared_ptr<Kulka>>& out) {
    for(int i=0; i<odbijacze.size(); i++) {
        for (int j = 0; j < kulki.size(); j++) {
            if(kulki[j]->getm()==odbijacze[i]->getm() && kulki[j]->getn()==odbijacze[i]->getn()) {
                if(odbijacze[i]->get_type()=='Z'){ //zjadający zjada wszystko
                    out.push_back(kulki[j]);
                    odbijacze[i]->collide(kulki, j);
                    time.erase(time.begin()+j);
                }else if( odbijacze[i]->get_type()=='S'){
                    if(time[j]==1 || time[j]==kulki[j]->get_velocity()) {
                        odbijacze[i]->collide(kulki, j);
                    }else {
                        time[j]--;
                    }
                }else if(odbijacze[i]->get_type()=='P'){
                    odbijacze[i]->collide(kulki, j);
                    time[j] = kulki[j]->get_velocity();
                }else if (odbijacze[i]->get_type()!='S' && odbijacze[i]->get_type()!='P' && odbijacze[i]->get_type()!='Z' && kulki[j]->get_type()!='T' && kulki[j]->get_type()!='W'){
                    if(time[j]==1 || time[j]==kulki[j]->get_velocity()) {
                        odbijacze[i]->collide(kulki, j);
                    }else {
                        time[j]--;
                    }
                }else if(kulki[j]->get_type()=='T') {
                    kulki[j]->collide2(odbijacze, i);
                }else if(kulki[j]->get_type()=='W' && kulki[j]->get_time()==0) {
                    kulki[j]->collide2(odbijacze, i);
                }else if(kulki[j]->get_type()=='W' && kulki[j]->get_time()!=0) {
                    odbijacze[i]->collide(kulki, j);
                }
            }
        }
    }
}

void Surface::check_collisions2(vector<int> & time) {
    for (int i = 0; i < kulki.size(); i++) {
        for (int j = i + 1; j < kulki.size(); j++) {
            if (kulki[i]->getn() == kulki[j]->getn() && kulki[i]->getm() == kulki[j]->getm()) {
                if (kulki[i]->get_type() == 'T') {
                    kulki[i]->collide(kulki, j);
                    time.erase(time.begin() + j);
                }else if(kulki[j]->get_type() == 'T') {
                    kulki[j]->collide(kulki, i);
                    time.erase(time.begin() + i);
                }else if (kulki[i]->get_type() == 'W') {
                    kulki[i]->collide(kulki, j);
                    if(time[i]==0)
                        time.erase(time.begin() + j);
                } else if (kulki[i]->get_type() == 'Z') {
                    kulki[i]->collide(kulki, j);
                }
            }
        }
    }
}
Surface::~Surface() {
    kulki.clear();
    odbijacze.clear();
}

void Surface::przesun_zwolniony(vector <int> & time, shared_ptr<Kulka>& kulka, int j) {
    for(int i=0; i<odbijacze.size(); i++) {
        if(kulka->getm()==odbijacze[i]->getm() && kulka->getn()==odbijacze[i]->getn()) {
            if(odbijacze[i]->get_type()!='S' && odbijacze[i]->get_type()!='P') {
                time[j]--;
            }else {
                return;
            }
        }
    }
    time[j]--;

}
