#import "CDVMagtek.h"

@implementation CDVMagtek

static NSString *dataCallbackId = nil;

#pragma mark -
#pragma mark Device Connection
#pragma mark -

- (void)pluginInitialize {
    self.lib = [MTSCRA new];
    self.lib.delegate = self;
    [self.lib setDeviceType:MAGTEKIDYNAMO];
    [self.lib setDeviceProtocolString:@"com.magtek.idynamo"];
}

- (void)init: (CDVInvokedUrlCommand *) command {
    dataCallbackId = command.callbackId;
    CDVPluginResult* result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];;
    [result setKeepCallbackAsBool:YES];
    [self.commandDelegate sendPluginResult:result callbackId:dataCallbackId];

}

- (void)openDevice:(CDVInvokedUrlCommand*)command {
    //CDVPluginResult* result = nil;
    // [result setKeepCallbackAsBool:YES];
    if(!self.lib.isDeviceOpened ) {
        [self.lib openDevice];
        // dataCallbackId = command.callbackId;
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK] callbackId:command.callbackId];
    } else {
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_INVALID_ACTION] callbackId:command.callbackId];
    }
    
}

- (void)closeDevice:(CDVInvokedUrlCommand*)command{
    if(self.lib.isDeviceOpened ) {
        [self.lib closeDevice];
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_OK] callbackId:command.callbackId];
    } else {
        [self.commandDelegate sendPluginResult:[CDVPluginResult resultWithStatus:CDVCommandStatus_INVALID_ACTION] callbackId:command.callbackId];
    }
}

#pragma mark -
#pragma mark MTSCRA Delegate Methods
#pragma mark -

- (void) cardSwipeDidStart:(id)instance {
    dispatch_async(dispatch_get_main_queue(), ^{
        [self sendEvent:@"cardSwipeDidStart" withData:nil];
    });
}
- (void) cardSwipeDidGetTransError {
    dispatch_async(dispatch_get_main_queue(), ^{
        [self sendEvent:@"cardSwipeDidGetTransError" withData:nil];
    });
}

-(void) onDeviceConnectionDidChange:(MTSCRADeviceType)deviceType connected:(BOOL)connected instance:(id)instance {
    dispatch_async(dispatch_get_main_queue(), ^{
        if([(MTSCRA*)instance isDeviceOpened]){
            if(connected) {
                [self sendEvent:@"onDeviceConnectionDidChange" withData:@"Connected"];
            } else {
                [self sendEvent:@"onDeviceConnectionDidChange" withData:@"Disconnected"];
            }
        } else {
            [self sendEvent:@"onDeviceConnectionDidChange" withData:@"Disconnected"];
        }
    });
}

-(void)onDataReceived:(MTCardData *)cardDataObj instance:(id)instance {
    dispatch_async(dispatch_get_main_queue(), ^{
        NSMutableDictionary *data = [[NSMutableDictionary alloc] init];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.trackDecodeStatus] forKey:@"TrackStatus"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.track1DecodeStatus] forKey:@"Track1Status"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.track2DecodeStatus] forKey:@"Track2Status"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.track3DecodeStatus] forKey:@"Track3Status"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.encryptionStatus] forKey:@"EncryptionStatus"];
        [data setObject:[NSString stringWithFormat:@"%ld", cardDataObj.batteryLevel] forKey:@"BatteryLevel"];
        [data setObject:[NSString stringWithFormat:@"%ld", cardDataObj.swipeCount] forKey:@"SwipeCount"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.maskedTracks] forKey:@"TrackMasked"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.maskedTrack1] forKey:@"Track1Masked"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.maskedTrack2] forKey:@"Track2Masked"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.maskedTrack3] forKey:@"Track3Masked"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.encryptedTrack1] forKey:@"Track1Encrypted"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.encryptedTrack2] forKey:@"Track2Encrypted"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.encryptedTrack3] forKey:@"Track3Encrypted"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.cardPAN] forKey:@"CardPAN"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.encryptedMagneprint] forKey:@"MagnePrintEncrypted"];
        [data setObject:[NSString stringWithFormat:@"%d", cardDataObj.magnePrintLength] forKey:@"MagnePrintLength"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.magneprintStatus] forKey:@"MagnePrintStatus"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.encrypedSessionID] forKey:@"SessionID"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.cardIIN] forKey:@"CardIIN"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.cardName] forKey:@"CardName"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.cardLast4] forKey:@"CardLast4"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.cardExpDate] forKey:@"CardExpDate"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.cardExpDateMonth] forKey:@"CardExpDateMonth"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.cardExpDateYear] forKey:@"CardExpDateYear"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.cardServiceCode] forKey:@"CardSvcCode"];
        [data setObject:[NSString stringWithFormat:@"%ld", cardDataObj.cardPANLength] forKey:@"CardPANLength"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.deviceKSN] forKey:@"KSN"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.deviceSerialNumber] forKey:@"DeviceSerialNumber"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.deviceSerialNumberMagTek] forKey:@"MagTekSerialNumber"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.firmware] forKey:@"Firmware"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.deviceName] forKey:@"DeviceName"];
        [data setObject:[(MTSCRA*)instance getTLVPayload] forKey:@"TLV_Payload"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.deviceCaps] forKey:@"DeviceCapMSR"];
        [data setObject:[(MTSCRA*)instance getOperationStatus] forKey:@"OperationStatus"];
        [data setObject:[NSString stringWithFormat:@"%@", cardDataObj.cardStatus] forKey:@"CardStatus"];
        [data setObject:[(MTSCRA*)instance getResponseData] forKey:@"RawData"];

        [self sendEvent:@"onDataReceived" withData:data];
    });
}

#pragma mark -
#pragma mark Util
#pragma mark -

- (void)sendEvent:(NSString *)dataType withData:(id)data {
    if (dataCallbackId != nil) {
        NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
        [dict setObject:dataType forKey:@"dataType"];
        if (data != nil) {
            [dict setObject:data forKey:@"data"];
        }
        CDVPluginResult *result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsDictionary:dict];
        [result setKeepCallbackAsBool:YES];
        [self.commandDelegate sendPluginResult:result callbackId:dataCallbackId];
    }
}

@end