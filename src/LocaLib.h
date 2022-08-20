//------------------------------------------------------------------------------
// LocaLib v1.0
// Released under the "Public Domain" (CC0).
// Written by Gie "Max" Vanommeslaeghe
// https://github.com/LBBStudios/LocaLib
// Released 'AS-IS' without warranty of any kind. Use at your own risk.
//------------------------------------------------------------------------------

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <vector>

namespace LocaLib {
    class Locale final {
    public:
        //Constructor
        Locale(const std::string& filename, const std::wstring& language) {
            std::cout << "LocaLib v1.0 by Gie 'Max' Vanommeslaeghe --- Using locale file: " << filename << std::endl;
            m_filename = filename;
            Load(language);
        }

        //Desctructor function
        ~Locale() {
            m_entries.clear();
            m_languages.clear();
        }

        //Loads the locale from the given file. Only loads the given language, but other languages can be switched, see the "SwitchLanguage" function.
        void Load(const std::wstring& language) {
            m_entries.clear();
            m_languages.clear();

            //open the file:
            std::wifstream f(m_filename.c_str());
            if (!f.good()) {
                std::cout << "Error: Could not open file " << m_filename << std::endl;
                return;
            }

            //read the file:
            std::wstring line;
            int columnForRequestedLanguage = -1;
            int lineCount = 0;

            while (std::getline(f, line)) {
                lineCount++;

                //split the line into tokens:
                std::wstringstream ss(line);
                std::wstring token;
                std::vector<std::wstring> tokens;

                while (std::getline(ss, token, L';')) {
                    tokens.push_back(token);
                }

                if (tokens.size() < 2) {
                    continue;
                }

                //check if the first token of this line was "key":
                if (lineCount == 1 && tokens[0] == L"key") {
                    //find our language in our tokens:
                    for (size_t i = 0; i < tokens.size(); i++) {
                        if (tokens[i] == language) columnForRequestedLanguage = (int)i;
                        m_languages.push_back(tokens[i]);
                    }

                    continue;
                }

                //add the entry to the map:
                m_entries.insert(std::make_pair(tokens[0], tokens[columnForRequestedLanguage]));
            }
        }

        //Returns the string for the given key. If the key is not found, the key is returned.
        const std::wstring& Get(const std::wstring& key) const {
            auto it = m_entries.find(key);
            if (it != m_entries.end()) return it->second;
            return key;
        }

        //Returns the string for the given key. If the key is not found, the key is returned.
        const std::wstring& operator[](const std::wstring& key) const {
            return Get(key);
        }

        //Get the languages of the locale file, in the order they are specified in the file. Returned as a vector of strings.
        const std::vector<std::wstring>& GetLanguages() const {
            return m_languages;
        }

        //Switches the language by reloading the locale file.
        void SwitchLanguage(const std::wstring& language) {
            std::wcout << "Switching language to " << language << std::endl;
            Load(language);
        }

    private:
        std::string m_filename;
        std::map<std::wstring, std::wstring> m_entries;
        std::vector<std::wstring> m_languages;
    };
}
