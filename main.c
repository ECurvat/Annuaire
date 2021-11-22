#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define chemin "annuaire5000.csv"

#define taille 100

typedef struct structurecsv
{
    char prenom[30], nom[30], ville[40], cp[10], tel[17], mail[50], metier[30];
} scsv;

// adr est l'adresse mémoire de la personne qu'on a envoyé en paramètre de la fonction
// * = pointer

/*
:entree scsv*adr:char, colonne : int, position : int, cara : char
:pre-cond 
:sortie aucune
:post-cond le caractère cara a été ajouté à la position position dans la catégorie colonne de la structure qui a pour adresse scsv*adr
*/
void ajoutcara(scsv *adr, int colonne, int position, char cara)
{
    switch (colonne)
    {
    case 0:
        (*adr).prenom[position] = cara;
        break;
    case 1:
        (*adr).nom[position] = cara;
        break;
    case 2:
        (*adr).ville[position] = cara;
        break;
    case 3:
        (*adr).cp[position] = cara;
        break;
    case 4:
        (*adr).tel[position] = cara;
        break;
    case 5:
        (*adr).mail[position] = cara;
        break;
    case 6:
        (*adr).metier[position] = cara;
        break;
    }
}

void printligne(scsv *adr)
{
    printf("%s | %s | %s | %s | %s | %s | %s\n", (*adr).prenom, (*adr).nom, (*adr).ville, (*adr).cp, (*adr).tel, (*adr).mail, (*adr).metier);
}

void clear()
{
#if _WIN32 && _WIN64
    system("cls");
#endif
#if __APPLE__
    system("clear");
#endif
}

int seleccategorie()
{
    int selection;
    printf("----------------------\n");
    printf("0 pour le prénom\n");
    printf("1 pour le nom\n");
    printf("2 pour la ville\n");
    printf("3 pour le code postal\n");
    printf("4 pour le téléphone\n");
    printf("5 pour l'email\n");
    printf("6 pour le métier\n");
    printf("7 pour quitter ce menu\n");
    printf("----------------------\n");
    scanf("%d", &selection);
    return selection;
}

