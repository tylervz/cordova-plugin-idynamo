var exec = require('cordova/exec');

module.exports = {
	init: function (callback) {
    	var connected = false;
    	exec(function (result) {
            if (!connected) {
                callback(null, result);
                connected = true;
            } else {
                self.alert(result)
                cordova.fireWindowEvent("magtekEvent", result);
            }
        },
        function (error) {
            callback(error)
    	}, 'CDVMagtek', 'init', []);
    },
    // openDevice: function () {
    //     exec(function (result) {
    //         // cordova.fireWindowEvent("magtekEvent", result);
    //         self.alert(result);
    //     },function (error) {
    //         self.alert("Things went downhill, sorry... :\r\r" + error);
    //     }, "CDVMagtek", "openDevice", []);
    // },
    openDevice: function (success, error) {
        exec(success, error, "CDVMagtek", "openDevice", []);
    },
    closeDevice: function (success, error) {
        exec(success, error, "CDVMagtek", "closeDevice", []);
    },
};