<?php
session_start();
if(isset($_SESSION['productCode']))//run sql for image
{
	echo $_SESSION['productCode'];
}
?>

<!DOCTYPE html>
<html>

<?php
if(isset($_SESSION['productCode']))//run sql for image
{
	echo $_SESSION[productCode];
	$imagequery="select image_link from products where productCode='".$_SESSION[productCode]."'";
	echo $imagequery;
	$connect = mysqli_connect("mysql.cs.dixie.edu", "ebeilmann", "kireth2002", "ebeilmann") or die("can't connect");
	$showresult = mysqli_query($connect, $imagequery) or die("can't do query" . $imagequery . mysqli_error($connect));
	echo "<img src='".$row[image_link]."' alt='fancy image here' width=250 height=200>";
}


if (isset($_POST['productName'])) //sql for insert
{
	$ProductCode=time();//just a way to garentee a unique key
	$ProductName=$_POST['productName'];
	$ProductLine=$_POST['productLine'];
	$ProductDescription=$_POST['productDescription'];
	$image_link=$_POST['image_link'];

	$insertquery = "insert into products values('$ProductCode','$ProductName','$ProductLine','$ProductDescription','$image_link')";
	$connect = mysqli_connect("mysql.cs.dixie.edu", "ebeilmann", "kireth2002", "ebeilmann") or die("can't connect");
	mysqli_query($connect, $insertquery) or die("can't do query" . $insertquery . mysqli_error($connect));
}
?>

<label>Submit a product:</label>
<form method="POST" action="http://www.ebeilmann.php.cs.dixie.edu/CS%204000/midterm/midterm.php">
	<label for="productName">Product Name</label>
	<select name="productName">
		<option>Tucker</option>
		<option>Studebaker</option>
		<option>DeSoto</option>
		<option>Edsel</option>
		<option>Packard</option>
	</select>

	<label for="productLine">Product Line</label>
	<input type="text" name="productLine">

	<label for="productDescription">Product Description</label>
	<input type="text" name="productDescription">

	<label for="image_link">Image Link</label>
	<input type="text" name="image_link" value="http://files.conceptcarz.com/img/Tucker/48_Tucker_Torpedo_DV-06-RMM-06.jpg">

	<input type="submit" name="submit_btn" value="Submit"/>
</form>

<label>Select Image:</label>
<form method="POST" action="midterm.php">
	<label for="productName">Product Name</label>
	
	<?php 
	$showquery="select * from products";
	$connect = mysqli_connect("mysql.cs.dixie.edu", "ebeilmann", "kireth2002", "ebeilmann") or die("can't connect");
	$showresult = mysqli_query($connect, $showquery) or die("can't do query" . $showquery . mysqli_error($connect));

	echo "<select name='productName'>";

	while ($row = mysqli_fetch_assoc($showresult)) 
	{
		echo "<option value='".$row['productCode']."'>".$row['productName']."</option>";
	}
	?>	
	<input type='submit' name='show_btn' value='Show'>
	<? 
		$_SESSION['productCode']=$row['productCode'] ;
		echo $_SESSION['productCode'];
	?>
	</select>
</form>

</html>

<?php
//http://www.ebeilmann.php.cs.dixie.edu/CS%204000/midterm/midterm.php
?>