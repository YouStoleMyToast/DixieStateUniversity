<!DOCTYPE html>
<html>

<?php
if(isset($_GET['PN']))//run sql for image
{
	$imagequery="select image_link from products where productCode='".$row['productCode']."'";
	$connect = mysqli_connect("mysql.cs.dixie.edu", "ebeilmann", "kireth2002", "ebeilmann") or die("can't connect");
	$imageresult = mysqli_query($connect, $imagequery) or die("can't do query" . $imagequery . mysqli_error($connect));
	echo "<img src='".$imageresult."' alt='fancy image here' width=250 height=200>";
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
	<input type="text" name="productName">
	
	<label for="productLine">Product Line</label>
	<input type="text" name="productLine">

	<label for="productDescription">Product Description</label>
	<input type="text" name="productDescription">

	<label for="image_link">Image Link</label>
	<input type="text" name="image_link">

	<input type="submit" name="submit_btn" value="Submit"/>
</form>

<label>Select Image:</label>

<form method="POST" action="midterm.php"> 
<label for="PN">Product Name</label>
	
	<?php 
		$showquery="select * from products";
		$connect = mysqli_connect("mysql.cs.dixie.edu", "ebeilmann", "kireth2002", "ebeilmann") or die("can't connect");
		$showresult = mysqli_query($connect, $showquery) or die("can't do query" . $showquery . mysqli_error($connect));
		echo "<select name='PN'>";
		while ($row = mysqli_fetch_assoc($showresult)) 
		{
			echo "<option value='$row[productName]'>$row[productName]</option>";
		}
		echo "<input type='submit' name='show_btn' value='Show'>";
	?>
	</select>
</form>

</html>

<?php
//http://www.ebeilmann.php.cs.dixie.edu/CS%204000/midterm/midterm.php
?>


