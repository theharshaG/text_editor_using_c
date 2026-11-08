#include "editor.h"

void handleCommand(TxtEdtr *edtr,char *command)
{
    char *token=strtok(command," \n");
    // If user just pressed Enter (empty command)
    if (token == NULL)
    {
        return;
    }
    if(strcmp(token,"insert")==0)
    {
        char *txt=strtok(NULL,"\n");
        if(txt==NULL)
        {
            printf("Usage: insert <text to insert>\n");
            return;
        }
        insertLine(edtr,txt);
    }
    else if (strcmp(token, "display") == 0)
    {
        displayText(edtr);
    }
    else if (strcmp(token, "delete") == 0)
    {
        // Extract delete count
        char *num = strtok(NULL, " \n");

        if (num == NULL)
        {
            printf("Usage: delete <count>\n");
            return;
        }

        // Convert string to integer
        int count = atoi(num);

        // Call deleteChar()
        deleteChar(edtr, count);
    }
    else if (strcmp(token, "help") == 0)
    {
        printf("\nAvailable Commands:\n");
        printf("  insert <text>    - Add a new line with the given text\n");
        printf("  display          - Display all lines in the editor\n");
        printf("  delete <count>   - Delete characters from the end of current line\n");
        printf("  deleteLine <line>- Delete a specific line number\n");
        printf("  help             - Show this help message\n");
        printf("  exit             - Exit the editor\n");
    }
    else
    {
        printf("Unknown command: '%s'. Type 'help' for available commands.\n", token);
    }
}

int main()
{
    TxtEdtr edtr;
    
    char command[2048];

    initEditor(&edtr);

    printf("============================================\n");
    printf("             TEXT EDITOR\n");
    printf("============================================\n");
    printf("Type 'help' for available commands.\n");

    
    while (1)
    {
        printf("\neditor> ");
        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            break; // Handles Ctrl+D / EOF
        }
        if (strcmp(command, "exit\n") == 0)
        {
            break;
        }
        handleCommand(&edtr, command);
    }
    freeEditor(&edtr);

    printf("Goodbye! Thank you for using Text Editor\n");
    return 0;
}