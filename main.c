#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <locale.h>
#include <conio.h>


#define MAX_USERS 100
#define NAME_LENGTH 30
#define SURNAME_LENGTH 30
#define USERNAME_LENGTH 30
#define PASSWORD_LENGTH 30
#define EMAIL_LENGTH 30
#define PHONE_LENGTH 15
#define MAX_USERNAME_LENGTH 30
#define MAX_RESERVATIONS 100
#define ID_LENGTH 10
#define FILEuser "users.bin"
#define FILEadmin "admin.bin"
#define FILEvoyageInterne "voyageInterne.bin"
#define FILEvoyageExterne "voyageExterne.bin"
#define FILENAME "compagnies.bin"
#define MAX_OFFRES 100 // Ajustez cette valeur selon vos besoins
#define MAX_TITRE 100
#define MAX_DESCRIPTION 500
#define MAX_NOM 50
#define MAX_EMAIL 100
#define MAX_CV 200
#define MAX_LETTRE 200
#define MAX_LENGTH 20
#define MIN_LENGTH 3

#define WHITE 15
#define MAGENTA 5
#define LIGHTRED 12



//styler 
// Définition des couleurs
#define COLOR_RESET 7
#define COLOR_HIGHLIGHT 14  // Jaune
#define COLOR_BORDER 11    // Cyan clair
#define COLOR_TITLE 10     // Vert clair
#define COLOR_LOGO 13      // Magenta clair
#define COLOR_PRIMARY 9     // Bleu clair - couleur principale
#define COLOR_SECONDARY 3   // Cyan - couleur secondaire
#define COLOR_ACCENT 15     // Blanc brillant - pour les éléments sélectionnés
#define COLOR_INACTIVE 8    // Gris - pour les éléments non sélectionnés
#define COLOR_BORDER 9      // Bleu clair - pour les bordures
#define COLOR_TITLE 15      // Blanc brillant - pour les titres
#define COLOR_SEPARATOR 9




// Fonction pour dessiner un champ de saisie
void drawInputField(const char* label, int y, char* buffer, int isPassword) {
    // Label
    setColor(9);
    gotoxy(35, y);
    printf("► %s", label);
    
    // Champ de saisie
    setColor(COLOR_BORDER);
    gotoxy(35, y + 1);
    printf("┌────────────────────────────────────────┐");
    gotoxy(35, y + 2);
    printf("│                                        │");
    gotoxy(35, y + 3);
    printf("└────────────────────────────────────────┘");
    
    // Position du curseur pour la saisie
    gotoxy(37, y + 2);
    setColor(COLOR_ACCENT);
    
    if (isPassword) {
        hide_input(buffer);
    } else {
        scanf("%s", buffer);
    }
    setColor(COLOR_RESET);
}

// Fonction pour vérifier si une chaîne ne contient que des lettres
int isAlphaString(const char* str) {
    for(int i = 0; str[i]; i++) {
        if (!isalpha(str[i]) && str[i] != ' ' && str[i] != '-') {
            return 0;
        }
    }
    return 1;
}

// Fonction pour vérifier le format de l'email
int isValidEmail(const char* email) {
    int atFound = 0;
    int dotFound = 0;
    int atPosition = -1;
    int length = strlen(email);
    
    if(length < 5) return 0; // a@b.c minimum
    
    for(int i = 0; i < length; i++) {
        if(email[i] == '@') {
            if(atFound || i == 0) return 0; // @ déjà trouvé ou au début
            atFound = 1;
            atPosition = i;
        }
        else if(email[i] == '.') {
            if(atPosition != -1 && i > atPosition) dotFound = 1;
        }
    }
    
    return atFound && dotFound;
}

// Fonction pour afficher un message d'erreur
void showError(const char* message, int y) {
    setColor(12);
    gotoxy(80, y);  // Position à droite du champ de saisie
    printf("* %s", message);
    setColor(COLOR_RESET);
}

// Fonction pour effacer un message d'erreur
void clearError(int y) {
    gotoxy(80, y);
    printf("%-50s", ""); // Efface le message
}







//styler 
// Définition des couleurs
#define COLOR_RESET 7
#define COLOR_HIGHLIGHT 14  // Jaune
#define COLOR_BORDER 11    // Cyan clair
#define COLOR_TITLE 10     // Vert clair
#define COLOR_LOGO 13      // Magenta clair
#define COLOR_PRIMARY 9     // Bleu clair - couleur principale
#define COLOR_SECONDARY 3   // Cyan - couleur secondaire
#define COLOR_ACCENT 15     // Blanc brillant - pour les éléments sélectionnés
#define COLOR_INACTIVE 8    // Gris - pour les éléments non sélectionnés
#define COLOR_BORDER 9      // Bleu clair - pour les bordures
#define COLOR_TITLE 15      // Blanc brillant - pour les titres
#define COLOR_SEPARATOR 9

// Structure pour les options du menu
typedef struct {
    char* text;
    void (*action)();
} MenuItem;

// Fonction pour positionner le curseur
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Fonction pour changer la couleur du texte
void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// Fonction pour dessiner le séparateur
void drawSeparator(int startX, int width, int y) {
    setColor(COLOR_SEPARATOR);
    gotoxy(startX, y);
    printf("╠");
    for(int i = 1; i < width - 1; i++) {
        printf("═");
    }
    printf("═╣");
    setColor(COLOR_RESET);
}

// Fonction pour dessiner le logo
void drawLogo() {
    setColor(COLOR_PRIMARY);
    gotoxy(35, 3);
    printf("    █████╗ ███╗   ███╗ █████╗ ███╗   ██╗██╗     ██╗███╗   ██╗███████╗███████╗");
    gotoxy(35, 4);
    printf("   ██╔══██╗████╗ ████║██╔══██╗████╗  ██║██║     ██║████╗  ██║██╔════╝██╔════╝");
    gotoxy(35, 5);
    printf("   ███████║██╔████╔██║███████║██╔██╗ ██║██║     ██║██╔██╗ ██║█████╗  ███████╗");
    gotoxy(35, 6);
    printf("   ██╔══██║██║╚██╔╝██║██╔══██║██║╚██╗██║██║     ██║██║╚██╗██║██╔══╝  ╚════██║");
    gotoxy(35, 7);
    printf("   ██║  ██║██║ ╚═╝ ██║██║  ██║██║ ╚████║███████╗██║██║ ╚████║███████╗███████║");
    gotoxy(35, 8);
    printf("   ╚═╝  ╚═╝╚═╝     ╚═╝╚═╝  ╚═╝╚═╝  ╚═══╝╚══════╝╚═╝╚═╝  ╚═══╝╚══════╝╚══════╝");
    setColor(COLOR_RESET);
}


//draw frame
void drawFrame(int startX, int startY, int width, int height) {
    setColor(COLOR_BORDER);
    
    // Coins
    gotoxy(startX, startY); printf("╔");
    gotoxy(startX + width, startY); printf("╗");
    gotoxy(startX, startY + height); printf("╚");
    gotoxy(startX + width, startY + height); printf("╝");
    
    // Lignes horizontales
    for(int i = 1; i < width; i++) {
        gotoxy(startX + i, startY); printf("═");
        gotoxy(startX + i, startY + height); printf("═");
    }
    
    // Lignes verticales
    for(int i = 1; i < height; i++) {
        gotoxy(startX, startY + i); printf("║");
        gotoxy(startX + width, startY + i); printf("║");
    }
    
    setColor(COLOR_RESET);
}

// Fonction pour afficher une option du menu
void drawMenuItem(const char* text, int x, int y, int isSelected) {
    gotoxy(x, y);
    if(isSelected) {
        setColor(COLOR_ACCENT);
        printf("  ►  %s", text);
    } else {
        setColor(COLOR_INACTIVE);
        printf("   %s", text);
    }
    setColor(COLOR_RESET);
}


//****************************** */
// Flight information structures
typedef struct {
    int jour;
    int mois;
    int annee;
} Date;
typedef struct {

    int mois;
    int annee;
} Date2;

typedef struct {
    int heure;
    int minute;
} Heure;

// Structure for internal flights (unchanged)
typedef struct {
    char id[ID_LENGTH + 1];  // Unique ID for each voyage
    char aeroport_depart[30];
    char aeroport_arrive[30];
    Date date_voyage;
    Heure heure_depart;
    Heure heure_arrivee;
    int nb_place;
    char compagnie[30];
    int prix;
    Heure duree_vol;
} VoyageInterne;

// Structure for external flights (new)
typedef struct {
    char id[ID_LENGTH + 1];  // Unique ID for each voyage
    char aeroport_depart[30];
    char aeroport_arrive[30];
    char pays_depart[30];
    char pays_arrivee[30];
    Date date_voyage;
    Heure heure_depart;
    Heure heure_arrivee;
    int nb_place;
    char compagnie[30];
    int prix;
    char classe[20];
    Heure duree_vol;
} VoyageExterne;

// Structure to store user information
typedef struct {
    char nom[NAME_LENGTH];
    char prenom[SURNAME_LENGTH];
    char email[EMAIL_LENGTH];
    char telephone[PHONE_LENGTH];
    char username[USERNAME_LENGTH];
    char password[PASSWORD_LENGTH];
} User;

typedef struct {
    char numero_carte[20];
    char titulaire_carte[50];
    Date2 date_expiration;
    char code_securite[5];
} InformationsPaiement;

typedef struct {
    char username[50];
    char voyage_id[30];
    int nb_places_reservees;
    Date date_reservation;
    float montant_paye;
} Reservation;

typedef struct {
    char nom[30];  // Nom de la compagnie
    char pays[30]; // Pays d'origine de la compagnie
    int annee_creation; // Année de création de la compagnie
    int nb_avions;  // Nombre d'avions dans la flotte
} Compagnie;
typedef struct {
    char id_contrat[20];  // Identifiant du contrat
    char date_debut[15];  // Date de début du contrat (format: dd/mm/yyyy)
    char date_fin[15];    // Date de fin du contrat (format: dd/mm/yyyy)
    float montant;        // Montant du contrat
} Contrat;

typedef struct {
    char nom[50];
    char prenom[50];
    char identifiant[30];  // Identifiant unique de l'employé
    char mot_de_passe[30];  // Mot de passe de l'employé
    char poste[50];  // Poste de l'employé dans l'agence
    char ville[50];  // Ville où travaille l'employé
    char email[100]; // Email de l'employé
    char telephone[20]; // Numéro de téléphone de l'employé
} Employe;
// structure pour les offres existants
typedef struct {
    char id[20]; // Identifiant unique de l'offre
    char titre[MAX_TITRE];
    char description[MAX_DESCRIPTION];
    char entreprise[MAX_TITRE];
    char localisation[MAX_TITRE];
    char type_contrat[20];
    int salaire;
      
} OffreEmploi;

// structure pour les condidatures
typedef struct {
    char offre_id[20];
    char nom[50];
    char prenom[50];
    char email[100];
    char telephone[20];
    char niveau_etude[50];    // Licence, Master, Doctorat, etc.
    char specialite[100];     // Domaine d'étude
    char experience[500];     // Description de l'expérience professionnelle
    char competences[500];    // Liste des compétences
    char langues[200];        // Langues maîtrisées
    char date_candidature[20];
    char statut[20];         // "En attente", "Acceptée", "Refusée"
    char cv_path[200];       // Chemin vers le fichier CV
} Candidature;











//recuperer la date
// Fonction pour obtenir la date du jour
void obtenir_date_du_jour(Date *date) {
    time_t maintenant = time(NULL); // Obtenir le timestamp actuel
    struct tm *temps_local = localtime(&maintenant); // Convertir en temps local

    // Remplir la structure Date
    date->jour = temps_local->tm_mday;
    date->mois = temps_local->tm_mon + 1; // Les mois vont de 0 (janvier) à 11 (décembre)
    date->annee = temps_local->tm_year + 1900; // Année depuis 1900, donc on ajoute 1900
}



//partie utilisateur
void hide_input(char* input) {
    char ch;
    int i = 0;
    while (1) {
        ch = _getch();  // Lire un caractère sans l'afficher
        if (ch == 13) {  // Touche Enter
            break;
        } else if (ch == 8) {  // Touche Backspace
            if (i > 0) {
                i--;
                printf("\b \b");  // Effacer l'astérisque précédent
            }
        } else {
            input[i] = ch;
            i++;
            printf("*");  // Afficher un astérisque
        }
    }
    input[i] = '\0';  // Terminer la chaîne de caractères
}

// Signup function
char* signUp() {
    static char username[USERNAME_LENGTH];
    char confirmermotdepasse[30];
    User newUser;
    FILE *file = fopen(FILEuser, "ab+");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    // Configuration initiale
    system("cls");
    
    // Dessiner le cadre principal
    drawFrame(20, 1, 100, 30);
    
    // Dessiner le logo
    drawLogo();
    
    // Dessiner le séparateur
    drawSeparator(20, 100, 10);

    // Titre
    setColor(9);
    gotoxy(20,13);
    printf("╠══════════════════════════════════════════ INSCRIPTION ════════════════════════════════════════════╣");

    // Saisie et validation du nom
    do {
        clearError(14);
        drawInputField("Nom", 14, newUser.nom, 0);
        if(strlen(newUser.nom) > MAX_LENGTH) {
            showError("Le nom ne doit pas dépasser 20 caractères", 17);
            continue;
        }
        if(!isAlphaString(newUser.nom)) {
            showError("Le nom ne doit contenir que des lettres", 17);
            continue;
        }
        break;
    } while(1);
    clearError(17);

    // Saisie et validation du prénom
    do {
        clearError(18);
        drawInputField("Prénom", 18, newUser.prenom, 0);
        if(strlen(newUser.prenom) > MAX_LENGTH) {
            showError("Le prénom ne doit pas dépasser 20 caractères", 21);
            continue;
        }
        if(!isAlphaString(newUser.prenom)) {
            showError("Le prénom ne doit contenir que des lettres", 21);
            continue;
        }
        break;
    } while(1);
    clearError(21);

    // Saisie et validation de l'email
    do {
        clearError(22);
        drawInputField("Email", 22, newUser.email, 0);
        if(strlen(newUser.email) > MAX_LENGTH * 2) {
            showError("L'email est trop long       ", 25);
            continue;
        }
        if(!isValidEmail(newUser.email)) {
            showError("Format d'email invalide    ", 25);
            continue;
        }
        break;
    } while(1);
    clearError(25);

    // Saisie et validation du nom d'utilisateur
    do {
        clearError(26);
        drawInputField("username ", 26, newUser.username, 0);
        if(strlen(newUser.username) > MAX_LENGTH) {
            showError("Le nom d'utilisateur ne doit pas dépasser 20 caractères", 29);
            continue;
        }
        if(strlen(newUser.username) < MIN_LENGTH) {
            showError("Le nom d'utilisateur doit avoir au moins 3 caractères", 29);
            continue;
        }
        
        // Vérifier si le nom d'utilisateur existe déjà
        User tempUser;
        rewind(file);
        int exists = 0;
        while (fread(&tempUser, sizeof(User), 1, file)) {
            if (strcmp(tempUser.username, newUser.username) == 0) {
                showError("Ce nom d'utilisateur est déjà pris", 29);
                exists = 1;
                break;
            }
        }
        if (exists) continue;
        break;
    } while(1);
    clearError(29);

    // Configuration initiale pour la page du mot de passe
    system("cls");
    drawFrame(20, 1, 100, 30);
    drawLogo();
     drawSeparator(20, 100, 10);

    // Titre
    setColor(9);
    gotoxy(20,12);
    printf("╠══════════════════════════════════════════ INSCRIPTION ════════════════════════════════════════════╣");

    // Saisie et validation du mot de passe
    do {
        clearError(16);
        
        drawInputField("pasworld ", 16, newUser.password, 1);
        if(strlen(newUser.password) > MAX_LENGTH) {
            showError("Le mot de passe ne doit pas dépasser 20 caractères", 19);
            continue;
        }
        if(strlen(newUser.password) < MIN_LENGTH) {
            showError("Le mot de passe doit avoir au moins 3 caractères", 19);
            continue;
        }
        clearError(19);
        
        clearError(20);
        drawInputField("Confirmation passworld", 20, confirmermotdepasse, 1);
        if(strcmp(newUser.password, confirmermotdepasse) != 0) {
            showError("Les mots de passe ne correspondent pas", 23);
            continue;
        }
        break;
    } while(1);
    clearError(23);
    clearError(19);
    

    // Écrire les informations dans le fichier
    fwrite(&newUser, sizeof(User), 1, file);
    fclose(file);

    strcpy(username, newUser.username);
    
    // Message de succès

    setColor(10);
    gotoxy(45, 26);
    printf("Inscription réussie ! Bienvenue %s %s", newUser.nom, newUser.prenom);
    Sleep(3000);
    system("cls");

    return username;
}


char* login() {
    static char username[USERNAME_LENGTH];
    User user;
    FILE *file = fopen(FILEuser, "rb");

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return NULL;
    }

    // Configuration initiale
    system("cls");
    
    // Dessiner le cadre principal
    drawFrame(20, 1, 100, 30);
    
    // Dessiner le logo
    drawLogo();
    
    // Dessiner le séparateur
    drawSeparator(20, 100, 10);

    // Titre
    setColor(9);
    gotoxy(20, 13);
    printf("╠═════════════════════════════════════════ CONNEXION ═══════════════════════════════════════════════╣");

    // Saisie du nom d'utilisateur
    drawInputField("username", 16, user.username, 0);
    
    // Saisie du mot de passe
    drawInputField("password", 20, user.password, 1);

    User tempUser;
    int loginSuccess = 0;
    while (fread(&tempUser, sizeof(User), 1, file)) {
        if (strcmp(tempUser.username, user.username) == 0 && strcmp(tempUser.password, user.password) == 0) {
            strcpy(username, tempUser.username);
            setColor(10);
            gotoxy(45, 24);
            printf("Connexion réussie ! Bienvenue, %s %s", tempUser.nom, tempUser.prenom);
            loginSuccess = 1;
            break;
        }
    }

    if (!loginSuccess) {
        setColor(12);
        gotoxy(45, 24);
        printf("Nom d'utilisateur ou mot de passe incorrect");
        Sleep(2000);
    } else {
        Sleep(2000);
    }

    fclose(file);
    system("cls");
    return loginSuccess ? username : NULL;
}




void drawBox(int startX, int startY, int endX, int endY) {
    // Coins
    gotoxy(startX, startY);
    printf("╔");
    gotoxy(endX, startY);
    printf("╗");
    gotoxy(startX, endY);
    printf("╚");
    gotoxy(endX, endY);
    printf("╝");

    // Lignes horizontales
    for (int i = startX + 1; i < endX; i++) {
        gotoxy(i, startY);
        printf("═");
        gotoxy(i, endY);
        printf("═");
    }

    // Lignes verticales
    for (int i = startY + 1; i < endY; i++) {
        gotoxy(startX, i);
        printf("║");
        gotoxy(endX, i);
        printf("║");
    }
}


void afficherOffres() {
    FILE *file = fopen("offres.bin", "rb");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier des offres.\n");
        return;
    }

    OffreEmploi offre;
    int count = 0;
    int currentPage = 0;
    int itemsPerPage = 3;
    
    fseek(file, 0, SEEK_END);
    int totalOffres = ftell(file) / sizeof(OffreEmploi);
    int totalPages = (totalOffres + itemsPerPage - 1) / itemsPerPage;
    rewind(file);

    while(1) {
        system("cls");
        drawFrame(20, 1, 100, 31);
        drawLogo();
        drawSeparator(20, 100, 10);

        setColor(9);
        gotoxy(20, 12);
        printf("╠═════════════════════════════════ LISTE DES OFFRES D'EMPLOI ═══════════════════════════════════╣");

        fseek(file, currentPage * itemsPerPage * sizeof(OffreEmploi), SEEK_SET);
        count = 0;

        while (count < itemsPerPage && fread(&offre, sizeof(OffreEmploi), 1, file)) {
            // ID et Titre
            gotoxy(30, 14 + (count * 4));
            setColor(11); // Cyan clair pour "ID"
            printf("► ID: ");
            setColor(15); // Blanc pour la valeur
            printf("%s - ", offre.id);
            setColor(13); // Magenta clair pour le titre
            printf("%s", offre.titre);

            // Description
            gotoxy(30, 15 + (count * 4));
            setColor(14); // Jaune pour "Description"
            printf("  Description: ");
            setColor(7); // Gris clair pour le texte
            printf("%s", offre.description);

            // Localisation, Type et Salaire
            gotoxy(30, 16 + (count * 4));
            setColor(10); // Vert clair pour "Localisation"
            printf("  Localisation: ");
            setColor(15); // Blanc pour la valeur
            printf("%s - ", offre.localisation);
            
            setColor(12); // Rouge clair pour "Type"
            printf("Type: ");
            setColor(15); // Blanc pour la valeur
            printf("%s - ", offre.type_contrat);
            
            setColor(11); // Cyan clair pour "Salaire"
            printf("Salaire: ");
            setColor(15); // Blanc pour la valeur
            printf("%d DH", offre.salaire);

            // Ligne de séparation
            gotoxy(30, 17 + (count * 4));
            setColor(8); // Gris foncé pour la ligne
            printf("------------------------------------------------------------------------------------");
            count++;
        }

        // Navigation
        setColor(13); // Magenta clair pour la navigation
        gotoxy(30, 30);
        printf("◄ Page précédente");
        gotoxy(75, 30);
        printf("Page suivante ►");
        
        setColor(11); // Cyan clair pour le numéro de page
        gotoxy(55, 30);
        printf("Page %d/%d", currentPage + 1, totalPages);
        
        // Navigation
        char key = _getch();
        if (key == 27) { // Échap
            break;
        }
        else if (key == 75 && currentPage > 0) { // Gauche
            currentPage--;
        }
        else if (key == 77 && currentPage < totalPages - 1) { // Droite
            currentPage++;
        }
    }

    fclose(file);
}


int ajouterCandidature(const Candidature *candidature) {
    if (candidature == NULL) {
        return 0;
    }

    FILE *fp_candidatures = fopen("candidatures.bin", "ab");
    if (fp_candidatures == NULL) {
        return 0;
    }

    int success = (fwrite(candidature, sizeof(Candidature), 1, fp_candidatures) == 1);
    fclose(fp_candidatures);
    return success;
}





