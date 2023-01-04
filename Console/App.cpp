#include <cstdio>
#include <limits>
#include <fstream>

#include <pawal/SystemMacor.hpp>
#include <pawal/IPawalApi.hpp>
#include <pawal/AnosuApi.hpp>

#ifdef PAWAL_IS_WIN
#include <io.h>
#include <Windows.h>
#else
#include <unistd.h>
#include <sys/stat.h>
#endif

static bool ExistFile(const char *name)
{
#ifdef PAWAL_IS_WIN
    return ::_access_s(name, 0) == 0;
#else
    return ::access(name, F_OK) == 0;
#endif
}

static std::string SelectPath(const std::string &keyword)
{
    std::string path;
    path.resize(12 + keyword.size());
    for (std::uint16_t i = 0; i != (std::numeric_limits<std::uint16_t>::max)(); ++i)
    {
        std::snprintf(const_cast<char*>(path.data()),path.size() + 1,"./%s-%hu.png",keyword.data(),i);
        if(!ExistFile(path.data()))
        {
            return path;
        }
    }
    return std::string{};
}

int main(int argc, char const *argv[])
{
    if(argc < 2)
    {
        std::fputs("Usage: <keyword> - search image\n",stderr);
        return -1;
    }
    std::unique_ptr<pawal::IPawalApi> api{new (std::nothrow) pawal::AnosuApi{}};
    std::vector<char> image{api->LookupImage(argv[1])};
    if(image.empty())
    {
        std::fprintf(stderr,"Cannot find image about %s\n",argv[1]);
        return -1;
    }
    std::string path{SelectPath(argv[1])};
    std::fstream fs{path.c_str(),std::ios_base::binary|std::ios_base::out|std::ios_base::trunc};
    if(!fs)
    {
         std::fprintf(stderr,"Fail to open file %s\n",path.c_str());
        return -1;
    }
    fs.write(image.data(),image.size());
    return 0;
}