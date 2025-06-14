#include <stdio.h>
#include <string.h>
#define MAX_SUBJECTS 10
#define MAX_SEMESTERS 8
float gradePoints(float marks){
    if(marks >= 85){
        return 4.0;
    }else if(marks >= 80){
        return 3.7;
    }else if(marks >= 75){
        return 3.3;
    }else if(marks >= 70){
        return 3.0;
    }else if(marks >= 65){
        return 2.7;
    }else if(marks >= 61){
        return 2.3;
    }else if(marks >= 58){
        return 2.0;
    }else if(marks >= 55){
        return 1.7;
    }else if(marks >= 50){
        return 1.0;
    }else {
        return 0.0;
    }
}
float calculateGPA(float marks[], float creditHours[], int n){
    float totalGradePoints = 0;
    float totalCredit = 0;
    for(int i =0; i<n; i++){
        float gradepoint = gradePoints(marks[i]);
        totalGradePoints += gradepoint * creditHours[i];
        totalCredit += creditHours[i];
    }
    if(totalCredit == 0){
        return 0;
    }else{
        return totalGradePoints/totalCredit;
    }
}
float calculateCGPA(float gpaList[], int totalsems){
    float total =0;
    for(int i=0; i <totalsems; i++){
        total += gpaList[i];
    }
    if(totalsems > 0){
        return total / totalsems;
    }else{
        return 0;
    }
}

int main() {
    char name[50];
    int choice;

    printf("Welcome to the GPA/CGPA Calculator!\n");
    printf("  --------------------------------------\n");
    printf ("    Follow the below prompts please    \n");
    printf("Please enter your name: ");
    fgets(name, sizeof(name), stdin);

    name[strcspn(name, "\n")] = 0;

    do {
        printf("\n--- Main Menu ---\n");
        printf("1 --> Calculate GPA\n");
        printf("2 --> Calculate CGPA\n");
        printf("0 --> Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            int n;
            float marks[MAX_SUBJECTS];
            float credits[MAX_SUBJECTS];

            do {
                printf("\nEnter number of subjects (1 to %d): ", MAX_SUBJECTS);
                scanf("%d", &n);
                if (n <= 0 || n > MAX_SUBJECTS) {
                    printf("Invalid number of subjects.\n");
                }
            } while (n <= 0 || n > MAX_SUBJECTS);

            for (int i = 0; i < n; i++) {
                do {
                    printf("Enter marks for subject %d (0-100): ", i + 1);
                    scanf("%f", &marks[i]);
                    if (marks[i] < 0 || marks[i] > 100)
                        printf("Marks must be between 0 and 100.\n");
                } while (marks[i] < 0 || marks[i] > 100);

                do {
                    printf("Enter credit hours for subject %d (positive): ", i + 1);
                    scanf("%f", &credits[i]);
                    if (credits[i] <= 0)
                        printf("Credit hours must be positive.\n");
                } while (credits[i] <= 0);
            }

            float gpa = calculateGPA(marks, credits, n);
            printf("\n GPA Calculated: %.2f\n", gpa);

            int save;
            printf("Do you want to save the result? (1 = Yes, 0 = No): ");
            scanf("%d", &save);
            if (save == 1) {
               FILE *fp=fopen("gpa_data.txt","a");
               if (fp==NULL)
               {
                printf("Error opening the file.");
               }
               else{
                fprintf(fp,"Name: %s | GPA: %.2f\n",name,gpa);
                fclose(fp);
               }
            int d;
            printf("Do you want to see the data of gpa?\n(1 = Yes, 0 = No)=");
            scanf("%d",&d);

            if (d==1)
            {
                fp=fopen("gpa_data.txt","r");
                if (fp==NULL)
                {
                    printf("Error reading file.\n");
                }
                
                else {
                        char line[200];
                        printf("\n--- GPA Data ---\n");
                        while (fgets(line, sizeof(line), fp) != NULL) {
                             printf("%s", line);
                        }
                        fclose(fp);
                }
            }
            else if (d==0)
            {
                printf("ok! your data was added successfully!\n");
            }
            else{
                printf("Invalid choice!");
            }
            }

        } else if (choice == 2) {
            int sems;
            float gpaList[MAX_SEMESTERS];

            do {
                printf("\nEnter number of semesters (1 to %d): ", MAX_SEMESTERS);
                scanf("%d", &sems);
                if (sems <= 0 && sems > MAX_SEMESTERS) {
                    printf("Invalid number of semesters.\n");
                }
            } while (sems <= 0 || sems > MAX_SEMESTERS);

            for (int i = 0; i < sems; i++) {
                do {
                    printf("Enter GPA for semester %d (0.0 - 4.0): ", i + 1);
                    scanf("%f", &gpaList[i]);
                    if (gpaList[i] < 0 || gpaList[i] > 4.0)
                        printf("GPA must be between 0.0 and 4.0.\n");
                } while (gpaList[i] < 0 || gpaList[i] > 4.0);
            }

            float cgpa = calculateCGPA(gpaList, sems);
            printf("\n CGPA Calculated: %.2f\n", cgpa);

            int save;
            printf("Do you want to save the result? (1 = Yes, 0 = No): ");
            scanf("%d", &save);
            if (save == 1) {
                FILE *fc=fopen("cgpa_data.txt","a");
                if (fc==NULL)
                {
                    printf("Error opening the file!\n");
                }
                else{
                    printf("File open successfully!\n");
                    fprintf(fc,"NAME : %s | CGPA : %.2f\n",name,cgpa);
                    fclose(fc);
                }
                
            }
            int d;
            printf("Do you want to see the data of cgpa?\n(1 = Yes, 0 = No)=");
            scanf("%d",&d);
            if (d==1)
            {
                FILE *fc=fopen("cgpa_data.txt","r");
                if (fc==NULL)
                {
                    printf("Error reading file.\n");
                }
                
                else {
                        char line[200];
                        printf("\n--- CGPA Data ---\n");
                        while (fgets(line, sizeof(line), fc) != NULL) {
                            printf("%s", line);
                        }
                        fclose(fc);
                }
            }
            else if (d==0)
            {
                printf("ok! your data was added successfully!\n");
            }
            else{
                printf("Invalid choice!");
            }
            }
            

         else if (choice == 0) {
            printf("\n Thank you, %s! Goodbye.\n", name);
        } else {
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 0);

    return 0;
}