void rechercherEmploi(char* username) {
    // Afficher d'abord les offres disponibles
    afficherOffres();
    
    // Demander à l'utilisateur s'il veut postuler
    int currentChoice = 0;
    char choix;
    const char* options[] = {"Oui", "Non"};
    
    do {
        system("cls");
        drawFrame(20, 1, 100, 30);
        drawLogo();
        drawSeparator(20, 100, 10);

        setColor(9);
        gotoxy(20, 12);
        printf("╠═════════════════════════════════════════ POSTULER À UNE OFFRE ════════════════════════════════════════╣");
        
        // Afficher la question en plus grand et centré
        setColor(13);
        gotoxy(45, 15);
        printf("╔══════════════════════════════════════════════════╗");
        gotoxy(45, 16);
        printf("║                                                  ║");
        gotoxy(45, 17);
        printf("║          Voulez-vous postuler à une offre ?      ║");
        gotoxy(45, 18);
        printf("║                                                  ║");
        gotoxy(45, 19);
        printf("╚══════════════════════════════════════════════════╝");

        // Afficher les options centrées
        for(int i = 0; i < 2; i++) {
            gotoxy(55 + i*20, 21);
            if(i == currentChoice) {
                setColor(11);
                printf("►  %s  ◄", options[i]);
            } else {
                setColor(15);
                printf("   %s   ", options[i]);
            }
        }

        // Navigation
        choix = _getch();
        if(choix == 75 && currentChoice > 0) { // Flèche gauche
            currentChoice--;
        }
        else if(choix == 77 && currentChoice < 1) { // Flèche droite
            currentChoice++;
        }
        else if(choix == 13) { // Entrée
            if(currentChoice == 1) { // Non
                return;
            }
            break; // Oui
        }
    } while(1);

    int pageFormulaire = 0;
    Candidature candidature;
    
    // Initialiser les champs
    memset(&candidature, 0, sizeof(Candidature));

    do {
        system("cls");
        drawFrame(20, 1, 100, 30);
        drawLogo();
        drawSeparator(20, 100, 10);

        setColor(9);
        gotoxy(20, 12);
        if (pageFormulaire == 0) {
            printf("╠═══════════════════════════════════ INFORMATIONS PERSONNELLES ═══════════════════════════════╣");
            
            setColor(15);
            // Afficher les labels
            gotoxy(25, 15);
            printf("👤 Nom:");
            gotoxy(37, 15);
            printf("%-40s", candidature.nom);

            gotoxy(25, 18);
            printf("👤 Prénom:");
            gotoxy(37, 18);
            printf("%-40s", candidature.prenom);

            gotoxy(25, 21);
            printf("📧 Email:");
            gotoxy(37, 21);
            printf("%-40s", candidature.email);

            gotoxy(25, 24);
            printf("📞 Téléphone:");
            gotoxy(37, 24);
            printf("%-40s", candidature.telephone);

            // Afficher les messages d'erreur en rouge
            setColor(12);
            if(strlen(candidature.nom) > 0 && (strlen(candidature.nom) < 2 || !isAlphaString(candidature.nom))) {
                gotoxy(37, 16);
                printf("❌ Le nom doit contenir au moins 2 caractères alphabétiques");
            }
            if(strlen(candidature.prenom) > 0 && (strlen(candidature.prenom) < 2 || !isAlphaString(candidature.prenom))) {
                gotoxy(37, 19);
                printf("❌ Le prénom doit contenir au moins 2 caractères alphabétiques");
            }
            if(strlen(candidature.email) > 0 && !isValidEmail(candidature.email)) {
                gotoxy(37, 22);
                printf("❌ Format d'email invalide");
            }
            if(strlen(candidature.telephone) > 0 && strlen(candidature.telephone) < 8) {
                gotoxy(37, 25);
                printf("❌ Numéro de téléphone invalide");
            }

        } else {
            printf("╠═══════════════════════════════════ FORMATION ET EXPÉRIENCE ════════════════════════════════╣");
            
            setColor(15);
            gotoxy(25, 15);
            printf("🎓 Niveau d'études:");
            gotoxy(45, 15);
            printf("%-50s", candidature.niveau_etude);

            gotoxy(25, 18);
            printf("📚 Spécialité:");
            gotoxy(45, 18);
            printf("%-50s", candidature.specialite);

            gotoxy(25, 21);
            printf("💼 Expérience:");
            gotoxy(45, 21);
            printf("%-50s", candidature.experience);

            gotoxy(25, 24);
            printf("🔧 Compétences:");
            gotoxy(45, 24);
            printf("%-50s", candidature.competences);
        }

        // Barre de navigation
        setColor(13);
        gotoxy(20, 27);
        printf("╠════════════════════════════════════════════════════════════════════════════════════════╣");
        gotoxy(25, 28);
        if (pageFormulaire == 0) {
            printf("← (ESC) Retour | (→) Page Suivante | (TAB) Champ suivant | (ENTRÉE) Modifier");
        } else {
            printf("(←) Page Précédente | (ENTRÉE) Soumettre | (ESC) Retour | (TAB) Champ suivant");
        }

        choix = _getch();
        if (choix == 27) { // ESC
            return;
        } else if (choix == 77 && pageFormulaire == 0) { // Flèche droite
            if(strlen(candidature.nom) >= 2 && isAlphaString(candidature.nom) &&
               strlen(candidature.prenom) >= 2 && isAlphaString(candidature.prenom) &&
               isValidEmail(candidature.email) && strlen(candidature.telephone) >= 8) {
                pageFormulaire = 1;
            }
        } else if (choix == 75 && pageFormulaire == 1) { // Flèche gauche
            pageFormulaire = 0;
        } else if (choix == 13) { // Entrée
            char buffer[500];
            if (pageFormulaire == 0) {
                // Mode édition pour la première page
                gotoxy(37, 15);
                printf("%-40s", "");
                gotoxy(37, 15);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                if(strlen(buffer) > 0) strcpy(candidature.nom, buffer);

                gotoxy(37, 18);
                printf("%-40s", "");
                gotoxy(37, 18);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                if(strlen(buffer) > 0) strcpy(candidature.prenom, buffer);

                gotoxy(37, 21);
                printf("%-40s", "");
                gotoxy(37, 21);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                if(strlen(buffer) > 0) strcpy(candidature.email, buffer);

                gotoxy(37, 24);
                printf("%-40s", "");
                gotoxy(37, 24);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                if(strlen(buffer) > 0) strcpy(candidature.telephone, buffer);
            } else {
                // Mode édition pour la deuxième page
                gotoxy(45, 15);
                printf("%-50s", "");
                gotoxy(45, 15);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                if(strlen(buffer) > 0) strcpy(candidature.niveau_etude, buffer);

                gotoxy(45, 18);
                printf("%-50s", "");
                gotoxy(45, 18);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                if(strlen(buffer) > 0) strcpy(candidature.specialite, buffer);

                gotoxy(45, 21);
                printf("%-50s", "");
                gotoxy(45, 21);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                if(strlen(buffer) > 0) strcpy(candidature.experience, buffer);

                gotoxy(45, 24);
                printf("%-50s", "");
                gotoxy(45, 24);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = 0;
                if(strlen(buffer) > 0) strcpy(candidature.competences, buffer);

                // Vérification et soumission du formulaire
                if(strlen(candidature.niveau_etude) >= 2 && strlen(candidature.specialite) >= 2 && 
                   strlen(candidature.experience) >= 2 && strlen(candidature.competences) >= 2) {
                    
                    // Préparation de la candidature
                    time_t now = time(NULL);
                    struct tm *tm = localtime(&now);
                    strftime(candidature.date_candidature, sizeof(candidature.date_candidature), "%Y-%m-%d", tm);
                    strcpy(candidature.statut, "En attente");
                    
                    // Tentative d'ajout de la candidature
                    if (ajouterCandidature(&candidature)) {
                        // Écran de confirmation
                        system("cls");
                        drawFrame(20, 1, 100, 30);
                        drawLogo();
                        drawSeparator(20, 100, 10);

                        setColor(9);
                        gotoxy(20, 12);
                        printf("╠═══════════════════════════════════ CONFIRMATION ═══════════════════════════════════════╣");
                        
                        setColor(10);
                        gotoxy(35, 15);
                        printf("✅ Votre candidature a été enregistrée avec succès!");
                        
                        setColor(15);
                        gotoxy(35, 17);
                        printf("📋 Détails de la candidature:");
                        
                        gotoxy(35, 19);
                        printf("👤 Nom: %s %s", candidature.nom, candidature.prenom);
                        
                        gotoxy(35, 20);
                        printf("📧 Email: %s", candidature.email);
                        
                        gotoxy(35, 21);
                        printf("📞 Téléphone: %s", candidature.telephone);
                        
                        gotoxy(35, 22);
                        printf("🎓 Formation: %s en %s", candidature.niveau_etude, candidature.specialite);
                        
                        gotoxy(35, 23);
                        printf("📅 Date: %s", candidature.date_candidature);
                        
                        gotoxy(35, 24);
                        printf("📌 Statut: %s", candidature.statut);

                        setColor(13);
                        gotoxy(30, 26);
                        printf("Votre candidature a été enregistrée et sera examinée prochainement.");
                        
                        setColor(15);
                        gotoxy(35, 28);
                        printf("Appuyez sur une touche pour continuer...");
                        _getch();
                        return;
                    } else {
                        setColor(12);
                        gotoxy(35, 26);
                        printf("❌ Erreur lors de l'enregistrement de la candidature");
                        gotoxy(35, 27);
                        printf("Veuillez réessayer plus tard.");
                        Sleep(2000);
                        return;
                    }
                } else {
                    setColor(12);
                    gotoxy(35, 26);
                    printf("❌ Veuillez remplir tous les champs correctement");
                    Sleep(2000);
                }
            }
        }
    } while(1);
}



void afficherBillet(const VoyageInterne *voyage, const Reservation *reservation) {
    int page_courante = 1;
    const int TOTAL_PAGES = 2;
    char touche;

    do {
        // Configuration initiale
        system("cls");
        drawFrame(20, 1, 100, 30);
        drawLogo();
        drawSeparator(20, 100, 10);
        
        setColor(9);
        gotoxy(20, 12);
        printf("╠═══════════════════════════════════════ BILLET ELECTRONIQUE ═══════════════════════════════════════╣");

        if (page_courante == 1) {
            // Page 1 : Informations de réservation
            setColor(11);
            gotoxy(30, 14);
            printf("╔═══════════════════ INFORMATIONS DE RESERVATION ═══════════════════╗");
            
            setColor(15);
            gotoxy(32, 16);
            printf("Numéro de réservation  : %s", reservation->voyage_id);
            gotoxy(32, 17);
            printf("Nom du passager        : %s", reservation->username);
            gotoxy(32, 18);
            printf("Nombre de places       : %d", reservation->nb_places_reservees);
            gotoxy(32, 19);
            printf("Montant payé           : %.2f MAD", reservation->montant_paye);
            
            setColor(11);
            gotoxy(30, 21);
            printf("╚════════════════════════════════════════════════════════════════╝");
        }
        else if (page_courante == 2) {
            // Page 2 : Détails du vol
            setColor(11);
            gotoxy(30, 14);
            printf("╔════════════════════════ DETAILS DU VOL ════════════════════════╗");
            
            setColor(15);
            gotoxy(32, 16);
            printf("Compagnie aérienne     : %s", voyage->compagnie);
            gotoxy(32, 17);
            printf("Aéroport de départ     : %s", voyage->aeroport_depart);
            gotoxy(32, 18);
            printf("Aéroport d'arrivée     : %s", voyage->aeroport_arrive);
            gotoxy(32, 19);
            printf("Date du départ         : %02d/%02d/%d", 
                   voyage->date_voyage.jour, voyage->date_voyage.mois, voyage->date_voyage.annee);
            gotoxy(32, 20);
            printf("Heure de départ        : %02d:%02d", 
                   voyage->heure_depart.heure, voyage->heure_depart.minute);
            gotoxy(32, 21);
            printf("Heure d'arrivée        : %02d:%02d", 
                   voyage->heure_arrivee.heure, voyage->heure_arrivee.minute);
            gotoxy(32, 22);
            printf("Durée du vol           : %02dh%02dm", 
                   voyage->duree_vol.heure, voyage->duree_vol.minute);
            
            setColor(11);
            gotoxy(30, 24);
            printf("╚════════════════════════════════════════════════════════════════╝");
        }

        // Barre de navigation
        setColor(13);
        gotoxy(20, 26);
        printf("╠═══════════════════════════════════════════ NAVIGATION ════════════════════════════════════════════╣");
        
        setColor(15);
        gotoxy(30, 27);
        printf("◄  Page précédente  ←  |  Page %d/%d  |  Page suivante  →  ►", page_courante, TOTAL_PAGES);
        gotoxy(40, 28);
        printf("Appuyez sur [Entrée] pour quitter");

        // Gestion de la navigation
        touche = _getch();
        if (touche == 75 && page_courante > 1) { // Flèche gauche
            page_courante--;
        }
        else if (touche == 77 && page_courante < TOTAL_PAGES) { // Flèche droite
            page_courante++;
        }
        else if (touche == 13) { // Entrée
            break;
        }
    } while (1);
}




void afficherBilletApresPaiement(const char *username) {
    // Configuration initiale
    system("cls");
    drawFrame(20, 1, 100, 30);
    drawLogo();
    drawSeparator(20, 100, 10);
    
    setColor(9);
    gotoxy(20, 12);
    printf("╠═══════════════════════════════════ BILLET DE RESERVATION ════════════════════════════════════╣");

    // Ouvrir le fichier des réservations
    FILE *fp_reservations = fopen("reservationsInterne.bin", "rb");
    if (fp_reservations == NULL) {
        setColor(12);
        gotoxy(35, 15);
        printf("Erreur lors de l'ouverture du fichier des réservations");
        gotoxy(35, 16);
        printf("Appuyez sur une touche pour continuer...");
        _getch();
        return;
    }

    // Ouvrir le fichier des voyages
    FILE *fp_voyages = fopen("voyageInterne.bin", "rb");
    if (fp_voyages == NULL) {
        setColor(12);
        gotoxy(35, 15);
        printf("Erreur lors de l'ouverture du fichier des voyages");
        gotoxy(35, 16);
        printf("Appuyez sur une touche pour continuer...");
        _getch();
        fclose(fp_reservations);
        return;
    }

    Reservation reservation;
    VoyageInterne voyage;
    Reservation derniereReservation;
    VoyageInterne dernierVoyage;
    int reservationTrouvee = 0;

    // Animation de recherche
    setColor(15);
    gotoxy(35, 15);
    printf("Recherche de votre réservation");
    for(int i = 0; i < 3; i++) {
        printf(".");
        Sleep(300);
    }

    // Se positionner à la fin du fichier pour lire la dernière réservation
    fseek(fp_reservations, -sizeof(Reservation), SEEK_END);
    
    if (fread(&reservation, sizeof(Reservation), 1, fp_reservations) == 1) {
        if (strcmp(reservation.username, username) == 0) {
            // Chercher le voyage correspondant
            rewind(fp_voyages);
            while (fread(&voyage, sizeof(VoyageInterne), 1, fp_voyages) == 1) {
                if (strcmp(reservation.voyage_id, voyage.id) == 0) {
                    derniereReservation = reservation;
                    dernierVoyage = voyage;
                    reservationTrouvee = 1;
                    break;
                }
            }
        }
    }

    system("cls");
    drawFrame(20, 1, 100, 30);
    drawLogo();
    drawSeparator(20, 100, 10);
    
    setColor(9);
    gotoxy(20, 12);
    printf("╠═══════════════════════════════════ BILLET DE RESERVATION ════════════════════════════════════╣");

    if (reservationTrouvee) {
        setColor(10); // Vert pour le succès
        gotoxy(35, 14);
        printf("Réservation trouvée pour : %s", username);
        gotoxy(35, 15);
        printf("ID du voyage : %s", derniereReservation.voyage_id);
        
        afficherBillet(&dernierVoyage, &derniereReservation);
    } else {
        setColor(12); // Rouge pour l'erreur
        gotoxy(35, 15);
        printf("Aucune réservation trouvée pour l'utilisateur %s", username);
        gotoxy(35, 17);
        system("cls");
        printf("Appuyez sur une touche pour continuer...");
        _getch();
    }

    fclose(fp_reservations);
    fclose(fp_voyages);
}



void afficherBilletE(const VoyageExterne *voyage, const Reservation *reservation) {
    int page_courante = 1;
    const int TOTAL_PAGES = 2;
    char touche;

    do {
        // Configuration initiale
        system("cls");
        drawFrame(20, 1, 100, 30);
        drawLogo();
        drawSeparator(20, 100, 10);
        
        setColor(9);
        gotoxy(20, 12);
        printf("╠═══════════════════════════════ BILLET ELECTRONIQUE INTERNATIONAL ══════════════════════════════╣");

        if (page_courante == 1) {
            // Page 1 : Informations de réservation
            setColor(11);
            gotoxy(30, 14);
            printf("╔═══════════════════ INFORMATIONS DE RESERVATION ═══════════════════╗");
            
            setColor(15);
            gotoxy(32, 16);
            printf("Numéro de réservation  : %s", reservation->voyage_id);
            gotoxy(32, 17);
            printf("Nom du passager        : %s", reservation->username);
            gotoxy(32, 18);
            printf("Nombre de places       : %d", reservation->nb_places_reservees);
            gotoxy(32, 19);
            printf("Montant payé           : %.2f MAD", reservation->montant_paye);
            
            setColor(11);
            gotoxy(30, 21);
            printf("╚════════════════════════════════════════════════════════════════╝");
        }
        else if (page_courante == 2) {
            // Page 2 : Détails du vol international
            setColor(11);
            gotoxy(30, 14);
            printf("╔════════════════════ DETAILS DU VOL INTERNATIONAL ═══════════════╗");
            
            setColor(15);
            gotoxy(32, 16);
            printf("Compagnie aérienne     : %s", voyage->compagnie);
            gotoxy(32, 17);
            printf("Classe de voyage       : %s", voyage->classe);
            gotoxy(32, 18);
            printf("Pays de départ         : %s", voyage->pays_depart);
            gotoxy(32, 19);
            printf("Aéroport de départ     : %s", voyage->aeroport_depart);
            gotoxy(32, 20);
            printf("Pays d'arrivée         : %s", voyage->pays_arrivee);
            gotoxy(32, 21);
            printf("Aéroport d'arrivée     : %s", voyage->aeroport_arrive);
            gotoxy(32, 22);
            printf("Date de départ         : %02d/%02d/%d", 
                   voyage->date_voyage.jour, voyage->date_voyage.mois, voyage->date_voyage.annee);
            gotoxy(32, 23);
            printf("Heure de départ        : %02d:%02d", 
                   voyage->heure_depart.heure, voyage->heure_depart.minute);
            gotoxy(32, 24);
            printf("Heure d'arrivée        : %02d:%02d", 
                   voyage->heure_arrivee.heure, voyage->heure_arrivee.minute);
            gotoxy(32, 25);
            printf("Durée du vol           : %02dh%02dm", 
                   voyage->duree_vol.heure, voyage->duree_vol.minute);
            
            setColor(11);
            gotoxy(30, 26);
            printf("╚════════════════════════════════════════════════════════════════╝");
        }

        // Barre de navigation
        setColor(13);
        gotoxy(20, 27);
        printf("╠═══════════════════════════════════ NAVIGATION ═══════════════════════════════════╣");
        
        setColor(15);
        gotoxy(30, 28);
        printf("◄ Page précédente (←)  |  Page %d/%d  |  Page suivante (→) ►", page_courante, TOTAL_PAGES);
        gotoxy(30, 29);
        printf("Appuyez sur [Entrée] pour quitter");

        // Gestion de la navigation
        touche = _getch();
        if (touche == 75 && page_courante > 1) { // Flèche gauche
            page_courante--;
        }
        else if (touche == 77 && page_courante < TOTAL_PAGES) { // Flèche droite
            page_courante++;
        }
        else if (touche == 13) { // Entrée
            break;
        }
    } while (1);
}





void afficherBilletApresPaiementE(const char *username) {
    // Configuration initiale
    system("cls");
    drawFrame(20, 1, 100, 30);
    drawLogo();
    drawSeparator(20, 100, 10);
    
    setColor(9);
    gotoxy(20, 12);
    printf("╠═══════════════════════════════ BILLET DE RESERVATION INTERNATIONALE ══════════════════════════════╣");

    // Ouvrir le fichier des réservations
    FILE *fp_reservations = fopen("reservationsExterne.bin", "rb");
    if (fp_reservations == NULL) {
        setColor(12);
        gotoxy(35, 15);
        printf("Erreur lors de l'ouverture du fichier des réservations externes");
        gotoxy(35, 16);
        printf("Appuyez sur une touche pour continuer...");
        _getch();
        return;
    }

    // Ouvrir le fichier des voyages
    FILE *fp_voyages = fopen("voyageExterne.bin", "rb");
    if (fp_voyages == NULL) {
        setColor(12);
        gotoxy(35, 15);
        printf("Erreur lors de l'ouverture du fichier des voyages externes");
        gotoxy(35, 16);
        printf("Appuyez sur une touche pour continuer...");
        _getch();
        fclose(fp_reservations);
        return;
    }

    Reservation reservation;
    VoyageExterne voyage;
    Reservation derniereReservation;
    VoyageExterne dernierVoyage;
    int reservationTrouvee = 0;

    // Animation de recherche
    setColor(15);
    gotoxy(35, 15);
    printf("Recherche de votre réservation internationale");
    for(int i = 0; i < 3; i++) {
        printf(".");
        Sleep(300);
    }

    // Se positionner à la fin du fichier pour lire la dernière réservation
    fseek(fp_reservations, -sizeof(Reservation), SEEK_END);
    
    if (fread(&reservation, sizeof(Reservation), 1, fp_reservations) == 1) {
        if (strcmp(reservation.username, username) == 0) {
            // Chercher le voyage correspondant
            rewind(fp_voyages);
            while (fread(&voyage, sizeof(VoyageExterne), 1, fp_voyages) == 1) {
                if (strcmp(reservation.voyage_id, voyage.id) == 0) {
                    derniereReservation = reservation;
                    dernierVoyage = voyage;
                    reservationTrouvee = 1;
                    break;
                }
            }
        }
    }

    system("cls");
    drawFrame(20, 1, 100, 30);
    drawLogo();
    drawSeparator(20, 100, 10);
    
    setColor(9);
    gotoxy(20, 12);
    printf("╠═══════════════════════════════ BILLET DE RESERVATION INTERNATIONALE ══════════════════════════════╣");

    if (reservationTrouvee) {
        setColor(10); // Vert pour le succès
        gotoxy(35, 14);
        printf("Réservation internationale trouvée pour : %s", username);
        gotoxy(35, 15);
        printf("ID du voyage : %s", derniereReservation.voyage_id);
        
        afficherBilletE(&dernierVoyage, &derniereReservation);
    } else {
        setColor(12); // Rouge pour l'erreur
        gotoxy(35, 15);
        printf("Aucune réservation internationale trouvée pour l'utilisateur %s", username);
        gotoxy(35, 17);
        printf("Appuyez sur une touche pour continuer...");
        _getch();
    }

    fclose(fp_reservations);
    fclose(fp_voyages);
}



