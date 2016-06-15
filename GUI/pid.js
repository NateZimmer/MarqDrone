var PID_Value_Array = [];
var PID_Text_Array = [PID_PP_T,PID_PI_T,PID_PD_T,PID_RP_T,PID_RI_T,PID_RD_T,PID_YP_T,PID_YI_T,PID_YD_T];
var PID_Slider_Array = [PID_PP_S,PID_PI_S,PID_PD_S,PID_RP_S,PID_RI_S,PID_RD_S,PID_YP_S,PID_YI_S,PID_YD_S];

// Updates motor text values, pass in numerical id of motor.
function Update_PID_Text(index_number){ 
	PID_Value_Array[index_number] = PID_Slider_Array[index_number].value;
	document.getElementById(PID_Text_Array[index_number].getAttribute('id')).innerHTML= PID_Value_Array[index_number]/10;
}

$('.PID_Slider').on('input', function(){
	$('.PID_Slider').each(function(i,obj){Update_PID_Text(i);}); // Enumerates through the classes and updates values
	
	var PID_Format_String='';
	for(i = 0; i<PID_Text_Array.length-1;i++)
	{
		PID_Format_String =PID_Format_String+PID_Value_Array[i].toString()+',';	
	}
	PID_Format_String= PID_Format_String + PID_Value_Array[PID_Text_Array.length-1].toString();
	chrome.storage.local.set({'PID_String':PID_Format_String});
	console.log('Saving PID String: '+PID_Format_String);
	
	//var myString = "MOTOR_SPEED,"+parseInt(PID_Value_Array[0]).toString(16)+","+parseInt(PID_Value_Array[1]).toString(16)+","+parseInt(Motor_Value_Array[2]).toString(16)+","+parseInt(Motor_Value_Array[3]).toString(16)+"\r";
	
	//if(Remote_Connected)
	//{
	//	if(Ok_To_Update_Motor) // Limits the speed at which we update the controller for sanity sake. 
	//	{
	//		Ok_To_Update_Motor = false;
	//		chrome.serial.send(ConnectionData.connectionId,str2ab(myString),onSend);
	//	}
	//}

	
});

$('#transferPID').on('change', function(){
	if(Remote_Connected)
	{
		if(transferPID.checked)
		{
			chrome.serial.send(ConnectionData.connectionId,str2ab("EN_PID_GAIN,1\r"),onSend);
		}
		else
		{
			chrome.serial.send(ConnectionData.connectionId,str2ab("EN_PID,GAIN,0\r"),onSend);
		}
	}
});


// Restore saved values of PID array
function Init_Slider(SliderValues)
{
	for(i =0; i <SliderValues.length;i++)
	{
		PID_Slider_Array[i].value = parseInt(SliderValues[i]);
		Update_PID_Text(i)
		
	}
	console.log("Updated PID Values");
	
}