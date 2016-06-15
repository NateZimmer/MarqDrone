function getData(recievedInfo)
{
	//console.log(recievedInfo);
	var inputString="";
	inputString = ab2str(recievedInfo.data); 
	lines+=inputString;
	handleLogging(inputString);
	while((index =lines.indexOf('\n'))>0)
	{
		var line = lines.substr(0,index+1);
		lines=lines.substr(index+1);
		parseLines(line);
	}
}

function parseLines(inputStrings)
{
	//console.log("Recieved Line: "+inputStrings);
	var index;
	if(inputStrings.indexOf("ACC,")>=0)
	{
		handleAcc(inputStrings);
	}
	if(inputStrings.indexOf("GYRO,")>=0)
	{
		handleGyro(inputStrings);
	}
	if(inputStrings.indexOf("MAG,")>=0)
	{
		handleMag(inputStrings);
	}
	if(inputStrings.indexOf("Y_P_R,")>=0)
	{
		handleFusion(inputStrings);
	}
	if(inputStrings.indexOf("Remote,")>=0)
	{
		handleRemote(inputStrings);
	}
	if(inputStrings.indexOf("PR,")>=0)
	{
		handlePR(inputStrings);
	}
	if(inputStrings.indexOf("RSTATE,")>=0)
	{
		handleRemoteState(inputStrings);
	}
	if(inputStrings.indexOf("DSTATE,")>=0)
	{
		handleDroneState(inputStrings);
	}
	if(inputStrings.indexOf("CPU,")>=0)
	{
		handleCPU(inputStrings);
	}
	if(inputStrings.indexOf("PID,")>=0)
	{
		handlePID(inputStrings);
	}
	if(inputStrings.indexOf("MTR,")>=0)
	{
		handleMotorSpeeds(inputStrings);
	}

	
	
	handleDevices(inputStrings);
	handleDebugMessages(inputStrings);

}

var ax,ay,az;

var f_yaw = 0.0;
var f_roll = 0.0;
var f_pitch = 0.0;

var BigString = [];
var WriteSample = 0;


//var Remote_Throttle_Value = 0;
//var Remote_Yaw_Value=0;
//var Remote_Pitch_Value =0;
//var Remote_Roll_Value = 0;

var writeStarted = false;
var FileCreated = false;

function handleFusion(inputStrings)
{
	newArray=inputStrings.split(',');
	f_yaw=parseFloat(newArray[1]);
	f_pitch=parseFloat(newArray[2]);
	f_roll=parseFloat(newArray[3]);
	
	
	document.getElementById("KV").style.transform = myTranslate+"rotateY("+f_yaw+"deg) rotateX("+f_pitch+"deg) rotateZ("+f_roll+"deg)";
	updatePlot(kP,kArray,f_yaw,f_pitch,f_roll,k_options,ksamples,fusionLegend);

	
	if(Remote_Connected)
	{
		var compareString =document.getElementById("R_State_Text").innerHTML;
		if(compareString == "Drone is ARMED!" )
		{
				BigString[WriteSample]=f_pitch.toString()+','+f_roll.toString()+','+f_yaw.toString()+','+parseInt(Remote_Pitch_Value).toString()+','+parseInt(Remote_Roll_Value).toString()+','+parseInt(Remote_Yaw_Value).toString()+','+parseInt(Remote_Throttle_Value).toString() +',end\n';
				WriteSample++;
				writeStarted = true; 
				console.log("prepping log string "+WriteSample);
				if(FileCreated==false)
				{
					createFile();
					FileCreated=true;
					BigString[0] = 'Pitch,Roll,Yaw,rPitch,rRoll,rYaw,rThrottle,end\n';
				}
		}
		else
		{
			if(writeStarted)
			{
				writeStarted = false;
				FileCreated = false;
				console.log('Attempt Writing to log file');
				writeToLogFile(BigString);
				BigString = [];
				WriteSample = 0;
			}
		}	
	}
	
}

