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
    while((c=getchar())!='\n' && c!=EOF);
}

int rollExists(char roll[])
{
    Student *t=head;
    while(t)
    {
        if(strcmp(t->roll,roll)==0) return 1;
        t=t->next;
    }
    return 0;
}

int erpExists(char erp[])
{
    Student *t=head;
    while(t)
    {
        if(strcmp(t->erp,erp)==0) return 1;
        t=t->next;
    }
    return 0;
}

void saveToFile()
{
    if(head==NULL)
    {
        remove(FILE_NAME);
        return;
    }

    FILE *fp=fopen(FILE_NAME,"w");
    if(!fp) return;

    Student *t=head;
    while(t)
    {
        fprintf(fp,"%s|%s|%s|%s|%s|%s\n",
        t->course,t->branch,t->roll,t->erp,t->name,t->phone);
        t=t->next;
    }
    fclose(fp);
}

void loadFromFile()
{
    FILE *fp=fopen(FILE_NAME,"r");
    if(!fp) return;

    while(1)
    {
        Student *n=(Student*)malloc(sizeof(Student));

        if(fscanf(fp,"%49[^|]|%49[^|]|%29[^|]|%29[^|]|%99[^|]|%19[^\n]\n",
        n->course,n->branch,n->roll,n->erp,n->name,n->phone)!=6)
        {
            free(n);
            break;
        }

        n->next=head;
        head=n;
    }
    fclose(fp);
}

void selectCourseBranch(char course[], char branch[])
{
    int c,b;

    while(1)
    {
        printf("\nSelect Course\n");
        printf("1. B.Tech\n2. BCA\n3. BBA\n4. MBA\n5. MCA\n");
        printf("Choice: ");
        scanf("%d",&c);

        if(c==1)
        {
            strcpy(course,"B.Tech");

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
                scanf("%d",&b);

                switch(b)
                {
                    case 1:strcpy(branch,"CSE"); return;
                    case 2:strcpy(branch,"CSE (AI & ML)"); return;
                    case 3:strcpy(branch,"CSE (Data Science)"); return;
                    case 4:strcpy(branch,"CSE (Cyber Security)"); return;
                    case 5:strcpy(branch,"IT"); return;
                    case 6:strcpy(branch,"ECE"); return;
                    case 7:strcpy(branch,"Mechanical"); return;
                    case 8:strcpy(branch,"Civil"); return;
                    default: printf("Invalid Choice\n");
                }
            }
        }
        else if(c==2){strcpy(course,"BCA"); strcpy(branch,"Computer Applications"); return;}
        else if(c==3){strcpy(course,"BBA"); strcpy(branch,"Business Administration"); return;}
        else if(c==4){strcpy(course,"MBA"); strcpy(branch,"Management"); return;}
        else if(c==5){strcpy(course,"MCA"); strcpy(branch,"Computer Applications"); return;}
        else printf("Invalid Choice\n");
    }
}

void addStudent()
{
    Student *n=(Student*)malloc(sizeof(Student));

    selectCourseBranch(n->course,n->branch);
    clearBuffer();

    do{
        printf("University Roll No: ");
        fgets(n->roll,sizeof(n->roll),stdin);
        n->roll[strcspn(n->roll,"\n")]=0;
        if(rollExists(n->roll))
            printf("Roll Number already exists!\n");
    }while(rollExists(n->roll));

    do{
        printf("ERP ID: ");
        fgets(n->erp,sizeof(n->erp),stdin);
        n->erp[strcspn(n->erp,"\n")]=0;
        if(erpExists(n->erp))
            printf("ERP ID already exists!\n");
    }while(erpExists(n->erp));

    printf("Name: ");
    fgets(n->name,sizeof(n->name),stdin);
    n->name[strcspn(n->name,"\n")]=0;

    printf("Phone Number: ");
    fgets(n->phone,sizeof(n->phone),stdin);
    n->phone[strcspn(n->phone,"\n")]=0;

    n->next=head;
    head=n;

    saveToFile();
    printf("\nStudent Added Successfully.\n");
}

