Pebble.addEventListener('showConfiguration', function(e) {
  // Show config page
  Pebble.openURL('https://reddit.com');
});

// Close config page and return data
location.href = 'pebblejs://close#success';
