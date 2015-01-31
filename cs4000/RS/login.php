<?php
include_once "functions.php";

if(isset($_SESSION['username']) && isset($_SESSION['admin']))
{
	echo "<div id='logout'>";
	echo "<form method='post'>";
	echo "<table>";
	echo "<tr>";
	echo "<td><h4>User: ".$_SESSION['username']."</h4></td>";	
	echo "</tr>";
	echo "<tr>";
	echo "<td><input type='submit' name='logout' value='logout'></td>";
	echo "</tr>";
	echo "</table>";
	echo "</form>";
	echo "</div>";
}
if(isset($_POST['logout']))
{
	session_destroy();
	header("Location: ".$_SERVER['PHP_SELF']."");  
}
if(!isset($_SESSION['username']) && !isset($_SESSION['admin']))
{
	if(isset($_POST['user']) && isset($_POST['pass']))
	{
		$username=$_POST['user'];
		$password=$_POST['pass'];
		$userquery="select user_id from users where password='".$password."' and username='".$username."'";
		$userresult = queryfunction($userquery);
		$idarray = array();
		while ($row=mysqli_fetch_array($userresult))
		{
			$idarray[]=$row[0];
		}
		$id=$idarray[0];
		$adminquery="select role_id from user_roles where user_id='".$id."'";
		$adminresult = queryfunction($adminquery);
		$adminarray = array();
		while ($rows=mysqli_fetch_array($adminresult))
		{
			$adminarray[]=$rows[0];
		}
		$admin=$adminarray[0];
		if(count($idarray)==1)
		{
			$_SESSION['username']=$username;
			$_SESSION['admin']=$admin;
			header("Location: ".$_SERVER['PHP_SELF']."");  
			die();
		}
		else
		{
			echo "<div id='loginerror'>";
			echo "Wrong username or password";
			echo "</div>";
		}
	}
	echo "<div id='login'>";
	echo "<form method='post'>";
	echo "<table>";
	echo "<tr>";
	echo "<td><label for='user' >Username </label></td>";
	echo "<td><input type='text' name='user'></td>";
	echo "</tr>";
	echo "<tr>";
	echo "<td><label for='pass'>Password </label></td>";
	echo "<td><input type='password' name='pass'></td>";
	echo "</tr>";
	echo "<tr>";
	echo "<td colspan=2><input type='submit' name='login' value='login'></td>";
	echo "</tr>";
	echo "</table>";
	echo "</form>";
	echo "</div>";
}
?>