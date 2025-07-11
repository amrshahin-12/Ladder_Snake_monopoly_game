# Snake and Ladders Game (C++)

This is a C++ implementation of the classic board game **Snakes and Ladders**, featuring a graphical user interface using the **CMU Graphics Library**.

---

## Features

- Playable Snakes and Ladders board game  
- Multiple player support  
- Cards, ladders, and snakes with various effects  
- Graphical interface powered by CMUgraphicsLib  
- Modular code structure for easy extension and maintenance  

---

## Project Structure

- `Main.cpp` — Entry point of the application  
- `ApplicationManager.*` — Manages overall game flow and actions  
- `Grid.*` — Represents the game board  
- `Player.*` — Player logic and data  
- `Card.cpp/h` — Different card types and their effects  
- `Ladder.*`, `Snake.*` — Board objects  
- `Input.*`, `Output.*` — Handle user input and graphical output  
- `CMUgraphicsLib/` — Third-party graphics library (includes JPEG support)  

---

## Getting Started

### Prerequisites

- C++ compiler (e.g., `g++`, MSVC)  
- CMU Graphics Library (included in `CMUgraphicsLib/` folder)  

### Build Instructions

Clone the repository:

```bash
git clone <your-repo-url>
cd <repo-folder>
