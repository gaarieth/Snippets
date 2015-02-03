
#include "StdAfx.h"
#include "Key.h"
#include "Hash.h"

using namespace Crypto;

static void ExportKey(HCRYPTKEY hKeyToExport,
                      HCRYPTKEY hEncryptionKey,
                      DWORD blobType,
                      ByteVector& keyBlob)
{
    if (!hKeyToExport)
        return;

    DWORD keySize = 0;

    if (!CryptExportKey(hKeyToExport,
                        hEncryptionKey,
                        blobType,
                        0,
                        0,
                        &keySize))
    {
        return;
    }

    keyBlob.resize(keySize);

    if (!keySize)
        return;

    CryptExportKey(hKeyToExport,
                   hEncryptionKey,
                   blobType,
                   0,
                   &keyBlob[0],
                   &keySize);
}

static HCRYPTKEY ImportKey(const CContext& context,
                           HCRYPTKEY hDecryptionKey,
                           const ByteVector& keyBlob,
                           DWORD keyFlags = 0)
{
    HCRYPTKEY hKey = 0;

    if (DWORD keySize = keyBlob.size())
    {
        CryptImportKey(context,
                       &keyBlob[0],
                       keySize,
                       hDecryptionKey,
                       CRYPT_EXPORTABLE | keyFlags,
                       &hKey);
    }

    return hKey;
}
/*
CKey& CKey::operator=(const CKey& key)
{
    if (this != &key)
    {
        DestroyKey();

        DuplicateKey(key);
    }

    return *this;
}
*/
CKey::CKey(const CKey& key)
    : m_hKey(0)
    , m_algorithmId(0)
    , m_keyLength(0)
    , m_blockLength(0)
    , m_encryptLength(0)
    , AlgorithmId(m_algorithmId)
    , KeyLength(m_keyLength)
    , BlockLength(m_blockLength)
    , EncryptLength(m_encryptLength)
{
    DuplicateKey(key);

    GetKeyParameters();
}

CKey::CKey(void)
    : m_hKey(0)
    , m_algorithmId(0)
    , m_keyLength(0)
    , m_blockLength(0)
    , m_encryptLength(0)
    , AlgorithmId(m_algorithmId)
    , KeyLength(m_keyLength)
    , BlockLength(m_blockLength)
    , EncryptLength(m_encryptLength)
{
}

CKey::~CKey(void)
{
    DestroyKey();
}

CKey::operator HCRYPTKEY() const
{
    return m_hKey;
}

void CKey::DuplicateKey(const CKey& key)
{
    if (m_hKey)
        DebugBreak();

    if (key.m_hKey)
        CryptDuplicateKey(key.m_hKey, 0, 0, &m_hKey);
}

void CKey::DestroyKey()
{
    if (!m_hKey)
        return;

    CryptDestroyKey(m_hKey);

    m_hKey = 0;
}

template <class T>
void CKey::GetKeyParameter(DWORD name, T& value)
{
    DWORD valueSize = sizeof(value);

    CryptGetKeyParam(m_hKey, name, LPBYTE(&value), &valueSize, 0);
}

void CKey::GetKeyParameters()
{
    GetKeyParameter(KP_ALGID, m_algorithmId);
    GetKeyParameter(KP_KEYLEN, m_keyLength);
    GetKeyParameter(KP_BLOCKLEN, m_blockLength);

    if (m_blockLength)
        m_encryptLength = (m_blockLength / 8) - 11;
}

bool CKey::Encrypt(ByteVector& data, CHash& hash, bool final)
{
    if (data.empty())
        return false;

    DWORD plainTextLength = data.size();
    DWORD cipherTextLength = plainTextLength;

    CryptEncrypt(m_hKey, 0, final, 0, 0, &cipherTextLength, 0);

    if (cipherTextLength < plainTextLength)
        DebugBreak();

    if (cipherTextLength > plainTextLength)
        data.resize(cipherTextLength);

    return (CryptEncrypt(m_hKey,
                         hash,
                         final,
                         0,
                         &data[0],
                         &plainTextLength,
                         cipherTextLength) != 0);
}

bool CKey::Decrypt(ByteVector& data, CHash& hash, bool final)
{
    if (data.empty())
        return false;

    DWORD length = data.size();

    if (CryptDecrypt(m_hKey, hash, final, 0, &data[0], &length))
    {
        if (length > data.size())
            DebugBreak();

        if (length < data.size())
            data.resize(length);

        return true;
    }

    return false;
}

CKeyPair::CKeyPair(const CContext& context)
{
    CryptGenKey(context,
                AT_KEYEXCHANGE,
                CRYPT_EXPORTABLE | RSA1024BIT_KEY,
                &m_hKey);

    GetKeyParameters();
}

CKeyPair::CKeyPair(const CContext& context, const ByteVector& keyBlob)
{
    m_hKey = ImportKey(context, 0, keyBlob);

    GetKeyParameters();
}

void CKeyPair::ExportKeyPair(ByteVector& keyBlob) const
{
    ExportKey(m_hKey, 0, PRIVATEKEYBLOB, keyBlob);
}

void CKeyPair::ExportPublicKey(ByteVector& keyBlob) const
{
    ExportKey(m_hKey, 0, PUBLICKEYBLOB, keyBlob);
}

CPublicKey::CPublicKey(const CContext& context, const ByteVector& keyBlob)
{
    m_hKey = ImportKey(context, 0, keyBlob);

    GetKeyParameters();
}

CSessionKey::CSessionKey(const CContext& context)
{
    CryptGenKey(context,
                CALG_RC4,
                CRYPT_EXPORTABLE | CRYPT_NO_SALT,
                &m_hKey);

    GetKeyParameters();
}

CSessionKey::CSessionKey(const CContext& context,
                         const ByteVector& keyBlob,
                         const CKeyPair& keyPair)
{
    m_hKey = ImportKey(context, CKeyPair(keyPair), keyBlob, CRYPT_NO_SALT);

    GetKeyParameters();
}

void CSessionKey::ExportSessionKey(ByteVector& keyBlob,
                                   const CPublicKey& publicKey) const
{
    ExportKey(m_hKey, CPublicKey(publicKey), SIMPLEBLOB, keyBlob);
}
