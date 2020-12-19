#include <stdio.h>   /* pour les entrées-sorties */
#include <string.h>  /* pour les manipulations de chaînes de caractères */
#include <conio.h>
#include <ctype.h>
#include <stdlib.h>
#include <locale.h>
#include "rep.h"

#define VERSION 3.0
#define SQUELET
/**************************************************************************/
/* Compléter votre nom ici                                                */
/*   Nom :   POINDRON                      Prénom : RAPHAEL               */
/**************************************************************************/

extern bool modif;


/**********************************************************************/
/*  Ajout d'un contact dans le répertoire stocké en mémoire           */
/**********************************************************************/

int ajouter_un_contact_dans_rep(Repertoire *rep, Enregistrement enr)
{
#ifdef IMPL_TAB
	// compléter code ici pour tableau
	int idx;
	

	if (rep->nb_elts < MAX_ENREG)
	{
		rep->tab[rep->nb_elts] = enr;		// ajoute le contact
		rep->nb_elts = rep->nb_elts + 1;	//crée un contact
		modif = true;
		return rep->nb_elts;				// return le nouveau contact
		
	}
	else {
		return(ERROR);
	}

	
#else
#ifdef IMPL_LIST

	bool inserted = false;
	if (rep->nb_elts == 0) {
		if (InsertElementAt(rep->liste, rep->liste->size, enr) != 0) {
			rep->nb_elts += 1;
			modif = true;
			rep->est_trie = true;
			return(OK);
		}

	}
	else {
		int i = 0;
		while (i < rep->nb_elts && est_sup(GetElementAt(rep->liste, i)->pers, enr)) {
			i++;
		}
		if (inserted = InsertElementAt(rep->liste, i, enr)) {
			rep->nb_elts += 1;
			rep->est_trie = true;
			modif = true;
		}
		return inserted;
	}


#endif
	
#endif


	return(OK);

} /* fin ajout */


  /**********************************************************************/
  /* supprime du répertoire l'enregistrement dont l'indice est donné en */
  /*   paramètre       et place modif = true                            */
  /**********************************************************************/



#ifdef IMPL_TAB
void supprimer_un_contact_dans_rep(Repertoire *rep, int indice) {

	// compléter code ici pour tableau
	if (rep->nb_elts >= 1)		/* s'il y a au moins un element ds le tableau */
	{							/* et que l'indice pointe a l'interieur */
		for(int i= indice; i < rep->nb_elts -1 ; i++)
			rep->tab[i] = rep->tab[i + 1];


		rep->nb_elts -= 1;		/* ds ts les cas, il y a un element en moins */
		modif = true;
	}

	return;
} /* fin supprimer */

#else
#ifdef IMPL_LIST
  /************************************************************************/
  /* supprime du répertoire l'enregistrement contenu dans le maillon elem */
  /*                   et fixe modif à vrai                              */
  /************************************************************************/
  // complet

	int supprimer_un_contact_dans_rep_liste(Repertoire *rep, SingleLinkedListElem *elem) {
	
	int ret=DeleteLinkedListElem(rep->liste, elem);
	if (ret == 1) {
		rep->nb_elts--;
		modif = true;
	}

	return (0); 
	}
#endif
#endif



  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement sur une ligne à l'écran  */
  /* ex Dupont, Jean                 0320304050                         */
  /**********************************************************************/
void affichage_enreg(Enregistrement enr)
{
	printf("%s   %s           %s", enr.nom, enr.prenom, enr.tel);


} /* fin affichage_enreg */



  /**********************************************************************/
  /*  fonction d'affichage d'un enregistrement avec alignement des mots */
  /* pour les listes                                                    */
  /* ex | Dupont                |Jean                  |0320304050      */
  /**********************************************************************/
void affichage_enreg_frmt(Enregistrement enr)
{
	printf("|%-30s|%-30s|%-30s\n", enr.nom, enr.prenom, enr.tel);
	// comme fonction affichage_enreg, mais avec présentation alignées des infos
	

} /* fin affichage_enreg */



  /**********************************************************************/
  /* test si dans l'ordre alphabetique, un enregistrement est apres     */
  /* un autre                                                           */
  /**********************************************************************/
