#define UNICODE
#include <windows.h>
#include <shlobj.h> // Para la función SHBrowseForFolder
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

// Función para abrir el cuadro de diálogo y seleccionar una carpeta
std::wstring select_folder() {
    BROWSEINFO bi = {0};
    bi.lpszTitle = L"Selecciona una carpeta"; // Título del cuadro de diálogo

    // Abrir el cuadro de diálogo
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != 0) {
        // Obtener la ruta seleccionada
        wchar_t path[MAX_PATH];
        if (SHGetPathFromIDList(pidl, path)) {
            CoTaskMemFree(pidl);
            return path; // Retorna la ruta de la carpeta seleccionada
        }
    }
    return L""; // Si no se seleccionó nada
}

// Función para mover los archivos según su fecha
void move_files_by_date(const fs::path& source_folder, const fs::path& destination_folder) {
    try {
        // Verificar si la carpeta de destino existe, si no, crearla
        if (!fs::exists(destination_folder)) {
            fs::create_directories(destination_folder);
        }

        std::vector<fs::directory_entry> files;

        // Leer todos los archivos en la carpeta origen
        for (const auto& entry : fs::directory_iterator(source_folder)) {
            if (fs::is_regular_file(entry.status())) {
                files.push_back(entry);
            }
        }

        // Ordenar los archivos por fecha de modificación
        std::sort(files.begin(), files.end(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
            return fs::last_write_time(a) < fs::last_write_time(b);
        });

        // Mover los archivos a la carpeta destino, creando subcarpetas por fecha
        for (const auto& file : files) {
            auto last_write_time = fs::last_write_time(file);
            auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                last_write_time - fs::file_time_type::clock::now() +std::chrono::system_clock::now());
            std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);

            // Convertir la fecha en formato "dd_mm_yyyy"
            std::tm tm = *std::localtime(&cftime);
            char date_str[100];
            strftime(date_str, sizeof(date_str), "%d-%m-%Y", &tm);

            // Crear una subcarpeta con la fecha de la última modificación
            fs::path date_folder = destination_folder / date_str;
            if (!fs::exists(date_folder)) {
                fs::create_directory(date_folder);
            }

            // Mover el archivo a la subcarpeta correspondiente
            fs::path destination_file = date_folder / file.path().filename();
            fs::rename(file.path(), destination_file);

            std::wcout << L"Archivo movido: " << file.path() << L" -> " << destination_file << std::endl;
        }

    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    // Abrir el cuadro de selección de carpeta para la carpeta origen
    std::wcout << L"Selecciona la carpeta origen:" << std::endl;
    std::wstring source_folder = select_folder();
    if (source_folder.empty()) {
        std::wcout << L"No se seleccionó una carpeta origen. Saliendo..." << std::endl;
        return 1;
    }

    // Abrir el cuadro de selección de carpeta para la carpeta destino
    std::wcout << L"Selecciona la carpeta destino:" << std::endl;
    std::wstring destination_folder = select_folder();
    if (destination_folder.empty()) {
        std::wcout << L"No se seleccionó una carpeta destino. Saliendo..." << std::endl;
        return 1;
    }

    // Llamar a la función para mover los archivos
    move_files_by_date(source_folder, destination_folder);

return 0;
}