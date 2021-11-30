#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define chemin "annuaire5000.csv"

typedef struct structurecsv
{
    char prenom[30], nom[30], ville[40], cp[10], tel[17], mail[50], metier[30];
} scsv;

// adr est l'adresse mémoire de la personne qu'on a envoyé en paramètre de la fonction
// * = pointer

/**
:auteur Elliot Curvat
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

/**
:auteur Elliot Curvat
:entree scsv*adr:char
:pre-cond 
:sortie aucune
:post-cond la ligne qui a pour adresse scsv*adr a été affichée dans le terminal
*/
void printligne(scsv *adr)
{
    printf("%s | %s | %s | %s | %s | %s | %s\n", (*adr).prenom, (*adr).nom, (*adr).ville, (*adr).cp, (*adr).tel, (*adr).mail, (*adr).metier);
}

/**
:auteur Elliot Curvat
:entree aucune
:pre-cond aucune
:sortie aucune
:post-cond le contenu du terminal a été effacé
*/
void clrscr()
{
    system("clear");
}

/**
:auteur Elliot Curvat
:entree aucune
:pre-cond aucune
:sortie selection:int
:post-cond les choix ont été affichés et l'utilisateur a entré un choix
*/
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
    do
        scanf("%d", &selection);
    while (selection < 0 && selection > 7);
    return selection;
}

/**
:auteur Elliot Curvat
:entree scsv*adr:char, numcat:int
:pre-cond 0<=numcat<=6
:sortie un pointeur de type char
:post-cond l'adresse retournée correspond à celle de la catégorie entrée
*/
char *adrfromnumcat(scsv *adr, int numcat)
{
    switch (numcat)
    {
    case 0:
        return (*adr).prenom;
    case 1:
        return (*adr).nom;
    case 2:
        return (*adr).ville;
    case 3:
        return (*adr).cp;
    case 4:
        return (*adr).tel;
    case 5:
        return (*adr).mail;
    case 6:
        return (*adr).metier;
    default:
        return (*adr).prenom;
        break;
    }
}

/**
:auteur Elliot Curvat
:entree numcat:int
:pre-cond 0<=numcat<=6
:sortie char
:post-cond la catégorie qui est retournée correspond bien au numéro associé
*/
char *catefromnum(int numcat)
{
    switch (numcat)
    {
    case 0:
        return ("prénom");
        break;
    case 1:
        return ("nom");
        break;
    case 2:
        return ("ville");
        break;
    case 3:
        return ("code postal");
        break;
    case 4:
        return ("numéro de téléphpone");
        break;
    case 5:
        return ("adresse mail");
        break;
    case 6:
        return ("métier");
        break;
    default:
        return ("erreur lors de la récupération");
    }
}

/**
:auteur Elliot Curvat
:entree scsv*personne:char
:pre-cond
:sortie int
:post-cond
*/
int modifval(scsv *personne)
{
    printf("Quelle est l'information à modifier\n");
    int categorie = seleccategorie();
    if (categorie <= 6 && categorie >= 0)
    {
        // On enlève les possibles retours à la ligne qu'il y a dans stdin pour pouvoir traiter des cases vides
        fflush(stdin);
        printf("Modification de la categorie [%s] : \n", catefromnum(categorie));
        printf("Information actuelle : %s \n", adrfromnumcat(personne, categorie));
        printf("Entrer la nouvelle valeur :\n");
        fgets(adrfromnumcat(personne, categorie), 50, stdin);
        // strlen - 1 parce que c'est comme en algo, si la taille d'un tableau vaut 8, on a des cases qui vont de 0 à 7
        adrfromnumcat(personne, categorie)[strlen(adrfromnumcat(personne, categorie)) - 1] = '\0';
        printf("Client modifié avec succès :\n");
        printligne(personne);
    }
    return (categorie);
}

