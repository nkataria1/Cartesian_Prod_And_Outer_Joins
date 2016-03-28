#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Maximum rows and columns */
#define ROW 20
#define COL 20

/* 3-D Array for rows and columns */
char *f1[COL][ROW];
char *f2[COL][ROW];

/* Metadata about number of rows and columns 
 * for the two tables 
 * md[0][0] : number of rows of first table
 * md[0][1] : number of columns of first table
 * md[1][0] : number of rows of second table
 * md[1][1] : number of columns of second table
 */
int md[2][2];

void left_outer_join (char *f1[COL][ROW], char *f2[COL][ROW], int com_col) {
	int i=0, j=0, k=0, m=0, enter = 0;
	printf("Left Outer Join:\n");
	for (i=1;i<md[0][0];i++) {
		for (j=0; j<md[0][1]; j++) {
			printf ("%s ", f1[i][j]);
		}
		enter = 0;
		/* Check if there is a match */
		for (k=1;k<md[1][0];k++) {
			if (!strncmp(f2[k][com_col],f1[i][com_col],(int)strlen(f2[k][com_col]))) {
				enter = 1;
				break;
			}
		}
		for (m=0; m<md[1][1]; m++) {
			if (enter == 1) {
				printf ("%s ", f2[k][m]);
			} else {
				printf("%s ", "(null)");
			}
		}
		printf("\n");
	}
}

void right_outer_join (char *f1[COL][ROW], char *f2[COL][ROW], int com_col) {
	int i=0, j=0, k=0, m=0, enter = 0;

	printf("Right Outer Join:\n");
	for (i=1;i<md[1][0];i++) {
		enter = 0;
		/* Check if there is a match */
		for (k=1;k<md[0][0];k++) {
			if (!strncmp(f2[i][com_col],f1[k][com_col],(int)strlen(f2[i][com_col]))) {
				enter = 1;
				break;
			}
		}
		for (m=0; m<md[0][1]; m++) {
			if (enter == 1) {
				printf ("%s ", f1[k][m]);
			} else {
				printf("%s ", "(null)");
			}	
		}
		for (j=0; j<md[1][1]; j++) {
			printf ("%s ", f2[i][j]);
		}
		printf("\n");
	}
}

void full_outer_join (char *f1[COL][ROW], char *f2[COL][ROW], int com_col) {
	int i=0, j=0, k=0, m=0, enter = 0;
	printf("Full Outer Join:\n");

	/* Print all attributes from first row 
	 * as well as the matching ones 
	 */ 
	for (i=1;i<md[0][0];i++) {
		for (j=0; j<md[0][1]; j++) {
			printf ("%s ", f1[i][j]);
		}
		enter = 0;
		/* Check if there is a match */
		for (k=1;k<md[1][0];k++) {
			//printf("Comparing %s %s %d %d\n", f2[k][0], f1[i][0], strlen(f2[k][0]), strlen(f1[i][0]));
			if (!strncmp(f2[k][com_col],f1[i][com_col],(int)strlen(f2[k][com_col]))) {
				enter = 1;
				break;
			}
		}
		for (m=0; m<md[1][1]; m++) {
			if (enter == 1) {
				printf ("%s ", f2[k][m]);
			} else {
				printf("%s ", "(null)");
			}
		}
		printf("\n");
	}

	/* We have printed attributes with matching rows 
	 * in the first loop, Here we print rest of the 
	 * elements from second table.
	 */ 
	for (i=1;i<md[1][0];i++) {
		enter = 0;
		/* Check if there is a match */
		for (k=1;k<md[0][0];k++) {
			if (!strncmp(f2[i][com_col],f1[k][com_col],(int)strlen(f2[i][com_col]))) {
				enter = 1;
				break;
			}
		}
		for (m=0; m<md[0][1]; m++) {
			if (enter) {
				break;
			} else {
				printf("%s ", "(null)");
			}	
		}
		for (j=0; j<md[1][1]; j++) {
			if (!enter) {
				printf ("%s ", f2[i][j]);
			}
		}
		if (!enter)
			printf("\n");
	}
}

