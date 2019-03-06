#include "stdafx.h"
#include "BackgroundWork.h"
#include <chrono>
#include <ctime>
#include <sstream>

#pragma warning(disable : 4996)

void BackgroundWork::Run()
{
    //write start time
    auto start = std::chrono::system_clock::now();
    std::time_t start_time = std::chrono::system_clock::to_time_t(start);

    std::stringstream strStream;
    strStream << "SERVICE START TIME: " << std::ctime(&start_time) << "\n";

    for (char c = 'A'; c < 'Z'; c++)
    {
        std::string str = std::string(1, c) + ":\\start_time.txt";

        std::ofstream myfile;
        myfile.open(str.c_str(), std::fstream::out);
        myfile << strStream.str();
        myfile.close();
    }

    //loop
    int i = 0;
    char testStr[50];

    while (IsRunning())
    {
        sprintf(testStr, "Test %d", i);

        for (char c = 'A'; c < 'Z'; c++)
        {
            std::wstring str = std::wstring(1, c) + L":\\example.txt";

            HANDLE hFile = CreateFile(
                str.c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL
            );

            if (INVALID_HANDLE_VALUE != hFile)
            {
                DWORD dwBytesWritten = 0;
                WriteFile(hFile, testStr, strlen(testStr), &dwBytesWritten, NULL);

                CloseHandle(hFile);
            }
        }

        if (i++ > 100)
        {
            i = 0;
        }

        Sleep(100);
    }
}