bool est_sup(Enregistrement enr1, Enregistrement enr2)
{
	if (_strcmpi(enr1.nom, enr2.nom) == 0 && _strcmpi(enr1.prenom, enr2.prenom) == 0 &&_strcmpi(enr1.tel, enr2.tel) > 0) {     // utilisateur avec le même nom et utilisateur avec le même prénom et numéro pas dans l'ordre
		return(false);
	
	}

	if (_strcmpi(enr1.nom, enr2.nom) == 0 && _strcmpi(enr1.prenom, enr2.prenom) > 0) {	// utilisateur avec le même nom et prénom pas dans l'ordre
			return(false);	
	}

	else if (_strcmpi(enr1.nom, enr2.nom) > 0) {        // si nom pas dans l'ordre
		return(false);
	}

	else {
		return(true);									// si dans l'ordre
	}
	return(true);
}
 


/*********************************************************************/
/*   Tri Alphabetique du tableau d'enregistrements                   */
/*********************************************************************/

void trier(Repertoire *rep)
{

#ifdef IMPL_TAB
	Enregistrement tmps ;
	for (int i = 0 ; i < rep->nb_elts ; i++ ) 
	{
		for (int j = i + 1 ; j < rep->nb_elts ; j++) 
		{
			if (est_sup( rep->tab[i] , rep->tab[j]) == false) 
			{
				tmps = rep->tab[i] ;
				rep->tab[i] = rep->tab[j] ;
				rep->tab[j] = tmps ;
			}
		}
	}
	


	
#else
#ifdef IMPL_LIST
	// ajouter code ici pour Liste
	// rien à faire !
	// la liste est toujours triée
#endif
#endif


	rep->est_trie = true;

} /* fin trier */




  /**********************************************************************/
  /* recherche dans le répertoire d'un enregistrement correspondant au  */
  /*   nom à partir de l'indice ind                                     */
  /*   retourne l'indice de l'enregistrement correspondant au critère ou*/
  /*   un entier négatif si la recherche est négative				    */
  /**********************************************************************/

int rechercher_nom(Repertoire *rep, char nom[], int ind)
{
	int i = ind;		    /* position (indice) de début de recherche dans tableau/liste rep */
	int ind_fin;			/* position (indice) de fin de tableau/liste rep */

	char tmp_nom[MAX_NOM];	/* 2 variables temporaires dans lesquelles */
	char tmp_nom2[MAX_NOM];	/* on place la chaine recherchee et la chaine lue dans le */
							/* tableau, afin de les convertir en majuscules et les comparer */
	bool trouve = false;		

	ind_fin = rep->nb_elts - 1; // indice de fin à ne pas dépasser
	strncpy_s(tmp_nom, _countof(tmp_nom), nom, _TRUNCATE);
	_strupr_s(tmp_nom, strlen(tmp_nom) + 1);



#ifdef IMPL_TAB
	while ((i <= ind_fin) && (!trouve)) 
	{
		strncpy_s(tmp_nom2, _countof(tmp_nom2), rep->tab[i].nom, _TRUNCATE);   //on copie dans tmp_nom2 le nom du répertoire et on le passe en maj
		
		_strupr_s(tmp_nom2, strlen(tmp_nom2) + 1);
		
		if (strcmp(tmp_nom, tmp_nom2) == 0) trouve = true; //comparaison de la chaine 
		
		else i++; 
	}
#else
#ifdef IMPL_LIST
	ind_fin = rep->nb_elts;
	strncpy_s(tmp_nom, _countof(tmp_nom), nom, _TRUNCATE);
	_strupr_s(tmp_nom, strlen(tmp_nom) + 1);
	while (trouve == false && i < ind_fin) {				 

		strncpy_s(tmp_nom2, _countof(tmp_nom2), GetElementAt(rep->liste, i)->pers.nom, _TRUNCATE); 
		_strupr_s(tmp_nom2, strlen(tmp_nom2) + 1);
		if (strcmp(tmp_nom, tmp_nom2) == 0) trouve = true;
		else i++;
	}
	
#endif
#endif

	return((trouve) ? i : -1);
} /* fin rechercher_nom */

  /*********************************************************************/
  /* Supprimer tous les caracteres non numériques de la chaines        */
  /*********************************************************************/