function handleAcc(inputStrings)
{
	newArray=inputStrings.split(',');
	ax=parseFloat(newArray[1]);
	ay=parseFloat(newArray[2]);
	az=parseFloat(newArray[3]);
	
	//writeToLogFile("Accel, "+ax.toString()+","+ay.toString()+","+az.toString()+"\r\n");
	
	pitch = getPitch(ax,ay,az);
	roll = getRoll(ax,ay,az);
	//console.log("Pitch: "+ pitch);
	//console.log("Roll: "+ roll);
	document.getElementById("AccV").style.transform = myTranslate+"rotateY("+0+"deg) rotateX("+roll+"deg) rotateZ("+pitch+"deg)";
	updatePlot(myPlot,myArray,ax,ay,az,acc_options,samples,accLegend);
	//Normal notation Z(up), X(in/out of page), Y (left right)
	//CSS: Y (UP), Z(at you), X(left,right)
}

var gx,gy,gz;
var gxp=0.01;
var gyp=0.01;
var gzp=0.01;

var ggain = 1;

function handleGyro(inputStrings)
{
	gyroRaw=inputStrings.split(',');
	gx=parseFloat(gyroRaw[1]);
	gy=parseFloat(gyroRaw[2]);
	gz=parseFloat(gyroRaw[3]);
	
	gxp=gxp*0.999+0.05*gx; // Integrations of values 
	gyp=gyp*0.999+0.05*gy;
	gzp=gzp*0.999+0.05*gz;
	
	
	gxn = -1*gxp; // Sign reversals, // Note css X is Z 
	gyn = -1*gyp; // Note css y is X 
	gzn = -1*gzp; // Note css Y is gyro Z aka yaw. 
	
	document.getElementById("GyroV").style.transform = myTranslate+"rotateY("+gzn+"deg) rotateX("+gyn+"deg) rotateZ("+gxn+"deg)";
	updatePlot(gyroP,gyroArray,gx,gy,gz,gyro_options,gsamples,accLegend);
}

function handleMotorSpeeds(inputStrings)
{
	motorSpeeds=inputStrings.split(',');
	var m0 = parseInt(motorSpeeds[1])/10;
	var m1 = parseInt(motorSpeeds[2])/10;
	var m2 = parseInt(motorSpeeds[3])/10;
	var m3 = parseInt(motorSpeeds[4])/10;
	
	updateSpeed(m0,m1+1,m2+2,m3+3,speedSamples);
}



$('#GyroV').click(function(){
	gxp = 0.01;
	gyp = 0.01;
	gzp = 0.01;
});

var magScale=500;

var mx,my,mz;
var mxx=0,myy=0,mzz=0;
var mmaxx=-500,mmaxy=-500,mmaxz=-500,mminx=500,mminy=500,mminz=500;
var magCalibrate = 0;

function removeOffset(kx,kx_max,kx_min) // Removes DC offset and scales signal 
{
	//mag = (Math.abs(kx_max)+Math.abs(kx_min)) / 2.0;
	//kxx = magScale / (mag) * ( kx - (kx_max - mag));
	kxx = (kx - kx_min)/(kx_max - kx_min)*500 - 250;
	return kxx; 
}

$('#MagPlot').click(function(){ // Handle state machine for calibration of magnetometer 
	magCalibrate++;
	magCalibrate=magCalibrate%3;
	if(magCalibrate==0)
	{
		document.getElementById("magTitle").innerHTML="Magnetometer Plot:(Raw)";
	}
	else if(magCalibrate==1)
	{
		mmaxx=-500; mmaxy = -500; mmaxz = -500; mminx = 500; mminy = 500; mminz = 500;
		document.getElementById("magTitle").innerHTML="Magnetometer Plot:(Calibrating)";
	}
	else
	{
		console.log('Writing calibration mag data to local storage');
		
		chrome.storage.local.set({'Mx_Max':mmaxx.toString()});
		chrome.storage.local.set({'My_Max':mmaxy.toString()});
		chrome.storage.local.set({'Mz_Max':mmaxz.toString()});
		chrome.storage.local.set({'Mx_Min':mminx.toString()});
		chrome.storage.local.set({'My_Min':mminy.toString()});
		chrome.storage.local.set({'Mz_Min':mminz.toString()});
		
		document.getElementById("magTitle").innerHTML="Magnetometer Plot:(Compensated)";
	}
});


