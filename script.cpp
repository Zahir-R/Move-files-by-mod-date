#define UNICODE
#include <windows.h>
#include <shlobj.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <string>

namespace fs = std::filesystem;

// Open chart and select a folder
std::wstring select_folder() {
    BROWSEINFO bi = {0};
    bi.lpszTitle = L"Select a folder";

    // Open dialog box
    LPITEMIDLIST pidl = SHBrowseForFolder(&bi);
    if (pidl != nullptr) {
        // Get path
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

// Function to show a message box for confirmation
bool confirm_move(const std::vector<fs::directory_entry>& files) {
    std::wstring message = L"The following files will be moved:\n";
    
    for (const auto& file : files) {
        message += file.path().wstring() + L"\n";
    }
    
    message += L"\nDo you want to continue?";
    
    // Display the message box with YES and NO options
    int result = MessageBox(
        NULL,
        message.c_str(),
        L"Confirm Move",
        MB_YESNO | MB_ICONQUESTION
    );

    // If YES is clicked, result will be IDYES
    return (result == IDYES);
}

// Move files based on the dates
void move_files_by_date(const fs::path& source_folder, const fs::path& destination_folder) {
    try {
        // Create a folder if it does not exist
        if (!fs::exists(destination_folder)) {
            fs::create_directories(destination_folder);
        }

        std::vector<fs::directory_entry> files;

        // Read all files in the source folder
        for (const auto& entry : fs::directory_iterator(source_folder)) {
            if (fs::is_regular_file(entry.status())) {
                files.push_back(entry);
            }
        }

        // If there are files, ask the user for confirmation
        if (!files.empty() && confirm_move(files)) {
            // Sort files by modification date
            std::sort(files.begin(), files.end(), [](const fs::directory_entry& a, const fs::directory_entry& b) {
                return fs::last_write_time(a) < fs::last_write_time(b);
            });

            // Move the files to the destination folder, creating subfolders by date
            for (const auto& file : files) {
                auto last_write_time = fs::last_write_time(file);
                auto sctp = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
                    last_write_time - fs::file_time_type::clock::now() + std::chrono::system_clock::now());
                std::time_t cftime = std::chrono::system_clock::to_time_t(sctp);

                // Convert date format to "dd_mm_yyyy"
                std::tm tm = *std::localtime(&cftime);
                char date_str[100];
                strftime(date_str, sizeof(date_str), "%d-%m-%Y", &tm);

                // Create a subfolder with the last modification date
                fs::path date_folder = destination_folder / date_str;
                if (!fs::exists(date_folder)) {
                    fs::create_directory(date_folder);
                }

                // Move the file to the subfolder
                fs::path filename = file.path().filename();
                fs::path destination_file = date_folder / filename;
                
                // If file exists, add a numeric suffix before extension
                int counter = 1;
                while (fs::exists(destination_file)) {
                    std::wstring stem = filename.stem().wstring();
                    std::wstring extension = filename.extension().wstring();
                    destination_file = date_folder / fs::path(stem + L"_" + std::to_wstring(counter) + extension);
                    ++counter;
                }
                
                // Move the file
                fs::rename(file.path(), destination_file);

                std::wcout << L"File moved: " << file.path() << L" -> " << destination_file << std::endl;
            }
        } else {
            std::wcout << L"File move operation canceled.\n";
        }

    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    CoInitialize(NULL);
    
    std::wcout << L"Select the source folder:" << std::endl;
    std::wstring source_folder = select_folder();
    if (source_folder.empty()) {
        std::wcout << L"No source folder selected." << std::endl;
        return 1;
    }

    std::wcout << L"Select the destination folder:" << std::endl;
    std::wstring destination_folder = select_folder();
    if (destination_folder.empty()) {
        std::wcout << L"No destination folder selected." << std::endl;
        return 1;
    }

    move_files_by_date(source_folder, destination_folder);

    CoUninitialize();
    return 0;
}
