
#pragma once

namespace Crypto
{
    class CHash;

    class CKey
    {
        CKey& operator=(const CKey&);

    protected:
        CKey(const CKey&);

        CKey(void);

        ~CKey(void);

    public:
        operator HCRYPTKEY() const;

    private:
        void DuplicateKey(const CKey&);

        void DestroyKey();

    protected:
        template <class T>
        void GetKeyParameter(DWORD name, T& value);

        void GetKeyParameters();

    public:
        bool Encrypt(ByteVector&, CHash&, bool final);

        bool Decrypt(ByteVector&, CHash&, bool final);

    protected:
        HCRYPTKEY m_hKey;

        ALG_ID m_algorithmId;

        DWORD m_keyLength;

        DWORD m_blockLength;

        DWORD m_encryptLength;

    public:
        const ALG_ID& AlgorithmId;

        const DWORD& KeyLength;

        const DWORD& BlockLength;

        const DWORD& EncryptLength;
    };

    class CKeyPair : public CKey
    {
    public:
        explicit CKeyPair(const CContext&);

        CKeyPair(const CContext&, const ByteVector&);

    public:
        void ExportKeyPair(ByteVector&) const;

        void ExportPublicKey(ByteVector&) const;
    };

    class CPublicKey : public CKey
    {
    public:
        CPublicKey(const CContext&, const ByteVector&);
    };

    class CSessionKey : public CKey
    {
    public:
        explicit CSessionKey(const CContext&);

        CSessionKey(const CContext&, const ByteVector&, const CKeyPair&);

    public:
        void ExportSessionKey(ByteVector&, const CPublicKey&) const;
    };
}
