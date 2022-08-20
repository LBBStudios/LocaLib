# LocaLib
A simple, public domain, header-only C++ library that handles localizations for various languages.
Comes with no warranty of any kind, and is provided 'AS-IS'.

## Sample usage
Although there is a Code::Blocks project provided for convience, ***you only require the LocaLib.h header to use the library.***
Here is a minimal example of all the major functions:

```cpp
#include "LocaLib.h"
using namespace LocaLib;

int main(int argc, char** argv) {
    std::cout << "Test app for LocaLib" << std::endl;

    //load the locale:
    Locale locale("sample.csv", L"en-us");

    //get the string:
    std::wcout << locale.Get(L"gameover") << std::endl;
    std::wcout << locale.Get(L"sayhello") << std::endl;

    //switch the language:
    locale.SwitchLanguage(L"nl-be");
    std::wcout << locale.Get(L"gameover") << std::endl;
    std::wcout << locale.Get(L"sayhello") << std::endl;

    return 0;
}
```

## Creating a CSV file for localizations
The first row should be key;(lang1);(lang2), or use the sample.csv file included in the repository.
