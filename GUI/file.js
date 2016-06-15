var chosenEntry = null;
var chooseFileButton = document.querySelector('#choose_file');
var chooseDirButton = document.querySelector('#choose_dir');
var saveFileButton = document.querySelector('#save_file');
var savefFileButton = document.querySelector('#save_filef');
var output = document.querySelector('output');
var textarea = document.querySelector('textarea');

var testStorageValue = '0';
var testV = 0;

var Mx_Max ='0.0';
var My_Max ='0.0';
var Mz_Max ='0.0';
var Mx_Min ='0.0';
var My_Min ='0.0';
var Mz_Min ='0.0';

var PID_String='1,1,1,1,1,1,1,1,1';


function errorHandler(e) {
  console.error(e);
}

function displayEntryData(theEntry) {
  if (theEntry.isFile) {
    chrome.fileSystem.getDisplayPath(theEntry, function(path) {
      document.querySelector('#file_path').value = path;
    });
    theEntry.getMetadata(function(data) {
      document.querySelector('#file_size').textContent = data.size;
    });    
  }
  else {
    document.querySelector('#file_path').value = theEntry.fullPath;
    document.querySelector('#file_size').textContent = "N/A";
  }
}

function readAsText(fileEntry, callback) {
  fileEntry.file(function(file) {
    var reader = new FileReader();

    reader.onerror = errorHandler;
    reader.onload = function(e) {
      callback(e.target.result);
    };

    reader.readAsText(file);
  });
}

function writeFileEntry(writableEntry, opt_blob, callback) {
  if (!writableEntry) {
    output.textContent = 'Nothing selected.';
    return;
  }

  writableEntry.createWriter(function(writer) {

    writer.onerror = errorHandler;
    writer.onwriteend = callback;

    // If we have data, write it to the file. Otherwise, just use the file we
    // loaded.
    if (opt_blob) {
      writer.truncate(opt_blob.size);
      waitForIO(writer, function() {
        writer.seek(0);
        writer.write(opt_blob);
      });
    } 
    else {
      chosenEntry.file(function(file) {
        writer.truncate(file.fileSize);
        waitForIO(writer, function() {
          writer.seek(0);
          writer.write(file);
        });
      });
    }
  }, errorHandler);
}

function waitForIO(writer, callback) {
  // set a watchdog to avoid eventual locking:
  var start = Date.now();
  // wait for a few seconds
  var reentrant = function() {
    if (writer.readyState===writer.WRITING && Date.now()-start<4000) {
      setTimeout(reentrant, 100);
      return;
    }
    if (writer.readyState===writer.WRITING) {
      console.error("Write operation taking too long, aborting!"+
        " (current writer readyState is "+writer.readyState+")");
      writer.abort();
    } 
    else {
      callback();
    }
  };
  setTimeout(reentrant, 100);
}

// for files, read the text content into the textarea
function loadFileEntry(_chosenEntry) {
  chosenEntry = _chosenEntry;
  chosenEntry.file(function(file) {
    readAsText(chosenEntry, function(result) {
		//
		document.getElementById('file_path').value = result;
      //textarea.value = result; /// NEED TO REPLACE NATE
    });
    // Update display.
    saveFileButton.disabled = false; // allow the user to save the content
    displayEntryData(chosenEntry);
  });
}

// for directories, read the contents of the top-level directory (ignore sub-dirs)
// and put the results into the textarea, then disable the Save As button
function loadDirEntry(_chosenEntry) {
  chosenEntry = _chosenEntry;
  if (chosenEntry.isDirectory) {
    var dirReader = chosenEntry.createReader();
    var entries = [];

    // Call the reader.readEntries() until no more results are returned.
    var readEntries = function() {
       dirReader.readEntries (function(results) {
        if (!results.length) {
          //textarea.value = entries.join("\n"); /// Disabled Nate, fix baud rate issue. 
          saveFileButton.disabled = true; // don't allow saving of the list
          displayEntryData(chosenEntry);
        } 
        else {
          results.forEach(function(item) { 
            entries = entries.concat(item.fullPath);
          });
          readEntries();
        }
      }, errorHandler);
    };

    readEntries(); // Start reading dirs.    
  }
}

