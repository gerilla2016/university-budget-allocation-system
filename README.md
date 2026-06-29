# University Budget Allocation System

## Overview

The University Budget Allocation System is a C program that simulates how a university budget is distributed across academic departments. The program reads department purchase requests from input files, uses a priority queue to give funding priority to departments that have received less money, and generates a report showing approved purchases, skipped requests, and total spending by department.

## Features

- Reads department item requests from input files
- Uses a priority queue to select the department with the lowest total spending
- Processes approved and skipped purchase requests
- Awards scholarship funding when a department has no remaining purchase requests
- Tracks total spending by department
- Generates a final budget allocation report
- Organizes the program using separate C source and header files

## Technologies Used

- C
- Makefile
- Priority Queue
- Queue
- File I/O
- Structs
- Pointers
- Dynamic Memory Allocation

## Project Structure

```text
university-budget-allocation-system
├── README.md
├── .gitignore
├── src
│   ├── driver.c
│   ├── department.h
│   ├── item.h
│   ├── priorityQueueDepartment.c
│   ├── priorityQueueDepartment.h
│   ├── queue.c
│   ├── queue.h
│   ├── resourceManagement.c
│   ├── resourceManagement.h
│   └── makefile
├── sample-input
│   ├── Department-Chemistry.txt
│   ├── Department-ComputerScience.txt
│   ├── Department-Mathematics.txt
│   └── Department-PhysicsAndAstronomy.txt
├── sample-output
│   └── SampleOutput.txt
└── docs
    └── project-overview.pdf
```

## How to Compile

Open a terminal in the `src` folder.

On Windows with MSYS2/MinGW, compile with:

```bash
mingw32-make
```

On macOS/Linux, compile with:

```bash
make
```

## How to Run

From the `src` folder, run:

```bash
./university-budget
```

On Windows, run:

```bash
./university-budget.exe
```

## How to Clean Build Files

From the `src` folder, run:

```bash
mingw32-make clean
```

or on macOS/Linux:

```bash
make clean
```

## Sample Input and Output

Sample department request files are included in the `sample-input` folder. A sample output file is included in the `sample-output` folder.

## What I Practiced

- Implementing data structures in C
- Using priority queues to solve a resource allocation problem
- Reading and processing data from text files
- Organizing a C program with multiple source and header files
- Debugging logic related to queues, spending totals, and file input
- Creating output reports from processed data

## Resume Connection

This project demonstrates C programming, data structures, file input/output, modular program design, memory management, and debugging skills.
