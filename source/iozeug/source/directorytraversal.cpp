
#include <iozeug/directorytraversal.h>

#include <cassert>
#include <iostream>

#ifdef _MSC_VER
#include <windows.h>
#include "dirent_msvc.h"
#else
#include <dirent.h>
#endif

#include <iozeug/filename.h>


namespace iozeug
{


void getFiles(const std::string & directory, bool recursive, std::vector<std::string> & files)
{
    // Open directory
    DIR * dir = opendir(directory.c_str());
    if (!dir)
    {
        std::cout << "Could not open directory " << directory << "." << std::endl;
        return;
    }

    // Read directory entries
    while (dirent * entry = readdir(dir))
    {
        // Compose complete path
        const std::string name = entry->d_name;
        const std::string path = directory + "/" + name;

        // Check if entry points to a file or a directory
        bool isDir = false;
        bool isFile = false;
        if (entry->d_type == DT_DIR)
        {
            isDir = true;
        }
        else if (entry->d_type == DT_REG)
        {
            isFile = true;
        }
        else if (entry->d_type == DT_UNKNOWN)
        {
            DIR * subDir = opendir(path.c_str());
            isDir = (subDir != nullptr);
            isFile = !isDir;
            if (subDir != nullptr)
                closedir(subDir);
        }

        // Make sure that the type of entry has been determined
        assert(!(isDir && isFile));

        // Recurse into sub-directories
        if (isDir && recursive && name != "." && name != "..")
        {
            getFiles(path, true, files);
        }

        // Add files to list
        else if (isFile)
        {
            files.push_back(path);
        }
    }

    // Close directory handle
    closedir(dir);
}

std::vector<std::string> getFiles(const std::string & directory, bool recursive)
{
    std::vector<std::string> files;

    getFiles(directory, recursive, files);

    return files;
}

std::vector<std::string> scanDirectory(const std::string & directory, const std::string & fileExtension, bool recursive)
{
    std::vector<std::string> fileList;

    // Get all files in the directory
    auto files = getFiles(directory, recursive);
    for (const std::string & file : files)
    {
        // Check extension
        std::string extension = getExtension(file);
        if (fileExtension != "*" && extension != fileExtension)
            continue;

        // Add file to list
        fileList.push_back(file);
    }

    return fileList;
}

void scanDirectory(const std::string & directory, const std::string & fileExtension, bool recursive, const std::function<void(const std::string &)> & callback)
{
    // Get all files in the directory
    auto files = getFiles(directory, recursive);
    for (const std::string & file : files)
    {
        // Check extension
        std::string extension = getExtension(file);
        if (fileExtension != "*" && extension != fileExtension)
            continue;

        // Call callback function
        callback(file);
    }
}


} // namespace iozeug
