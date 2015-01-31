<?php
function authenticate($u, $p)

if(!empty($_POST))

	{
		if(($u=='Eric')&&($p=='password'))
		{
		if (authenticate($uname,$pwd)==True)
		{
			header("location: http://www.google.com");//could direct you to any site
			echo "You are logged in as $u< /br>"
		}
		else:
		{
			$_SESSION['invalid_attempts']+=1;
			$times_left=5-$_SESSION['invalid_attempts'];
			echo "you have tried to log in"
			.$_SESSION['invalid attempts']
			. 'times, you have $times_left attempts';
			{
				setcookie('login', $username, time()+300;
			}
		}
	}
    echo "$_POST[user]";
    echo "<br />";
    echo "$_POST[password]"; 
	
	authenticate($user,$password);
?>