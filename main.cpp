//Tasowanie w osobnym wątku (std::thread i std::ref)


#include <iostream>
#include <vector>
#include <string>

class Karta {
public:
    Karta();
    ~Karta();

    int pobierzkolor() { return kolor; }
    char pobierzznak() { return znak; }
    char pobierzwartosc() { return wartosc; }

    void przypiszkolor(int kolorek) {
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
    char kolor;
    char znak;
    char wartosc
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


int main() {
    Karta* talia[52];
    int x = 0;
    for (int i = 0; i < 4; i++) {

        for (int j = 1; j < 14; j++) {
            talia[i * 13 + j - 1] = new Karta;
            talia[i * 13 + j - 1]->przypiszwartosc(j);
            talia[i * 13 + j - 1]->przypiszkolor(i / 2);
            talia[i * 13 + j - 1]->przypiszznak(i);
        }
    }
    for (int i = 0; i < 52; i++) {
        std::cout << talia[i]->pobierzkolor() << ", " << talia[i]->pobierzwartosc() << ", " << talia[i]->pobierzznak() << std::endl;
    }
    delete *talia;


}