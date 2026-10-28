
#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME "students.txt"
#define MAX_STUDENTS 100

struct Student {
    int id;
    char name[50];
    float marks;
};

int loadStudents(struct Student students[]) {
    FILE *file = fopen(FILE_NAME, "r");

    if (file == NULL) {
        return 0;
    }

    int count = 0;

    while (count < MAX_STUDENTS &&
           fscanf(file, "%d %49s %f",
                  &students[count].id,
                  students[count].name,
                  &students[count].marks) == 3) {
        count++;
    }

    fclose(file);
    return count;
}

void addStudent(void) {
    struct Student students[MAX_STUDENTS];
    int count = loadStudents(students);
    struct Student s;

    if (count >= MAX_STUDENTS) {
        printf("Student limit reached!\n");
        return;
    }

    printf("Enter student ID: ");
    if (scanf("%d", &s.id) != 1) {
        printf("Invalid ID.\n");
        while (getchar() != '\n');
        return;
    }

    for (int i = 0; i < count; i++) {
        if (students[i].id == s.id) {
            printf("This student ID already exists!\n");
            return;
        }
    }

    printf("Enter name (one word): ");
    if (scanf("%49s", s.name) != 1) {
        printf("Invalid name.\n");
        return;
    }

    printf("Enter marks (0-100): ");
    if (scanf("%f", &s.marks) != 1 ||
        s.marks < 0 || s.marks > 100) {
        printf("Invalid marks!\n");
        while (getchar() != '\n');
        return;
    }

    FILE *file = fopen(FILE_NAME, "a");

    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fprintf(file, "%d %s %.2f\n", s.id, s.name, s.marks);
    fclose(file);

    printf("Student record saved successfully!\n");
}

void viewStudents(void) {
    struct Student students[MAX_STUDENTS];
    int count = loadStudents(students);

    if (count == 0) {
        printf("No student records found.\n");
        return;
    }

    printf("\n%-10s %-20s %-10s\n", "ID", "Name", "Marks");
    printf("------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-10d %-20s %-10.2f\n",
               students[i].id,
               students[i].name,
               students[i].marks);
    }
}

void searchStudent(void) {
    struct Student students[MAX_STUDENTS];
    int count = loadStudents(students);
    int searchID;

    printf("Enter ID to search: ");
    if (scanf("%d", &searchID) != 1) {
        printf("Invalid ID.\n");
        while (getchar() != '\n');
        return;
    }

    for (int i = 0; i < count; i++) {
        if (students[i].id == searchID) {
            printf("\nStudent found!\n");
            printf("ID: %d\n", students[i].id);
            printf("Name: %s\n", students[i].name);
            printf("Marks: %.2f\n", students[i].marks);
            return;
        }
    }

    printf("Student not found.\n");
}

void showRanking(void) {
    struct Student students[MAX_STUDENTS];
    int count = loadStudents(students);

    if (count == 0) {
        printf("No student records found.\n");
        return;
    }

    /* Sort students by marks in descending order */
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].marks < students[j + 1].marks) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("\n===== STUDENT RANKING =====\n");

    for (int i = 0; i < count; i++) {
        printf("Rank %d: %s (ID: %d) - %.2f marks\n",
               i + 1,
               students[i].name,
               students[i].id,
               students[i].marks);
    }
}

int main(void) {
    int choice;

    do {
        printf("\n===== STUDENT MANAGEMENT =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search by ID\n");
        printf("4. Show Ranking\n");
        printf("5. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                viewStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                showRanking();
                break;
            case 5:
                printf("Program closed.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
