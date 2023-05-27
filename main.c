#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "wns.h"

#include "definitions.h"

#include "categories.c"
#include "livres.c"



void menu();

int main() {
	title(0,0,"Gestion d'une bibliotheque");
	design();
    lire_categoires();
    lire_livres();
    menu();
    color(COULEUR_BLANC);
    vider_livres();
    vider_categories();
    return 0;
}

void menu(){
	int choix,id,c, r;
	Cat* categorie = NULL;
	Livre* livre = NULL;
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
		printf("%2d. Quitter\n",QUITER);
		printHline(0,18 ,70);		
		if(categorie){
			color(COULEUR_JAUNE);
			printf("\n	Categorie: %s (%d livres)\n",
					categorie->nom,compter_livres_cat(categorie->id));
			printHline(0,20 ,70);
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
				fflush(stdin);
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
				fflush(stdin);
				fgets(str, 20, stdin);
			    // supprimer "\n" de str
				str[strcspn(str, "\n")] = '\0';
				resulta();
				r = chercher_par_autheur(str);
				color(COULEUR_ROUGE);
				printf("\n %d resultat\n",r);
				break;
			case QUITER:
				printf("Au revoir!\n");
				return;
				break;
			default:
				color(COULEUR_ROUGE);
				printf("Choix invalide. Veuillez reeessayer.\n");
				break;
		}
		color(COULEUR_BLANC);
		printf("Appuier sur une touche pour continuer...");
		fflush(stdin);
		getchar();

	} while (1);
}

