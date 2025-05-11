# Mover archivos por Fecha de Modificación

## 🇪🇸 Español
*(Leer versión en inglés más abajo)*

Un programa sencillo de C++ que organiza archivos moviéndolos de una carpeta a otra en base a sus fechas de modificación y tipo de archivo. Esta herramienta es ideal para organizar archivos como fotos, videos, o documentos de forma estructurada por su fecha.

---

## Funcionalidades

- **Selecciona una carpeta origen**: Elige la carpeta en donde están los archivos.
- **Selecciona una carpeta destino**: Elige la carpeta en donde los archivos serán movidos.
- **Crea subcarpetas automáticamente por su fecha de modificación y extensión**: El programa crea subcarpetas con nombres según el tipo de archivo encontrado y la fecha de modificación (por ejemplo, "Fotos/05-05-2025").
- **Mover archivos a la subcarpeta correspondiente**: Los archivos son movidos a la subcarpeta en base a su categoría y fecha de modificación (Las categorías se basan en la extensión del archivo: por ejemplo, .jpg y .png se agrupan como Fotos, .mp4 y .avi como Videos).

---

## Requisitos

- **Sistema Operativo**: Windows
- **C++17** o superior
- Un compilador compatible con C++ (Por ejemplo, **MSVC**, **MinGW**, o **Clang**)

---

## Cómo usar

1. **Descarga o clona** el repositorio a tu equipo local.
2. **Compila el código fuente C++** usando un compilador de C++ moderno (instrucciones abajo).
3. **Ejecuta el programa compilado** (`mover_archivos.exe`).
4. Al ejecutarse, selecciona la **carpeta origen** (donde están los archivos).
5. Selecciona la **carpeta destino** (donde se moverán los archivos).
6. El programa creará subcarpetas automáticamente en la carpeta destino con nombre de la **categoría y la fecha de modificación** del archivo (por ejemplo, "Fotos/05-05-2025") y moverá los archivos a las subcarpetas apropiadas.

## Cómo compilar

Para compilar el código C++, necesitas un compilador compatible con **C++17**.

### Usando MinGW:

1. Instala MinGW.
2. Abre tu terminal o Símbolo del Sistema.
3. Navega a la carpeta donde está el código fuente.
4. Ejecuta el siguiente comando para compilar el programa:

```bash
g++ -o mover_archivos mover_archivos.cpp
```

Nota: El programa utiliza funciones Unicode de Windows, por lo tanto si estás usando MinGW, asegúrate de compilar con el flag `-municode`. Además, asegúrate de usar el estándar `C++17` o superior:

```bash
g++ -std=c++17 -municode -o mover_archivos mover_archivos.cpp
```

5. Después de la compilación, puedes ejecutar el ejecutable resultante (mover_archivos.exe) desde tu terminal o Símbolo del sistema.

## Manejo de errores
- Permisos: Asegúrate de que el programa tiene permisos para leer la carpeta origen y de escribir en la carpeta destino. Si no, ejecuta el programa como administrador.
- Conflictos de Nombres: Si un archivo con el mismo nombre ya existe en la carpeta destino, el programa añadirá un sufijo numérico (por ejemplo, IMG_20250505_1.jpg) para prevenir la sobreescritura.

## Licencia
Este proyecto está bajo la licencia MIT. Ver el archivo LICENSE para detalles.

## Contribuciones
Siéntete libre de bifurcar el proyecto y enviar solicitudes de incorporación de cambios con cualquier mejora, corrección de errores o funcionalidad que quieras añadir. Las contribuciones siempre son bienvenidas!

## Autor
Zahir-R

## 🇬🇧 English
*(See Spanish version above)*

A simple C++ program that organizes files by moving them from one folder to another based on their modification dates and file type. This tool is ideal for organizing files such as photos, videos, or documents in a structured way by date.

---

## Features

- **Select an origin folder**: Choose the folder where the files are located.
- **Select a destination folder**: Choose the folder where the files will be moved.
- **Automatically create subfolders by modification date and extension**: The program creates subfolders with names based on the type of file found and their modification date (e.g., "Fotos/05-05-2025").
- **Move files into the corresponding folder**: Files are moved to the appropriate subfolder based on their category and their last modification date (categories are based on file extension: for example, .jpg and .png are grouped as Fotos, .mp4 and .avi as Videos).

---

## Requirements

- **Operating System**: Windows
- **C++17** or higher
- A compatible C++ compiler (e.g., **MSVC**, **MinGW**, or **Clang**)

---

## How to Use

1. **Download or clone** the repository to your local machine.
2. **Compile the C++ source code** using a modern C++ compiler (instructions below).
3. **Run the compiled program** (`mover_archivos.exe`).
4. When prompted, select the **origin folder** (where the files are).
5. Select the **destination folder** (where the files will be moved).
6. The program will automatically create subfolders in the destination folder named by the file's **modification date** (e.g., "15-03-2021") and move the files into the appropriate subfolders.

## How to Compile

To compile the C++ code, you need a **C++17** compatible compiler.

### Using MinGW:

1. Install MinGW.
2. Open your terminal or command prompt.
3. Navigate to the folder where the source code is located.
4. Run the following command to compile the program:

```bash
g++ -o mover_archivos mover_archivos.cpp
```

Note: This program uses Windows Unicode functions, so if you're using MinGW, make sure to compile with the `-municode` flag. Also, be sure to use the `C++17` standard or higher:

```bash
g++ -std=c++17 -municode -o mover_archivos mover_archivos.cpp
```

5. After compilation, you can run the resulting executable (mover_archivos.exe) from your terminal or command prompt.

## Error Handling
- Permissions: Make sure the program has permission to read from the origin folder and write to the destination folder. If not, run the program as an administrator.
- File Name Conflicts: If a file with the same name already exists in the destination folder, the program will add a numeric suffix (e.g., IMG_20250505_1.jpg) to prevent overwriting.

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Contributing
Feel free to fork the project and submit pull requests with any improvements, bug fixes, or features you would like to add. Contributions are always welcome!

## Author
Zahir-R
