#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define FILE_NAME "students.txt"

typedef struct Student
{
    char course[50];
    char branch[50];
    char roll[30];
    char erp[30];
    char name[100];
    char phone[20];
    struct Student *next;
} Student;

Student *head = NULL;

void banner()
{
    system("cls");

    printf("=========================================================\n");
    printf("      NOIDA INSTITUTE OF ENGINEERING & TECHNOLOGY\n");
    printf("             STUDENT RECORD MANAGEMENT SYSTEM\n");
    printf("=========================================================\n");
}

void clearBuffer()
{
    int c;

    while((c = getchar()) != '\n' && c != EOF);
}

void pauseScreen()
{
    printf("\nPress Enter to continue...");
    clearBuffer();
    getchar();
}

int rollExists(char roll[])
{
    Student *temp = head;

    while(temp != NULL)
    {
        if(strcmp(temp->roll, roll) == 0)
            return 1;

        temp = temp->next;
    }

    return 0;
}

int erpExists(char erp[])
{
    Student *temp = head;

    while(temp != NULL)
    {
        if(strcmp(temp->erp, erp) == 0)
            return 1;

        temp = temp->next;
    }

    return 0;
}

void saveToFile()
{
    if(head == NULL)
    {
        remove(FILE_NAME);
        return;
    }

    FILE *fp = fopen(FILE_NAME, "w");

    if(fp == NULL)
        return;

    Student *temp = head;

    while(temp != NULL)
    {
        fprintf(fp,
                "%s|%s|%s|%s|%s|%s\n",
                temp->course,
                temp->branch,
                temp->roll,
                temp->erp,
                temp->name,
                temp->phone);

        temp = temp->next;
    }

    fclose(fp);
}

void loadFromFile()
{
    FILE *fp = fopen(FILE_NAME, "r");

    if(fp == NULL)
        return;

    while(1)
    {
        Student *newNode =
            (Student *)malloc(sizeof(Student));

        if(fscanf(fp,
                  "%49[^|]|%49[^|]|%29[^|]|%29[^|]|%99[^|]|%19[^\n]\n",
                  newNode->course,
                  newNode->branch,
                  newNode->roll,
                  newNode->erp,
                  newNode->name,
                  newNode->phone) != 6)
        {
            free(newNode);
            break;
        }

        newNode->next = head;
        head = newNode;
    }

    fclose(fp);
}

void selectCourseBranch(char course[],
                        char branch[])
{
    int courseChoice;
    int branchChoice;

    while(1)
    {
        printf("\nSelect Course\n");
        printf("1. B.Tech\n");
        printf("2. BCA\n");
        printf("3. BBA\n");
        printf("4. MBA\n");
        printf("5. MCA\n");

        printf("Choice: ");
        scanf("%d", &courseChoice);

        if(courseChoice == 1)
        {
            strcpy(course, "B.Tech");

            while(1)
            {
                printf("\nSelect Branch\n");

                printf("1. CSE\n");
                printf("2. CSE (AI & ML)\n");
                printf("3. CSE (Data Science)\n");
                printf("4. CSE (Cyber Security)\n");
                printf("5. IT\n");
                printf("6. ECE\n");
                printf("7. Mechanical\n");
                printf("8. Civil\n");

                printf("Choice: ");
                scanf("%d", &branchChoice);

                switch(branchChoice)
                {
                    case 1:
                        strcpy(branch, "CSE");
                        return;

                    case 2:
                        strcpy(branch, "CSE (AI & ML)");
                        return;

                    case 3:
                        strcpy(branch, "CSE (Data Science)");
                        return;

                    case 4:
                        strcpy(branch, "CSE (Cyber Security)");
                        return;

                    case 5:
                        strcpy(branch, "IT");
                        return;

                    case 6:
                        strcpy(branch, "ECE");
                        return;

                    case 7:
                        strcpy(branch, "Mechanical");
                        return;

                    case 8:
                        strcpy(branch, "Civil");
                        return;

                    default:
                        printf("Invalid Choice\n");
                }
            }
        }
        else if(courseChoice == 2)
        {
            strcpy(course,
                   "BCA");

            strcpy(branch,
                   "Computer Applications");

            return;
        }
        else if(courseChoice == 3)
        {
            strcpy(course,
                   "BBA");

            strcpy(branch,
                   "Business Administration");

            return;
        }
        else if(courseChoice == 4)
        {
            strcpy(course,
                   "MBA");

            strcpy(branch,
                   "Management");

            return;
        }
        else if(courseChoice == 5)
        {
            strcpy(course,
                   "MCA");

            strcpy(branch,
                   "Computer Applications");

            return;
        }
        else
        {
            printf("Invalid Choice\n");
        }
    }
}

