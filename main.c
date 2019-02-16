#include <stdio.h>
#include <stdlib.h>
#include "constante.h"
#include "functii.h"



/*#define NUMAR 52 // numarul de carti din pachet
#define CARTIJUC 6 //numarul de carti ale fiecarui jucator*/

/*struct CARTE
{
    int nume_carte;
    unsigned int model : 3;
    int punctaj;
};

struct JUCATOR
{
    struct CARTE *mana;
    int puncte;
};

struct JUCATOR J1, J2;
struct CARTE *pachet;
struct CARTE *pachet_amestecat;
struct CARTE *pachet_cartijos;

int ord[NUMAR];

void creare_pachet()
{
    int x;
    static const char filename1[] = "pachet_carti.txt";
    static const char filename2[] = "pachet_carti_model.txt";
    static const char filename3[] = "pachet_carti_punctaj.txt";
    pachet = (struct CARTE*) malloc (NUMAR * sizeof(struct CARTE));
    FILE *file1 = fopen ( filename1, "r" );
    FILE *file2 = fopen ( filename2, "r" );
    FILE *file3 = fopen ( filename3, "r" );
    if ( file1 != NULL )
    {
        int i = 0;
        while (!feof (file1))
        {
            fscanf (file1, "%d", &x);
            pachet[i].nume_carte = x;
            i++;
        }

    }
    else
    {
        printf("Eroare la deschiderea fisierului cu valoarea cartilor-file1"); // atunci cand fisierul 1 nu se poate deschide
    }

    if ( file2 != NULL )
    {
        int i = 0;
        while (!feof (file2))
        {
            fscanf (file2, "%d", &x);
            pachet[i].model = x;
            i++;
        }

    }
    else
    {
        printf("Eroare la deschiderea fisierului cu modelul de carte-file2"); //atunci and fisierul 2 nu se poate deschide
    }

    if ( file3 != NULL )
    {
        int i = 0;
        while (!feof (file3))
        {
            fscanf (file3, "%d", &x);
            pachet[i].punctaj = x;
            i++;
        }

    }
    else
    {
        printf("Eroare la deschiderea fisierului cu punctajul cartilor-file3"); //atunci cand fisierul file3 nu se poate deschide
    }
    fclose (file1);// inchiderea fisierelor
    fclose (file2);
    fclose (file3);
}

int give_rand(int ord[])
{

    srand(time(NULL));//atribuie un numar la intamplare  intre 2-52
    int r = rand()%52;

    while(ord[r] != 0)//verifica daca numarul este bifat sau nu,daca este atunci atribuie un alt numar intre 2-52
        r = rand()%52;
    return r;
}


void amestecare_pachet(int ord[])
{
    pachet_amestecat = (struct CARTE*) malloc (NUMAR * sizeof(struct CARTE));//realizeaza un pachet de 52 de carti amestecat
    int i;
    for(i=0; i<NUMAR; i++)
    {
        int rez = give_rand(ord);
        ord[rez] = 1;
        pachet_amestecat[i].nume_carte = pachet[rez].nume_carte;//atribuie fiecarei carti valoarea,modelul si punctajul
        pachet_amestecat[i].model = pachet[rez].model;
        pachet_amestecat[i].punctaj = pachet[rez].punctaj;
    }

}

void imparte_carti() //impartirea cartilor pentru prima runda si eliminarea acestora din pachetul amestecat
{
    int i;
    J1.mana = (struct CARTE*) malloc (CARTIJUC * sizeof(struct CARTE));
    J2.mana = (struct CARTE*) malloc (CARTIJUC * sizeof(struct CARTE));
    pachet_cartijos = (struct CARTE*) malloc (52 * sizeof(struct CARTE));
    for (i=0; i<6; i++)
    {
        J1.mana[i].nume_carte=pachet_amestecat[i].nume_carte;
        J1.mana[i].model=pachet_amestecat[i].model;
        J1.mana[i].punctaj=pachet_amestecat[i].punctaj;
        pachet_amestecat[i].nume_carte = 0;//eliminarea cartilor impartite din pachetul amestecat pt jucatorul 1
        pachet_amestecat[i].model=0;
        pachet_amestecat[i].punctaj=0;

    }
    for(i=6; i<12; i++)
    {
        J2.mana[i-6].nume_carte=pachet_amestecat[i].nume_carte;
        J2.mana[i-6].model=pachet_amestecat[i].model;
        J2.mana[i-6].punctaj=pachet_amestecat[i].punctaj;
        pachet_amestecat[i].nume_carte=0;//eliminarea cartilor impartite din pachetul amestecat pt jucatorul 2
        pachet_amestecat[i].model=0;
        pachet_amestecat[i].punctaj=0;
    }
    for(i=12; i<16; i++)
    {
        pachet_cartijos[i-12].nume_carte=pachet_amestecat[i].nume_carte;
        pachet_cartijos[i-12].model=pachet_amestecat[i].model;
        pachet_cartijos[i-12].punctaj=pachet_amestecat[i].punctaj;
        pachet_amestecat[i].nume_carte=0;//eliminarea cartilor care au fost puse jos din pachetul amestecat
        pachet_amestecat[i].model=0;
        pachet_amestecat[i].punctaj=0;


    }

}
void Joc_1_2_3()//realizeaza punctajul fiecarui jucator si elimina cartile pentru fiecare punctaj obtinut
{
    int i,j;


    int S1=0,S2=0; // reprezinta punctele adunate de cei doi jucatori dupa runda curenta
    for(i=0; i<52; i++)
    {
        if (pachet_cartijos[i].nume_carte != 0)//conditia ca , ce se afla jos sa existe
        {
            for(j=0; j<CARTIJUC; j++)//cautarea cartilor pt jucatorul 1 care reprezinta puncte si se afla printre cartile de jos
                if(pachet_cartijos[i].nume_carte==J1.mana[j].nume_carte && ((pachet_cartijos[i].nume_carte == 2 && pachet_cartijos[i].model == 2) || pachet_cartijos[i].nume_carte > 9))
                {
                    if (pachet_cartijos[i].nume_carte == 2)//conditia speciala pentru 2 de trefla
                        S1=S1+1;
                    else
                        S1=S1+2;
                    pachet_cartijos[i].nume_carte=0;//eliminarea cartilor corespunzatoare fiecarui punctaj atat din pachetul de jos cat si din mana jucatorului
                    pachet_cartijos[i].model=0;
                    pachet_cartijos[i].punctaj=0;
                    J1.mana[j].nume_carte=0;
                    J1.mana[j].model=0;
                    J1.mana[j].punctaj=0;


                }
        }
    }
    J1.puncte=J1.puncte+S1;//adunarea punctelor pt jucatorul 1
    int index;
    index=0;
    for(i=0; i<CARTIJUC; i++)
    {
        if(J1.mana[i].nume_carte != 0)// cauta cartea care nu a fost luata din mana
        {
            while(pachet_cartijos[index].nume_carte!=0)//cauta pozitia pe care sa puna cartea neluata din mana jucatorului
                index = index+1;
            pachet_cartijos[index].nume_carte=J1.mana[i].nume_carte;//completeaza sirul cartilor de jos cu cartile nealese din mana jucatorului 1
            pachet_cartijos[index].model=J1.mana[i].model;
            pachet_cartijos[index].punctaj=J1.mana[i].punctaj;

        }
    }


    for(i=0; i<52; i++)
    {
        if (pachet_cartijos[i].nume_carte != 0)//conditia ca ce se afla jos sa existe
        {
            for(j=0; j<CARTIJUC; j++)//cautarea cartilor pt J2 care sunt puncte si se afla printre cartile de jos
                if(pachet_cartijos[i].nume_carte==J2.mana[j].nume_carte && ((pachet_cartijos[i].nume_carte == 2 && pachet_cartijos[i].model == 2) || pachet_cartijos[i].nume_carte > 9))
                {
                    if (pachet_cartijos[i].nume_carte == 2)//conditia speciala pt 2 de trefla
                        S2=S2+1;
                    else
                        S2=S2+2;
                    pachet_cartijos[i].nume_carte=0;//eliminarea cartilor alese pentru fiecare punctaj al jucatorului 2 atat de jos cat si din mana acestuia
                    pachet_cartijos[i].model=0;
                    pachet_cartijos[i].punctaj=0;
                    J2.mana[j].nume_carte=0;
                    J2.mana[j].model=0;
                    J2.mana[j].punctaj=0;


                }
        }
    }
    J2.puncte=J2.puncte+S2;//insumarea punctajului pt jucatorul 2
    index=0;
    for(i=0; i<CARTIJUC; i++)
    {
        if(J2.mana[i].nume_carte!=0)// cauta cartea care nu a fost luata din mana
        {
            while(pachet_cartijos[index].nume_carte!=0)//cauta pozitia pe care sa puna cartea neluata din mana jucatorului 2
                index = index+1;
            pachet_cartijos[index].nume_carte=J2.mana[i].nume_carte;//completeaza sirul cartilor de jos cu cartile nealese din mana jucatorului 2
            pachet_cartijos[index].model=J2.mana[i].model;
            pachet_cartijos[index].punctaj=J2.mana[i].punctaj;

        }
    }



    free(J1.mana);//elibereaza memoria alocata pentru cartile din mana ale celor 2 jucatori
    free(J2.mana);
}


void imparte_carti_jucatori()//realizeaza urmatoarea impartire a cartilor
{
    int i,j;
    J1.mana = (struct CARTE*) malloc (CARTIJUC * sizeof(struct CARTE));
    J2.mana = (struct CARTE*) malloc (CARTIJUC * sizeof(struct CARTE));
    int contor=0;
    while (pachet_amestecat[contor].nume_carte == 0)//cauta pozitia unde exista carte
    {
        contor++;
    }
    i = contor;
    for (j=i; j<contor+6; j++)//atribuie jucatorului 1 6 carti in mana
    {
        J1.mana[j-contor].nume_carte=pachet_amestecat[j].nume_carte;
        J1.mana[j-contor].model=pachet_amestecat[j].model;
        J1.mana[j-contor].punctaj=pachet_amestecat[j].punctaj;
        pachet_amestecat[j].nume_carte = 0;//eliminarea cartilor impartite din pachet
        pachet_amestecat[j].model=0;
        pachet_amestecat[j].punctaj=0;

    }
    int contor2 = contor+6;//pt a incepe de la a 7-a pozitie(pt a imparti urmatoarele 6 carti  ale jucatorului 2 in ordine)
    for(j=contor2; j<contor2+6; j++)//ii atribuie 6 carti jucatorului 2
    {
        J2.mana[j-contor2].nume_carte=pachet_amestecat[j].nume_carte;
        J2.mana[j-contor2].model=pachet_amestecat[j].model;
        J2.mana[j-contor2].punctaj=pachet_amestecat[j].punctaj;
        pachet_amestecat[j].nume_carte=0;//eliminarea din pachet a cartilor pentru jucatorul 2
        pachet_amestecat[j].model=0;
        pachet_amestecat[j].punctaj=0;
    }
}
void eliberare_memorie()//pentru a elibera memorie la sfarsit
{
    free(pachet);
    free(pachet_amestecat);
    free(pachet_cartijos);
    free(J1.mana);
    free(J2.mana);
}
void start_joc()
{
    int i;
    printf("      ********************************** CARTILE NOROCOASE ******************************      " );
    printf("\n");
    enum runde
    {
        r1=1,
        r2,
        r3,
        r4
    };
    creare_pachet();//realizeaza pachetul,citindu-l din fisier
    printf("    Pachetul amestecat este : \n");
    printf("\n");

    amestecare_pachet(ord);//afiseaza tot pachetul amestecat
    for(i=0; i<52; i++)
    {
        printf("[%d , ",pachet_amestecat[i].nume_carte);
        if(pachet_amestecat[i].model==1) printf("inima rosie] ");
        if(pachet_amestecat[i].model==2) printf("trefla] ");
        if(pachet_amestecat[i].model==3) printf("inima neagra] ");
        if(pachet_amestecat[i].model==4) printf("romb] ");
        printf("\n");
    }
    printf("\n");

    imparte_carti();//imparte primul set de carti fiecarui jucator si imparte si cartile de jos

    printf("    Cartile de jos sunt: ");
    printf("\n");
    for(i=0; i<52; i++)
        if (pachet_cartijos[i].nume_carte !=0)
        {
            printf("[%d , ",pachet_cartijos[i].nume_carte);
            if(pachet_cartijos[i].model == 1)
                printf("inima rosie]  ");
            if(pachet_cartijos[i].model == 2)
                printf("trefla]  ");
            if(pachet_cartijos[i].model == 3)
                printf("inima neagra]  ");
            if(pachet_cartijos[i].model == 4)
                printf("romb]  ");
            printf("\n");
        }

    printf("\n\n");
    printf("    Cartile lui J1: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {
        printf("[%d , ",J1.mana[i].nume_carte);
        if(J1.mana[i].model == 1)
            printf("inima rosie] ");
        if(J1.mana[i].model == 2)
            printf("trefla] ");
        if(J1.mana[i].model == 3)
            printf("inima neagra] ");
        if(J1.mana[i].model == 4)
            printf("romb] ");
        printf("\n");
    }


    printf("\n");

    printf("    Cartile lui J2: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {
        printf("[%d , ",J2.mana[i].nume_carte);
        if(J2.mana[i].model == 1)
            printf("inima rosie]  ");
        if(J2.mana[i].model == 2)
            printf("trefla]  ");
        if(J2.mana[i].model == 3)
            printf("inima neagra]  ");
        if(J2.mana[i].model == 4)
            printf("romb]  ");
        printf("\n");
    }


    printf("\n");

    printf("=================================== RUNDA %d=====================================\n",r1);
    Joc_1_2_3();//realizeaza punctajul jucatorilor si situatia cartilor fiecaruia si a cartilor de jos
    printf("    Cartile lui J1: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {
        if (J1.mana[i].nume_carte>1 && J1.mana[i].nume_carte<53)//afiseaza cartile doar daca exista(daca nu au fost luate)
        {
            printf("[%d , ",J1.mana[i].nume_carte);
            if(J1.mana[i].model == 1)
                printf("inima rosie] ");
            if(J1.mana[i].model == 2)
                printf("trefla] ");
            if(J1.mana[i].model == 3)
                printf("inima neagra] ");
            if(J1.mana[i].model == 4)
                printf("romb] ");
            printf("\n");
        }

    }


    printf("\n");

    printf("    Cartile lui J2: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {
        if (J2.mana[i].nume_carte>1 && J2.mana[i].nume_carte<53)//afiseaza doar cartile existente( cele care nu au fost luate)
        {
            printf("[%d , ",J2.mana[i].nume_carte);
            if(J2.mana[i].model == 1)
                printf("inima rosie]  ");
            if(J2.mana[i].model == 2)
                printf("trefla]  ");
            if(J2.mana[i].model == 3)
                printf("inima neagra]  ");
            if(J2.mana[i].model == 4)
                printf("romb]  ");
            printf("\n");
        }
    }


    printf("\n");
    printf("    Cartile de jos sunt: ");
    printf("\n");
    for(i=0; i<52; i++)
        if (pachet_cartijos[i].nume_carte !=0)
        {
            printf("[%d , ",pachet_cartijos[i].nume_carte);
            if(pachet_cartijos[i].model == 1)
                printf("inima rosie]  ");
            if(pachet_cartijos[i].model == 2)
                printf("trefla]  ");
            if(pachet_cartijos[i].model == 3)
                printf("inima neagra]  ");
            if(pachet_cartijos[i].model == 4)
                printf("romb]  ");
            printf("\n");
        }


    printf("\n");
    printf("    Puncte J1 %d \n",J1.puncte);
    printf("    Puncte J2 %d \n ",J2.puncte);
    printf("\n");
    printf("\n");


    imparte_carti_jucatori();//imparte cartile pentru runda urmatoare celor 2 jucatori
    printf("-----------Impart cartile pentru a %d-a runda------------\n",r2);
    printf("    Cartile lui J1: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {
        printf("[%d , ",J1.mana[i].nume_carte);
        if(J1.mana[i].model == 1)
            printf("inima rosie] ");
        if(J1.mana[i].model == 2)
            printf("trefla] ");
        if(J1.mana[i].model == 3)
            printf("inima neagra] ");
        if(J1.mana[i].model == 4)
            printf("romb] ");
        printf("\n");
    }


    printf("\n");

    printf("    Cartile lui J2: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {
        printf("[%d , ",J2.mana[i].nume_carte);
        if(J2.mana[i].model == 1)
            printf("inima rosie]  ");
        if(J2.mana[i].model == 2)
            printf("trefla]  ");
        if(J2.mana[i].model == 3)
            printf("inima neagra]  ");
        if(J2.mana[i].model == 4)
            printf("romb]  ");
        printf("\n");
    }


    printf("\n");
    printf("\n");
    printf("=================================== RUNDA %d=====================================\n",r2);
    Joc_1_2_3();//calculeaza punctajul si situatia cartilor din mana ale fiecarui jucator si a cartilor de jos
    printf("    Cartile lui J1: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {
        if (J1.mana[i].nume_carte>1 && J1.mana[i].nume_carte<53) //afiseaza doar cartile existente(care nu au fost luate)
        {
            printf("[%d , ",J1.mana[i].nume_carte);
            if(J1.mana[i].model == 1)
                printf("inima rosie]  ");
            if(J1.mana[i].model == 2)
                printf("trefla]  ");
            if(J1.mana[i].model == 3)
                printf("inima neagra]  ");
            if(J1.mana[i].model == 4)
                printf("romb]  ");
            printf("\n");
        }
    }
    printf("\n");

    printf("    Cartile lui J2: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {

        if (J2.mana[i].nume_carte>1 && J2.mana[i].nume_carte<53) //afiseaza doar cartile existente(care nu au fost luate)
        {
            printf("[%d , ",J2.mana[i].nume_carte);
            if(J2.mana[i].model == 1)
                printf("inima rosie]  ");
            if(J2.mana[i].model == 2)
                printf("trefla]  ");
            if(J2.mana[i].model == 3)
                printf("inima neagra]  ");
            if(J2.mana[i].model == 4)
                printf("romb]  ");
            printf("\n");
        }
    }

    printf("\n");

    printf("    Cartile de jos sunt: ");//afiseaza situatia curenta a cartilor de jos
    printf("\n");
    for(i=0; i<52; i++)
        if (pachet_cartijos[i].nume_carte !=0)
        {
            printf("[%d , ",pachet_cartijos[i].nume_carte);
            if(pachet_cartijos[i].model == 1)
                printf("inima rosie]  ");
            if(pachet_cartijos[i].model == 2)
                printf("trefla]  ");
            if(pachet_cartijos[i].model == 3)
                printf("inima neagra]  ");
            if(pachet_cartijos[i].model == 4)
                printf("romb]  ");
            printf("\n");
        }
    printf("\n");
    printf("\n");
    printf("    Puncte J1 %d \n",J1.puncte);
    printf("    Puncte J2 %d \n ",J2.puncte);
    printf("\n");
    printf("\n");


    imparte_carti_jucatori();//imparte cartile celor 2 jucatori pentru urmatoare runda
    printf("-----------Impart cartile pentru a %d-a runda------------\n",r3);
    printf("    Cartile lui J1: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {

        printf("[%d , ",J1.mana[i].nume_carte);
        if(J1.mana[i].model == 1)
            printf("inima rosie] ");
        if(J1.mana[i].model == 2)
            printf("trefla] ");
        if(J1.mana[i].model == 3)
            printf("inima neagra] ");
        if(J1.mana[i].model == 4)
            printf("romb] ");
        printf("\n");
    }


    printf("\n");

    printf("    Cartile lui J2: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {
        printf("[%d , ",J2.mana[i].nume_carte);
        if(J2.mana[i].model == 1)
            printf("inima rosie]  ");
        if(J2.mana[i].model == 2)
            printf("trefla]  ");
        if(J2.mana[i].model == 3)
            printf("inima neagra]  ");
        if(J2.mana[i].model == 4)
            printf("romb]  ");
        printf("\n");
    }


    printf("\n");

    printf("=================================== RUNDA %d=====================================\n",r3);
    Joc_1_2_3();//calculeaza punctajul fiecarui jucator si realizeaza situatie cartilor din mana ale jucatorilor si a cartilor de jos
    printf("    Cartile lui J1: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {
        if (J1.mana[i].nume_carte>1 && J1.mana[i].nume_carte<53) //afiseaza doar cartile existente ( care nu au fost luate)
        {
            printf("[%d , ",J1.mana[i].nume_carte);
            if(J1.mana[i].model == 1)
                printf("inima rosie]  ");
            if(J1.mana[i].model == 2)
                printf("trefla]  ");
            if(J1.mana[i].model == 3)
                printf("inima neagra]  ");
            if(J1.mana[i].model == 4)
                printf("romb]  ");
            printf("\n");
        }
    }

    printf("\n");

    printf("    Cartile lui J2: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {

        if (J2.mana[i].nume_carte>1 && J2.mana[i].nume_carte<53) //afiseaza doar cartile existente(care nu au fost luate)
        {
            printf("[%d ,  ",J2.mana[i].nume_carte);
            if(J2.mana[i].model == 1)
                printf("inima rosie]  ");
            if(J2.mana[i].model == 2)
                printf("trefla]  ");
            if(J2.mana[i].model == 3)
                printf("inima neagra]  ");
            if(J2.mana[i].model == 4)
                printf("romb]  ");
            printf("\n");
        }
    }

    printf("\n");

    printf("    Cartile de jos sunt: ");
    printf("\n");
    for(i=0; i<52; i++)
        if (pachet_cartijos[i].nume_carte !=0)
        {
            printf("[%d ,  ",pachet_cartijos[i].nume_carte);
            if(pachet_cartijos[i].model == 1)
                printf("inima rosie]  ");
            if(pachet_cartijos[i].model == 2)
                printf("trefla]  ");
            if(pachet_cartijos[i].model == 3)
                printf("inima neagra]  ");
            if(pachet_cartijos[i].model == 4)
                printf("romb]  ");
            printf("\n");
        }
    printf("\n");
    printf("    Puncte J1  %d \n",J1.puncte);
    printf("    Puncte J2 %d \n ",J2.puncte);
    printf("\n");
    printf("\n");




    imparte_carti_jucatori();//imparte cartile celor 2 jucatori pentru ultima runda
    printf("-----------Impart cartile pentru a %d-a runda------------\n",r4);
    printf("    Cartile lui J1: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {
        printf("[%d , ",J1.mana[i].nume_carte);
        if(J1.mana[i].model == 1)
            printf("inima rosie] ");
        if(J1.mana[i].model == 2)
            printf("trefla] ");
        if(J1.mana[i].model == 3)
            printf("inima neagra] ");
        if(J1.mana[i].model == 4)
            printf("romb] ");
        printf("\n");
    }


    printf("\n");

    printf("    Cartile lui J2: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {
        printf("[%d , ",J2.mana[i].nume_carte);
        if(J2.mana[i].model == 1)
            printf("inima rosie]  ");
        if(J2.mana[i].model == 2)
            printf("trefla]  ");
        if(J2.mana[i].model == 3)
            printf("inima neagra]  ");
        if(J2.mana[i].model == 4)
            printf("romb]  ");
        printf("\n");
    }


    printf("\n");


    printf("=================================== RUNDA %d=====================================\n",r4);
    Joc_1_2_3();//calculeaza punctajul fiecarui jucator si situatia curenta a cartilor din mana ale jucatorilor si a cartilor de jos
    printf("    Cartile lui J1: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {
        if (J1.mana[i].nume_carte>1 && J1.mana[i].nume_carte<53) //afiseaza doar daca cartile exista(nu au fost luate)
        {
            printf("[%d , ",J1.mana[i].nume_carte);
            if(J1.mana[i].model == 1)
                printf("inima rosie]  ");
            if(J1.mana[i].model == 2)
                printf("trefla]  ");
            if(J1.mana[i].model == 3)
                printf("inima neagra]  ");
            if(J1.mana[i].model == 4)
                printf("romb]  ");
            printf("\n");
        }
    }
    printf("\n");

    printf("    Cartile lui J2: ");
    printf("\n");
    for(i=0; i<CARTIJUC; i++)
    {

        if (J2.mana[i].nume_carte>1 && J2.mana[i].nume_carte<53) //afiseaza doar daca cartile exista(nu au fost luate)
        {
            printf("[%d , ",J2.mana[i].nume_carte);
            if(J2.mana[i].model == 1)
                printf("inima rosie]  ");
            if(J2.mana[i].model == 2)
                printf("trefla]  ");
            if(J2.mana[i].model == 3)
                printf("inima neagra]  ");
            if(J2.mana[i].model == 4)
                printf("romb]  ");
            printf("\n");
        }
    }
    printf("\n");

    printf("    Cartile de jos sunt: ");
    printf("\n");
    for(i=0; i<52; i++)
        if (pachet_cartijos[i].nume_carte !=0)
        {
            printf("[%d , ",pachet_cartijos[i].nume_carte);
            if(pachet_cartijos[i].model == 1)
                printf("inima rosie]  ");
            if(pachet_cartijos[i].model == 2)
                printf("trefla]  ");
            if(pachet_cartijos[i].model == 3)
                printf("inima neagra]  ");
            if(pachet_cartijos[i].model == 4)
                printf("romb]  ");
            printf("\n");
        }
    printf("\n");
    printf("    Puncte J1  %d \n",J1.puncte);
    printf("    Puncte J2 %d \n ",J2.puncte);
    printf("\n");
    printf("\n");
    printf("=================================== SCOR =====================================\n");
    if(J1.puncte>J2.puncte)//realizeaza comparatia punctajelor celor  jucatori si desemneaza castigatorul jocului
        printf("JUCATORUL 1 a castigat");
    else if (J1.puncte<J2.puncte)
        printf("JUCATORUL 2 a castigat");
    else
        printf("    EGALITATE!");







}*/

int main()
{
    start_joc();
//  eliberare_memorie();





    return 0;
}

