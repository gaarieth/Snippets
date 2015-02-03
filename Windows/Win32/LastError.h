
#pragma once

namespace Windows
{
    struct LastError
    {
        const DWORD Number;

        LPWSTR const String;

        explicit LastError(DWORD number = GetLastError());

        ~LastError(void);

        void MsgBox(HWND Owner = GetActiveWindow()) const;
    };
}
