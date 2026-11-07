
#include "editor.h"

void initEditor(TxtEdtr *edtr)
{
    edtr->head = NULL;
    edtr->tail = NULL;
    edtr->cursor = NULL;

    edtr->cline = 1;
    edtr->cpos = 0;
}

void freeEditor(TxtEdtr *edtr)
{
    Node *temp = edtr->head;

    while (temp != NULL)
    {
        Node *next = temp->next;

        free(temp->line);
        free(temp);

        temp = next;
    }

    edtr->head = NULL;
    edtr->tail = NULL;
    edtr->cursor = NULL;

    edtr->cline = 1;
    edtr->cpos = 0;
}