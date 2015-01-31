<?php

include_once "header.php";

echo "<h1>Contest</h1>";

date_default_timezone_set("America/Boise");
$formatdate=date('Y-m-d');
$dayquerry="select dayname('".$formatdate."')";
$dayresults=queryfunction($dayquerry);
$dayarray=array();
while($row=mysqli_fetch_array($dayresults))
{
	$dayarray[]=$row[0];
}
$dayname=$dayarray[0];
$formattime=date('Y-m-d H:i:s');
$timequerry="select hour('".$formattime."')";
$timeresults=queryfunction($timequerry);
$timearray=array();
while($row=mysqli_fetch_array($timeresults))
{
	$timearray[]=$row[0];
}
$hour=$timearray[0];
if($dayname=="Tuesday" && $hour==20)
{
	$clearquerry="update oipmembers set lastcap='NULL'";
	queryfunction($clearquerry);
}
if(isset($_POST['updatecapped']))
{
	$member=$_POST['updatecapped'];
	$formatdate=date('Y-m-d H:i:s');
	$qcapquery="select username,lastcap from oipmembers where username='".$member."'";
	$qcapresults=queryfunction($qcapquery);
	$qcaparray=array();
	while($qcaprow=mysqli_fetch_array($qcapresults))
	{
		$qcaparray[]=$qcaprow[0];
		$qcaparray[]=$qcaprow[1];
	}
	if($qcaparray[1]==NULL)
	{
		$capupdatequery="update oipmembers set lastcap='".$formatdate."' where username='".$member."'";
		queryfunction($capupdatequery);
	}
	else if($qcaparray[1]!=NULL)
	{
		echo "<div id='caperror'>";
		echo "You Have Already Capped";
		echo "</div>";
	}
}
if(isset($_POST['startcomp']))
{
	$skill=$_POST['selectcompskill'];
	$formatdate=date('MY');
	$filenamecap=$formatdate.$skill;
	$filename=strtolower($filenamecap);
	
	$skillnamequery="select skillnum from runeskills where skill='".$skill."'";
	$skillnameresults=queryfunction($skillnamequery);
	$skillnamearray=mysqli_fetch_array($skillnameresults);
	$skillnumber=$skillnamearray[0];
	$rankloc=$skillnumber*3-3;
	$levelloc=$skillnumber*3+1-3;
	$xploc=$skillnumber*3+2-3;
	
	$dropquery="drop table if exists ".$filename;
	queryfunction($dropquery);
	
	$createtablequery="create table ".$filename."(username varchar(20) not null, skill varchar(20) not null, initlevel  int not null, initxp int not null, finlevel  int not null, finxp int not null, diflevel  int not null, difxp int not null)";
	queryfunction($createtablequery);
	
	$competequery="select username from oipmembers where competing=1";
	$competeresults=queryfunction($competequery);
	while ($row=mysqli_fetch_array($competeresults))
	{
		$username=$row[0];
		
		$link = 'http://hiscore.runescape.com/index_lite.ws?player='.$username;
		$file=file_get_contents($link);
		$str = preg_replace(array('/[^\d,]/','/(?<=,),+/','/^,+/','/,+$/'),',',$file);
		$statlist=explode(',',$str);
		
		$initxp=$statlist[$xploc];
		$initlevel=$statlist[$levelloc];
		
		$finlevel=$initlevel;
		$finxp=$initxp;
		$diflevel=0;
		$difxp=0;
		if($initxp>0)
		{
			$query="insert into ".$filename." values('".$username."','".$skill."','".$initlevel."','".$initxp."','".$finlevel."','".$finxp."','".$diflevel."','".$difxp."')";
			$results=queryfunction($query);
		}
	}
}
if(isset($_POST['updatestats']) && isset($_POST['radioskill']))
{
	$skill=$_POST['radioskill'];
	if($skill=='None')
	{
		echo "<div id='skillerror'>";
		echo "That is Not A Skill";
		echo "</div>";
	}
	$formatdate=date('MY');
	$filenamecap=$formatdate.$skill;
	$filename=strtolower($filenamecap);

	$skillquery="select skill from ".$filename;
	$skillresults=queryfunction($skillquery);
	$skillname=mysqli_fetch_array($skillresults);
	$skill=$skillname[0];
	
	$skillnamequery="select skillnum from runeskills where skill='".$skill."'";
	$skillnameresults=queryfunction($skillnamequery);
	$skillnamearray=mysqli_fetch_array($skillnameresults);
	$skillnumber=$skillnamearray[0];
	$rankloc=$skillnumber*3-3;
	$levelloc=$skillnumber*3+1-3;
	$xploc=$skillnumber*3+2-3;
	
	$playerquery="select * from ".$filename;
	$playerresults=queryfunction($playerquery);

	while ($row=mysqli_fetch_array($playerresults))
	{
		$username=$row[0];
		$skill=$row[1];
		$initlevel=$row[2];
		$initxp=$row[3];
	
		$link = 'http://hiscore.runescape.com/index_lite.ws?player='.$username;
		$file=file_get_contents($link);
		$str = preg_replace(array('/[^\d,]/','/(?<=,),+/','/^,+/','/,+$/'),',',$file);
		$statlist=explode(',',$str);
		
		$finlevel=$statlist[$levelloc];
		$finxp=$statlist[$xploc];
	
		$diflevel=$finlevel-$initlevel;
		$difxp=$finxp-$initxp;
		
		$updatequery="update ".$filename." set finlevel='".$finlevel."', finxp='".$finxp."', diflevel='".$diflevel."', difxp='".$difxp."' where username='".$username."'";
		$updateresults=queryfunction($updatequery);
	}
}
$formatdate=date('MY');
$filenamecap=$formatdate;
$filenamedate=strtolower($filenamecap);
$radioquery="select table_name from INFORMATION_SCHEMA.TABLES WHERE table_schema = 'ebeilmann' and table_name like'".$filenamedate."%'";
$radioresults=queryfunction($radioquery);
$radiovars = array();
while ($radiorow=mysqli_fetch_array($radioresults))
{
	$radiovars[]=$radiorow[0];
}
$skill1=substr($radiovars[0],7);
$skill2=substr($radiovars[1],7);
if($skill1=="")
{
	$skill1="None";
}
if($skill2=="")
{
	$skill2="None";
}	
echo "<form method='post'>";
if(isset($_SESSION['username']) && isset($_SESSION['admin']))
{
	$query="select skill from runeskills";
	$results=queryfunction($query);
	echo "<div id='logedskillcontest'>";
	echo "<h4>Skill Contest</h4>";
	echo "<select name='selectcompskill' style='position:relative;left:10px;width:126px;'>";
	while ($row=mysqli_fetch_array($results))
	{
		echo "<option>".$row[0]."</option>";
	}
	echo "</select>";
	echo "<input type='submit' name='startcomp' value='Start Competition'/>";
	echo "</form>";
	echo "<br>";

	echo "<input type='radio' name='radioskill' value='".$skill1."' style='position:relative;left:5px;'>";
	echo "<label for='radioskill' style='position:relative;left:-10px;'>".$skill1." </label>";

	echo "<input type='radio' name='radioskill' value='".$skill2."' style='position:relative;left:117px;'>";
	echo "<label for='radioskill' style='position:relative;left:85px;'>".$skill2." </label>";
	echo "<br>";

	echo "<input type='submit' name='updatestats' value='Update Stats'/>";
	echo "<input type='submit' name='showstats' value='Show Stats'/>";
	echo "</div>";
	echo "<br>";
}
if(!isset($_SESSION['username']) && !isset($_SESSION['admin']))
{
	echo "<div id='skillcontest'>";
	echo "<h4>Skill Contest</h4>";
	echo "<input type='radio' name='radioskill' value='".$skill1."' style='position:relative;left:5px;'>";
	echo "<label for='radioskill' style='position:relative;left:-10px;'>".$skill1." </label>";

	echo "<input type='radio' name='radioskill' value='".$skill2."' style='position:relative;left:117px;'>";
	echo "<label for='radioskill' style='position:relative;left:85px;'>".$skill2." </label>";
	echo "<br>";

	echo "<input type='submit' name='updatestats' value='Update Stats'/>";
	echo "<input type='submit' name='showstats' value='Show Stats'/>";
	echo "</div>";
	echo "<br>";
}
echo "</form>";
$setcapquery="select username from oipmembers";
$setcapresults=queryfunction($setcapquery);
echo "<div id='capcontest'>";
echo "<h4>Capped</h4>";
echo "<form method='post'>";
echo "<select name='updatecapped' style='position:relative;left:10px;'>";
while ($setcaprow=mysqli_fetch_array($setcapresults))
{
	echo "<option>".$setcaprow[0]."</option>";
}
echo "</select>";
echo "<input type='submit' name='cap' value='Update' />";
echo "</form>";
echo "<form method='post'>";
echo "<input type='submit' name='showcaplist' value='Show Cappped' style='position:relative;left:80px;'/>";
echo "</form>";
echo "<form method='post'>";
if(isset($_SESSION['username']) && isset($_SESSION['admin']))
{
	echo "<input type='submit' name='capwin' value='Set Winners' style='position:relative;left:80px;'/>";	
}
echo "</form>";
echo "</div>";
echo "<br>";
//capwin is new
if(isset($_POST['capwin']))
{
	$clearwinnersquery="update oipmembers set capwin=NULL";
	queryfunction($clearwinnersquery);
	$capwincount=0;
	$capwinquerry="select username from oipmembers where lastcap!='NULL' order by lastcap";
	$capwinresults=queryfunction($capwinquerry);
	$capwinarray=array();
	while ($capwinrow=mysqli_fetch_array($capwinresults))
	{
		$capwincount++;
		$capwinarray[]=$capwinrow[0];
	}
	$winone=rand(1,$capwincount);
	$wintwo=rand(1,$capwincount);
	$winthree=rand(1,$capwincount);
	while($winone==$wintwo)
	{
		$wintwo=rand(1,$capwincount);
	}
	while($winthree==$winone || $winthree==$wintwo)
	{
		$winthree=rand(1,$capwincount);
	}
	$one=$capwinarray[$winone-1];
	$two=$capwinarray[$wintwo-1];
	$three=$capwinarray[$winthree-1];
	$winonequerry="update oipmembers set capwin='first' where username='".$one."'";
	$wintwoquerry="update oipmembers set capwin='second' where username='".$two."'";
	$winthreequerry="update oipmembers set capwin='third' where username='".$three."'";
	queryfunction($winonequerry);
	queryfunction($wintwoquerry);
	queryfunction($winthreequerry);
}
if(isset($_POST['showcaplist']))
{
	$getcapquerry="select username,capwin from oipmembers where lastcap!='NULL' order by lastcap";
	$getcapresults=queryfunction($getcapquerry);
	$getcapcount=0;
	echo "<div id='captable'>";
	echo "<table>";
	echo "<td height='50px' width='100px'><h4>Order</h4></td><td width='500px'><h4>Name</h4></td><td width='100px'><h4>Winners</h4></td>";
	while ($getcaprow=mysqli_fetch_array($getcapresults))
	{
		$getcapcount++;
		echo "<tr>";
		echo "<td>".$getcapcount."</td><td>".$getcaprow[0]."</td><td>".$getcaprow[1]."</td>";
		echo "</tr>";
	}
	echo "</table>";
	echo "</div>";
	echo "<br>";
}
if(isset($_POST['showstats']) && !isset($_POST['radioskill']))
{
	echo "<div id='skillerror'>";
	echo "No Skill Was Selected";
	echo "</div>";
}
if(isset($_POST['updatestats']) && !isset($_POST['radioskill']))
{
	echo "<div id='skillerror'>";
	echo "No Skill Was Selected";
	echo "</div>";
}
if(isset($_POST['showstats']) && isset($_POST['radioskill']))
{
	$skill=$_POST['radioskill'];
	$formatdate=date('MY');
	$filenamecap=$formatdate.$skill;
	$filename=strtolower($filenamecap);
	
	$getstatsquery="select * from ".$filename." order by difxp desc, username";
	$getstatsresults=queryfunction($getstatsquery);
	
	if($skill=='None')
	{
		echo "<div id='skillerror'>";
		echo "That is Not A Skill";
		echo "</div>";
	}
	if($skill!='None')
	{
		echo "<div id='statstable'>";
		echo "<table>";
		echo "<td><h4>Name</h4></td><td><h4>Skill</h4></td><td><h4>initlevel</h4></td><td><h4>initxp</h4></td><td><h4>finlevel</h4></td><td><h4>finxp</h4></td><td><h4>diflevel</h4></td><td><h4>difxp</h4></td>";
	}
	
	while ($statsrow=mysqli_fetch_array($getstatsresults))
	{
		echo "<tr>";
		echo "<td>".$statsrow[0]."</td><td>".$statsrow[1]."</td><td>".$statsrow[2]."</td><td>".$statsrow[3]."</td><td>".$statsrow[4]."</td><td>".$statsrow[5]."</td><td>".$statsrow[6]."</td><td>".$statsrow[7]."</td>";
		echo "</tr>";
	}
	echo "</table>";
	echo "</div>";
	echo "<br>";
}

include_once "footer.php";
?>