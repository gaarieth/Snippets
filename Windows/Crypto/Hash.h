
#pragma once

namespace Crypto
{
    class CPublicKey;

    class CHash
    {
        NO_COPY(CHash);

    public:
        explicit CHash(const CContext&);

        ~CHash(void);

    public:
        operator HCRYPTHASH() const;

    public:
        bool HashData(const ByteVector&);

        void GetHashValue(ByteVector&);

        void SignHash(ByteVector& signature);

        bool VerifySignature(const ByteVector& signature, const CPublicKey&);

    private:
        HCRYPTHASH m_hHash;
    };
}
