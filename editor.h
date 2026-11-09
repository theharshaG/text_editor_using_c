
#ifndef EDITOR_H
#define EDITOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char *line;
    struct Node *prev;
    struct Node *next;
} Node;

typedef struct
{
    Node *head;
    Node *tail;
    Node *cursor;

    int cline;
    int cpos;
} TxtEdtr;

void handleCommand(TxtEdtr *edtr,char *command);
void initEditor(TxtEdtr *edtr);
void freeEditor(TxtEdtr *edtr);

Node *create_node(char *str);
void insertLine(TxtEdtr *edtr, char *str);
void displayText(TxtEdtr *edtr);
void deleteChar(TxtEdtr *edtr, int count);
void deleteLine(TxtEdtr *edtr);
void moveUp(TxtEdtr *edtr);
void moveDown(TxtEdtr *edtr);
void moveRight(TxtEdtr *edtr);
void moveLeft(TxtEdtr *edtr);
void moveToStart(TxtEdtr *edtr);
void moveToEnd(TxtEdtr *edtr);

void showCursorPosition(TxtEdtr *edtr);

#endif