int estDateValide(Date date) {
    // Tableau des jours dans chaque mois (année non bissextile)
    const int jours_par_mois[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    // Vérifier l'année (on suppose que les voyages sont pour 2024 et après)
    if (date.annee < 2024) {
        return 0;
    }

    // Vérifier le mois
    if (date.mois < 1 || date.mois > 12) {
        return 0;
    }

    // Vérifier le jour
    int max_jours = jours_par_mois[date.mois];
    
    // Ajuster pour février lors d'une année bissextile
    if (date.mois == 2 && ((date.annee % 4 == 0 && date.annee % 100 != 0) || date.annee % 400 == 0)) {
        max_jours = 29;
    }

    if (date.jour < 1 || date.jour > max_jours) {
        return 0;
    }

    // Obtenir la date actuelle
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    Date date_actuelle = {
        .jour = tm_now->tm_mday,
        .mois = tm_now->tm_mon + 1,
        .annee = tm_now->tm_year + 1900
    };

    // Vérifier que la date n'est pas dans le passé
    if (date.annee < date_actuelle.annee ||
        (date.annee == date_actuelle.annee && date.mois < date_actuelle.mois) ||
        (date.annee == date_actuelle.annee && date.mois == date_actuelle.mois && date.jour < date_actuelle.jour)) {
        return 0;
    }

    // La date est valide
    return 1;
}





void saisirCriteresRechercheExterne(char *depart, char *arrive, char *pays_depart, char *pays_arrivee, Date *date, int *nb_places) {
    printf("Entrez le pays de départ : ");
    scanf("%s", pays_depart);
    printf("Entrez l'aéroport de départ : ");
    scanf("%s", depart);
    printf("Entrez le pays d'arrivée : ");
    scanf("%s", pays_arrivee);
    printf("Entrez l'aéroport d'arrivée : ");
    scanf("%s", arrive);
    printf("Entrez la date de voyage (jour mois année) : ");
    scanf("%d %d %d", &date->jour, &date->mois, &date->annee);
    printf("Entrez le nombre de places à réserver : ");
    scanf("%d", nb_places);
}




int afficherVoyagesDisponiblesInternes(FILE *fichier, const char *depart, const char *arrive, Date date, int nb_places) {
    VoyageInterne voyage;
    int index = 1;
    int voyage_trouve = 0;
    int ligne_actuelle = 14; // Position de départ après le titre

    // Afficher l'en-tête stylisé
    setColor(11); // Cyan clair pour l'en-tête
    gotoxy(22, ligne_actuelle);
    printf("╔════════════════════════════════════════ VOLS DISPONIBLES ══════════════════════════════════════╗");
    ligne_actuelle += 2;

    // En-tête des colonnes
    setColor(13); // Blanc pour les détails
    gotoxy(25, ligne_actuelle);
    printf("Critères de recherche :");
    setColor(7);
    gotoxy(25, ligne_actuelle + 1);
    printf("De: %-15s  Vers: %-15s  Date: %02d/%02d/%04d  Places: %d", 
           depart, arrive, date.jour, date.mois, date.annee, nb_places);
    ligne_actuelle += 3;

    while (fread(&voyage, sizeof(VoyageInterne), 1, fichier)) {
        if (strcmp(voyage.aeroport_depart, depart) == 0 &&
            strcmp(voyage.aeroport_arrive, arrive) == 0 &&
            voyage.date_voyage.jour == date.jour &&
            voyage.date_voyage.mois == date.mois &&
            voyage.date_voyage.annee == date.annee &&
            voyage.nb_place >= nb_places) {

            voyage_trouve = 1;

            // Cadre pour chaque vol
            setColor(9); // Bleu pour le cadre
            gotoxy(25, ligne_actuelle);
            printf("┌─────────────────────────────────── Vol N°%d ────────────────────────────────────┐", index);
            
            // Informations du vol en deux colonnes
            setColor(index % 2 == 0 ? 15 : 7); // Alterner blanc et gris clair
            
            // Colonne gauche
            gotoxy(27, ligne_actuelle + 1);
            printf("ID Vol: %-10s              Compagnie: %-20s", voyage.id, voyage.compagnie);
            
            gotoxy(27, ligne_actuelle + 2);
            printf("Départ: %-10s              Arrivée: %-20s", voyage.aeroport_depart, voyage.aeroport_arrive);
            
            gotoxy(27, ligne_actuelle + 3);
            printf("Date: %02d/%02d/%04d               Prix: %d MAD", 
                   voyage.date_voyage.jour, voyage.date_voyage.mois, 
                   voyage.date_voyage.annee, voyage.prix);
            
            gotoxy(27, ligne_actuelle + 4);
            printf("Heure départ: %02d:%02d           Heure arrivée: %02d:%02d", 
                   voyage.heure_depart.heure, voyage.heure_depart.minute,
                   voyage.heure_arrivee.heure, voyage.heure_arrivee.minute);
            
            gotoxy(27, ligne_actuelle + 5);
            printf("Durée du vol: %02dh%02dm          Places disponibles: %d", 
                   voyage.duree_vol.heure, voyage.duree_vol.minute, voyage.nb_place);

            // Ligne de fermeture du cadre
            setColor(9);
            gotoxy(25, ligne_actuelle + 6);
            printf("└──────────────────────────────────────────────────────────────────────────────┘");

            ligne_actuelle += 8; // Espace entre les vols
            index++;

            // Vérifier si on atteint la limite du cadre
            if (ligne_actuelle > 25) {
                setColor(14); // Jaune pour le message
                gotoxy(25, 26);
                printf("↑↓ Utilisez les flèches pour voir plus de vols...");
                break;
            }
        }
    }

    if (!voyage_trouve) {
        setColor(12); // Rouge pour message d'erreur
        gotoxy(30, ligne_actuelle);
        printf("Aucun vol ne correspond à vos critères de recherche.");
    }

    setColor(15); // Retour à la couleur par défaut
    return voyage_trouve ? index - 1 : 0;
}



int demanderChoixVoyage(int index_max) {
    int choix_voyage;
    
    // Nettoyer l'écran et dessiner le cadre complet
    system("cls");
    drawFrame(20, 1, 100, 30);
    drawLogo();
    drawSeparator(20, 100, 10);

    // Titre
    setColor(9);
    gotoxy(20, 12);
    printf("╠══════════════════════════════════════ SÉLECTION DU VOL ═══════════════════════════════════════╣");

    // Afficher les options
    setColor(15); // Blanc pour le texte
    gotoxy(35, 15);
    printf("▶ Pour annuler la réservation, entrez [0]");
    
    gotoxy(35, 17);
    printf("▶ Pour sélectionner un vol, entrez un numéro entre [1-%d]", index_max);

    // Zone de saisie avec style
    setColor(11); // Cyan clair pour la saisie
    gotoxy(35, 19);
    printf("Votre choix ➤ ");
    
    scanf("%d", &choix_voyage);

    // Gestion des messages de retour
    if (choix_voyage < 0 || choix_voyage > index_max) {
        setColor(12); // Rouge pour l'erreur
        gotoxy(48, 19);
        printf("⚠ Choix invalide !");
        Sleep(1500);
        return -1;
    }

    // Message de confirmation
    if (choix_voyage > 0) {
        system("cls");
        setColor(10); // Vert pour la confirmation
        gotoxy(48, 19);
        printf("✓ Vol %d sélectionné !", choix_voyage);
    } else {
        setColor(14); // Jaune pour l'annulation
        gotoxy(48, 19);
        printf("○ Réservation annulée");
    }
    Sleep(1000);

    setColor(15); // Retour à la couleur par défaut
    return choix_voyage;
}



int traiterPaiement(const char *username, float montant_total) {
    InformationsPaiement payement;

    // Configuration initiale
    system("cls");
    drawFrame(20, 1, 100, 30);
    drawLogo();
    drawSeparator(20, 100, 10);
    
    setColor(9);
    gotoxy(20, 12);
    printf("╠═════════════════════════════════════ PROCESSUS DE PAIEMENT ═══════════════════════════════════════╣");

    // Informations de base
    setColor(11);
    gotoxy(30, 14);
    printf("Client: %-20s", username);
    gotoxy(30, 15);
    printf("Montant total à payer: %.2f MAD", montant_total);

    setColor(15);
    gotoxy(30, 17);
    printf("╔══════════════════ INFORMATIONS DE PAIEMENT ══════════════════╗");

    // Numéro de carte
    gotoxy(31, 18);
    printf("Numéro de carte (16 chiffres) : ");
    gotoxy(65, 18);
    if (scanf("%16s", payement.numero_carte) != 1) {
        setColor(12);
        gotoxy(35, 24);
        printf("Erreur de lecture du numéro de carte.");
        return 0;
    }
    while (getchar() != '\n');

    // Date d'expiration
    gotoxy(32, 19);
    printf("Date d'expiration (MM AA)     : ");
    gotoxy(65, 19);
    if (scanf("%d %d", &payement.date_expiration.mois, &payement.date_expiration.annee) != 2) {
        setColor(12);
        gotoxy(35, 24);
        printf("Erreur de lecture de la date d'expiration.");
        return 0;
    }
    while (getchar() != '\n');

    // Titulaire
    gotoxy(32, 20);
    printf("Titulaire de la carte         : ");
    gotoxy(65, 20);
    if (fgets(payement.titulaire_carte, sizeof(payement.titulaire_carte), stdin) == NULL) {
        setColor(12);
        gotoxy(35, 24);
        printf("Erreur de lecture du nom du titulaire.");
        return 0;
    }
    payement.titulaire_carte[strcspn(payement.titulaire_carte, "\n")] = '\0';

    // CVV
    gotoxy(32, 21);
    printf("Code de sécurité (CVV)        : ");
    gotoxy(65, 21);
    if (scanf("%3s", payement.code_securite) != 1) {
        setColor(12);
        gotoxy(35, 24);
        printf("Erreur de lecture du CVV.");
        return 0;
    }
    while (getchar() != '\n');

    gotoxy(30, 22);
    printf("╚═════════════════════════════════════════════════════════════╝");

    // Validation
    if (strlen(payement.numero_carte) != 16) {
        setColor(12);
        gotoxy(35, 24);
        printf("Le numéro de carte doit contenir exactement 16 chiffres.");
        return 0;
    }

    if (strlen(payement.code_securite) != 3) {
        setColor(12);
        gotoxy(35, 24);
        printf("Le CVV doit contenir exactement 3 chiffres.");
        return 0;
    }

    if (payement.date_expiration.mois < 1 || payement.date_expiration.mois > 12) {
        setColor(12);
        gotoxy(35, 24);
        printf("Mois d'expiration invalide.");
        return 0;
    }

    // Message de succès
    setColor(10);
    gotoxy(35, 24);
    printf("Paiement de %.2f MAD effectué avec succès!", montant_total);
    gotoxy(35, 25);
    printf("Merci pour votre confiance!");
    Sleep(2000);

    return 1;
}





int traiterPaiementE(const char *username, float montant_total) {
    InformationsPaiement payement;
    
    // Constantes pour le centrage
    const int FRAME_LEFT = 20;
    const int FRAME_RIGHT = 100;
    const int FRAME_WIDTH = FRAME_RIGHT - FRAME_LEFT;
    const int CENTER_X = FRAME_LEFT + (FRAME_WIDTH / 2) + 8; // Ajouté +3 pour un meilleur centrage
    const int FORM_LEFT = CENTER_X - 15;

    // Affichage de l'écran de paiement
    system("cls");
    drawFrame(FRAME_LEFT, 1, FRAME_RIGHT, 30);
    drawLogo();
    drawSeparator(FRAME_LEFT, FRAME_RIGHT, 10);
    
    setColor(9);
    gotoxy(FRAME_LEFT, 12);
    printf("╠═════════════════════════════════════ PROCESSUS DE PAIEMENT ═══════════════════════════════════════╣");

    // Informations de paiement
    setColor(15);
    char info[100];
    sprintf(info, "Utilisateur : %s", username);
    gotoxy(CENTER_X - (strlen(info) / 2), 14);
    printf("%s", info);

    setColor(14); // Jaune pour le montant
    sprintf(info, "Montant total à payer : %.2f MAD", montant_total);
    gotoxy(CENTER_X - (strlen(info) / 2), 15);
    printf("%s", info);

    // Formulaire de paiement
    setColor(15);
    gotoxy(FORM_LEFT, 17);
    printf("Numéro de carte (16 chiffres) : ");
    scanf("%s", payement.numero_carte);
    
    gotoxy(FORM_LEFT, 18);
    printf("Date d'expiration (MM AA)     : ");
    scanf("%d %d", &payement.date_expiration.mois, &payement.date_expiration.annee);
    
    // Vider le buffer d'entrée
    while (getchar() != '\n');
    
    gotoxy(FORM_LEFT, 19);
    printf("Titulaire de la carte         : ");
    fgets(payement.titulaire_carte, sizeof(payement.titulaire_carte), stdin);
    payement.titulaire_carte[strcspn(payement.titulaire_carte, "\n")] = '\0';
    
    gotoxy(FORM_LEFT, 20);
    printf("Code de sécurité (CVV)        : ");
    scanf("%s", payement.code_securite);

    // Validation des informations
    if (strlen(payement.numero_carte) != 16 || strlen(payement.code_securite) != 3) {
        setColor(12); // Rouge pour l'erreur
        const char* error_msg = "⚠️ Erreur : Les informations de paiement sont invalides.";
        gotoxy(CENTER_X - (strlen(error_msg) / 2), 22);
        printf("%s", error_msg);
        Sleep(2000);
        return 0;
    }

    // Animation de traitement
    setColor(13);
    const char* processing_msg = "Traitement du paiement en cours...";
    gotoxy(CENTER_X - (strlen(processing_msg) / 2), 22);
    printf("%s", processing_msg);
    Sleep(1500);

    // Message de succès
    system("cls");
    drawFrame(FRAME_LEFT, 1, FRAME_RIGHT, 30);
    drawLogo();
    drawSeparator(FRAME_LEFT, FRAME_RIGHT, 10);
    
    setColor(13); // Changé en mauve (13)
    gotoxy(FRAME_LEFT, 12);
    printf("╠═══════════════════════════════════════ PAIEMENT RÉUSSI ═══════════════════════════════════════════╣");

    setColor(15);
    sprintf(info, "Paiement de %.2f MAD effectué avec succès!", montant_total);
    gotoxy(CENTER_X - (strlen(info) / 2), 15);
    printf("%s", info);

    sprintf(info, "Carte utilisée : **** **** **** %s", &payement.numero_carte[12]);
    gotoxy(CENTER_X - (strlen(info) / 2), 16);
    printf("%s", info);

    setColor(13);
    const char* thanks_msg = "Merci pour votre confiance!";
    gotoxy(CENTER_X - (strlen(thanks_msg) / 2), 18);
    printf("%s", thanks_msg);

    const char* continue_msg = "Appuyez sur une touche pour voir votre billet...";
    gotoxy(CENTER_X - (strlen(continue_msg) / 2), 20);
    printf("%s", continue_msg);
    _getch();

   // Afficher le billet
    afficherBilletApresPaiementE(username);
    return 1;
}






void enregistrerReservationInterne(const char *username, VoyageInterne voyage, int nb_places, float montant_paye) {
    FILE *reservation_file = fopen("reservationsInterne.bin", "ab");
    if (reservation_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier des réservations internes.\n");
        return;
    }

    Reservation reservation;
    strcpy(reservation.username, username);
    strcpy(reservation.voyage_id, voyage.id);
    reservation.nb_places_reservees = nb_places;
    reservation.montant_paye = montant_paye;  // Enregistrement du montant payé

    // Simule la date actuelle
    obtenir_date_du_jour(&reservation.date_reservation);

    fwrite(&reservation, sizeof(Reservation), 1, reservation_file);
    fclose(reservation_file);

    printf("Les informations de réservation et le montant payé ont été enregistrées pour le voyage interne.\n");
}



void confirmerReservationInterne(FILE *fichier, const char *username, int choix_voyage, int nb_places,
                                  char *aeroport_depart, char *aeroport_arrive, Date date) {
    VoyageInterne voyage;
    int index = 1;

    rewind(fichier);
    while (fread(&voyage, sizeof(VoyageInterne), 1, fichier)) {
        if (strcmp(voyage.aeroport_depart, aeroport_depart) == 0 &&
            strcmp(voyage.aeroport_arrive, aeroport_arrive) == 0 &&
            voyage.date_voyage.jour == date.jour &&
            voyage.date_voyage.mois == date.mois &&
            voyage.date_voyage.annee == date.annee &&
            voyage.nb_place >= nb_places) {

            if (index == choix_voyage) {
                // Étape 1 : Traitement du paiement
                float montant_total =  voyage.prix * nb_places ; // Calcul du montant total à payer

                int paiement_reussi = traiterPaiement(username, montant_total);
                if (!paiement_reussi) {
                    printf("Paiement annulé. Réservation non effectuée.\n");
                    return;
                }

                // Étape 2 : Mise à jour des places disponibles
                voyage.nb_place -= nb_places;
                fseek(fichier, -sizeof(VoyageInterne), SEEK_CUR);
                fwrite(&voyage, sizeof(VoyageInterne), 1, fichier);

                // Étape 3 : Enregistrement de la réservation avec le montant payé
                enregistrerReservationInterne(username, voyage, nb_places, montant_total);

                printf("Réservation confirmée pour %d place(s) pour le voyage %s.\n", nb_places, voyage.id);
                afficherBilletApresPaiement(username);
                break;
            }
            index++;
        }
    }
 
}



// faire une reservation;
void saisirCriteresRecherche(char *depart, char *arrive, Date *date, int *nb_places) {
    printf("Entrez l'aéroport de départ : ");
    scanf("%s", depart);
    printf("Entrez l'aéroport d'arrivée : ");
    scanf("%s", arrive);
    printf("Entrez la date de voyage (jour mois année) : ");
    scanf("%d %d %d", &date->jour, &date->mois, &date->annee);
    printf("Entrez le nombre de places à réserver : ");
    scanf("%d", nb_places);
}




//reserver voyage interne

void ReserverVoyageInterne(const char *username) {
    char depart[30], arrive[30];
    Date date;
    int nb_places;
    int index;
    int choix_voyage;

    // Configuration initiale
    system("cls");
    drawFrame(20, 1, 100, 30);
    drawLogo();
    drawSeparator(20, 100, 10);
    
    setColor(13);
    gotoxy(20, 12);
    printf("╠═══════════════════════════════════ RESERVATION VOYAGE INTERNE ════════════════════════════════════╣");

    FILE *fichier = fopen("voyageInterne.bin", "rb+");
    if (fichier == NULL) {
        setColor(12); // Rouge pour l'erreur
        gotoxy(35, 15);
        printf("Erreur lors de l'ouverture du fichier des voyages internes.");
        _getch();
        return;
    }

    // Saisie des critères de recherche
    setColor(15); // Blanc pour le texte normal
    gotoxy(30, 14);
    printf("Entrez l'aéroport de départ : ");
    gotoxy(61, 14);
    scanf("%s", depart);

    gotoxy(30, 15);
    printf("Entrez l'aéroport d'arrivée : ");
    gotoxy(61, 15);
    scanf("%s", arrive);

    gotoxy(30, 16);
    printf("Date de voyage (jour mois année) : ");
    gotoxy(64, 16);
    scanf("%d %d %d", &date.jour, &date.mois, &date.annee);

    gotoxy(30, 17);
    printf("Nombre de places à réserver : ");
    gotoxy(60, 17);
    scanf("%d", &nb_places);

    // Affichage des voyages disponibles
    system("cls");
    drawFrame(20, 1, 100, 30);
    drawLogo();
    drawSeparator(20, 100, 10);
    
    setColor(9);
    gotoxy(20, 12);
    printf("╠═════════════════════════════════════ VOYAGES DISPONIBLES ═════════════════════════════════════════╣");

    index = afficherVoyagesDisponiblesInternes(fichier, depart, arrive, date, nb_places);
    
    if (index == 0) {
        system("cls");
        setColor(12);
        gotoxy(35, 15);
        printf("Aucun voyage disponible ne correspond à vos critères.");
        gotoxy(35, 17);
        printf("Appuyez sur une touche pour revenir au menu...");
        _getch();
    } else {
        // Attendre que l'utilisateur voie les vols disponibles
        setColor(15);
        gotoxy(30, 30);
        printf("Appuyez sur une touche pour continuer la sélection...");
        _getch();
        
        // Demander le choix du vol
        choix_voyage = demanderChoixVoyage(index);
            
        if (choix_voyage == 0) {
            setColor(14);
            gotoxy(35, 27);
            printf("Réservation annulée.");
            Sleep(1500);
            fclose(fichier);
            return;
        } else if (choix_voyage != -1) {
            // Confirmation et enregistrement de la réservation
            system("cls");
            drawFrame(20, 1, 100, 30);
            drawLogo();
            drawSeparator(20, 100, 10);
            
            setColor(9);
            gotoxy(20, 12);
            printf("╠═════════════════════════════════ CONFIRMATION DE RESERVATION ══════════════════════════════════╣");

            confirmerReservationInterne(fichier, username, choix_voyage, nb_places, depart, arrive, date);
            
            setColor(15);
            gotoxy(30, 27);
            system("cls");
            printf("Appuyez sur une touche pour revenir au menu...");
            _getch();
        }
    }

    fclose(fichier);
}






//affichage des lignes disponibles

int afficherVoyagesDisponiblesExterne(FILE *fichier, const char *depart, const char *arrive, 
                                     const char *pays_depart, const char *pays_arrivee, 
                                     Date date, int nb_places) {
    VoyageExterne voyage;
    int index = 1;
    int voyage_trouve = 0;
    int ligne_actuelle = 14; // Position de départ après le titre

    // Afficher l'en-tête stylisé
    setColor(11);
    gotoxy(22, ligne_actuelle);
    printf("╔════════════════════════════════ VOLS INTERNATIONAUX DISPONIBLES ═══════════════════════════════╗");
    ligne_actuelle += 2;

    // En-tête des critères de recherche
    setColor(13);
    gotoxy(25, ligne_actuelle);
    printf("Critères de recherche :");
    setColor(7);
    gotoxy(25, ligne_actuelle + 1);
    printf("De: %s (%s)", depart, pays_depart);
    gotoxy(25, ligne_actuelle + 2);
    printf("Vers: %s (%s)", arrive, pays_arrivee);
    gotoxy(25, ligne_actuelle + 3);
    printf("Date: %02d/%02d/%04d  Places: %d", date.jour, date.mois, date.annee, nb_places);
    ligne_actuelle += 5;

    while (fread(&voyage, sizeof(VoyageExterne), 1, fichier)) {
        if (strcmp(voyage.aeroport_depart, depart) == 0 &&
            strcmp(voyage.aeroport_arrive, arrive) == 0 &&
            strcmp(voyage.pays_depart, pays_depart) == 0 &&
            strcmp(voyage.pays_arrivee, pays_arrivee) == 0 &&
            voyage.date_voyage.jour == date.jour &&
            voyage.date_voyage.mois == date.mois &&
            voyage.date_voyage.annee == date.annee &&
            voyage.nb_place >= nb_places) {

            voyage_trouve = 1;

            // Cadre pour chaque vol
            setColor(9);
            gotoxy(25, ligne_actuelle);
            printf("┌─────────────────────────────────── Vol N°%d ────────────────────────────────────┐", index);
            
            // Informations du vol avec alternance de couleurs
            setColor(index % 2 == 0 ? 15 : 7);
            
            // Première ligne
            gotoxy(27, ligne_actuelle + 1);
            printf("ID Vol: %-10s              Compagnie: %-20s", voyage.id, voyage.compagnie);
            
            // Deuxième ligne
            gotoxy(27, ligne_actuelle + 2);
            printf("Départ: %-10s (%s)        Arrivée: %-10s (%s)", 
                   voyage.aeroport_depart, voyage.pays_depart,
                   voyage.aeroport_arrive, voyage.pays_arrivee);
            
            // Troisième ligne
            gotoxy(27, ligne_actuelle + 3);
            printf("Date: %02d/%02d/%04d               Classe: %s", 
                   voyage.date_voyage.jour, voyage.date_voyage.mois, 
                   voyage.date_voyage.annee, voyage.classe);
            
            // Quatrième ligne
            gotoxy(27, ligne_actuelle + 4);
            printf("Heure départ: %02d:%02d           Heure arrivée: %02d:%02d", 
                   voyage.heure_depart.heure, voyage.heure_depart.minute,
                   voyage.heure_arrivee.heure, voyage.heure_arrivee.minute);
            
            // Cinquième ligne
            gotoxy(27, ligne_actuelle + 5);
            printf("Durée: %02dh%02dm                 Prix: %d MAD", 
                   voyage.duree_vol.heure, voyage.duree_vol.minute, voyage.prix);

            // Sixième ligne
            gotoxy(27, ligne_actuelle + 6);
            printf("Places disponibles: %d", voyage.nb_place);

            // Ligne de fermeture du cadre
            setColor(9);
            gotoxy(25, ligne_actuelle + 7);
            printf("└──────────────────────────────────────────────────────────────────────────────┘");

            ligne_actuelle += 9; // Espace entre les vols
            index++;

            // Vérifier si on atteint la limite du cadre
            if (ligne_actuelle > 25) {
                setColor(14);
                gotoxy(25, 29);
                printf("↑↓ Utilisez les flèches pour voir plus de vols...");
                break;
            }
        }
    }

    if (!voyage_trouve) {
        setColor(12);
        gotoxy(30, ligne_actuelle);
        printf("Aucun vol international ne correspond à vos critères de recherche.");
    }

    setColor(15); // Retour à la couleur par défaut
    return voyage_trouve ? index - 1 : 0;
}


void confirmerReservationExterne(FILE *fichier, const char *username, int choix_voyage, int nb_places,
                               const char *depart, const char *arrive, const char *pays_depart, 
                               const char *pays_arrivee, Date date) {
    VoyageExterne voyage;
    Reservation nouvelle_reservation;
    int position = (choix_voyage - 1) * sizeof(VoyageExterne);
    
    // Positionner le curseur au bon voyage
    fseek(fichier, position, SEEK_SET);
    fread(&voyage, sizeof(VoyageExterne), 1, fichier);

    // Calculer le montant total
    float montant_total = voyage.prix * nb_places;

    // Traiter le paiement
    if (traiterPaiement(username, montant_total)) {
        // Préparer la nouvelle réservation
        strcpy(nouvelle_reservation.voyage_id, voyage.id);
        strcpy(nouvelle_reservation.username, username);
        nouvelle_reservation.nb_places_reservees = nb_places;
        nouvelle_reservation.montant_paye = montant_total;  // Stocker le montant calculé

        // Mettre à jour le nombre de places disponibles
        voyage.nb_place -= nb_places;
        fseek(fichier, position, SEEK_SET);
        fwrite(&voyage, sizeof(VoyageExterne), 1, fichier);

        // Enregistrer la réservation
        FILE *fichier_reservations = fopen("reservationsExterne.bin", "ab");
        if (fichier_reservations != NULL) {
            fwrite(&nouvelle_reservation, sizeof(Reservation), 1, fichier_reservations);
            fclose(fichier_reservations);

            // Afficher le billet
            afficherBilletApresPaiementE(username);
        } else {
            setColor(12);
            gotoxy(35, 20);
            printf("Erreur lors de l'enregistrement de la réservation.");
            Sleep(2000);
        }
    }
}



void enregistrerReservationExterne(const char *username, VoyageExterne voyage, int nb_places, float montant_paye) {
    FILE *reservation_file = fopen("reservationsExterne.bin", "ab");
    if (reservation_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier des réservations externes.\n");
        return;
    }

    Reservation reservation;
    strcpy(reservation.username, username);
    strcpy(reservation.voyage_id, voyage.id);
    reservation.nb_places_reservees = nb_places;
    reservation.montant_paye = montant_paye;

    // Simule la date actuelle
    obtenir_date_du_jour(&reservation.date_reservation);

    fwrite(&reservation, sizeof(Reservation), 1, reservation_file);
    fclose(reservation_file);

    printf("Les informations de réservation et le montant payé ont été enregistrés pour le voyage international.\n");
}



void ReserverVoyageExterne(const char *username) {
    char depart[30], arrive[30], pays_depart[30], pays_arrivee[30];
    Date date;
    int nb_places;
    int index;
    int choix_voyage;

    // Configuration initiale
    system("cls");
    drawFrame(20, 1, 100, 30);
    drawLogo();
    drawSeparator(20, 100, 10);
    
    setColor(13);
    gotoxy(20, 12);
    printf("╠═══════════════════════════════════ RESERVATION VOYAGE EXTERNE ════════════════════════════════════╣");

    FILE *fichier = fopen("voyageExterne.bin", "rb+");
    if (fichier == NULL) {
        setColor(12); // Rouge pour l'erreur
        gotoxy(35, 15);
        printf("Erreur lors de l'ouverture du fichier des voyages externes.");

        _getch();
        return;
    }

    // Saisie des critères de recherche
    setColor(15); // Blanc pour le texte normal
    gotoxy(30, 14);
    printf("Entrez l'aéroport de départ : ");
    gotoxy(61, 14);
    scanf("%s", depart);

    gotoxy(30, 15);
    printf("Entrez le pays de départ    : ");
    gotoxy(61, 15);
    scanf("%s", pays_depart);

    gotoxy(30, 16);
    printf("Entrez l'aéroport d'arrivée : ");
    gotoxy(61, 16);
    scanf("%s", arrive);

    gotoxy(30, 17);
    printf("Entrez le pays d'arrivée    : ");
    gotoxy(61, 17);
    scanf("%s", pays_arrivee);

    gotoxy(30, 18);
    printf("Date de voyage (jour mois année) : ");
    gotoxy(64, 18);
    scanf("%d %d %d", &date.jour, &date.mois, &date.annee);

    gotoxy(30, 19);
    printf("Nombre de places à réserver : ");
    gotoxy(60, 19);
    scanf("%d", &nb_places);

    // Affichage des voyages disponibles
    system("cls");
    drawFrame(20, 1, 100, 30);
    drawLogo();
    drawSeparator(20, 100, 10);
    
    setColor(9);
    gotoxy(20, 12);
    printf("╠═════════════════════════════════════ VOYAGES DISPONIBLES ═════════════════════════════════════════╣");

    index = afficherVoyagesDisponiblesExterne(fichier, depart, arrive, pays_depart, pays_arrivee, date, nb_places);
    
    if (index == 0) {
        setColor(12);
        gotoxy(35, 15);
        printf("Aucun voyage disponible ne correspond à vos critères.");
        gotoxy(35, 17);
        printf("Appuyez sur une touche pour revenir au menu...");
        _getch();
    } else {
        // Attendre que l'utilisateur voie les vols disponibles
        setColor(15);
        gotoxy(30, 30);
        printf("Appuyez sur une touche pour continuer la sélection...");
        _getch();

        // Demander le choix du vol
        choix_voyage = demanderChoixVoyage(index);
            
        if (choix_voyage == 0) {
            setColor(14);
            gotoxy(35, 27);
            printf("Réservation annulée.");
            Sleep(1500);
            fclose(fichier);
            return;
        } else if (choix_voyage != -1) {
            // Confirmation et enregistrement de la réservation
            system("cls");
            drawFrame(20, 1, 100, 30);
            drawLogo();
            drawSeparator(20, 100, 10);
            
            setColor(9);
            gotoxy(20, 12);
            printf("╠═════════════════════════════════ CONFIRMATION DE RESERVATION ══════════════════════════════════╣");

            confirmerReservationExterne(fichier, username, choix_voyage, nb_places, depart, arrive, pays_depart, pays_arrivee, date);
            
            setColor(15);

            _getch();
        }
    }

    fclose(fichier);
}


// reservation de voyage;

void ReserverVoyage(char* username) {
    system("cls");
    int currentChoice = 0;
    const int NUM_OPTIONS = 3;
    char* options[] = {
        "Voyage interne",
        "Voyage externe",
        "Retour"
    };

    // Constantes pour le centrage
    const int FRAME_LEFT = 20;
    const int FRAME_RIGHT = 100;
    const int FRAME_WIDTH = FRAME_RIGHT - FRAME_LEFT;
    const int CENTER_X = FRAME_LEFT + (FRAME_WIDTH / 2);
    const int MENU_START_Y = 15;

    while(1) {
        // Affichage initial
        drawFrame(FRAME_LEFT, 1, FRAME_RIGHT, 30);
        drawLogo();
        drawSeparator(FRAME_LEFT, FRAME_RIGHT, 10);
        
        // Titre
        setColor(9);
        gotoxy(FRAME_LEFT, 12);
        printf("╠══════════════════════════════════════ RÉSERVATION DE VOYAGE ══════════════════════════════════════╣");

        // Afficher les options (centrées)
        for(int i = 0; i < NUM_OPTIONS; i++) {
            int optionLength = strlen(options[i]);
            int startX = CENTER_X - (optionLength / 2) + 5;

            if(i == currentChoice) {
                setColor(13); // Mauve pour la sélection
                gotoxy(startX - 2, MENU_START_Y + i * 2);
                printf("→ %s", options[i]);
            } else {
                setColor(15); // Blanc pour les autres options
                gotoxy(startX, MENU_START_Y + i * 2);
                printf("%s", options[i]);
            }
        }

        // Instructions de navigation (centrées)
        setColor(13);
        const char* instructions = "↑↓: Navigation    ENTRÉE: Sélectionner    ÉCHAP: Retour";
        gotoxy(CENTER_X - (strlen(instructions) / 2) + 5, 26);
        printf("%s", instructions);

        // Navigation
        char key = _getch();
        if(key == 72) { // Flèche haut
            currentChoice = (currentChoice - 1 + NUM_OPTIONS) % NUM_OPTIONS;
        }
        else if(key == 80) { // Flèche bas
            currentChoice = (currentChoice + 1) % NUM_OPTIONS;
        }
        else if(key == 13) { // Entrée
            system("cls");
            
            switch(currentChoice) {
                case 0: {
                    // Réservation voyage interne
                    drawFrame(FRAME_LEFT, 1, FRAME_RIGHT, 30);
                    drawLogo();
                    drawSeparator(FRAME_LEFT, FRAME_RIGHT, 10);
                    
                    setColor(9);
                    gotoxy(FRAME_LEFT, 12);
                    printf("╠═════════════════════════════════ VOYAGE INTERNE ══════════════════════════════════╣");
                    
                    ReserverVoyageInterne(username);
                    
                    // Attendre que l'utilisateur soit prêt à revenir au menu
                    setColor(15);
                    printf("\n\nAppuyez sur une touche pour revenir au menu principal...");
                    _getch();
                    while(kbhit()) _getch(); // Vider le buffer clavier
                    break;
                }
                case 1: {
                    // Réservation voyage externe
                    drawFrame(FRAME_LEFT, 1, FRAME_RIGHT, 30);
                    drawLogo();
                    drawSeparator(FRAME_LEFT, FRAME_RIGHT, 10);
                    
                    setColor(9);
                    gotoxy(FRAME_LEFT, 12);
                    printf("╠═════════════════════════════════ VOYAGE EXTERNE ═════════════════════════════════════╣");
                    
                    ReserverVoyageExterne(username);
                    
                    // Attendre que l'utilisateur soit prêt à revenir au menu
                    setColor(15);
                    printf("\n\nAppuyez sur une touche pour revenir au menu principal...");
                    _getch();
                    while(kbhit()) _getch(); // Vider le buffer clavier
                    break;
                }
                case 2: {
                    return; // Retour au menu précédent
                }
            }
            system("cls");
        }
        else if(key == 27) { // Échap
            system("cls");
            return;
        }
        system("cls");
    }
}






void afficherReservationsInternes(const char* username) {
    system("cls");
    int page_actuelle = 1;
    int reservations_par_page = 2;
    int total_reservations = 0;
    int total_pages;
    char key;
    
    // Compter d'abord le nombre total de réservations
    FILE *count_file = fopen("reservationsInterne.bin", "rb");
    if (count_file != NULL) {
        Reservation temp;
        while (fread(&temp, sizeof(Reservation), 1, count_file) == 1) {
            if (strcmp(temp.username, username) == 0) {
                total_reservations++;
            }
        }
        fclose(count_file);
    }
    
    total_pages = (total_reservations + reservations_par_page - 1) / reservations_par_page;
    if (total_pages == 0) total_pages = 1;

    do {
        system("cls");
        // Dessiner le cadre principal et les éléments de base
        drawFrame(20, 1, 100, 30);
        drawLogo();
        drawSeparator(20, 100, 10);
        
        // Titre du menu
        setColor(13);
        gotoxy(20, 12);
        printf("╠═══════════════════════════════════ VOS RESERVATIONS INTERNES ═════════════════════════════════════╣");
        
        FILE *reservation_file = fopen("reservationsInterne.bin", "rb");
        if (reservation_file == NULL) {
            setColor(12);
            gotoxy(40, 15);
            printf("Erreur lors de l'ouverture du fichier des réservations.");
            gotoxy(40, 17);
            printf("Appuyez sur une touche pour continuer...");
            _getch();
            return;
        }

        Reservation reservation;
        int y_pos = 14;
        int reservations_trouvees = 0;
        int reservations_affichees = 0;
        int skip_count = (page_actuelle - 1) * reservations_par_page;

        while (fread(&reservation, sizeof(Reservation), 1, reservation_file) == 1) {
            if (strcmp(reservation.username, username) == 0) {
                if (skip_count > 0) {
                    skip_count--;
                    continue;
                }
                
                if (reservations_affichees >= reservations_par_page) {
                    break;
                }

                reservations_trouvees = 1;
                
                // Cadre pour chaque réservation
                setColor(9);
                gotoxy(30, y_pos);
                printf("╔════════════════════════════════════════════════════╗");
                gotoxy(30, y_pos + 1);
                printf("║");
                gotoxy(83, y_pos + 1);
                printf("║");
                gotoxy(30, y_pos + 2);
                printf("║");
                gotoxy(83, y_pos + 2);
                printf("║");
                gotoxy(30, y_pos + 3);
                printf("║");
                gotoxy(83, y_pos + 3);
                printf("║");
                gotoxy(30, y_pos + 4);
                printf("║");
                gotoxy(83, y_pos + 4);
                printf("║");
                gotoxy(30, y_pos + 5);
                printf("╚════════════════════════════════════════════════════╝");

                // Affichage des informations
                setColor(15);
                gotoxy(32, y_pos + 1);
                printf("ID du voyage : %s", reservation.voyage_id);
                gotoxy(32, y_pos + 2);
                printf("Nombre de places : %d", reservation.nb_places_reservees);
                gotoxy(32, y_pos + 3);
                printf("Montant payé : %.2f DH", reservation.montant_paye);
                gotoxy(32, y_pos + 4);
                printf("Date : %02d/%02d/%04d", 
                       reservation.date_reservation.jour,
                       reservation.date_reservation.mois,
                       reservation.date_reservation.annee);

                y_pos += 7;
                reservations_affichees++;
            }
        }

        fclose(reservation_file);

        if (!reservations_trouvees) {
            setColor(14);
            gotoxy(40, 15);
            printf("Vous n'avez aucune réservation interne.");
        }

        // Barre de navigation modifiée
        setColor(13);
        gotoxy(20, 28);
        printf("╠═══════════════════════════════════════════════════════════════════════════════════════════════════╣");
        gotoxy(25, 29);
        printf(" Page %d/%d   ← Précédent | Suivant → | (ESC) Retour au menu précédent", page_actuelle, total_pages);

        // Attendre l'entrée utilisateur
        key = _getch();
        if (key == 75 && page_actuelle > 1) { // Flèche gauche
            page_actuelle--;
        }
        else if (key == 77 && page_actuelle < total_pages) { // Flèche droite
            page_actuelle++;
        }
        else if (key == 27) { // Échap (ASCII 27)
            break;
        }

    } while (1);
}




void afficherReservationsExternes(const char* username) {
    system("cls");
    int page_actuelle = 1;
    int reservations_par_page = 2;
    int total_reservations = 0;
    int total_pages;
    char key;
    
    // Compter le nombre total de réservations
    FILE *count_file = fopen("reservationsExterne.bin", "rb");
    if (count_file != NULL) {
        Reservation temp;
        while (fread(&temp, sizeof(Reservation), 1, count_file) == 1) {
            if (strcmp(temp.username, username) == 0) {
                total_reservations++;
            }
        }
        fclose(count_file);
    }
    
    total_pages = (total_reservations + reservations_par_page - 1) / reservations_par_page;
    if (total_pages == 0) total_pages = 1;

    do {
        system("cls");
        drawFrame(20, 1, 100, 30);
        drawLogo();
        drawSeparator(20, 100, 10);
        
        // Titre du menu
        setColor(13);
        gotoxy(20, 12);
        printf("╠═══════════════════════════════════ VOS RESERVATIONS EXTERNES ═════════════════════════════════════╣");
        
        FILE *reservation_file = fopen("reservationsExterne.bin", "rb");
        if (reservation_file == NULL) {
            setColor(12);
            gotoxy(40, 15);
            printf("Erreur lors de l'ouverture du fichier des réservations.");
            gotoxy(40, 17);
            printf("Appuyez sur une touche pour continuer...");
            _getch();
            return;
        }

        Reservation reservation;
        int y_pos = 15;
        int reservations_trouvees = 0;
        int reservations_affichees = 0;
        int skip_count = (page_actuelle - 1) * reservations_par_page;

        while (fread(&reservation, sizeof(Reservation), 1, reservation_file) == 1) {
            if (strcmp(reservation.username, username) == 0) {
                if (skip_count > 0) {
                    skip_count--;
                    continue;
                }
                
                if (reservations_affichees >= reservations_par_page) {
                    break;
                }

                reservations_trouvees = 1;
                
                // Cadre pour chaque réservation
                setColor(9);
                gotoxy(30, y_pos);
                printf("╔════════════════════════════════════════════════════╗");
                gotoxy(30, y_pos + 1);
                printf("║");
                gotoxy(83, y_pos + 1);
                printf("║");
                gotoxy(30, y_pos + 2);
                printf("║");
                gotoxy(83, y_pos + 2);
                printf("║");
                gotoxy(30, y_pos + 3);
                printf("║");
                gotoxy(83, y_pos + 3);
                printf("║");
                gotoxy(30, y_pos + 4);
                printf("║");
                gotoxy(83, y_pos + 4);
                printf("║");
                gotoxy(30, y_pos + 5);
                printf("╚════════════════════════════════════════════════════╝");

                // Affichage des informations
                setColor(15);
                gotoxy(32, y_pos + 1);
                printf("ID du voyage : %s", reservation.voyage_id);
                gotoxy(32, y_pos + 2);
                printf("Nombre de places : %d", reservation.nb_places_reservees);
                gotoxy(32, y_pos + 3);
                printf("Montant payé : %.2f DH", reservation.montant_paye);
                gotoxy(32, y_pos + 4);
                printf("Date : %02d/%02d/%04d", 
                       reservation.date_reservation.jour,
                       reservation.date_reservation.mois,
                       reservation.date_reservation.annee);

                y_pos += 7;
                reservations_affichees++;
            }
        }

        fclose(reservation_file);

        if (!reservations_trouvees) {
            setColor(14);
            gotoxy(40, 15);
            printf("Vous n'avez aucune réservation externe.");
        }

        // Barre de navigation modifiée
        setColor(13);
        gotoxy(20, 28);
        printf("╠═══════════════════════════════════════════════════════════════════════════════════════════════════╣");
        gotoxy(25, 29);
        printf("  Page %d/%d   ← Précédent   | Suivant →  | (ESC) Retour au menu précédent ", page_actuelle, total_pages);

        // Attendre l'entrée utilisateur
        key = _getch();
        if (key == 75 && page_actuelle > 1) { // Flèche gauche
            page_actuelle--;
        }
        else if (key == 77 && page_actuelle < total_pages) { // Flèche droite
            page_actuelle++;
        }
        else if (key == 27) { // Échap (ASCII 27)
            break;
        }

    } while (1);
}



void afficherLignes(char* username) {
    system("cls");
    int choix;
    int currentChoice = 0;
    const int NUM_OPTIONS = 3;
    char* options[] = {
        "Lignes internes",
        "Lignes externes",
        "Retour"
    };

    do {
        // Affichage initial
        drawFrame(20, 1, 100, 30);
        drawLogo();
        drawSeparator(20, 100, 10);
        
        setColor(9); // Bleu pour le titre principal
        gotoxy(20, 12);
        printf("╠══════════════════════════════════════ AFFICHAGE DES LIGNES ═════════════════════════════════════╣");

        // Afficher les options
        for(int i = 0; i < NUM_OPTIONS; i++) {
            if(i == currentChoice) {
                setColor(13); // Mauve pour la sélection
                gotoxy(60, 15 + i * 2);
                printf("→ %s", options[i]);
            } else {
                setColor(15); // Blanc pour les autres options
                gotoxy(60, 15 + i * 2);
                printf("  %s", options[i]);
            }
        }

        // Navigation
        char key = _getch();
        if(key == 72) { // Flèche haut
            currentChoice = (currentChoice - 1 + NUM_OPTIONS) % NUM_OPTIONS;
        }
        else if(key == 80) { // Flèche bas
            currentChoice = (currentChoice + 1) % NUM_OPTIONS;
        }
        else if(key == 13) { // Entrée
            system("cls");
            
            switch(currentChoice) {
                case 0: { // Lignes internes
                    FILE *file = fopen(FILEvoyageInterne, "rb");
                    if (!file) {
                        drawFrame(20, 1, 100, 30);
                        drawLogo();
                        drawSeparator(20, 100, 10);
                        
                        setColor(12); // Rouge pour l'erreur
                        gotoxy(40, 15);
                        printf("⚠️ Erreur : Impossible d'ouvrir le fichier des lignes internes.");
                        Sleep(2000);
                    } else {
                        VoyageInterne voyage;
                        int found = 0;
                        int pageCourante = 0;
                        const int LIGNES_PAR_PAGE = 8;
                        const int DEBUT_LISTE = 16;
                        const int FIN_LISTE = 24;

                        do {
                            system("cls");
                            drawFrame(20, 1, 100, 30);
                            drawLogo();
                            drawSeparator(20, 100, 10);
                            
                            setColor(9);
                            gotoxy(20, 12);
                            printf("╠═════════════════════════════════ LIGNES INTERNES DISPONIBLES ═════════════════════════════════╣");
                            
                            setColor(13);
                            gotoxy(25, 14);
                            printf("%-10s %-15s %-15s %-10s %-12s", "ID", "Départ", "Arrivée", "Date", "Prix");
                            
                            setColor(15);
                            int ligne = DEBUT_LISTE;
                            fseek(file, pageCourante * LIGNES_PAR_PAGE * sizeof(VoyageInterne), SEEK_SET);
                            int compteur = 0;

                            while (fread(&voyage, sizeof(VoyageInterne), 1, file) == 1 && compteur < LIGNES_PAR_PAGE) {
                                found = 1;
                                gotoxy(25, ligne);
                                printf("%-10s %-15s %-15s %02d/%02d/%04d %-8d MAD",
                                    voyage.id, voyage.aeroport_depart, voyage.aeroport_arrive,
                                    voyage.date_voyage.jour, voyage.date_voyage.mois, 
                                    voyage.date_voyage.annee, voyage.prix);
                                ligne++;
                                compteur++;
                            }

                            if (found) {
                                setColor(13);
                                gotoxy(30, 26);
                                printf("← Utilisez les flèches pour naviguer entre les pages →");
                                gotoxy(45, 27);
                                printf("ÉCHAP: Retour");

                                char key = _getch();
                                if (key == -32 || key == 0) {
                                    key = _getch();
                                    if (key == 75) { // Gauche
                                        if (pageCourante > 0) pageCourante--;
                                    }
                                    else if (key == 77) { // Droite
                                        VoyageInterne nextVoyage;
                                        long currentPos = ftell(file);
                                        if (fread(&nextVoyage, sizeof(VoyageInterne), 1, file) == 1) {
                                            pageCourante++;
                                        }
                                        fseek(file, currentPos, SEEK_SET);
                                    }
                                }
                                else if (key == 27) { // Échap
                                    break;
                                }
                            } else {
                                setColor(12);
                                gotoxy(40, 16);
                                printf("⚠️ Aucun vol interne disponible pour le moment.");
                                Sleep(2000);
                                break;
                            }
                        } while (1);
                        fclose(file);
                    }
                    break;
                }
                
                case 1: { // Lignes externes
                    FILE *file = fopen(FILEvoyageExterne, "rb");
                    if (!file) {
                        drawFrame(20, 1, 100, 30);
                        drawLogo();
                        drawSeparator(20, 100, 10);
                        
                        setColor(12);
                        gotoxy(40, 15);
                        printf("⚠️ Erreur : Impossible d'ouvrir le fichier des lignes externes.");
                        Sleep(2000);
                    } else {
                        VoyageExterne voyage;
                        int found = 0;
                        int pageCourante = 0;
                        const int LIGNES_PAR_PAGE = 8;
                        const int DEBUT_LISTE = 16;
                        const int FIN_LISTE = 24;

                        do {
                            system("cls");
                            drawFrame(20, 1, 100, 30);
                            drawLogo();
                            drawSeparator(20, 100, 10);
                            
                            setColor(9);
                            gotoxy(20, 12);
                            printf("╠════════════════════════════════ VOLS INTERNATIONAUX DISPONIBLES ═════════════════════════════╣");
                            
                            setColor(13);
                            gotoxy(22, 14);
                            printf("%-10s %-12s %-12s %-15s %-15s %-10s %-10s %-8s",
                                "ID", "Départ", "Arrivée", "Aéro. Dép.", "Aéro. Arr.",
                                "Date", "Prix", "Classe");
                            
                            setColor(15);
                            int ligne = DEBUT_LISTE;
                            fseek(file, pageCourante * LIGNES_PAR_PAGE * sizeof(VoyageExterne), SEEK_SET);
                            int compteur = 0;

                            while (fread(&voyage, sizeof(VoyageExterne), 1, file) == 1 && compteur < LIGNES_PAR_PAGE) {
                                found = 1;
                                gotoxy(22, ligne);
                                printf("%-10s %-12s %-12s %-15s %-15s %02d/%02d/%04d %-8d %-8s",
                                    voyage.id, voyage.pays_depart, voyage.pays_arrivee,
                                    voyage.aeroport_depart, voyage.aeroport_arrive,
                                    voyage.date_voyage.jour, voyage.date_voyage.mois,
                                    voyage.date_voyage.annee, voyage.prix, voyage.classe);
                                ligne++;
                                compteur++;
                            }

                            if (found) {
                                setColor(13);
                                gotoxy(30, 26);
                                printf("← Utilisez les flèches pour naviguer entre les pages →");
                                gotoxy(45, 27);
                                printf("ÉCHAP: Retour");

                                char key = _getch();
                                if (key == -32 || key == 0) {
                                    key = _getch();
                                    if (key == 75) { // Gauche
                                        if (pageCourante > 0) pageCourante--;
                                    }
                                    else if (key == 77) { // Droite
                                        VoyageExterne nextVoyage;
                                        long currentPos = ftell(file);
                                        if (fread(&nextVoyage, sizeof(VoyageExterne), 1, file) == 1) {
                                            pageCourante++;
                                        }
                                        fseek(file, currentPos, SEEK_SET);
                                    }
                                }
                                else if (key == 27) { // Échap
                                    break;
                                }
                            } else {
                                setColor(12);
                                gotoxy(40, 16);
                                printf("⚠️ Aucun vol externe disponible pour le moment.");
                                Sleep(2000);
                                break;
                            }
                        } while (1);
                        fclose(file);
                    }
                    break;
                }
                
                case 2: // Retour
                    return;
            }
            system("cls");
        }
        system("cls");
    } while (1);
}




void menuPostConnexion(char* username) {
    system("cls");
    int currentChoice = 0;
    const int NUM_OPTIONS = 5;
    char* options[] = {
        "Chercher un voyage",
        "Afficher vos réservations internes",
        "Afficher vos réservations externes",
        "Voir nos offres",
        "Retour"
    };

    // Constantes pour le centrage
    const int FRAME_LEFT = 20;
    const int FRAME_RIGHT = 100;
    const int FRAME_WIDTH = FRAME_RIGHT - FRAME_LEFT;
    const int CENTER_X = FRAME_LEFT + (FRAME_WIDTH / 2);
    const int MENU_START_Y = 15; // Position Y de départ pour le menu

    while(1) {
        // Affichage initial
        drawFrame(FRAME_LEFT, 1, FRAME_RIGHT, 30);
        drawLogo();
        drawSeparator(FRAME_LEFT, FRAME_RIGHT, 10);
        
        // Titre avec le nom d'utilisateur
        setColor(9);
        gotoxy(FRAME_LEFT, 12);
        printf("╠═════════════════════════════════════ BIENVENUE %s ════════════════════════════════════════════╣", username);
                
        // Afficher les options (centrées)
        for(int i = 0; i < NUM_OPTIONS; i++) {
            int optionLength = strlen(options[i]);
            // Ajustement du centrage : +5 pour déplacer légèrement vers la droite
            int startX = CENTER_X - (optionLength / 2) + 5;

            if(i == currentChoice) {
                setColor(13); // Mauve pour la sélection
                gotoxy(startX - 2, MENU_START_Y + i * 2); // -2 pour la flèche
                printf("→ %s", options[i]);
            } else {
                setColor(15); // Blanc pour les autres options
                gotoxy(startX, MENU_START_Y + i * 2);
                printf("%s", options[i]);
            }
        }

        // Instructions de navigation (centrées)
        setColor(13);
        const char* instructions = "↑↓: Navigation    ENTRÉE: Sélectionner    ÉCHAP: Retour";
        // Ajustement du centrage des instructions : +5 pour déplacer légèrement vers la droite
        gotoxy(CENTER_X - (strlen(instructions) / 2) + 5, 26);
        printf("%s", instructions);

        // Navigation
        char key = _getch();
        if(key == 72) { // Flèche haut
            currentChoice = (currentChoice - 1 + NUM_OPTIONS) % NUM_OPTIONS;
        }
        else if(key == 80) { // Flèche bas
            currentChoice = (currentChoice + 1) % NUM_OPTIONS;
        }
        else if(key == 13) { // Entrée
            system("cls");
            
            switch(currentChoice) {
                case 0: {
                    
                    ReserverVoyage(username);
                    break;
                }
                case 1: {
                    afficherReservationsInternes(username);
                    break;
                }
                case 2: {
                    afficherReservationsExternes(username);
                    break;
                }
                case 3: {                    
                    rechercherEmploi(username);
                    break;
                }
                case 4:
                    return;
            }
            system("cls");
        }
        else if(key == 27) { // Échap
            return;
        }
        system("cls");
    }
}


























//Partie administrateur;

//fonction generator Id
void generateUniqueID(char *id) {
    static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    srand(time(NULL)); // Seed the random number generator

    id[0] = alphabet[rand() % (sizeof(alphabet) - 1)]; // Generate a random alphabetic character

    for (int i = 1; i < ID_LENGTH; i++) { // Generate 7 random digits
        id[i] = '0' + rand() % 10;
    }
    id[ID_LENGTH] = '\0'; // Null-terminate the string
}


int loginAdmin() {
    User admin;
    FILE *file = fopen(FILEadmin, "rb"); // Ouvrir en mode binaire

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return 0;
    }

    printf("Connexion administrateur:\n");

    // Saisie de l'identifiant
    printf("Entrez votre Identifiant: ");
    scanf("%s", admin.username);

    // Saisie du mot de passe masqué
    printf("Entrez votre mot de passe: ");
    char ch;
    int index = 0;
    while ((ch = getch()) != '\r') { // '\r' pour Enter (sous Windows)
        if (ch == '\b' && index > 0) { // Gérer le retour arrière
            index--;
            printf("\b \b"); // Efface un caractère
        } else if (ch != '\b') {
            admin.password[index++] = ch;
            printf("*"); // Affiche une étoile pour chaque caractère
        }
    }
    admin.password[index] = '\0'; // Terminer la chaîne
    printf("\n");

    // Vérification des informations d'identification de l'administrateur
    User tempAdmin;
    while (fread(&tempAdmin, sizeof(User), 1, file) == 1) {
        if (strcmp(tempAdmin.username, admin.username) == 0 && strcmp(tempAdmin.password, admin.password) == 0) {
            printf("Connexion réussie ! Bienvenue, %s %s.\n", tempAdmin.nom, tempAdmin.prenom);
            fclose(file);
            return 1;
        }
    }

    printf("Identifiant ou mot de passe incorrect.\n");
    fclose(file);
    return 0;
}

