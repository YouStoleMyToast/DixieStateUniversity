<?php

include_once "header.php";

$finmembers=file_get_contents("memberslist.txt");
$memberslist=explode("\n", $finmembers);
$finskillslist=file_get_contents("skillslist.txt");
$skillslist=explode("\r\n", $finskillslist);
$finminigames=file_get_contents("minigamelist.txt");
$minigames=explode("\n", $finminigames);

//for creating a data set
echo "<table border='1'>";
echo "<tr>";
	echo "<td>";
	echo "<h2>For Creating a File of all Players in one Skill</h2>";
	echo "<form method='post'>";
		echo "<label for='createdata'>Skill</lable>";
		echo "<select name='setskill'>";
		for($i = 0; $i <count($skillslist) ; $i++)
		{
			echo '<option value="'.$i.'">'.$skillslist[$i].'</option>';
		}
		echo "</select>";
		echo "<p><input type='submit' name='createdata' value='CreateData'/></p>";
	echo "</form>";
	echo "</td>";

	//show current stats without making data
	echo "<td>";
	echo "<h2>For Displaying The Current Stats of all Players in one Skill</h2>";
	echo "<form method='post'>";
		echo "<label for='displaystats'>Skill</lable>";
		echo "<select name='skillset'>";
		for($i = 0; $i <count($skillslist) ; $i++)
		{
			echo '<option value="'.$i.'">'.$skillslist[$i].'</option>';
		}
		echo "</select>";
		echo "<p><input type='submit' name='displaystats' value='DisplayData'/></p>";
	echo "</form>";
	echo "</td>";

	//for individual members stats
	echo "<td>";
	echo "<h2>For Displaying an Individuals Stats</h2>";
	echo "<form method='post'>";
		echo "<label for='displayplayer'>Member</lable>";
		echo "<select name='playerstat'>";
		for($i = 0; $i <count($memberslist) ; $i++)
		{
			echo "<option>$memberslist[$i]</option>";
		}
		echo "</select>";
		echo "<p><input type='submit' name='displayplayer' value='SoloStats'/></p>";
	echo "</form>";

	//for processing a full report
	echo "<td>";
	echo "<h2>For Displaying a Full Report</h2>";
	echo "<form method='post'>";
		echo "<label for='processdata'>Skill</lable>";
		echo "<select name='getskill'>";
		for($i = 0; $i <count($skillslist) ; $i++)
		{
			echo '<option value="'.$i.'">'.$skillslist[$i].'</option>';
		}
		echo "</select>";
		echo "<p><input type='submit' name='processdata' value='ProcessData'/></p>";
	echo "</form>";
	echo "</td>";
echo "</tr>";
echo "</table>";

//to process data
if(isset($_POST['processdata']))
{
	//$getmonth=$month[$_POST['getmonth']];
	//$getyear=$year[$_POST['getyear']];
	$getskill=$skillslist[$_POST['getskill']];
	processdataset($getskill);
}

//isset for individual members stats
if(isset($_POST['playerstat']))
{
	$player=$_POST['playerstat'];
	printplayerstats($player, $skillslist, $minigames);
}

//isset for printing current stats
if(isset($_POST['displaystats']))
{
	$skill=$skillslist[$_POST['skillset']];
	$skillindex = $_POST['skillset'];
	printsingleskillforall($memberslist, $skill, $skillindex, $skillslist);
}

//isset for creating a data set
if(isset($_POST['createdata']))
{
	$skillindex = $_POST['setskill'];
	$skill=$skillslist[$_POST['setskill']];
	createdataset($memberslist, $skill, $skillindex, $skillslist);
}

function processdataset($skill)
{
	$sfin=file_get_contents("hpapr2013start.txt");
	$cfin=file_get_contents("hpapr2013end.txt");
	$sarray=explode("\n",$sfin);
	$carray=explode("\n",$cfin);
	$res = array_merge_recursive($sarray,$carray);
	$resjson=json_encode($res);
	$array=json_decode($resjson, true);
	$full=count($array);
	$half=count($array)/2;
	echo "<table border=1>";
	echo "<tr>";
	echo "<th>Player</th><th>Skill</th><th colspan=2>Original</th><th colspan=2>Current</th><th colspan=2>Difference</th>";
	$i=0;
	while($i<$half)
	{
		echo "<tr>";
		$split=explode(",",$array[$i]);
		
		$name=str_replace('"','',$split[0]);
		$name=str_replace('[','',$name);
		$track=str_replace('"','',$split[1]);
		$track=str_replace('\r','',$track);
		$slevel=str_replace('"','',$split[2]);
		$sxp=str_replace('"','',$split[3]);
		$sxp=str_replace(']','',$sxp);
		
		echo "<td>".$name."</td><td>".$track."</td><td>".$slevel."</td><td>".$sxp."</td>";
		
		$splitc=explode(",",$array[$half+$i]);

		$flevel=str_replace('"','',$splitc[2]);
		$fxp=str_replace('"','',$splitc[3]);
		$fxp=str_replace(']','',$fxp);
		
		echo "<td>".$flevel."</td><td>".$fxp."</td>";
		$leveldif=$flevel-$slevel;
		$xpdif=$fxp-$sxp;

		echo "<td>".$leveldif."</td><td>".$xpdif."</td>";
		$i++;
		echo "</tr>";
		//echo $array[$i];
		//echo $array[$half+$i];
		$i++;
	}
	echo "</table>";
}

