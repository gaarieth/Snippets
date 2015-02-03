
#include "StdAfx.h"

using namespace Crypto;

CContext::CContext(void)
    : m_hProvider(0)
{
    CryptAcquireContext(&m_hProvider,
                        0,
                        MS_STRONG_PROV,
                        PROV_RSA_FULL,
                        CRYPT_VERIFYCONTEXT);
}

CContext::~CContext(void)
{
    CryptReleaseContext(m_hProvider, 0);
}

CContext::operator HCRYPTPROV() const
{
    return m_hProvider;
}