function SetMagFromSavedData()
{

	console.log('Restoring Mag cal data to local variables');
	magCalibrate=1;
	mmaxx = parseFloat(Mx_Max);
	mmaxy = parseFloat(My_Max);
	mmaxz = parseFloat(Mz_Max);
	
	mminx = parseFloat(Mx_Min);
	mminy = parseFloat(My_Min);
	mminz = parseFloat(Mz_Min);
	
	$('#MagPlot').click();
	
}


function handleDebugMessages(inputStrings)
{
	var myString ="";
	if(inputStrings.indexOf("MSG,")>=0)
	{
		var strings = inputStrings.split(',');
		myString = document.getElementById("textBox").innerHTML;
		myString=strings[1]+myString+"\r\n";
		while(myString.length>500)
		{
			myString = myString.substr(10);
		}
		document.getElementById("textBox").innerHTML = myString; 
		
	}
}



function handleMagCalibration()
{
	if(magCalibrate==1)
	{
		if(mmaxx<mx)
		{mmaxx = mx;} 
		if(mmaxy<my)
		{mmaxy = my;}
		if(mmaxz<mz)
		{mmaxz = mz;}
	
		if(mminx>mx)
		{mminx = mx;}
		if(mminy>my)
		{mminy = my;}		
		if(mminz>mz)
		{mminz = mz;}	
	}
	if((magCalibrate ==1)||(magCalibrate==2)) // Calibrate
	{
		mxx = removeOffset(mx,mmaxx,mminx).toFixed(2);
		myy = removeOffset(my,mmaxy,mminy).toFixed(2);
		mzz = removeOffset(mz,mmaxz,mminz).toFixed(2);
	}
	else //Display raw values 
	{
		mxx =mx;
		myy =my;
		mzz =mz;
	}

}

	
var yaw_mag = 0.0;

function handleMag(inputStrings)
{

	var psi_num = 0.0;
	var psi_den = 0.0
	
	magRaw=inputStrings.split(',');
	mx=parseFloat(magRaw[1]);
	my=parseFloat(magRaw[2]);
	mz=parseFloat(magRaw[3]);
	
	
	handleMagCalibration();
	bz = mzz;
	bx = -mxx;
	by = -myy;
	
	psi_num = (bz)*Math.sin(f_roll*Math.PI/180) - (by)*Math.cos(f_roll*Math.PI/180);
	psi_den = (bx)*Math.cos(f_pitch*Math.PI/180) + (by)*Math.sin(f_pitch*Math.PI/180)*Math.sin(f_roll*Math.PI/180)+(bz)*Math.sin(f_pitch*Math.PI/180)*Math.cos(f_roll*Math.PI/180);
	
	
	mmag = Math.sqrt(myy*myy + mxx*mxx);
	myyy = myy/mmag;
	mxxx = mxx/mmag;
	
	yaw_mag = Math.atan2(psi_num,psi_den)*180/Math.PI;;
	
	//yaw = Math.atan2(myyy,mxxx)*180/Math.PI;
	//pitch = Math.atan2(mzz,mmag)*180/Math.PI-70;
	pitch = 0;
	document.getElementById("MagV").style.transform = myTranslate+" rotateY("+yaw_mag+"deg) rotateX("+f_pitch+"deg) rotateZ("+f_roll+"deg)";
	updatePlot(magP,magArray,bx,by,bz,mag_options,msamples,accLegend);
}

function getPitch(kx,ky,kz)
{
	return 180*Math.atan2(kx,Math.sqrt(Math.pow(ky,2)+Math.pow(kz,2)))/Math.PI;
	//return 180*Math.atan2(ax,Math.sqrt(Math.pow(ay,2)+Math.pow(az,2)))/Math.PI;
} 

function getRoll(kx,ky,kz)
{
	return 180*Math.atan2(-ky,kz)/Math.PI;
	//return 180*Math.atan2(ay,Math.sqrt(Math.pow(ax,2)+Math.pow(az,2)))/Math.PI;
}

function handlePR(inputStrings)
{
	var InputData = inputStrings.split(',');
	InputData = parseInt(InputData[1]);
	document.getElementById("Packet_Rate_Text").innerHTML = InputData.toString();
}

