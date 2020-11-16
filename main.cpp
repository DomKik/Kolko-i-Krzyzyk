#include <stdio.h>
#include <stdlib.h>
#define W_PLANSZY 3
#define WYGRANA 1
#define PRZEGRANA -1
#define NIKT_NIE_WYGRAL 0

void wypisz(char plansza[W_PLANSZY][W_PLANSZY])
{
         for(int i=0; i<W_PLANSZY; i++)
         {
                  for(int j=0; j<W_PLANSZY; j++)
                  {
                           printf("%c ", plansza[i][j]);
                  }
                  printf("\n");
         }
}

int kto_wygral(char wygrany)
{
         if(wygrany == 'x') { return WYGRANA; }
         else if(wygrany == 'o'){ return PRZEGRANA; }
         return NIKT_NIE_WYGRAL;
}

int ocen(char plansza[3][3])
{
         char wygrany;
         for(int i=0; i<3; i++)
         {
                  wygrany = plansza[0][i];
                  if(wygrany != ' ' && plansza[0][i] == plansza[1][i] && plansza[1][i] == plansza[2][i]) { return kto_wygral(wygrany); }
                  wygrany = plansza[i][0];
                  if(wygrany != ' ' && plansza[i][0] == plansza[i][1] && plansza[i][1] == plansza[i][2]) { return kto_wygral(wygrany); }
         }
         wygrany = plansza[1][1];
         if(plansza[0][0] == plansza[1][1] && plansza[0][0] == plansza[2][2]) { return kto_wygral(wygrany); }
         if(plansza[0][2] == plansza[1][1] && plansza[0][2] == plansza[2][0]) { return kto_wygral(wygrany); }

         return NIKT_NIE_WYGRAL;
}

int naj_wiersz, naj_kolumna;

int sprawdz_mozliwosci(char plansza[W_PLANSZY][W_PLANSZY], char symbol_gracza, int glebia)
{
         int ocena_wygranej = ocen(plansza), ile_zajetych_pol = 0;
         if(ocena_wygranej != NIKT_NIE_WYGRAL) { return ocena_wygranej; }

         int aktualna_ocena, najlepsza_opcja;
         if(symbol_gracza == 'o') { najlepsza_opcja = WYGRANA + 1; }
         else { najlepsza_opcja = PRZEGRANA - 1; }

         for(int i=0; i<W_PLANSZY; i++)
         {
                  for(int j=0; j<W_PLANSZY; j++)
                  {
                           if(plansza[i][j] == ' ')
                           {
                                    plansza[i][j] = symbol_gracza;
                                    if(symbol_gracza == 'x')
                                    {
                                             aktualna_ocena = sprawdz_mozliwosci(plansza, 'o', glebia + 1);
                                    }
                                    else if(symbol_gracza == 'o')
                                    {
                                             aktualna_ocena = sprawdz_mozliwosci(plansza, 'x', glebia + 1);
                                    }
                                    plansza[i][j] = ' ';
                                    if(symbol_gracza == 'x' && aktualna_ocena > najlepsza_opcja)
                                    {
                                             najlepsza_opcja = aktualna_ocena;
                                             if(glebia == 0)
                                             {
                                                      naj_wiersz = i;
                                                      naj_kolumna = j;
                                             }
                                    }
                                    else if(symbol_gracza == 'o' && aktualna_ocena < najlepsza_opcja)
                                    {
                                             najlepsza_opcja = aktualna_ocena;
                                    }
                           }
                           else { ++ile_zajetych_pol; }
                  }
         }
         if(ile_zajetych_pol > 8) { return ocena_wygranej; }
         return najlepsza_opcja;
}

void wyczysc(char plansza[W_PLANSZY][W_PLANSZY])
{
         for(int i=0; i<W_PLANSZY; i++)
         {
                  for(int j=0; j<W_PLANSZY; j++)
                  {
                           plansza[i][j] = ' ';
                  }
         }
}

int main()
{
    //printf("wygrany w x i o: %d\n", ocen(plansza));
    //sprawdz_mozliwosci(plansza, 'x');
    //printf("naj opcja: %d\n",najlepsza_opcja);
    char plansza[W_PLANSZY][W_PLANSZY];
    wyczysc(plansza);
    int wiersz, kolumna, stan_gry = NIKT_NIE_WYGRAL, zajete_pola = 0;
    while(stan_gry == NIKT_NIE_WYGRAL && zajete_pola < 9)
    {
             printf("Wpisz w ktorym wierszu i kolumnie chcesz postawic 'o':\n");
             scanf("%d %d", &wiersz, &kolumna);
             if(plansza[wiersz][kolumna] == ' ')
             {
                      plansza[wiersz][kolumna] = 'o';
             }
             else
             {
                      while(plansza[wiersz][kolumna] != ' ')
                      {
                               printf("Wpisz w ktorym pustym wierszu i pustej kolumnie chcesz postawic 'o':\n");
                               scanf("%d %d", &wiersz, &kolumna);
                      }
             }
             ++zajete_pola;
             sprawdz_mozliwosci(plansza, 'x', 0);
             plansza[naj_wiersz][naj_kolumna] = 'x';
             ++zajete_pola;
             wypisz(plansza);
             stan_gry = ocen(plansza);
    }
    if(stan_gry == WYGRANA) { printf("KONIEC GRY WYGRAL: x"); }
    else if(stan_gry == PRZEGRANA) { printf("KONIEC GRY WYGRALO: o"); }
    else { printf("KONIEC GRY REMIS"); }
    return 0;
}
