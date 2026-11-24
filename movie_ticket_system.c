#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>

#define MOVIE_FILE "movies.txt"
#define TICKET_FILE "tickets.txt"

struct Movie {
    int movie_id;
    char title[50];
    char genre[30];
    char show_time[15];
    int total_seats;
    int seats_booked;
};

struct Ticket {
    int ticket_id;
    int movie_id;
    char customer_name[50];
    int seat_no;
    char booking_date[15];
};

void mainMenu();
int login();
void addMovie();
void viewMovies();
void sellTicket();
void cancelTicket();
void viewTickets();
int getNextTicketId();

int main() {
    int choice;
    char ch = '0';
    char dec;
    char confirm[3];

    while (1) {
        printf("\n===== MOVIE TICKETING SYSTEM =====\n");
        mainMenu();
        while (1) {
            printf("\nSelect your choice: ");
            if (scanf(" %c", &ch) != 1 || (ch < '1' || ch > '3')) {
                while (getchar() != '\n');
                printf("\nInvalid choice. Please enter a valid option (1, 2, or 3).\n");
                continue;
            }
            break;
        }

        int direct_menu = 1;
        switch (ch) {
            case '1':
                system("cls");
                if (login()) {
                    while (direct_menu) {
                        system("cls");
                        printf("\n===== MOVIE TICKETING SYSTEM =====\n");
                        printf("\n======== ADMIN MENU ========\n");
                        printf("1. Add Movie\n");
                        printf("2. View All Movies\n");
                        printf("3. Sell Ticket\n");
                        printf("4. Cancel Ticket\n");
                        printf("5. View All Tickets Sold\n");
                        printf("6. Return to Main Menu\n");
                        printf("Enter your choice: ");
                        scanf("%d", &choice);
                        switch (choice) {
                            case 1:
                                addMovie();
                                break;
                            case 2:
                                viewMovies();
                                printf("\nPress Enter to return...");
                                getchar();
                                getchar();
                                break;
                            case 3:
                                sellTicket();
                                break;
                            case 4:
                                cancelTicket();
                                break;
                            case 5:
                                viewTickets();
                                printf("\nPress Enter to return...");
                                getchar();
                                getchar();
                                break;
                            case 6:
                                printf("Do you want to return to the main menu? (y/n): ");
                                while (getchar() != '\n');
                                fgets(confirm, sizeof(confirm), stdin);
                                confirm[strcspn(confirm, "\n")] = '\0';
                                if (confirm[0] == 'y' || confirm[0] == 'Y') {
                                    printf("Returning to main menu...\n");
                                    Sleep(1500);
                                    system("cls");
                                    direct_menu = 0;
                                } else {
                                    printf("Staying in the same menu.\n");
                                    Sleep(1500);
                                    system("cls");
                                }
                                break;
                            default:
                                printf("Invalid choice. Try again.\n");
                                Sleep(1500);
                                break;
                        }
                    }
                }
                break;

            case '2':
                while (direct_menu) {
                    system("cls");
                    printf("\n===== MOVIE TICKETING SYSTEM =====\n");
                    printf("\n======== CUSTOMER MENU ========\n");
                    printf("1. View Movies / Shows\n");
                    printf("2. Return to Main Menu\n");
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    switch (choice) {
                        case 1:
                            viewMovies();
                            printf("\nPress Enter to return...");
                            getchar();
                            getchar();
                            break;
                        case 2:
                            printf("Do you want to return to the main menu? (y/n): ");
                            while (getchar() != '\n');
                            fgets(confirm, sizeof(confirm), stdin);
                            confirm[strcspn(confirm, "\n")] = '\0';
                            if (confirm[0] == 'y' || confirm[0] == 'Y') {
                                printf("Returning to main menu...\n");
                                Sleep(1500);
                                system("cls");
                                direct_menu = 0;
                            } else {
                                printf("Staying in the same menu.\n");
                                Sleep(1500);
                                system("cls");
                            }
                            break;
                        default:
                            printf("Invalid choice. Try again.\n");
                            Sleep(1500);
                            break;
                    }
                }
                break;

            case '3':
                system("cls");
                printf("\nAre you sure you want to exit? (Y/N) ");
                scanf(" %c", &dec);
                if (dec == 'Y' || dec == 'y') {
                    printf("\n\nThank you for using the Movie Ticketing System.\n");
                    exit(0);
                } else {
                    printf("\nReturning to Main Menu....\n");
                    Sleep(1500);
                    system("cls");
                }
                break;

            default:
                printf("Invalid choice. Try again.\n");
                Sleep(1500);
                system("cls");
                break;
        }
        ch = '0';
    }
    return 0;
}

