#include "file_utils.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

std::filesystem::path getExecutablePath() {
    #ifdef _WIN32
        char path_buffer[MAX_PATH];
        GetModuleFileNameA(NULL, path_buffer, MAX_PATH);
        return std::filesystem::path(path_buffer).parent_path();
    #else
        char path_buffer(1024);
        readlink("/proc/self/exe", path_buffer, sizeof(path_buffer));
        return std::filesystem::path(path_buffer).parent_path();
    #endif
}
