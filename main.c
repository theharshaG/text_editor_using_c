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
    else if (strcmp(token, "print") == 0)
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

    else if(strcmp(token,"deleteLine")==0)
    {
        deleteLine(edtr);
    }

    else if(strcmp(token,"up")==0)
    {
        moveUp(edtr);
    }

    else if(strcmp(token,"down")==0)
    {
        moveDown(edtr);
    }
    else if(strcmp(token,"right")==0)
    {
        moveRight(edtr);
    }
    else if(strcmp(token,"left")==0)
    {
        moveLeft(edtr);
    }
    else if(strcmp(token,"start")==0)
    {
        moveToStart(edtr);
    }
    else if(strcmp(token,"end")==0)
    {
        moveToEnd(edtr);
    }

    else if (strcmp(token, "help") == 0)
    {
        printf("\nAvailable Commands:\n");
        printf("  insert <text>    - Add a new line with the given text\n");
        printf("  print            - Display all lines in the editor\n");
        printf("  delete <count>   - Delete characters from the end of current line\n");
        printf("  deleteLine       - Delete a currently selected line\n");
        printf("  up               - Move the cursor next line.\n");
        printf("  down             - Move the cursor previous line.\n");
        printf("  left             - Move the cursor one character to the left.\n");
        printf("  right            - Move the cursor one character to the right.\n");
        printf("  start            - Move the cursor directly to the beginning of the current line.\n");
        printf("  end              - Move the cursor directly to the end of the current line.\n");
        printf("  copy             - Copies the current line into the clipboard.\n");
        printf("  cut              - Copies the current line and deletes it from the editor.\n");
        printf("  paste            - Inserts the copied line at the current cursor position.\n");
        printf("  undo\n");
        printf("  redo\n");
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