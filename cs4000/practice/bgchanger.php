<html>  
    <head>
        <title>Background Changer</title>
    </head>

<?php
$bgcolor=$_GET['color'];
echo $bgcolor;
echo "<body bgcolor=$bgcolor>";
?>
    <form method=GET action=background.php>
    <select name="color">
    <option>red</option>
    <option>blue</option>
    <option>green</option>
    </select>
    <input type="submit">
    </form>
    
</body>