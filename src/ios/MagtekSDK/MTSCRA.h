//
//  MTSCRA.h
//  MTSCRA
//
//  Created by Imran Jahanzeb on 1/31/12.
//  Copyright (c) 2012 MagTek. All rights reserved.


#import <AudioUnit/AudioUnit.h>
#import <Foundation/Foundation.h>
#import <AudioToolbox/AudioToolbox.h>
#import <CoreBluetooth/CoreBluetooth.h>
//#if TARGET_OS_IPHONE

#import <ExternalAccessory/ExternalAccessory.h>

//#import "MTCardData.h"
#import <AVFoundation/AVFoundation.h>
//#endif


#ifdef DEBUG
#define _DBGPRNT
#endif

/*
 Error code
 */

#define ERROR_SUCCESS 0
#define ERROR_TIMEOUT 1
#define ERROR_DEVICE_NOT_OPEN 5
#define ERROR_INVALID_PARAMETER 6
#define ERROR_DEVICE_COMMUNICATION_ERROR 7
#define ERROR_OTHER_ERROR 9
#define ERROR_BUSY 15
#define ERROR_DATA_IS_NOT_EXIST 16
#define ERROR_NOT_SUPPORT 17 
#define ERROR_UNKNOWN 255

#define FIRMWARE_TYPE_BOOTLOADER    0
#define FIRMWARE_TYPE_MAIN          1
#define FIRMWARE_TYPE_BLUETOOTH     2
#define FIRMWARE_TYPE_NFC           3
#define FIRMWARE_TYPE_WIFI          4

#define UPDATE_FIRMWARE_STARTED     0
#define UPDATE_FIRMWARE_SUCCESS     1
#define UPDATE_FIRMWARE_ERROR       9
#define UPDATE_FIRMWARE_NA          15

@class IMTSCRAData;
@class MTSCRADevice;

enum
{
    TLV_OPSTS,
    TLV_CARDSTS,
    TLV_TRACKSTS,
    
    TLV_CARDNAME,
    TLV_CARDIIN,
    TLV_CARDLAST4,
    TLV_CARDEXPDATE,
    TLV_CARDSVCCODE,
    TLV_CARDPANLEN,
    
    TLV_ENCTK1,
    TLV_ENCTK2,
    TLV_ENCTK3,
    
    TLV_DEVSN,
    TLV_DEVSNMAGTEK,
    TLV_DEVFW,
    TLV_DEVNAME,
    TLV_DEVCAPS,
    TLV_DEVSTATUS,
    TLV_TLVVERSION,
    TLV_DEVPARTNUMBER,
    TLV_CAPMSR,
    TLV_CAPTRACKS,
    TLV_CAPMAGSTRIPEENCRYPTION,
    TLV_KSN,
    TLV_CMAC,
    TLV_SWPCOUNT,
    TLV_BATTLEVEL,
    TLV_CFGTLVVERSION,
    TLV_CFGDISCOVERY,
    TLV_CFGCARDNAME,
    TLV_CFGCARDIIN,
    TLV_CFGCARDLAST4,
    TLV_CFGCARDEXPDATE,
    TLV_CFGCARDSVCCODE,
    TLV_CFGCARDPANLEN,
    TLV_MSKTK1,
    TLV_MSKTK2,
    TLV_MSKTK3,
    TLV_HASHCODE,
    TLV_SESSIONID,
    TLV_MAGNEPRINT,
    TLV_MAGNEPRINT_STS
    
};
typedef NSUInteger MTSCRATransactionData;

typedef NS_ENUM(NSUInteger, MTSCRATransactionStatus)
{
    TRANS_STATUS_OK,
    TRANS_STATUS_START,
    TRANS_STATUS_ERROR
};


enum
{
    TRANS_EVENT_OK = 1,
    TRANS_EVENT_ERROR=2,
    TRANS_EVENT_START = 4,
    
};
typedef NSUInteger MTSCRATransactionEvent;

enum
{
    CAP_MASKING = 1,
    CAP_ENCRYPTION=2,
    CAP_CARD_AUTH = 4,
    CAP_DEVICE_AUTH = 8,
    CAP_SESSION_ID = 16,
    CAP_DISCOVERY= 32,
};
typedef NSUInteger MTSCRACapabilities;

enum
{
    MAGTEKAUDIOREADER, //iOS Only
    MAGTEKIDYNAMO,
    MAGTEKDYNAMAX,
    MAGTEKEDYNAMO,
    MAGTEKUSBMSR, //OSX Only
    MAGTEKKDYNAMO,
    MAGTEKTDYNAMO,
    MAGTEKDYNAWAVE,
    MAGTEKMDYNAMO,
    MAGTEKIDYNAMO_G3,
    MAGTEKNONE
    
};
typedef NSUInteger MTSCRADeviceType;


enum
{
    BLE,
    BLE_EMV,
    USB,
    Lightning,
    NONE
};
typedef NSUInteger ConnectionType;
 

enum
{
    Connection,
    CommandMessageData,
    CardMessageData,
    BLERawMessage,
    DeviceInfo,
    RawDataMessage
    
};
typedef int MTSCRADebugDomain;


