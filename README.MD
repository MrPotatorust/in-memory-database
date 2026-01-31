# In-Memory Database

A simple key-value store implemented in C using a hash table with collision resolution via linked lists.


**Disclaimer:**

This doc was written by Claude Haiku 4.5 using Copilot. But the project was implemented by me with minimal use of ai, mostly for searching or asking specific questions about memory managment and pointers. Because this is my first C project.


## Usage

### Build

```bash
make
```

### Run

```bash
./main [optional: seed_number]
```

**Example:**

```bash
./main 5  # Seeds the database with 5 random key-value pairs
./main    # Starts with empty database
```

### Commands

Once running, the program presents an interactive menu:

| Command | Action                                    |
| ------- | ----------------------------------------- |
| `s`     | **Save** - Add or update a key-value pair |
| `g`     | **Get** - Retrieve a value by key         |
| `d`     | **Delete** - Remove a key-value pair      |
| `p`     | **Print** - Display all stored data       |
| `c`     | **Config** - Parse config.json file WIP   |
| `e`     | **Exit** - Close the program              |

**Example Session:**

```
ACTION: s
Key: username
Value: john_doe
ACTION: g
KEY: username
john_doe
ACTION: p
[displays all key-value pairs]
ACTION: e
```

## Implementation

### Architecture

The database uses a **hash table with chaining** for collision resolution:

- **Storage Array**: 1000 slots (`STORAGE_SZ`)
- **Each Slot**: Points to a linked list of `Node` structures
- **Hash Function**: DJB2 algorithm (`hash()` in `helpers.c`)

### Data Structure

```c
typedef struct Node {
    struct Node *next;
    char key[KEY_SZ];      // Max 20 characters
    char value[VALUE_SZ];  // Max 100 characters
} Node;
```

### Core Components

#### 1. **Storage Management** (`helpers.c`)

- `saveNode(Node *newNode)` - Insert or update a node
- `getValue(char *key)` - Retrieve a value
- `deleteNode(char *key)` - Remove a node
- `getStorageIndex(char *str)` - Calculate hash table index
- `hash(char *str)` - DJB2 hash algorithm

#### 2. **User Actions** (`actions.c`)

- `actionSave()` - Handle save command
- `actionGetValue()` - Handle get command
- `actionDelete()` - Handle delete command

#### 3. **Utilities** (`helpers.c`)

- `getString(char *prompt)` - Get user input
- `getConfirmation()` - Ask for y/n confirmation
- `printStorage()` - Display entire database
- `freeStorage()` - Clean up all allocated memory

#### 4. **Seeding** (`seeder.c`)

- `seedStorage(int count)` - Generate random key-value pairs for testing

#### 5. **Config Parser** (`src/config_parser/config.c`) WIP

- `parse()` - Parse config.json file
- `trimString()` - Remove whitespace from strings

### Key Limits

- **Key Size**: 20 characters
- **Value Size**: 100 characters
- **Hash Table Size**: 1000 slots
- **Collision Handling**: Linked list chaining

### Memory Management

- Nodes are dynamically allocated with `malloc()` and freed with `free()`
- User input strings are allocated and freed after use
- `freeStorage()` releases all nodes when the program exits

### Collision Resolution

When two keys hash to the same index, they're stored in a linked list at that slot. The program traverses the list to find the specific key.

**Example:**

```
storage[100] -> Node(key="a") -> Node(key="b") -> Node(key="c") -> NULL
```