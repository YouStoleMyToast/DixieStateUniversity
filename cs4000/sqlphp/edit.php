<?php
include_once 'equipmentfunctions.php';

if(isset($_POST['eqt_name']))
{
	$eqt_brand=$POST['eqt_brand'];
	$eqt_name=$POST['eqt_name'];
	$eqt_quantity=$POST['eqt_quantity'];
	$eqt_id=$_POST['eqt_id]';
	
	//do update
	$query="update equipment set name=$eqt_name, brand=$eqt_brand, quantity=$eqt_quanity where id=$eqt_id";
	queryfunc($query);
	header('Locations:./equipment.php');
}
else{
//get variable
$id=$_GET['id'];

//query
$query="select * from equipment where id=$id";
$results=queryfunc($query);
//get that row
$row=mysqli_fetch_assoc($results);
//display the row in a form
echo "<form method=post action=$_SERVE[PHP_SELF]>";

?>
<label for='eqt_name'>Equipment Name:</label>
<input type='text' name='eqt_name' value=<? $row['name']?>/>
<input type='text' name='eqt_name' value=<? $row['id']?>/>
<input type='hiden' name='action' value='savechanges'/>
<label for="eqt_quantity">Quantity:</label>

<select name="eqt_quantity">
<?php
for ($i = 0; $i < 10; $i++) 
{
	$selected=($row['brand']==$i)?'selected':'';
    echo "<option selected=$selected value=$i>$i</option>";
}
?>
</select>
<label for="eqt_brand">Equipment Brand:</label>
<input type="text" name="eqt_brand" />
<input type="submit" name="btn_submit" value="Haga cliq"/>

//submit the new values to the same page?
//update the database
//send back to equipment.php
