
#pragma once

class FileDescriptor
{
    NO_COPY(FileDescriptor);

public:
    explicit FileDescriptor(int);

    ~FileDescriptor();

public:
    int GetDescriptor() const;

    bool isValid() const;

public:
    void CloseDescriptor();

    void MarkAsNonBlocking();

private:
    int m_descriptor;
};
