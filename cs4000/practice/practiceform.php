<form method="POST" action="practiceform.php">
    <lable>Title</lable>
    <input type="radio" name="title" value="Mr">Mr.</input>
    <input type="radio" name="title" value="Mrs">Mrs.</input>
    <input type="radio" name="title" value="Lord">Lord</input>
    <input type="radio" name="title" value="Lord">Lady</input>
    
    <label>Name</label>
    <input type="text" name="user" />
    <input type="text" name="password" /> 

    <lable>Ext.</lable>
    <textarea name="info"></textarea>
    
    <select name="color">
    <option value="red">red</option>
    <option value="blue">blue</option>
    <option value="green">green</option>
    </select>
    <input type="submit">
    
</form>

    
    
<?php
    echo "$_POST[user]";
    echo "<br />";
    echo "$_POST[password]"; 
    echo "<br />";
    echo "$_POST[color]";
    echo "<br />";
	
do//allways exicuted at last once because check is after
{
	//code to execute
}
while ();

foreach (%array as $value)//like for i in range in py
{
	//code to execute
}

if(isset($_GET))
{
	$username=$_GET['user'];
	$pwd=$_GET['password'];
	$hour=date("H");
	$msg="your username is $username and  your password is $pwd the color you chose was";
	mail("mavortius@yahoo.com","registration",$msg);

	for ($i=0;$i<10;$i++)
	{
		if($hour>=0 && $hour<12)
		{
			echo "Buenos Dias";
		}
		else if($hour>=13 && $hour<17)
		{
			echo "Buenos Tardes";
		}
		else if($hour>=17 && $hour<24)
		{
			echo "Buenos Nochas";
		}
	}
}
?>