void natural_join (char *f1[COL][ROW], char *f2[COL][ROW], int com_col) {
	int i=0, j=0, k=0, m=0, enter = 0;
	printf("Natural Join:\n");
	for (i=1;i<md[1][0];i++) {
		enter = 0;
		/* Check if there is a match */
		for (k=1;k<md[0][0];k++) {
			if (!strncmp(f2[i][com_col],f1[k][com_col],(int)strlen(f2[i][com_col]))) {
				enter = 1;
				break;
			}
		}
		for (m=0; m<md[0][1]; m++) {
			if (enter == 1) {
				printf ("%s ", f1[k][m]);
			}
		}
		for (j=0; j<md[1][1]; j++) {
			if (enter) {
				printf ("%s ", f2[i][j]);
			}
		}
		if (enter)
			printf("\n");
	}
}

void cart_prod (char *f1[COL][ROW], char *f2[COL][ROW]) {
	int i=0,j=0,k=0,l=0;

	printf("Cartesian Product:\n");
	for (i=1;i<md[0][0];i++) {
		for (k=1;k<md[1][0];k++) {
			for (j=0;j<md[0][1];j++) {
				printf ("%s ", f1[i][j]);
			}
			for (l=0;l<md[1][1];l++) {
				printf ("%s ", f2[k][l]);
			}
			printf("\n");
		}
	}
}

void populate_tables(FILE *fd1, FILE *fd2) {
	char *elem;
	char temp[100];
	int i=0,j=0;

	/* Populate first table */
	while (fgets(temp, 100, fd1) != NULL) {
		temp[strlen(temp)-1] = '\0';
		elem = strtok(temp, " ");
		j = 0;
		while (elem) {
			f1[i][j] = (char *)calloc(1, strlen(elem)); 
			sprintf(f1[i][j], "%s ", elem);
			j++;
			elem = strtok(NULL, elem);
		}
		i++;
	}
	/* Keep a count of Rows X Column for the table */
	md[0][0] = i;
	md[0][1] = j;

	/* Reinit the values */
	i = 0;
	j = 0;
	/* Populate second table */
	while (fgets(temp, 100, fd2) != NULL) {
		temp[strlen(temp)-1] = '\0';
		elem = strtok(temp, " ");
		j = 0;
		while (elem) {
			f2[i][j] = (char *)calloc(1, strlen(elem)); 
			sprintf(f2[i][j], "%s", elem);
			j++;
			elem = strtok(NULL, elem);
		}
		i++;
	}
	/* Keep a count of Rows X Column for the table */
	md[1][0] = i;
	md[1][1] = j;

	printf("First table:\n");
	for (i=0;i<md[0][0];i++) {
		for (j=0;j<md[0][1];j++) {
			printf("%s ", f1[i][j]);
		}
		printf("\n");
	}
	printf("Second table:\n");
	for (i=0;i<md[1][0];i++) {
		for (j=0;j<md[1][1];j++) {
			printf("%s ", f2[i][j]);
		}
		printf("\n");
	}
}

int main() { 
	int i=0, j=0, com_col = 0;
	FILE *fd1 = fopen("file1", "r+");
	FILE *fd2 = fopen("file2", "r+");
	
	/* Populate the tables */
	populate_tables(fd1, fd2);
	fclose(fd1);
	fclose(fd2);
	
	/* Find the common column on which we can perform join */
	for(i=0;i<md[0][1];i++) {
		for (j=0;j<md[1][1];j++) {
			if (!strncmp(f2[0][i], f2[0][j], strlen(f2[0][i]))) {
				com_col = j;
				goto next;
			}	
		}
	}
next:
	/* Print natural join */
	natural_join (f1, f2, com_col);
	/* Print left outer join on common column */
	left_outer_join(f1,f2,com_col);
	/* Print right outer join on common column */
	right_outer_join(f1,f2,com_col);
	/* Print full outer join on common column */
	full_outer_join(f1,f2,com_col);
	return 0;
}	
