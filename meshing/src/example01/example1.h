#pragma once

#include <filesystem>
#include <fstream>
#include <stack>
#include <string>
#include <vector>



inline bool make_file_writable(const std::string& filename)
{
    std::filesystem::path filepath(filename);

    if (std::filesystem::exists(filepath) && std::filesystem::is_regular_file(filepath))
        return true;

    std::filesystem::path parent_path = filepath.parent_path();
    if (std::filesystem::exists(parent_path) && std::filesystem::is_directory(parent_path))
        return true;

    std::filesystem::create_directories(parent_path);

    return false;
}

inline bool make_dir_writable(const std::string& dirname)
{
    std::filesystem::path dirpath(dirname);

    if (std::filesystem::exists(dirpath) && std::filesystem::is_directory(dirpath))
        return true;

    std::filesystem::create_directories(dirpath);

    return false;
}

#define OUTPUT_DIRECTORY(TEST_SUIT_NAME, TEST_NAME)           \
    std::string outdir =                                        \
      "./data/test_output/" #TEST_SUIT_NAME "/" #TEST_NAME "/"; \
    make_dir_writable(outdir)