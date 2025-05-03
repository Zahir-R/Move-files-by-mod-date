## Move Files by Mod-Date

A simple C++ script that moves files from one folder to another based on their modification dates. Ideal for organizing files such as photos or documents in a structured way by date.

## Features

- Select an **origin folder** (where the files are).
- Select a **destination folder** (where the files will be moved).
- Automatically creates subfolders by **modification date** (e.g., "15-03-2021").
- Moves files into the corresponding folder based on their last modification date.

## Requirements

- **Windows** OS
- **C++17** or higher
- A C++ compiler (e.g., MSVC, MinGW)

## How to Use

1. Download or clone the repository.
2. Compile the C++ source code.
3. Run the compiled program.
4. Select the **origin folder** and the **destination folder** when prompted.
5. The program will create subfolders in the destination folder, organized by the modification date of each file, and move the files accordingly.

## How to Compile

To compile the C++ code, you can use any modern C++ compiler. Here's an example using **MinGW**:

```bash
g++ -o move_files move_files.cpp
```
After compilation, run the resulting executable (move_files.exe)

## License
This project is licensed under MIT License - see the LICENSE file for details.

## Contributing
Feel free to fork the project and send pull requests with improvements or fixes.
Contributions are welcome!

## Author
Zahir-R
