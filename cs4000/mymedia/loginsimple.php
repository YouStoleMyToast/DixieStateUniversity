<?php
include_once "header.php";
if(!isset($_SESSION['invalid_attempts']))
{
	$_SESSION['invalide_attempts'] = 0;
}

if(isset($_POST))
{
	$user = $_POST['user'];
	$password = $_POST['password'];
	if(($user=='eric')&&($password=='password'))
	{
		echo "You are logged in as $user<br>";
		$_SESSION['user'] = $user;
	}
	else
	{
		echo '<h1>Login</h1>';
		$_SESSION['invalid_attempts']+=1;
		$times_left=5-$_SESSION['invalid_attempts'];
		echo "you have tried to log in"
		.$_SESSION['invalid attempts']
		."times, you have $times_left attempts";
	}
}
if(!isset($_SESSION['user']) AND $_SESSION['invalid_attempts'] < $times_left)
{

?>
<form action="<?=$_SERVER['PHP_SELF']?>" method="POST">
    <label>Name</label>
    <input type="text" name="user" />
	<label>Password</label>
    <input type="text" name="password" /> 
    <input type="submit" />
</form>
<?php
}
else
{
	if(isset($_SESSION['user']))
	{
	
	}
	else
	{
		echo 'You can not log in at the time';
	}
}
include_once "footer.php";
?>