void displayStudents()
{
    Student *t=head;

    if(!t){ printf("\nNo Records Found.\n"); return; }

    while(t)
    {
        printf("\n-----------------------------\n");
        printf("Course : %s\n",t->course);
        printf("Branch : %s\n",t->branch);
        printf("Roll No: %s\n",t->roll);
        printf("ERP ID : %s\n",t->erp);
        printf("Name   : %s\n",t->name);
        printf("Phone  : %s\n",t->phone);
        t=t->next;
    }
}

void searchStudent()
{
    char roll[30];
    clearBuffer();

    printf("Enter Roll No: ");
    fgets(roll,sizeof(roll),stdin);
    roll[strcspn(roll,"\n")]=0;

    Student *t=head;

    while(t)
    {
        if(strcmp(t->roll,roll)==0)
        {
            printf("\nFound!\n");
            printf("Name: %s\n",t->name);
            printf("Course: %s\n",t->course);
            printf("Branch: %s\n",t->branch);
            printf("ERP ID: %s\n",t->erp);
            printf("Phone: %s\n",t->phone);
            return;
        }
        t=t->next;
    }

    printf("Student Not Found.\n");
}

void deleteStudent()
{
    char roll[30];
    clearBuffer();

    printf("Enter Roll No: ");
    fgets(roll,sizeof(roll),stdin);
    roll[strcspn(roll,"\n")]=0;

    Student *t=head,*p=NULL;

    while(t)
    {
        if(strcmp(t->roll,roll)==0)
        {
            if(p==NULL) head=t->next;
            else p->next=t->next;

            free(t);
            saveToFile();
            printf("Deleted Successfully.\n");
            return;
        }
        p=t;
        t=t->next;
    }

    printf("Student Not Found.\n");
}

void updateStudent()
{
    char roll[30];
    clearBuffer();

    printf("Enter Roll No: ");
    fgets(roll,sizeof(roll),stdin);
    roll[strcspn(roll,"\n")]=0;

    Student *t=head;

    while(t)
    {
        if(strcmp(t->roll,roll)==0)
        {
            selectCourseBranch(t->course,t->branch);
            clearBuffer();

            printf("Name: ");
            fgets(t->name,sizeof(t->name),stdin);
            t->name[strcspn(t->name,"\n")]=0;

            printf("Phone: ");
            fgets(t->phone,sizeof(t->phone),stdin);
            t->phone[strcspn(t->phone,"\n")]=0;

            saveToFile();
            printf("Updated Successfully.\n");
            return;
        }
        t=t->next;
    }

    printf("Student Not Found.\n");
}

void sortStudents()
{
    Student *i,*j;

    for(i=head;i;i=i->next)
    {
        for(j=i->next;j;j=j->next)
        {
            if(strcmp(i->roll,j->roll)>0)
            {
                Student temp=*i;

                strcpy(i->course,j->course);
                strcpy(i->branch,j->branch);
                strcpy(i->roll,j->roll);
                strcpy(i->erp,j->erp);
                strcpy(i->name,j->name);
                strcpy(i->phone,j->phone);

                strcpy(j->course,temp.course);
                strcpy(j->branch,temp.branch);
                strcpy(j->roll,temp.roll);
                strcpy(j->erp,temp.erp);
                strcpy(j->name,temp.name);
                strcpy(j->phone,temp.phone);
            }
        }
    }

    saveToFile();
    printf("Sorted Successfully.\n");
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

    printf("\nAll records deleted successfully.\n");
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
        printf("7. Delete all records\n");
        printf("8. Exit\n");
        printf("Enter Choice: ");

        scanf("%d",&choice);

        switch(choice)
        {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: sortStudents(); break;
            case 7: deleteAllRecords(); break;
            case 8: return 0;
            default: printf("Invalid Choice\n");
        }
    }
}
