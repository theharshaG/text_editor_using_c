#include "editor.h"

// Push a snapshot onto a history stack
void pushHistory(History **stack, const char *text, int cline, int cpos)
{
    if (stack == NULL) 
        return;

    History *node = (History *)malloc(sizeof(History));
    if (node == NULL) return;

    if (text != NULL)
    {
        node->text = (char *)malloc(strlen(text) + 1);
        if (node->text != NULL)
            strcpy(node->text, text);
    }
    else
    {
        node->text = (char *)malloc(1);
        if (node->text != NULL)
            node->text[0] = '\0';
    }

    node->cline = cline;
    node->cpos = cpos;
    node->next = *stack;
    *stack = node;
}

// Pop a snapshot from a history stack
History *popHistory(History **stack)
{
    if (stack == NULL || *stack == NULL)
        return NULL;

    History *top = *stack;
    *stack = top->next;
    top->next = NULL;
    return top;
}

// Free all snapshots in a stack
void clearHistory(History **stack)
{
    if (stack == NULL) return;

    History *curr = *stack;
    while (curr != NULL)
    {
        History *next = curr->next;
        free(curr->text);
        free(curr);
        curr = next;
    }
    *stack = NULL;
}

// Convert all lines in the editor to a single string separated by \n
char *serializeEditor(TxtEdtr *edtr)
{
    if (edtr == NULL || edtr->head == NULL)
    {
        char *empty = (char *)malloc(1);
        if (empty != NULL) empty[0] = '\0';
        return empty;
    }

    size_t total_len = 0;
    Node *curr = edtr->head;
    while (curr != NULL)
    {
        total_len += strlen(curr->line) + 1;
        curr = curr->next;
    }

    char *buffer = (char *)malloc(total_len + 1);
    if (buffer == NULL) return NULL;

    buffer[0] = '\0';
    curr = edtr->head;
    while (curr != NULL)
    {
        strcat(buffer, curr->line);
        if (curr->next != NULL)
            strcat(buffer, "\n");
        curr = curr->next;
    }

    return buffer;
}

// Clear all lines in the editor
static void clearEditorLines(TxtEdtr *edtr)
{
    if (edtr == NULL) return;

    Node *curr = edtr->head;
    while (curr != NULL)
    {
        Node *next = curr->next;
        free(curr->line);
        free(curr);
        curr = next;
    }
    edtr->head = NULL;
    edtr->tail = NULL;
    edtr->cursor = NULL;
    edtr->cline = 1;
    edtr->cpos = 0;
}

// Restore editor state from a history snapshot
void restoreEditor(TxtEdtr *edtr, History *snap)
{
    if (edtr == NULL || snap == NULL) return;

    clearEditorLines(edtr);

    if (snap->text == NULL || snap->text[0] == '\0')
    {
        edtr->cline = 1;
        edtr->cpos = 0;
        return;
    }

    // Split text line by line and rebuild the doubly linked list
    const char *p = snap->text;
    while (*p != '\0')
    {
        const char *end = strchr(p, '\n');
        size_t len = (end != NULL) ? (size_t)(end - p) : strlen(p);

        char *lineStr = (char *)malloc(len + 1);
        if (lineStr != NULL)
        {
            strncpy(lineStr, p, len);
            lineStr[len] = '\0';

            Node *newNode = create_node(lineStr);
            free(lineStr);

            if (newNode != NULL)
            {
                if (edtr->head == NULL)
                {
                    edtr->head = newNode;
                    edtr->tail = newNode;
                }
                else
                {
                    edtr->tail->next = newNode;
                    newNode->prev = edtr->tail;
                    edtr->tail = newNode;
                }
            }
        }

        if (end == NULL) break;
        p = end + 1;
    }

    // Restore cursor position
    edtr->cline = snap->cline;
    edtr->cpos = snap->cpos;

    // Reposition cursor pointer to matching line
    Node *curr = edtr->head;
    int idx = 1;
    while (curr != NULL && idx < edtr->cline)
    {
        curr = curr->next;
        idx++;
    }
    edtr->cursor = (curr != NULL) ? curr : edtr->tail;

    if (edtr->cursor != NULL)
    {
        int len = strlen(edtr->cursor->line);
        if (edtr->cpos > len)
            edtr->cpos = len;
    }
    else
    {
        edtr->cline = 1;
        edtr->cpos = 0;
    }
}

// Call this BEFORE making any modifications to the text
void saveState(TxtEdtr *edtr)
{
    if (edtr == NULL) return;

    char *snapshot = serializeEditor(edtr);
    if (snapshot == NULL) 
        return;

    pushHistory(&edtr->undoStack, snapshot, edtr->cline, edtr->cpos);
    free(snapshot);

    // Any new change clears future redo history
    clearHistory(&edtr->redoStack);
}

// Undo command
void undo(TxtEdtr *edtr)
{
    if (edtr == NULL || edtr->undoStack == NULL)
    {
        printf("Nothing to undo!\n");
        return;
    }

    // Save current state onto redo stack
    char *currentSnapshot = serializeEditor(edtr);
    if (currentSnapshot != NULL)
    {
        pushHistory(&edtr->redoStack, currentSnapshot, edtr->cline, edtr->cpos);
        free(currentSnapshot);
    }

    // Pop and apply previous state
    History *past = popHistory(&edtr->undoStack);
    if (past != NULL)
    {
        restoreEditor(edtr, past);
        free(past->text);
        free(past);
    }

    printf("Undo successful.\n");
}

// Redo command
void redo(TxtEdtr *edtr)
{
    if (edtr == NULL || edtr->redoStack == NULL)
    {
        printf("Nothing to redo!\n");
        return;
    }

    // Save current state onto undo stack
    char *currentSnapshot = serializeEditor(edtr);
    if (currentSnapshot != NULL)
    {
        pushHistory(&edtr->undoStack, currentSnapshot, edtr->cline, edtr->cpos);
        free(currentSnapshot);
    }

    // Pop and apply future state
    History *future = popHistory(&edtr->redoStack);
    if (future != NULL)
    {
        restoreEditor(edtr, future);
        free(future->text);
        free(future);
    }

    printf("Redo successful.\n");
}