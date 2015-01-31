<?php
include_once "header.php";
?>

<h1>Media Collection</h1>

<?php
$fin=file_get_contents("mediadata.txt");
$lines = explode("\n", $fin);
echo "<h2>Music</h2>";
echo "<table>";
foreach($lines as $line)
{
	$array=json_decode($line, true);
	echo "<tr>";
	foreach($array as $key=>$value)
	{
		if($array['mediatype'] == 'music')
		{
			echo "<td>$value</td>";
		}
	}
	echo "</tr>";
}
echo "</table>";
?>

<?php
$fin=file_get_contents("mediadata.txt");
$lines = explode("\n", $fin);
echo "<h2>Shows</h2>";
echo "<table>";
foreach($lines as $line)
{
	$array=json_decode($line, true);
	echo "<tr>";
	foreach($array as $key=>$value)
	{
		if($array['mediatype'] == 'show')
		{
			echo "<td>$value</td>";
		}
	}
	echo "</tr>";
}
echo "</table>";
?>

<?php
$fin=file_get_contents("mediadata.txt");
$lines = explode("\n", $fin);
echo "<h2>Movies</h2>";
echo "<table>";
foreach($lines as $line)
{
	$array=json_decode($line, true);
	echo "<tr>";
	foreach($array as $key=>$value)
	{
		if($array['mediatype'] == 'movie')
		{
			echo "<td>$value</td>";
		}
	}
	echo "</tr>";
}
echo "</table>";
?>

<?php
$fin=file_get_contents("mediadata.txt");
$lines = explode("\n", $fin);
echo "<h2>Pictures</h2>";
echo "<table>";
foreach($lines as $line)
{
	$array=json_decode($line, true);
	echo "<tr>";
	foreach($array as $key=>$value)
	{
		if($array['mediatype'] == 'picture')
		{
			echo "<td>$value</td>";
		}
	}
	echo "</tr>";
}
echo "</table>";
?>


<?php
include_once "footer.php";
?>
