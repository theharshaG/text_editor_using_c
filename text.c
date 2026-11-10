#include "editor.h"

char *clipboard = NULL;

Node *create_node(char *str)
{
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
        edtr->cursor = newNode;
        edtr->cline = 1;
    }
    else
    {
        // Insert after current cursor position
        newNode->next = edtr->cursor->next;
        newNode->prev = edtr->cursor;

        if (edtr->cursor->next != NULL)
        {
            edtr->cursor->next->prev = newNode;
        }
        else
        {
            edtr->tail = newNode;
        }

        edtr->cursor->next = newNode;
        edtr->cursor = newNode;
        edtr->cline++;
    }

    edtr->cpos = strlen(str);
    printf("Text inserted successfully..\n");
}

void deleteChar(TxtEdtr *edtr, int count)
{
    // Check whether editor or cursor is valid
    if (edtr == NULL || edtr->cursor == NULL)
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

    // Update cursor position if it was past the new end
    if (edtr->cpos > new_len)
    {
        edtr->cpos = new_len;
    }

    printf("Deleted %d characters successfully.\n", count);
}

void deleteLine(TxtEdtr *edtr)
{
    // Step 1: Check whether editor or cursor is NULL
    if (edtr == NULL || edtr->cursor == NULL)
    {
        printf("Editor is empty. Nothing to delete!\n");
        return;
    } 

    // Step 2: Store current, previous and next nodes
    Node *current = edtr->cursor;
    Node *previous = current->prev;
    Node *next = current->next;

    // Step 3: Connect previous node to next node
    if (previous != NULL)
    {
        previous->next = next;
    }
    else
    {
        edtr->head = next;
    }

    // Step 4: Connect next node to previous node
    if (next != NULL)
    {
        next->prev = previous;
    }
    else
    {
        edtr->tail = previous;
    }

    // Step 5: Free current node memory
    free(current->line);
    free(current);

    // Step 6: Move cursor to next node
    if (next != NULL)
    {
        edtr->cursor = next;
        edtr->cpos = 0;
    }

    // Step 7: If next node does not exist
    else if (previous != NULL)
    {
        edtr->cursor = previous;
        edtr->cline--;
        edtr->cpos = strlen(edtr->cursor->line);
    }

    // Step 8: If editor becomes empty
    else
    {
        edtr->cursor = NULL;
        edtr->cline = 1;
        edtr->cpos = 0;
    }

    printf("Line deleted successfully!\n");
}

void copyText(TxtEdtr *editor)
{
    if (editor == NULL || editor->cursor == NULL)
    {
        printf("Error: Editor is empty.\n");
        return;
    }
  
    free(clipboard);
    clipboard = NULL;
    
    clipboard = (char *)malloc(strlen(editor->cursor->line) + 1);
    if (clipboard == NULL)
    {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    strcpy(clipboard, editor->cursor->line);
    printf("Text copied successfully.\n");
}

void cutText(TxtEdtr *editor)
{
    if (editor == NULL || editor->cursor == NULL)
    {
        printf("Error: Editor is empty.\n");
        return;
    }

    copyText(editor);
    deleteLine(editor);
    printf("Text cut successfully.\n");
}

void pasteText(TxtEdtr *editor)
{
    if (editor == NULL)
        return;
    
    if (clipboard == NULL)
    {
        printf("Clipboard is empty.\n");
        return;
    }
    insertLine(editor, clipboard);

    printf("Text pasted successfully.\n");
}

void freeClipboard(void)
{
    if (clipboard != NULL)
    {
        free(clipboard);
        clipboard = NULL;
    }
}
