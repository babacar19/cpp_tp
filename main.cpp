#include <iostream>
//#include <locale>
#include "FileHandling.hpp"
#include "CWordStats.hpp"
#include "CIndex.h"
using namespace std;


int main()
{
    // Mise en place de la locale pour que la conversion de casse (std::lower) puisse g�rer les carat�res accentu�s
    // Par d�fault la locale en C (codage ASCII 7 bits) ; sous Unix, la locale s'�crit "fr_FR"

#ifdef __WIN32
    std::locale::global(std::locale("fr-FR"));
#else
    std::locale::global(std::locale("fr_FR.UTF-8"));
#endif

    CWordStats stats;
    //...

    IterateOnFileDir<100>("./../textes/output/", stats);//calcul des fr�quences
    stats.generateStopWordsList("../stopWordsList.txt");// generation de notre stopWordlist
    CIndex index("../stopWordsList.txt");//creation d'index renvers�
    IterateOnFileDir<100>("./../textes/output/", index);//utilisation de l'index renvers�

    // test de la fonction PrintDocs sur quelques mots
    /*
     * si vous �tes sous unix , vous pouvez v�rifier la conformit� du r�sultat
     * avec grep -ril 'chaine' ./emplacement des fichiers
     */
    index.PrintDocs("centrafrique");
    //index.PrintDocs("albanie");
    //index.PrintDocs("croissante");
    //index.PrintDocs("centrafrique");




    return(EXIT_SUCCESS);
}