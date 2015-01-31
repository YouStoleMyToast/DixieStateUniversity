<?php 
include_once 'equipmentfunctions.php';
?>
<html>
    <head>
        <title>This is my equipment page</title>
        <style>
            label {color:sienna;}
            body {background-color:#9999ff;}
        </style>
    </head>
    <body>
        <form method="POST" action="equipment.php">
            <label for="eqt_name">Equipment Name:</label>
            <input type="text" name="eqt_name" />
            <label for="eqt_quantity">Quantity:</label>

            <select name="eqt_quantity">
			
<?php 		
for ($i = 0; $i < 10; $i++) {
	$selected=($row['quantity']==$i)?'selected=selected':'';
    echo "<option value=$i>$i</option>";
}
?>
            </select>
            <label for="eqt_brand">Equipment Brand:</label>
            <?php
			getbranddropdown();
			?>
            <input type="submit" name="btn_submit" value="Haga cliq"/>
        </form>

    </body>
</html>
<?php
if (isset($_POST)) 
{
    $eqt_name = $_POST["eqt_name"];
    $eqt_quantity = $_POST["eqt_quantity"];
    $eqt_brand = $_POST["eqt_brand"];
    $query = "INSERT into equipment VALUES(NULL, '$eqt_name', '$eqt_quantity', '$eqt_brand')";
	queryfunc($query);
}
if(isset($_GET['action']))
{
	$query="delete from row where id=$_GET[id]";
	queryfunc($query);
}
$query="select * from equipment as e
		join brand as b
		on e.brand=b.brand_id";
$results=queryfunc($query);
echo "<table>";
while ($row=mysqli_fetch_array($results))//mysqli_fetch_assoc while i can fetch a row out of the results with using column name in [] below//if fetch array you can use index numbers in [] below
{
	echo "<tr>";
	echo "<td> $row[name]</td>";
	echo "<td> $row[quantity]</td>";
	echo "<td>$row[brand_name]</td>";
	echo "<td><a href=./equipment.php?action=delete&id=$row[id]>del</a></td>";
	echo "<td><a href=./edit.php?action=delete&id=$row[id]>edit</a></td>";
	echo "</tr>";
}
echo "</table>";
?>
