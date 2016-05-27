//
//  TusBackgroundUpload.h
//  tus-ios-client-demo
//
//  Originally Created by Felix Geisendoerfer on 07.04.13.
//  Copyright (c) 2013 Felix Geisendoerfer. All rights reserved.
//
//  Additions and Maintenance for TUSKit 1.0.0 and up by Mark Robert Masterson
//  Copyright (c) 2015-2016 Mark Robert Masterson. All rights reserved.

@import Foundation;
@class TUSUploadStore;

typedef void (^TUSUploadResultBlock)(NSURL* fileURL);
typedef void (^TUSUploadFailureBlock)(NSError* error);
typedef void (^TUSUploadProgressBlock)(NSUInteger bytesWritten, NSUInteger bytesTotal);

@interface TUSBackgroundUpload : NSObject

@property (readwrite, copy) TUSUploadResultBlock resultBlock;
@property (readwrite, copy) TUSUploadFailureBlock failureBlock;
@property (readwrite, copy) TUSUploadProgressBlock progressBlock;
@property (readonly) NSString *id;

/**
Initializer methods
*/
- (id)initWithURL:(NSURL *)url
       sourceFile:(NSURL *)sourceFile
    uploadHeaders:(NSDictionary *)headers
      uploadStore:(TUSUploadStore *)store;
+ (instancetype)loadUploadWithId:(NSString *)uploadId
                       fromStore:(TUSUploadStore *)store;
/**
Delegate Methods
*/
- (void) task:(NSURLSessionTask *)task didSendBodyData:(int64_t)bytesSent totalBytesSent:(int64_t)totalBytesSent totalBytesExpectedToSend:(int64_t)totalBytesExpectedToSend;
- (void) dataTask:(NSURLSessionDataTask *)task didReceiveResponse:(NSURLResponse *)response completionHandler:(void (^)(NSURLSessionResponseDisposition))completionHandler;
- (void) task:(NSURLSessionTask *)task didCompleteWithError:(NSError *)error;

 /**
Utility Methods
*/
- (NSURLSessionTask *) makeNextCallWithSession:(NSURLSession *)session;
- (void) updateStateFromHeaders:(NSDictionary*)headers;
- (NSDictionary *) serializeObject;
- (BOOL) isComplete;

/**
File actions
*/
 - (NSURLSessionTask *) checkFile:(NSURLSession *)session;
- (NSURLSessionTask *) createFile:(NSURLSession *)session;
- (NSURLSessionTask *) uploadFile:(NSURLSession *)session;

/**
 Recreate a TUSBackgroundUpload from a dictionary
 */
-(void)saveToStore:(TUSUploadStore *)store;


@end