void signUpAdmin() {
    User newAdmin;
    FILE *file = fopen(FILEadmin, "ab+"); // Open the file in binary append mode

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    printf("Inscription:\n");

    // Collect user information
    printf("Entrez votre nom: ");
    scanf("%s", newAdmin.nom);
    printf("Entrez votre prénom: ");
    scanf("%s", newAdmin.prenom);
    printf("Entrez votre email: ");
    scanf("%s", newAdmin.email);
    printf("Entrez votre numéro de téléphone: ");
    scanf("%s", newAdmin.telephone);
    printf("Entrez un nom d'utilisateur: ");
    scanf("%s", newAdmin.username);

    // Check if the username already exists
    User tempAdmin;
    rewind(file); // Rewind to the beginning of the file for checking
    while (fread(&tempAdmin, sizeof(User), 1, file)) {
        if (strcmp(tempAdmin.username, newAdmin.username) == 0) {
            printf("Ce nom d'utilisateur est déjà pris.\n");
            fclose(file);
            return;
        }
    }

    printf("Entrez un mot de passe: ");
    scanf("%s", newAdmin.password);

    // Write user information to the file
    fwrite(&newAdmin, sizeof(User), 1, file);
    fclose(file);

    printf("Inscription réussie !\n");
}

//stocker les offres dans un fichier
void enregistrerOffres(OffreEmploi offres[], int nbOffres) {
    FILE *fp = fopen("offres.bin", "wb");
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }

    if (fwrite(offres, sizeof(OffreEmploi), nbOffres, fp) != nbOffres) {
        perror("Erreur lors de l'écriture dans le fichier");
    }

    fclose(fp);
    printf("Les offres ont été enregistrées dans le fichier offres.bin.\n");
}



