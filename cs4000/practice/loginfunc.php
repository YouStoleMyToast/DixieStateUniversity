
<?php
function authenticate($u, $p)
{
	if(($u=='Eric')&&($p=='password'))
	{
		header("location: http://www.google.com");//could direct you to any site
		echo "You are logged in as $u< /br>"
	}
	else:
	{
		echo "You are logged in as $u< /br>";
	}
}
    echo "$_POST[user]";
    echo "<br />";
    echo "$_POST[password]"; 
	
	authenticate($user,$password);
?>
