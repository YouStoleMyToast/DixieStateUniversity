<?php

$host='mysql.cs.dixie.edu';
$username='jfrancom';
$password='francom1';

$mysqli=mysqli_connect($host, $username, $password, $username);
print_r($mysqli);

$sql= "SELECT * from customers";

$result=mysqli_query($mysqli, $sql);
echo "<br >";
echo "<br >";
print_r($result);
echo "<br >";
echo "<br >";
$fields=mysqli_fetch_fields($result);
echo "<pre>";
print_r($fields);
echo "/pre>";
echo "<br >";
echo "<br >";
// while($row = mysqli_fetch_assoc($result))
// {
	// echo '<pre>';
	// print_r($row);
	// echo '</pre>';
// }
echo "<form>";
echo "<select name=customer_id>";
while($row = mysqli_fetch_assoc($result))
{
	echo "option value=$row[customerNumber]>$row[customerNumber]</option>";
}
echo "</select>";
echo"</form>"
?>