// fct d'ajout d'un offre 
void ajouterOffre(OffreEmploi offres[], int *nbOffres) {
    if (*nbOffres >= MAX_OFFRES) {
        printf("Nombre maximal d'offres atteint.\n");
        return;
    }

    OffreEmploi nouvelleOffre;

    printf("Identifiant de l'offre : ");
    scanf("%s", nouvelleOffre.id);

    printf("Titre de l'offre : ");
    scanf("%s", nouvelleOffre.titre);

    printf("Description de l'offre : ");
    scanf("%s", nouvelleOffre.description);

    printf("Entreprise : ");
    scanf("%s", nouvelleOffre.entreprise);

    printf("Localisation : ");
    scanf("%s", nouvelleOffre.localisation);

    printf("Type de contrat : ");
    scanf("%s", nouvelleOffre.type_contrat);

    printf("Salaire : ");
    scanf("%d", &nouvelleOffre.salaire);

    offres[*nbOffres] = nouvelleOffre;
    (*nbOffres)++;

    printf("Offre ajoutée avec succès.\n");

  // Enregistrer les offres après chaque ajout
    enregistrerOffres(offres, *nbOffres);
}



// Function to add an internal flight line
void ajouterLigneInterne(FILE *file) {
    VoyageInterne voyage;
    printf("Ajouter une ligne interne:\n");


    generateUniqueID(voyage.id);  // Generate a unique ID
    printf("ID du voyage: %s\n", voyage.id);


    printf("Entrez la ville de départ: ");
    scanf("%s", voyage.aeroport_depart);
    printf("Entrez la ville d'arrivée: ");
    scanf("%s", voyage.aeroport_arrive);

    printf("Entrez la date de voyage (jour mois année): ");
    scanf("%d %d %d", &voyage.date_voyage.jour, &voyage.date_voyage.mois, &voyage.date_voyage.annee);

    printf("Entrez l'heure de départ (heure minute): ");
    scanf("%d %d", &voyage.heure_depart.heure, &voyage.heure_depart.minute);

    printf("Entrez l'heure d'arrivée (heure minute): ");
    scanf("%d %d", &voyage.heure_arrivee.heure, &voyage.heure_arrivee.minute);

    printf("Entrez le nombre de places : ");
    scanf("%d", &voyage.nb_place);

    printf("Entrez le nom de la compagnie: ");
    scanf("%s", voyage.compagnie);

    printf("Entrez le prix du billet (MAD): ");
    scanf("%d", &voyage.prix);
    printf("Entrez la durée du vol (h:min): ");

    scanf("%d%d", &voyage.duree_vol.heure,&voyage.duree_vol.minute);

    // enregstrer les information de voyage
    fwrite(&voyage, sizeof(VoyageInterne), 1, file);

    printf("Ligne interne ajoutée avec succès.\n");
}






// Function to add an external flight line
void ajouterLigneExterne(FILE *file) {
    VoyageExterne voyage;
    printf("Ajouter une ligne externe:\n");

    generateUniqueID(voyage.id);  // Generate a unique ID
    printf("ID du voyage: %s\n", voyage.id);

    printf("Entrez le pays de départ: ");
    scanf("%s", voyage.pays_depart);
    printf("Entrez l'aéroport de départ: ");
    scanf("%s", voyage.aeroport_depart);

    printf("Entrez le pays d'arrivée: ");
    scanf("%s", voyage.pays_arrivee);
    printf("Entrez l'aéroport d'arrivée: ");
    scanf("%s", voyage.aeroport_arrive);

    printf("Entrez la date de voyage (jour mois année): ");
    scanf("%d %d %d", &voyage.date_voyage.jour, &voyage.date_voyage.mois, &voyage.date_voyage.annee);

    printf("Entrez l'heure de départ (heure minute): ");
    scanf("%d %d", &voyage.heure_depart.heure, &voyage.heure_depart.minute);

    printf("Entrez l'heure d'arrivée (heure minute): ");
    scanf("%d %d", &voyage.heure_arrivee.heure, &voyage.heure_arrivee.minute);

    printf("Entrez le nombre de places : ");
    scanf("%d", &voyage.nb_place);

    printf("Entrez le nom de la compagnie: ");
    scanf("%s", voyage.compagnie);

    printf("Entrez le prix du billet (MAD): ");
    scanf("%d", &voyage.prix);

    printf("Entrez la classe de vol (economy, business, first): ");
    scanf("%s", voyage.classe);

    printf("Entrez la durée du vol (h:min): ");
    scanf("%d%d", &voyage.duree_vol.heure, &voyage.duree_vol.minute);

    // Save the external flight information with the unique ID
     fwrite(&voyage, sizeof(VoyageExterne), 1, file);

    printf("Ligne externe ajoutée avec succès.\n");
}

void AjouterLigne() {
    int choix;

    do {
        printf("\n1. Ajouter une ligne interne\n");
        printf("2. Ajouter une ligne externe \n");
        printf("3. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1: {
                // Ouvre le fichier binaire en mode ajout ("ab")
                FILE *file = fopen(FILEvoyageInterne, "ab+");
                if (!file) {
                    printf("Erreur lors de l'ouverture du fichier voyageInterne.bin\n");
                    return;
                }

                ajouterLigneInterne(file);  // Ajouter une ligne de vol interne
                fclose(file);
                break;
            }





            case 2: {
                FILE *file = fopen(FILEvoyageExterne, "ab+");

                if (!file) {
                    printf("Erreur lors de l'ouverture du fichier voyageExterne.bin\n");
                    return;
                }

                ajouterLigneExterne(file);  // Ajouter une ligne de vol externe
                fclose(file);
                break;
            }

            case 3:
                printf("Retour au menu principal.\n");
                break;

            default:
                printf("Choix invalide! Veuillez réessayer.\n");
                break;
        }
    } while (choix != 3);
}


