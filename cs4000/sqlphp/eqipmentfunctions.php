<?php
function queryfunc($query)
{
	$connect = mysqli_connect("mysql.cs.dixie.edu", "jfrancom", "francom1", "jfrancom") or die("can't connect");
    $result = mysqli_query($connect, $query) or die("can't do query" . $query . mysqli_error($connect));
    if (!mysqli_affected_rows($connect) > 0)
	{
        echo "fail";
    }
	return $result;
}

function getbranddropdown($brand=Null)
{
	$query="select * from brand";
	$result=query($query);
	echo "<slect name='eqt_brand' id='eqt_brand'>"; //note: best practice is to do both names and ids
	while($row=mysqli_fetch_assoc($result))
	{
		$selected=($brand==$row[brand_id])?'selected=selected':'';
		echo "<option $selected value='$row[brand_id]'>$row[brand_name]</option>";
	}
	echo "</select>";
}
?>
