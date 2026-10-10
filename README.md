# Online Voting System in C

A simple command-line voting system written in C that allows users to manage candidates, cast votes, and view results with data persistence.

## Features

- **Add Candidates**: Register up to 10 candidates for voting
- **Cast Votes**: Vote for any registered candidate
- **View Results**: Display vote counts and percentages for all candidates
- **Reset Votes**: Clear all votes while keeping candidates (with confirmation)
- **Clear All Data**: Remove all candidates and votes for a fresh start (with confirmation)
- **Data Persistence**: Automatically saves data to binary file between sessions

## How It Works

### Code Structure

The program is built around a simple data structure and several key functions:

#### Data Structure

```c
typedef struct {
    char name[MAX_NAME_LENGTH];  // Candidate name (up to 50 characters)
    int votes;                   // Vote count for this candidate
} Candidate;
```

The program maintains:
- An array of up to 10 `Candidate` structures
- A global `candidate_count` variable tracking the number of registered candidates
- A binary data file (`voting_data.dat`) for persistence

#### Main Functions

1. **`load_data()`**: Loads candidate data from the binary file at startup
   - Opens `voting_data.dat` in read-binary mode
   - Reads the candidate count first
   - Validates the count (must be 0-10)
   - Reads candidate structures into memory
   - Closes the file

2. **`save_data()`**: Saves current state to the binary file
   - Opens `voting_data.dat` in write-binary mode
   - Writes the candidate count
   - Writes all candidate structures
   - Closes the file

3. **`add_candidate()`**: Registers a new candidate
   - Checks if maximum candidates (10) reached
   - Prompts for candidate name
   - Initializes vote count to 0
   - Increments candidate count
   - Saves data to file

4. **`cast_vote()`**: Allows voting for a candidate
   - Displays all registered candidates with numbers
   - Prompts user for their choice
   - Validates the choice
   - Increments the selected candidate's vote count
   - Saves data to file

5. **`display_results()`**: Shows voting statistics
   - Calculates total votes across all candidates
   - Displays each candidate's name, vote count, and percentage
   - Shows total vote count

6. **`reset_voting()`**: Clears all votes (keeps candidates)
   - Asks for confirmation
   - Sets all vote counts to 0
   - Saves data to file

7. **`clear_all_data()`**: Removes all candidates and votes
   - Asks for confirmation
   - Sets candidate count to 0
   - Saves data to file

#### Program Flow

```
Start
  ↓
Load data from file
  ↓
Display menu
  ↓
┌─────────────────────────────┐
│ 1. Add Candidate            │
│ 2. Cast Vote                │
│ 3. View Results             │
│ 4. Reset Votes              │
│ 5. Clear All Data           │
│ 6. Exit                     │
└─────────────────────────────┘
  ↓
Execute selected action
  ↓
Save data (if modified)
  ↓
Return to menu (unless Exit)
```

### File Format

The binary data file (`voting_data.dat`) stores:
1. An integer (4 bytes) - the candidate count
2. Candidate structures (each = 50 chars + 4 bytes = 54 bytes)

Total file size = 4 + (candidate_count × 54) bytes

### Key Design Decisions

- **Binary file storage**: Chosen for simplicity and efficiency compared to text files
- **Global variables**: Simplifies the code for this small project (candidates array and count)
- **C89 compatibility**: Loop variables declared at function start for older compilers
- **Confirmation prompts**: Prevents accidental data loss for reset/clear operations
- **Input validation**: Checks for valid ranges and prevents buffer overflows

## Compilation

### Using GCC (Linux/Mac)
```bash
gcc -std=c99 voting_system.c -o voting_system
```

### Using MinGW (Windows with Dev-C++)
```bash
"C:\Program Files (x86)\Dev-Cpp\MinGW64\bin\gcc.exe" -std=c99 voting_system.c -o voting_system.exe
```

### Using Clang
```bash
clang -std=c99 voting_system.c -o voting_system
```

### Using MSVC (Visual Studio)
```cmd
cl voting_system.c
```

## Running the Program

### Windows
```bash
voting_system.exe
```

### Linux/Mac
```bash
./voting_system
```

## Usage Example

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

## Project Structure

```
online-voting-system/
├── voting_system.c      # Main source code
├── README.md            # This file
├── .gitignore           # Git ignore rules
└── voting_data.dat      # Binary data file (auto-generated)
```

## Technical Details

### Constants
- `MAX_CANDIDATES`: 10 (maximum number of candidates)
- `MAX_NAME_LENGTH`: 50 (maximum characters in candidate name)
- `DATA_FILE`: "voting_data.dat" (data file name)

### Input Handling
- Uses `scanf(" %[^\n]", ...)` to read names with spaces
- Uses `scanf(" %c", ...)` to read single characters (skips whitespace)
- Integer inputs use standard `scanf("%d", ...)`

### Error Handling
- Checks file open operations
- Validates candidate count range
- Checks array bounds before access
- Confirms destructive operations

## Limitations

- Maximum of 10 candidates
- No user authentication (anyone can vote multiple times)
- Single-user local system (not networked)
- Basic error handling (no recovery from corrupted files)
- No vote history or audit trail
- Command-line interface only (no GUI)

## Future Enhancements

- Add user authentication with unique voter IDs
- Implement network capabilities for remote voting
- Add time-limited voting periods
- Support multiple voting categories/elections
- Export results to CSV or JSON format
- Add vote history and audit logging
- Implement GUI interface
- Add encryption for data security
- Support for weighted voting
- Backup and restore functionality

## Requirements

- C compiler (GCC, Clang, or MSVC)
- Standard C library (stdio.h, stdlib.h, string.h)
- C89 or later standard support

## License

This project is open source and available for educational purposes.

## Author

Created as a beginner-friendly C programming project to demonstrate file I/O, data structures, and menu-driven applications.