// ------------------ MENU FUNCTION ------------------
void mainMenu() {
    printf("\n======== MAIN MENU ========\n\n");
    printf("Please Select the User Type: \n");
    printf("\n\t1: User - Staff (Admin)\n");
    printf("\t2: User - Customer\n");
    printf("\t3: Exit\n");
    printf("\n================================\n");
}

// ------------------ LOGIN FUNCTION ------------------
int login() {
    char username[20], password[20];
    printf("\n--- LOGIN REQUIRED ---\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        printf("Login Successful!\n");
        Sleep(1500);
        return 1;
    } else {
        printf("Invalid Username or Password!\n");
        Sleep(1500);
        return 0;
    }
}

// ------------------ ADD MOVIE ------------------
void addMovie() {
    system("cls");
    FILE *fp = fopen(MOVIE_FILE, "a");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }
    struct Movie m;
    printf("\n---- ADD MOVIE ----\n");
    printf("\nEnter Movie ID: ");
    scanf("%d", &m.movie_id);
    printf("Enter Title: ");
    scanf(" %[^\n]", m.title);
    printf("Enter Genre: ");
    scanf(" %[^\n]", m.genre);
    printf("Enter Show Time (e.g. 05:30 PM): ");
    scanf(" %[^\n]", m.show_time);
    printf("Enter Total Seats: ");
    scanf("%d", &m.total_seats);
    m.seats_booked = 0;

    fprintf(fp, "%d|%s|%s|%s|%d|%d\n", m.movie_id, m.title, m.genre,
            m.show_time, m.total_seats, m.seats_booked);
    fclose(fp);
    printf("Movie added successfully!\n");
    printf("\nReturning to the Admin Menu.\n");
    Sleep(1500);
}

// ------------------ VIEW ALL MOVIES ------------------
void viewMovies() {
    system("cls");
    FILE *fp = fopen(MOVIE_FILE, "r");
    if (!fp) {
        printf("Movies file not found!\n");
        return;
    }
    struct Movie m;
    printf("\n---- LIST OF ALL MOVIES / SHOWS ----\n");
    while (fscanf(fp, "%d|%49[^|]|%29[^|]|%14[^|]|%d|%d\n", &m.movie_id,
                   m.title, m.genre, m.show_time, &m.total_seats,
                   &m.seats_booked) != EOF) {
        int available = m.total_seats - m.seats_booked;
        printf("ID: %d | Title: %s | Genre: %s | Show Time: %s | Seats Available: %d/%d\n",
               m.movie_id, m.title, m.genre, m.show_time, available, m.total_seats);
    }
    fclose(fp);
}

// ------------------ GET NEXT TICKET ID ------------------
int getNextTicketId() {
    FILE *fp = fopen(TICKET_FILE, "r");
    struct Ticket t;
    int maxId = 0;
    if (fp) {
        while (fscanf(fp, "%d|%d|%49[^|]|%d|%14[^\n]\n", &t.ticket_id,
                       &t.movie_id, t.customer_name, &t.seat_no,
                       t.booking_date) != EOF) {
            if (t.ticket_id > maxId) maxId = t.ticket_id;
        }
        fclose(fp);
    }
    return maxId + 1;
}

