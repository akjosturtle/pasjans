//Tasowanie w osobnym wątku (std::thread i std::ref)


#include <iostream>
#include <vector>
#include <string>
#include <thread>           //std:thread
#include <functional>       //std::ref
//#include <conio.h>
//#include "menu.hpp"

void piszmenu(int a);
int menu();

class Karta {
public:
    Karta();
    ~Karta();

    int pobierzkolor() { return kolor; }
    char pobierzznak() { return znak; }
    char pobierzwartosc() { return wartosc; }

    void przypiszkolor(int kolorek) {    //// !!!!!!!!!!! do poprawy (rozdzielic  na Karta::funkcja.............)
        kolor = kolorek;
    }
    void przypiszznak(int znaczek) {
        if (znaczek == 0)
            znak = 's';  // kier (serce)
        else if (znaczek == 1)
            znak = 'k';  // karo
        else if (znaczek == 2)
            znak = 'p';  // pik
        else if (znaczek == 3)
            znak = 't';  //trefl
    }
    void przypiszwartosc(int warto) {
        if (warto == 1)
            wartosc = 'A';  // As
        else if (warto == 11)
            wartosc = 'J';  // Jopek
        else if (warto == 12)
            wartosc = 'Q';  // Qrulowa
        else if (warto == 13)
            wartosc = 'K';  // Krul
        else if (warto == 10)
            wartosc = '0';
        else
            wartosc = char(warto+48);
    }

private:
    int kolor;
    char znak;
    char wartosc;
};

Karta::Karta() {
    std::cout << "siema" << std::endl;
    kolor = '0';
    znak = '0';
    wartosc = '0';
}

Karta::~Karta() {
    std::cout << "nara";
}

void los1(class Karta** talia, int &kol, char &war, char &znak, int kt){
    srand(time(NULL));
    int x = rand() % 52;
    kol = talia[x]->pobierzkolor();
    war = talia[x]->pobierzwartosc();
    znak = talia[x]->pobierzznak();
    std::cout << "dupa1: " <<  kol << war << znak << '\n';
}
void los2(class Karta** talia, int a, char b, char c, int kt){
    srand(time(NULL));
    int x = rand() % 52;
    int kol = talia[x]->pobierzkolor();
    char war = talia[x]->pobierzwartosc();
    char znak = talia[x]->pobierzznak();
    talia[x]->przypiszkolor(a);
    talia[x]->przypiszwartosc(b);
    talia[x]->przypiszznak(c);
    talia[kt]->przypiszkolor(kol);
    talia[kt]->przypiszwartosc(war);
    talia[kt]->przypiszznak(znak);

    std::cout << "dupa2: " <<  kol << war << znak << '\n';
}
void menusterowanie(){
    char a;
    do{
        piszmenu(2);
        std::cin >> a;
    } while(a != '0');
}

int menu(){
    char a;
    //piszmenu(1);
    do{
        //system("cls");
        piszmenu(1);
        std::cin >> a;
        switch (a) {
        case '1': return 1;
            break;
        case '2': menusterowanie();
            break;
        default:
            break;
        }
    } while (a != '0');
    return 0;
}
void piszmenu(int a){
    using std::cout;
    using std::endl;
    //system("cls");
    switch(a){
        case 1:
            cout << "Pasjans Freecell" << endl;
            cout << "1 - Rozpocznij gre" << endl;
            cout << "2 - Sterowanie" << endl;
            cout << "0 - Wyjscie" << endl;
            cout << "" << endl;
            cout << "Michał Sojka, Bartosz Twardowski" << endl;
            cout << "ACiR 3, sem.2 2023" << endl;
            break;
        case 2:
            cout << "Sterowanie:" << endl;
            cout << "A, S, D, F, G, H, J, K - wybierane kart z pola gry (od lewej)" << endl;
            cout << "Q, W, E, R - wybieranie kart/miejsc sposrod grupy pol pomocniczych" << endl;
            cout << "Z, X, C, V - Pola docelowe" << endl;
            cout << "Ruch nalezy wykonac wpisujac kombinacje 2 znakow" << endl;
            cout << "np. AQ - ruch przenosi karte z pola gry A do pola pomocniczego Q" << endl;
            cout << "" << endl;
            cout << "0 - powrot do menu gry" << endl;
            cout << "" << endl;
            cout << "ACiR 3, sem.2 2023" << endl;
        default:
            break;
        }
}

void inicjalizacjaTalii(class Karta** talia){
for (int i = 0; i < 4; i++) {

        for (int j = 1; j < 14; j++) {
            talia[i * 13 + j - 1] = new Karta;
            talia[i * 13 + j - 1]->przypiszwartosc(j);
            talia[i * 13 + j - 1]->przypiszkolor(i / 2);
            talia[i * 13 + j - 1]->przypiszznak(i);
        }
    }
}

int main() {
    Karta* talia[52];
    inicjalizacjaTalii(talia);
    int a = 0;
    int x = 0;
    char y = '\0';
    char z = '\0';
    int kt = 0;
    
    for (int i = 0; i < 52; i++) {
        std::cout << talia[i]->pobierzkolor() << ", " << talia[i]->pobierzwartosc() << ", " << talia[i]->pobierzznak() << std::endl;
    }
    los1(talia, x, y, z, kt);
    //std::thread l1(los1, talia);
    std::thread l2(los2, talia, x, y, z, kt);
    
    //l1.join();
    l2.join();

    a = menu();
    std::cout << a;
    //if (a == 1)gra();
    delete *talia;
}