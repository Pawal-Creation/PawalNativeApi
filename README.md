# Pawal Native Api

## Install

* Build Library:
    1. Install OpenSSL 
    2. Add OpenSSL root to environment variable
    3. Run `build.cmd` or `build.sh`
* Build Console:
    1. Install OpenSSL 
    2. Add OpenSSL root to environment variable
    3. Run `build_console.cmd` or `build_console.sh`
* With Cmake(Version 3.14.0+):
```cmake
include(FetchContent)

fetchcontent_declare(PawalNativeApi GIT_REPOSITORY "git://Pawal-Creation/PawalNativeApi" GIT_TAG "Git tag" SOURCE_DIR "You install path")
fetchcontent_makeavailable(PawalNativeApi)

target_link_libraries(YourApp PawalApi)
```

## Usage

```cpp
std::unique_ptr<pawal::IPawalApi> api{new (std::nothrow) pawal::AnosuApi{}};
std::vector<char> image{api->LookupImage("keyword")};
if(image.empty())
{
    //not found
}
```