// ------------------ SELL TICKET ------------------
void sellTicket() {
    system("cls");
    int id;
    printf("\n---- SELL TICKET ----\n");
    printf("Enter Movie ID: ");
    scanf("%d", &id);

    FILE *fp = fopen(MOVIE_FILE, "r");
    FILE *temp = fopen("temp.txt", "w");
    if (!fp || !temp) {
        printf("Movies file not found!\n");
        return;
    }

    struct Movie m;
    int found = 0;
    int assignedSeat = -1;

    while (fscanf(fp, "%d|%49[^|]|%29[^|]|%14[^|]|%d|%d\n", &m.movie_id,
                   m.title, m.genre, m.show_time, &m.total_seats,
                   &m.seats_booked) != EOF) {
        if (m.movie_id == id && !found) {
            if (m.seats_booked < m.total_seats) {
                m.seats_booked++;
                assignedSeat = m.seats_booked;
                found = 1;
            } else {
                found = -1;
            }
        }
        fprintf(temp, "%d|%s|%s|%s|%d|%d\n", m.movie_id, m.title, m.genre,
                m.show_time, m.total_seats, m.seats_booked);
    }
    fclose(fp);
    fclose(temp);
    remove(MOVIE_FILE);
    rename("temp.txt", MOVIE_FILE);

    if (found == 1) {
        struct Ticket t;
        t.ticket_id = getNextTicketId();
        t.movie_id = id;
        printf("Enter Customer Name: ");
        scanf(" %[^\n]", t.customer_name);
        t.seat_no = assignedSeat;
        printf("Enter Booking Date (dd/mm/yyyy): ");
        scanf("%s", t.booking_date);

        FILE *tf = fopen(TICKET_FILE, "a");
        fprintf(tf, "%d|%d|%s|%d|%s\n", t.ticket_id, t.movie_id,
                t.customer_name, t.seat_no, t.booking_date);
        fclose(tf);

        printf("\nTicket booked successfully! Ticket ID: %d, Seat No: %d\n",
               t.ticket_id, t.seat_no);
        printf("Returning to the Admin Menu.\n");
        Sleep(1500);
    } else if (found == -1) {
        printf("Sorry, all seats for this show are already booked!\n");
        Sleep(1500);
    } else {
        printf("Movie not found!\n");
        Sleep(1500);
    }
}

// ------------------ CANCEL TICKET ------------------
void cancelTicket() {
    system("cls");
    int id;
    printf("\n---- CANCEL TICKET ----\n");
    printf("Enter Ticket ID to cancel: ");
    scanf("%d", &id);

    FILE *fp = fopen(TICKET_FILE, "r");
    FILE *temp = fopen("ttemp.txt", "w");
    if (!fp || !temp) {
        printf("Tickets file not found!\n");
        return;
    }

    struct Ticket t;
    int found = 0;
    int cancelledMovieId = -1;

    while (fscanf(fp, "%d|%d|%49[^|]|%d|%14[^\n]\n", &t.ticket_id,
                   &t.movie_id, t.customer_name, &t.seat_no,
                   t.booking_date) != EOF) {
        if (t.ticket_id == id) {
            found = 1;
            cancelledMovieId = t.movie_id;
            continue; /* skip writing this ticket (it is cancelled) */
        }
        fprintf(temp, "%d|%d|%s|%d|%s\n", t.ticket_id, t.movie_id,
                t.customer_name, t.seat_no, t.booking_date);
    }
    fclose(fp);
    fclose(temp);
    remove(TICKET_FILE);
    rename("ttemp.txt", TICKET_FILE);

    if (found) {
        /* Free up the seat in the movies file */
        FILE *mfp = fopen(MOVIE_FILE, "r");
        FILE *mtemp = fopen("mtemp.txt", "w");
        struct Movie m;
        while (fscanf(mfp, "%d|%49[^|]|%29[^|]|%14[^|]|%d|%d\n", &m.movie_id,
                       m.title, m.genre, m.show_time, &m.total_seats,
                       &m.seats_booked) != EOF) {
            if (m.movie_id == cancelledMovieId && m.seats_booked > 0) {
                m.seats_booked--;
            }
            fprintf(mtemp, "%d|%s|%s|%s|%d|%d\n", m.movie_id, m.title,
                    m.genre, m.show_time, m.total_seats, m.seats_booked);
        }
        fclose(mfp);
        fclose(mtemp);
        remove(MOVIE_FILE);
        rename("mtemp.txt", MOVIE_FILE);

        printf("Ticket cancelled successfully!\n");
        printf("Returning to the Admin Menu.\n");
        Sleep(1500);
    } else {
        printf("Ticket ID not found!\n");
        Sleep(1500);
    }
}

// ------------------ VIEW ALL TICKETS SOLD ------------------
void viewTickets() {
    system("cls");
    FILE *fp = fopen(TICKET_FILE, "r");
    if (!fp) {
        printf("Tickets file not found!\n");
        return;
    }
    struct Ticket t;
    printf("\n---- LIST OF ALL TICKETS SOLD ----\n");
    while (fscanf(fp, "%d|%d|%49[^|]|%d|%14[^\n]\n", &t.ticket_id,
                   &t.movie_id, t.customer_name, &t.seat_no,
                   t.booking_date) != EOF) {
        printf("Ticket ID: %d | Movie ID: %d | Customer: %s | Seat No: %d | Date: %s\n",
               t.ticket_id, t.movie_id, t.customer_name, t.seat_no,
               t.booking_date);
    }
    fclose(fp);
}
