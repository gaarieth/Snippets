
#import "TcpConnection.h"
#import "NSStream+RunLoop.h"

@implementation TcpConnection

@synthesize delegate;

- (id) initWithHost: (NSString*) host andPort: (ushort) port
{
    if (!(self = [super init]))
        return nil;

    CFReadStreamRef readStream = 0;
    CFWriteStreamRef writeStream = 0;

    CFStreamCreatePairWithSocketToHost(0,
                                       (CFStringRef) host,
                                       port,
                                       &readStream,
                                       &writeStream);

    dataToSend = [[NSMutableData data] retain];

    inputStream = NSMakeCollectable(readStream);
    outputStream = NSMakeCollectable(writeStream);

    [inputStream setDelegate: self];
    [outputStream setDelegate: self];

    [inputStream scheduleInRunLoop];
    [outputStream scheduleInRunLoop];

    [inputStream open];
    [outputStream open];

    return self;
}

- (void) dealloc
{
    [inputStream close];
    [outputStream close];
    [inputStream removeFromRunLoop];
    [outputStream removeFromRunLoop];
    [inputStream release];
    [outputStream release];
    [dataToSend release];

    [super dealloc];
}

- (void) readData
{
    uint8_t bytes[0x400] = {0};

    NSInteger i = [inputStream read: bytes maxLength: sizeof(bytes)];

    if (i < 1)
        return;

    NSData* data = [NSData dataWithBytes: bytes length: i];

    [delegate tcpConnection: self dataAvailable: data];
}

- (void) sendData
{
    NSUInteger length = dataToSend.length;

    NSInteger i = [outputStream write: dataToSend.bytes maxLength: length];

    if (i < 1)
        return;

    if (i < length)
    {
        length -= i;

        memmove(dataToSend.mutableBytes, dataToSend.mutableBytes + i, length);

        dataToSend.length = length;
    }
    else
        dataToSend.length = 0;
}

- (void) stream: (NSStream*) stream handleEvent: (NSStreamEvent) streamEvent
{
    switch (streamEvent)
    {
        case NSStreamEventHasBytesAvailable:
            [self readData];
            break;
        case NSStreamEventHasSpaceAvailable:
            canSendData = YES;
            if (dataToSend.length)
                [self sendData];
            break;
        case NSStreamEventErrorOccurred:
        case NSStreamEventEndEncountered:
            [delegate tcpConnection: self closedWithError: stream.streamError];
        default:
            break;
    }
}

- (void) sendData: (NSData*) data
{
    [dataToSend appendData: data];

    if (canSendData && dataToSend.length)
        [self sendData];
}

@end
