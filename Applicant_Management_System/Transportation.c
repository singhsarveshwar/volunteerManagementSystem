#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

enum days_of_week {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};

char* removeDuplicateWords(char sentence[]) {
    char words[100][100], temp[100];
    int i, j, k, n;

    // split the sentence into words
    n = 0;
    for (i = 0; sentence[i] != '\0'; i++) {
        if (sentence[i] == ' ') {
            words[n][k] = '\0';
            n++;
            k = 0;
        }
        else {
            words[n][k] = sentence[i];
            k++;
        }
    }
    words[n][k] = '\0';
    n++;

    // remove duplicate words
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                strcpy(words[j], "");
            }
        }
    }

    // create a new sentence without duplicate words
    char* newSentence = strdup("");
    for (i = 0; i < n; i++) {
        if (strlen(words[i]) > 0) {
            strcat(newSentence, words[i]);
            strcat(newSentence, " ");
        }
    }

    return newSentence;
}


char* delete_word_from_sentence(char* sentence, char* word) {
    char* new_sentence = NULL;
    int sentence_len = strlen(sentence);
    int word_len = strlen(word);
    char* word_start = strstr(sentence, word);
    if (word_start != NULL) {
        int new_sentence_len = sentence_len - word_len + 1; 
        new_sentence = (char*) malloc(sizeof(char) * new_sentence_len);
        strncpy(new_sentence, sentence, word_start - sentence);
        new_sentence[word_start - sentence] = '\0'; 
        strcat(new_sentence, word_start + word_len);
    }
    else {
        new_sentence = strdup(sentence);
    }
    
    return new_sentence;
}

void addApplicant(char *name, char *day, int week) {
    int weekIndex = 0;
    if(strcmp(day, "MONDAY") == 0){
        weekIndex = week*7 + MONDAY;
    }
    else if(strcmp(day, "TUESDAY") == 0){
        weekIndex = week*7 + TUESDAY;
    }
    else if(strcmp(day, "WEDNESDAY") == 0){
        weekIndex = week*7 +WEDNESDAY;
    }
    else if(strcmp(day, "THURSDAY") == 0){
        weekIndex = week*7 + THURSDAY;
    }
    else if(strcmp(day, "FRIDAY") == 0){
        weekIndex = week*7+FRIDAY;
    }
    else if(strcmp(day, "SATURDAY") == 0){
        weekIndex = week*7+SATURDAY;
    }
    else if(strcmp(day, "SUNDAY") == 0){
        weekIndex = SUNDAY  + 7*week;
    }

    if (weekIndex < 0 || weekIndex >= 84) {
        printf("Sorry, %s, week %d does not exist.\n", day, weekIndex);
        return;
    }
    FILE *fp,*temp;
    fp = fopen("records.txt", "r");
    temp = fopen("temp.txt", "w+");
    if (fp == NULL && temp ==NULL) {
        printf("Error opening file\n");
        return;
    }
    char buffer[100];
    
    for (int i = 0; i < 84*3; i++)
    {
        
         
        if(i % 3 == 0)
        {
               fprintf(temp,"%s",fgets(buffer, sizeof(buffer), fp));
               fgets(buffer, sizeof(buffer), fp);
              //  printf("%s",fgets(buffer, sizeof(buffer), fp));
        }
        else if ( i % 3 == 1)
        {
            int a = 0;
            int numberOfHelpers = atoi(buffer);
            char ch[100];
            if (i == (weekIndex*3 +1))
            {
            if (numberOfHelpers <= 0) {
                printf("Sorry, the maximum number of helpers has been reached for %s, week %d.\n", day, week);
                //fclose(fp);
            }
            fprintf(temp, "%d\n", numberOfHelpers-1);
            a = 1;
            }
            if( a == 0){
             fprintf(temp, "%d\n", numberOfHelpers);
            }
            fgets(buffer, sizeof(buffer), fp);
        }
              else
        {
            if (i == (weekIndex*3 +2))
            {
                char* names =(buffer);
                int pos = strcspn(names, "\n"); // find position of newline character
                if (pos < strlen(names)) {
                    names[pos] = '\0'; // replace newline character with null character
                }
                strcat(names, " "); // put space between people
                strcat(names, name);
              ///  printf("%s",names);
                fprintf(temp,"%s\n",names);
            } else {
                fprintf(temp, "%s", buffer); // write the original people line
            }
        }

    }
   
       fclose(fp);
        fclose(temp);
    remove("records.txt");
    rename("temp.txt","records.txt");
}

