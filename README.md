# Fauxtoshop 🖼️🔄

## 📌 Project Overview

Fauxtoshop is a **C-based image processing program** that allows users to rotate BMP images **90° clockwise**. It reads a BMP file, processes its pixel data, and outputs a rotated version while maintaining the original BMP format and structure.

## 🚀 Features

- Reads BMP image files as input.
- Rotates images **90° clockwise**.
- Preserves the BMP file structure and metadata.
- Efficiently processes **24-bit BMP images**.
- Outputs the rotated image as a new BMP file.

## 🛠️ Technologies Used

- **Programming Language:** C
- **File Handling:** Reads and writes BMP files.
- **Memory Management:** Utilizes dynamic memory allocation to handle image data.

## 📂 File Structure

```
/Fauxtoshop
 ├── src
 │   ├── fauxtoshop.c         # Main C program
 │
 ├── test
 │   ├── input.bmp            # Sample input BMP file
 │   ├── output.bmp           # Expected output BMP file
 │
 ├── README.md                # Project documentation
```

## 🏃‍♂️ How to Use

### **1. Compilation**

To compile the program, use the following GCC command:

```sh
gcc -O3 -Wall -Wextra -Werror -pedantic -o fauxtoshop src/fauxtoshop.c
```

### **2. Execution**

Run the program by providing an input BMP file and redirecting the output to a new file:

```sh
./fauxtoshop < test/input.bmp > test/output.bmp
```

This command rotates `input.bmp` and saves the transformed image as `output.bmp`.

### **3. Example Usage**

#### **Before Rotation (Input BMP):** 🖼️
```
⬜⬛⬜⬛⬜⬛
⬛⬜⬛⬜⬛⬜
⬜⬛⬜⬛⬜⬛
⬛⬜⬛⬜⬛⬜
⬜⬛⬜⬛⬜⬛
⬛⬜⬛⬜⬛⬜
```

⬇ **After Running Fauxtoshop** ⬇

#### **After Rotation (Output BMP):** 🔄
```
⬛⬜⬛⬜⬛⬜
⬜⬛⬜⬛⬜⬛
⬛⬜⬛⬜⬛⬜
⬜⬛⬜⬛⬜⬛
⬛⬜⬛⬜⬛⬜
⬜⬛⬜⬛⬜⬛
```

## 🔍 Edge Cases Considered

- **Non-BMP files:** The program verifies that the input file is in BMP format.
- **Invalid BMP headers:** Ensures compliance with the Windows 3.x BMP standard.
- **Empty or Corrupt Images:** Implements error handling for incomplete or malformed BMP files.

## 🎯 Future Improvements

- Support for **grayscale and additional color depths**.
- Extend functionality to rotate images **180° and 270°**.
- Introduce a **graphical user interface (GUI)** for enhanced usability.

## 📜 License

This project is licensed under the **MIT License**.

## 👤 Author

**Giorgos Theodorou**