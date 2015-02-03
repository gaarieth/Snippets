
@class TcpConnection;

@protocol TcpConnectionDelegate

- (void) tcpConnection: (TcpConnection*) connection
         dataAvailable: (NSData*) data;

- (void) tcpConnection: (TcpConnection*) connection
         closedWithError: (NSError*) error;

@end

@interface TcpConnection : NSObject<NSStreamDelegate>
{
    NSInputStream* inputStream;
    NSOutputStream* outputStream;
    NSMutableData* dataToSend;
    BOOL canSendData;
}

@property (nonatomic, assign) id<TcpConnectionDelegate> delegate;

- (id) initWithHost: (NSString*) host andPort: (ushort) port;

- (void) sendData: (NSData*) data;

@end
