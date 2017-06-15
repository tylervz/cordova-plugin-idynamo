#import <Cordova/CDVPlugin.h>
#import <Foundation/Foundation.h>
#import <Cordova/CDV.h>

#import "MTSCRA.h"

@interface CDVMagtek : CDVPlugin <MTSCRAEventDelegate>

@property (nonatomic, strong) MTSCRA* lib;
// @property (nonatomic, strong) NSString* dataCallbackId;

- (void)init: (CDVInvokedUrlCommand *) command;
- (void)openDevice: (CDVInvokedUrlCommand *) command;
- (void)closeDevice: (CDVInvokedUrlCommand *) command;

@end