//supprimer une ligne Interne;
void supprimerLigneInterne() {
    char id[ID_LENGTH + 1];
    printf("Entrez l'ID de la ligne interne à supprimer : ");
    scanf("%s", id);

    FILE *file = fopen(FILEvoyageInterne, "rb");
    FILE *tempFile = fopen("tempInterne.bin", "wb");
    if (!file || !tempFile) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    VoyageInterne voyage;
    int found = 0;

    while (fread(&voyage, sizeof(VoyageInterne), 1, file)) {
        if (strcmp(voyage.id, id) != 0) {
            fwrite(&voyage, sizeof(VoyageInterne), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILEvoyageInterne);
    rename("tempInterne.bin", FILEvoyageInterne);

    if (found) {
        printf("Ligne interne supprimée avec succès.\n");
    } else {
        printf("Ligne interne non trouvée.\n");
    }
}
//suprimer ligne externe
void supprimerLigneExterne() {
    char id[ID_LENGTH + 1];
    printf("Entrez l'ID de la ligne externe à supprimer : ");
    scanf("%s", id);

    FILE *file = fopen(FILEvoyageExterne, "rb");
    FILE *tempFile = fopen("tempExterne.bin", "wb");
    if (!file || !tempFile) {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    VoyageExterne voyage;
    int found = 0;

    while (fread(&voyage, sizeof(VoyageExterne), 1, file)) {
        if (strcmp(voyage.id, id) != 0) {
            fwrite(&voyage, sizeof(VoyageExterne), 1, tempFile);
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILEvoyageExterne);
    rename("tempExterne.bin", FILEvoyageExterne);

    if (found) {
        printf("Ligne externe supprimée avec succès.\n");
    } else {
        printf("Ligne externe non trouvée.\n");
    }
}
// supprimer une ligne qlq
void supprimerLigne(){
    char c;
    do{
        printf("\nVoulez-vous Supprimer une ligne :\n");
        printf("1. Interne\n");
        printf("2. Externe\n");
        printf("3. Annuller\n");
        printf("Entrez votre choix: ");
        scanf("%d",&c);
        switch (c)
                {
                case 1:{
                    supprimerLigneInterne();
                    break;
                }
                case 2:{
                    supprimerLigneExterne();
                    break;
                }

               case 3:
                    break;

                default:
                     printf("Choix invalide! Veuillez réessayer.\n");
                     break;
                }



    }while(c!=3);
}
//modifier un voyage
void modifierLigneInterne() {
    FILE *file = fopen(FILEvoyageInterne, "rb+");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier de voyages internes.\n");
        return;
    }

    char id[ID_LENGTH + 1];
    printf("Entrez l'ID du voyage interne à modifier : ");
    scanf("%s", id);

    VoyageInterne voyage;
    int found = 0;

    while (fread(&voyage, sizeof(VoyageInterne), 1, file) == 1) {
        if (strcmp(voyage.id, id) == 0) {
            int choix;
            do{
            printf("Voyage interne trouvé. Choisissez l'information à modifier :\n");
            printf("1. Aéroport de départ\n");
            printf("2. Aéroport d'arrivée\n");
            printf("3. Date de voyage\n");
            printf("4. Heure de départ\n");
            printf("5. Heure d'arrivée\n");
            printf("6. Nombre de places\n");
            printf("7. Compagnie\n");
            printf("8. Prix\n");
            printf("9. Durée du vol\n");
            printf("0. Quitter la modification\n");
            printf("Entrez votre choix : ");

            scanf("%d", &choix);

            switch (choix) {
                case 1:
                    printf("Nouvel aéroport de départ : ");
                    scanf("%s", voyage.aeroport_depart);
                    break;
                case 2:
                    printf("Nouvel aéroport d'arrivée : ");
                    scanf("%s", voyage.aeroport_arrive);
                    break;
                case 3:
                    printf("Nouvelle date (jour mois année) : ");
                    scanf("%d %d %d", &voyage.date_voyage.jour, &voyage.date_voyage.mois, &voyage.date_voyage.annee);
                    break;
                case 4:
                    printf("Nouvelle heure de départ (heure minute) : ");
                    scanf("%d %d", &voyage.heure_depart.heure, &voyage.heure_depart.minute);
                    break;
                case 5:
                    printf("Nouvelle heure d'arrivée (heure minute) : ");
                    scanf("%d %d", &voyage.heure_arrivee.heure, &voyage.heure_arrivee.minute);
                    break;
                case 6:
                    printf("Nouveau nombre de places : ");
                    scanf("%d", &voyage.nb_place);
                    break;
                case 7:
                    printf("Nouvelle compagnie : ");
                    scanf("%s", voyage.compagnie);
                    break;
                case 8:
                    printf("Nouveau prix : ");
                    scanf("%d", &voyage.prix);
                    break;
                case 9:
                    printf("Nouvelle durée du vol (heure minute) : ");
                    scanf("%d %d", &voyage.duree_vol.heure, &voyage.duree_vol.minute);
                    break;
                case 0:
                    break;
                default:
                    printf("Choix invalide!\n");
                    break;
            }

            // Remet le curseur à la position de ce voyage dans le fichier
            fseek(file, -sizeof(VoyageInterne), SEEK_CUR);
            fwrite(&voyage, sizeof(VoyageInterne), 1, file);

            }while(choix!=0);
            found = 1;
            printf("Informations du voyage interne modifiées avec succès.\n");
            break;
        }
    }

    if (!found) {
        printf("Voyage interne avec l'ID %s non trouvé.\n", id);
    }

    fclose(file);
}

// Fonction pour modifier les informations spécifiques d'un voyage externe
void modifierLigneExterne() {
    FILE *file = fopen(FILEvoyageExterne, "rb+");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier de voyages externes.\n");
        return;
    }

    char id[ID_LENGTH + 1];
    printf("Entrez l'ID du voyage externe à modifier : ");
    scanf("%s", id);

    VoyageExterne voyage;
    int found = 0;

    while (fread(&voyage, sizeof(VoyageExterne), 1, file) == 1) {
        if (strcmp(voyage.id, id) == 0) {
            int choix;
            do{
            printf("Voyage externe trouvé. Choisissez l'information à modifier :\n");
            printf("1. Pays de départ\n");
            printf("2. Aéroport de départ\n");
            printf("3. Pays d'arrivée\n");
            printf("4. Aéroport d'arrivée\n");
            printf("5. Date de voyage\n");
            printf("6. Heure de départ\n");
            printf("7. Heure d'arrivée\n");
            printf("8. Nombre de places\n");
            printf("9. Compagnie\n");
            printf("10. Prix\n");
            printf("11. Classe de vol\n");
            printf("12. Durée du vol\n");
            printf("0. Quitter la modification\n");
            printf("Entrez votre choix : ");

            scanf("%d", &choix);

            switch (choix) {
                case 1:
                    printf("Nouveau pays de départ : ");
                    scanf("%s", voyage.pays_depart);
                    break;
                case 2:
                    printf("Nouvel aéroport de départ : ");
                    scanf("%s", voyage.aeroport_depart);
                    break;
                case 3:
                    printf("Nouveau pays d'arrivée : ");
                    scanf("%s", voyage.pays_arrivee);
                    break;
                case 4:
                    printf("Nouvel aéroport d'arrivée : ");
                    scanf("%s", voyage.aeroport_arrive);
                    break;
                case 5:
                    printf("Nouvelle date (jour mois année) : ");
                    scanf("%d %d %d", &voyage.date_voyage.jour, &voyage.date_voyage.mois, &voyage.date_voyage.annee);
                    break;
                case 6:
                    printf("Nouvelle heure de départ (heure minute) : ");
                    scanf("%d %d", &voyage.heure_depart.heure, &voyage.heure_depart.minute);
                    break;
                case 7:
                    printf("Nouvelle heure d'arrivée (heure minute) : ");
                    scanf("%d %d", &voyage.heure_arrivee.heure, &voyage.heure_arrivee.minute);
                    break;
                case 8:
                    printf("Nouveau nombre de places : ");
                    scanf("%d", &voyage.nb_place);
                    break;
                case 9:
                    printf("Nouvelle compagnie : ");
                    scanf("%s", voyage.compagnie);
                    break;
                case 10:
                    printf("Nouveau prix(MAD) : ");
                    scanf("%d", &voyage.prix);
                    break;
                case 11:
                    printf("Nouvelle classe de vol : ");
                    scanf("%s", voyage.classe);
                    break;
                case 12:
                    printf("Nouvelle durée du vol (heure minute) : ");
                    scanf("%d %d", &voyage.duree_vol.heure, &voyage.duree_vol.minute);
                    break;
                case 0:
                    break;
                default:
                    printf("Choix invalide!\n");
                    break;
            }

            // Remet le curseur à la position de ce voyage dans le fichier
            fseek(file, -sizeof(VoyageExterne), SEEK_CUR);
            fwrite(&voyage, sizeof(VoyageExterne), 1, file);

            }while (choix != 0);
            found = 1;
            printf("Informations du voyage externe modifiées avec succès.\n");
            break;
        }
    }

    if (!found) {
        printf("Voyage externe avec l'ID %s non trouvé.\n", id);
    }

    fclose(file);
}

// Fonction principale pour gérer la modification de voyage

void modifierVoyage(){
     char c;
    do{
        printf("\nLa ligne que vous voulez modifier:\n");
        printf("1. Interne\n");
        printf("2. Externe\n");
        printf("3. Annuller\n");
        printf("Entrez votre choix: ");
        scanf("%d",&c);
        switch (c)
                {
                case 1:{
                    modifierLigneInterne();
                    break;
                }
                case 2:{
                    modifierLigneExterne();
                    break;
                }

               case 3:
                    break;

                default:
                     printf("Choix invalide! Veuillez réessayer.\n");
                     break;
                }



    }while(c!=3);

}


FILE* Ouvrir_Fichier(const char *nom_fichier, const char *mode) {
    FILE *fichier = fopen(nom_fichier, mode);
    if (fichier == NULL) {
        fprintf(stderr, "Erreur: Impossible d'ouvrir le fichier %s en mode %s.\n", nom_fichier, mode);
        return NULL;  // Retourne NULL si l'ouverture échoue
    }
    return fichier;
}


void afficherReservations(FILE* fichier) {


    Reservation reservation;
    printf("\n=== Liste des Réservations Externes ===\n");
    printf("%-20s %-15s %-10s %-12s %-20s\n",
           "Nom d'utilisateur", "ID Voyage", "Places", "Date", "Paiement");
    printf("--------------------------------------------------------------\n");

    while (fread(&reservation, sizeof(Reservation), 1, fichier)) {
        printf("%-20s %-15s %-10d %02d/%02d/%04d       %.2f\n",
               reservation.username,
               reservation.voyage_id,
               reservation.nb_places_reservees,
               reservation.date_reservation.jour,
               reservation.date_reservation.mois,
               reservation.date_reservation.annee,
               reservation.montant_paye);
         printf("--------------------------------------------------------------\n");
    }

    fclose(fichier);
}

void ConsulterVoyages(){
    int c;
    do{
        printf("Voulez-vous consulter :\n");
        printf("              1. Reservations Internes ;\n");
        printf("              2. Reservations Externes ;\n");
        printf("              3. Quitter\n");
        printf("Entrer votre choix :");
        scanf("%d",&c);
        switch (c)
                {
                case 1:{
                    FILE *fichier =Ouvrir_Fichier("reservationsInterne.bin","rb");
                    afficherReservations(fichier);
                    break;
                }
                case 2:{
                    FILE *fichier =Ouvrir_Fichier("reservationsExterne.bin","rb");
                    afficherReservations(fichier);
                    break;
                }

               case 3:
                    break;
                }

    }while(c!=3);

}






//partie de statistiques


//statistique sur le nombre de reservation
// Fonction pour obtenir l'année et le mois actuel
void getCurrentYearAndMonth(int* year, int* month) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    *year = tm.tm_year + 1900; // tm_year commence à partir de 1900
    *month = tm.tm_mon + 1;    // tm_mon commence à partir de 0 (janvier)
}

// Fonction pour générer un rapport mensuel des réservations
char* generate_Monthly_Internal_reserv_Report() {
    int year, month;
    getCurrentYearAndMonth(&year, &month);

    // Ouvrir le fichier binaire des réservations
    FILE *binFile = fopen("reservationsInterne.bin", "rb");
    if (!binFile) {
        printf("Erreur : Impossible d'ouvrir reservationsInterne.bin.\n");
        return NULL;  // Retourner NULL en cas d'erreur
    }

    // Lire les réservations depuis le fichier binaire
    Reservation reservations[MAX_RESERVATIONS];
    int numReservations = fread(reservations, sizeof(Reservation), MAX_RESERVATIONS, binFile);
    fclose(binFile);

    // Créer un nom de fichier basé sur l'année et le mois
    static char filename[256];  // Utiliser static pour conserver le nom du fichier après la fonction
    snprintf(filename, sizeof(filename), "reports/Interne/statistique_reservations/reports-mois/%d-%02d_reservations.txt", year, month);

    // Ouvrir le fichier texte pour écrire les résultats
    FILE *txtFile = fopen(filename, "w");
    if (!txtFile) {
        printf("Erreur : Impossible de créer le fichier %s.\n", filename);
        return NULL;  // Retourner NULL en cas d'erreur
    }

    // Initialiser un tableau pour compter les réservations par jour (31 jours max)
    int reservationsPerDay[31] = {0};  // Tableau pour 31 jours

    // Comptabiliser les réservations pour chaque jour du mois
    for (int i = 0; i < numReservations; i++) {
        // Vérifier si la réservation est pour le mois et l'année actuels
        if (reservations[i].date_reservation.mois == month && reservations[i].date_reservation.annee == year) {
            reservationsPerDay[reservations[i].date_reservation.jour - 1] += reservations[i].nb_places_reservees;
        }
    }

    // Écrire les résultats dans le fichier texte (même pour les jours avec 0 réservation)
    for (int day = 0; day < 31; day++) {
        // Écrire le jour et le nombre de réservations, même s'il est à 0
        fprintf(txtFile, "%d %d\n", day + 1, reservationsPerDay[day]);
    }

    fclose(txtFile);
    printf("Le rapport des réservations pour %d-%02d a été généré dans %s\n", year, month, filename);

    return filename;  // Retourner le nom du fichier généré
}

//les reservations eterne
char* generate_Monthly_External_reserv_Report() {
    int year, month;
    getCurrentYearAndMonth(&year, &month);

    // Ouvrir le fichier binaire des réservations externes
    FILE *binFile = fopen("reservationsExterne.bin", "rb");
    if (!binFile) {
        printf("Erreur : Impossible d'ouvrir reservationsExterne.bin.\n");
        return NULL;  // Retourner NULL en cas d'erreur
    }

    // Lire les réservations depuis le fichier binaire
    Reservation reservations[MAX_RESERVATIONS];
    int numReservations = fread(reservations, sizeof(Reservation), MAX_RESERVATIONS, binFile);
    fclose(binFile);

    // Créer un nom de fichier basé sur l'année et le mois
    static char filename[256];  // Utiliser static pour conserver le nom du fichier après la fonction
    snprintf(filename, sizeof(filename), "reports/Externe/statistique_reservations/reports-mois/%d-%02d_reservations_externe.txt", year, month);

    // Ouvrir le fichier texte pour écrire les résultats
    FILE *txtFile = fopen(filename, "w");
    if (!txtFile) {
        printf("Erreur : Impossible de créer le fichier %s.\n", filename);
        return NULL;  // Retourner NULL en cas d'erreur
    }

    // Initialiser un tableau pour compter les réservations par jour (31 jours max)
    int reservationsPerDay[31] = {0};  // Tableau pour 31 jours

    // Comptabiliser les réservations pour chaque jour du mois
    for (int i = 0; i < numReservations; i++) {
        // Vérifier si la réservation est pour le mois et l'année actuels
        if (reservations[i].date_reservation.mois == month && reservations[i].date_reservation.annee == year) {
            reservationsPerDay[reservations[i].date_reservation.jour - 1] += reservations[i].nb_places_reservees;
        }
    }

    // Écrire les résultats dans le fichier texte (même pour les jours avec 0 réservation)
    for (int day = 0; day < 31; day++) {
        fprintf(txtFile, "%d %d\n", day + 1, reservationsPerDay[day]);  // Écrire le jour et le nombre de réservations
    }

    fclose(txtFile);
    printf("Le rapport des réservations externes pour %d-%02d a été généré dans %s\n", year, month, filename);

    return filename;  // Retourner le nom du fichier généré
}


void ReservationM() {
    // Générer le rapport des réservations internes
    char* filename_interne = generate_Monthly_Internal_reserv_Report();
    // Générer le rapport des réservations externes
    char* filename_externe = generate_Monthly_External_reserv_Report();

    if (filename_interne != NULL && filename_externe != NULL) {
        // Construire la commande pour exécuter le script Python avec les deux fichiers
        char command[512];
        snprintf(command, sizeof(command),
            "\"%s\" graphes/reservationsM.py %s %s",
            "C:\\Users\\DELL\\AppData\\Local\\Programs\\Python\\Python313\\pythonw.exe",
            filename_interne,
            filename_externe
        );

        // Appeler le script Python avec system()
        int result = system(command);

        if (result == 0) {
            printf("Le graphe a été tracé avec succès.\n");
        } else {
            printf("Erreur lors de l'exécution du script Python.\n");
        }
    } else {
        printf("Erreur lors de la génération des rapports ou du tracé.\n");
    }
}





// reservation annuelle
// Fonction pour obtenir l'année actuelle
void getCurrentYear(int* year) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    *year = tm.tm_year + 1900; // tm_year commence à partir de 1900
}

// Fonction pour générer un rapport annuel des réservations
char* generate_Annual_Internal_reserv_Report() {
    int year;
    getCurrentYear(&year);


    const char* folderName = "";

    // Ouvrir le fichier binaire des réservations
    FILE *binFile = fopen("reservationsInterne.bin", "rb");
    if (!binFile) {
        printf("Erreur : Impossible d'ouvrir reservationsInterne.bin.\n");
        return NULL;  // Retourner NULL en cas d'erreur
    }

    // Lire les réservations depuis le fichier binaire
    Reservation reservations[MAX_RESERVATIONS];
    int numReservations = fread(reservations, sizeof(Reservation), MAX_RESERVATIONS, binFile);
    fclose(binFile);

    // Créer un nom de fichier basé sur l'année
    static char filename[256];  // Utiliser static pour conserver le nom du fichier après la fonction
    snprintf(filename, sizeof(filename), "reports/Interne/statistique_reservations/reports-anne/%d_annual_reservations.txt", year);

    // Ouvrir le fichier texte pour écrire les résultats
    FILE *txtFile = fopen(filename, "w");
    if (!txtFile) {
        printf("Erreur : Impossible de créer le fichier %s.\n", filename);
        return NULL;  // Retourner NULL en cas d'erreur
    }

    // Initialiser un tableau pour compter les réservations par mois (12 mois)
    int reservationsPerMonth[12] = {0};  // Tableau pour 12 mois

    // Comptabiliser les réservations pour chaque mois de l'année
    for (int i = 0; i < numReservations; i++) {
        if (reservations[i].date_reservation.annee == year) {
            reservationsPerMonth[reservations[i].date_reservation.mois - 1] += reservations[i].nb_places_reservees;
        }
    }

    // Écrire les résultats dans le fichier texte (même pour les mois avec 0 réservation)
    for (int month = 0; month < 12; month++) {
        // Écrire le mois et le nombre de réservations, même s'il est à 0
        fprintf(txtFile, "%d %d\n", month + 1, reservationsPerMonth[month]);
    }

    fclose(txtFile);
    printf("Le rapport des réservations pour l'année %d a été généré dans %s\n", year, filename);

    return filename;  // Retourner le nom du fichier généré
}




char* generate_Annual_External_reserv_Report() {
    int year;
    getCurrentYear(&year); // Obtenir l'année actuelle

    // Ouvrir le fichier binaire des réservations externes
    FILE *binFile = fopen("reservationsExterne.bin", "rb");
    if (!binFile) {
        printf("Erreur : Impossible d'ouvrir reservationsExterne.bin.\n");
        return NULL;  // Retourner NULL en cas d'erreur
    }

    // Lire les réservations depuis le fichier binaire
    Reservation reservations[MAX_RESERVATIONS];
    int numReservations = fread(reservations, sizeof(Reservation), MAX_RESERVATIONS, binFile);
    fclose(binFile);

    // Créer un nom de fichier basé sur l'année
    static char filename[256];  // Utiliser static pour conserver le nom du fichier après la fonction
    snprintf(filename, sizeof(filename), "reports/Externe/statistique_reservations/reports-anne/%d_annual_reservations_externe.txt", year);

    // Ouvrir le fichier texte pour écrire les résultats
    FILE *txtFile = fopen(filename, "w");
    if (!txtFile) {
        printf("Erreur : Impossible de creer le fichier %s.\n", filename);
        return NULL;  // Retourner NULL en cas d'erreur
    }

    // Initialiser un tableau pour compter les réservations par mois (12 mois)
    int reservationsPerMonth[12] = {0};  // Tableau pour 12 mois

    // Comptabiliser les réservations pour chaque mois de l'année
    for (int i = 0; i < numReservations; i++) {
        // Vérifier si la réservation est pour l'année actuelle
        if (reservations[i].date_reservation.annee == year) {
            reservationsPerMonth[reservations[i].date_reservation.mois - 1] += reservations[i].nb_places_reservees;
        }
    }

    // Écrire les résultats dans le fichier texte (même pour les mois avec 0 réservation)
    for (int month = 0; month < 12; month++) {
        fprintf(txtFile, "%d %d\n", month + 1, reservationsPerMonth[month]);  // Écrire le mois et le nombre de réservations
    }

    fclose(txtFile);
    printf("Le rapport annuel des réservations externes pour l'année %d a été généré dans %s\n", year, filename);

    return filename;  // Retourner le nom du fichier généré
}


// Fonction principale qui appelle les deux fonctions : Génération du rapport et tracé avec Gnuplot
void ReservationA() {
    // Générer le rapport des réservations internes
    char* filename_interne = generate_Annual_Internal_reserv_Report();
    // Générer le rapport des réservations externes
    char* filename_externe = generate_Annual_External_reserv_Report();

    if (filename_interne != NULL && filename_externe != NULL) {
        // Construire la commande pour exécuter le script Python avec les deux fichiers
        char command[512];
        snprintf(command, sizeof(command),
                 "\"C:\\Users\\DELL\\AppData\\Local\\Programs\\Python\\Python313\\pythonw.exe\" graphes/reservationsA.py %s %s",
                 filename_interne, filename_externe);

        // Appeler le script Python avec system()
        int result = system(command);

        if (result == 0) {
            printf("Le graphe annuel a été tracé avec succès.\n");
        } else {
            printf("Erreur lors de l'exécution du script Python.\n");
        }
    } else {
        printf("Erreur lors de la génération des rapports ou du tracé.\n");
    }
}





void statistiqueReservation(){
    int c;
    do{
            printf("\nReservations:\n");
            printf("            1.Monssuelle \n");
            printf("            2.Annuelle\n");
            printf("Entrez votre choix: ");
            scanf("%d",&c);
            switch (c)
                {
                case 1:
                     ReservationM();
                     break;
                case 2:{
                     ReservationA();

                    break;
                }
               default:
                     printf("Choix invalide! Veuillez réessayer.\n");
                     break;
         }



    }while(c!=2);


}









//stistique sur le revenue
// Fonction pour générer le rapport des revenus mensuels
char* generate_Monthly_Internal_Revenue_Report() {
    int year, month;
    getCurrentYearAndMonth(&year, &month);  // Utilisez getCurrentYearAndMonth() pour obtenir l'année et le mois actuels

    // Ouvrir le fichier binaire des réservations
    FILE *binFile = fopen("reservationsInterne.bin", "rb");
    if (!binFile) {
        printf("Erreur : Impossible d'ouvrir reservationsInterne.bin.\n");
        return NULL;  // Retourner NULL en cas d'erreur
    }

    // Lire les réservations depuis le fichier binaire
    Reservation reservations[MAX_RESERVATIONS];
    int numReservations = fread(reservations, sizeof(Reservation), MAX_RESERVATIONS, binFile);
    fclose(binFile);

    // Créer un nom de fichier basé sur l'année et le mois
    static char filename[256];  // Utiliser static pour conserver le nom du fichier après la fonction
    snprintf(filename, sizeof(filename), "reports/Interne/statistique_revenue/reports-mois/%d-%02d_revenue.txt", year, month);

    // Ouvrir le fichier texte pour écrire les résultats
    FILE *txtFile = fopen(filename, "w");
    if (!txtFile) {
        printf("Erreur : Impossible de créer le fichier %s.\n", filename);
        return NULL;  // Retourner NULL en cas d'erreur
    }

    // Initialiser un tableau pour compter les revenus par jour (31 jours max)
    float revenuePerDay[31] = {0.0};  // Tableau pour 31 jours

    // Comptabiliser les revenus pour chaque jour du mois
    for (int i = 0; i < numReservations; i++) {
        // Vérifier si la réservation est pour le mois et l'année actuels
        if (reservations[i].date_reservation.mois == month && reservations[i].date_reservation.annee == year) {
            revenuePerDay[reservations[i].date_reservation.jour - 1] += reservations[i].montant_paye;  // Ajouter le montant payé
        }
    }

    // Écrire les résultats dans le fichier texte (même pour les jours avec 0 revenu)
    for (int day = 0; day < 31; day++) {
        // Écrire le jour et le revenu, même s'il est à 0
        fprintf(txtFile, "%d %.2f\n", day + 1, revenuePerDay[day]);
    }

    fclose(txtFile);
    printf("Le rapport des revenus pour %d-%02d a été généré dans %s\n", year, month, filename);

    return filename;  // Retourner le nom du fichier généré
}


