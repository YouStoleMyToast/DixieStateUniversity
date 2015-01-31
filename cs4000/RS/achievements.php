<?php
include_once "header.php";

echo "<h1>Achievements</h1>";

echo "<div id=achieve>";
echo "<table>";
echo "<tr>";

	echo "<td>";
	echo "<form method='post'>";
		echo "<input type='submit' name='updateach' value='Update Stats'/>";
	echo "</form>";
	echo "</td>";
	
	echo "<td>";
	echo "<form method='post'>";
		echo "<input type='submit' name='shownns' value='Members at Level 99'/>";
	echo "</form>";
	echo "</td>";
	
	echo "<td>";
	echo "<form method='post'>";
		echo "<input type='submit' name='maxlevel' value='Members at Max Level'/>";
	echo "</form>";
	echo "</td>";
	
echo "</tr>";
echo "</table>";
echo "</div>";


if(isset($_POST['shownns']))
{
	$query="select username,skill from ninetynine order by username,skill";
	$results=queryfunction($query);
	echo "<div id=nntable>";
	echo "<table width=600px>";
	echo "<tr>";
	echo "<td colspan=2><h4>Players With Level 99</h4></td>";
	echo "</tr>";
	echo "<tr>";
	echo "<td><h4>Name</h4></td><td><h4>skill</h4></td>";
	echo "</tr>";
	while ($row=mysqli_fetch_array($results))
	{
		echo "<tr>";
		echo "<td>".$row[0]."</td><td>".$row[1]."</td>";
		echo "<tr>";
	}
	echo "</table>";
	echo "</div>";
}

if(isset($_POST['maxlevel']))
{
	$query="select distinct(username) from runemax";
	$results=queryfunction($query);
	echo "<div id=maxtable>";
	echo "<table>";
	echo "<td><h4>Player at Max Level</h4></td>";
	while ($row=mysqli_fetch_array($results))
	{
		echo "<tr>";
		echo "<td>".$row[0]."</td>";
		echo "<tr>";
	}
	echo "</table>";
	echo "</div>";
}

if(isset($_POST['updateach']))
{

	$skillquery="select skill from runeskills";
	$skillresults=queryfunction($skillquery);
	$skillarray=array();
	
	while ($skillrow=mysqli_fetch_array($skillresults))
	{
			$skillarray[]=$skillrow[0];
	}
	$ninequery="select username from oipmembers";
	$nineresults=queryfunction($ninequery);
	while ($row=mysqli_fetch_array($nineresults))
	{
		$username=$row[0];
		$clanrank='swabbie';
		$link = 'http://hiscore.runescape.com/index_lite.ws?player='.$username;
		$file=file_get_contents($link);
		$str = preg_replace(array('/[^\d,]/','/(?<=,),+/','/^,+/','/,+$/'),',',$file);
		$statlist=explode(',',$str);
		{
			if($statlist[$stat]=='99')
			{
				$skillnumber=$stat/3;
				$skill=$skillarray[$skillnumber];
				$query="insert ignore into ninetynine values('".$username."','".$skill."')";
				queryfunction($query);
			}
			if($statlist[1]==2496)
			{
				$maxquery="insert into runemax values('".$username."')";
				queryfunction($maxquery);
			}
		}
		
	}
	
}

/*
if(isset($_POST['statcheck']))
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
		
		$rank=$statlist[$rankloc];
		$level=$statlist[$levelloc];
		$xp=$statlist[$xploc];
		$query="insert into ninetynine values('".$username."','".$skill."') where ";
		$results=queryfunction($query);

	}
}
*/


include_once "footer.php";
?>