int main()
{
    // Buffer
    char tab[200];
    // Utile pour savoir là où on se trouve
    int nbligne = 0, nbcol = 0;
    int i, j, k;
    int categorie;
    int retour1, retour2, retour3;
    int idclient;
    char validation;
    char premlet;
    char recherche[50], ainserer[50], recherche1[50], recherche2[50], recherche3[50];
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
                // Il faut envoyer les caractères un par un, donc on utilise j qui est réinitialisé à chaque nouvelle virgule
                ajoutcara(&(tabstruct[nbligne]), nbcol, j, tab[i]);
                j++;
            }
        }
        nbligne++;
    }
    nbligne--;
    // On ferme le fichier quand on a fini de remplir le tableau de structures contenant toutes les lignes
    fclose(fic);

    // --------------------- Menu principal

    int choix1, choix2, choix3, choix4;
    do
    {
        printf("Menu principal\n");
        printf("    0 -- Rechercher parmi les clients\n");
        printf("    1 -- Modifier l'annuaire de clients\n");
        printf("    2 -- Sauvegarder l'annuaire\n");
        printf("    3 -- Quitter le programme\n");
        scanf("%d", &choix1);
        clrscr();
        switch (choix1)
        {
        case 0:
            // Rechercher parmi les clients
            do
            {
                printf("Rechercher parmi les clients\n");
                printf("        0 -- Afficher tous les clients\n");
                printf("        1 -- Afficher les clients remplissant un critère\n");
                printf("        2 -- Afficher un client particulier\n");
                printf("        3 -- Afficher les clients pour lesquels il manque une information\n");
                printf("        4 -- Retour au menu précédent\n");
                scanf("%d", &choix2);
                clrscr();
                switch (choix2)
                {
                case 0:
                    // Afficher tous les clients
                    for (i = 0; i <= nbligne; i++)
                        printligne(&(tabstruct[i]));
                    break;
                case 1:
                    do
                    {
                        printf("Afficher les clients remplissant un critère\n");
                        printf("            0 -- Critère sur le prénom\n");
                        printf("            1 -- Critère sur le nom\n");
                        printf("            2 -- Critère sur la ville\n");
                        printf("            3 -- Critère sur le code postal\n");
                        printf("            4 -- Critère sur le numéro de téléphone\n");
                        printf("            5 -- Critère sur l'adresse mail\n");
                        printf("            6 -- Critère sur le métier\n");
                        printf("            7 -- Retour au menu précédent\n");
                        scanf("%d", &choix3);
                        if (choix3 <= 6 && choix3 >= 0)
                        {
                            printf("                0 -- Commence par...\n");
                            printf("                1 -- Contient...\n");
                            printf("                2 -- Est exactement...\n");
                            scanf("%d", &choix4);
                            switch (choix4)
                            {
                            case 0:
                                printf("Saisir un caractère\n");
                                fflush(stdin);
                                scanf("%c", &premlet);
                                for (i = 0; i <= nbligne; i++)
                                {
                                    if (adrfromnumcat(&tabstruct[i], choix3)[0] == premlet)
                                        printligne(&tabstruct[i]);
                                }
                                break;
                            case 1:
                                // Contient ...
                                printf("Saisir la recherche sur le critère\n");
                                scanf(" %s", recherche);
                                k = 0;
                                for (k = 0; k <= nbligne; k++)
                                {
                                    char *retour4 = strstr(adrfromnumcat(&tabstruct[k], choix3), recherche);
                                    if (retour4)
                                    {
                                        printf("ID : %d ", k);
                                        printligne(&tabstruct[k]);
                                    }
                                }
                                break;
                            case 2:
                                // Est exactement...
                                printf("Saisir la recherche sur le critère\n");
                                scanf(" %s", recherche);
                                k = 0;
                                for (k = 0; k <= nbligne; k++)
                                {
                                    retour1 = strcasecmp(adrfromnumcat(&tabstruct[k], choix3), recherche);
                                    if (retour1 == 0)
                                    {
                                        printf("ID : %d ", k);
                                        printligne(&tabstruct[k]);
                                    }
                                }
                                // choix4 = 3;
                                break;
                            default:
                                break;
                            }
                        }
                    } while (choix3 <= 6 && choix3 >= 0);
                    break;
                case 2:
                    // Afficher un client particulier
                    do
                    {
                        printf("Afficher un client particulier\n");
                        printf("            0 -- Rechercher avec prénom, nom et adresse mail\n");
                        printf("            1 -- Rechercher avec prénom, nom et numéro de téléphone\n");
                        printf("            2 -- Retour au menu précédent\n");
                        scanf("%d", &choix3);
                        clrscr();
                        switch (choix3)
                        {
                        case 0:
                            // Rechercher avec prénom, nom et adresse mail
                            printf("Saisir le prénom\n");
                            scanf(" %s", recherche1);
                            printf("Saisir le nom\n");
                            scanf(" %s", recherche2);
                            printf("Saisir l'adresse mail\n");
                            scanf(" %s", recherche3);
                            for (k = 0; k <= nbligne; k++)
                            {
                                int retour1 = strcasecmp(tabstruct[k].prenom, recherche1);
                                int retour2 = strcasecmp(tabstruct[k].nom, recherche2);
                                int retour3 = strcasecmp(tabstruct[k].mail, recherche3);
                                if (retour1 == 0 && retour2 == 0 && retour3 == 0)
                                {
                                    printf("ID : %d -- ", k);
                                    printligne(&tabstruct[k]);
                                }
                            }
                            break;
                        case 1:
                            // Rechercher avec prénom, nom et numéro de téléphone
                            printf("Saisir le prénom\n");
                            scanf(" %s", recherche1);
                            printf("Saisir le nom\n");
                            scanf(" %s", recherche2);
                            printf("Saisir le numéro de téléphone\n");
                            scanf(" %s", recherche3);
                            for (k = 0; k <= nbligne; k++)
                            {
                                int retour1 = strcasecmp(tabstruct[k].prenom, recherche1);
                                int retour2 = strcasecmp(tabstruct[k].nom, recherche2);
                                int retour3 = strcasecmp(tabstruct[k].tel, recherche3);
                                if (retour1 == 0 && retour2 == 0 && retour3 == 0)
                                {
                                    printf("ID : %d -- ", k);
                                    printligne(&tabstruct[k]);
                                }
                            }
                            break;
                        default:
                            break;
                        }
                    } while (choix3 <= 1 && choix3 >= 0);
                    break;
                case 3:
                    // Afficher les clients pour lesquels il manque une information
                    printf("OK pour 3\n");
                    break;
                default:
                    break;
                }
            } while (choix2 <= 3 && choix2 >= 0);
            break;
        case 1:
            // Modifier l'annuaire des clients
            do
            {
                printf("Modifier l'annuaire des clients\n");
                printf("        0 -- Ajouter un client\n");
                printf("        1 -- Modifier un client\n");
                printf("        2 -- Supprimer un client\n");
                printf("        3 -- Retour au menu précédent\n");
                scanf("%d", &choix2);
                clrscr();
                switch (choix2)
                {
                case 0:
                    // Ajouter un client
                    for (i = 0; i <= 6; i++)
                    {
                        printf("Information à saisir [%s] : ", catefromnum(i));
                        fflush(stdin);
                        fgets(adrfromnumcat(&tabstruct[nbligne], i), 50, stdin);
                        adrfromnumcat(&tabstruct[nbligne], i)[strlen(adrfromnumcat(&tabstruct[nbligne], i)) - 1] = '\0';
                    }
                    printligne(&tabstruct[nbligne]);
                    nbligne++;
                    break;
                case 1:
                    // Modifier un client
                    do
                    {
                        printf("Modifier un client\n");
                        printf("            0 -- Je connais déjà le client à modifier\n");
                        printf("            1 -- Je souhaite faire une recherche exacte\n");
                        printf("            2 -- Retour au menu précédent\n");
                        scanf("%d", &choix3);
                        clrscr();
                        switch (choix3)
                        {
                        case 0:
                            // Je connais déjà le client à modifier
                            printf("OK pour 0\n");
                            break;
                        case 1:
                            // Je souhaite faire une recherche exacte
                            printf("Recherche du client par :\n");
                            categorie = seleccategorie();
                            printf("Saisir les occurrences à afficher\n");
                            scanf(" %s", recherche);
                            k = 0;
                            for (k = 0; k <= nbligne; k++)
                            {
                                retour1 = strcasecmp(adrfromnumcat(&tabstruct[k], categorie), recherche);
                                if (retour1 == 0)
                                {
                                    printf("ID : %d ", k);
                                    printligne(&tabstruct[k]);
                                }
                            }
                            printf("Sélectionner l'id du client que vous voulez modifier\n");
                            scanf("%d", &idclient);
                            printf("Vous allez modifier ce client :\n");
                            printligne(&tabstruct[idclient]);
                            do
                            {
                                categorie = modifval(&tabstruct[idclient]);
                            } while (categorie >= 0 && categorie <= 6);
                            break;
                        default:
                            break;
                        }
                    } while (choix3 <= 1 && choix3 >= 0);

                    break;
                case 2:
                    // Supprimer un client
                    printf("Recherche du client par :\n");
                    categorie = seleccategorie();
                    printf("Saisir les occurrences à afficher\n");
                    scanf(" %s", recherche);
                    for (k = 0; k <= nbligne; k++)
                    {
                        retour1 = strcasecmp(adrfromnumcat(&tabstruct[k], categorie), recherche);
                        if (retour1 == 0)
                        {
                            printf("ID : %d -- ", k);
                            printligne(&tabstruct[k]);
                        }
                    }
                    printf("Sélectionner l'id du client que vous voulez supprimer\n");
                    scanf("%d", &idclient);
                    printf("Êtes-vous certain de vouloir supprimer ce client (y/n) ? Cette action est irréversible\n");
                    scanf(" %c", &validation);
                    if (validation == 'y')
                    {
                        for (i = idclient; i <= nbligne; i++)
                            tabstruct[i] = tabstruct[i + 1];
                        nbligne--;
                        printf("Succès de l'opération\n");
                        printf("Il reste %d clients dans l'annuaire.\n", nbligne);
                    }
                    else
                        printf("Annulation de l'opération\n");
                    break;
                default:
                    break;
                }
            } while (choix2 <= 2 && choix2 >= 0);
            break;
        case 2:
            // Sauvegarder l'annuaire
            do
            {
                printf("Sauvegarder l'annuaire\n");
                printf("            0 -- Je connais déjà le client à modifier\n");
                printf("            1 -- Je souhaite faire une recherche\n");
                printf("            2 -- Revenir au menu précédent\n");
                scanf("%d", &choix2);
                clrscr();
                switch (choix2)
                {
                case 0:
                    // Je connais déjà le client à modifier
                    printf("Ok pour 0\n");
                    break;
                case 1:
                    // Je souhaite faire une recherche
                    printf("Ok pour 1\n");
                    break;
                default:
                    break;
                }
            } while (choix2 <= 1 && choix2 >= 0);
            break;
        case 3:
            // Quitter le programme
            exit(EXIT_SUCCESS);
            break;
        default:
            break;
        }
    } while (choix1 <= 3 && choix1 >= 0);
    return 0;
}