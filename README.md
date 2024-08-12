# Pokedex System in C

## Overview

This repository contains the implementation of a Pokedex system using the C programming language. The project demonstrates advanced programming concepts, including dynamic memory management, pointers, and struct usage in C.

## Project Description

The project involves creating a Pokedex system that stores and manipulates data about various Pokemon and their types. The system allows for the creation, deletion, and querying of Pokemon and type data, emphasizing efficient memory management and correct use of pointers.

### Key Features

- **Pokemon and Type Structures:**
  - Each Pokemon has attributes such as name, species, height, weight, attack, and type.
  - Each type has a name, effectiveness against other types, and a list of types effective against it.
  
- **Dynamic Memory Management:**
  - Efficient allocation and deallocation of memory for Pokemon and types.
  - Use of dynamic arrays to store lists of Pokemon and types, allowing for flexible and efficient memory usage.

### Functionalities

- **Creating and Managing Pokemon and Types:**
  - Create new Pokemon and type objects dynamically.
  - Add and remove effectiveness relationships between types.
  
- **Querying Data:**
  - Print information about all Pokemon and types.
  - Query Pokemon by name or type.
  
- **Memory Management:**
  - Ensure no memory leaks by properly freeing all allocated memory.
  - Use tools like `valgrind` to detect and fix memory issues.

## Getting Started

To compile and run the project, follow these steps:

1. **Clone the repository:**
    ```
    git clone https://github.com/Yarin-Shohat/Pokemon.git
    ```
2. **Navigate to the project directory:**
    ```
    cd Pokemon
    ```
3. **Compile the project:**
    ```
    make
    ```
4. **Run the executable:**
    ```
    ./Pokedex <numberOfTypes> <numberOfPokemons> <configurationFile>
    ```

## Project Structure

- `Pokemon.h`: Contains the struct definitions and function prototypes related to Pokemon.
- `Pokemon.c`: Implements the functions for creating, deleting, and managing Pokemon.
- `Pokedex.c`: Contains the main function and overall program logic.
- `Defs.h`: Contains general definitions and enumerations used throughout the project.

### Example Configuration File

```
Types
Fire,Water,Electric,Grass
Fire effective-against-me:Water
Fire effective-against-other:Grass,Electric
Electric effective-against-other:Water

Pokemons
Pikachu,MousePokemon,0.4,6,55,Electric
Charmander,LizardPokemon,0.6,8.5,52,Fire
Ponyta,FireHorsePokemon,1.0,30.0,85,Fire
Squirtle,TinyTurtlePokemon,0.5,9,48,Water
Psyduck,DuckPokemon,0.8,19.6,52,Water
```

## Memory Management

The project focuses on dynamic memory management:
- **Allocation:** Using `malloc` and `calloc` for allocating memory dynamically.
- **Deallocation:** Ensuring all allocated memory is freed using `free` to prevent memory leaks.
- **Error Handling:** Checking the success of memory allocation and handling errors gracefully.

### Tools for Memory Management

- **Valgrind:** Use Valgrind to check for memory leaks and errors.
    ```
    valgrind --leak-check=full ./Pokedex <numberOfTypes> <numberOfPokemons> <configurationFile>
    ```

## Contribution

Contributions are welcome! Fork the repository and create a pull request with your improvements or bug fixes.
