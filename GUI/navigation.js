function handleNavClick(thisItem,thisControl)
{
    if($(thisControl).css("display")=='none')
    {	
        $(thisControl).css("display","block");
        $(thisItem).css("backgroundColor","#fbac3a");
        $(thisItem).css("color","#000");
    }
    else
    {
        $(thisControl).css("display","none");
        $(thisItem).css("backgroundColor","#555");
        $(thisItem).css("color","#FFF");
    }
}

function getNavElement(ButtonId) // Links buttons to divs, probably should be converted to an array lookup
{
	var ReturnValue = "";
	if(ButtonId == "Console")
		ReturnValue = "#serialComs";
	else if(ButtonId =="Counter")
		ReturnValue = "#jPractice";
	else if(ButtonId =="CubeB")
		ReturnValue = "#FullCube";
	else if(ButtonId =="MotorB")
		ReturnValue = "#Motor";
	else if(ButtonId =="IMUB")
		ReturnValue = "#IMU_Nav";
	else if(ButtonId =="JoysticksB")
		ReturnValue = "#Joysticks";
	else if(ButtonId =="MetaDataB")
		ReturnValue = "#MetaData";
	else if(ButtonId =="AccCubeB") 
		ReturnValue = "#AccCube";
	else if(ButtonId =="AccPlotB")
		ReturnValue = "#AccPlot";
	else if(ButtonId =="GyroCubeB")
		ReturnValue = "#GyroCube";
	else if(ButtonId =="GyroPlotB")
		ReturnValue = "#GyroPlot";
	else if(ButtonId =="MagCubeB")
		ReturnValue = "#MagCube";
	else if(ButtonId =="MagPlotB")
		ReturnValue = "#MagPlot";
	else if(ButtonId =="KCubeB")
		ReturnValue = "#KCube";	
	else if(ButtonId =="KPlotB")
		ReturnValue = "#KPlot";		
	
	return ReturnValue;
}

$('.NavButton').click(function() {
	var myStrings = getNavElement(this.id);
	handleNavClick(this,myStrings);
})

handleNavClick('#AccCubeB',"#AccCube");
handleNavClick('#AccPlotB',"#AccPlot");handleNavClick('#AccPlotB',"#AccPlot");
handleNavClick('#GyroCubeB',"#GyroCube");
handleNavClick('#GyroPlotB',"#GyroPlot");handleNavClick('#GyroPlotB',"#GyroPlot");
handleNavClick('#MagCubeB',"#MagCube");
handleNavClick('#MagPlotB',"#MagPlot");handleNavClick('#MagPlotB',"#MagPlot");
handleNavClick('#KCubeB',"#KCube");
handleNavClick('#KPlotB',"#KPlot");handleNavClick('#KPlotB',"#KPlot");
handleNavClick('#MotorB',"#Motor");handleNavClick('#MotorB',"#Motor");
handleNavClick('#JoysticksB',"#Joysticks");handleNavClick('#JoysticksB',"#Joysticks");
handleNavClick('#MetaDataB',"#MetaData");handleNavClick('#MetaDataB',"#MetaData");