char* generate_Monthly_External_Revenue_Report() {
    int year, month;
    getCurrentYearAndMonth(&year, &month);  // Récupérer l'année et le mois actuels

    // Ouvrir le fichier binaire des réservations externes
    FILE *binFile = fopen("reservationsExterne.bin", "rb");
    if (!binFile) {
        printf("Erreur : Impossible d'ouvrir reservationsExterne.bin.\n");
        return NULL;  // Retourner NULL en cas d'erreur
    }

    // Lire les réservations depuis le fichier binaire
    Reservation reservations[MAX_RESERVATIONS];
    int numReservations = fread(reservations, sizeof(Reservation), MAX_RESERVATIONS, binFile);
    fclose(binFile);

    // Créer un nom de fichier basé sur l'année et le mois
    static char filename[256];  // Utiliser static pour conserver le nom du fichier après la fonction
    snprintf(filename, sizeof(filename), "reports/Externe/statistique_revenue/reports-mois/%d-%02d_revenue_externe.txt", year, month);

    // Ouvrir le fichier texte pour écrire les résultats
    FILE *txtFile = fopen(filename, "w");
    if (!txtFile) {
        printf("Erreur : Impossible de créer le fichier %s.\n", filename);
        return NULL;  // Retourner NULL en cas d'erreur
    }

    // Initialiser un tableau pour compter les revenus par jour (31 jours max)
    float revenuePerDay[31] = {0.0};  // Tableau pour 31 jours

    // Comptabiliser les revenus pour chaque jour du mois
    for (int i = 0; i < numReservations; i++) {
        if (reservations[i].date_reservation.mois == month && reservations[i].date_reservation.annee == year) {
            revenuePerDay[reservations[i].date_reservation.jour - 1] += reservations[i].montant_paye;  // Ajouter le montant payé
        }
    }

    // Écrire les résultats dans le fichier texte (même pour les jours avec 0 revenu)
    for (int day = 0; day < 31; day++) {
        fprintf(txtFile, "%d %.2f\n", day + 1, revenuePerDay[day]);
    }

    fclose(txtFile);
    printf("Le rapport des revenus externes pour %d-%02d a été généré dans %s\n", year, month, filename);

    return filename;  // Retourner le nom du fichier généré
}

void RevenueM() {
    int year, month;
    getCurrentYearAndMonth(&year, &month);  // Récupérer l'année et le mois actuels

    // Générer le rapport des revenus mensuels internes
    char* reportFileInterne = generate_Monthly_Internal_Revenue_Report();
    // Générer le rapport des revenus mensuels externes
    char* reportFileExterne = generate_Monthly_External_Revenue_Report();

    if (reportFileInterne != NULL && reportFileExterne != NULL) {
        // Construire la commande pour exécuter le script Python avec les deux fichiers
        char command[512];
        snprintf(command, sizeof(command), "C:\\Users\\DELL\\AppData\\Local\\Programs\\Python\\Python313\\pythonw.exe graphes\\revenueM.py %s %s", reportFileInterne, reportFileExterne);

        // Exécuter le script Python
        int result = system(command);

        if (result == 0) {
            printf("Le graphe mensuel des revenus a été tracé avec succès.\n");
        } else {
            printf("Erreur lors de l'exécution du script Python.\n");
        }
    } else {
        printf("Erreur lors de la génération des rapports des revenus mensuels.\n");
    }
}




// Fonction pour générer le rapport des revenus annuels
char* generate_Annual_Internal_Revenue_Report() {
    int year;
    getCurrentYear(&year);  // Utilisez getCurrentYear() pour obtenir l'année actuelle

    // Ouvrir le fichier binaire des réservations
    FILE *binFile = fopen("reservationsInterne.bin", "rb");
    if (!binFile) {
        printf("Erreur : Impossible d'ouvrir reservationsInterne.bin.\n");
        return NULL;  // Retourner NULL en cas d'erreur
    }

    // Lire les réservations depuis le fichier binaire
    Reservation reservations[MAX_RESERVATIONS];
    int numReservations = fread(reservations, sizeof(Reservation), MAX_RESERVATIONS, binFile);
    fclose(binFile);

    // Créer un nom de fichier basé sur l'année
    static char filename[256];  // Utiliser static pour conserver le nom du fichier après la fonction
    snprintf(filename, sizeof(filename), "reports/Interne/statistique_revenue/reports-anne/%d_annual_revenue.txt", year);

    // Ouvrir le fichier texte pour écrire les résultats
    FILE *txtFile = fopen(filename, "w");
    if (!txtFile) {
        printf("Erreur : Impossible de créer le fichier %s.\n", filename);
        return NULL;  // Retourner NULL en cas d'erreur
    }

    // Initialiser un tableau pour compter les revenus par mois (12 mois)
    float revenuePerMonth[12] = {0.0};  // Tableau pour 12 mois

    // Comptabiliser les revenus pour chaque mois de l'année
    for (int i = 0; i < numReservations; i++) {
        if (reservations[i].date_reservation.annee == year) {
            revenuePerMonth[reservations[i].date_reservation.mois - 1] += reservations[i].montant_paye;  // Ajouter le montant payé
        }
    }

    // Écrire les résultats dans le fichier texte (mois et revenu)
    for (int month = 0; month < 12; month++) {
        // Écrire le mois et le revenu, même s'il est à 0
        fprintf(txtFile, "%d %.2f\n", month + 1, revenuePerMonth[month]);
    }

    fclose(txtFile);
    printf("Le rapport des revenus pour l'année %d a été généré dans %s\n", year, filename);

    return filename;  // Retourner le nom du fichier généré
}


// Fonction pour générer le rapport des revenus annuels externes
char* generate_Annual_External_Revenue_Report() {
    int year;
    getCurrentYear(&year);  // Obtenez l'année actuelle

    // Ouvrir le fichier binaire des réservations externes
    FILE *binFile = fopen("reservationsExterne.bin", "rb");
    if (!binFile) {
        printf("Erreur : Impossible d'ouvrir reservationsExterne.bin.\n");
        return NULL;
    }

    // Lire les réservations depuis le fichier binaire
    Reservation reservations[MAX_RESERVATIONS];
    int numReservations = fread(reservations, sizeof(Reservation), MAX_RESERVATIONS, binFile);
    fclose(binFile);

    // Créer un nom de fichier basé sur l'année
    static char filename[256];  // Utiliser static pour conserver le nom du fichier
    snprintf(filename, sizeof(filename), "reports/Externe/statistique_revenue/reports-anne/%d_annual_revenue_externe.txt", year);

    // Ouvrir le fichier texte
    FILE *txtFile = fopen(filename, "w");
    if (!txtFile) {
        printf("Erreur : Impossible de créer le fichier %s.\n", filename);
        return NULL;
    }

    // Initialiser les revenus par mois (12 mois)
    float revenuePerMonth[12] = {0.0};

    // Comptabiliser les revenus pour chaque mois de l'année
    for (int i = 0; i < numReservations; i++) {
        if (reservations[i].date_reservation.annee == year) {
            revenuePerMonth[reservations[i].date_reservation.mois - 1] += reservations[i].montant_paye;
        }
    }

    // Écrire les résultats dans le fichier
    for (int month = 0; month < 12; month++) {
        fprintf(txtFile, "%d %.2f\n", month + 1, revenuePerMonth[month]);
    }

    fclose(txtFile);
    printf("Le rapport des revenus externes pour l'année %d a été généré dans %s\n", year, filename);

    return filename;
}


void RevenueA() {
    int year;
    getCurrentYear(&year);  // Récupérer l'année actuelle

    // Générer les rapports annuels
    char* reportFileInterne = generate_Annual_Internal_Revenue_Report();
    char* reportFileExterne = generate_Annual_External_Revenue_Report();

    if (reportFileInterne != NULL && reportFileExterne != NULL) {
        // Construire la commande pour exécuter le script Python avec les deux fichiers
        char command[512];
        snprintf(command, sizeof(command), "C:\\Users\\DELL\\AppData\\Local\\Programs\\Python\\Python313\\pythonw.exe graphes\\revenueA.py %s %s", reportFileInterne, reportFileExterne);

        // Exécuter le script Python
        int result = system(command);

        if (result == 0) {
            printf("Le graphe annuel des revenus a été tracé avec succès.\n");
        } else {
            printf("Erreur lors de l'exécution du script Python.\n");
        }
    } else {
        printf("Erreur lors de la génération des rapports des revenus annuels.\n");
    }
}






void statistiqueRevenue(){
    int c;
    do{
            printf("\nRevenue:\n");
            printf("            1.Monssuelle \n");
            printf("            2.Annuelle\n");
            printf("Entrez votre choix: ");
            scanf("%d",&c);
            switch (c)
                {
                case 1:
                     RevenueM();
                     break;
                case 2:{
                     RevenueA();
                    break;
                }
               default:
                     printf("Choix invalide! Veuillez réessayer.\n");
                     break;
         }



    }while(c!=2);


}







// menue de statistique ;
void ConsulterStatistique(){
    int c ;
    do{
        printf("voulez-vous voir :\n");
        printf("            1.Le nombre de reservation \n");
        printf("            2.Le revenue \n");
        printf("Entrez votre choix: ");
        scanf("%d",&c);
        switch (c)
                {
                case 1:
                     statistiqueReservation();
                     break;
                case 2:{
                     statistiqueRevenue();
                     break;
                }
               default:
                     printf("Choix invalide! Veuillez réessayer.\n");
                     break;
         }
    }while(c!=2);
}


// Fonction pour ajouter une compagnie
void ajouterCompagnie() {
    Compagnie nouvelleCompagnie;
    Contrat nouveauContrat;

    // Encodage UTF-8 pour afficher correctement les caractères spéciaux
    SetConsoleOutputCP(CP_UTF8);

    // Saisie des informations sur la compagnie
    printf("Entrez le nom de la compagnie: ");
    scanf("%29s", nouvelleCompagnie.nom);

    printf("Entrez le pays d'origine de la compagnie: ");
    scanf("%29s", nouvelleCompagnie.pays);

    printf("Entrez l'année de création de la compagnie: ");
    scanf("%d", &nouvelleCompagnie.annee_creation);

    printf("Entrez le nombre d'avions dans la flotte: ");
    scanf("%d", &nouvelleCompagnie.nb_avions);

    // Saisie des informations sur le contrat
    printf("\nEntrez l'identifiant du contrat: ");
    scanf("%19s", nouveauContrat.id_contrat);

    printf("Entrez la date de début du contrat (dd/mm/yyyy): ");
    scanf("%14s", nouveauContrat.date_debut);

    printf("Entrez la date de fin du contrat (dd/mm/yyyy): ");
    scanf("%14s", nouveauContrat.date_fin);

    printf("Entrez le montant du contrat: ");
    scanf("%f", &nouveauContrat.montant);

    // Ouverture du fichier en mode ajout binaire
    FILE *fichier = fopen(FILENAME, "ab");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Écriture des données dans le fichier
    fwrite(&nouvelleCompagnie, sizeof(Compagnie), 1, fichier);
    fwrite(&nouveauContrat, sizeof(Contrat), 1, fichier);

    fclose(fichier);
    printf("Compagnie et contrat ajoutés avec succès.\n");
}

// Fonction pour supprimer une compagnie
void supprimerCompagnie() {
    char nomCompagnie[30];

    // Saisie du nom de la compagnie à supprimer
    printf("Entrez le nom de la compagnie à supprimer: ");
    scanf("%29s", nomCompagnie);

    FILE *fichier = fopen(FILENAME, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Calcul de la taille du fichier
    fseek(fichier, 0, SEEK_END);
    long taille_fichier = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);

    long nb_compagnies = taille_fichier / (sizeof(Compagnie) + sizeof(Contrat));
    Compagnie compagnie;
    Contrat contrat;
    Compagnie compagnies[100];
    Contrat contrats[100];
    long i = 0;

    // Lecture des données dans des tableaux temporaires
    while (fread(&compagnie, sizeof(Compagnie), 1, fichier)) {
        fread(&contrat, sizeof(Contrat), 1, fichier);
        compagnies[i] = compagnie;
        contrats[i] = contrat;
        i++;
    }

    fclose(fichier);

    // Réouverture du fichier en mode écriture
    fichier = fopen(FILENAME, "wb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier en mode écriture.\n");
        return;
    }

    // Réécriture des données en ignorant la compagnie à supprimer
    int trouve = 0;
    for (i = 0; i < nb_compagnies; i++) {
        if (strcmp(compagnies[i].nom, nomCompagnie) != 0) {
            fwrite(&compagnies[i], sizeof(Compagnie), 1, fichier);
            fwrite(&contrats[i], sizeof(Contrat), 1, fichier);
        } else {
            trouve = 1;
        }
    }

    fclose(fichier);

    if (trouve) {
        printf("La compagnie '%s' a été supprimée.\n", nomCompagnie);
    } else {
        printf("La compagnie '%s' n'a pas été trouvée.\n", nomCompagnie);
    }
}


void afficherCompagnies() {
    FILE *fichier = fopen(FILENAME, "rb");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    Compagnie compagnie;
    Contrat contrat;
    int compteur = 0;

    printf("\nListe des compagnies enregistrées :\n");
    printf("----------------------------------------------------------\n");

    // Lire et afficher chaque compagnie et son contrat
    while (fread(&compagnie, sizeof(Compagnie), 1, fichier)) {
        fread(&contrat, sizeof(Contrat), 1, fichier); // Lire le contrat correspondant
        compteur++;
        printf("Compagnie %d :\n", compteur);
        printf("  Nom              : %s\n", compagnie.nom);
        printf("  Pays d'origine   : %s\n", compagnie.pays);
        printf("  Année de création: %d\n", compagnie.annee_creation);
        printf("  Nombre d'avions  : %d\n", compagnie.nb_avions);
        printf("  Contrat associé :\n");
        printf("    ID Contrat     : %s\n", contrat.id_contrat);
        printf("    Date de début  : %s\n", contrat.date_debut);
        printf("    Date de fin    : %s\n", contrat.date_fin);
        printf("    Montant        : %.2f\n", contrat.montant);
        printf("----------------------------------------------------------\n");
    }

    fclose(fichier);

    if (compteur == 0) {
        printf("Aucune compagnie enregistrée.\n");
    }
}


void informationCompagnie(){
    int c ;
    do{
        printf("\nCompagnie:\n");
        printf("1/ Ajouter Compagnie\n");
        printf("2/ Supprime Compagnie\n");
        printf("3/ affichier listes des compagnies\n");

        scanf("%d",&c);
                switch (c)
                {
                case 1:
                     ajouterCompagnie();
                     break;
                case 2:{
                    supprimerCompagnie();
                    break;
                }
                case 3:
                     afficherCompagnies();
                     break;
                case 4:
                     printf("Retour au programme principal.\n");
                     break;

               default:
                     printf("Choix invalide! Veuillez réessayer.\n");
                     break;

    }
}while(c!=4);
}



//gestion des employes 
// Fonction pour vérifier si l'identifiant existe déjà dans le fichier
int identifiantExiste(const char *nom_fichier, const char *identifiant) {
    FILE *fichier = fopen(nom_fichier, "rb");
    if (fichier == NULL) {
        return 0;  // Le fichier n'existe pas encore, donc aucun employé n'est enregistré
    }

    Employe employe;
    while (fread(&employe, sizeof(Employe), 1, fichier)) {
        if (strcmp(employe.identifiant, identifiant) == 0) {
            fclose(fichier);
            return 1;  // L'identifiant existe déjà
        }
    }

    fclose(fichier);
    return 0;  // L'identifiant est unique
}

// Fonction pour ajouter un employé au système et stocker ses informations dans un fichier
void ajouterEmploye() {
    Employe employe;
    const char *nom_fichier = "employe.bin"; // Le fichier dans lequel les employés sont enregistrés
    
    // Demander les informations à entrer pour l'employé
    printf("Nom de l'employé: ");
    scanf("%49s", employe.nom);

    printf("Prénom de l'employé: ");
    scanf("%49s", employe.prenom);

    printf("Poste de l'employé: ");
    scanf("%49s", employe.poste);

    printf("Ville où travaille l'employé: ");
    scanf("%49s", employe.ville);

    printf("Email de l'employé: ");
    scanf("%99s", employe.email);

    printf("Numéro de téléphone de l'employé: ");
    scanf("%19s", employe.telephone);

    // Vérifier que l'identifiant est unique
    do {
        printf("Identifiant de connexion (unique): ");
        scanf("%29s", employe.identifiant);
        if (identifiantExiste(nom_fichier, employe.identifiant)) {
            printf("Erreur: cet identifiant existe déjà. Veuillez en saisir un autre.\n");
        }
    } while (identifiantExiste(nom_fichier, employe.identifiant));

    printf("Mot de passe: ");
    scanf("%29s", employe.mot_de_passe);

    // Ouvrir le fichier en mode ajout binaire
    FILE *fichier = fopen(nom_fichier, "ab");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return;
    }

    // Écrire les informations de l'employé dans le fichier
    fwrite(&employe, sizeof(Employe), 1, fichier);

    // Fermer le fichier
    fclose(fichier);

    printf("L'employé a été ajouté avec succès.\n");
}

// Fonction pour supprimer un employé du fichier
void supprimerEmploye() {
    char identifiant[30];
    
    // Demander à l'administrateur de saisir l'identifiant de l'employé à supprimer
    printf("Entrez l'identifiant de l'employé à supprimer: ");
    scanf("%29s", identifiant);

    FILE *fichier = fopen("employe.bin", "rb");
    if (fichier == NULL) {
        printf("Le fichier n'existe pas.\n");
        return;
    }

    FILE *tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL) {
        printf("Erreur lors de la création du fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    Employe employe;
    int trouve = 0;

    // Parcourir tous les employés et copier dans le fichier temporaire sauf l'employé à supprimer
    while (fread(&employe, sizeof(Employe), 1, fichier)) {
        if (strcmp(employe.identifiant, identifiant) != 0) {
            fwrite(&employe, sizeof(Employe), 1, tempFile);  // Copier l'employé si l'identifiant ne correspond pas
        } else {
            trouve = 1;  // L'employé a été trouvé et supprimé
        }
    }

    fclose(fichier);
    fclose(tempFile);

    if (!trouve) {
        printf("Aucun employé trouvé avec cet identifiant.\n");
        remove("temp.bin");  // Supprimer le fichier temporaire si aucun employé n'a été trouvé
        return;
    }

    // Remplacer l'ancien fichier par le nouveau fichier sans l'employé supprimé
    remove("employe.bin");  // Supprimer l'ancien fichier
    rename("temp.bin", "employe.bin");  // Renommer le fichier temporaire en fichier original

    printf("L'employé a été supprimé avec succès.\n");
}

void afficherEmployes() {
    FILE *fichier = fopen("employe.bin", "rb");
    if (fichier == NULL) {
        printf("Le fichier n'existe pas.\n");
        return;
    }

    Employe employe;
    int compteur = 0;

    printf("Liste des employés :\n");

    // Parcourir le fichier et afficher les informations de chaque employé
    while (fread(&employe, sizeof(Employe), 1, fichier)) {
        printf("\nEmployé %d:\n", ++compteur);
        printf("Nom: %s\n", employe.nom);
        printf("Prénom: %s\n", employe.prenom);
        printf("Identifiant: %s\n", employe.identifiant);
        printf("Poste: %s\n", employe.poste);
        printf("Ville: %s\n", employe.ville);
        printf("Email: %s\n", employe.email);
        printf("Téléphone: %s\n", employe.telephone);
    }

    fclose(fichier);

    if (compteur == 0) {
        printf("Aucun employé enregistré.\n");
    }
}


// Fonction pour supprimer une réservation dans le fichier
void supprimerReservation(const char *nom_fichier) {
    char username[50], voyage_id[30];
    
    // Demander l'ID de la réservation et le nom d'utilisateur
    printf("Entrez le nom d'utilisateur de la réservation à supprimer : ");
    scanf("%49s", username);
    
    printf("Entrez l'ID de la réservation à supprimer : ");
    scanf("%29s", voyage_id);
    
    // Ouvrir le fichier des réservations en mode lecture binaire
    FILE *fichier = fopen(nom_fichier, "rb");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier des réservations.\n");
        return;
    }
    
    // Ouvrir un fichier temporaire pour écrire les réservations restantes
    FILE *temp_file = fopen("temp.bin", "wb");
    if (temp_file == NULL) {
        printf("Erreur lors de la création du fichier temporaire.\n");
        fclose(fichier);
        return;
    }

    Reservation reservation;
    int found = 0;

    // Parcourir le fichier et écrire les réservations restantes dans le fichier temporaire
    while (fread(&reservation, sizeof(Reservation), 1, fichier)) {
        // Vérifier si l'utilisateur et l'ID de la réservation correspondent
        if (strcmp(reservation.username, username) == 0 && strcmp(reservation.voyage_id, voyage_id) == 0) {
            printf("Réservation trouvée et supprimée.\n");
            found = 1;  // Marquer que la réservation a été trouvée et supprimée
        } else {
            // Si la réservation ne correspond pas, l'écrire dans le fichier temporaire
            fwrite(&reservation, sizeof(Reservation), 1, temp_file);
        }
    }

    // Fermer les fichiers
    fclose(fichier);
    fclose(temp_file);

    // Vérifier si la réservation a été trouvée et supprimée
    if (!found) {
        printf("Aucune réservation trouvée avec cet identifiant et nom d'utilisateur.\n");
        // Supprimer le fichier temporaire s'il n'y a pas eu de suppression
        remove("temp.bin");
        return;
    }

    // Supprimer le fichier original et renommer le fichier temporaire
    remove(nom_fichier);
    rename("temp.bin", nom_fichier);  // Le fichier temporaire devient le fichier principal

    printf("La réservation a été supprimée avec succès.\n");
}


void gestionEmploye(){
    int choix;
    do {
        printf("\nMenu de gestion des employés\n");
        printf("1. Ajouter un employé\n");
        printf("2. Supprimer un employé\n");
        printf("3. Afficher les employés\n");
        printf("4. Quitter\n");
        printf("Choisissez une option: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterEmploye();
                break;
            case 2:
                supprimerEmploye();
                break;
            case 3:
                afficherEmployes();
                break;
            case 4:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide, essayez encore.\n");
        }
    } while (choix != 4);

}

