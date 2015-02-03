
#include "StreamProtocol.h"
#include "Stream.h"

template<class T, int R, int S>
StreamProtocol<T, R, S>::StreamProtocol(Stream& stream, T& t)
    : OnPDU(0)
    , OnStreamReadError(0)
    , OnStreamSendError(0)
    , stream(stream)
    , t(t)
    , readLength(0)
    , sendLength(0)
{
}

template<class T, int R, int S>
bool StreamProtocol<T, R, S>::InsertPDU(pdu_t t, pbyte p, uint16 n)
{
    if (!(t && p && n))
        return false;
    if (n > sizeof(sendBuffer) - sendLength - 4)
        return false;
    byte* pdu = sendBuffer + sendLength;
    *((short*) (pdu + 0)) = htons(n + 4);
    *((short*) (pdu + 2)) = htons(t);
    memcpy(pdu + 4, p, n);
    sendLength += n + 4;
    return true;
}

template<class T, int R, int S>
void StreamProtocol<T, R, S>::ExtractPDUs()
{
    while (true)
    {
        uint16 n = sizeof(readBuffer) - readLength;

        if (stream.ExtractBytes(readBuffer + readLength, n))
        {
            if (n > 0)
            {
                readLength += n;

                ExtractPDUs(readBuffer, readLength);
            }
            else
                break;
        }
        else
        {
            if (OnStreamReadError)
                (t.*OnStreamReadError)();
            break;
        }
    } // while
}

template<class T, int R, int S>
void StreamProtocol<T, R, S>::InsertPDUs()
{
    while (sendLength)
    {
        uint16 n = sendLength;

        if (stream.InsertBytes(sendBuffer, n))
        {
            if (n > 0)
            {
                memmove(sendBuffer, sendBuffer + n, sendLength - n);

                sendLength -= n;
            }
            else
                break;
        }
        else
        {
            if (OnStreamSendError)
                (t.*OnStreamSendError)();
            break;
        }
    } // while
}

template<class T, int R, int S>
void StreamProtocol<T, R, S>::ExtractPDUs(byte* p, uint16& n)
{
    uint16 i = 0;

    while (i < n)
    {
        if (n - i < 4)
            break;

        pbyte pdu = p + i;

        uint16 length = ntohs(*((short*) pdu));
        uint16 type = ntohs(*((short*) (pdu + 2)));

        if (length > R)
        {
            if (OnStreamReadError)
                (t.*OnStreamReadError)();
            break;
        }

        if (n - i < length)
            break;

        if (OnPDU)
            (t.*OnPDU)(type, pdu + 4, length - 4);

        i += length;
    }

    if (i)
        memmove(p, p + i, n -= i);
}
