#include "editor.h"

void moveUp(TxtEdtr *edtr)
{
    if (edtr == NULL || edtr->cursor == NULL)
    {
        printf("Editor Empty!\n");
        return;
    }
    if (edtr->cursor->prev == NULL)
    {
        printf("Already at the first line!\n");
        return;
    }
    edtr->cursor = edtr->cursor->prev;
    edtr->cline--;
    int len = strlen(edtr->cursor->line);

    if (edtr->cpos > len)
    {
        edtr->cpos = len;
    }   
}

void moveDown(TxtEdtr *edtr)
{
    if (edtr == NULL || edtr->cursor == NULL)
    {
        printf("Editor Empty!\n");
        return;
    }
    if (edtr->cursor->next == NULL)
    {
        printf("Already at the last line!\n");
        return;
    }
    edtr->cursor = edtr->cursor->next;
    edtr->cline++;
    int len = strlen(edtr->cursor->line);
    if (edtr->cpos > len)
    {
        edtr->cpos = len;
    }
}

void moveRight(TxtEdtr *edtr)
{
    if (edtr == NULL || edtr->cursor == NULL)
    {
        printf("Editor Empty!\n");
        return;
    }

    int len = strlen(edtr->cursor->line);

    if (edtr->cpos < len)
    {
        edtr->cpos++;
    }
    else
    {
        printf("Already at the end of the line!\n");
    }
}

void moveLeft(TxtEdtr *edtr)
{
    if (edtr == NULL || edtr->cursor == NULL)
    {
        printf("Editor Empty!\n");
        return;
    }

    if (edtr->cpos > 0)
    {
        edtr->cpos--;
    }
    else
    {
        printf("Already at the beginning of the line!\n");
    }
}

void moveToStart(TxtEdtr *edtr)
{
    if (edtr == NULL || edtr->cursor == NULL)
    {
        printf("Editor Empty!\n");
        return;
    }

    edtr->cpos = 0;
}

void moveToEnd(TxtEdtr *edtr)
{
    if (edtr == NULL || edtr->cursor == NULL)
    {
        printf("Editor Empty!\n");
        return;
    }

    edtr->cpos = strlen(edtr->cursor->line);
}