enum
{
    OK,
    OFF,
    RESETTING,
    DISCONNECTED,
    UNSUPPORTED,
    UNAUTHORIZED,
    UNKNOWN
    
};
typedef int MTSCRABLEState;

@interface MTDeviceInfo : NSObject
@property(nonatomic, strong) NSString *Address;
@property(nonatomic, strong) NSString *Name;
@property(nonatomic, strong) NSString *ProductID;
@property(nonatomic) int RSSI;
@property ConnectionType connectionType;
@end

@interface MTConnectionInfo : NSObject
@property(nonatomic) int disconnectStatus;
@property(nonatomic, strong) NSString *disconnectReason;
@property(nonatomic, strong) CBPeripheral *peripheral;
@end

@interface MTDebugInfo : NSObject
@property(nonatomic, strong) NSString *name;
@property(nonatomic) MTSCRADebugDomain debugDomain;
@property(nonatomic, strong) NSString *value;
@property ConnectionType connectionType;
@property (nonatomic,strong) NSDate* timeStamp;
@end


//#if TARGET_OS_IPHONE

@protocol EADetectorDelegate <NSObject>

@optional
- (void) DeviceConnected;
- (void) DeviceDisconnected;

@end

@interface EADetector : NSObject

@property (nonatomic, weak) id<EADetectorDelegate> delegate;
@property (nonatomic, readonly, getter=getAccessories) NSArray<EAAccessory*>* accessories;

+ (id) sharedDetector;

- (NSArray<EAAccessory*>*) getAccessories;
- (UInt32) getDeviceType : (EAAccessory*) accessory;
- (NSString*) getDeviceTypeString : (EAAccessory*) accessory;

@end

//#endif

@interface MTCardData : NSObject

- (id)initWithCardData:(NSString*)cardData;
/*!
    @attribute cardIIN
    @discussion cardIIN is 6 digits of the account, usually can help to identify the issuer
 */
@property(nonatomic, strong) NSString *cardIIN;
/*!
    @attribute cardData
    @discussion track1 | track2 | track3
 */
@property(nonatomic, strong) NSString *cardData;
/*!
    @attribute cardLast4
    @discussion last 4 digits of account, usually can help user to identify him/her self
 */
@property(nonatomic, strong) NSString *cardLast4;
/*!
    @attribute cardName
    @discussion card holder name
 */
@property(nonatomic, strong) NSString *cardName;

/*!
 * @attribute cardLastName
 * @discussion card holder last name
 * @see cardName
 */
@property (strong, nonatomic) NSString *cardLastName;
/*!
 * @attribute cardMiddleName
 * @discussion card holder middle name
 */
@property (strong, nonatomic) NSString *cardMiddleName;
/*!
 * @attribute cardFirstName
 * @discussion card holder first name
 */
@property (strong, nonatomic) NSString *cardFirstName;

/*!
 * @attribute cardExpDate
 * @discussion card expiration date (MM/YY) on track 2
 */
@property(nonatomic, strong) NSString *cardExpDate;
/*!
 * @attribute cardServiceCode
 * @discussion card service code on track 2
 */
@property(nonatomic, strong) NSString *cardServiceCode;

/*!
 * @attribute cardStatus
 * @discussion card swipe status
 *
 * "00" The card was swiped in the withdrawal direction.
 *
 * "01" The card was swiped in the insertion direction.
 */
@property(nonatomic, strong) NSString *cardStatus;
@property(nonatomic, strong) NSString *responseData;
@property(nonatomic, strong) NSString *maskedTracks;

/*!
 * @attribute encryptedTrack1
 * @discussion Encrypted track 1 data (in HEX)
 */
@property(nonatomic, strong) NSString *encryptedTrack1;

/*!
 * @attribute encryptedTrack2
 * @discussion Encrypted track 2 data (in HEX)
 */
@property(nonatomic, strong) NSString *encryptedTrack2;

/*!
 * @attribute encryptedTrack3
 * @discussion Encrypted track 3 data (in HEX)
 */
@property(nonatomic, strong) NSString *encryptedTrack3;
@property(nonatomic, strong) NSString *encryptionStatus;
@property(nonatomic, strong) NSString *maskedTrack1;
@property(nonatomic, strong) NSString *maskedTrack2;
@property(nonatomic, strong) NSString *maskedTrack3;
@property(nonatomic, strong) NSString *trackDecodeStatus;
@property(nonatomic, strong) NSString *encryptedMagneprint;
@property(nonatomic, strong) NSString *magneprintStatus;
@property(nonatomic, strong) NSString *deviceSerialNumber;
@property(nonatomic, strong) NSString *deviceSerialNumberMagTek;
@property(nonatomic, strong) NSString *encrypedSessionID;
/*!
    @attribute deviceKSN
    @discussion Key Serial Number for the card swipe
 */
