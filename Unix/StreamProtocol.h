
#pragma once

class Stream;

typedef uint16 pdu_t;

template <class T, int ReadBufferSize = 1024, int SendBufferSize = 1024>
class StreamProtocol
{
    NO_COPY(StreamProtocol);

public:
    void (T::*OnPDU)(pdu_t, pbyte, uint16);

    void (T::*OnStreamReadError)();
    void (T::*OnStreamSendError)();

public:
    StreamProtocol(Stream&, T&);

public:
    bool EncodePDU(pdu_t, pbyte, uint16);

public:
    void ExtractPDUs();

    void InsertPDUs();

private:
    void DecodePDUs(byte*, uint16&);

private:
    Stream& stream;

    T& t;

    byte readBuffer[ReadBufferSize];
    byte sendBuffer[SendBufferSize];

    uint16 readLength;
    uint16 sendLength;
};
