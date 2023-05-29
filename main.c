#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void clear_stdin(){
	int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

#include "wns.h"


#include "definitions.h"

#include "categories.c"
#include "livres.c"
#include "etudiants.c"

void menu();
void menu_etudiant(Etudiant*);

int main() {
	design();
    lire_categories();
    lire_livres();
    lire_etudiants();
    menu();
    vider_etudiants();
    vider_livres();
    vider_categories();
    return 0;
}

void menu(){
	int choix,id,c, r;
	Cat* categorie = NULL;
	Livre* livre = NULL;
	Etudiant* etudiant = NULL;
	char str[20];
	do {
		system("cls");
		color(COULEUR_VERT);
		printf("\n	Bibliotheque menu	\n");
		printHline(0,2 ,70);
		printf("\n\tCategories:%d	Livres:%d	\n",CATEGORIES->nbr,LIVRES->nbr);
		printHline(0,4 ,70);
		color(COULEUR_BLEU);
		printf("\n");
		printf("%2d. Afficher toutes les categories\n",AFFICHER_CATEGORIES);
		printf("%2d. Afficher tous les livres\n",AFFICHER_LIVRES);
		printf("%2d. Afficher les livres de la categorie\n",AFFICHER_LIVRES_CAT);
		printf("%2d. Afficher le livre courant\n",AFFICHER_LIVRE);
		printf("%2d. Ajouter une categorie\n",AJOUTER_CAT);
		printf("%2d. Supprimer une categorie\n",SUPPR_CAT);
		printf("%2d. Selectionner une categorie\n",SELECT_CAT);
		printf("%2d. Selectionner un livre\n",SELECT_LIVRE);
		printf("%2d. Ajouter un livre\n",AJOUTER_LIVRE);
		printf("%2d. Supprimer un livre\n",SUPPR_LIVRE);
		printf("%2d. Rechercher un livre par titre/description\n",CHERCHER_TITRE);
		printf("%2d. Rechercher un livre par autheur\n",CHERCHER_AUTHEUR);
		printf("%2d. Afficher tous les etudiants\n",AFFICHER_ETUDIANTS);
		printf("%2d. Ajouter un etudiant\n",AJOUTER_ETUDIANT);
		printf("%2d. Supprimer un etudiant\n",SUPPR_ETUDIANT);
		printf("%2d. Menu Etudiant\n",MENU_ETUDIANT);
		printf("%2d. Quitter\n",QUITER);
		printHline(0, 22,70);
		if(categorie){
			color(COULEUR_JAUNE);
			printf("\n	Categorie: %s (%d livres)\n",
					categorie->nom,compter_livres_cat(categorie->id));
			printHline(0,24 ,70);
		}
		color(COULEUR_JAUNE);
		printf("\nEntrez votre choix: ");
		if(scanf("%d", &choix) != 1 ){
			scanf("%*[^\n]"); // clear input buffer
			continue;
		}
		int kk;
		switch (choix) {
			case 20:
				for(int i = 0 ; i<1000; i++ ) {
					kk = LIVRES->livres_sorties[i];
					if(kk)printf("%d, ",kk);
				}
				break;
			case AFFICHER_CATEGORIES:
				afficher_categories();
				break;
			case AFFICHER_ETUDIANTS:
				afficher_etudiants();
				break;
			case AJOUTER_CAT:
				ajouter_cat();
				break;
			case SELECT_CAT:
				printf("Donner l'id de la categorie: ");
				scanf("%d",&id);
				categorie = trouver_cat_par_id(id);
				continue;
				break;
			case SUPPR_CAT:
				printf("Donner l'id de la categorie a  supprimer(0 pour annuler): ");
				scanf("%d",&id);
				if(suppr_categorie_de_list(id)) printf("rien a  supprimer\n");
				color(COULEUR_ROUGE);
				printf("supprimer aussi de la base de donnees (0/1)? : ");
				scanf("%d",&c);
				if(c) suppr_cat_fichier(id);
				break;
			case AFFICHER_LIVRES:
				afficher_livres();
				break;
			case AFFICHER_LIVRES_CAT:
				if(categorie) afficher_livres_cat(categorie->id);
				else {
					color(COULEUR_ROUGE);
					printf("Selectionner d'abord une categorie\n");
				}
				break;
			case AJOUTER_LIVRE:
				ajouter_livre();
				break;
			case SELECT_LIVRE:
				printf("Donner l'id du livre: ");
				scanf("%d",&id);
				livre = trouver_livre_par_id(id);
				if(livre) afficher_livre(livre);
				else printf("Livre d'ID %d non trouve\n",id);
				break;
			case AFFICHER_LIVRE:
				if(livre) afficher_livre(livre);
				else {
					color(COULEUR_ROUGE);
					printf("Selectionner d'abord un livre\n");
				}
				break;
			case SUPPR_LIVRE:
				printf("Donner l'id du livre a  supprimer(0 pour annuler): ");
				scanf("%d",&id);
				if(suppr_livre_de_list(id) == 0 ){
					color(COULEUR_ROUGE);
					printf("Supprimer egalement de base de donnees: (0/1)?: ");
					scanf("%d",&c);
					if(c) suppr_livre_fichier(id);
				}else {
					printf("rien a  supprimer\n");
				}
				break;
			case CHERCHER_TITRE:
				color(COULEUR_BLANC);
				printf("Tapper qlq chose: ");
				clear_stdin();
				fgets(str,20,stdin);
			    // supprimer "\n" de str
				str[strcspn(str, "\n")] = '\0';
				resulta();
				r = chercher_par_titre_desc(str);
				color(COULEUR_ROUGE);
				printf("\n %d resultat\n",r);
				break;
			case CHERCHER_AUTHEUR:
				color(COULEUR_BLANC);
				printf("Tapper qlq chose: ");
				clear_stdin();
				fgets(str, 20, stdin);
			    // supprimer "\n" de str
				str[strcspn(str, "\n")] = '\0';
				resulta();
				r = chercher_par_autheur(str);
				color(COULEUR_ROUGE);
				printf("\n %d resultat\n",r);
				break;
			case MENU_ETUDIANT:
				printf("Donner l'id de l'etudiant: ");
				scanf("%d",&id);
				etudiant = trouver_etudiant_par_id(id);
				if(etudiant) menu_etudiant(etudiant);
				else printf("Livre d'ID %d non trouve\n",id);
				etudiant = NULL;
				break;
			case AJOUTER_ETUDIANT:
				ajouter_etudiant();
				break;
			case SUPPR_ETUDIANT:
				printf("Donner l'id de l'etudiant a supprimer(0 pour annuler): ");
				scanf("%d",&id);
				if(suppr_etudiant_de_list(id) == 0 ){
					color(COULEUR_ROUGE);
					printf("Supprimer egalement de base de donnees: (0/1)?: ");
					scanf("%d",&c);
					if(c) suppr_etudiant_fichier(id);
				}else {
					printf("rien a  supprimer\n");
				}
				break;
			case QUITER:
				printf("Au revoir!\n");
				color(COULEUR_BLANC);
				return;
				break;
			default:
				color(COULEUR_ROUGE);
				printf("Choix invalide. Veuillez reeessayer.\n");
				break;
		}
		color(COULEUR_BLANC);
		printf("Appuier sur une touche pour continuer...");
		
		clear_stdin();
		getchar();

	} while (1);
}

