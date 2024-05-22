# Laboratorio-Algoritmi-E-Strutture-Dati

Welcome to the Algorithm and Data Structures Lab repository for the academic year 2023/2024 held by [**Professor Fabio Mogavero**](https://www.docenti.unina.it/#!/professor/464142494f4d4f47415645524f4d475646424138334533314837303341/riferimenti).

## Prerequisites
- Ensure you have `g++` and `make` installed on your system to compile and run the code.
- Optional: `valgrind` for memory debugging. [Official site](https://valgrind.org).

## How to Compile and Run
Navigate to the desired directory and execute the following in your terminal:

```bash
make && ./main
```

For memory debugging with `valgring`, update the `Makefile` by removing `-f-sanitize=address` from the `CXXFLAGS`, then run:

```bash
make && valgrind -s --leak-check=full --show-leak-kinds=all --track-origins=yes ./main
```

## Cleaning Up
To remove all `.o` files given in output, use:

```bash
make clean
```

## Exercise Details
Each exercise is designed to give you practical experience with the fundamental and complex structures in computer science.

### Exercise 1: Implementing Basic Data Structures
Develop four C++ libraries for managing dynamic data structures such as Vector, List, Stack, and Queue containing generic data types like integers, strings, etc. For Stacks and Queues, implement two versions using (a) vectors with efficient automatic resizing and (b) lists.

#### Functional Requirements
1. **Construction and Destruction**: Build and teardown a data structure.
2. **Assignment and Comparison**: Perform assignment and comparison operations between different instances of the same structure.
3. **Common Operations**: 
   - Emptiness check
   - Size reading
   - Clearing the structure
4. **Operations for Vectors and Lists**: 
   - Non-destructive access to the initial, final, or a specific indexed element
   - Data existence check
   - Application of functions across elements (map functions)
   - Value traversal and accumulation (traverse and fold functions)
5. **Operations for Stacks and Queues**: 
   - Insertion of an element
   - Removal, removal with read, and non-destructive read of the next accessible element
6. **Specific Functions for Vectors**: 
   - Resizing of the vector
7. **Specific Functions for Lists**: 
   - Insertion of a value at the beginning or end
   - Removal and removal with read from the beginning
   - Dictionary management operations


### Exercise 2: Implementing Binary Trees and Binary Search Trees
Develop two C++ libraries for managing dynamic data structures of binary trees and binary search trees containing generic data types such as integers, strings, etc. Specifically:
- The binary tree should be implemented using two concrete representations: (1) a vector of nodes, and (2) pointers to nodes.
- The binary search tree should use a representation explicitly as a binary tree through pointers to nodes.

#### Functional Requirements
1. **Construction and Destruction**: Build and teardown of a data structure.
2. **Assignment and Comparison**: 
   - Perform assignment and comparison operations between different instances of a structure.
   - For arbitrary binary trees, enable comparisons irrespective of the concrete representation.
3. **Common Operations for Both Structures**:
   - Existence check for a specific value.
   - Traversal and accumulation of values in breadth-first, pre-order, in-order, and post-order (traverse and fold functions).
   - Emptiness test.
   - Size reading.
   - Clearing the structure.
   - Node property queries (read/write access to data, existence and access to left/right child).
   - Navigation using iterators.
4. **Specific Functions for Binary Trees**:
   - Application of a function in breadth-first, pre-order, in-order, and post-order to all elements (map functions).
5. **Specific Functions for Binary Search Trees**:
   - Insertion/deletion of elements.
   - Removal, removal with read, and non-destructive read of the minimum/maximum element or the predecessor/successor of a given element.

### Exercise 3: Implementing a Hash Table Library
Develop a C++ library for managing a dynamic hash table data structure containing generic data types such as integers, strings, etc. This structure should be implemented using the following two conflict resolution techniques:
1. Closed addressing / open hashing / chaining.
2. Open addressing / closed hashing.

#### Functional Requirements
1. **Construction and Destruction**: Build and teardown of the data structure.
2. **Assignment and Comparison**: Perform assignment and comparison operations between different instances of the data structure.
3. **Specific Operations of the Data Structure**: 
   - Table resizing.
   - Dictionary management operations.
4. **Generic Operations on the Data Structure**:
   - Existence check for a specific value.
   - Emptiness test.
   - Size reading.
   - Clearing the structure.


## Credits

This project was solely developed by **Davide Gargiulo**. No external libraries were used in the development of the exercises contained within this repository.

<div align="center">

### Developed By
[Davide Gargiulo](https://github.com/DavideGargiulo)  
<img src="https://avatars2.githubusercontent.com/u/107481480?v=4&s=100" alt="Davide Gargiulo"/>  
[📝](https://github.com/DavideGargiulo) [💻](https://github.com/DavideGargiulo/Laboratorio-Algoritmi-E-Strutture-Dati/commits?author=DavideGargiulo) [📖](https://github.com/DavideGargiulo/Laboratorio-Algoritmi-E-Strutture-Dati/blob/main/README.md)

</div>

### Special Thanks
Special thanks to [**Professor Fabio Mogavero**](https://www.docenti.unina.it/#!/professor/464142494f4d4f47415645524f4d475646424138334533314837303341/riferimenti) for guidance and providing the educational framework for the project.

## License

For the full terms and conditions, see the [LICENSE](LICENSE) file in this repository.
