#ifndef EDITOR_H
#define EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Doubly Linked List Node
typedef struct Node
{
    char *line;
    struct Node *prev;
    struct Node *next;
} Node;

// Undo / Redo History Node
typedef struct History
{
    char *text;
    int cline;
    int cpos;
    struct History *next;
} History;

// Text Editor Structure
typedef struct
{
    Node *head;
    Node *tail;
    Node *cursor;

    int cline;
    int cpos;

    History *undoStack;
    History *redoStack;

} TxtEdtr;

// Initialization and Memory
void initEditor(TxtEdtr *edtr);
void freeEditor(TxtEdtr *edtr);

// Node Operations
Node *create_node(char *str);

// Text Operations
void insertLine(TxtEdtr *edtr, char *str);
void deleteLine(TxtEdtr *edtr);
void deleteChar(TxtEdtr *edtr, int count);

// Clipboard Operations
void copyText(TxtEdtr *editor);
void cutText(TxtEdtr *editor);
void pasteText(TxtEdtr *editor);
void freeClipboard();

// Display Operations
void displayText(TxtEdtr *edtr);
void showCursorPosition(TxtEdtr *edtr);

// Cursor Operations
void moveUp(TxtEdtr *edtr);
void moveDown(TxtEdtr *edtr);
void moveLeft(TxtEdtr *edtr);
void moveRight(TxtEdtr *edtr);
void moveToStart(TxtEdtr *edtr);
void moveToEnd(TxtEdtr *edtr);

// Command Handler
void handleCommand(TxtEdtr *edtr, char *command);

// History & Undo / Redo Operations
void saveState(TxtEdtr *edtr);
void undo(TxtEdtr *edtr);
void redo(TxtEdtr *edtr);
void clearHistory(History **stack);

#endif
