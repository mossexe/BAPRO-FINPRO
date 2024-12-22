#include <stdio.h>

int main()
{

    do
    {
        printf("\nMenu Options:\n");
        printf("A. Growth Tracker\n");
        printf("B. Vaccine Tracker\n");
        printf("C. Sleep Tracker\n");
        printf("D. Health Database\n");
        printf("E. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &menu);

        switch (menu)
        {
        case 'A':
            break;

        case 'B':
            break;

        case 'C':
            break;

        case 'D':
            break;

        case 'E':
            printf("Exiting program. Thank you!\n");
            break;

        default:
            printf("Invalid Input! Try Again.\n");
        }
    } while (menu != 'E');

    return 0;
}