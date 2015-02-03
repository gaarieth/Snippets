
#pragma once

#define ARRAY_SIZE(A) (sizeof(A) / sizeof(A[0]))

#define NO_COPY(C) \
    private: \
        C(const C&); \
        C& operator=(const C&)

#define NO_VTABLE __declspec(novtable)
