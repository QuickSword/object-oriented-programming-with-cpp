/*
 Author: Joanna Keczkowska
 Email: jk406704@students.mimuw.edu.pl
 IDE: CLion 2020.3.2
 */


//Przykladowy plik:
/*
20 10 10
W  Z


        L

  Mu   S P
Z    U
    M
   M
  M

T
*/




#include <iostream>
#include <fstream> //file usage
#include <string>
#include <sstream> //istringstream
#include <utility>
#include <vector>
#include <cstdlib> // atoi()
#include <ctime> //time()

#include <Kulka.h>
#include <Losowy.h>
#include <Mglowy.h>
#include <Odbijacz.h>
#include <Przyspieszajacy.h>
#include <Spowalniajacy.h>
#include <Surface>
#include <Taran.h>
#include <Ukosny.h>
#include <Wybuchowa.h>
#include <Zjadajacy.h>
#include <Zwykla.h>
using namespace std;

int main() {
    srand( time( nullptr ) );
    Surface board = Surface();
    cout << "m = " << board.get_mmax() << endl;
    cout << "n = " << board.get_nmax() << endl;
    cout << "Liczba tur: " << board.get_turns() << endl;


    board.print(nullptr);
    board.simulation();

    cout << "Koniec symulacji!" << endl;

    return 0;

}
