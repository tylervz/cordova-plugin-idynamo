# Magtek Plugin

Cordova plugin for [Magtek](https://www.magtek.com/) iDynamo devices, with this plugin you can detect swipe events on an iDynamo device to obtain the card information.

# Use
This plugin defines global **magtek** object.

Although in the global scope, it is not available until after the deviceready event.
```javascript
document.addEventListener("deviceready", onDeviceReady, false);
function onDeviceReady() {
    console.log(magtek);
}
```

Note: Plugin requires the following frameworks, although plugin adds them, double check that are properly referenced in xcode project:

- AVFoundation.framework
- ExternalAccessory.framework
- libstdc++.dylib


# Install

Install using `cordova plugin add https://github.com/auctifera-josed/cordova-plugin-idynamo`

## Configuration

This plugins requires the following usage descriptions in the `info.plist`:

* [`NSBluetoothPeripheralUsageDescription`](https://developer.apple.com/documentation/bundleresources/information_property_list/nsbluetoothperipheralusagedescription) describes the reason the app is requesting the ability to connect to Bluetooth peripherals.
* [`NSBluetoothAlwaysUsageDescription`](https://developer.apple.com/documentation/bundleresources/information_property_list/nsbluetoothalwaysusagedescription) describes the reason the why the app needs access to Bluetooth.

To add these entries into the `info.plist`, you can add `edit-config` tags in your `config.xml` like this:

```
<edit-config target="NSBluetoothPeripheralUsageDescription" file="*-Info.plist" mode="merge">
    <string>Needs Bluetooth access to connect to a MagTek card reader</string>
</edit-config>

<edit-config target="NSBluetoothAlwaysUsageDescription" file="*-Info.plist" mode="merge">
    <string>Needs Bluetooth access to connect to a MagTek card reader</string>
</edit-config>
```

Apple will reject apps that use this plugin but do not have these usage descriptions. 

# Example
```javascript
window.addEventListener('magtekEvent', function (e) {
  switch (e.dataType) {
    case 'onDataReceived':
      console.log(e.data);
      break;
    default:
      console.log(e);
  }
});

magtek.init(function(err,res){console.log(err);console.log(res);});

var q = function(res){console.log(res);}
magtek.openDevice(q,q);
//make a swipe
magtek.closeDevice(q,q); //Closing the device saves battery life
```
# API Reference



Function List
- [init(callback)](#init)
- [openDevice(success, error)](#opendevice)
- [closeDevice(success, error)](#closedevice)

[Event List](#events)
- onDataReceived
- onDeviceConnectionDidChange
- cardSwipeDidStart
- cardSwipeDidGetTransError

---

# Functions

## init
The `init(callback)` function initializes the magtek instance.

callback eg: `function(err,res){console.log(err);console.log(res);}`

## openDevice
The `openDevice(success, error)` method starts the magtek device.

## closeDevice
The `closeDevice(success, error)` method stops the magtek device.

---

# Events
Listen to Magtek events as cases of the **magtekEvent** event and get the event `data` attribute: 

```javascript
window.addEventListener('magtekEvent', function (e) {
  switch (e.dataType) {
    case 'onDeviceConnectionDidChange':
      console.log(e.data);
      break;
    case 'onDataReceived':
      console.log(e.data);
      break;
    default:
      console.log(e);
  }
});
```

| Event | description | data  |
| --- | -------- | -------- |
| cardSwipeDidStart  | Card swipe has started| null |
| cardSwipeDidGetTransError | Card swipe got an error during transmission. | null |
| onDeviceConnectionDidChange | Device connection changed whether from close to open or vice versa. | String: Connected/Disconnected |
| onDataReceived | Return a card object type with card swipe data. | JSON: Example below |

onDataReceived object:
```javascript
{
  "TrackStatus": "",
  "Track1Status": "",
  "Track2Status": "",
  "Track3Status": "",
  "EncryptionStatus": "",
  "BatteryLevel": 0,
  "SwipeCount": 0,
  "TrackMasked": "",
  "Track1Masked": "",
  "Track2Masked": "",
  "Track3Masked": "",
  "Track1Encrypted": "",
  "Track2Encrypted": "",
  "Track3Encrypted": "",
  "CardPAN": "",
  "MagnePrintEncrypted": "",
  "MagnePrintLength": 0,
  "MagnePrintStatus": "",
  "SessionID": "",
  "CardIIN": "",
  "CardName": "",
  "CardLast4": "",
  "CardExpDate": "",
  "CardExpDateMonth": "",
  "CardExpDateYear": "",
  "CardSvcCode": "",
  "CardPANLength": 0,
  "KSN": "",
  "DeviceSerialNumber": "",
  "MagTekSerialNumber": "",
  "Firmware": "",
  "DeviceName": "",
  "TLVPayload": "",
  "DeviceCapMSR": "",
  "OperationStatus": "",
  "CardStatus": "",
  "RawData": ""
}
```
