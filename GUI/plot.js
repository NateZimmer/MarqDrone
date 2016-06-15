var myArray = [];
var gyroArray = [];
var magArray = [];
var kArray = [];
var speedArray=[];

var plotLength = 500;
var acc_options;
var samples=100;
var gsamples=100;
var msamples=100;
var ksamples=100;
var speedSamples=100;

var accLegend = ["X ", "Y ", "Z "];
var fusionLegend = ["Yaw ","Pitch ","Roll "];

acc_options = {
	title: "Acc (G/s)",
	shadowSize: 0,
	yaxis: {
		max: 1.2,
		min: -1.2
	},
	xaxis: {
		//noTicks = 0
	},
	grid: {
		backgroundColor: "#FFFFFF"
	},
	legend: {
		position: "wn",
		backgroundOpacity: 0
	}
}

gyro_options = {
	title: "Gyro (G/s)",
	shadowSize: 0,
	yaxis: {
		max: 260,
		min: -260
	},
	xaxis: {
		//noTicks = 0
	},
	grid: {
		backgroundColor: "#FFFFFF"
	},
	legend: {
		position: "wn",
		backgroundOpacity: 0
	}
}

mag_options = {
	title: "Mag (G/s)",
	shadowSize: 0,
	yaxis: {
		max: 700,
		min: -700
	},
	xaxis: {
		//noTicks = 0
	},
	grid: {
		backgroundColor: "#FFFFFF"
	},
	legend: {
		position: "wn",
		backgroundOpacity: 0
	}
}

k_options = {
	title: "Fusion (degrees)",
	shadowSize: 0,
	yaxis: {
		max: 120,
		min: -120
	},
	xaxis: {
		//noTicks = 0
	},
	grid: {
		backgroundColor: "#FFFFFF"
	},
	legend: {
		position: "wn",
		backgroundOpacity: 0
	}
}

all_options = {
	title: "All",
	shadowSize: 0,
	yaxis: {
		max: 120,
		min: -120
	},
	xaxis: {
		//noTicks = 0
	},
	grid: {
		backgroundColor: "#FFFFFF"
	},
	legend: {
		position: "wn",
		backgroundOpacity: 0
	}
}

function updatePlot(ID,myArrays,kx,ky,kz,options,sample,plotLegends)
{
	myArrays[0].push([sample,kx]);
	myArrays[1].push([sample,ky]);
	myArrays[2].push([sample,kz]);
	
	while (myArrays[0].length > plotLength) {            
		myArrays[0].shift();
		myArrays[1].shift();
		myArrays[2].shift();
	}
	
	Flotr.draw(ID, [ 
	{data: myArrays[0], label:plotLegends[0]+kx}, 
	{data: myArrays[1], label:plotLegends[1]+ky}, 
	{data: myArrays[2], label:plotLegends[2]+kz} ], options);  
}


function updateSpeed(m0,m1,m2,m3,sample)
{
	speedArray[0].push([sample,m0]);
	speedArray[1].push([sample,m1]);
	speedArray[2].push([sample,m2]);
	speedArray[3].push([sample,m3]);
	
	while (speedArray[0].length > plotLength) {            
		speedArray[0].shift();
		speedArray[1].shift();
		speedArray[2].shift();
		speedArray[3].shift();
	}
	
	Flotr.draw(motorP,[ 
	{data: speedArray[0], label: "M0"}, 
	{data: speedArray[1], label: "M1"}, 
	{data: speedArray[2], label: "M2"},
	{data: speedArray[3], label: "M3"}], all_options);  
}

function generatePlot(myArrays,ID,options, length) {

        var
          start = (new Date).getTime(),
          data, graph, offset, i;
	
	for(var i = 0; i < length ; i++)
	{
		myArrays[i]=[];
	}

	for (var i = 0; i <= plotLength; i++) { 
		
		for(var j = 0; j < length;j++)
		{
			myArrays[j].push([i,0]);
		}
    }
	
	Flotr.draw(ID, [ 
	{data: myArrays[0], label: "X"}, 
	{data: myArrays[1], label: "Y"}, 
	{data: myArrays[2], label: "Z"} ], options);  	
        	
}



generatePlot(myArray,myPlot,acc_options,3);
generatePlot(gyroArray,gyroP,gyro_options,3);
generatePlot(magArray,magP,mag_options,3);
generatePlot(kArray,kP,k_options,3);
generatePlot(speedArray,motorP,all_options,4);

//generatePlot(speedArray,motorP,all_options);


