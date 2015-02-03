
#include "StdAfx.h"
#include "Hash.h"
#include "Key.h"

using namespace Crypto;

static const ALG_ID ALGORITHM = CALG_SHA;

static const DWORD HASH_FLAGS = CRYPT_NOHASHOID;

CHash::CHash(const CContext& context)
    : m_hHash(0)
{
    CryptCreateHash(context, ALGORITHM, 0, 0, &m_hHash);
}

CHash::~CHash(void)
{
    if (m_hHash)
        CryptDestroyHash(m_hHash);
}

CHash::operator HCRYPTHASH() const
{
    return m_hHash;
}

bool CHash::HashData(const ByteVector& data)
{
    return (m_hHash &&
            (!data.empty()) &&
            CryptHashData(m_hHash, &data[0], data.size(), 0));
}

void CHash::GetHashValue(ByteVector& hashValue)
{
    if (!m_hHash)
        return;

    DWORD hashSize = 0;
    DWORD hashSizeLength = sizeof(hashSize);

    if (!CryptGetHashParam(m_hHash,
                           HP_HASHSIZE,
                           LPBYTE(&hashSize),
                           &hashSizeLength,
                           0))
    {
        return;
    }

    hashValue.resize(hashSize);

    if (!hashSize)
        return;

    CryptGetHashParam(m_hHash,
                      HP_HASHVAL,
                      &hashValue[0],
                      &hashSize,
                      0);
}

void CHash::SignHash(ByteVector& signature)
{
    if (!m_hHash)
        return;

    DWORD signatureSize = 0;

    if (!CryptSignHash(m_hHash,
                       AT_KEYEXCHANGE,
                       0,
                       HASH_FLAGS,
                       0,
                       &signatureSize))
    {
        return;
    }

    signature.resize(signatureSize);

    if (!signatureSize)
        return;

    CryptSignHash(m_hHash,
                  AT_KEYEXCHANGE,
                  0,
                  HASH_FLAGS,
                  &signature[0],
                  &signatureSize);
}

bool CHash::VerifySignature(const ByteVector& signature,
                            const CPublicKey& publicKey)
{
    return (m_hHash &&
            (!signature.empty()) &&
            CryptVerifySignature(m_hHash,
                                 &signature[0],
                                 signature.size(),
                                 publicKey,
                                 0,
                                 HASH_FLAGS));
}
