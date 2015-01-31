

<html>  
    <head>
        <title>Background Changer With Cookies</title>
    </head>

<?php

if(isset($_GET['color']))
{
	$bgcolor=$_GET['color'];
	setcookie('bgcolor',$bgcolor, time() + 600);//600 seconds
}
elseif(isset($_COOKIE['bgcolor']))
{
	$bgcolor=$_COOKIE['bgcolor'];
}

echo "<body bgcolor=$bgcolor>";
?>
    <form method=GET action=cookies1.php>
    <select name="color">
    <option>red</option>
    <option>blue</option>
    <option>green</option>
    </select>
    <input type="submit">
    </form>
    
</body>