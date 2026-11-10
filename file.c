#include "editor.h"

// Open a file and load its lines into the editor
void openFile(TxtEdtr *edtr, const char *filename)
{
    if (edtr == NULL || filename == NULL) return;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: Could not open file '%s'.\n", filename);
        return;
    }

    // Close and clear current content if editor already has text
    if (edtr->head != NULL)
    {
        closeFile(edtr);
    }

    char buffer[2048];
    int lineCount = 0;

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        // Strip trailing \r and \n
        buffer[strcspn(buffer, "\r\n")] = '\0';

        Node *newNode = create_node(buffer);
        if (newNode == NULL) break;

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
        lineCount++;
    }

    fclose(fp);

    edtr->cursor = edtr->head;
    edtr->cline = 1;
    edtr->cpos = 0;

    strncpy(edtr->filename, filename, sizeof(edtr->filename) - 1);
    edtr->filename[sizeof(edtr->filename) - 1] = '\0';

    // Clear history stacks for the newly opened file
    clearHistory(&edtr->undoStack);
    clearHistory(&edtr->redoStack);

    printf("File '%s' opened successfully (%d lines).\n", filename, lineCount);
}

// Save all lines from the editor to a file
void saveFile(TxtEdtr *edtr, const char *filename)
{
    if (edtr == NULL) return;

    const char *target = filename;

    // If no filename was passed in the command, use the current open filename
    if (target == NULL || target[0] == '\0')
    {
        if (edtr->filename[0] != '\0')
        {
            target = edtr->filename;
        }
        else
        {
            printf("Usage: save <filename>\n");
            return;
        }
    }

    FILE *fp = fopen(target, "w");
    if (fp == NULL)
    {
        printf("Error: Could not write to file '%s'.\n", target);
        return;
    }

    Node *curr = edtr->head;
    while (curr != NULL)
    {
        fprintf(fp, "%s\n", curr->line);
        curr = curr->next;
    }

    fclose(fp);

    // Remember this filename as the active file
    strncpy(edtr->filename, target, sizeof(edtr->filename) - 1);
    edtr->filename[sizeof(edtr->filename) - 1] = '\0';

    printf("File '%s' saved successfully.\n", target);
}

// Close current file and reset the editor
void closeFile(TxtEdtr *edtr)
{
    if (edtr == NULL || edtr->head == NULL)
    {
        printf("No file is currently open.\n");
        return;
    }

    // Free all line nodes
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
    edtr->filename[0] = '\0';

    // Clear undo/redo stacks
    clearHistory(&edtr->undoStack);
    clearHistory(&edtr->redoStack);

    printf("File closed successfully.\n");
}