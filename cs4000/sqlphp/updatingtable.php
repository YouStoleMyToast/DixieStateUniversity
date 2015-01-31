<?php

$result=mysqli_query($mysqli, $update);
print_r($result);

?>

<form action="<?=$_SERVER['PHP_SELF']?>" method="POST">
    <label for="itemname">Item Name</label>
    <input type="text" name="itemname" />
	
	<label for="quantity">Quantity</label>
    <input type="text" name="quantity" /> 
  
	<label for="brand">Brand</label>
    <input type="text" name="brand" /> 
    <input type="submit" />
</form>

<?php

if(isset($_POST))
{
	$name=$_POST['itemname'];//note name on right has to be the same as above in form, left can be different
	$qty=$_POST['quantity'];
	$brand=$_POST['brand'];
	
	$host='mysql.cs.dixie.edu';
	$username='jfrancom';
	$password='francom1';
	$conn=mysqli_connect($host, $username, $password, $username);
	
	$update="insert into equipment values(null,'$name', $qty,'brand');";////qty being a number
	$result=mysqli_query($conn, $update) or die('no can do'.$query.mysqli_error());
	if(mysqli_affected_rows($conn)>0)
	{
		echo "success";
	}
	else
	{
		echo "fail";
	}
}
?>