function createdataset($memberslist, $skill, $skillindex, $skillslist)
{
	$outfile="hpapr2013end.txt";
	$fin=fopen($outfile,"w");
	fclose($fin);
	for($j = 0; $j <count($memberslist) ; $j++)
	{
		$player=$memberslist[$j];
		$link = 'http://hiscore.runescape.com/index_lite.ws?player='.$player;
		$file=file_get_contents($link);//$file type is string
		$arr1=str_split($file);
		$newstr="";
		$numarray=array('0','1','2','3','4','5','6','7','8','9','-');
		for($i = 0; $i <count($arr1) ; $i++)
		{
			if(in_array($arr1[$i],$numarray))
			{
				$newstr=$newstr.$arr1[$i];
			}
			else
			{
				$newstr=$newstr.',';
			}
		}
		$stats=explode(',',$newstr);
		$levelloc=$skillindex*3+1;
		$xploc=$skillindex*3+2;
		$level=$stats[$levelloc];
		$xp=$stats[$xploc];
		$currentContents = file_get_contents($outfile);
		$fin=fopen($outfile,"w");
		$playerdata=array($player, $skill, $level, $xp);
		$object = json_encode($playerdata);
		fwrite($fin, $currentContents.$object."\n");
	}
	fclose($fin);
}

function printsingleskillforall($memberslist, $skill, $skillindex, $skillslist)
{
	echo "<h2>Current Stats</h2>";
	echo "<table border='1'>";
	echo '<tr>';
	echo '<td></td>';
	echo '<td>Skill</td>';
	echo '<td>Level</td>';
	echo '<td>Total XP</td>';
	echo '</tr>';
	for($j = 0; $j <count($memberslist) ; $j++)
	{
		$player=$memberslist[$j];
		$link = 'http://hiscore.runescape.com/index_lite.ws?player='.$player;
		$file=file_get_contents($link);//$file type is string
		$arr1=str_split($file);
		$newstr="";
		$numarray=array('0','1','2','3','4','5','6','7','8','9','-');
		for($i = 0; $i <count($arr1) ; $i++)
		{
			if(in_array($arr1[$i],$numarray))
			{
				$newstr=$newstr.$arr1[$i];
			}
			else
			{
				$newstr=$newstr.',';
			}
		}
		$stats=explode(',',$newstr);
		
		$levelloc=$skillindex*3+1;
		$xploc=$skillindex*3+2;
		echo '<tr>';
		echo '<td>'.$player.'</td>';
		echo '<td>'.$skill.'</td>';
		echo '<td>'.$stats[$levelloc].'</td>';
		echo '<td>'.$stats[$xploc].'</td>';
		echo '</tr>';
	}
	echo '</table>';
}

function printmemberlist($memberslist)
{
	sort($memberslist);
	for($q = 0; $q <count($memberslist) ; $q++)
	{
		echo $memberslist[$q].'<br>';
	}
}

function printplayerstats($player, $skillslist, $minigames)
{
	echo "<h2>Stats for ".$player."</h2>";
	echo "<table border='1'>";
	echo '<tr>';
	echo '<td></td>';
	echo '<td>Rank</td>';
	echo '<td>Level</td>';
	echo '<td>Total XP</td>';
	echo '</tr>';
	$link = 'http://hiscore.runescape.com/index_lite.ws?player='.$player;
	$file=file_get_contents($link);//$file type is string
	$arr1=str_split($file);
	$newstr="";
	$numarray=array('0','1','2','3','4','5','6','7','8','9','-');
	for($i = 0; $i <count($arr1) ; $i++)
	{
		if(in_array($arr1[$i],$numarray))
		{
			$newstr=$newstr.$arr1[$i];
		}
		else
		{
			$newstr=$newstr.',';
		}
	}
	$stats=explode(',',$newstr);	
	$skillcount=count($skillslist);
	$skilldatacount=$skillcount*3;
	$skillstats=array();
	for($m = 0; $m <$skilldatacount ; $m++)
	{
		array_push($skillstats, $stats[$m]);
	}

	$gamecount=count($minigames);
	$gamedatacount=$gamecount*2;
	$gamestats=array();
	for($n = $skilldatacount; $n <count($stats) ; $n++)
	{
		array_push($gamestats, $stats[$n]);
	}

	$skillnum=0;
	for($j = 0; $j <(count($skillstats)) ; $j++)
	{
		$skillnum=$j/3;
		$skill=$skillslist[$skillnum];
		if($j%3==0)
		{
			echo '<tr>';
			echo '<td>'.$skill.'</td>';
			echo '<td>'.$skillstats[$j].'</td>';
		}
		if($j%3==1)
		{
			echo '<td>'.$skillstats[$j].'</td>';
		}
		if($j%3==2)
		{
			echo '<td>'.$skillstats[$j].'</td>';
			echo '</tr>';
			$skillnum=$skillnum++;
		}
	}
	echo '</table>';
	
	echo "<table border='1'>";
	echo '<tr>';
	echo '<td></td>';
	echo '<td>Rank</td>';
	echo '<td>Level</td>';
	echo '</tr>';
	$gamenum=0;
	for($k = 0; $k <$gamedatacount ; $k++)
	{
		$gamenum=$k/2;
		$minigame=$minigames[$gamenum];
		if($k%2==0)
		{
			echo '<tr>';
			echo '<td>'.$minigame.'</td>';
			echo '<td>'.$gamestats[$k].'</td>';
		}
		if($k%2==1)
		{
			echo '<td>'.$gamestats[$k].'</td>';
			echo '</tr>';
		}
	}
	echo '</table>';
}

?>