void menu_etudiant(Etudiant* e){
	int choix,id,c, r;
	int livre_pris = 0;
	int x,y;
	Livre* livre = NULL;
	Livre* livre_s = NULL;
	Cat* categorie = NULL;
	char str[20];
	do {
		system("cls");
		color(COULEUR_VERT);
		printf("\n	menu  Etudiant	 \n");
		printHline(0,2 ,70);
		if(e){
			printf("\n id: %d	Nom: %s	\n",e->id,e->nom);
			printHline(0,4 ,70);
			printf("\n Mes Livres:\n");
			for(int i = 0; i<5 ; i++) {
				if(e->livres[i] == 0) continue;
				livre = trouver_livre_par_id(e->livres[i]);
				if(livre){
					printf("\t -> %d : %s\n",livre->id,livre->nom);
				}
			}
		}
		if(livre_s){
			color(COULEUR_VERT);
			printf("\n livre selectionne: %d - %s\n",livre_s->id,livre_s->nom);
		}
		getxy(&x,&y);
		printHline(0,y+1 ,70);
		color(COULEUR_BLEU);
		printf("\n");
		printf("%2d. Afficher toutes les categories\n",AFFICHER_CATEGORIES);
		printf("%2d. Afficher tous les livres\n",AFFICHER_LIVRES);
		printf("%2d. Afficher les livres de la categorie\n",AFFICHER_LIVRES_CAT);
		printf("%2d. Afficher le livre courant\n",AFFICHER_LIVRE);
		printf("%2d. Selectionner une categorie\n",SELECT_CAT);
		printf("%2d. Selectionner un livre\n",SELECT_LIVRE);
		printf("%2d. Rechercher un livre par titre/description\n",CHERCHER_TITRE);
		printf("%2d. Rechercher un livre par autheur\n",CHERCHER_AUTHEUR);
		printf("%2d. Prendre livre\n",PRENDRE_LIVRE);
		printf("%2d. Retourner livre\n",RETOURN_LIVRE);
		printf("%2d. Menu Principal\n",QUITER);
		getxy(&x,&y);
		printHline(0,y+1 ,70);
		if(categorie){
			color(COULEUR_JAUNE);
			printf("\n	Categorie: %s (%d livres)\n",
					categorie->nom,compter_livres_cat(categorie->id));
			printHline(0,y+3 ,70);
		}
		color(COULEUR_JAUNE);
		printf("\nEntrez votre choix: ");
		if(scanf("%d", &choix) != 1 ){
			scanf("%*[^\n]"); // clear input buffer
			continue;
		}

		switch (choix) {
			case AFFICHER_CATEGORIES:
				afficher_categories();
				break;
			case SELECT_CAT:
				printf("Donner l'id de la categorie: ");
				scanf("%d",&id);
				categorie = trouver_cat_par_id(id);
				continue;
				break;
			case AFFICHER_LIVRES:
				afficher_livres();
				break;
			case AFFICHER_LIVRES_CAT:
				if(categorie) afficher_livres_cat(categorie->id);
				else {
					color(COULEUR_ROUGE);
					printf("Selectionner d'abord une categorie\n");
				}
				break;
			case SELECT_LIVRE:
				printf("Donner l'id du livre: ");
				scanf("%d",&id);
				livre_s = trouver_livre_par_id(id);
				if(livre_s) afficher_livre(livre_s);
				else printf("Livre d'ID %d non trouve\n",id);
				break;
			case AFFICHER_LIVRE:
				if(livre_s) afficher_livre(livre_s);
				else {
					color(COULEUR_ROUGE);
					printf("Selectionner d'abord un livre\n");
				}
				break;
			case CHERCHER_TITRE:
				color(COULEUR_BLANC);
				printf("Tapper qlq chose: ");
				clear_stdin();
				fgets(str,20,stdin);
			    	// supprimer "\n" de str
				str[strcspn(str, "\n")] = '\0';
				resulta();
				r = chercher_par_titre_desc(str);
				color(COULEUR_ROUGE);
				printf("\n %d resultat\n",r);
				break;
			case CHERCHER_AUTHEUR:
				color(COULEUR_BLANC);
				printf("Tapper qlq chose: ");
				clear_stdin();
				fgets(str, 20, stdin);
			    	// supprimer "\n" de str
				str[strcspn(str, "\n")] = '\0';
				resulta();
				r = chercher_par_autheur(str);
				color(COULEUR_ROUGE);
				printf("\n %d resultat\n",r);
				break;
			case PRENDRE_LIVRE:
				if(livre_s) {
					livre_pris = 0 ;
					for(int i = 0 ; i <1000; i++){
						if(LIVRES->livres_sorties[i] == livre_s->id) {
							color(COULEUR_ROUGE);
							printf("ce livre est deja pris\n");
							livre_pris = 1 ;
							break;
						}
					}
					if(livre_pris != 1 ) {
						prendre_livre(e,livre_s->id);
						for(int i = 0 ; i <1000; i++){
							if(LIVRES->livres_sorties[i] == 0 ) {
								LIVRES->livres_sorties[i] = livre_s->id;
								break;
							}
						}
					}
				}
				else {
					color(COULEUR_ROUGE);
					printf("Selectionner d'abord un livre\n");
				}
				break;
			case RETOURN_LIVRE:
				if(livre_s) {
					retourner_livre(e,livre_s->id);
					for(int i = 0 ; i<1000; i++) {
						if(LIVRES->livres_sorties[i] == livre_s->id) {
							LIVRES->livres_sorties[i] = 0;
							break;
						}
					}
				}
				else {
					color(COULEUR_ROUGE);
					printf("Selectionner d'abord un livre\n");
				}
				break;
			case QUITER:
				return;
				break;
			default:
				color(COULEUR_ROUGE);
				printf("Choix invalide. Veuillez reeessayer.\n");
				break;
		}
		color(COULEUR_BLANC);
		printf("Appuier sur une touche pour continuer...");
		clear_stdin();
		getchar();

	} while (1);
}