function loadInitialFile(launchData) {
  if (launchData && launchData.items && launchData.items[0]) {
    loadFileEntry(launchData.items[0].entry);
	 console.info("1st Line Ran");
  } 
  else {
    // see if the app retained access to an earlier file or directory
    console.info("2nd Line Ran");
	chrome.storage.local.get('testStorage', function(items) {
		if(items.testStorage)
		{
			console.info("test sttorage is=" +items.testStorage );
			testV = parseInt(items.testStorage);
			myFunction();
		}
	});
	
	chrome.storage.local.get('Mx_Max', function(items) {
		if(items.Mx_Max)
		{
			Mx_Max = items.Mx_Max;	
		}
	});
	
	chrome.storage.local.get('My_Max', function(items) {
		if(items.My_Max)
		{
			My_Max = items.My_Max;	
		}
	});	
	
	chrome.storage.local.get('Mz_Max', function(items) {
		if(items.Mz_Max)
		{
			Mz_Max = items.Mz_Max;	
		}
	});	
	
	chrome.storage.local.get('Mx_Min', function(items) {
		if(items.Mx_Min)
		{
			Mx_Min = items.Mx_Min;	
		}
	});

	chrome.storage.local.get('My_Min', function(items) {
		if(items.My_Min)
		{
			My_Min = items.My_Min;	
		}
	});

	chrome.storage.local.get('Mz_Min', function(items) {
		if(items.Mz_Min)
		{
			Mz_Min = items.Mz_Min;	
		}
		
		if(Math.abs(parseFloat(Mz_Min))>1) // Ensure mag data is non zero 
		{
				console.log("Restoring Mag Calibration Data: "+ Mz_Min);
				SetMagFromSavedData();
		}
	});
		
	chrome.storage.local.get('PID_String', function(items) {
		if(items.PID_String)
		{
			PID_String= items.PID_String;	
		}
			var PID_Array = PID_String.split(',');
		console.log('PID String is:'+PID_String+'and length is: '+PID_Array.length.toString());
	
		if(PID_Array.length==9) // String is not corrupt
		{
				console.log("Restoring PID Values");
				Init_Slider(PID_Array);
		}		
	});
	
	
	
	chrome.storage.local.get('chosenFile', function(items) {
      if (items.chosenFile) {
        // if an entry was retained earlier, see if it can be restored
        chrome.fileSystem.isRestorable(items.chosenFile, function(bIsRestorable) {
          // the entry is still there, load the content
          console.info("Restoring " + items.chosenFile);
          chrome.fileSystem.restoreEntry(items.chosenFile, function(chosenEntry) {
            if (chosenEntry) {
              chosenEntry.isFile ? loadFileEntry(chosenEntry) : loadDirEntry(chosenEntry);
            }
          });
        });
      }
    });
	
  }
}

chooseFileButton.addEventListener('click', function(e) {
  var accepts = [{
	  extensions: ['csv']
  }];
  chrome.fileSystem.chooseEntry({type: 'openFile', accepts: accepts}, function(theEntry) {
    if (!theEntry) {
      output.textContent = 'No file selected.';
      return;
    }
    // use local storage to retain access to this file
    chrome.storage.local.set({'chosenFile': chrome.fileSystem.retainEntry(theEntry)});
    loadFileEntry(theEntry);
  });
});


function createFile()
{
	var myDate = new Date();
	
	var myFileName= (myDate.getMonth()+1).toString()+'_'+myDate.getDay().toString()+'_'+myDate.getHours().toString()+'_'+myDate.getMinutes().toString()+'log.csv';
	if (chosenEntry == null) {
      console.log('No file directory loaded!')
      return;
    }

	console.log("Creating file: "+myFileName);
	chosenEntry.getFile(myFileName,{create: true}, function(fileEntry)
	{
	   console.log(fileEntry);
	   myNewEntry =fileEntry
	});
	
}

