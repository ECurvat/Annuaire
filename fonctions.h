#define taillexxs 6
#define taillexs 15
#define tailles 20
#define taillem 30
#define taillel 40

typedef struct structurecsv
{
	char prenom[taillem], nom[taillem], ville[taillem], cp[taillexxs], tel[taillexs], mail[taillel], metier[tailles];
} scsv;

/**
:referent Elliot Curvat
:entree adr: pointeur de structure scsv, colonne : int, position : int, cara : char
:post-cond le caractere cara a ete ajoute a la position position dans la categorie colonne de la structure qui a pour adresse adr
*/
void ajoutcara(scsv *adr, int colonne, int position, char cara);

/**
:referent Elliot Curvat et Kieran Limbourg
:entree adr: pointeur de structure scsv
:post-cond la ligne qui a pour adresse scsv*adr a ete affichee dans le terminal
*/
void printligne(scsv *adr);

/**
:referent Elliot Curvat
:post-cond le contenu du terminal a ete efface
*/
void clrscr();

/**
:referent Elliot Curvat
:sortie selection:int
:post-cond les choix ont ete affiches et le choix selectionne est retourne
*/
int seleccategorie();

/**
:referent Elliot Curvat
:entree adr: pointeur de structure scsv, numcat:int
:pre-cond 0<=numcat<=6
:sortie un pointeur de type char
:post-cond l'adresse retournee correspond a celle de la categorie entree
*/
char *adrfromnumcat(scsv *adr, int numcat);

/**
:referent Elliot Curvat
:entree numcat:int
:pre-cond 0<=numcat<=6
:sortie char
:post-cond la categorie qui est retournee correspond bien au numero associe
*/
char *catefromnum(int numcat);

/**
:referent Elliot Curvat
:entree personne: pointeur de structure scsv
:sortie int
:post-cond la valeur a la categorie souhaitee a ete remplacee par l'entree de l'utilisateur
*/
int modifval(scsv *personne);

/**
:referent Elliot Curvat
:entree tabstruct:tableau de structure scsv, indices: tableau d'int, nbligne: int, cat: int
:post-cond tabstruct n'a pas ete modifie, indices contient les indices des elements de tabstruct tries par ordre croissant suivant la categorie cat
*/
void tri_insertion_indirect(scsv tabstruct[], int indices[], int nbligne, int cat);