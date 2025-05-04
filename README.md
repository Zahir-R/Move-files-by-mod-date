# Move Files by Mod-Date

A simple C++ program that organizes files by moving them from one folder to another based on their modification dates. This tool is ideal for organizing files such as photos, videos, or documents in a structured way by date.

---

## Features

- **Select an origin folder**: Choose the folder where the files are located.
- **Select a destination folder**: Choose the folder where the files will be moved.
- **Automatically create subfolders by modification date**: The program creates subfolders with names based on the modification date (e.g., "15-03-2021").
- **Move files into the corresponding folder**: Files are moved to the appropriate subfolder based on their last modification date.

---

## Requirements

- **Operating System**: Windows
- **C++17** or higher
- A compatible C++ compiler (e.g., **MSVC**, **MinGW**, or **Clang**)

---

## How to Use

1. **Download or clone** the repository to your local machine.
2. **Compile the C++ source code** using a modern C++ compiler (instructions below).
3. **Run the compiled program** (`move_files.exe`).
4. When prompted, select the **origin folder** (where the files are).
5. Select the **destination folder** (where the files will be moved).
6. The program will automatically create subfolders in the destination folder named by the file's **modification date** (e.g., "15-03-2021") and move the files into the appropriate subfolders.

## How to Compile

To compile the C++ code, you need a **C++17** compatible compiler.

### Using MinGW:

1. Install MinGW or any other compatible C++17 compiler (e.g., **MSVC** or **Clang**).
2. Open your terminal or command prompt.
3. Navigate to the folder where the source code is located.
4. Run the following command to compile the program:

```bash
g++ -o move_files move_files.cpp
```

5. After compilation, you can run the resulting executable (move_files.exe) from your terminal or command prompt.

## Error Handling
- Permissions Issues: Make sure the program has permission to read from the origin folder and write to the destination folder. If not, run the program as an administrator.
- File Name Conflicts: If a file with the same name already exists in the destination folder, the program will add a numeric suffix (e.g., IMG_20250303_1.jpg) to prevent overwriting.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Contributing
Feel free to fork the project and submit pull requests with any improvements, bug fixes, or features you would like to add. Contributions are always welcome!

## Author
Zahir-R
