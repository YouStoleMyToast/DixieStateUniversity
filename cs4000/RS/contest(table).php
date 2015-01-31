<?php

include_once "header.php";



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



echo "<h1>Contest</h1>";

echo "<table>";
	echo "<tr>";
	echo "<th colspan='3'>Skill Contest</th>";
	echo "<th colspan='3'>Capped</th>";
	echo "</tr>";
	echo "<form method='post' action='http://www.ebeilmann.php.cs.dixie.edu/CS%204000/RS/contest.php'>";
if(isset($_SESSION['username']) && isset($_SESSION['admin']))
{
		echo "<tr>";
		echo "<td><label for='startcomp' style='padding-right:5px;'>Skill </label></td>";
		$query="select skill from runeskills";
		$results=queryfunction($query);
		echo "<td><select name='selectcompskill'>";
		while ($row=mysqli_fetch_array($results))
		{
			echo "<option>".$row[0]."</option>";
		}
		echo "</select></td>";
		echo "<td><input type='submit' name='startcomp' value='Start Competition'/></td>";
}			
		date_default_timezone_set("America/Boise");
		$formatdate=date('MY');
		$filenamecap=$formatdate;
		$filenamedate=strtolower($filenamecap);
		$radioquery="select table_name from INFORMATION_SCHEMA.TABLES WHERE table_schema = 'ebeilmann' and table_name like'".$filenamedate."%'";
		$radioresults=queryfunction($radioquery);
		$vars = array();
		while ($row=mysqli_fetch_array($radioresults))
		{
			$vars[]=$row[0];
		}
		$skill1=substr($vars[0],7);
		$skill2=substr($vars[1],7);

		if($skill1=="")
		{
			$skill1="None";
		}
		
		if($skill2=="")
		{
			$skill2="None";
		}	
		echo "<tr>";
		echo "<td><input type='radio' name='radioskill' value='".$skill1."'></td>";
		echo "<td><label for='radioskill'>".$skill1." </label></td>";
		echo "<td><input type='submit' name='updatestats' value='Update Stats' /></td>";
		
		
		echo "<td><label for='cap'>Name</label></td>";
		$query="select username from oipmembers";
		$results=queryfunction($query);
		echo "<td><select name='capped'>";
		while ($row=mysqli_fetch_array($results))
		{
			echo "<option>".$row[0]."</option>";
		}
		echo "</select></td>";
		echo "<td><input type='submit' name='cap' value='Capped' /></td>";
		echo "</tr>";
	
		echo "<tr>";
		echo "<td><input type='radio' name='radioskill' value='".$skill2."'></td>";
		echo "<td><label for='radioskill'>".$skill2." </label></td>";
		echo "<td><input type='submit' name='showstats' value='Show Stats' /></td>";
		
		
		echo "<td colspan='3'><input type='submit' name='showcaplist' value='Show Cappped List' /></td>";
		echo "</tr>";
	echo "</form>";
	
echo "</table>";

if(isset($_POST['capped']))
{
	$member=$_POST['capped'];
	date_default_timezone_set("America/Boise");
	$formatdate=date('Y-m-d H:i:s');
	$query="update oipmembers set lastcap='".$formatdate."' where username='".$member."'";
	queryfunction($query);
}

if(isset($_POST['showcaplist']))
{
	$capquerry="select username from oipmembers where lastcap!='NULL' order by lastcap";
	$capresults=queryfunction($capquerry);
	$count=0;
	echo "<table border=1>";
	while ($caprow=mysqli_fetch_array($capresults))
	{
		$count++;
		echo "<tr>";
		echo "<td>".$count."</td><td>".$caprow[0]."</td>";
		echo "<tr>";
	}
	echo "</table>";
}

if(isset($_POST['startcomp']))
{
	$skill=$_POST['selectcompskill'];
	date_default_timezone_set("America/Boise");
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
		$query="insert into ".$filename." values('".$username."','".$skill."','".$initlevel."','".$initxp."','".$finlevel."','".$finxp."','".$diflevel."','".$difxp."')";
		$results=queryfunction($query);

	}
}


if(isset($_POST['updatestats']) && isset($_POST['radioskill']))
{

	$skill=$_POST['radioskill'];
	date_default_timezone_set("America/Boise");
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

if(isset($_POST['showstats']) && isset($_POST['radioskill']))
{
	$skill=$_POST['radioskill'];
	date_default_timezone_set("America/Boise");
	$formatdate=date('MY');
	$filenamecap=$formatdate.$skill;
	$filename=strtolower($filenamecap);
	
	$query="select * from ".$filename." order by difxp desc, finxp desc, initxp desc";
	$results=queryfunction($query);
	echo "<table border=1>";
	echo "<td>Name</td><td>Skill</td><td>initlevel</td><td>initxp</td><td>finlevel</td><td>finxp</td><td>diflevel</td><td>difxp</td>";
	while ($row=mysqli_fetch_array($results))
	{
		echo "<tr>";
		echo "<td>".$row[0]."</td><td>".$row[1]."</td><td>".$row[2]."</td><td>".$row[3]."</td><td>".$row[4]."</td><td>".$row[5]."</td><td>".$row[6]."</td><td>".$row[7]."</td>";
		echo "<tr>";
	}
	echo "</table>";
}


?>



<?php
include_once "footer.php";
?>