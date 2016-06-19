var CONFIG_URL = "http://martinchamarro.com/pebble/stats/settings.html";
var WEBVIEW_CANCELLED = "CANCELLED";
var DEMO_URL = "http://martinchamarro.com/pebble/stats/demo.json";
var KEY_URL = "url";

var mURL;

function saveConfig(config) {
	if (config) {
		console.log(config);
		// Save URL
		var url = config.url;
		if (url) {
			localStorage.setItem(KEY_URL, url);
			mURL = url;
		}
	}
}

function loadConfig() {
	// Load URL
	var url = localStorage.getItem(KEY_URL);
	if (url) {
		mURL = url;
	} else {
		mURL = DEMO_URL;
	}
}

function requestStats() {
	if (mURL) {
		var xmlhttp = new XMLHttpRequest();
		xmlhttp.open("GET", mURL, true);
		xmlhttp.setRequestHeader("User-Agent", "Stats for Pebble 1.0");
		xmlhttp.onreadystatechange = function() {
			if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
				try {
					console.log(xmlhttp.responseText);
					var json = JSON.parse(xmlhttp.responseText);
					sendStatsToPebble(json);
				} catch (err) {
					console.log("Error loadings stats: " + err.message);
				}
			}
		};
		xmlhttp.send();
	}
}

function sendStatsToPebble(json) {
	var dictionary = {
		"KEY_ICON_0" : json.data[0].icon,
		"KEY_COLOR_0" : GColorFromHex(json.data[0].color),
		"KEY_VALUE_0" : json.data[0].value,
		"KEY_ICON_1" : json.data[1].icon,
		"KEY_COLOR_1" : GColorFromHex(json.data[1].color),
		"KEY_VALUE_1" : json.data[1].value,
		"KEY_ICON_2" : json.data[2].icon,
		"KEY_COLOR_2" : GColorFromHex(json.data[2].color),
		"KEY_VALUE_2" : json.data[2].value,
		"KEY_ICON_3" : json.data[3].icon,
		"KEY_COLOR_3" : GColorFromHex(json.data[3].color),
		"KEY_VALUE_3" : json.data[3].value,
		"KEY_BACKGROUND_COLOR" : GColorFromHex(json.background_color),
		"KEY_VIBRATION" : json.vibration
	};
	sendDictionaryToPebble(dictionary);
}

function sendDictionaryToPebble(dictionary) {
	console.log("Sending dictionary: " + dictionary);
	Pebble.sendAppMessage(dictionary,
		function(e) {
			console.log("Dictionary sent to Pebble successfully!");
		},
		function(e) {
			console.log("Error sending dictionary to Pebble!");
		}
	);
}

function GColorFromHex(hex) {
	hex = hex.replace('#', '');
    var hexNum = parseInt(hex, 16);
    var a = 192;
    var r = (((hexNum >> 16) & 0xFF) >> 6) << 4;
    var g = (((hexNum >>  8) & 0xFF) >> 6) << 2;
    var b = (((hexNum >>  0) & 0xFF) >> 6) << 0;
	var color = a + r + g + b;
	// console.log("HexToColor: " + hex + " -> " + color);
    return color;
}

// Listen for when the watchface is opened
Pebble.addEventListener('ready', 
	function(e) {
		console.log("PebbleKit JS ready!");
		loadConfig();
		requestStats();
	}
);

// Listen for when an AppMessage is received
Pebble.addEventListener('appmessage',
	function(e) {
		console.log("AppMessage received!");
	}
);

// Listen for when the user wants to show the application configuration page
Pebble.addEventListener("showConfiguration", function(e) {
	Pebble.openURL(CONFIG_URL);
});

// Listen for when the user closes the configuration screen
Pebble.addEventListener("webviewclosed",
	function(e) {
		if (e.response && e.response != WEBVIEW_CANCELLED) {
			console.log("Callback to save settings: " + e.response);
			var config = JSON.parse(e.response);
			saveConfig(config);
		}
	}
);