void addStudent()
{
    Student *newNode =
        (Student *)malloc(sizeof(Student));

    selectCourseBranch(
        newNode->course,
        newNode->branch);

    clearBuffer();

    do
    {
        printf("University Roll No: ");

        fgets(newNode->roll,
              sizeof(newNode->roll),
              stdin);

        newNode->roll[
            strcspn(newNode->roll, "\n")] = '\0';

        if(rollExists(newNode->roll))
        {
            printf("Roll Number already exists!\n");
        }

    } while(rollExists(newNode->roll));

    do
    {
        printf("ERP ID: ");

        fgets(newNode->erp,
              sizeof(newNode->erp),
              stdin);

        newNode->erp[
            strcspn(newNode->erp, "\n")] = '\0';

        if(erpExists(newNode->erp))
        {
            printf("ERP ID already exists!\n");
        }

    } while(erpExists(newNode->erp));

    printf("Name: ");

    fgets(newNode->name,
          sizeof(newNode->name),
          stdin);

    newNode->name[
        strcspn(newNode->name, "\n")] = '\0';

    printf("Phone Number: ");

    fgets(newNode->phone,
          sizeof(newNode->phone),
          stdin);

    newNode->phone[
        strcspn(newNode->phone, "\n")] = '\0';

    newNode->next = head;
    head = newNode;

    saveToFile();

    printf("\nStudent Added Successfully.\n");
}

void displayStudents()
{
    Student *temp = head;

    if(temp == NULL)
    {
        printf("\nNo Records Found.\n");
        return;
    }

    while(temp != NULL)
    {
        printf("\n+------------------------------------------------+\n");

        printf("| Course : %-38s |\n",
               temp->course);

        printf("| Branch : %-38s |\n",
               temp->branch);

        printf("| Roll   : %-38s |\n",
               temp->roll);

        printf("| ERP ID : %-38s |\n",
               temp->erp);

        printf("| Name   : %-38s |\n",
               temp->name);

        printf("| Phone  : %-38s |\n",
               temp->phone);

        printf("+------------------------------------------------+\n");

        temp = temp->next;
    }
}

void searchStudent()
{
    char roll[30];

    clearBuffer();

    printf("Enter Roll Number: ");

    fgets(roll,
          sizeof(roll),
          stdin);

    roll[strcspn(roll, "\n")] = '\0';

    Student *temp = head;

    while(temp != NULL)
    {
        if(strcmp(temp->roll, roll) == 0)
        {
            printf("\nStudent Found!\n");

            printf("Course : %s\n",
                   temp->course);

            printf("Branch : %s\n",
                   temp->branch);

            printf("Roll No: %s\n",
                   temp->roll);

            printf("ERP ID : %s\n",
                   temp->erp);

            printf("Name   : %s\n",
                   temp->name);

            printf("Phone  : %s\n",
                   temp->phone);

            return;
        }

        temp = temp->next;
    }

    printf("\nStudent Not Found.\n");
}

