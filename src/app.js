Pebble.addEventListener('ready', function() {
  console.log('PebbleKit JS ready!');
});

Pebble.addEventListener('showConfiguration', function() {
  var url = 'https://rawgit.com/Herschee/Watchdog/master/settingsPage/index.html';
  console.log('Showing configuration page: ' + url);

  Pebble.openURL(url);
});

Pebble.addEventListener('webviewclosed', function(e) {
  var configData = JSON.parse(decodeURIComponent(e.response));
  console.log('Configuration page returned: ' + JSON.stringify(configData));

	// Following keys: name, phone (String), timer & vibrate time in seconds
	// For more information, check out the settings javascript (Within the html page)
	
	// Prepare AppMessage payload
  var dict = {
    'KEY_PHONE': configData['phone'],
    'KEY_NAME': configData['name'],
    'KEY_TIMER': configData['timer'],
    'KEY_VIBRATE': configData['vibrate']
  };

  console.log(dict);

  // Send this info to the app
  Pebble.sendAppMessage(dict, function() {
    console.log('Send successful: ' + JSON.stringify(dict));
  }, function(error) {
    console.log('Send failed!' + error.response);
  });
});
