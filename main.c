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
void clear()
{
#if _WIN32 || _WIN64
    system("cls");
#else
    system("clear");
#endif
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
        return("prénom");
        break;
        case 1:
        return("nom");
        break;
        case 2:
        return("ville");
        break;
        case 3:
        return("code postal");
        break;
        case 4:
        return("numéro de téléphpne");
        break;
        case 5:
        return("adresse mail");
        break;
        case 6:
        return("métier");
        break;
    }
}


void modifval(scsv *personne , char categorie){
    // On enlève les possibles retours à la ligne qu'il y a dans stdin
    fflush(stdin);
    printf("Modification de la categorie [%s] : \n",catefromnum(categorie));
    printf("Information actuelle : %s \n", adrfromnumcat(personne,categorie));
    printf("Entrer la nouvelle valeur :\n");
    fgets(adrfromnumcat(personne,categorie),50,stdin);
    // strlen - 1 parce que c'est comme en algo, si la taille d'un tableau vaut 8, on a des cases qui vont de 0 à 7
    adrfromnumcat(personne,categorie)[strlen(adrfromnumcat(personne,categorie))-1] = '\0';
    printligne(personne);
    printf("\n");
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
                // Il faut envoyer les caractères un par un, donc on utilise j qui est réinitialisé à chaque nouvelle virgule
                ajoutcara(&(tabstruct[nbligne]), nbcol, j, tab[i]);
                j++;
            }
        }
        nbligne++;
    }
    // On ferme le fichier quand on a fini de remplir le tableau de structures contenant toutes les lignes
    fclose(fic);

    // --------------------- Menu principal
    int choix = -1;
    printf("Sélectionner l'opération à effectuer\n");
    printf("0 pour modifier les données d'un client\n");
    printf("1 pour ajouter un client");
    scanf("%d", &choix);
    switch (choix)
    {
    case 0:
        printf("Recherche du client par :\n");
        categorie = seleccategorie();
        printf("Saisir les occurrences à afficher\n");
        scanf(" %s", recherche);
        k = 0;
        for (k = 0; k <= nbligne; k++)
        {
            int retour = strcasecmp(adrfromnumcat(&tabstruct[k], categorie), recherche);
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
        while (categorie <= 7 && categorie >= 0 && categorie != -1)
        {
            switch (categorie)
            {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                modifval(&tabstruct[choix],categorie);
                categorie = seleccategorie();
                break;

            case 7:
                printf("Sortie du menu");
                categorie = -1;
                break;
            }
        }
        break;
    case 1:
        for (i = 0; i <= 6; i++)
        {
            printf("Information à saisir [%s] : ", catefromnum(i));
            fflush(stdin);
            fgets(adrfromnumcat(&tabstruct[nbligne],i),50,stdin);
            adrfromnumcat(&tabstruct[nbligne],i)[strlen(adrfromnumcat(&tabstruct[nbligne],i))-1] = '\0';
        }
        printligne(&tabstruct[nbligne]);
        nbligne++;
    }

    return 0;
}
