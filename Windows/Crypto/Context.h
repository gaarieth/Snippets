
#pragma once

namespace Crypto
{
    class CContext
    {
        NO_COPY(CContext);

    public:
        CContext(void);

        ~CContext(void);

    public:
        operator HCRYPTPROV() const;

    private:
        HCRYPTPROV m_hProvider;
    };
}