@property(nonatomic, strong) NSString *deviceKSN;
@property(nonatomic, strong) NSString *deviceFirmware;
@property(nonatomic, strong) NSString *deviceName;
@property(nonatomic, strong) NSString *deviceCaps;
@property(nonatomic, strong) NSString *deviceStatus;
@property(nonatomic, strong) NSString *tlvVersion;
@property(nonatomic, strong) NSString *devicePartNumber;
@property(nonatomic, strong) NSString *capMSR;
@property(nonatomic, strong) NSString *capTracks;
@property(nonatomic, strong) NSString *capMagStripeEncryption;
@property(nonatomic, strong) NSString *maskedPAN;
@property(nonatomic) long cardPANLength;
@property(nonatomic, strong) NSString *additionalInfoTrack1;
@property(nonatomic, strong) NSString *additionalInfoTrack2;
@property(nonatomic, strong) NSString *responseType;
@property(nonatomic) long batteryLevel;
@property(nonatomic) long swipeCount;
@property(nonatomic, strong) NSString *firmware;
@property(nonatomic, strong) NSString *tagValue;
@property(nonatomic) int magnePrintLength;
@property(nonatomic) int cardType;
@property(nonatomic, strong) NSString *cardExpDateMonth;
@property(nonatomic, strong) NSString *cardExpDateYear;
@property(nonatomic, strong) NSString *cardPAN;
@property(nonatomic, strong) NSString *track1DecodeStatus;
@property(nonatomic, strong) NSString *track2DecodeStatus;
@property(nonatomic, strong) NSString *track3DecodeStatus;
@property(nonatomic, strong) NSDate* timeStamp;

@property(nonatomic, strong) NSString* messageID;
@property(nonatomic, strong) NSString* msrDUKPTKeyInfo; // 16 bytes
@property(nonatomic, strong) NSString* mpDUKPTKeySerialNumber;   // 0/20/24
@property(nonatomic, strong) NSString* mpDUKPTKeyInfo; // 16 bytes
@property(nonatomic, strong) NSString* macKeyInfo; // 16 bytes
@property(nonatomic, strong) NSString* macMessageLength;
@property(nonatomic, strong) NSString* mac;

@property(nonatomic, strong) NSString* tokenDUKPTKeyInfo;
@property(nonatomic, strong) NSString* tokenDUKPTKeySerialNumber;
@property(nonatomic, strong) NSString* encryptedQwantumDataBuffer;
@property(nonatomic, strong) NSString* qwantumStatus;
@property(nonatomic, strong) NSString* qwantumToken;
@property(nonatomic, strong) NSString* qwantumCardID;

@property(nonatomic, strong) NSString* customerMessageCode;
@property(nonatomic, strong) NSString* customerMessage;


@property(nonatomic) BOOL isQwantumCard;
@property(nonatomic) BOOL isQwantumBuffer;
@property(nonatomic) BOOL isCustomerMessage;

@property(nonatomic, strong) NSDictionary* allObjects;
@property(nonatomic, strong) NSArray<NSString*>* objectArray;

@end

typedef void (^MTSCRADebugCallback)(MTDebugInfo*);
@protocol MTSCRAEventDelegate <NSObject>
@optional
- (void) onDataReceived: (MTCardData*)cardDataObj instance:(id)instance;
- (void) cardSwipeDidStart:(id)instance;
- (void) cardSwipeDidGetTransError;
- (void) onDeviceConnectionDidChange:(MTSCRADeviceType)deviceType connected:(BOOL) connected instance:(id)instance;
- (void) bleReaderConnected:(CBPeripheral*)peripheral;
- (void) bleReaderDidDisconnected:(MTConnectionInfo*)connectionInfo;
- (void) bleReaderDidDiscoverPeripheral;
/*!
 A callback delegate to notify Bluetooth reader state changed
 
 Application can start scan Bluetooth LE device after reader state changed to OK.
 
 ~~~
 if (state == OK) {
     // dispatch in main queue is very important
     DispatchQueue.main.asyncAfter(deadline: .now() + 0.1, execute: {
         if (UserOptions.shared.isScanNew()) {
             self.log("Press and hold power button for 3 seconds to enter pairing mode!")
             self.lib.startScanningForPeripherals()
         } else {
             self.lib.setAddress(UserOptions.shared.address)
             self.lib.openDevice()
         }
     })
 }
 ~~~
 
 @param state Bluetooth reader state
 - OK, power on and ready to connect
 - OFF, power off, should have no communication after that.
 - RESETTING, reader is resetting
 - DISCONNECTED, reader is disconnected
 - UNSUPPORTED, reader is not supported
 - UNAUTHORIZED, reader is not in authorized state
 - UNKNOWN, unknown state
 
 */
- (void) bleReaderStateUpdated:(MTSCRABLEState)state;
- (void) onDeviceResponse:(NSData*)data;
- (void) onDeviceError:(NSError*)error;
//EMV delegate
- (void) OnTransactionStatus:(NSData*)data;
- (void) OnDisplayMessageRequest:(NSData*)data;
- (void) OnUserSelectionRequest:(NSData*)data;
- (void) OnARQCReceived:(NSData*)data;
- (void) OnTransactionResult:(NSData*)data;
- (void) OnEMVCommandResult:(NSData*)data;
- (void) onDeviceExtendedResponse:(NSString*)data;
/*!
 A callback delegate to notify device is not paired
 
 Bluetooth LE device need to be paired before use. To put device into pairing mode, just press the pairing button 3 seconds and wait the light turn blue.
 */
- (void) deviceNotPaired;
- (void) didGetRSSI:(int)RSSI error:(NSError*)error;

