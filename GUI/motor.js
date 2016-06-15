var Motor_Value_Array = [];
var Motor_Text_Array = [M0_T,M1_T,M2_T,M3_T,M_ALL_T];
var Motor_Slider_Array = [M0,M1,M2,M3,M_ALL];

// Updates motor text values, pass in numerical id of motor.
function Update_Motor_Text(Target_Motor){ 
	Motor_Value_Array[Target_Motor] = Motor_Slider_Array[Target_Motor].value;
	document.getElementById(Motor_Text_Array[Target_Motor].getAttribute('id')).innerHTML= Motor_Value_Array[Target_Motor];
}

$('.M_Slider').on('input', function(){
	
	
	$('.M_Slider').each(function(i,obj){Update_Motor_Text(i);}); // Enumerates through the classes and updates values
	//var myString = "MOTOR_SPEED,"+parseInt(Motor_Value_Array[0]).toString(16)+","+parseInt(Motor_Value_Array[1]).toString(16)+","+parseInt(Motor_Value_Array[2]).toString(16)+","+parseInt(Motor_Value_Array[3]).toString(16)+"\r";
	/*
	if(Remote_Connected)
	{
		if(Ok_To_Update_Motor) // Limits the speed at which we update the controller for sanity sake. 
		{
			Ok_To_Update_Motor = false;
			chrome.serial.send(ConnectionData.connectionId,str2ab(myString),onSend);
		}
	}
	*/

});


function Manual_Motor_Mode_Update_Speeds()
{
	var myString;

	if(parseInt(M_ALL.value)==0)
	{
		myString = "MOTOR_SPEED,"+parseInt(Motor_Value_Array[0]).toString(16)+","+parseInt(Motor_Value_Array[1]).toString(16)+","+parseInt(Motor_Value_Array[2]).toString(16)+","+parseInt(Motor_Value_Array[3]).toString(16)+"\r";	
	}
	else
	{
		myString = "MOTOR_SPEED,"+parseInt(M_ALL.value).toString(16)+","+parseInt(M_ALL.value).toString(16)+","+parseInt(M_ALL.value).toString(16)+","+parseInt(M_ALL.value).toString(16)+"\r";	
	}
	chrome.serial.send(ConnectionData.connectionId,str2ab(myString),onSend);
}

$('#manualMotorSpeed').on('change', function(){
	if(Remote_Connected)
	{
		if(manualMotorSpeed.checked)
		{
			chrome.serial.send(ConnectionData.connectionId,str2ab("MODE,1\r"),onSend);
		}
		else
		{
			chrome.serial.send(ConnectionData.connectionId,str2ab("MODE,0\r"),onSend);
		}
	}

});
