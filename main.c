
#include "editor.h"

int main()
{
    TxtEdtr edtr;
    char str[1000];
    int choice;

    initEditor(&edtr);

    while (1)
    {
        printf("\n----- TEXT EDITOR -----\n");
        printf("1. Insert Line\n");
        printf("2. Display Text\n");
        printf("3. Delete Line\n");
        printf("4. Save File\n");
        printf("5. Open File\n");
        printf("6. Undo\n");
        printf("7. Redo\n");
        printf("8. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter a line: ");
                scanf(" %[^\n]", str);
                insertLine(&edtr, str);
                break;

            case 2:
                displayText(&edtr);
                break;

            case 3:
                // Delete line
                break;

            case 4:
                // Save file
                break;

            case 5:
                // Open file
                break;

            case 6:
                // Undo
                break;

            case 7:
                // Redo
                break;

            case 8:
                freeEditor(&edtr);
                printf("Exiting Text Editor...\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
