//Tasowanie w osobnym wątku (std::thread i std::ref)


#include <iostream>
#include <vector>
#include <string>
#include <thread>           //std:thread
#include <functional>       //std::ref
#include <vector>
#include <algorithm>
#include <iterator>
#include <random>
#include <cstring>
//#include <conio.h>
//#include "menu.hpp"

const int ik = 8;

void piszmenu(int a);
int menu();

class Karta {
public:
    Karta();
    ~Karta();

    int pobierzkolor() { return kolor; }
    char pobierzznak() { return znak; }
    int pobierzwartosc() { return wartosc; }

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
            wartosc = warto;
    }

private:
    int kolor;
    char znak;
    int wartosc;
};
Karta::Karta() {
    std::cout << "siema" << std::endl;
    kolor = '0';
    znak = '0';
    wartosc = '0';
}
Karta::~Karta() {
    std::cout << " ";
}

void sterowanie(){
    
}

void gra(std::vector<Karta> &talia){
    std::vector<Karta> kupka[ik];
    Karta kupka_koncowa[4];
    Karta odkladanie[4];
    for(int i = 0; i < 4; i++){
        odkladanie[i].przypiszwartosc(0);
        kupka_koncowa[i].przypiszwartosc(0);
    }
    for(int i = 0; i < 8; i++){
        int ile = 7;
        if(i > 3) ile = 6;
        for(int j = 0; j < ile; j++){
        kupka[i].push_back(talia.back());
        talia.pop_back();
        }  
    }
    while (true)
    {
          
    int ZJakiej;
    int naJaka;
    std::cin >> ZJakiej;
    std::cin >> naJaka;
    Karta kartaW_rece;

    if(ZJakiej >= 0 && ZJakiej <= 7){
        kartaW_rece = kupka[ZJakiej].back();
    }
    else if(ZJakiej > 7 && ZJakiej < 12){
        if(odkladanie[ZJakiej-8].pobierzwartosc()!=0){
            kartaW_rece = odkladanie[ZJakiej-8];
        }
    }
    else continue;

    if(naJaka >= 0 && naJaka <= 7){
       if(kartaW_rece.pobierzwartosc() == kupka[naJaka].back().pobierzwartosc() - 1 ){
            if(kartaW_rece.pobierzkolor() != kupka[naJaka].back().pobierzkolor()){
                kupka[ZJakiej].pop_back();
                kupka[naJaka].push_back(kartaW_rece);
            }
            else continue;
       }
       else continue;
    }
    else if(naJaka > 7 && naJaka < 12){
        if(odkladanie[naJaka-8].pobierzwartosc()==0){
            odkladanie[naJaka-8] = kartaW_rece;
        }
    }
    else if(naJaka > 12 && naJaka < 16){
        if(kartaW_rece.pobierzwartosc() == kupka_koncowa[naJaka-12].pobierzwartosc() + 1){
            if(kartaW_rece.pobierzwartosc() == 1){
                kupka_koncowa[naJaka-12] = kartaW_rece;
            }
            else if(char(kartaW_rece.pobierzznak()) == char(kupka_koncowa[naJaka-12].pobierzznak())){
                kupka_koncowa[naJaka-12] = kartaW_rece;
            }
            else continue;
        }
        else continue;
    }
    else continue;
    }
  
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

void inicjalizacjaTalii(std::vector<Karta> &talia){
    Karta k;
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 14; j++) {
            k.przypiszwartosc(j);
            k.przypiszkolor(i / 2);
            k.przypiszznak(i);
            talia.push_back(k);
        }
    }
}
void tasowanie(std::vector<Karta> &talia){
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(talia.begin(), talia.end(), g);
    
}

int main() {
    std::vector<Karta> talia;
    inicjalizacjaTalii(talia);


    int a = 0;
    
    for (int i = 0; i < 52; i++) {
        std::cout << talia[i].pobierzkolor() << ", " << talia[i].pobierzwartosc() << ", " << talia[i].pobierzznak() << std::endl;
    }

    
    //tasowanie
    std::thread t1(tasowanie, std::ref(talia));
    t1.join();

    for (int i = 0; i < 52; i++) {
        std::cout << talia[i].pobierzkolor() << ", " << talia[i].pobierzwartosc() << ", " << talia[i].pobierzznak() << std::endl;
    }
    
    gra(talia);
    //a = menu();
    //std::cout << a;
    //if (a == 1)gra();
}

// for(int i = 0; i < ik; i++){
    //     std::cout << "kupka" << i << '\n';
    //     for(int j = 0; j < kupka[i].size(); j++){
    //         std::cout << kupka[i][j].pobierzwartosc() << kupka[i][j].pobierzznak() << '\n';
    //     }
    // }

    // switch (ZJakiej)
    // {
    // case 0:
        
    //     break;
    // case 1:
    //     break;
    
    // case 2:
    //     break;
    
    // case 3:
    //     break;
    
    // case 4:
    //     break;
    
    // case 5:
    //     break;
    // case 6:
    //     break;
    
    // case 7:
    //     break;
    
    // case 8:
    //     break;
    
    // case 9:
    //     break;
    
    // case 10:
    //     break;

    // case 11:
    
    // default:
    //     break;
    // }