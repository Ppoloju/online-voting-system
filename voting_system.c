#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CANDIDATES 10
#define MAX_NAME_LENGTH 50
#define DATA_FILE "voting_data.dat"
#define EXPORT_FILE "voting_results.txt"

typedef struct {
    char name[MAX_NAME_LENGTH];
    int votes;
} Candidate;

Candidate candidates[MAX_CANDIDATES];
int candidate_count = 0;

void clear_all_data();
void edit_candidate();
void delete_candidate();
void view_candidates();
void sort_candidates();
void export_results();
void show_statistics();

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

void view_candidates() {
    int i;

    if (candidate_count == 0) {
        printf("No candidates registered yet!\n");
        return;
    }

    printf("\n--- Registered Candidates ---\n");
    for (i = 0; i < candidate_count; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }
    printf("Total candidates: %d\n", candidate_count);
}

void edit_candidate() {
    int i, choice;

    if (candidate_count == 0) {
        printf("No candidates registered yet!\n");
        return;
    }

    printf("\n--- Edit Candidate ---\n");
    for (i = 0; i < candidate_count; i++) {
        printf("%d. %s\n", i + 1, candidates[i].name);
    }

    printf("Enter candidate number to edit (1-%d): ", candidate_count);
    scanf("%d", &choice);

    if (choice >= 1 && choice <= candidate_count) {
        printf("Current name: %s\n", candidates[choice - 1].name);
        printf("Enter new name: ");
        scanf(" %[^\n]", candidates[choice - 1].name);
        save_data();
        printf("Candidate name updated successfully!\n");
    } else {
        printf("Invalid choice!\n");
    }
}

void delete_candidate() {
    int i, choice, j;
    char confirm;

    if (candidate_count == 0) {
        printf("No candidates registered yet!\n");
        return;
    }

    printf("\n--- Delete Candidate ---\n");
    for (i = 0; i < candidate_count; i++) {
        printf("%d. %s (%d votes)\n", i + 1, candidates[i].name, candidates[i].votes);
    }

    printf("Enter candidate number to delete (1-%d): ", candidate_count);
    scanf("%d", &choice);

    if (choice >= 1 && choice <= candidate_count) {
        printf("Are you sure you want to delete %s? (y/n): ", candidates[choice - 1].name);
        scanf(" %c", &confirm);

        if (confirm == 'y' || confirm == 'Y') {
            for (j = choice - 1; j < candidate_count - 1; j++) {
                strcpy(candidates[j].name, candidates[j + 1].name);
                candidates[j].votes = candidates[j + 1].votes;
            }
            candidate_count--;
            save_data();
            printf("Candidate deleted successfully!\n");
        } else {
            printf("Deletion cancelled.\n");
        }
    } else {
        printf("Invalid choice!\n");
    }
}

void sort_candidates() {
    int i, j;
    Candidate temp;

    if (candidate_count < 2) {
        printf("Need at least 2 candidates to sort!\n");
        return;
    }

    for (i = 0; i < candidate_count - 1; i++) {
        for (j = 0; j < candidate_count - i - 1; j++) {
            if (candidates[j].votes < candidates[j + 1].votes) {
                temp = candidates[j];
                candidates[j] = candidates[j + 1];
                candidates[j + 1] = temp;
            }
        }
    }

    printf("\n--- Candidates Sorted by Votes ---\n");
    for (i = 0; i < candidate_count; i++) {
        printf("%d. %s: %d votes\n", i + 1, candidates[i].name, candidates[i].votes);
    }
}

void export_results() {
    int i;
    int total_votes = 0;
    float percentage;
    FILE *file;

    if (candidate_count == 0) {
        printf("No candidates registered yet!\n");
        return;
    }

    for (i = 0; i < candidate_count; i++) {
        total_votes += candidates[i].votes;
    }

    file = fopen(EXPORT_FILE, "w");
    if (!file) {
        printf("Error creating export file!\n");
        return;
    }

    fprintf(file, "=== Voting Results ===\n\n");
    fprintf(file, "Total Votes: %d\n\n", total_votes);
    fprintf(file, "Candidate Results:\n");
    fprintf(file, "------------------\n");

    for (i = 0; i < candidate_count; i++) {
        percentage = total_votes > 0 ? (candidates[i].votes * 100.0) / total_votes : 0;
        fprintf(file, "%s: %d votes (%.2f%%)\n", candidates[i].name, candidates[i].votes, percentage);
    }

    fclose(file);
    printf("Results exported to %s successfully!\n", EXPORT_FILE);
}

void show_statistics() {
    int i;
    int total_votes = 0;
    int max_votes = 0;
    int min_votes = 0;
    int winner_index = -1;
    float percentage;

    if (candidate_count == 0) {
        printf("No candidates registered yet!\n");
        return;
    }

    for (i = 0; i < candidate_count; i++) {
        total_votes += candidates[i].votes;
        if (candidates[i].votes > max_votes) {
            max_votes = candidates[i].votes;
            winner_index = i;
        }
    }

    min_votes = max_votes;
    for (i = 0; i < candidate_count; i++) {
        if (candidates[i].votes < min_votes) {
            min_votes = candidates[i].votes;
        }
    }

    printf("\n=== Voting Statistics ===\n");
    printf("Total candidates: %d\n", candidate_count);
    printf("Total votes cast: %d\n", total_votes);
    printf("Average votes per candidate: %.2f\n", (float)total_votes / candidate_count);
    printf("Highest vote count: %d\n", max_votes);
    printf("Lowest vote count: %d\n", min_votes);

    if (winner_index != -1 && total_votes > 0) {
        percentage = (candidates[winner_index].votes * 100.0) / total_votes;
        printf("\nCurrent Leader: %s with %d votes (%.2f%%)\n",
               candidates[winner_index].name, candidates[winner_index].votes, percentage);
    }
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
    printf("2. View Candidates\n");
    printf("3. Edit Candidate\n");
    printf("4. Delete Candidate\n");
    printf("5. Cast Vote\n");
    printf("6. View Results\n");
    printf("7. Sort by Votes\n");
    printf("8. Show Statistics\n");
    printf("9. Export Results\n");
    printf("10. Reset Votes\n");
    printf("11. Clear All Data\n");
    printf("12. Exit\n");
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
                view_candidates();
                break;
            case 3:
                edit_candidate();
                break;
            case 4:
                delete_candidate();
                break;
            case 5:
                cast_vote();
                break;
            case 6:
                display_results();
                break;
            case 7:
                sort_candidates();
                break;
            case 8:
                show_statistics();
                break;
            case 9:
                export_results();
                break;
            case 10:
                reset_voting();
                break;
            case 11:
                clear_all_data();
                break;
            case 12:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 12);

    return 0;
}
