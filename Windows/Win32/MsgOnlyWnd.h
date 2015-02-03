
#pragma once

template <class T>
struct MsgOnlyWnd
{
    typedef void (T::*OnMsg)(UINT, WPARAM, LPARAM);

    HWND hWnd;

    T& t;

    OnMsg onMsg;

    MsgOnlyWnd(T& t, OnMsg onMsg)
        : hWnd(0)
        , t(t)
        , onMsg(onMsg)
    {
        static LPCSTR atom = 0;

        if (!atom)
        {
            WNDCLASS wndCls =
            {
                0, OnWndMsg, 0, 0, 0, 0, 0, 0, 0, "MsgOnlyWnd"
            };

            atom = LPCSTR(RegisterClass(&wndCls));
        }

        hWnd = CreateWindow(atom, 0, 0, 0, 0, 0, 0, HWND_MESSAGE, 0, 0, 0);

        SetWindowLongPtr(hWnd, GWLP_USERDATA, LONG_PTR(this));
    }

    static LRESULT CALLBACK OnWndMsg(HWND hWnd, UINT m, WPARAM w, LPARAM l)
    {
        if (LONG_PTR p = GetWindowLongPtr(hWnd, GWLP_USERDATA))
        {
            MsgOnlyWnd* self = reinterpret_cast<MsgOnlyWnd*>(p);

            (self->t.*self->onMsg)(m, w, l);
        }

        return DefWindowProc(hWnd, m, w, l);
    }

    ~MsgOnlyWnd()
    {
        DestroyWindow(hWnd);
    }
};
