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
