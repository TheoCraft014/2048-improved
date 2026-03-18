#ifndef STAREJOC_H
#define STAREJOC_H

/*biblioteca retine informatii privind starea unui joc si anumite
dimensiuni sau valori numerice importante*/

/* valori ce constata daca jocul a fost pierdut, castigat sau ruleaza */
#define PIERDUT 4
#define CASTIGAT 10
#define MERGE 2

/* deoarece matricea jocului este patratica vom nota
DIM_TABEL ca o variabila ce face referinta la nr de linii
si de coloane */
#define DIM_TABEL 4

/*pentru programe ciclice*/
#define FOREVER 1

/* MARIME_ORIZONTALA si MARIME_VERTICALA sugereaza dimensiunile matricei
pe interfata grafica */
#define MARIME_ORIZONTALA 33
#define MARIME_VERTICALA 16

/* retin ipostaza jocului intr-o structura */
struct Joc
{
    /*matricea jocului*/
    int matrix[DIM_TABEL][DIM_TABEL];

    /*matrice ce memoreaza pozitiile libere*/
    int verific[DIM_TABEL * DIM_TABEL][2];

    /*memorez numarul de casute libere - util in generarea aleatorie*/
    int nrValabil;

    /*variabila ce indica starea unui joc (pierdut,castigat,ruleaza)*/
    int game_over;

    /* calculez punctajul jocului*/
    int punctaj;

    /*timpul necesar ca jocul sa faca o mutare singur*/
    int timp;

    /*ID-ul jocului*/
    int ID;
};

/*retin anumite dimensiuni utile in crearea interfetei grafice a jocului*/
struct Lungimi
{
    /*retin dimensiunile ecranului*/
    int linmax;
    int colmax;

    /*distanta dintre matrice si marginea  dreapta a ecranului*/
    int distantaX;

    /*distanta dintre matrice si marginea superioara a ecranului*/
    int distantaY;

    /* distanta de la matrice la instructiuni*/
    int dMT;

    /*coeficient ce multiplica distantele*/
    int coef;
};

#endif