void updateStudent()
{
    char roll[30];

    clearBuffer();

    printf("Enter Roll Number: ");

    fgets(roll,
          sizeof(roll),
          stdin);

    roll[strcspn(roll, "\n")] = '\0';

    Student *temp = head;

    while(temp != NULL)
    {
        if(strcmp(temp->roll, roll) == 0)
        {
            printf("\nUpdating Student...\n");

            selectCourseBranch(
                temp->course,
                temp->branch);

            clearBuffer();

            printf("Enter New Name: ");

            fgets(temp->name,
                  sizeof(temp->name),
                  stdin);

            temp->name[
                strcspn(temp->name, "\n")] = '\0';

            printf("Enter New Phone Number: ");

            fgets(temp->phone,
                  sizeof(temp->phone),
                  stdin);

            temp->phone[
                strcspn(temp->phone, "\n")] = '\0';

            saveToFile();

            printf("\nRecord Updated Successfully.\n");
            return;
        }

        temp = temp->next;
    }

    printf("\nStudent Not Found.\n");
}

void deleteStudent()
{
    char roll[30];

    clearBuffer();

    printf("Enter Roll Number: ");

    fgets(roll,
          sizeof(roll),
          stdin);

    roll[strcspn(roll, "\n")] = '\0';

    Student *temp = head;
    Student *prev = NULL;

    while(temp != NULL)
    {
        if(strcmp(temp->roll, roll) == 0)
        {
            if(prev == NULL)
            {
                head = temp->next;
            }
            else
            {
                prev->next = temp->next;
            }

            free(temp);

            saveToFile();

            printf("\nStudent Deleted Successfully.\n");
            return;
        }

        prev = temp;
        temp = temp->next;
    }

    printf("\nStudent Not Found.\n");
}

void sortStudents()
{
    Student *i;
    Student *j;

    char tempCourse[50];
    char tempBranch[50];
    char tempRoll[30];
    char tempERP[30];
    char tempName[100];
    char tempPhone[20];

    for(i = head; i != NULL; i = i->next)
    {
        for(j = i->next; j != NULL; j = j->next)
        {
            if(strcmp(i->roll, j->roll) > 0)
            {
                strcpy(tempCourse, i->course);
                strcpy(tempBranch, i->branch);
                strcpy(tempRoll, i->roll);
                strcpy(tempERP, i->erp);
                strcpy(tempName, i->name);
                strcpy(tempPhone, i->phone);

                strcpy(i->course, j->course);
                strcpy(i->branch, j->branch);
                strcpy(i->roll, j->roll);
                strcpy(i->erp, j->erp);
                strcpy(i->name, j->name);
                strcpy(i->phone, j->phone);

                strcpy(j->course, tempCourse);
                strcpy(j->branch, tempBranch);
                strcpy(j->roll, tempRoll);
                strcpy(j->erp, tempERP);
                strcpy(j->name, tempName);
                strcpy(j->phone, tempPhone);
            }
        }
    }

    saveToFile();

    printf("\nRecords Sorted Successfully.\n");
}

void deleteAllRecords()
{
    Student *temp;

    while(head != NULL)
    {
        temp = head;
        head = head->next;

        free(temp);
    }

    remove(FILE_NAME);

    printf("\nAll Records Deleted Successfully.\n");
}

int main()
{
    int choice;

    loadFromFile();

    while(1)
    {
        banner();

        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Sort Students\n");
        printf("7. Delete All Records\n");
        printf("8. Exit\n");

        printf("\nEnter Choice: ");

        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addStudent();
                pauseScreen();
                break;

            case 2:
                displayStudents();
                pauseScreen();
                break;

            case 3:
                searchStudent();
                pauseScreen();
                break;

            case 4:
                updateStudent();
                pauseScreen();
                break;

            case 5:
                deleteStudent();
                pauseScreen();
                break;

            case 6:
                sortStudents();
                pauseScreen();
                break;

            case 7:
                deleteAllRecords();
                pauseScreen();
                break;

            case 8:
                printf("\nExiting Program...\n");
                return 0;

            default:
                printf("\nInvalid Choice!\n");
                pauseScreen();
        }
    }

    return 0;
}