var myNewEntry;

chooseDirButton.addEventListener('click', function(e) {
  chrome.fileSystem.chooseEntry({type: 'openDirectory'}, function(theEntry) {
    if (!theEntry) {
      output.textContent = 'No Directory selected.';
      return;
    }

	console.log("Creating file")
	theEntry.getFile('tzzzzest.csv',{create: true}, function(fileEntry)
	{
	   console.log(fileEntry);
	   myNewEntry =fileEntry
	});
	
	chrome.storage.local.set({'chosenFile': chrome.fileSystem.retainEntry(theEntry)});
    loadDirEntry(theEntry);
	
  });
});


var sleepTimer = 0;

function writeToLogFile(myData)
{
	while(myNewEntry == null)
	{
		setTimeout(function(){while(true){}}, 1000); //wait ten seconds before continuing
		sleepTimer++;
		if(sleepTimer>10)
		{
			console.log("sleep timer expired");
			break;
			
		}
	}
	 sleepTimer = 0;
	
	
	if(myNewEntry != null)
	{
		var blob = new Blob(myData, {type: 'text/plain'});
		myNewEntry.createWriter(function(writer) {
		  writer.onerror = function(e) {
			  console.log('something went wrong!');
		  };
		  writer.onwriteend = function(e) {
			console.log('write complete');
		  };
		  writer.seek(writer.length); // Start write position at EOF.
		  writer.write(blob);
		}, errorHandler);		
	}
	else
	{
		console.log('Invalid file handle!')
	}
}

var myFileEntry;
var testFileEntry;

saveFileButton.addEventListener('click', function(e) {
  var config = {type: 'saveFile', suggestedName: chosenEntry.name};
  chrome.fileSystem.chooseEntry(config, function(writableEntry) {
    var blob = new Blob([file_path.value], {type: 'text/plain'});
    myFileEntry = writableEntry;
	writeFileEntry(writableEntry, blob, function(e) {
      output.textContent = 'Write complete :)';
    });
  });
});


savefFileButton.addEventListener('click',function(e) {
	
	var myData = "I really hate javascript files"; 
	var blob = new Blob([myData], {type: 'text/plain'});
	//writeFileEntry(myNewEntry, blob, function(e) {
    //  console.log("Attempting to write to a file");
    //});
	
	myNewEntry.createWriter(function(writer) {
		  writer.onerror = function(e) {
			  console.log('something went wrong!');
		  };
		  writer.onwriteend = function(e) {
			console.log('write complete');
		  };
		  writer.seek(writer.length); // Start write position at EOF.
		  writer.write(blob);
	}, errorHandler);

	console.log("Hopefully this worked ");
	
});

var myFileSystem; 
var myVolumes;

loadInitialFile(launchData); // just added to test peristant storage. 


/*
chrome.fileSystem.getVolumeList( function(VolumeList)
{
	myVolumes =VolumeList; 
	console.log(VolumeList);
});
*/

/*
function myEntry(entry)
{
	myFileEntry = entry;		
}
*/

/*
// Support dropping a single file onto this app.
var dnd = new DnDFileController('body', function(data) {
  chosenEntry = null;
  for (var i = 0; i < data.items.length; i++) {
    var item = data.items[i];
    if (item.kind == 'file' &&
        item.type.match('text/*') &&
        item.webkitGetAsEntry()) {
      chosenEntry = item.webkitGetAsEntry();
      break;
    }
  };

  if (!chosenEntry) {
    output.textContent = "Sorry. That's not a text file.";
    return;
  } 
  else {
    output.textContent = "";
  }

  readAsText(chosenEntry, function(result) {
    textarea.value = result;
  });
  // Update display.
  saveFileButton.disabled = false;
  displayEntryData(chosenEntry);
});
*/