int main()
{
    // Buffer
    char tab[200];
    // Utile pour savoir là où on se trouve
    int nbligne = 0;
    int nbcol = 0;
    int i, j, k;
    int categorie;
    char recherche[50], ainserer[50];
    // On crée un tableau qui contient une structure par case --> éviter de faire une structure par personne pour 5000 personnes
    scsv tabstruct[6000];
    FILE *fic = fopen(chemin, "r");
    // Si le fichier est vide, on arrête le programme tt de suite
    if (fic == NULL)
        exit(EXIT_FAILURE);

    // Lecture de chaque ligne une par une
    while (fgets(tab, sizeof(tab), fic) != NULL)
    {
        // On reset nbcol à chaque nouvelle lecture de ligne
        nbcol = 0;
        j = 0;
        // On parcourt chaque ligne
        for (i = 0; tab[i] != '\0'; i++)
        {
            // Dans le parcourt de chaque ligne, on execute le code dessous si on trouve une ,
            // Permet de changer la catégorie, de remplir le tableau  de structures
            if (tab[i] == ',' || tab[i] == '\n')
            {
                // On ajoute un \0 avant de passer à la catégorie suivante quand on détecte une ,
                // But = réduire les bugs possibles
                // On augmente nbcol pour savoir à quelle catégorie on se trouve (nom, prénom...)
                ajoutcara(&(tabstruct[nbligne]), nbcol, j, '\0');
                nbcol++;
                j = 0;
            }
            else
            {
                // On appelle la fonction ajoutcara pour ajouter chaque caractère (tab[i]) un par un dans la bonne structure à la bonne colonne (catégorie) et au bon indice de tableau de catégorie
                // Il faut envoyer les caractères un par un, donc on utilise j qui est réinitialisé à chaque nouvelle ,
                ajoutcara(&(tabstruct[nbligne]), nbcol, j, tab[i]);
                j++;
            }
        }
        nbligne++;
    }
    // On ferme le fichier quand on a fini de remplir le tableau de structures contenant toutes les lignes
    fclose(fic);
    // Si on fait tabstruct[1000], on aura les informations de la ligne 999
    printf("%s\n", tabstruct[2].nom);

    // --------------------- Menu principal
    int choix = -1;
    printf("Sélectionner l'opération à effectuer\n");
    printf("0 pour modifier les données d'un client\n");
    scanf("%d", &choix);
    switch (choix)
    {
    case 0:
        printf("Recherche du client par :\n");
        categorie = seleccategorie();
        printf("Saisir les occurrences à afficher\n");
        scanf(" %s", recherche);
        switch (categorie)
        {
        case 0:
            k = 0;
            for (k = 0; k <= nbligne; k++)
            {
                int retour = strcasecmp(tabstruct[k].prenom, recherche);
                if (retour == 0)
                {
                    printf("ID : %d ", k);
                    printligne(&tabstruct[k]);
                }
            }
            printf("Sélectionner l'id de la ligne que vous voulez modifier\n");
            scanf("%d", &choix);
            clear();
            printf("Vous allez modifier cette ligne :\n");
            printligne(&tabstruct[choix]);
            printf("Quelle est l'information à modifier\n");
            categorie = seleccategorie();
            while (categorie <= 7 && categorie >= 0)
            {
                switch (categorie)
                {
                case 0:
                    printf("Saisir le nouveau prénom pour ce client\n");
                    scanf(" %s", ainserer);
                    for (i = 0; i <= strlen(ainserer); i++)
                        ajoutcara(&(tabstruct[choix]), categorie, i, ainserer[i]);
                    printf("Information à jour :\n");
                    printligne(&tabstruct[choix]);
                    printf("Autre information à modifier ?\n");
                    categorie = seleccategorie();
                    break;
                case 1:
                    printf("Saisir le nouveau nom pour ce client\n");
                    scanf(" %s", ainserer);
                    for (i = 0; i <= strlen(ainserer); i++)
                        ajoutcara(&(tabstruct[choix]), categorie, i, ainserer[i]);
                    printf("Information à jour :\n");
                    printligne(&tabstruct[choix]);
                    printf("Quelle est l'information à modifier\n");
                    categorie = seleccategorie();
                    break;
                case 2:
                    printf("Saisir la nouvelle ville pour ce client\n");
                    scanf(" %s", ainserer);
                    for (i = 0; i <= strlen(ainserer); i++)
                        ajoutcara(&(tabstruct[choix]), categorie, i, ainserer[i]);
                    printf("Information à jour :\n");
                    printligne(&tabstruct[choix]);
                    printf("Quelle est l'information à modifier\n");
                    categorie = seleccategorie();
                    break;
                case 3:
                    printf("Saisir le nouveau code postal pour ce client\n");
                    scanf(" %s", ainserer);
                    for (i = 0; i <= strlen(ainserer); i++)
                        ajoutcara(&(tabstruct[choix]), categorie, i, ainserer[i]);
                    printf("Information à jour :\n");
                    printligne(&tabstruct[choix]);
                    printf("Quelle est l'information à modifier\n");
                    categorie = seleccategorie();
                    break;
                case 4:
                    printf("Saisir le nouveau numéro de téléphone pour ce client\n");
                    scanf(" %s", ainserer);
                    for (i = 0; i <= strlen(ainserer); i++)
                        ajoutcara(&(tabstruct[choix]), categorie, i, ainserer[i]);
                    printf("Information à jour :\n");
                    printligne(&tabstruct[choix]);
                    printf("Quelle est l'information à modifier\n");
                    categorie = seleccategorie();
                    break;
                case 5:
                    printf("Saisir la nouvelle adresse mail pour ce client\n");
                    scanf(" %s", ainserer);
                    for (i = 0; i <= strlen(ainserer); i++)
                        ajoutcara(&(tabstruct[choix]), categorie, i, ainserer[i]);
                    printf("Information à jour :\n");
                    printligne(&tabstruct[choix]);
                    printf("Quelle est l'information à modifier\n");
                    categorie = seleccategorie();
                    break;
                case 6:
                    printf("Saisir le nouveau métier pour ce client\n");
                    scanf(" %s", ainserer);
                    for (i = 0; i <= strlen(ainserer); i++)
                        ajoutcara(&(tabstruct[choix]), categorie, i, ainserer[i]);
                    printf("Information à jour :\n");
                    printligne(&tabstruct[choix]);
                    printf("Quelle est l'information à modifier\n");
                    categorie = seleccategorie();
                    break;
                case 7:
                    printf("Sortie du menu");
                    categorie = -1;
                    break;
                }
            }
            break;
        }
        break;
    }

    return 0;
}
