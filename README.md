# Pawal Native Api

## Install

* Build Library:
    1. Install OpenSSL 
    2. Add OpenSSL root to environment variable `OPENSSL_ROOT_DIR` (Windows only)
    3. Run `build.cmd` or `build.sh`
* Build Console:
    1. Install OpenSSL 
    2. Add OpenSSL root to environment variable `OPENSSL_ROOT_DIR` (Windows only)
    3. Run `build_console.cmd` or `build_console.sh`
* With Cmake(Version 3.14.0+):
```cmake
include(FetchContent)

fetchcontent_declare(PawalNativeApi GIT_REPOSITORY "git://Pawal-Creation/PawalNativeApi" GIT_TAG "Git tag" SOURCE_DIR "You install path")
fetchcontent_makeavailable(PawalNativeApi)

target_link_libraries(YourApp PawalApi)
```

_NOTE:_ You need set environment variable `ANDROID_OPENSSL_ROOT_DIR` to `OPENSSL for Android` path, if you want to build a Android application
## Usage

```cpp
std::unique_ptr<pawal::IPawalApi> api{new (std::nothrow) pawal::AnosuApi{}};
std::vector<char> image{api->LookupImage("keyword")};
if(image.empty())
{
    //not found
}
```