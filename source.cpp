#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <iomanip>

using namespace std;

void drukuj_macierz(float macierz[6][6], int x = 6, int y = 6);
void generuj_macierz(float macierz[6][6], int x = 6, int y = 6); // matrix with pseudo-random data
void wprowadz_macierz(float macierz[6][6]);
void sumuj_macierz(float macierz[6][6]);
void roznica_macierz(float macierz[6][6]);
bool czy_iterowac(float macierz[6][6]);
void iteracja_macierz(float macierz[6][6]);
void zapisz_wynik_macierz(float macierz[6][6], int iteracja);

int main(){
    const int rejony = 3;
    float macierz_wynikowa[rejony+3][rejony+3] = {0};


    wprowadz_macierz(macierz_wynikowa);
    sumuj_macierz(macierz_wynikowa);
    roznica_macierz(macierz_wynikowa);
    drukuj_macierz(macierz_wynikowa);

    cout << "podaj MAKSYMALNĄ dopuszczalną ilość iteracji\n(rada: zacznij od wartości nie większej niż 50)\n" << "warunek_stop: ";
    int warunek_stop;
    cin >> warunek_stop;
    bool stop = false;

    int iteracja = 0;
    while(czy_iterowac(macierz_wynikowa) && iteracja <= warunek_stop) {
        cout << "=======Iteracja numer " << iteracja+1 << "=======\n";
        iteracja_macierz(macierz_wynikowa);
        iteracja++;
        if(iteracja == warunek_stop){
            cout << "PRZEKROCZONO ZAKRES\nzwiększ warunek_stop\n";
            stop = true;
        }
    }
    if(!stop) zapisz_wynik_macierz(macierz_wynikowa, iteracja);

    return 0;
}

void drukuj_macierz(float macierz[6][6], int x, int y){
    cout << "Rejony\t1\t\t2\t\t3\t\tSuma\t\tGeneracja\tRóżnica\t";
    for(int i = 0 ; i < x; i++){
        if( i == 0) cout << endl << "1\t";
        if( i == 1) cout << endl << "2\t";
        if( i == 2) cout << endl << "3\t";
        if( i == 3) cout << endl << "Suma\t";
        if( i == 4) cout << endl << "Absorbc\t";
        if( i == 5) cout << endl << "Różnica\t";
        for(int k = 0 ; k < y ; k++){
            if( (( k == 3 || k == 4 || k == 5 || k == 6) && ( i == 3 || i == 4 || i == 5))) cout << "\t";
            else printf("%lf\t", macierz[i][k]);
        }
    }
    cout << "\n\n";
}

void generuj_macierz(float macierz[6][6], int x, int y){
    srand(time(NULL));
    for(int i = 0 ; i < x; i++){
        for(int k = 0 ; k < y ; k++){
            if(i==k) macierz[i][k] = 0;
            else macierz[i][k] = rand()% 10 +1;
        }
    }
}

void wprowadz_macierz(float macierz[6][6]){
    for(int rejon = 1 ; rejon < 4 ; rejon++){
        cout << "Podaj ilosc Generacji dla rejonu " << rejon << ": ";
        cin >> macierz[rejon-1][4];
    }
    cout << endl;

    for(int rejon = 1 ; rejon < 4 ; rejon++){
        cout << "Podaj ilosc Absorbcji dla rejonu " << rejon << ": ";
        cin >> macierz[4][rejon-1];
    }
    cout << endl;
        
    for(int rejon1 = 1 ; rejon1 < 4 ; rejon1++){
        cout << "Wiersz  " << rejon1 << endl;
        for(int rejon2 = 1 ; rejon2 < 4 ; rejon2++){
            if(rejon1 == rejon2) macierz[rejon2-1][rejon1-1] = 0;
            else{
                cout << "Podaj ilosc podrozy miedzy rejonem " << rejon1
                     << " a rejonem " << rejon2 << ": ";
                cin >> macierz[rejon1-1][rejon2-1];
            }
        }
        cout << endl;
    }
    cout << endl;
}

void sumuj_macierz(float macierz[6][6]){
    float suma = 0;
    for(int kolumna = 0 ; kolumna < 3 ; kolumna++){
        for(int wiersz = 0 ; wiersz < 3 ; wiersz++){
            suma += macierz[wiersz][kolumna];
            if(wiersz == 2){
                macierz[3][kolumna] = suma;
                suma = 0;
            }
        }
    }
    suma = 0;
    for(int wiersz = 0 ; wiersz < 3 ; wiersz++){
        for(int kolumna = 0 ; kolumna < 3 ; kolumna++){
            suma += macierz[wiersz][kolumna];
            if(kolumna == 2){
                macierz[wiersz][3] = suma;
                suma = 0;
            }
        }
    }
}

void roznica_macierz(float macierz[6][6]){
    for(int kolumna = 0 ; kolumna < 3 ; kolumna++)
        macierz[5][kolumna] = macierz[3][kolumna] - macierz[4][kolumna];

    for(int wiersz = 0 ; wiersz < 3 ; wiersz++)
        macierz[wiersz][5] = macierz[wiersz][3] - macierz[wiersz][4];
}

bool czy_iterowac(float macierz[6][6]){
    for(int kolumna = 0 ; kolumna < 3 ; kolumna++)
        if(macierz[5][kolumna] != 0) return true;
    for(int wiersz = 0 ; wiersz < 3 ; wiersz++)
        if(macierz[wiersz][5] != 0) return true;
    return false;
}

void iteracja_macierz(float macierz[6][6]){
    for(int wiersz = 0 ; wiersz < 3 ; wiersz++){
        for(int kolumna = 0 ; kolumna < 3 ; kolumna++){
            if(wiersz != kolumna) macierz[wiersz][kolumna] = macierz[wiersz][kolumna] / macierz[wiersz][3] * macierz[wiersz][4];
        }
    }
    sumuj_macierz(macierz);
    roznica_macierz(macierz);
    for(int wiersz = 0 ; wiersz < 3 ; wiersz++){
        for(int kolumna = 0 ; kolumna < 3 ; kolumna++){
            if(wiersz != kolumna) macierz[wiersz][kolumna] = macierz[wiersz][kolumna] / macierz[3][kolumna] * macierz[4][kolumna];
        }
    }    
    sumuj_macierz(macierz);
    roznica_macierz(macierz);

    drukuj_macierz(macierz);
}

void zapisz_wynik_macierz(float macierz[6][6], int iteracja){
    ofstream file;
    file.open("wynik.txt", ios::app);
    file << std::fixed;
    file << std::setprecision(2);
    file << "\n~\n\n===Wynik po " << iteracja << " iteracji===\n";
    file << "Rejony\t\t1\t\t2\t\t3";
    for(int wiersz = 0 ; wiersz < 3 ; wiersz++){
        file << "\n" << wiersz+1 << "\t\t";
        for(int kolumna = 0 ; kolumna < 3 ; kolumna++){
            file << macierz[wiersz][kolumna] << "\t\t";
        }
    }
    file.close();
    cout << "Wynik zapisano do pliku \"wynik.txt\".\nJeżeli plik już istniał, wynik został dopisany.\n";
}
