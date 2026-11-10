# TxtEdtr 📑

A lightweight, command-driven terminal text editor built in C. **TxtEdtr** manages text dynamically using a **Doubly Linked List** for flexible line-by-line editing, a **snapshot-based history stack** for full Undo/Redo capability, a dedicated **clipboard** (Copy/Cut/Paste), multi-directional **cursor navigation**, and persistent **file I/O** (Open/Save/Close).

---

## Features

- **Doubly Linked List Architecture:** Every line is stored as an independent node (`Node`), enabling efficient line insertions and deletions.
- **Full Cursor Navigation:** Move up, down, left, right, to the start of a line, or directly to the end of a line with automatic column clamping.
- **Clipboard Support:** Copy the current line, cut lines directly from the buffer, and paste them at the current cursor position.
- **Snapshot Undo & Redo:** Full document state snapshots saved before modifying operations, allowing unlimited undo and redo without desynchronization.
- **File Persistence:** Open existing text files, save buffer content to disk, and cleanly close files.
- **Memory Safe:** Thoroughly validated with AddressSanitizer (`-fsanitize=address,undefined`) with zero memory leaks.

---

## 📂 Project Structure

```
TxtEdtr/
├── editor.h      # Core data structures (Node, History, TxtEdtr) and prototypes
├── main.c        # Interactive REPL, command parsing, and dispatch
├── editor.c      # Editor lifecycle (initEditor, freeEditor)
├── text.c        # Text node operations, insertions, deletions, and clipboard
├── cursor.c      # Cursor movements (up, down, left, right, start, end)
├── display.c     # Screen rendering (displayText, showCursorPosition)
├── history.c     # Document snapshotting, history stacks, undo, and redo
├── file.c        # File I/O operations (openFile, saveFile, closeFile)
├── Makefile      # Build automation configuration
└── README.md     # Documentation
```

---

## 🛠️ Data Structures

### 1. Doubly Linked List Node (`Node`)
Stores a single line of text with pointers to previous and next lines:
```c
typedef struct Node
{
    char *line;
    struct Node *prev;
    struct Node *next;
} Node;
```

### 2. History Node (`History`)
Represents a document snapshot stored on the `undoStack` or `redoStack`:
```c
typedef struct History
{
    char *text;          // Complete document contents joined with '\n'
    int cline;           // Cursor line number at snapshot time
    int cpos;            // Cursor column position at snapshot time
    struct History *next;
} History;
```

### 3. Editor Context (`TxtEdtr`)
Maintains the complete editor runtime state:
```c
typedef struct
{
    Node *head;          // First line in document
    Node *tail;          // Last line in document
    Node *cursor;        // Currently selected line node

    int cline;           // Current line number (1-indexed)
    int cpos;            // Current column position (0-indexed)

    History *undoStack;  // LIFO stack for Undo operations
    History *redoStack;  // LIFO stack for Redo operations

    char filename[256];  // Active file name
} TxtEdtr;
```

---

## ⌨️ Command Reference

| Command | Usage Example | Description |
| :--- | :--- | :--- |
| `insert <text>` | `insert Hello World` | Inserts a new line after the current cursor position |
| `print` / `display` | `print` | Displays all lines with line numbers and cursor coordinates |
| `delete <count>` | `delete 5` | Deletes `<count>` characters from the end of the current line |
| `deleteLine` | `deleteLine` | Deletes the line currently selected by the cursor |
| `up` | `up` | Moves the cursor up to the previous line |
| `down` | `down` | Moves the cursor down to the next line |
| `left` | `left` | Moves cursor one character left |
| `right` | `right` | Moves cursor one character right |
| `start` | `start` | Moves cursor directly to the beginning of the line (column 0) |
| `end` | `end` | Moves cursor directly to the end of the current line |
| `copy` | `copy` | Copies the current line into the clipboard |
| `cut` | `cut` | Copies the current line to clipboard and removes it from editor |
| `paste` | `paste` | Inserts the clipboard text after the current cursor position |
| `undo` | `undo` | Reverts the last text-modifying action |
| `redo` | `redo` | Re-applies the most recently undone action |
| `open <file>` | `open notes.txt` | Loads an existing file into the editor |
| `save [file]` | `save notes.txt` or `save` | Saves the editor buffer to disk |
| `close` | `close` | Closes the current file and resets the editor to blank |
| `help` | `help` | Prints the list of available commands |
| `exit` | `exit` | Frees all allocated memory and exits the editor |

---

## 🔨 Build & Run Instructions

### Prerequisites
- GCC (`gcc`) compiler supporting C99 or later.
- GNU Make (`make`).

### Compiling with Make
```bash
# Build the project
make

# Build and run immediately
make run

# Clean build artifacts (.o files and executable)
make clean
```

### Compiling Manually with GCC
```bash
gcc -Wall -Wextra -std=c99 -pedantic -g *.c -o txtedtr
./txtedtr
```

---

## 💡 Example Session

```text
============================================
             TEXT EDITOR
============================================
Type 'help' for available commands.

editor> insert First line
Text inserted successfully..

editor> insert Second line
Text inserted successfully..

editor> print
============================================
               📑 TEXT EDITOR
============================================
LINE: 1 ~ First line
LINE: 2 ~ Second line
--------------------------------------------
Cursor position: Line 2, Column 11
============================================

editor> save doc.txt
File 'doc.txt' saved successfully.

editor> deleteLine
Line deleted successfully!

editor> undo
Undo successful.

editor> print
============================================
               📑 TEXT EDITOR
============================================
LINE: 1 ~ First line
LINE: 2 ~ Second line
--------------------------------------------
Cursor position: Line 2, Column 11
============================================

editor> exit
Goodbye! Thank you for using Text Editor
```

---

## 🛡️ Memory Safety
All dynamically allocated memory (line strings, doubly linked list nodes, history snapshots, and clipboard) is completely freed on file close or editor exit. You can verify memory hygiene at any time with AddressSanitizer:

```bash
gcc -fsanitize=address,undefined -g *.c -o asan_test
./asan_test
```