/*!
 A callback delegate to receive the device list
 
 After calling function **requestDeviceList** or **startScanningForPeripherals**, the connected device or peripheral surrounded will send back through this delegate.
 
 It is maybe called once or multiple time when enumeration/scanning is in progress
 
 @param instance The calling object
 @param connectionType The enumeration connection type, for example "USB"
 @param deviceList An array of devices, object type MTDeviceInfo

 */
- (void) onDeviceList:(id)instance connectionType:(ConnectionType)connectionType deviceList:(NSArray*)deviceList;

/*!
 A callback delegate to receive the firmware updating information
 
 Calling **updateFirmware:Data:** will trigger this callback.
 
 @param sender a MTSCRA device to call the delegate
 @param status status of current firmware updating
 - UPDATE_FIRMWARE_STARTED     0  updating is started
 - UPDATE_FIRMWARE_SUCCESS    1 updating is completed
 - UPDATE_FIRMWARE_ERROR       9  updating got error
 - UPDATE_FIRMWARE_NA          15 unknown failure
 @param progress interger value from 0 to 100
 @param information a string to represent the current status
 */
- (void) OnUpdateFirmware : (NSObject*) sender Status: (int) status Progress:(int)progress Information : (NSString*) information;
@end



@interface MTSCRA : NSObject <NSStreamDelegate>
{
    
 
@private
    
    NSString *cardIIN;
    NSString *cardData;
    NSString *cardLast4;
    NSString *cardName;
    
    NSString *cardLastName;
    NSString *cardMiddleName;
    NSString *cardFirstName;
    
    NSString *cardExpDate;
    NSString *cardServiceCode;
    NSString *cardStatus;
    NSString *responseData;
    NSString *maskedTracks;
    NSString *stdTrack1;
    NSString *stdTrack2;
    NSString *stdTrack3;
    NSString *encryptedTrack1;
    NSString *encryptedTrack2;
    NSString *encryptedTrack3;
    NSString *encryptionStatus;
    NSString *maskedTrack1;
    NSString *maskedTrack2;
    NSString *maskedTrack3;
    NSString *trackDecodeStatus;
    NSString *encryptedMagneprint;
    NSString *magneprintStatus;
    NSString *deviceSerialNumber;
    NSString *deviceSerialNumberMagTek;
    NSString *encrypedSessionID;
    NSString *deviceKSN;
    NSString *deviceFirmware;
    NSString *deviceName;
    NSString *deviceCaps;
    NSString *deviceStatus;
    NSString *tlvVersion;
    NSString *devicePartNumber;
    NSString *capMSR;
    NSString *capTracks;
    NSString *capMagStripeEncryption;
    NSString *maskedPAN;
    NSString *additionalInfoTrack1;
    NSString *additionalInfoTrack2;
    NSString *responseType;
    NSString *batteryLevel;
    NSString *swipeCount;
    
    
    AudioUnit					rioUnit;
    AURenderCallbackStruct		inputProc;
    
    AudioStreamBasicDescription	thruFormat;
    AudioBufferList             bufferlist;
    AudioBuffer                 buf;
    AudioBuffer                 buf1;
    BOOL                        isDeviceConnected;
    long eventMask;
    long devCapabilities;
    
    Byte *commandBits;
    int commandBitsIndex;
#if TARGET_OS_IPHONE
    EAAccessory * _accessory;
    //EASession *   _session;
    EAAccessoryManager *eaAccessory;
    //AVAudioSession *audioSession;
#endif
    NSMutableString *dataFromiDynamo;
    NSMutableString *deviceProtocolString;
    NSMutableString *configParams;
    
    
    
    MTSCRADeviceType devType;
    
}

void audioReaderDelegate(void*self, int status);

//Initialize device
/*!
 This function opens a connction to the device
 
 @return
 - YES = Success
 - NO = Error
 
 @discussion To use this function to connect a device, it need to use **setConnectionType** first.
  And call **setAddress** to indicate which device should be open (optional step).

   After calling this function, call isDeviceOpened to make sure the device was successfully opend.
 */
-(BOOL) openDevice;

/*!
 It is a synchronize call to openDevice
 */
-(BOOL) openDeviceSync;

//Close device
/*!
 Close the current opened device
 
 @return - YES = Success 
 - NO = Error
 */
-(BOOL) closeDevice;

/*!
 It is a synchronize call to closeDevice
 */
-(BOOL) closeDeviceSync;

//Retrieves if the device is connected
/*!
    This function reports whether any compatible devices are connected to the host
 
 @return - YES = host is connected to a device
   - NO = host is not connected to a device
 */
- (BOOL) isDeviceConnected;

//Retrieve Masked Track1 if any
/*!
 Retrieves masked track 1 data after a cardholder swipes a card
 
 @discussion some of the data may be masked by special characters
 */
- (NSString *) getTrack1Masked;

//Retrieve Masked Track2 if any
/*!
 Retrieves masked track 2 data after a cardholder swipes a card
 
 @discussion some of the data may be masked by special characters
 */
- (NSString *) getTrack2Masked;

//Retrieve Masked Track3 if any
/*!
 Retrieves masked track 3 data after a cardholder swipes a card
 
 @discussion some of the data may be masked by special characters
 */
