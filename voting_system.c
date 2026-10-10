#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 10
#define MAX_NAME_LENGTH 50
#define DATA_FILE "voting_data.dat"

typedef struct {
    char name[MAX_NAME_LENGTH];
    int votes;
} Candidate;

Candidate candidates[MAX_CANDIDATES];
int candidate_count = 0;

void clear_all_data();

void load_data() {
    FILE *file = fopen(DATA_FILE, "rb");
    if (file) {
        fread(&candidate_count, sizeof(int), 1, file);
        if (candidate_count < 0 || candidate_count > MAX_CANDIDATES) {
            candidate_count = 0;
            fclose(file);
            return;
        }
        fread(candidates, sizeof(Candidate), candidate_count, file);
        fclose(file);
    }
}

void save_data() {
    FILE *file = fopen(DATA_FILE, "wb");
    if (file) {
        fwrite(&candidate_count, sizeof(int), 1, file);
        fwrite(candidates, sizeof(Candidate), candidate_count, file);
        fclose(file);
    }
}

void add_candidate() {
    if (candidate_count >= MAX_CANDIDATES) {
        printf("Maximum number of candidates reached!\n");
        return;
    }

    printf("Enter candidate name: ");
    scanf(" %[^\n]", candidates[candidate_count].name);
    candidates[candidate_count].votes = 0;
    candidate_count++;
    save_data();
    printf("Candidate added successfully!\n");
}

void cast_vote() {
    int i, choice;
    
    if (candidate_count == 0) {
        printf("No candidates registered yet!\n");
        return;
    }

    printf("\n--- Candidates ---\n");
    for (i = 0; i < candidate_count; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }

    printf("Enter your choice (1-%d): ", candidate_count);
    scanf("%d", &choice);

    if (choice >= 1 && choice <= candidate_count) {
        candidates[choice - 1].votes++;
        save_data();
        printf("Vote cast successfully for %s!\n", candidates[choice - 1].name);
    } else {
        printf("Invalid choice!\n");
    }
}

void display_results() {
    int i;
    int total_votes = 0;
    float percentage;
    
    if (candidate_count == 0) {
        printf("No candidates registered yet!\n");
        return;
    }

    printf("\n--- Voting Results ---\n");
    for (i = 0; i < candidate_count; i++) {
        total_votes += candidates[i].votes;
    }

    for (i = 0; i < candidate_count; i++) {
        percentage = total_votes > 0 ? (candidates[i].votes * 100.0) / total_votes : 0;
        printf("%s: %d votes (%.2f%%)\n", candidates[i].name, candidates[i].votes, percentage);
    }
    printf("Total votes: %d\n", total_votes);
}

void reset_voting() {
    int i;
    char confirm;
    
    if (candidate_count == 0) {
        printf("No candidates to reset!\n");
        return;
    }

    printf("Are you sure you want to reset all votes? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        for (i = 0; i < candidate_count; i++) {
            candidates[i].votes = 0;
        }
        save_data();
        printf("All votes have been reset!\n");
    } else {
        printf("Reset cancelled.\n");
    }
}

void clear_all_data() {
    char confirm;
    
    printf("This will delete ALL candidates and votes. Are you sure? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        candidate_count = 0;
        save_data();
        printf("All data has been cleared!\n");
    } else {
        printf("Clear cancelled.\n");
    }
}

void display_menu() {
    printf("\n=== Online Voting System ===\n");
    printf("1. Add Candidate\n");
    printf("2. Cast Vote\n");
    printf("3. View Results\n");
    printf("4. Reset Votes\n");
    printf("5. Clear All Data\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    load_data();

    int choice;
    do {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_candidate();
                break;
            case 2:
                cast_vote();
                break;
            case 3:
                display_results();
                break;
            case 4:
                reset_voting();
                break;
            case 5:
                clear_all_data();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}
