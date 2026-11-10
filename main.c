#include "editor.h"

void handleCommand(TxtEdtr *edtr, char *command)
{
    char *token = strtok(command, " \r\n");
    // If user just pressed Enter (empty command)
    if (token == NULL)
    {
        return;
    }
    if (strcmp(token, "insert") == 0)
    {
        char *txt = strtok(NULL, "\r\n");
        if (txt != NULL)
        {
            while (*txt == ' ' || *txt == '\t') txt++;
        }
        if (txt == NULL || *txt == '\0')
        {
            printf("Usage: insert <text to insert>\n");
            return;
        }
        saveState(edtr);
        insertLine(edtr, txt);
    }
    else if (strcmp(token, "print") == 0 || strcmp(token, "display") == 0)
    {
        displayText(edtr);
    }
    else if (strcmp(token, "delete") == 0)
    {
        // Extract delete count
        char *num = strtok(NULL, " \r\n");

        if (num == NULL)
        {
            printf("Usage: delete <count>\n");
            return;
        }

        // Convert string to integer
        int count = atoi(num);

        if (edtr->cursor != NULL && count > 0 && count <= (int)strlen(edtr->cursor->line))
        {
            saveState(edtr);
        }

        // Call deleteChar()
        deleteChar(edtr, count);
    }
    else if (strcmp(token, "deleteLine") == 0)
    {
        if (edtr->head != NULL && edtr->cursor != NULL)
        {
            saveState(edtr);
        }
        deleteLine(edtr);
    }
    else if (strcmp(token, "copy") == 0)
    {
        copyText(edtr);
    }
    else if (strcmp(token, "cut") == 0)
    {
        if (edtr->head != NULL && edtr->cursor != NULL)
        {
            saveState(edtr);
        }
        cutText(edtr);
    }
    else if (strcmp(token, "paste") == 0)
    {
        saveState(edtr);
        pasteText(edtr);
    }
    else if (strcmp(token, "undo") == 0)
    {
        undo(edtr);
    }
    else if (strcmp(token, "redo") == 0)
    {
        redo(edtr);
    }
    else if (strcmp(token, "up") == 0)
    {
        moveUp(edtr);
    }
    else if (strcmp(token, "down") == 0)
    {
        moveDown(edtr);
    }
    else if (strcmp(token, "right") == 0)
    {
        moveRight(edtr);
    }
    else if (strcmp(token, "left") == 0)
    {
        moveLeft(edtr);
    }
    else if (strcmp(token, "start") == 0)
    {
        moveToStart(edtr);
    }
    else if (strcmp(token, "end") == 0)
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
        printf("  up               - Move the cursor to the previous line\n");
        printf("  down             - Move the cursor to the next line\n");
        printf("  left             - Move the cursor one character to the left\n");
        printf("  right            - Move the cursor one character to the right\n");
        printf("  start            - Move the cursor directly to the beginning of the current line\n");
        printf("  end              - Move the cursor directly to the end of the current line\n");
        printf("  copy             - Copies the current line into the clipboard\n");
        printf("  cut              - Copies the current line and deletes it from the editor\n");
        printf("  paste            - Inserts the copied line at the current cursor position\n");
        printf("  undo             - Revert the last change\n");
        printf("  redo             - Reapply the last undone change\n");
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

        // Strip trailing \r and \n
        command[strcspn(command, "\r\n")] = '\0';

        // Check for exit command
        char temp[2048];
        strcpy(temp, command);
        char *first = strtok(temp, " \t");
        if (first != NULL && strcmp(first, "exit") == 0)
        {
            break;
        }

        handleCommand(&edtr, command);
    }
    freeEditor(&edtr);

    printf("Goodbye! Thank you for using Text Editor\n");
    return 0;
}