- (NSString *) getTrack3Masked;

//Retrieves existing stored Masked data, only supported for iDynamo, it will return a empty string in audio reader
- (NSString *) getMaskedTracks;

//Retrieve Encrypted Track1 if any
/*!
 Retrieves encrypted track 1 data after a cardholder swipes a card
 
 @discussion data is encrypted by MSR key with the current KSN **getKSN**
 */
- (NSString *) getTrack1;

//Retrieve Encrypted Track2 if any
/*!
 Retrieves encrypted track 2 data after a cardholder swipes a card
 
 @discussion data is encrypted by MSR key with the current KSN **getKSN**
 */
- (NSString *) getTrack2;

//Retrieve Encrypted Track3 if any
/*!
 Retrieves encrypted track 3 data after a cardholder swipes a card
 
 @discussion data is encrypted by MSR key with the current KSN **getKSN**
 */
- (NSString *) getTrack3;

/*!
 
  Retrieves encrypted magne print data after a cardholder swipes a card
  
  @discussion data is encrypted by MSR key or Magne Print key
 */
- (NSString *) getMagnePrint;

//Retrieve MagnePrint Status, only supported for iDynamo, it will return a empty string in audio reader
/*!
  Retrieves magne print status after a cardholder swipes a card
  
 @discussion For more information, see **D99875475**
 */
- (NSString *) getMagnePrintStatus;

//Retrieve Device Serial Number
/*!
  Retrieves device serial number after a cardholder swipes a card or read back the serial number from device.
 */
- (NSString *) getDeviceSerial;

///Retrieve Device Serial Number created by MagTek
- (NSString *) getMagTekDeviceSerial;

/*!
 Retrieve firmware part number and revision number
 
 @return a string of firmware
 */
- (NSString *) getFirmware;

///Retrieve Device Name
- (NSString *) getDeviceName;

///Retrieve Device Capabilities
- (NSString *) getDeviceCaps;

///Retrieve Device Status
- (NSString *) getDeviceStatus;

///Retrieve TLV Version
- (NSString *) getTLVVersion;

///Retrieve Device Part Number
- (NSString *) getDevicePartNumber;

//Retrieve Key Serial Number
/*!
 Retrieves MSR dukpt key serial number after cardholder swipes a card
 */
- (NSString *) getKSN;

//Retrieve individual tag value, only supported in audio reader
- (NSString *) getTagValue: (UInt32)tag;

//Retrieve MSR Capability
- (NSString *) getCapMSR;

//Retrieve Tracks Capability
- (NSString *) getCapTracks;

//Retrieve MagStripe Encryption Capability
- (NSString *) getCapMagStripeEncryption;

- (int) getMagnePrintLength;

/*!
 Send a direct command to the device
 
 @deprecated This function is deprecated, use sendcommandWithLength
 */
- (int) sendCommandToDevice:(NSString *)pData __attribute__((deprecated))  __deprecated_msg("use sendcommandWithLength instead.");

/*!
 send a command to device
 
 @param command hexadecimal string represents a command
 
 @return integer value for the status of command
 - 0 Success
 - 9 Error
 - 15 Busy
 */
- (int) sendcommandWithLength:(NSString *)command;

/*!
 Set the timeout for the synchronization
 
 Default value is 5000 milliseconds.
 
 @param timeoutMS time out value in milliseconds
 */
- (void) setTimeout : (NSUInteger) timeoutMS;

/*!
 Set the polling time frame for the synchronization call
 
 @param ms time frame value in milliseconds
 */
+ (void) setTimeFrame : (unsigned int) ms;

/*!
 Enable debug print to the xcode console
 
 @param enabled YES = Enabled, NO = disabled (default value)
 
 @discussion by default, debug print will not show.
 */
+ (void) enableDebugPrint : (BOOL) enabled;

/*!
 Send a command and get back the response
 
 It is a synchronization call for the **sendcommandWithLength:**
 
 @param command Hexadecimal string represents a command
 
 @return Hexadecimal string for the response
 */
- (NSString*)sendCommandSync:(NSString*)command;

//Sets the protocol String for iDynamo
/*!
 Sets the protocol string to open the device.
 
 From SDK "135.03" and up. This function is not need to be called to open device.
 Will be deprecated soon.
 
 @param protocolString A protocol string to match with the device
 */
- (void) setDeviceProtocolString:(NSString *)protocolString;
//Sets the config params for SDK
- (void) setConfigurationParams:(NSString *)pData;

/*!
 Setup the events to listen for audio reader
 
 @param event
    event can be combination of following value
- TRANS_EVENT_OK = Transaction succeeded
- TRANS_EVENT_START = Reader started sending data.
- TRANS_EVENT_ERROR = Reader failed sending data.
 */
- (void) listenForEvents:(UInt32)event;

///Retrieves the Device Type
- (long) getDeviceType;


///Retrieve card PAN
- (NSString*) getCardPAN;

///Retrieves the Length of teh PAN
- (int) getCardPANLength;

///Retrieve Session ID, only supported for iDynamo, it will return a empty string in audio reader
- (NSString *) getSessionID;

/*!
 Retrieved the whole card swipe response from the reader
 
 @discussion Data format may be different for different reader
 */
