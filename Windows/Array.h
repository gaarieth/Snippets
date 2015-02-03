
#pragma once

template <class T>
class CArray
{
    NO_COPY(CArray);

public:
    explicit CArray(BYTE size)
        : m_pT(0)
        , n(0)
        , length(n)
    {
        Resize(size);
    }

    ~CArray(void)
    {
        Resize(0);
    }

public:
    void Resize(BYTE size)
    {
        delete [] m_pT;

        m_pT = (size ? (new T[size]) : 0);

        if (m_pT)
        {
            ZeroMemory(m_pT, size * sizeof(T));

            n = size;
        }
        else
            n = 0;
    }

public:
    T* GetArray() const
    {
        return m_pT;
    }

    T& operator[](BYTE i) const
    {
        return m_pT[i];
    }

private:
    T* m_pT;

    BYTE n;

public:
    const BYTE& length;
};