void compact(char *s)
{
	int i = 0;
	int j = 0;
	while (s[i] != '\0') {  // parcours de la chaine
		if (s[i] < 0x30 || s[i] > 0x39) {   //code ascii de 0 à 9 et suppresion des caractères non numérique
			j = i;
			while (s[j + 1] != '\0') {    //on décale tout vers la gauche
				*(s + j) = *(s + j + 1);
				j++;
			}
		}
		else i++;
	}
	return;
}

/**********************************************************************/
/* sauvegarde le répertoire dans le fichier dont le nom est passé en  */
/* argument                                                           */
/* retourne OK si la sauvegarde a fonctionné ou ERROR sinon           */
/**********************************************************************/
int sauvegarder(Repertoire* rep, char nom_fichier[])
{
	FILE* fic_rep;					/* le fichier */
#ifdef IMPL_TAB
	fopen_s(&fic_rep, nom_fichier, "w");  // ouverture fichier
	
	for (int i = 0; i < rep->nb_elts; i++) {
		fputs(rep->tab[i].nom, fic_rep);
		fputs(";", fic_rep);
		fputs(rep->tab[i].prenom, fic_rep);
		fputs(";", fic_rep);
		fputs(rep->tab[i].tel, fic_rep);
		fputs("\n", fic_rep);
	}
	fclose(fic_rep);

	modif = false;
#else
#ifdef IMPL_LIST
	errno_t err = fopen_s(&fic_rep, nom_fichier, "w");
	if (err == 0) {
		for (int i = 0; i < rep->nb_elts; i++) {
			fputs(GetElementAt(rep->liste, i)->pers.nom, fic_rep);
			fputs(";", fic_rep);
			fputs(GetElementAt(rep->liste, i)->pers.prenom, fic_rep);
			fputs(";", fic_rep);
			fputs(GetElementAt(rep->liste, i)->pers.tel, fic_rep);
			fputs("\n", fic_rep);
		}
		fclose(fic_rep);
}
	else return (ERROR);
#endif
#endif

	return(OK);
} /* fin sauvegarder */


  /**********************************************************************/
  /*   charge dans le répertoire le contenu du fichier dont le nom est  */
  /*   passé en argument                                                */
  /*   retourne OK si le chargement a fonctionné et ERROR sinon         */
  /**********************************************************************/

int charger(Repertoire *rep, char nom_fichier[])
{
	FILE *fic_rep;					/* le fichier */
	errno_t err;
	int num_rec = 0;						/* index sur enregistrements */
	int long_max_rec = sizeof(Enregistrement);
	char buffer[sizeof(Enregistrement) + 1];
	int idx = 0;

	char *char_nw_line;
	
	_set_errno(0);
	if ( ((err = fopen_s(&fic_rep, nom_fichier, "r")) != 0) || (fic_rep == NULL) )
	{
		return(err);
	}
	else
	{
		while (!feof(fic_rep) && (rep->nb_elts < MAX_ENREG))
		{
			if (fgets(buffer, long_max_rec, fic_rep) != NULL)
			{
				/* memorisation de l'enregistrement lu dans le tableau */
				buffer[long_max_rec] = 0;			/* en principe il y a deja un fin_de_chaine, cf fgets */

				if ((char_nw_line = strchr(buffer, '\n')) != NULL)
					*char_nw_line = '\0';			/* suppression du fin_de_ligne eventuel */

				idx = 0;								/* analyse depuis le debut de la ligne */
#ifdef IMPL_TAB
				if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							/* on saute le separateur */
					if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, rep->tab[num_rec].tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		/* element à priori correct, on le comptabilise */
					}
				}
#else
#ifdef IMPL_LIST
				Enregistrement nouveau;
				if (lire_champ_suivant(buffer, &idx, nouveau.nom, MAX_NOM, SEPARATEUR) == OK)
				{
					idx++;							
					idx++;							
					if (lire_champ_suivant(buffer, &idx, nouveau.prenom, MAX_NOM, SEPARATEUR) == OK)
					{
						idx++;
						if (lire_champ_suivant(buffer, &idx, nouveau.tel, MAX_TEL, SEPARATEUR) == OK)
							num_rec++;		
					}
				}										
				InsertElementAt(rep->liste, num_rec, nouveau);
#endif
#endif




			}

		}
		rep->nb_elts = num_rec;
		fclose(fic_rep);
		return(OK);
	}


} /* fin charger */