- (NSString *) getResponseData;

//Retrieves the Name in the Card
- (NSString *) getCardName;

//Retrieves the IIN in the Card
- (NSString *) getCardIIN;

//Retrieves the Last 4 of the PAN
- (NSString *) getCardLast4;

//Retrieves the Expiration Date
- (NSString *) getCardExpDate;

- (NSString*) getExpDateMonth;

- (NSString*) getExpDateYear;

///Retrieves the Service Code
- (NSString *) getCardServiceCode;

///Retrieves the Card Status
- (NSString *) getCardStatus;

///Retrieves the Track Decode Status
- (NSString *) getTrackDecodeStatus;

/// Retrives the track 1 decode status
/// - "00" Good data
/// - "01" Error decoding, maybe a bad track
/// - "02" Empty
- (NSString*) getTrack1DecodeStatus;

/// Retrives the track 2 decode status
/// - "00" Good data
/// - "01" Error decoding, maybe a bad track
/// - "02" Empty
- (NSString*) getTrack2DecodeStatus;

/// Retrives the track 3 decode status
/// - "00" Good data
/// - "01" Error decoding, maybe a bad track
/// - "02" Empty
- (NSString*) getTrack3DecodeStatus;

//Retrieve Response Type
- (NSString *) getResponseType;

//
/*!
 Sets the type of device to open or scan
 
 call **setDeviceType** with MAGTEKEDYNAMO, MAGTEKTDYNAMO and MAGTEKDYNAMAX will initialize the Bluetooth, it may trigger delegate **bleReaderStateUpdated**, call **setDeviceType** with MAGTEKIDYNAMO, MAGTEKKDYNAMO and MAGTEKIDYNAMO_G3 will use the Lightning connection
 
 @param deviceType Type of device. Can be one of following value
- MAGTEKAUDIOREADER (iOS Only)
- MAGTEKIDYNAMO, iDynamo, iDynamo5
- MAGTEKDYNAMAX, DynaMax
- MAGTEKEDYNAMO, eDynamo
- MAGTEKUSBMSR (MacOS Only) Any use reader
- MAGTEKKDYNAMO, kDynamo or iDynamo6
- MAGTEKTDYNAMO, tDynamo
- MAGTEKDYNAWAVE, DynaWave
- MAGTEKMDYNAMO, mDynamo, mDynamo Gen II
- MAGTEKIDYNAMO_G3, iDynamo 5 Gen III
 */
-(void) setDeviceType: (UInt32)deviceType;






/*!
 Retrieves device opened status
 
 @return - YES = Device is opened
  - NO = Device is not opened
 */
- (BOOL) isDeviceOpened;

/*!
 Clears all the buffer that is stored during card swipe or command response
 
 */
- (void) clearBuffers;

//Retrieves the battery Level
/*!
 Get device battery level
 
 @return 0-100
 
 @discussion It will return 100 when connected to USB
 */
- (long) getBatteryLevel;

//Retrieves the swipe count
- (long) getSwipeCount;

//Gets the current version of the SDK.
/*!
 @return String containing the SDK revision number.
                   Example : "135.01"
 */
- (NSString *) getSDKVersion;

//Retrieves the Operation Status
- (NSString *) getOperationStatus;

//Config Functions
- (NSString *) getEncryptionStatus;

// Stops scanning for surrounding Peripherals
/*!
 Stops scanning for surrounding Bluetooth LE Peripherals
 
 @method stopScanningForPeripherals
 @discussion after you find the device you want to connect to, you should call this function to stop scanning.
 */
- (void)stopScanningForPeripherals;

// Starts scanning for surrounding Peripherals
/*!
 Starts scanning for surrounding Bluetooth LE Peripherals
 
 @discussion This function retrives a list of avaible Bluetooth LE devices. After calling this function to locate the device
  you wish to connect to, use setAddress to tell the library which device you want to connect to.
  Use <code>stopScanningForPeripherals</code>  to stop scan.
 @see stopScanningForPeripherals
 @seealso onDeviceList:connectionType:deviceList:
 */
- (void)startScanningForPeripherals;

// Sets the UUID String
/*!
 @deprecated
 */
- (void)setUUIDString:(NSString *)uuidString __deprecated_msg("setUUIDString will be deprecated in future, use setAddress instead.");

// Retrieves the currently connected Peripheral
- (CBPeripheral *)getConnectedPeripheral;

// Retrieves the list of Peripherals that are in range and can be connected to
/*!
 Retrieves the array of discovered Bluetooth LE device in previous scanning.
 */
- (NSMutableArray *)getDiscoveredPeripherals;


// Retrieves the BLE device information
- (NSDictionary*)getDeviceInformationDictionary;

