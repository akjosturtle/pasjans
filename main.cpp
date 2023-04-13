//Tasowanie w osobnym wątku (std::thread i std::ref)


#include <iostream>
#include <vector>
#include <thread>           //std:thread
#include <functional>       //std::ref
#include <algorithm>
#include <iterator>
#include <random>
#include <iomanip>
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
bool wygrana(Karta kupka_docelowa[4]){
     int w = 0;
    for(int i = 0; i < 4; i++)
        if(kupka_docelowa[i].pobierzwartosc() == 13)
            w++;
    if(w == 4)
        return 0;
    else 
        return 1;

}
void wyswietlwartosci(int x){
    using std::cout;
    cout << std::setw(2);
    switch(x){
                case 1: cout << "A";
                    break;
                case 11: cout << "J";
                    break;
                case 12: cout << "Q";
                    break;
                case 13: cout << "K";
                    break;
                default: cout << x;
                    break;
            }
}
void wyswietlznaczki(char x){
    using std::cout;
    if(x == 's'){
        cout << char(3);
    }
    else if(x == 'k'){
        cout << char(4);
    }
    else if(x == 't'){
        cout << char(5);
    }
    else if(x == 'p'){
        cout << char(6);
    }
}
void wyswietlanie(std::vector<Karta> kupka[ik], Karta kupka_docelowa[4], Karta odkladanie[4]){
    using std::cout;
    using std::endl;
    int max = 0;
    cout << endl <<" |  8  |  9  | 10  | 11  |||  12 |  13 |  14 |  15 |" << endl;
    cout << "  -------------------------------------------------" << endl;
    cout << " | ";
    for(int i = 0; i < 4; i++){
        if(odkladanie[i].pobierzwartosc()!=0){
            wyswietlwartosci(odkladanie[i].pobierzwartosc());
            //wyswietlznaczki(odkladanie[i].pobierzznak());
            cout << odkladanie[i].pobierzznak();
        }
        else
            cout << std:: setw(3) << " ";
        cout << " | ";
    }
    cout << "| ";
    for(int i = 0; i < 4; i++){
        if(kupka_docelowa[i].pobierzwartosc()!=0){
            wyswietlwartosci(kupka_docelowa[i].pobierzwartosc());
            //wyswietlznaczki(kupka_docelowa[i].pobierzznak());
            cout << kupka_docelowa[i].pobierzznak();
        }
        else
            cout << std:: setw(3) << " ";
        cout << " | ";
    }
    cout << endl;
    cout <<"  -------------------------------------------------" << endl;
    cout <<"  -------------------------------------------------" << endl;

    for(int j = 0; j < 8; j++){
        if(max < kupka[j].size())
        max = kupka[j].size();
    }
    
    for(int i = 0; i < max; i++){
        cout << "  | ";
        for(int j = 0; j < 8; j++){
            if(kupka[j].size() > i){                    //mozliwe wycieki
                wyswietlwartosci(kupka[j][i].pobierzwartosc());
                //wyswietlznaczki(kupka[j][i].pobierzznak());
                cout << kupka[j][i].pobierzznak();
            }
            else 
                cout << std::setw(3) << "  ";
            cout << " | ";
        }
        cout << endl;
    }
    cout << "  -------------------------------------------------" << endl;
    cout <<"  |  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |" << endl;
    // cout <<"" << endl;
    // cout <<"" << endl;
    // cout <<"" << endl;

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
    wyswietlanie(kupka, kupka_koncowa, odkladanie); 
    int ZJakiej;
    int naJaka;
    bool kupkaCzyNie;
    while (wygrana(kupka_koncowa))
    {
    std::cin >> ZJakiej;
    if(ZJakiej == 999)
        break;
    std::cin >> naJaka;
    Karta kartaW_rece;

    //branie karty z kupki
    if(ZJakiej >= 0 && ZJakiej <= 7){
        kartaW_rece = kupka[ZJakiej].back();
        kupkaCzyNie = true;
    }
    else if(ZJakiej > 7 && ZJakiej < 12){
        if(odkladanie[ZJakiej-8].pobierzwartosc()!=0){
            kartaW_rece = odkladanie[ZJakiej-8];
            kupkaCzyNie = false;
        }
    }
    else continue;

    //odkladanie karty na inna kupke
    if(naJaka >= 0 && naJaka <= 7){ //na kupke kart
       if(kartaW_rece.pobierzwartosc() == kupka[naJaka].back().pobierzwartosc() - 1 ){
            if(kartaW_rece.pobierzkolor() != kupka[naJaka].back().pobierzkolor()){
                kupka[naJaka].push_back(kartaW_rece);
                if(kupkaCzyNie) kupka[ZJakiej].pop_back();
                else odkladanie[ZJakiej].przypiszwartosc(0);
            }
            else continue;
       }
       else continue;
    }
    else if(naJaka > 7 && naJaka < 12){ //na kupke pomocniczą
        if(odkladanie[naJaka-8].pobierzwartosc()==0){
            odkladanie[naJaka-8] = kartaW_rece;
            if(kupkaCzyNie) kupka[ZJakiej].pop_back();
            else odkladanie[ZJakiej].przypiszwartosc(0);
        }
    }
    else if(naJaka >= 12 && naJaka <= 15){ //na kupke koncowa
        if(kartaW_rece.pobierzwartosc() == kupka_koncowa[naJaka-12].pobierzwartosc() + 1){
            if(kartaW_rece.pobierzwartosc() == 1){
                kupka_koncowa[naJaka-12] = kartaW_rece;
                if(kupkaCzyNie) kupka[ZJakiej].pop_back();
                else odkladanie[ZJakiej].przypiszwartosc(0);

            }
            else if(char(kartaW_rece.pobierzznak()) == char(kupka_koncowa[naJaka-12].pobierzznak())){
                kupka_koncowa[naJaka-12] = kartaW_rece;
                if(kupkaCzyNie) kupka[ZJakiej].pop_back();
                else odkladanie[ZJakiej].przypiszwartosc(0);
            }
            else continue;
        }
        else continue;
    }
    else continue;
    wyswietlanie(kupka, kupka_koncowa, odkladanie); 
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
            cout << "s - kier(serce), k - karo, t - trefl, p - pik" << endl;
            cout << "0-7 - wybierane kart z pola gry (od lewej)" << endl;
            cout << "8-11 - wybieranie kart/miejsc sposrod grupy pol pomocniczych" << endl;
            cout << "12-15 - Pola docelowe" << endl;
            cout << "Ruch nalezy wykonac wpisujac kombinacje 2 znakow oddzielonych spacja" << endl;
            cout << "np. 0 8 - ruch przenosi karte z pola gry 0 do pola pomocniczego 8" << endl;
            cout << "wpisanie 999 podczas rozgrywki konczy gre" << endl;
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
    int a = 1;
    // for (int i = 0; i < 52; i++) {
    //     std::cout << talia[i].pobierzkolor() << ", " << talia[i].pobierzwartosc() << ", " << talia[i].pobierzznak() << std::endl;
    // }
    do{
    inicjalizacjaTalii(talia);
    //tasowanie
    std::thread t1(tasowanie, std::ref(talia));
    t1.join();

    // gra(talia);
    a = menu();
    //std::cout << a;
    if (a == 1)
        gra(talia);
    } while(a != 0);
}
