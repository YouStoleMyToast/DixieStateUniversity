<?php
include_once "header.php";



echo "<div id='sublink'>";
echo "<ul>";
echo "<li><a href='http://www.ebeilmann.php.cs.dixie.edu/CS 4000/RS/members.php'>Members</a></li>";
echo "<li><a href='http://www.ebeilmann.php.cs.dixie.edu/CS 4000/RS/ranks.php'>Ranks</a></li>";
echo "<li><a href='http://www.ebeilmann.php.cs.dixie.edu/CS 4000/RS/join.php'>Join</a></li>";
echo "</ul>";
echo "</div>";
echo "<br>";

echo "<h1>Members</h1>";

if(isset($_SESSION['username']) && isset($_SESSION['admin']))
{	
	echo "<div id=logedmembersform>";
	echo "<table>";
	echo "<form method='post'>";
		echo "<tr>";
		echo "<td colspan=2><h6>Add/Update Members</h6></td>";
		echo "<td colspan=2 width='60px'></td>";
		echo "<td colspan=2><h6>Delete Members</h6></td>";
		echo "</tr>";
		
		echo "<tr>";
		echo "<td><label for='addmem'>Name</label></td>";
		echo "<td><input type='text' name='addedmember'/></td>";
		echo "<td colspan=2></td>";
		echo "<td><label for='delmem' style='position:relative;float:right;'>Name</label></td>";
		echo "<td colspan=2><input type='text' name='deletedmember'/></td>";
		echo "</tr>";
		
		echo "<tr>";
		echo "<td><label for='addedmem'>Rank</label></td>";
		echo "<td><select name='addedrank' style='width:120px;'>";
		$rankquery="select rank from runeranks where rank_id<6 order by rank_id desc";
		$rankresults=queryfunction($rankquery);
		while ($row=mysqli_fetch_array($rankresults))
		{
			echo "<option>".$row[0]."</option>";
		}
		echo "</select></td>";
		echo "<td colspan=4></td>";
		echo "</tr>";
		
		echo "<tr>";
		echo "<td><label for='memloc'>Location</label></td>";
		echo "<td><input type='text' name='memberlocation'/></td>";
		echo "<td colspan=4></td>";
		echo "</tr>";
		
		echo "<tr>";
		echo "<td><label for='addedmem'>Competing</label></td>";
		echo "<td><select name='addedcomp' style='width:60px;'>";
			echo "<option>Yes</option>";
			echo "<option>No</option>";
		echo "</select></td>";
		echo "<td colspan=4></td>";
		echo "</tr>";
		
		echo "<tr>";
		echo "<td colspan=2><input type='submit' name='addsubmit' value='Add/Update Member'/></td>";
		echo "<td colspan=2></td>";
		echo "<td colspan=2><input type='submit' name='delsubmit' value='Delete Member'/></td>";
		echo "</tr>";
	echo "</table>";
	echo "</form>";
	echo "</div>";
}

