# Online Voting System in C

A command-line voting system written in C that allows users to manage candidates, cast votes, and view results with data persistence.

## Features

- Add up to 10 candidates for voting
- Cast votes for registered candidates
- View current voting results with vote counts and percentages
- Reset all votes while keeping candidates
- Clear all data (candidates and votes) for a fresh start
- Automatic data persistence using binary file storage

## How to Run

### Option 1: Using GCC (Linux/Mac/Windows)

Compile the program:
```bash
gcc -std=c99 voting_system.c -o voting_system
```

Run the program:
```bash
./voting_system
```

### Option 2: Using Dev-C++ (Windows)

If Dev-C++ is installed in the default location:
```bash
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\gcc.exe" -std=c99 voting_system.c -o voting_system.exe
```

Run the program:
```bash
voting_system.exe
```

**Note**: Adjust the path if Dev-C++ is installed in a different location.

### Option 3: Using Online Compiler

This project can also be compiled and run directly in an online C compiler without any installation:

1. Visit [OnlineGDB](https://www.onlinegdb.com/online_c_compiler) or [Programiz](https://www.programiz.com/c-programming/online-compiler)
2. Copy the code from `voting_system.c`
3. Paste it into the online editor
4. Click "Run" to execute

**Note**: Online compilers have limited file I/O capabilities, so data persistence may not work in all online environments.

## Usage

The program provides an interactive menu with the following options:

1. **Add Candidate** - Register a new candidate for voting
2. **Cast Vote** - Vote for one of the registered candidates
3. **View Results** - See current vote counts and percentages
4. **Reset Votes** - Clear all votes (keeps candidates, requires confirmation)
5. **Clear All Data** - Remove all candidates and votes (requires confirmation)
6. **Exit** - Close the program

### Example Session

```
=== Online Voting System ===
1. Add Candidate
2. Cast Vote
3. View Results
4. Reset Votes
5. Clear All Data
6. Exit
Enter your choice: 1
Enter candidate name: Alice
Candidate added successfully!

=== Online Voting System ===
1. Add Candidate
2. Cast Vote
3. View Results
4. Reset Votes
5. Clear All Data
6. Exit
Enter your choice: 1
Enter candidate name: Bob
Candidate added successfully!

=== Online Voting System ===
1. Add Candidate
2. Cast Vote
3. View Results
4. Reset Votes
5. Clear All Data
6. Exit
Enter your choice: 2

--- Candidates ---
1. Alice
2. Bob
Enter your choice (1-2): 1
Vote cast successfully for Alice!

=== Online Voting System ===
1. Add Candidate
2. Cast Vote
3. View Results
4. Reset Votes
5. Clear All Data
6. Exit
Enter your choice: 3

--- Voting Results ---
Alice: 1 votes (100.00%)
Bob: 0 votes (0.00%)
Total votes: 1
```

## How It Works

### Data Structure

The program uses a simple structure to store candidate information:

```c
typedef struct {
    char name[MAX_NAME_LENGTH];  // Candidate name (up to 50 characters)
    int votes;                   // Vote count for this candidate
} Candidate;
```

### Key Functions

- **`load_data()`** - Loads candidate data from the binary file at startup
- **`save_data()`** - Saves current state to the binary file
- **`add_candidate()`** - Registers a new candidate
- **`cast_vote()`** - Allows voting for a candidate
- **`display_results()`** - Shows voting statistics
- **`reset_voting()`** - Clears all votes (keeps candidates)
- **`clear_all_data()`** - Removes all candidates and votes

### Data Persistence

The system automatically saves voting data to `voting_data.dat` in the same directory. This file is created when you first run the program and is updated whenever changes are made. Data is loaded automatically when the program starts, ensuring your voting data persists between sessions.

**Note**: The online compiler option may not support file I/O, so data persistence features will not work in those environments.

## Project Structure

```
online-voting-system/
├── voting_system.c      # Main source code
├── README.md            # Documentation
├── .gitignore           # Git ignore rules
└── voting_data.dat      # Binary data file (auto-generated)
```

## Technical Details

### Constants
- `MAX_CANDIDATES`: 10 (maximum number of candidates)
- `MAX_NAME_LENGTH`: 50 (maximum characters in candidate name)
- `DATA_FILE`: "voting_data.dat" (data file name)

### Compilation Requirements
- C compiler with C99 support (GCC, Clang, or MinGW)
- Standard C library (stdio.h, stdlib.h, string.h)

### Compatibility
- Works on Linux, macOS, and Windows
- Compatible with online C compilers (with limited file I/O)
- Uses C89-compatible code for broader compiler support

## Limitations

- Maximum of 10 candidates
- No user authentication (anyone can vote multiple times)
- Single-user local system (not networked)
- Basic error handling (no recovery from corrupted files)
- Command-line interface only (no GUI)
- Data persistence requires local file system access
