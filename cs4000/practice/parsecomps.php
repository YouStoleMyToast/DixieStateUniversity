<?php

$file=fopen("http://vt4000.cs.dixie.edu/fileio/have_found2.txt",'r');

echo "<table border=1>";
while($line = fgets($file))
{
	$ary=explode(" ",$line);
	echo "<tr>";
	foreach($ary as $v)
	{
		echo "<td>$v</td>";
	}
	echo "</tr>";
}
echo "</table>";
fclose($file);
?>