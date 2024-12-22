#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LOGS 100

typedef struct{
    time_t timeStart;
    time_t timeEnd;
    int durationInmin;
    char notes[99];
} sleepLog;

typedef struct {
    sleepLog logs[MAX_LOGS];
    int logCount;
    float sleepTotal; // in hours
    int ageInMonth; // baby's age in months
} babySleep;

// Function declarations
int ageCalculator();
void sleepTracker();
void startSleep();
void endSleep();
void sleepHistory();
void sleepSummary();

int main() {
    int ageInMonths = ageCalculator(); // Calculate child's age in month
    char menu;
    babySleep tracker = {0};

    printf("Menu Options:\n");
    printf("A. Growth Tracker\n");
    printf("B. Vaccine Tracker\n");
    printf("C. Sleep Tracker\n");
    printf("D. Health Database\n");
    printf("Enter your choice: ");
    scanf(" %c", &menu);

    switch (menu) {
        case 'A':
            printf("Growth Tracker is under development.\n");
            break;

        case 'B':
            printf("Vaccine Tracker is under development.\n");
            break;

        case 'C':
            sleepTracker(&tracker); // call the sleep tracker
            break;

        case 'D':
            printf("Health Database is under development.\n");
            break;

        default:
            printf("Invalid Input! Try Again!\n");
    }

    return 0;
}

// Function to calculate child's age in months
int ageCalculator() {
    int dates[2][3]; // Array to store birthdate [0][...] and current date [1][...]

    // Get child's birthdate
    printf("Enter child's birthdate (YYYY MM DD): ");
    scanf("%d %d %d", &dates[0][0], &dates[0][1], &dates[0][2]); // [0][0]=Year, [0][1]=Month, [0][2]=Day

    // Get current date
    time_t t = time(NULL);
    struct tm currentDate = *localtime(&t);

    dates[1][0] = currentDate.tm_year + 1900; // Current Year
    dates[1][1] = currentDate.tm_mon + 1;    // Current Month
    dates[1][2] = currentDate.tm_mday;      // Current Day

    // Calculate age in months
    int ageInYears = dates[1][0] - dates[0][0];
    int ageInMonths = (dates[1][1] - dates[0][1]) + (ageInYears * 12);
    if (dates[1][1] < dates[0][1] || (dates[1][1] == dates[0][1] && dates[1][2] < dates[0][2])) {
        ageInMonths -= 1; // Adjust if birthdate hasn't occurred yet this month
    }

    printf("The child's age is %d months.\n", ageInMonths);
    return ageInMonths;
}

// Sleep Tracker function
void startSleep(babySleep *tracker){
    if(tracker -> logCount >= MAX_LOGS){
        printf("Log is more than its capacity!");
        return;
    }

    sleepLog *session = &tracker -> logs[tracker -> logCount];
    session -> timeStart = time(NULL);

    printf("Shhh! The baby starts to sleep. Monitor: %s\n", ctime(&session->timeStart));
}

void endSleep(babySleep *tracker){
    if(tracker -> logCount >= MAX_LOGS){
        printf("No active sleep sessions needs to be monitored.\n");
        return;
    }

    sleepLog *session = &tracker -> logs[tracker -> logCount];
    session -> timeEnd = time(NULL);

    // calculate the duration in minutes
    session -> durationInmin = (session -> timeEnd - session -> timeStart) / 60;

    // convert from minutes into hours
    tracker->sleepTotal += (float)session->durationInmin / 60.0;

    printf("Baby is now fresh and awake! Duration: %d\n", session->durationInmin);

    tracker -> logCount++;
}

void sleepHistory(babySleep *tracker){
    if (tracker -> logCount == 0){
        printf("No logs or history of baby sleeping.\n");
        return;
    }

    printf("\n==== Baby Sleep History ====\n");
    for(int i = 0; i < tracker -> logCount; i++){
        sleepLog *session = &tracker -> logs[i];  
        printf("Session %d: \n", i+1);
        printf("   Started: %s\n", ctime(&session -> timeStart));
        printf("   Ended: %s\n", ctime(&session -> timeEnd));
        printf("   Duration: %d minutes\n", session->durationInmin);  
    }
}

void sleepSummary(babySleep *tracker){
    int recommHours = 0;  

    if (tracker -> logCount == 0){
        printf("No sleep data.\n");
        return;
    }

    int totalBabySleeps = tracker -> logCount;
    float avgDuration = tracker -> sleepTotal / totalBabySleeps;

    printf("\n===== Baby Sleep Summary =====\n");
    printf("Total Sleep Sessions: %d\n", tracker -> logCount);
    printf("Total Sleep Time: %.2f hours\n", tracker->sleepTotal);
    printf("Average Sleep Duration: %.2f hours\n", avgDuration);

    // monitoring total sleep hours of the baby
    if (tracker -> ageInMonth <= 3){         
        recommHours = 14; 
        printf("Newborns needs a very long time to sleep!\n");              
    }       
    else if (tracker->ageInMonth > 3 && tracker -> ageInMonth <= 12){         
        recommHours = 12;
        printf("The baby needs more time to be asleep!\n");    
    }      
    else if(tracker->ageInMonth > 12){         
        recommHours = 10;
        printf("The baby still needs more time to be asleep!\n");         
            
    }  
    else{             
        printf("Your baby is now a toddler, but still needs more sleep!\n");         
    }  

    printf("Recommended Sleep Duration: %d hours\n", recommHours);
    if (tracker->sleepTotal < recommHours) {  
        printf("Notice: Total sleep duration is below normal.\nPlease consult to a doctor.\n");
    } else {
        printf("Total sleep duration is within the healthy range.\n");
    }
}

void sleepTracker(babySleep *tracker){ 
    int choice;

   while (1){
    printf("\n--- Baby Sleep Tracker ---\n");
        printf("1. Start Sleep Session\n");
        printf("2. End Sleep Session\n");
        printf("3. View Sleep History\n");
        printf("4. Sleep Summary\n");
        printf("5. Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);
        getchar(); 

    switch(choice){
        case 1:
           startSleep(tracker);
           break;
        case 2: 
           endSleep(tracker);
           break;
        case 3:
           sleepHistory(tracker);
           break;
        case 4:
           sleepSummary(tracker);
           break;
        case 5:
           return;
        default:
           printf("Invalid option!");
    }
   }
}