void SupprimerReservations(){
    int c;
    char* nom_fichier;
    do{
        printf("1. Supprimer une réservation Interne\n");
        printf("2. Supprimer une réservation Externe\n");
        printf("3. Quitter\n");
        printf("Choisissez une option: ");
        scanf("%d", &c);

        switch (c) {
            case 1:
                // Fichier pour les réservations internes
                nom_fichier = "reservationsInterne.bin";
                supprimerReservation(nom_fichier);
                break;
            case 2:
                // Fichier pour les réservations externes
                nom_fichier = "reservationsExterne.bin";
                supprimerReservation(nom_fichier);
                break;
            case 3:
                printf("Retour au menu précédent.\n");
                break;
            default:
                printf("Choix invalide, essayez encore.\n");
        }
    } while (c != 3);  // Quitter si c'est 3
}




// Fonction pour afficher le menu de gestion des réservations
void GestionReservations() {
    int choix;

    do {
        printf("\nMenu de Gestion des Réservations\n");
        printf("1. Supprimer une réservation\n");
        printf("2. Afficher toutes les réservations\n");
        printf("3. Quitter\n");
        printf("Choisissez une option: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                SupprimerReservations();
                break;
            case 2:
                ConsulterVoyages();
                break;
            case 3:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide, essayez encore.\n");
        }
    } while (choix != 3);
}



void gestionlignes(){
    int c;
    char *username;
    do{
        printf("1/ Affichier les lignes\n");
        printf("2/ Ajout d'une ligne\n");
        printf("3/ Supprimer d'une ligne\n");
        printf("4/ Modifier une ligne \n");
        printf("5/ Quitter \n");
        scanf("%d",&c);
        switch (c)
        {
        case 1:
            afficherLignes(username);
            break;
        case 2:{
            //ajouter une ligne;
            AjouterLigne();
            break;
        }
        case 3:{
             //supprimer une ligne
             supprimerLigne();
            break;
        }

        case 4:
           //modifier un voyage;
             modifierVoyage();
            break;
        case 5:
            break;
        default:
            printf("choix invalide !\n");
            break;
        }

    }while (c!=5);
    
}
//Menu d'administrateur
void MenuAdministrateur(){
    int c; char *username;
    OffreEmploi offres[100]; // Tableau pouvant contenir jusqu'à 100 offres
    int nbOffres = 0; // Initialisation du compteur à 0
    do{

                printf("\nMenu Administrateur:\n");
                printf("1/ Affichier les lignes\n");
                printf("2/ Ajout d'une ligne\n");
                printf("3/ Supprimer d'une ligne\n");
                printf("4/ Modifier les information de voyage \n");
                printf("5/ Consulter les reservations \n");
                printf("6/ Consulter les Statistiques \n");
                printf("7/ Ajouter un offre de travail \n");
                printf("8/ QUITTER\n");
                printf("Donner votre choix : ");
                scanf("%d",&c);
                switch (c)
                {
                case 1:
                     afficherLignes(username);
                     break;
                case 2:{
                    //ajouter une ligne;
                    AjouterLigne();
                    break;
                }
                case 3:{
                    //supprimer une ligne
                    supprimerLigne();
                     break;
                }

                case 4:
                     //modifier un voyage;
                     modifierVoyage();
                     break;
                case 5:
                     ConsulterVoyages();
                     break;
                case 6:
                     ConsulterStatistique();
                     break;
                case 7:
                    ajouterOffre(offres, &nbOffres);

                case 8:

                     printf("Retour au programme principal.\n");
                     break;

               default:
                     printf("Choix invalide! Veuillez réessayer.\n");
                     break;
         }

            }while(c!=8);
}






















//// partie employee


// Fonction pour vérifier la connexion d'un employé
int loginEmploye() {
    char identifiant[30];
    char mot_de_passe[30];
    int i = 0;
    
    printf("Identifiant: ");
    scanf("%29s", identifiant);

    printf("Mot de passe: ");
    // Utiliser _getch() pour masquer le mot de passe
    while (1) {
        char ch = _getch();  // Lire un caractère sans l'afficher
        if (ch == 13) {  // Si l'utilisateur appuie sur Enter (13 en ASCII)
            mot_de_passe[i] = '\0';  // Terminer la chaîne de caractères
            break;
        } else if (ch == 8 && i > 0) {  // Si c'est la touche Backspace
            printf("\b \b");  // Effacer le dernier caractère affiché
            i--;
        } else {
            mot_de_passe[i] = ch;  // Ajouter le caractère au mot de passe
            i++;
            printf("*");  // Afficher un astérisque pour masquer l'entrée
        }
    }
    printf("\n");

    // Ouvrir le fichier des employés en mode lecture binaire
    FILE *fichier = fopen("employe.bin", "rb");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier des employés.\n");
        return 0;
    }

    Employe employe;
    while (fread(&employe, sizeof(Employe), 1, fichier)) {
        // Vérifier si l'identifiant et le mot de passe correspondent
        if (strcmp(employe.identifiant, identifiant) == 0 && strcmp(employe.mot_de_passe, mot_de_passe) == 0) {
            fclose(fichier);
            printf("Connexion réussie.\n");
            return 1;  // Connexion réussie
        }
    }

    fclose(fichier);
    printf("Identifiant ou mot de passe incorrect.\n");
    return 0;  // Connexion échouée
}



void ReserverVoyageHorsLineInterne(char *username) {
    FILE *fichierVoyages = fopen("voyageInterne.bin", "rb");
    FILE *fichierReservations = fopen("reservationsInterne.bin", "ab"); // Fichier des réservations (ajout binaire)
    if (fichierVoyages == NULL || fichierReservations == NULL) {
        printf("Erreur d'ouverture des fichiers.");
        return;
    }

    char depart[30], arrive[30];
    Date date;
    int nb_places;
    saisirCriteresRecherche(depart, arrive, &date, &nb_places);

    int nb_voyages_disponibles = afficherVoyagesDisponiblesInternes(fichierVoyages, depart, arrive, date, nb_places);
    if (nb_voyages_disponibles == 0) {
        printf("Aucun voyage disponible ne correspond à vos critères.");
        fclose(fichierVoyages);
        fclose(fichierReservations);
        return;
    }

    int choix_voyage = demanderChoixVoyage(nb_voyages_disponibles);
    if (choix_voyage == 0) {
        printf("Réservation annulée.");
        fclose(fichierVoyages);
        fclose(fichierReservations);
        return;
    }

    // Repositionner le fichier à la première position
    rewind(fichierVoyages);
    
    // Récupérer le voyage choisi
    VoyageInterne voyage;
    int index = 1;
    while (fread(&voyage, sizeof(VoyageInterne), 1, fichierVoyages)) {
        if (strcmp(voyage.aeroport_depart, depart) == 0 &&
            strcmp(voyage.aeroport_arrive, arrive) == 0 &&
            voyage.date_voyage.jour == date.jour &&
            voyage.date_voyage.mois == date.mois &&
            voyage.date_voyage.annee == date.annee &&
            voyage.nb_place >= nb_places) {

            if (index == choix_voyage) {
                float montant_totale=voyage.prix * nb_places;
                printf("\nVous avez choisi le voyage : %s\n", voyage.id);
                printf("\nMontant total à payer: %.2f MAD\n", montant_totale);
                
                // Demander la confirmation de la réservation
                char confirmation;
                printf("Confirmez-vous la réservation ? (O/N): ");
                scanf(" %c", &confirmation);

                if (confirmation == 'O' || confirmation == 'o') {
                    // Mettre à jour le nombre de places disponibles
                    voyage.nb_place -= nb_places;
                    
                    // Créer une structure de réservation
                    Reservation nouvelleReservation;
                    strcpy(nouvelleReservation.username, username);
                    strcpy(nouvelleReservation.voyage_id, voyage.id);
                    nouvelleReservation.nb_places_reservees = nb_places;
                    obtenir_date_du_jour(&nouvelleReservation.date_reservation);
                    nouvelleReservation.montant_paye = voyage.prix * nb_places;
                    
                    // Écrire la réservation dans le fichier des réservations
                    fwrite(&nouvelleReservation, sizeof(Reservation), 1, fichierReservations);
                    printf("\nRéservation effectuée avec succès !\n");
                    
                    // Écrire les modifications dans le fichier des voyages
                    FILE *fichierTemp = fopen("temp.bin", "wb");
                    if (fichierTemp == NULL) {
                        printf("Erreur lors de la mise à jour du fichier des voyages.");
                        fclose(fichierVoyages);
                        fclose(fichierReservations);
                        return;
                    }
                    
                    rewind(fichierVoyages);
                    VoyageInterne tempVoyage;
                    while (fread(&tempVoyage, sizeof(VoyageInterne), 1, fichierVoyages)) {
                        if (strcmp(tempVoyage.id, voyage.id) == 0) {
                            fwrite(&voyage, sizeof(VoyageInterne), 1, fichierTemp); // Ecrire le voyage mis à jour
                        } else {
                            fwrite(&tempVoyage, sizeof(VoyageInterne), 1, fichierTemp); // Ecrire les autres voyages
                        }
                    }
                    
                    fclose(fichierTemp);
                    fclose(fichierVoyages);
                    remove("voyagesInterne.bin");
                    rename("temp.bin", "voyagesInterne.bin");
                    fclose(fichierReservations);
                    return;
                } else {
                    printf("\nRéservation annulée.\n");
                    fclose(fichierVoyages);
                    fclose(fichierReservations);
                    return;
                }
            }
            index++;
        }
    }

    printf("Erreur : voyage non trouvé.");
    fclose(fichierVoyages);
    fclose(fichierReservations);
}

// Fonction pour réserver un voyage hors ligne pour les voyages externes
void ReserverVoyageExterneHorsLine(char *username) {
    FILE *fichierVoyages = fopen("voyageExterne.bin", "rb");
    FILE *fichierReservations = fopen("reservationsExterne.bin", "ab"); // Fichier des réservations externes (ajout binaire)
    if (fichierVoyages == NULL || fichierReservations == NULL) {
        printf("Erreur d'ouverture des fichiers.");
        return;
    }

    char pays_depart[30], pays_arrive[30];
    char aeroport_depart[30], aeroport_arrive[30];
    Date date;
    int nb_places;
    
    saisirCriteresRechercheExterne(pays_depart, pays_arrive, aeroport_depart, aeroport_arrive, &date, &nb_places);

    int nb_voyages_disponibles = afficherVoyagesDisponiblesExterne(fichierVoyages, pays_depart, pays_arrive, aeroport_depart, aeroport_arrive, date, nb_places);
    if (nb_voyages_disponibles == 0) {
        printf("Aucun voyage disponible ne correspond à vos critères.");
        fclose(fichierVoyages);
        fclose(fichierReservations);
        return;
    }

    int choix_voyage = demanderChoixVoyage(nb_voyages_disponibles);
    if (choix_voyage == 0) {
        printf("Réservation annulée.");
        fclose(fichierVoyages);
        fclose(fichierReservations);
        return;
    }

    // Repositionner le fichier à la première position
    rewind(fichierVoyages);
    
    // Récupérer le voyage choisi
    VoyageExterne voyage;
    int index = 1;
    while (fread(&voyage, sizeof(VoyageExterne), 1, fichierVoyages)) {
        if (strcmp(voyage.aeroport_depart, aeroport_depart) == 0 &&
            strcmp(voyage.aeroport_arrive, aeroport_arrive) == 0 &&
            strcmp(voyage.pays_depart, pays_depart) == 0 &&
            strcmp(voyage.pays_arrivee, pays_arrive) == 0 &&
            voyage.date_voyage.jour == date.jour &&
            voyage.date_voyage.mois == date.mois &&
            voyage.date_voyage.annee == date.annee &&
            voyage.nb_place >= nb_places) {

            if (index == choix_voyage) {
                printf("\nVous avez choisi le voyage : %s\n", voyage.id);
                printf("\nMontant total à payer: %.2f MAD\n", voyage.prix * nb_places);
                
                // Demander la confirmation de la réservation
                char confirmation;
                printf("Confirmez-vous la réservation ? (O/N): ");
                scanf(" %c", &confirmation);

                if (confirmation == 'O' || confirmation == 'o') {
                    // Mettre à jour le nombre de places disponibles
                    voyage.nb_place -= nb_places;
                    
                    // Créer une structure de réservation
                    Reservation nouvelleReservation;
                    strcpy(nouvelleReservation.username, username);
                    strcpy(nouvelleReservation.voyage_id, voyage.id);
                    nouvelleReservation.nb_places_reservees = nb_places;
                    nouvelleReservation.date_reservation = date;
                    nouvelleReservation.montant_paye = voyage.prix * nb_places;
                    
                    // Écrire la réservation dans le fichier des réservations
                    fwrite(&nouvelleReservation, sizeof(Reservation), 1, fichierReservations);
                    printf("\nRéservation effectuée avec succès !\n");
                    
                    // Écrire les modifications dans le fichier des voyages
                    FILE *fichierTemp = fopen("temp.bin", "wb");
                    if (fichierTemp == NULL) {
                        printf("Erreur lors de la mise à jour du fichier des voyages.");
                        fclose(fichierVoyages);
                        fclose(fichierReservations);
                        return;
                    }
                    
                    rewind(fichierVoyages);
                    VoyageExterne tempVoyage;
                    while (fread(&tempVoyage, sizeof(VoyageExterne), 1, fichierVoyages)) {
                        if (strcmp(tempVoyage.id, voyage.id) == 0) {
                            fwrite(&voyage, sizeof(VoyageExterne), 1, fichierTemp); // Ecrire le voyage mis à jour
                        } else {
                            fwrite(&tempVoyage, sizeof(VoyageExterne), 1, fichierTemp); // Ecrire les autres voyages
                        }
                    }
                    
                    fclose(fichierTemp);
                    fclose(fichierVoyages);
                    remove("voyagesExterne.bin");
                    rename("temp.bin", "voyagesExterne.bin");
                    fclose(fichierReservations);
                    return;
                } else {
                    printf("\nRéservation annulée.\n");
                    fclose(fichierVoyages);
                    fclose(fichierReservations);
                    return;
                }
            }
            index++;
        }
    }

    printf("Erreur : voyage non trouvé.");
    fclose(fichierVoyages);
    fclose(fichierReservations);
}

void ReserverVoyageHorsLine(char *username) {
    int choix;
    do {
        printf("\n===== Menu Principal =====\n");
        printf("1. Réserver un voyage interne\n");
        printf("2. Réserver un voyage externe\n");
        printf("0. Quitter\n");
        printf("Votre choix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ReserverVoyageHorsLineInterne(username);
                break;
            case 2:
                ReserverVoyageExterneHorsLine(username);
                break;
            case 0:
                printf("Au revoir !\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
                break;
        }
    } while (choix != 0);
}


void MenueEmploye() {
    int currentChoice = 0;
    const int NUM_OPTIONS = 4;
    char* options[] = {
        "Lignes",
        "Réservations",
        "Voyages",
        "Déconnexion"
    };
    
    do {
        // Configuration initiale
        system("cls");
        
        // Dessiner le cadre principal
        drawFrame(20, 1, 100, 30);
        
        // Dessiner le logo
        drawLogo();
        
        // Dessiner le séparateur
        drawSeparator(20, 100, 10);
        
        // Titre du menu
        setColor(9);
        gotoxy(20, 12);
        printf("╠═══════════════════════════════════════ ESPACE EMPLOYE ════════════════════════════════════════╣");
        
        // Afficher les options du menu (centrées)
        for(int i = 0; i < NUM_OPTIONS; i++) {
            drawMenuItem(options[i], 60, 15 + i * 2, i == currentChoice);
        }
        printf("\n");
        
        // Navigation
        char key = _getch();
        if(key == 72) { // Flèche haut
            currentChoice = (currentChoice - 1 + NUM_OPTIONS) % NUM_OPTIONS;
        }
        else if(key == 80) { // Flèche bas
            currentChoice = (currentChoice + 1) % NUM_OPTIONS;
        }
        else if(key == 13) { // Touche Entrée
            system("cls");
            
            switch(currentChoice) {
                case 0:
                    gestionlignes();
                    break;
                case 1: {
                    char* username = signUp();
                    ReserverVoyageHorsLine(username);
                    break;
                }
                case 2:
                    ConsulterVoyages();
                    break;
                case 3:
                    system("cls");
                    drawFrame(20, 1, 100, 30);
                    drawLogo();
                    drawSeparator(20, 100, 10);
                    
                    setColor(9);
                    gotoxy(20, 12);
                    printf("╠════════════════════════════════════ AU REVOIR ! ═══════════════════════════════════════╣");
                    
                    setColor(COLOR_ACCENT);
                    gotoxy(50, 15);
                    printf("A bientôt cher(e) employé(e) !");
                    
                    gotoxy(0, 31);
                    Sleep(2000);
                    return;
            }
            system("cls");
        }
    } while(1);
}




















void MenuePrincipal() {
    char* username;
    int loggedIn;
    int currentChoice = 0;
    const int NUM_OPTIONS = 4;
    char* options[] = {
        "Client",
        "Admin",
        "Staff",
        "Quitter"
    };
    
    // Configuration initiale
    system("cls");
    
    while(1) {
        // Dessiner le cadre principal
        drawFrame(20, 1, 100, 30);
        
        // Dessiner le logo
        drawLogo();
        
        // Dessiner le séparateur
        drawSeparator(20, 100, 10);
        
        // Titre du menu
        setColor(9);
        gotoxy(20, 12);
        printf("╠════════════════════════════════════ BIENVENUE DANS AMANLINES ═════════════════════════════════════╣");
        
        // Afficher les options du menu (centrées)
        for(int i = 0; i < NUM_OPTIONS; i++) {
            drawMenuItem(options[i], 60, 15 + i * 2, i == currentChoice);
        }
        printf("\n");
        
        // Navigation
        char key = _getch();
        if(key == 72) { // Flèche haut
            currentChoice = (currentChoice - 1 + NUM_OPTIONS) % NUM_OPTIONS;
        }
        else if(key == 80) { // Flèche bas
            currentChoice = (currentChoice + 1) % NUM_OPTIONS;
        }
        else if(key == 13) { // Touche Entrée
            system("cls");
            
            switch(currentChoice) {
                case 0: { // Utilisateur
                    int userChoice = 0;
                    char* userOptions[] = {"S'inscrire", "Se connecter", "Retour"};
                    const int NUM_USER_OPTIONS = 3;
                    
                    while(1) {
                        drawFrame(20, 1, 100, 30);
                        drawLogo();
                        drawSeparator(20, 100, 10);
                        
                        setColor(9);
                        gotoxy(20, 12);
                        printf("╠═══════════════════════════════════════ ESPACE UTILISATEUR ════════════════════════════════════════╣");
                                
                        for(int i = 0; i < NUM_USER_OPTIONS; i++) {
                            drawMenuItem(userOptions[i], 60, 15 + i * 2, i == userChoice);
                        }
                        printf("\n");
                        
                        key = _getch();
                        if(key == 72) userChoice = (userChoice - 1 + NUM_USER_OPTIONS) % NUM_USER_OPTIONS;
                        else if(key == 80) userChoice = (userChoice + 1) % NUM_USER_OPTIONS;
                        else if(key == 13) {
                            system("cls");
                            switch(userChoice) {
                                case 0:
                                    username = signUp();
                                    if(username != NULL) menuPostConnexion(username);
                                    break;
                                case 1:
                                    username = login();
                                    if(username != NULL) menuPostConnexion(username);
                                    break;
                                case 2:
                                    goto main_menu;
                            }
                            break;
                        }
                        system("cls");
                    }
                    break;
                }
                
                case 1: { // Administrateur
                    int adminChoice = 0;
                    char* adminOptions[] = {"Se connecter", "Retour"};
                    const int NUM_ADMIN_OPTIONS = 2;
                    
                    while(1) {
                        drawFrame(20, 1, 100, 30);
                        drawLogo();
                        drawSeparator(20, 100, 10);
                        
                        setColor(9);
                        gotoxy(20, 12);
                        printf("╠══════════════════════════════════════ ESPACE ADMINISTRATEUR ══════════════════════════════════════╣");
                                
                        for(int i = 0; i < NUM_ADMIN_OPTIONS; i++) {
                            drawMenuItem(adminOptions[i], 60, 15 + i * 2, i == adminChoice);
                        }
                        printf("\n");
                        
                        key = _getch();
                        if(key == 72) adminChoice = (adminChoice - 1 + NUM_ADMIN_OPTIONS) % NUM_ADMIN_OPTIONS;
                        else if(key == 80) adminChoice = (adminChoice + 1) % NUM_ADMIN_OPTIONS;
                        else if(key == 13) {
                            system("cls");
                            switch(adminChoice) {
                                case 0:
                                    loggedIn = loginAdmin();
                                    if(loggedIn) MenuAdministrateur();
                                    break;
                                case 1:
                                    goto main_menu;
                            }
                            break;
                        }
                        system("cls");
                    }
                    break;
                }
                
                case 2: { // Employé
                    int empChoice = 0;
                    char* empOptions[] = {"Se connecter", "Retour"};
                    const int NUM_EMP_OPTIONS = 2;
                    
                    while(1) {
                        drawFrame(20, 1, 100, 30);
                        drawLogo();
                        drawSeparator(20, 100, 10);
                        
                        setColor(9);
                        gotoxy(20, 12);
                        printf("╠══════════════════════════════════════════ ESPACE EMPLOYE ═════════════════════════════════════════╣");
                    
                                
                        for(int i = 0; i < NUM_EMP_OPTIONS; i++) {
                            drawMenuItem(empOptions[i], 60, 15 + i * 2, i == empChoice);
                        }
                        printf("\n");
                        
                        key = _getch();
                        if(key == 72) empChoice = (empChoice - 1 + NUM_EMP_OPTIONS) % NUM_EMP_OPTIONS;
                        else if(key == 80) empChoice = (empChoice + 1) % NUM_EMP_OPTIONS;
                        else if(key == 13) {
                            system("cls");
                            switch(empChoice) {
                                case 0:
                                    loggedIn = loginEmploye();
                                    if(loggedIn) MenueEmploye();
                                    break;
                                case 1:
                                    goto main_menu;
                            }
                            break;
                        }
                        system("cls");
                    }
                    break;
                }
                
                case 3: // Quitter
                    system("cls");
                    drawFrame(20, 1, 100, 30);
                    drawLogo();
                    drawSeparator(20, 100, 10);
                    
                    setColor(9);
                    gotoxy(20, 12);
                    printf("╠════════════════════════════════════════ AU REVOIR ! ═══════════════════════════════════════╣");
                    setColor(COLOR_ACCENT);
                    gotoxy(50, 15);
                    printf("Merci d'avoir utilisé AMANLINES!");
                    
                    gotoxy(0, 31);
                    Sleep(2000);
                    return;
            }
            
            main_menu:
            system("cls");
        }
        system("cls");
    }
}






int main() {
    system("cls");
    SetConsoleOutputCP(CP_UTF8); // UTF-8 pour le support des accents
    MenuePrincipal();
    return 0;
}
