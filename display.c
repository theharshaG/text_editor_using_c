#include "editor.h"

void displayText(TxtEdtr *edtr)
{
    if (edtr == NULL || edtr->head == NULL)
    {
        printf("Text Editor is empty.\n");
        return;
    }

    Node *temp = edtr->head;
    int lineNum = 1;

    printf("\n============================================\n");
    printf("               📑 TEXT EDITOR\n");
    printf("============================================\n");

    while (temp != NULL)
    {
        // Display with line number for easy reference
        printf("LINE: %d ~ %s\n", lineNum++, temp->line);
        temp = temp->next;
    }
    showCursorPosition(edtr);
    printf("============================================\n");
}

void showCursorPosition(TxtEdtr *edtr)
{
    if (edtr == NULL || edtr->cursor == NULL)
    {
        printf("Cursor: No position\n");
        return;
    }

    printf("--------------------------------------------\n");
    printf("Cursor position: Line %d, Column %d\n",edtr->cline,edtr->cpos);
}
void moveToStart(TxtEdtr *edtr)
{
    if(edtr == NULL || edtr->cursor == NULL)
    {
        printf("Editor Empty!\n");
        return;
    }

    edtr->cpos = 0;
}
void moveToEnd(TxtEdtr *edtr)
{
    if(edtr == NULL || edtr->cursor == NULL)
    {
        printf("Editor Empty!\n");
        return;
    }

    edtr->cpos = strlen(edtr->cursor->line);
}