// Start EMV Transaction
/*!
 Start an EMV transaction
 
 @param timeLimit time out value for the transaction from 1 to 255 seconds, 0 is infinite (available on tDynamo, iDynamo 6)
 @param cardType a combination for MSR (1), Chip(2) and Contactless (4). For example, 7 means MSR + Chip + Contactless
 @param option combination for the following option
 - 0x01 Bypass PIN
 - 0x02 Force Online
 - 0x04 Acquierer not available
 - 0x20 NFC Tag
 - 0x80 Quick chip
 @param amount N12 format decimal for transaction amount. That is value for EMV Tag 9F02.
  For example : 00 00 00 09 99 09 means $ 999.09
 @param transactionType Transaction type for EMV flow. This is value for EMV Tag 9C. Can be value one of below.
 - 0x00 Purchase
 - 0x01 Cash advance
 - 0x02 Cash back
 - 0x04 Goods
 - 0x08 Services
 - 0x09 Cash back (Contactless)
 - 0x10 International Goods
 - 0x20 Refund
 - 0x40 International cash advance or cash back
 - 0x80 Domestic cash advance or cash back
 @param cashBack N12 format decimal for transaction cashback. That is value for EMV Tag 9F03.
 For example : 00 00 00 09 99 09 means $ 999.09
 @param currencyCode Currency code for the transaction.
 For example :
 - 0x0840 US Dollar
 - 0x0978 Euro
 - 0x0826 UK Pound
 @param reportingOption This byte indicate the level of transaction status notifications the host desires to receive. It can be one of those value
 - 0x00 Termination Status Only
 - 0x01 Major Status Change
 - 0x02 All Status Change
 
 @return integer value for the status of command
 - 0 Success
 - 9 Error
 - 15 Busy
 
 @discussion startTransaction will put device into EMV transaction state. In this state, it doesn't receive other non-emv command like 000103 (get property 3). And it can be cancelled by calling **cancelTransaction**.
 
 Device will ask user to present card, send back ARQC. Host application should response ARPC (normal transaction flow) then device will send back the final transaction result.
 */
- (int) startTransaction:(Byte)timeLimit cardType:(Byte)cardType option:(Byte)option amount:(Byte*)amount transactionType:(Byte)transactionType cashBack:(Byte*)cashBack currencyCode:(Byte*)currencyCode reportingOption:(Byte)reportingOption;

//Set User Selection for requests coming from card
/*!
 Sets the user selection result
 
 After host application received callback delegate **onUserSelectionRequest**, host application should prompt user to select and send back the user selectio result to device.
 
 @param status User behavior
 - 0x00 User selected successfuly
 - 0x01 User cannceled
 - 0x02 User didn't select, timed out
 @param selection User selection index, zero based.
 
 @return integer value for the status of command
 - 0 Success
 - 9 Error
 - 15 Busy
 */
- (int) setUserSelectionResult:(Byte)status selection:(Byte)selection;

//Sample to send resopond back to device
/*!
 Send the acquirer response to device to continue EMV transaction
 
 Host application should get transaction data processed and send back the response data to device. In quick chip mode, this call is not need and transaction will continue automatically.
 
 @param response Hexadecimal string for the response data following TLV message
 @param length Length of the response in bytes
 
 @return integer value for the status of command
 - 0 Success
 - 9 Error
 - 15 Busy
 */
- (int) setAcquirerResponse:(Byte*)response length:(int)length;

//Cancel Transaction
/*!
 Cancels a transaction while waiting for user to present a card.
 
 After user present card, you cannot cancel transaction.
 
 @return integer value for the status of command
 - 0 Success
 - 9 Error
 - 15 Busy
 */
- (int) cancelTransaction;

//Check if device support EMV
/*!
 Check if device support EMV transaction
 
 @return Boolean vlaue
 - YES = EMV is supported
 - NO = EMV is not supported
 */
- (BOOL) isDeviceEMV;

//send extended command to EMV Devices;
/*!
 Send a extended command to device (EMV device or iDynamo 5 Gen III)
 
 Command response will returned in event message **onDeviceExtendedResponse**
 
 @param commandIn Hexadecimal string of the byte array for the extended command. The first two bytes represent command id. The next two indicate the length of the following data.
 
 @return integer value for the status of command
 - 0 Success
 - 9 Error
 - 15 Busy
 */
- (int) sendExtendedCommand:(NSString*)commandIn;

/*!
 Send a extended command to device (EMV device or iDynamo 5 Gen III) and get back the response
 
 It is a syncrhoization call to **sendExtendedCommand**
 
 @param commandIn Hexadecimal string of the byte array for the extended command. The first two bytes represent command id. The next two indicate the length of the following data.
 
 @return A hexadecimal string contains the response data
 */
- (NSString*) sendExtendedCommandSync :(NSString*) commandIn;

- (int) getLastError;

//Return Card Data TLV Pay load
- (NSString*) getTLVPayload;

/*!
 Set device address for BLE devices.
 
 @param address Bluetooth LE address, received in callback delegate onDeviceList:connectionType:deviceList:
 */
- (void)setAddress:(NSString *)address;

//Get bluetooth device signal strength, only apply to Bluetooth LE devices.
- (int)getBluetoothRSSI;

/*!
 Sets the connection type
 
 @param connectionType Connection type to connect to device. can be one of following values.
 - BLE Bluetooth LE device, DynaMax
 - BLE_EMV Bluetooth LE EMV device, eDynamo, tDynamo
 - USB (MacOS Only) Any USB reader
 - Lightning (iOS Only)
 */
- (void) setConnectionType: (ConnectionType)connectionType;
- (ConnectionType)getConnectionType;


