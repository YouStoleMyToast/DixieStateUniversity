<form method="POST" action="forms.php">
    <label>Name</label>
    <input type="text" name="user" />
    <input type="text" name="password" /> 
    <input type="submit" />
</form>

<?php
    echo "$_POST[user]";
    echo "<br />";
    echo "$_POST[password]"; 
?>
