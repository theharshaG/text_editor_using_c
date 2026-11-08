#include "editor.h"

Node *create_node(char *str)
{
    // Fix: Allocate sizeof(Node) (24 bytes), NOT sizeof(new) (8 bytes)
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        return NULL;
    }

    if (str == NULL)
    {
        str = "";
    }

    newNode->line = (char *)malloc(strlen(str) + 1);
    if (newNode->line == NULL)
    {
        free(newNode);
        return NULL;
    }

    strcpy(newNode->line, str);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertLine(TxtEdtr *edtr, char *str)
{
    if (edtr == NULL)
        return;

    Node *newNode = create_node(str);
    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    // If editor is empty
    if (edtr->head == NULL)
    {
        edtr->head = newNode;
        edtr->tail = newNode;
        edtr->cline = 1;
    }
    else
    {
        edtr->tail->next = newNode;
        newNode->prev = edtr->tail;
        edtr->tail = newNode;
        edtr->cline++;
    }

    edtr->cursor = newNode;
    edtr->cpos = 0;
    printf("Text inserted successfully..\n");
}

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
    printf("============================================\n");
}
void deleteChar(TxtEdtr *edtr, int count)
{
    // Check whether cursor is valid
    if (edtr->cursor == NULL)
    {
        printf("Nothing to delete!\n");
        return;
    }

    // Get current line length
    int len = strlen(edtr->cursor->line);

    // Validate delete count
    if (count <= 0 || count > len)
    {
        printf("Invalid delete count!\n");
        return;
    }

    // Calculate new length
    int new_len = len - count;

    // Remove characters from the end
    edtr->cursor->line[new_len] = '\0';

    // Update cursor position
    edtr->cpos = new_len;

    printf("Deleted %d characters successfully.\n", count);
}