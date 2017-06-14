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

magtek.init();

var q = function(res){console.log(res);}
magtek.openDevice(q,q);
//make a swipe
magtek.closeDevice(q,q); //Closing the device saves battery live
```
# API Reference



Function List
- [init()](#init)
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
The `init()` function initializes the magtek instance.

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
  "Track.Status": "",
  "Track1.Status": "",
  "Track2.Status": "",
  "Track3.Status": "",
  "Encryption.Status": "",
  "Battery.Level": 0,
  "Swipe.Count": 0,
  "Track.Masked": "",
  "Track1.Masked": "",
  "Track2.Masked": "",
  "Track3.Masked": "",
  "Track1.Encrypted": "",
  "Track2.Encrypted": "",
  "Track3.Encrypted": "",
  "Card.PAN": "",
  "MagnePrint.Encrypted": "",
  "MagnePrint.Length": 0,
  "MagnePrint.Status": "",
  "SessionID": "",
  "Card.IIN": "",
  "Card.Name": "",
  "Card.Last4": "",
  "Card.ExpDate": "",
  "Card.ExpDateMonth": "",
  "Card.ExpDateYear": "",
  "Card.SvcCode": "",
  "Card.PANLength": 0,
  "KSN": "",
  "Device.SerialNumber": "",
  "MagTek.SerialNumber": "",
  "Firmware": "",
  "Device.Name": "",
  "TLV_Payload": "",
  "DeviceCapMSR": "",
  "Operation.Status": "",
  "Card.Status": "",
  "Raw_Data": ""
}
```
