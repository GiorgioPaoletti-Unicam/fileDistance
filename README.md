# FileDistance - A File Comparison Tool

This repository contains the implementation of a utility called `FileDistance`. It is designed to compute the "distance" between two files. In this context, the distance refers to the number of operations needed to transform one file into another. The operations include adding a byte, deleting a byte, and modifying a byte.

## 📃 Features

The program offers three primary functionalities:

1. **Calculate the distance between two files:** Use the `distance` command as follows: `filedistance distance file1 file2`. The output will be in the form: `EDIT DISTANCE: distance TIME: computation time`.

2. **Save the sequence of instructions:** Use the `distance` command as follows: `filedistance distance file1 file2 output`. The output, in the form of instructions, will be saved in the `output` file.

3. **Apply instructions to the first file to obtain the second file:** Use the `apply` command as follows: `filedistance apply inputfile filem outputfile`. The instructions contained in the `filem` are applied to `inputfile`, and the result is saved in `outputfile`.

## 📁 Data Structures

The following data structures have been used to develop these functionalities:

- `byte_list_t`: Enables storing the bytes contained in a file without knowing its length.

- `edit_matrix_t`: Enables storing an integer matrix representing the edit matrix. It also contains two `byte_list_t`, storing the bytes of the two files from which the matrix was generated.

- `edit_instruction_t`: Enables storing an instruction extracted from the edit matrix.

## 📚 Libraries

The project is structured around several libraries, each providing specific functionalities:

- **list.h**: Provides methods for creating, destroying, getting an element from, and getting the size of a `byte_list_t`.

- **edit.h**: Provides methods for creating and destroying an `edit_matrix_t`, getting the edit distance linked to the two files to which the matrix belongs, generating instruction files, and applying instructions file.

- **edit_instruction.h**: Provides methods for creating and destroying an `edit_instruction_t`.

## ⚙️ Build

The project build is done using a CMake script.

## ✉️ Contact

For any questions or clarifications regarding this project, please contact Giorgio Paoletti at [email].

## ⚖️ License

This project is licensed under the MIT License. See the `LICENSE` file for details.
