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

	// configure this dictionary you fucking idiot to save the settings from the rawgit
	// don't know what a dictionary is? https://en.wikipedia.org/wiki/Associative_array
	// EDIT: Nikita is dumb so I did it - Henry
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

  // Send this shit to the app, obviously
  Pebble.sendAppMessage(dict, function() {
    console.log('Send successful: ' + JSON.stringify(dict));
  }, function(error) {
    console.log('Send failed!' + error.response);
  });
});