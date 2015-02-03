
FileDescriptor::FileDescriptor(int descriptor)
    : m_descriptor(descriptor)
{
}

FileDescriptor::~FileDescriptor()
{
    CloseDescriptor();
}

int FileDescriptor::GetDescriptor() const
{
    return m_descriptor;
}

bool FileDescriptor::isValid() const
{
    return (m_descriptor != -1);
}

void FileDescriptor::CloseDescriptor()
{
    if (m_descriptor == -1)
        return;

    close(m_descriptor);

    m_descriptor = -1;
}

void FileDescriptor::MarkAsNonBlocking()
{
    if (m_descriptor == -1)
        return;

    int i = fcntl(m_descriptor, F_GETFL, 0);

    if (i != -1)
        i = fcntl(m_descriptor, F_SETFL, i | O_NONBLOCK);

    if (i == -1)
        CloseDescriptor();
}
