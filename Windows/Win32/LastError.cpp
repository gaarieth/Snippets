
#include "StdAfx.h"
#include "LastError.h"

using namespace Windows;

LastError::LastError(DWORD number)
    : Number(number)
    , String(0)
{
    FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                  0,
                  Number,
                  0,
                  LPWSTR(&String),
                  0,
                  0);
}

LastError::~LastError(void)
{
    LocalFree(String);
}

void LastError::MsgBox(HWND Owner) const
{
    WCHAR Caption[0x100] = {0};
    if (Owner)
        GetWindowText(Owner, Caption, ARRAY_SIZE(Caption));
    MessageBox(Owner, String, Caption, MB_ICONWARNING);
}
