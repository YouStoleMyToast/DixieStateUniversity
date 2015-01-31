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
	/*
	if(isset($_SERVER['editname']) && isset($_SERVER['editrank'])  && isset($_SERVER['editlocation']))
	{
		$editname=$_SERVER['editname'];
		$editrank=$_SERVER['editrank'];
		$editlocation=$_SERVER['editlocation'];
		echo "<div id=logedmembersform>";
		echo "<table border=1>";
		echo "<form method='post'>";
			echo "<tr>";
			echo "<td colspan=2><h6>Add/Update Members</h6></td>";
			echo "<td colspan=2 width='50px'></td>";
			echo "<td colspan=2><h6>Delete Members</h6></td>";
			echo "</tr>";
			
			echo "<tr>";
			echo "<td><label for='addmem'>Name</label></td>";
			echo "<td><input type='text' name='addedmember' value='".$editname."'/></td>";
			echo "<td colspan=4></td>";
			echo "</tr>";
			
			echo "<tr>";
			echo "<td><label for='addedmem'>Rank</label></td>";
			echo "<td><select name='addedrank' style='width:120px;'>";
			$rankquery="select rank from runeranks where rank_id<6 order by rank_id desc";
			$rankresults=queryfunction($rankquery);
			echo "<option>".$editrank."</option>";
			while ($rankrow=mysqli_fetch_array($rankresults))
			{
				echo "<option>".$rankrow[0]."</option>";
			}
			echo "</select></td>";
			
			echo "<td colspan=2></td>";
			echo "<td><label for='delmem'>Name</label></td>";
			echo "<td colspan=2><select name='deletedmember' style='width:120px;'>";
			$deluserquery="select username from oipmembers";
			$deluserresults=queryfunction($deluserquery);
			echo "<option></option>";
			while ($deluserrow=mysqli_fetch_array($deluserresults))
			{
				echo "<option>".$deluserrow[0]."</option>";
			}
			echo "</select></td>";
			echo "</tr>";
			
			echo "<tr>";
			echo "<td><label for='memloc'>Location</label></td>";
			echo "<td><input type='text' name='memberlocation' value='".$editlocation."'/></td>";
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
	if(!isset($_SERVER['editname']) && !isset($_SERVER['editrank']) && !isset($_SERVER['editlocation']))
	{
	*/
		echo "<div id=logedmembersform>";
		echo "<table>";
		echo "<form method='post'>";
			echo "<tr>";
			echo "<td colspan=2><h6>Add/Update Members</h6></td>";
			echo "<td colspan=2 width='50px'></td>";
			echo "<td colspan=2><h6>Delete Members</h6></td>";
			echo "</tr>";

			echo "<tr>";
			echo "<td><label for='addmem'>Name</label></td>";
			echo "<td><input type='text' name='addedmember'/></td>";
			echo "<td colspan=2></td>";
			echo "<td><label for='delmem'>Name</label></td>";
			echo "<td colspan=2><select name='deletedmember' style='width:120px;'>";
			$rankquery="select username from oipmembers";
			$rankresults=queryfunction($rankquery);
			echo "<option></option>";
			while ($row=mysqli_fetch_array($rankresults))
			{
				echo "<option>".$row[0]."</option>";
			}
			echo "</select></td>";
			echo "</tr>";
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
	//}
}

$center="Italy";
$maptype3='hybrid';
$sensor='false';
$zoom='1';
$size='550x350';
$regmark="&markers=color:black%7Clabel:O%7C";
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
	$delquerymem="delete from oipmembers where username='".$member."'";
	queryfunction($delquerymem);
	header("Location: ".$_SERVER['PHP_SELF']."");  
}

if(isset($_POST['addsubmit']) && isset($_POST['addedmember']))
{
	$username=$_POST['addedmember'];
	if(isset($_POST['addedmember']))
	{
		$createuserquery="insert into oipmembers (username) values('".$username."')";
		queryfunction($createuserquery);
	}
	if(isset($_POST['addedrank']))
	{
		$rank=$_POST['addedrank'];
		$rankquerry="update oipmembers set clanrank='".$rank."' where username='".$username."'";
		queryfunction($rankquerry);
	}
	if(isset($_POST['memberlocation']))
	{
		$loc=$_POST['memberlocation'];
		$locquerry="update oipmembers set location='".$loc."' where username='".$username."'";
		queryfunction($locquerry);
	}
	if(isset($_POST['addedcomp']))
	{
		$comp=$_POST['addedcomp'];
		$locquerry="update oipmembers set competing='".$comp."' where username='".$username."'";
		queryfunction($locquerry);
	}
	header("Location:http://www.ebeilmann.php.cs.dixie.edu/CS%204000/RS/members.php");  
}

$listquery="select username,clanrank,location from oipmembers order by clanrank, username";
$listresults=queryfunction($listquery);
echo "<div id=seememberstable>";
echo "<table>";
echo "<td><h4>Name</h4></td><td><h4>Rank</h4></td><td><h4>Location</h4></td>";
while ($listrow=mysqli_fetch_array($listresults))
{
	echo "<tr>";
	echo "<td class='".$listrow[0]."'>".$listrow[0]."</td><td class='".$listrow[1]."'>".$listrow[1]."</td><td class='".$listrow[2]."'>".$listrow[2]."</td>";
	/*
	if(isset($_SESSION['username']) && isset($_SESSION['admin']))
	{
		echo "<form method='post'>";
		echo "<td> <input type='submit' value='Edit'></td>";
		$_SERVER['editname']=$listrow[0]; 
		$_SERVER['editrank']=$listrow[1]; 
		$_SERVER['editlocation']=$listrow[2];
		echo "</form>";
	}
	*/
	echo "<tr>";
	$markloc[]=$listrow[2];
}
echo "</table>";
echo "</div>";	
	
include_once "footer.php";
?>
