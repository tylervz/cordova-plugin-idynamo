var exec = require('cordova/exec');

module.exports = {
	init: function (callback) {
    	var connected = false;
    	exec(function (result) {
            if (!connected) {
                callback(null, result);
                connected = true;
            } else {
                cordova.fireWindowEvent("magtekEvent", result);
            }
        },
        function (error) {
            callback(error)
    	}, 'CDVMagtek', 'init', []);
    },
    openDevice: function (success, error) {
        exec(success, error, "CDVMagtek", "openDevice", []);
    },
    closeDevice: function (success, error) {
        exec(success, error, "CDVMagtek", "closeDevice", []);
    },
};