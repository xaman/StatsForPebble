var CONFIG_URL = "http://martinchamarro.com/pebble/stats/settings.html";
var WEBVIEW_CANCELLED = "CANCELLED";
var DEMO_URL = "http://martinchamarro.com/pebble/stats/demo.json";
var KEY_URL = "url";
var KEY_INTERVAL = "interval";
var DEFAULT_INTERVAL = 30;

var url;
var interval;

function saveConfig(config) {
	if (config) {
		saveUrl(config);
		saveInterval(config);
	}
}

function saveUrl(config) {
	if (config.url) {
		localStorage.setItem(KEY_URL, config.url);
		url = config.url;
	}
}

function saveInterval(config) {
	if (config.interval) {
		localStorage.setItem(KEY_INTERVAL, config.interval);
		interval = config.interval;
	}
}

function loadConfig() {
	var loadedUrl = localStorage.getItem(KEY_URL);
	url = loadedUrl ? loadedUrl : DEMO_URL;
	var loadedInterval = localStorage.getItem(KEY_INTERVAL);
	interval = loadedInterval ? loadedInterval : DEFAULT_INTERVAL;
}

function requestStats() {
	if (url) {
		var xmlhttp = new XMLHttpRequest();
		xmlhttp.open("GET", url, true);
		xmlhttp.onreadystatechange = function() {
			if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
				try {
					console.log(xmlhttp.responseText);
					var json = JSON.parse(xmlhttp.responseText);
					sendInfoToWatchface(json);
				} catch (err) {
					console.log("Error loadings stats: " + err.message);
				}
			}
		};
		xmlhttp.send();
	}
}

function sendInfoToWatchface(json) {
	var dictionary = {
		"FIRST_ICON" : json.data[0].icon,
		"FIRST_COLOR" : convertHexToGColor(json.data[0].color),
		"FIRST_VALUE" : json.data[0].value,
		"SECOND_ICON" : json.data[1].icon,
		"SECOND_COLOR" : convertHexToGColor(json.data[1].color),
		"SECOND_VALUE" : json.data[1].value,
		"THIRD_ICON" : json.data[2].icon,
		"THIRD_COLOR" : convertHexToGColor(json.data[2].color),
		"THIRD_VALUE" : json.data[2].value,
		"FOURTH_ICON" : json.data[3].icon,
		"FOURTH_COLOR" : convertHexToGColor(json.data[3].color),
		"FOURTH_VALUE" : json.data[3].value,
		"BACKGROUND_COLOR" : convertHexToGColor(json.background_color),
		"VIBRATION" : json.vibration,
		"INTERVAL" : parseInt(interval)
	};
	sendDictionaryToWatchface(dictionary);
}

function sendDictionaryToWatchface(dictionary) {
	console.log("Sending dictionary: " + JSON.stringify(dictionary));
	Pebble.sendAppMessage(dictionary,
		function(e) {
			console.log("Dictionary sent to Pebble successfully!");
		},
		function(e) {
			console.log("Error sending dictionary to Pebble!");
		}
	);
}

function convertHexToGColor(hex) {
	hex = hex.replace('#', '');
    var hexNum = parseInt(hex, 16);
    var a = 192;
    var r = (((hexNum >> 16) & 0xFF) >> 6) << 4;
    var g = (((hexNum >>  8) & 0xFF) >> 6) << 2;
    var b = (((hexNum >>  0) & 0xFF) >> 6) << 0;
	var color = a + r + g + b;
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
		console.log("Watchface message received!");
		loadConfig();
		requestStats();
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
			requestStats();
		}
	}
);