<?php
	include_once "header.php";
?>

<?php

	include 'loginfunc.php';

	if(!empty($_POST))
	{
		$user=$_POST['username'];
		$password=$_POST['password'];
		authenticate($user,$password);
	}

?>


<form action="<?=$_SERVER['PHP_SELF']?>" method="POST">
    <label>Name</label>
    <input type="text" name="user" />
	<label>Password</label>
    <input type="text" name="password" /> 
    <input type="submit" />
</form>



<?php
	include_once "footer.php";
?>