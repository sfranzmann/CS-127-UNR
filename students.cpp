#include <stdio.h>
#define FILE_NAME "students.txt"
#define S 100

int getMenuChoice();

double loadStudents(FILE* fp, int studentNumbers[S], int numberOfCredits[S], double gpas[S]);

void displayStudents(int numberOfStudents, int studentNumbers[S], int numberOfCredits[S], double gpas[S]);

void calcStats(int numberOfStudents, double gpas[S], double *average, double *min, double *max);

double saveStudents(FILE* fp, int numberOfStudents, int studentNumbers[S], int numberOfCredits[S], double gpas[S]);

int main (void){
	FILE* fp;
	int menu, studentNumbers[S], numberOfCredits[S], numberOfStudents;
	double gpas[S], *average, *min, *max;
	menu = 5;
	
	while (menu !=0){
		
		menu = getMenuChoice();
		if (menu == 1){
			fp = fopen(FILE_NAME, "r");
				if (fp != NULL){
					numberOfStudents = loadStudents(fp, studentNumbers, numberOfCredits, gpas);
					fclose(fp);
				} else if (fp == NULL) {
					printf("File could not be found. Try adding students!\n");
				}
		} else if (menu == 2){
			displayStudents(numberOfStudents, studentNumbers, numberOfCredits, gpas);
		} else if (menu == 3) {
			calcStats(numberOfStudents, gpas, average, min, max);
		} else if (menu == 4){
			fp = fopen(FILE_NAME, "w");
			if (fp != NULL) {
				saveStudents(fp, numberOfStudents, studentNumbers, numberOfCredits, gpas);
				fclose(fp);
			} else if(fp == NULL) {
				printf("File could not be found. Try adding students!\n");
			}
			
		} else if (menu == 0){
			return 0;
		}
	}
}

//function definitions
int getMenuChoice()
{

	int choice;
	printf("***STUDENT SYSTEM***\n");
	printf("1. Load Students\n");
	printf("2. Display Students\n");
	printf("3. Analyze GPA\n");
	printf("4. Add Students\n");
	printf("0. EXIT\n");
	scanf("%d", &choice);
	return choice;
}
	
double loadStudents(FILE* fp, int studentNumbers[S], int numberOfCredits[S], double gpas[S]){
	int counter = 0;
	int numberOfStudents;
	char space;

	fscanf(fp, "%d%c\n", &numberOfStudents, &space);
	while(!feof(fp)){
		fscanf(fp, "%d%c %d%c %lf\n", &studentNumbers[counter], &space, &numberOfCredits[counter], &space, &gpas[counter]);
		counter++;
	}
	return numberOfStudents;
}

void displayStudents(int numberOfStudents, int studentNumbers[S], int numberOfCredits[S], double gpas[S]){
	int i = 1;	

	printf(" STUDENTS\n");
	printf("==================================================\n");
	printf("||Student ID  |      Credits      |     GPA     ||\n");
	printf("||==============================================||\n");
	while(i < numberOfStudents){
		printf("||------------|-------------------|-------------||\n");
		printf("||   %6d   | %8d          |   %-10.2lf||\n", studentNumbers[i], numberOfCredits[i], gpas[i]);
		i++;
	}
	printf("||------------|-------------------|-------------||\n");
	printf("==================================================\n");
}

void calcStats(int numberOfStudents, double gpas[S], double *average, double *min, double *max){
	double sum = 0;
	int i = 0;

	double fmin = 0;
	double fmax = 0;

	while(i < numberOfStudents){
		sum = sum + gpas[i];

		if (fmin > gpas[i]){
			fmin = gpas[i];
		}

		else if (fmax < gpas[i]){
			fmax = gpas[i];
		}

		i++;
	}

	double faverage = sum / numberOfStudents;

	average = &faverage;
	max = &fmax;
	min = &fmin;

	printf("Average GPA: %.2lf\n", *average);
	printf("Minimum GPA: %.2lf\n", *min);
	printf("Maximum GPA: %.2lf\n", *max);
}

double saveStudents(FILE* fp, int numberOfStudents, int studentNumbers[S], int numberOfCredits[S], double gpas[S]){
	int newStudents, total, x;
	
	printf("How many students are you adding? ");
	scanf("%d", &newStudents);
	
	total = newStudents + numberOfStudents;

	for (x = numberOfStudents; x < total; x++){
		printf("Enter a student number: ");
		scanf("%d", &studentNumbers[x]);
		printf("Enter the number of credits: ");
		scanf("%d", &numberOfCredits[x]);
		printf("Enter a GPA: ");
		scanf("%lf", &gpas[x]);
	}

	fprintf(fp, "%d\n", total);
	for (x = 0; x < total; x++){
		fprintf(fp, "%d, %d, %.4lf\n", studentNumbers[x], numberOfCredits[x], gpas[x]);
	}
	
	return total;
}













