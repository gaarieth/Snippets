
#pragma once

class Stream
{
    NO_COPY(Stream);

public:
    explicit Stream(const FileDescriptor&);

public:
    bool ExtractBytes(byte*, uint16&);

    bool InsertBytes(pbyte, uint16&);

private:
    ssize_t ReadBytes(byte*, uint16, int&);

    ssize_t SendBytes(pbyte, uint16, int&);

private:
    const FileDescriptor& m_descriptor;
};
