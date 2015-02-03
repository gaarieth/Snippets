
#pragma once

template <class T>
class Pointer
{
    NO_COPY(Pointer);

public:
    explicit Pointer(T* pT)
        : m_pT(pT)
    {
    }

    ~Pointer()
    {
        delete m_pT;
    }

public:
    T* operator->()
    {
        return m_pT;
    }

private:
    T* m_pT;
};
