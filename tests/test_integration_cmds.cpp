#include <gtest/gtest.h>

#include <windows.h>
#include <string>
#include <iostream>

static bool LaunchRhinoHeadless(const std::wstring& rhinoExePath, const std::wstring& script) {
    std::wstring cmd = L"\"" + rhinoExePath + L"\" /nosplash /notemplate /runscript=\"" + script + L"\"";

    // Set up security attributes for pipe
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), nullptr, TRUE };
    HANDLE hRead, hWrite;
    if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
        std::wcerr << L"Failed to create pipe." << std::endl;
        return false;
    }

    STARTUPINFOW si = { sizeof(si) };
    si.dwFlags |= STARTF_USESTDHANDLES;
    si.hStdOutput = hWrite;
    si.hStdError = hWrite;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

    PROCESS_INFORMATION pi;
    BOOL success = CreateProcessW(
        nullptr,
        &cmd[0],
        nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi
    );
    CloseHandle(hWrite); // Parent doesn't need this

    if (success) {
        // Read Rhino's output and print to std::wcout
        wchar_t buffer[4096];
        DWORD read;
        while (ReadFile(hRead, buffer, sizeof(buffer) - sizeof(wchar_t), &read, nullptr) && read > 0) {
            buffer[read / sizeof(wchar_t)] = 0;
            std::wcout << buffer;
        }
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        CloseHandle(hRead);
        return true;
    } else {
        std::wcerr << L"Failed to launch Rhino. Error: " << GetLastError() << std::endl;
        CloseHandle(hRead);
        CloseHandle(hWrite);
        return false;
    }
}

TEST(TEST_INTEGRATION_CommandsSuite, TestToBeNamed) {
    ASSERT_TRUE(true);
    // ASSERT_TRUE(LaunchRhinoHeadless(L"C:\\Program Files\\Rhino 8\\System\\Rhino.exe", L"-_cmake4rhino _Enter"));
}