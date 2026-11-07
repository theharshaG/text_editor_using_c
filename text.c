#include "editor.h"
Node *create_node(char *str)
{
    Node *new=malloc(sizeof(new));
    if(new==NULL)
    {
        return NULL;
    }
    new->line=malloc(strlen(str)+1);
    if(new->line==NULL)
    {
        free(new);
        return NULL;
    }
    strcpy(new->line,str);
    new->prev=NULL;
    new->next=NULL;
    return new;
}
void insertLine(TxtEdtr *edtr, char *str)
{
    Node *new=create_node(str);
    if(new==NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }
    if(edtr->head==NULL)
    {
        edtr->head=new;
        edtr->tail=new;
    }
    else
    {
        edtr->tail->next=new;
        new->prev=edtr->tail;
        edtr->tail=new;
    }
    edtr->cursor = new;
    edtr->cline++;
    edtr->cpos = 0;
}

void displayText(TxtEdtr *edtr)
{
    Node *temp = edtr->head;

    if (temp == NULL)
    {
        printf("Text Editor is empty\n");
        return;
    }

    while (temp != NULL)
    {
        printf("%s\n", temp->line);

        temp = temp->next;
    }
}

