/**
 * Listens for the app launching then creates the window
 *
 * @see http://developer.chrome.com/apps/app.window.html
 */
chrome.app.runtime.onLaunched.addListener(function(launchData) {
  chrome.app.window.create('index.html', {
    id: 'fileWin',
    bounds: { width: 800, height: 800 }}, function(win) {
    win.contentWindow.launchData = launchData;
  });
});