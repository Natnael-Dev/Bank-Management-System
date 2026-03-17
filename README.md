# 🏦 Natnael International Bank — Management System

A console-based Bank Management System written in **C++**, built as a personal learning project to practice core programming concepts including structs, file I/O, functions, and modular design. The system simulates real banking operations and persists all data using binary file storage.

---

## 📌 Project Overview

This program runs entirely in the terminal/command prompt and allows users to create and manage bank accounts, perform financial transactions, and view account records — all without needing a database or internet connection. Data is saved to a local binary file (`filename.bin`) so records survive between program runs.

---

## ✨ Features

- **Create Account** — Register a new bank account with a name, account number, and opening balance
- **Deposit** — Add funds to any existing account
- **Withdraw** — Remove funds with overdraft protection (cannot withdraw more than the balance)
- **Transfer** — Send money between two accounts with full validation
- **View Account** — Look up a specific account by account number
- **Modify Account** — Update account holder details
- **Delete Account** — Permanently remove an account from the system
- **List All Accounts** — Display a neatly formatted table of all registered accounts
- **Persistent Storage** — All data is saved to `filename.bin` automatically on every change
- **Input Validation** — All numeric inputs are validated; invalid entries prompt the user to re-enter

---

## 🛠️ Tech Stack

| Component | Details |
|---|---|
| Language | C++ (C++11 or later) |
| IDE | Code::Blocks (recommended) |
| Compiler | GCC / g++ (MinGW on Windows) |
| Storage | Binary file I/O (`fstream`) |
| UI | Console / terminal (no external libraries) |

---

## 🚀 How to Compile & Run

### ▶️ Windows (Code::Blocks — Recommended)

1. Download or clone this repository
2. Open **Code::Blocks**
3. Go to **File → Open** and select `project.cpp`
4. Click the green **Build and Run** button (or press `F9`)
5. The program will launch in the terminal window

> 💡 Make sure you have **MinGW** installed and configured in Code::Blocks as the compiler.

---

### ▶️ Windows (Command Prompt / PowerShell)

```bash
g++ project.cpp -o project.exe
project.exe
```

---

### ▶️ Linux

```bash
g++ project.cpp -o project
./project
```

---

### ▶️ macOS

```bash
g++ project.cpp -o project
./project
```

> ⚠️ On macOS, if `g++` is not found, install Xcode Command Line Tools:
> ```bash
> xcode-select --install
> ```

---

## 📁 Folder Structure

```
BankManagementSystem/
│
├── project.cpp          # Full source code (single file)
├── .gitignore           # Excludes binaries and runtime data from Git
└── README.md            # This file
```

> **Note:** `filename.bin` (the data file) is intentionally excluded from this repository via `.gitignore`. It will be created automatically the first time you run the program.

---

## 🔮 Future Features

These are planned improvements for future versions of this project:

- [ ] **Login system** — Password-protect accounts with encrypted PIN storage
- [ ] **Transaction history** — Log and display a full history of deposits, withdrawals, and transfers per account
- [ ] **Interest calculator** — Automatically apply monthly interest to savings accounts
- [ ] **Admin vs User roles** — Separate access levels for bank staff and customers
- [ ] **Search by name** — Look up accounts by account holder name, not just account number
- [ ] **GUI interface** — Migrate from console to a graphical UI using a framework like Qt
- [ ] **CSV/text export** — Export account summaries to a readable `.csv` or `.txt` file
- [ ] **Multiple account types** — Support for savings, checking, and loan accounts

---

## 👨‍💻 Author

**Natnael Tezazu**

Built as part of a personal C++ learning journey — practicing real-world programming concepts through a practical project.

---

## 📄 License

This project is open source and available for educational use.