$center="Italy";
$maptype3='hybrid';
$sensor='false';
$zoom='1';
$size='550x350';
$regmark="&markers=size:small%7Ccolor:black%7C";
$mapquery="select username,clanrank,location from oipmembers order by clanrank, username";
$mapresults=queryfunction($mapquery);
$markloc=array();
$markstring="";
while ($maprow=mysqli_fetch_array($mapresults))
{
	$markloc[]=$maprow[2];
}
foreach($markloc as $m)
{
	if($m != NULL)
	{
		$markstring.=$regmark.$m;
	}
}
$url="http://maps.googleapis.com/maps/api/staticmap?center=".$center."&zoom=".$zoom."&size=".$size."&maptype=".$maptype3.$markstring."&sensor=".$sensor;
echo "<div id=map>";
echo "<img src='".$url."'>";
echo "</div>";
echo "<br>";
if(isset($_POST['deletedmember']) && isset($_POST['delsubmit']))
{
	$member=$_POST['deletedmember'];
	if($member=='')
	{
		echo "<div id='nonameerror'>";
		echo "No Name Was Entered";
		echo "</div>";
	}
	else
	{
		$delquerymem="delete from oipmembers where username='".$member."'";
		queryfunction($delquerymem);
		header("Location: ".$_SERVER['PHP_SELF'].""); 
	}
}
if(isset($_POST['addsubmit']))
{	
	$username=$_POST['addedmember'];
	if($username=='')
	{
		echo "<div id='nonameerror'>";
		echo "No Name Was Entered";
		echo "</div>";
	}
	else
	{
		if(isset($_POST['addedmember']))
		{	
			$existquery="select username from oipmembers where username='".$username."'";
			$existresult=queryfunction($existquery);
			$existarray=array();
			while ($existrow=mysqli_fetch_array($existresult))
			{
				$existarray[]=$existrow[0];
			}
			if(count($existarray)==0)
			{
				$createuserquery="insert into oipmembers (username) values('".$username."')";
				queryfunction($createuserquery);
			}
		}
		if(isset($_POST['addedrank']) && isset($_POST['addedmember']))
		{	
			$rank=$_POST['addedrank'];
			$rankquerry="update oipmembers set clanrank='".$rank."' where username='".$username."'";
			queryfunction($rankquerry);
		}
		if(isset($_POST['memberlocation']) && isset($_POST['addedmember']))
		{	
			$loc=$_POST['memberlocation'];
			if($loc=='')
			{
				$loc='NULL';
			}
			$locquerry="update oipmembers set location='".$loc."' where username='".$username."'";
			queryfunction($locquerry);
		}
		if(isset($_POST['addedcomp']) && isset($_POST['addedmember']))
		{	
			$initcomp=$_POST['addedcomp'];
			$comp=0;
			if($initcomp='Yes')
			{
				$comp=1;
			}
			$locquerry="update oipmembers set competing='".$comp."' where username='".$username."'";
			queryfunction($locquerry);
		}
		header("Location: ".$_SERVER['PHP_SELF'].""); 
	}
}
echo "<div id=seememberstable>";
echo "<table>";
echo "<td><h4>Name</h4></td><td><h4>Rank</h4></td><td><h4>Location</h4></td>";
$listquery="select username,clanrank,location from oipmembers where clanrank='council' order by username";
$listresults=queryfunction($listquery);
while ($listrow=mysqli_fetch_array($listresults))
{
	$name=$listrow[0];
	$rank=$listrow[1];
	$loc=$listrow[2];
	if($loc=='NULL')
	{
		$loc='';
	}
	echo "<tr>";
	echo "<td>".$name."</td><td>".$rank."</td><td>".$loc."</td>";
	echo "<tr>";
	$markloc[]=$listrow[2];
}

$listquery="select username,clanrank,location from oipmembers where clanrank='Swashbuckler' order by username";
$listresults=queryfunction($listquery);
while ($listrow=mysqli_fetch_array($listresults))
{
	$name=$listrow[0];
	$rank=$listrow[1];
	$loc=$listrow[2];
	if($loc=='NULL')
	{
		$loc='';
	}
	echo "<tr>";
	echo "<td>".$name."</td><td>".$rank."</td><td>".$loc."</td>";
	echo "<tr>";
	$markloc[]=$listrow[2];
}

$listquery="select username,clanrank,location from oipmembers where clanrank='Buccaneer' order by username";
$listresults=queryfunction($listquery);
while ($listrow=mysqli_fetch_array($listresults))
{
	$name=$listrow[0];
	$rank=$listrow[1];
	$loc=$listrow[2];
	if($loc=='NULL')
	{
		$loc='';
	}
	echo "<tr>";
	echo "<td>".$name."</td><td>".$rank."</td><td>".$loc."</td>";
	echo "<tr>";
	$markloc[]=$listrow[2];
}

$listquery="select username,clanrank,location from oipmembers where clanrank='Privateer' order by username";
$listresults=queryfunction($listquery);
while ($listrow=mysqli_fetch_array($listresults))
{
	$name=$listrow[0];
	$rank=$listrow[1];
	$loc=$listrow[2];
	if($loc=='NULL')
	{
		$loc='';
	}
	echo "<tr>";
	echo "<td>".$name."</td><td>".$rank."</td><td>".$loc."</td>";
	echo "<tr>";
	$markloc[]=$listrow[2];
}

$listquery="select username,clanrank,location from oipmembers where clanrank='Swabbie' order by username";
$listresults=queryfunction($listquery);
while ($listrow=mysqli_fetch_array($listresults))
{
	$name=$listrow[0];
	$rank=$listrow[1];
	$loc=$listrow[2];
	if($loc=='NULL')
	{
		$loc='';
	}
	echo "<tr>";
	echo "<td>".$name."</td><td>".$rank."</td><td>".$loc."</td>";
	echo "<tr>";
	$markloc[]=$listrow[2];
}
echo "</table>";
echo "</div>";	
	
include_once "footer.php";
?>