/*!
    @method updateFirmware, update device firmware
    @param firmwareType : 0 main
    @param firmwareData : firmware data
    @return 0 for success
    @discussion it will change the device into boot loader mode if neccessory and reset device when need to.
 */

- (int) updateFirmware: (int) firmwareType Data :(NSData*) firmwareData;

///
///#if DEBUG
///- (void) setFirmwarePayloadSize : (int) payloadSize;
///#endif

/*!
 Send a NFC command to Type 2 tag card (tDynamo, iDynamo6)
 
 It is a wrapped extended command function to send NFC command
 
 @param command Type 2 command or NTag command
 @param lastCommand It is a last NFC command?
 - YES It is last command
 - NO It is not last command. Can have more command to send
 @param encrypt It indicates device send back response in encrypted data format
 - YES response will be encrypted
 - NO reponse will no be encrypted
 
 @return integer value for the status of command
 - 0 Success
 - 9 Error
 - 15 Busy
 */
- (int) sendNFCCommand: (NSString*) command lastCommand :(BOOL) lastCommand encrypt : (BOOL) encrypt;

/*!
 Send a NFC command to Mifare classic tag card (tDynamo, iDynamo6)
 
 It is a wrapped extended command function to send NFC command
 
 @param command Mifare classic 1k/4k command
 @param lastCommand It is a last NFC command?
 - YES It is last command
 - NO It is not last command. Can have more command to send
 @param encrypt It indicates device send back response in encrypted data format
 - YES response will be encrypted
 - NO reponse will no be encrypted
 
 @return integer value for the status of command
 - 0 Success
 - 9 Error
 - 15 Busy
 */
- (int) sendClassicNFCCommand: (NSString*) command lastCommand :(BOOL) lastCommand encrypt : (BOOL) encrypt;

/*!
 Send a NFC command to Mifare DESFire tag card (tDynamo, iDynamo6)
 
 It is a wrapped extended command function to send NFC command
 
 @param command Mifare DESFire command
 @param lastCommand It is a last NFC command?
 - YES It is last command
 - NO It is not last command. Can have more command to send
 @param encrypt It indicates device send back response in encrypted data format
 - YES response will be encrypted
 - NO reponse will no be encrypted
 
 @return integer value for the status of command
 - 0 Success
 - 9 Error
 - 15 Busy
 */
- (int) sendDESFireNFCCommand: (NSString*) command lastCommand :(BOOL) lastCommand encrypt : (BOOL) encrypt;

/*!
 Send a NFC command to NFC tag card (tDynamo, iDynamo6) and get back response
 
 Synchronization call to send a NFC command
 
 @param command NFC command
 @param lastCommand It is a last NFC command?
 - YES It is last command
 - NO It is not last command. Can have more command to send
 @param encrypt It indicates device send back response in encrypted data format
 - YES response will be encrypted
 - NO reponse will no be encrypted
 
 @return Extended response for the command
 */
- (NSString*) sendNFCCommandSync: (NSString*) command lastCommand :(BOOL) lastCommand encrypt : (BOOL) encrypt;

/*!
 Send a NFC command to NFC tag card (tDynamo, iDynamo6) and get back response in callback
 
 Asynchronization call to send a NFC command
 
 @param command NFC command
 @param lastCommand It is a last NFC command?
 - YES It is last command
 - NO It is not last command. Can have more command to send
 @param encrypt It indicates device send back response in encrypted data format
 - YES response will be encrypted
 - NO reponse will no be encrypted
 @param response A code block to receive the extended response for the NFC command
 
 @return integer value for the status of command
 - 0 Success
 - 9 Error
 - 15 Busy
 */
- (int) sendNFCCommandAsync: (NSString*) command lastCommand :(BOOL) lastCommand encrypt : (BOOL) encrypt response : (void (^)(NSString*)) response;

//MTSCRA Delegate
/*!
 Delegate to receive the callback
 
 To declare delegate:
 ~~~
 class ViewController: UIViewController, MTSCRAEventDelegate {
 ...
 }
 ~~~
 
 To assign delegate:
 ~~~
     lib.delegate = self
 ~~~
 */
@property (nonatomic, weak) id <MTSCRAEventDelegate> delegate;

/*!
 Setup a callback to received the debug information.
 
 @discussion it send back **MTDebugInfo** interface to tell the developer the debug information is coming.
 
 Sample code:
 @link
 
 lib.debugInfoCallback = {
        x in
     print("debug.name  - " + (x?.name ?? ""))
     print("debug.value - " + (x?.value ?? ""))
 }
 
 */
@property (nonatomic, strong) MTSCRADebugCallback debugInfoCallback;




#pragma mark MAC_OSX_FUNCTIONS
/*!
 Request scan device list to connect for the connection type
 
 It may need call **setDeviceType** first to scan **BLE_EMV** devices. Host may received multiple time of the device list by delegate callback **onDeviceList:connectionType:deviceList:**
 
 @param type Connection type for the scanning
 - BLE  DynaMax
 - BLE_EMV eDynamo, tDynamo
 - USB (MacOS Only)
 */
- (void)requestDeviceList:(ConnectionType)type;

// USB Only
/*!
 Get the product ID (USB PID) (MacOS Only)
 
 @return A short integer for product id
 */
- (int)getProductID;

@end