void deleteApplicant(char *name, char *day, int week) {
    int weekIndex = 0;
    if(strcmp(day, "MONDAY") == 0){
        weekIndex = week*7 + MONDAY;
    }
    else if(strcmp(day, "TUESDAY") == 0){
        weekIndex = week*7 + TUESDAY;
    }
    else if(strcmp(day, "WEDNESDAY") == 0){
        weekIndex = week*7 +WEDNESDAY;
    }
    else if(strcmp(day, "THURSDAY") == 0){
        weekIndex = week*7 + THURSDAY;
    }
    else if(strcmp(day, "FRIDAY") == 0){
        weekIndex = week*7+FRIDAY;
    }
    else if(strcmp(day, "SATURDAY") == 0){
        weekIndex = week*7+SATURDAY;
    }
    else if(strcmp(day, "SUNDAY") == 0){
        weekIndex = SUNDAY  + 7*week;
    }

    if (weekIndex < 0 || weekIndex >= 84) {
        printf("Sorry, %s, week %d does not exist.\n", day, weekIndex);
        return;
    }
    FILE *fp,*temp;
    fp = fopen("records.txt", "r");
    temp = fopen("temp.txt", "w+");
    if (fp == NULL && temp ==NULL) {
        printf("Error opening file\n");
        return;
    }
    char buffer[100];
    
    for (int i = 0; i < 84*3; i++)
    {
        //printf("weekIndex%d  i%d\n",weekIndex,i);
         
        if(i % 3 == 0)
        {
               fprintf(temp,"%s",fgets(buffer, sizeof(buffer), fp));
               fgets(buffer, sizeof(buffer), fp);
              //  printf("%s",fgets(buffer, sizeof(buffer), fp));
        }
        else if ( i % 3 == 1)
        {
            int a = 0;
            int numberOfHelpers = atoi(buffer);
            char ch[100];
            if (i == (weekIndex*3 +1))
            {
            fprintf(temp, "%d\n", numberOfHelpers+1);
            a=1;
            }
            if(a==0)
             fprintf(temp, "%d\n", numberOfHelpers);
            fgets(buffer, sizeof(buffer), fp);
        }
              else
        {
            if (i == (weekIndex*3 +2))
            {
                char* names =(buffer);
                int pos = strcspn(names, "\n"); // find position of newline character
                if (pos < strlen(names)) {
                    names[pos] = '\0'; // replace newline character with null character
                }
                char* new_sentence = delete_word_from_sentence(names, name);
                //printf("%s\n", new_sentence);
                fprintf(temp, "%s\n", new_sentence); 
                free(new_sentence);
            } else {
                fprintf(temp, "%s", buffer); // write the original people line
            }
        }

    }
   
       fclose(fp);
        fclose(temp);
    remove("records.txt");
    rename("temp.txt","records.txt");
}
void print_file_contents(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file '%s'.\n", filename);
        exit(1);
    }
    
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        printf("%c ", ch);
    }
    
    fclose(file);
}
void ApplicantList() {
    FILE *fp,*temp;
    fp = fopen("records.txt", "r");
    temp = fopen("ApplicantList.txt", "w");
    if (fp == NULL || temp == NULL) {
        printf("Error opening file\n");
        return;
    }
    char buffer[100];
    char largeString [10000];
    for (int i = 0; i < 84*3; i++)
    {
        if(i % 3 == 0)
        {
            fgets(buffer, sizeof(buffer), fp);
        }
        else if ( i % 3 == 1)
        {
            fgets(buffer, sizeof(buffer), fp);
        }
        else
        {
            fgets(buffer, sizeof(buffer), fp);
            char* new_sentence1 = delete_word_from_sentence(buffer,"people:");
            char* new_sentence = removeDuplicateWords(new_sentence1);
            fprintf(temp, "%s\n", new_sentence);
            if (new_sentence != NULL) {
                free(new_sentence);
            }
            if (new_sentence1 != NULL) {
                free(new_sentence1);
            }
        }
    }
    fclose(temp);
    fclose(fp);
    print_file_contents("ApplicantList.txt");
}
void initialisingFile(int maximumnumberOfhelper)
{
    char day[10];
    FILE *fp;
    fp = fopen("records.txt", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        return;
    }
    for (int i = 0; i < 84; i++) {
        if (i % 7 == 0) {
            strcpy(day, "MONDAY   ");
        } else if (i % 7 == 1) {
            strcpy(day, "TUESDAY  ");
        } else if (i % 7 == 2) {
            strcpy(day, "WEDNESDAY");
        } else if (i % 7 == 3) {
            strcpy(day, "THURSDAY ");
        } else if (i % 7 == 4) {
            strcpy(day, "FRIDAY   ");
        } else if (i % 7 == 5) {
            strcpy(day, "SATURDAY ");
        } else {
            strcpy(day, "SUNDAY   ");
        }
        fprintf(fp, "%s\n", day);
        fprintf(fp, "%d\n", maximumnumberOfhelper);
        fprintf(fp, "%s\n", "");
    }
   
    fclose(fp);
}
void fillNames()
{
    char* names[] = {
        "Aditya",
        "Arav",
        "Arya",
        "Asha",
        "Deepika",
        "Jaya",
        "Mohan",
        "Neelam",
        "Priya",
    };
   char* days[] = {
        "MONDAY",
        "TUESDAY",
        "WEDNESDAY",
        "THURSDAY",
        "FRIDAY",
        "SATURDAY",
        "SUNDAY"
    };
    for(int i = 0 ; i < 12;i++)
    {
        for(int j = 0 ; j < 9;j++)
        {
            for(int k = 0 ; k < 7 ;k++ )
            {
               addApplicant(names[j],days[k],i);
            }
      
        }
    }
}
void modifyApplicant(char *name, char *day, int week, char *day2, int week2)
{
    deleteApplicant(name,day,week);
    addApplicant(name,day2,week2);
}
int main() 
{
    initialisingFile(10);
    fillNames();
    int choice;
    char name[50], day[20], day2[20];
    int week, week2;

    while(1) {
        printf("\n**********MENU**********\n");
        printf("1. Add an Applicant\n");
        printf("2. Delete an Applicant\n");
        printf("3. Modify an Applicant\n");
        printf("4. Print Applicant List\n");
        printf("5. Exit\n");
        printf("************************\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("\nEnter Name: ");
                scanf("%s", name);
                printf("Enter Day: ");
                scanf("%s", day);
                printf("Enter Week Number: ");
                scanf("%d", &week);
                addApplicant(name, day, week);
                break;
            case 2:
                printf("\nEnter Name: ");
                scanf("%s", name);
                printf("Enter Day: ");
                scanf("%s", day);
                printf("Enter Week Number: ");
                scanf("%d", &week);
                deleteApplicant(name, day, week);
                break;
            case 3:
                printf("\nEnter Name: ");
                scanf("%s", name);
                printf("Enter Current Day: ");
                scanf("%s", day);
                printf("Enter Current Week Number: ");
                scanf("%d", &week);
                printf("Enter New Day: ");
                scanf("%s", day2);
                printf("Enter New Week Number: ");
                scanf("%d", &week2);
                modifyApplicant(name, day, week, day2, week2);
                break;
            case 4:
                ApplicantList();
                break;
            case 5:
                exit(0);
            default:
                printf("\nPlease enter valid choice\n");
        }
    }
    return 0;
}
