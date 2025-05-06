#define UNICODE
#include <windows.h>
#include <shlobj.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

namespace fs = std::filesystem;

// Categorías de extensiones
const std::set<std::wstring> image_exts = {L".jpg", L".jpeg", L".png", L".bmp", L".gif", L".tiff"};
const std::set<std::wstring> video_exts = {L".mp4", L".avi", L".mov", L".mkv", L".wmv"};
const std::set<std::wstring> document_exts = {L".pdf", L".doc", L".docx", L".xls", L".xlsx", L".ppt", L".pptx", L".txt"};

// Determinar tipo de archivo
std::wstring get_file_category(const std::wstring& extension) {
    std::wstring ext = extension;
    std::transform(ext.begin(), ext.end(), ext.begin(), ::towlower); // convertir a minúscula

    if (image_exts.count(ext)) return L"Fotos";
    if (video_exts.count(ext)) return L"Videos";
    if (document_exts.count(ext)) return L"Documentos";
    return L"Otros";
}

std::wstring select_folder() {
    BROWSEINFO bi = {0};
    bi.lpszTitle = L"Selecciona una carpeta";

    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != nullptr) {
        wchar_t path[MAX_PATH];
        if (SHGetPathFromIDList(pidl, path)) {
            std::wstring result(path);
            IMalloc* imalloc = nullptr;
            if (SUCCEEDED(SHGetMalloc(&imalloc))) {
                imalloc->Free(pidl);
                imalloc->Release();
            }
            return result;
        }
        IMalloc* imalloc = nullptr;
        if (SUCCEEDED(SHGetMalloc(&imalloc))) {
            imalloc->Free(pidl);
            imalloc->Release();
        }
    }
    return L"";
}

bool confirm_move(const std::vector<fs::directory_entry>& files) {
    std::wstring message = L"Los siguientes archivos serán movidos:\n";
    for (const auto& file : files) {
        message += file.path().wstring() + L"\n";
    }
    message += L"\n¿Desea continuar?";

    int result = MessageBox(NULL, message.c_str(), L"Confirmación", MB_YESNO | MB_ICONQUESTION);
    return (result == IDYES);
}

void move_files_by_date(const fs::path& source_folder, const fs::path& destination_folder) {
    try {
        if (!fs::exists(destination_folder)) {
            fs::create_directories(destination_folder);
        }

        std::vector<fs::directory_entry> files;
        for (const auto& entry : fs::directory_iterator(source_folder)) {
            if (fs::is_regular_file(entry.status())) {
                files.push_back(entry);
            }
        }

        if (!files.empty() && confirm_move(files)) {
            std::sort(files.begin(), files.end(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
                return fs::last_write_time(a) < fs::last_write_time(b);
            });

            for (const auto& file : files) {
                auto last_write_time = fs::last_write_time(file);
                auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                    last_write_time - fs::file_time_type::clock::now() + std::chrono::system_clock::now());
                std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);

                std::tm tm = *std::localtime(&cftime);
                char date_str[100];
                strftime(date_str, sizeof(date_str), "%d-%m-%Y", &tm);

                // Determinar categoría del archivo
                std::wstring category = get_file_category(file.path().extension().wstring());

                // Crear carpeta destino incluyendo categoría y fecha
                fs::path date_folder = destination_folder / category / date_str;
                if (!fs::exists(date_folder)) {
                    fs::create_directories(date_folder);
                }

                fs::path filename = file.path().filename();
                fs::path destination_file = date_folder / filename;

                // Manejo de colisión de nombres
                int counter = 1;
                while (fs::exists(destination_file)) {
                    std::wstring stem = filename.stem().wstring();
                    std::wstring extension = filename.extension().wstring();
                    destination_file = date_folder / fs::path(stem + L"_" + std::to_wstring(counter) + extension);
                    ++counter;
                }

                fs::rename(file.path(), destination_file);
                std::wcout << L"Archivo movido: " << file.path() << L" -> " << destination_file << std::endl;
            }
        } else {
            std::wcout << L"Operación cancelada.\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    CoInitialize(NULL);

    std::wcout << L"Selecciona la carpeta origen:\n";
    std::wstring source_folder = select_folder();
    if (source_folder.empty()) {
        std::wcout << L"No se seleccionó carpeta origen.\n";
        return 1;
    }

    std::wcout << L"Selecciona la carpeta destino:\n";
    std::wstring destination_folder = select_folder();
    if (destination_folder.empty()) {
        std::wcout << L"No se seleccionó carpeta destino.\n";
        return 1;
    }

    move_files_by_date(source_folder, destination_folder);

    CoUninitialize();
    return 0;
}
