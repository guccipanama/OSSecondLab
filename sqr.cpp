#pragma once
#include "source.h"

DWORD WINAPI sqr_(LPVOID param)
{
    HANDLE pipe_a = CreateNamedPipe(L"\\\\.\\pipe\\pipe_a", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);
    HANDLE pipe_b = CreateNamedPipe(L"\\\\.\\pipe\\pipe_b", PIPE_ACCESS_OUTBOUND, PIPE_TYPE_BYTE, 1, 0, 0, 0, NULL);

    HANDLE mutex_g = OpenMutex(MUTEX_ALL_ACCESS, TRUE, L"mutex_g");
    HANDLE mutex_h = OpenMutex(MUTEX_ALL_ACCESS, TRUE, L"mutex_h");

    while (true)
    {
        WaitForSingleObject(mutex_g, INFINITE);

        std::cout << std::endl << "DEBUG OUT: FOURTH PROGRAM" << std::endl;
        std::cout << "DEBUG OUT: Program is calculating square of a now!" << std::endl;

        int_convert received_a;
        int_convert res;

        DWORD real_reading_a = 0;
        DWORD real_reading_sqr = 0;

        auto tmp1 = ReadFile(pipe_a, &received_a.bytes, sizeof(int), &real_reading_a, NULL);
        auto tmp2 = ReadFile(pipe_b, &received_b.bytes, sizeof(int), &real_reading_b, NULL);

        HANDLE sqr = CreateFile(L"\\\\.\\pipe\\sqr", GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        res.value = received_a.value * received_a.value;

        WriteFile(sqr, res.bytes, sizeof(int), &real_reading_sqr, NULL);

        CloseHandle(pipe_a);
        CloseHandle(pipe_b);

        std::cout << std::endl << "DEBUG OUT: Function result - a^2: " << res.value << std::endl;
        std::cout << "DEBUG OUT: Program is terminating now!" << std::endl;
    }

    return 0;
    /*
        WaitForSingleObject(first_semafor, INFINITE);

        std::cout << "\n" << "DEBUG OUT: FIRST PROGRAM" << std::endl;
        std::cout << "\n" << "DEBUG OUT: Program is calculating pow of a and b now!" << std::endl;

        int_convert received_a;
        int_convert received_b;
        int_convert res_a;
        int_convert res_b;
        DWORD real_reading_a = 0;//unsigned long
        DWORD real_reading_b = 0;

        auto tmp1 = ReadFile(value_a, &received_a.bytes, sizeof(int), &real_reading_a, NULL);
        auto tmp2 = ReadFile(value_b, &received_b.bytes, sizeof(int), &real_reading_b, NULL);

        HANDLE a_pow = CreateFile(L"\\\\.\\mailslot\\a^2", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
        HANDLE b_pow = CreateFile(L"\\\\.\\mailslot\\b^2", GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

        real_reading_a = 0;
        real_reading_b = 0;

        res_a.value = received_a.value * received_a.value;
        res_b.value = received_b.value * received_b.value;

        WriteFile(a_pow, res_a.bytes, sizeof(int), &real_reading_a, NULL);
        WriteFile(b_pow, res_b.bytes, sizeof(int), &real_reading_b, NULL);

        std::cout << "\n" << "Function result - a: " << res_a.value << std::endl;
        std::cout << "\n" << "Function result - b: " << res_b.value << std::endl;
        std::cout << "\n" << "DEBUG OUT: FIRST PROGRAM is terminating now!" << std::endl;

        //CloseHandle(value_a);
       // CloseHandle(value_b);

        ReleaseSemaphore(second_semafor, 1, NULL);
    */
}