function handlePID(inputStrings)
{
	var InputData = inputStrings.split(',');
	var Command_Value = InputData[1].toString();
	var Data_Value = InputData[2];
	if(Command_Value==1)
		document.getElementById("PITCH_P").innerHTML = Data_Value;
	else if(Command_Value==2)
		document.getElementById("PITCH_I").innerHTML = Data_Value;
	else if(Command_Value==3)
		document.getElementById("PITCH_D").innerHTML = Data_Value;
	else if(Command_Value==4)
		document.getElementById("ROLL_P").innerHTML = Data_Value;
	else if(Command_Value==5)
		document.getElementById("ROLL_I").innerHTML = Data_Value;
	else if(Command_Value==6)
		document.getElementById("ROLL_D").innerHTML = Data_Value;
	else if(Command_Value==7)
		document.getElementById("YAW_P").innerHTML = Data_Value;
	else if(Command_Value==8)
		document.getElementById("YAW_I").innerHTML = Data_Value;
	else if(Command_Value==9)
		document.getElementById("YAW_D").innerHTML = Data_Value;

}

function handleDevices(inputStrings)
{
	if(inputStrings.indexOf("MarqRemote")>=0)
	{
		document.getElementById("Device_Text").innerHTML = "Marq Remote";
		Remote_Connected = true;
	}
	else if(inputStrings.indexOf("MarqDrone")>=0)
	{
		document.getElementById("Device_Text").innerHTML = "Marq Drone";
		Remote_Connected = false;
	}

}

var PID_Gain_Counter = 1;
function handle_PID_Gain()
{
	var PID_Value = 1;
	var TempIndex = PID_Gain_Counter - 1;
	PID_Value = 10*parseInt(PID_Slider_Array[TempIndex].value);
	
	if(Remote_Connected)
	{
		chrome.serial.send(ConnectionData.connectionId,str2ab("SET_PID_GAIN,"+PID_Gain_Counter.toString()+","+PID_Value.toString(16)+"\r"),onSend);
	}
	PID_Gain_Counter++;
	if(PID_Gain_Counter>9)
	{
		PID_Gain_Counter = 1;
	}
}

var MDC = 0; // Meta Data Counter 
function handleMetaDataCollection()
{

	if(MDC==0)
	{
		chrome.serial.send(ConnectionData.connectionId,str2ab("WHO_AM_I\r"),onSend);
	}
	else if(MDC==1)
	{
		if(Remote_Connected)
		{
			chrome.serial.send(ConnectionData.connectionId,str2ab("PACKET_RATE\r"),onSend);
		}

	}
	else if(MDC==2)
	{
		if(Remote_Connected)
		{
			chrome.serial.send(ConnectionData.connectionId,str2ab("GET_R_MODE\r"),onSend);
		}
		
	}
	else if(MDC==3)
	{
		if(Remote_Connected)
		{
			chrome.serial.send(ConnectionData.connectionId,str2ab("GET_CPU\r"),onSend);
		}

	}
	else if (MDC>3 && MDC<13)
	{
		if(Remote_Connected)
		{
			chrome.serial.send(ConnectionData.connectionId,str2ab("GET_PID_GAIN,"+(MDC-3).toString()+"\r"),onSend);
		}
	}
	else
	{
		handle_PID_Gain();
	}
	MDC = (MDC+1)%20;
}

function handleRemoteState(inputStrings)
{
	var InputData = inputStrings.split(',');
	var OutputString = "";
	InputData = parseInt(InputData[1]);
	
	if(InputData==0)
		OutputString = "No RF Connection";
	if (InputData==1)
		OutputString = "Manual Motor Mode";
	if (InputData==2)
		OutputString = "Drone in arming process";
	if (InputData==3)
		OutputString = "Drone is ARMED!";
	if (InputData==4)
		OutputString = "RF Link Connected";
	
	document.getElementById("R_State_Text").innerHTML =OutputString;
}

function handleDroneState(inputStrings)
{
	var InputData = inputStrings.split(',');
	InputData = parseInt(InputData[1]);
}

function handleCPU(inputStrings)
{
	var InputData = inputStrings.split(',');
	var CPU_Usage = 0;
	CPU_Usage = parseInt(InputData[1]);
	document.getElementById("CPU_Text").innerHTML =CPU_Usage.toString();
}

















