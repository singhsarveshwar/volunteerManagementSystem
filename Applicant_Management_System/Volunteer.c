#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_KEY 1234
#define MSG_SIZE 1024

typedef struct message {
    long msg_type;
    int passenger_count;
} message;
enum days_of_week {
    MONDAY,
    TUESDAY,
    WEDNESDAY,
    THURSDAY,
    FRIDAY,
    SATURDAY,
    SUNDAY
};
void signal_handler(int signum) {
    if (signum == SIGUSR1) {
        printf("Received SIGUSR1 from first bus process\n");
    } else if (signum == SIGUSR2) {
        printf("Received SIGUSR2 from second bus process\n");
    }
}

pid_t bus_process(int pipefd[2], int msgid) {
    pid_t pid = fork();
    if (pid == 0) {  // Child process
        close(pipefd[1]);
        printf("First bus: Ready to board\n");
        kill(getppid(), SIGUSR1);
        char buffer[MSG_SIZE + 1];  // Make sure to allocate enough space for the null character.
        sleep(2);
        int bytes_read = read(pipefd[0], buffer, MSG_SIZE);
        buffer[bytes_read] = '\0';  // Null-terminate the buffer.
        printf("First bus: received %s\n", buffer);
        message msg;
        msg.msg_type = 1;
        int passenger_count = 0;
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n') {
                passenger_count++;
            }
        }
        msg.passenger_count = passenger_count;
        msgsnd(msgid, &msg, sizeof(msg), 0);
        exit(0);
    }
    return pid;
}

pid_t bus_process_02(int pipefd[2], int msgid) {
    pid_t pid = fork();
    if (pid == 0) {  // Child process
        printf("Second bus: sending SIGUSR2 to parent\n");
        kill(getppid(), SIGUSR2);
        char buffer[MSG_SIZE + 1];  // Make sure to allocate enough space for the null character.
        sleep(5);
        int bytes_read = read(pipefd[0], buffer, MSG_SIZE);
        buffer[bytes_read] = '\0';  // Null-terminate the buffer.
        printf("Second bus: received %s\n", buffer);
        message msg;
        msg.msg_type = 1;
        int passenger_count = 0;
        for (int i = 0; i < bytes_read; i++) {
            if (buffer[i] == '\n') {
                passenger_count++;
            }
        }
        msg.passenger_count = passenger_count;
        msgsnd(msgid, &msg, sizeof(msg), 0);
        exit(0);
    }
    return pid;
}
#define MAX_WORDS 100

char** split_into_words(char* sentence) {
    static char* words[MAX_WORDS];
    int i = 0;

    char* word = strtok(sentence, " ");
    while (word != NULL && i < MAX_WORDS) {
        words[i++] = word;
        word = strtok(NULL, " ");
    }

    return words;
}
char** getPeople(int week,char* day)
{
    char* names;
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
        return NULL;
    }
    FILE *fp;
    fp = fopen("records.txt", "r");
    if (fp == NULL) {
        printf("Error opening file\n");
        return NULL;
    }
    char buffer[10000];
    
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
                 names =(buffer);
                int pos = strcspn(names, "\n"); // find position of newline character
                if (pos < strlen(names)) {
                    names[pos] = '\0'; // replace newline character with null character
                }
                

        }

    }
        return (split_into_words(names));
        free(names);
       fclose(fp);
}
int main() {
    int pipefd1[2], pipefd2[2];
    pipe(pipefd1);
    pipe(pipefd2);

    int msgid = msgget(MSG_KEY, 0666 | IPC_CREAT);

    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    pid_t p1 = bus_process(pipefd1, msgid);
    pid_t p2 = bus_process_02(pipefd2, msgid);
    char** passengers = getPeople(0,"MONDAY");
    int num_passengers = 0;
while(passengers[num_passengers] != NULL)
    num_passengers++;

  //  char* passengers[] = {"Alice", "Bob", "Charlie", "Dave", "Eve", "Frank", "Grace", "Heidi","Ballu","Sarveshwar"};
    /* int num_passengers = sizeof(passengers) / sizeof(char*); */
    for (int i = 0; i < num_passengers; i++) {
        char passenger_msg[MSG_SIZE];
        snprintf(passenger_msg, MSG_SIZE, "%s\n", passengers[i]);
        if (i < num_passengers / 2) {
            write(pipefd1[1], passenger_msg, strlen(passenger_msg));
        } else {
            write(pipefd2[1], passenger_msg, strlen(passenger_msg));
        }
    }

    close(pipefd1[1]);  // Close writing end of pipe 1.
    close(pipefd2[1]);  // Close writing end of pipe 2.

    wait(NULL);  // Wait for children to finish.
    wait(NULL);

    // Print passenger counts from message queue.
    message msg;
    msgrcv(msgid, &msg, sizeof(msg), 1, 0);
    printf("Bus 1 transported %d passengers.\n", msg.passenger_count);
    msgrcv(msgid, &msg, sizeof(msg),
1, 0);
printf("Bus 2 transported %d passengers.\n", msg.passenger_count);
msgctl(msgid, IPC_RMID, NULL); // Destroy the message queue.

return 0;
}