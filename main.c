#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARS 100
#define MAX_NAME_LENGTH 50
#define FILENAME "voitures.txt"
#define HISTORIQUE_FILE "Historique.txt"

struct Voiture {
    double matricule;
    char modele[MAX_NAME_LENGTH];
    char marque[MAX_NAME_LENGTH];
    char etat;
    char remarque[MAX_NAME_LENGTH];
};

void displayMenu() {
    printf("\n E_Cars \n");
    printf("\n Menu:\n");
    printf("1. Louer une Voiture.\n");
    printf("2. Afficher La Description d'une Voiture \n");
    printf("3. Mettre à jour La Description et L'etat d'une Voiture \n");
    printf("4. Supprimer une Voiture \n");
    printf("5. Afficher l'historique des locations \n");
    printf("6. Retour d’une voiture en cas de réclamation. \n");
    printf("7. Quitter\n");
    printf("Choix: ");
}

int main() {
    FILE *file;
    file = fopen(FILENAME, "a+"); // Open the file in append + read mode

    if (file == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return EXIT_FAILURE;
    }

    FILE *file2;
    file2 = fopen(HISTORIQUE_FILE, "a+"); // Open the file in append + read mode

    if (file2 == NULL) {
        perror("Erreur lors de l'ouverture du fichier historique");
        fclose(file);
        return EXIT_FAILURE;
    }

    struct Voiture voitures[MAX_CARS];
    int numOfCars = 0;

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        getchar(); // Consume the remaining newline character

        switch (choice) {
            case 1:
                // Rent a car
                if (numOfCars < MAX_CARS) {
                    printf("Matricule de la voiture: ");
                    scanf("%lf", &voitures[numOfCars].matricule);
                    getchar(); // Consume the remaining newline character

                    printf("Modele de la voiture: ");
                    scanf("%s", voitures[numOfCars].modele);

                    printf("Marque de la voiture: ");
                    scanf("%s", voitures[numOfCars].marque);

                    printf("État de la voiture (L = Louée, D = Disponible, P = Panne): ");
                    scanf(" %c", &voitures[numOfCars].etat);

                    if(voitures[numOfCars].etat=='L'){
                        char dated[11], datef[11];
                        printf("donner la date de debut (jj/mm/aaaa) : ");
                        scanf("%s", dated);
                        printf("donner la date de FIN (jj/mm/aaaa) : ");
                        scanf("%s", datef);
                        fprintf(file2, "%.0lf %s %s \n", voitures[numOfCars].matricule, dated, datef);
                    }

                    printf("Remarque sur la voiture: ");
                    scanf("%s", voitures[numOfCars].remarque);

                    fprintf(file, "%.0lf %s %s %c %s\n", voitures[numOfCars].matricule, voitures[numOfCars].modele,
                            voitures[numOfCars].marque, voitures[numOfCars].etat, voitures[numOfCars].remarque);

                    numOfCars++;
                } else {
                    printf("La liste des voitures est pleine.\n");
                }
                break;
            case 2:
                    // Display all cars
                    printf("\n Liste des voitures :\n");

                    fseek(file, 0, SEEK_SET);
                    while (fscanf(file, "%lf %s %s %c %s", &voitures[numOfCars].matricule, voitures[numOfCars].modele,
                                  voitures[numOfCars].marque, &voitures[numOfCars].etat, voitures[numOfCars].remarque) == 5) {
                        printf("Matricule: %.0lf\tModele: %s\tMarque: %s\tÉtat: %c\tRemarque: %s\n",
                               voitures[numOfCars].matricule, voitures[numOfCars].modele, voitures[numOfCars].marque,
                               voitures[numOfCars].etat, voitures[numOfCars].remarque);
                        numOfCars++;
                    }

                    if (numOfCars == 0) {
                        printf("Aucune voiture n'est enregistrée.\n");
                    }
                    break;

                                break;
            case 3:
                // Update a car
                printf("\n Donner La matricule de Voiture a modifier :\n");
                double id;
                scanf("%lf", &id);
                for (int i = 0; i < numOfCars; i++) {
                    if (voitures[i].matricule == id) {
                        printf("Matricule de la voiture: ");
                        scanf("%lf", &voitures[i].matricule);
                        getchar(); // Consume the remaining newline character

                        printf("Modele de la voiture: ");
                        scanf("%s", voitures[i].modele);

                        printf("Marque de la voiture: ");
                        scanf("%s", voitures[i].marque);
                        printf("État de la voiture (L = Louée, D = Disponible, P = Panne): ");
                        scanf(" %c", &voitures[i].etat);

                        printf("Remarque sur la voiture: ");
                        scanf("%s", voitures[i].remarque);

                        // Overwrite the old entry in the file
                        fseek(file, 0, SEEK_SET);
                        for (int j = 0; j < numOfCars; j++) {
                            fprintf(file, "%.0lf %s %s %c %s\n", voitures[j].matricule, voitures[j].modele,
                                    voitures[j].marque, voitures[j].etat, voitures[j].remarque);
                        }

                        printf("La voiture a été mise à jour avec succès.\n");
                        break;
                    }
                    else{
                        printf("aucune voiture avec ce matricule \N");
                    }
                }
                break;
            case 4:
                // Delete a car
                printf("\n Donner La matricule de Voiture a supprimer :\n");
                double matriculeToDelete;
                scanf("%lf", &matriculeToDelete);

                int found = 0;
                for (int i = 0; i < 1; i++) {
                    if (voitures[i].matricule == matriculeToDelete) {
                        // Delete the car by shifting the following elements
                        for (int j = i; j < numOfCars - 1; j++) {
                            voitures[j] = voitures[j + 1];
                        }
                        numOfCars--;

                        // Overwrite the file with the new list of cars
                        fseek(file, 0, SEEK_SET);
                        for (int j = 0; j < numOfCars; j++) {
                            fprintf(file, "%.0lf %s %s %c %s\n", voitures[j].matricule, voitures[j].modele,
                                    voitures[j].marque, voitures[j].etat, voitures[j].remarque);
                        }
                        printf("La voiture a été supprimée avec succès.\n");
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("Aucune voiture trouvée avec ce matricule.\n");
                }
                break;
               case 5:
                // Display rental history
                printf("\n Historique des locations :\n");
                fseek(file2, 0, SEEK_SET);
                char historyLine[100];
                while (fgets(historyLine, sizeof(historyLine), file2) != NULL) {
                    printf("%s", historyLine);
                }
                break;

            case 6:
    // Return a car due to a complaint
    printf("\n Donner La matricule de Voiture a retourner :\n");
    double matriculeToReturn;
    scanf("%lf", &matriculeToReturn);

    int foundReturn = 0;
    for (int i = 0; i < numOfCars; i++) {
        if (voitures[i].matricule == matriculeToReturn) {
            // Car found, process the return logic here
            printf("La voiture a été trouvée. Entrez la nouvelle état (L = Louée, D = Disponible, P = Panne): ");
            scanf(" %c", &voitures[i].etat);

            // Overwrite the old entry in the file with the updated information
            fseek(file, 0, SEEK_SET);
            for (int j = 0; j < numOfCars; j++) {
                fprintf(file, "%.0lf %s %s %c %s\n", voitures[j].matricule, voitures[j].modele,
                        voitures[j].marque, voitures[j].etat, voitures[j].remarque);
            }

            foundReturn = 1;
            printf("La voiture a été retournée avec succès.\n");
            break;
        }
    }

    if (!foundReturn) {
        printf("Aucune voiture trouvée avec ce matricule.\n");
    }
    break;


            default:
                printf("Choix invalide. Veuillez entrer un nombre entre 1 et 7.\n");
        }
    } while (choice != 7);

    fclose(file);
    fclose(file2);
    return 0;
}
