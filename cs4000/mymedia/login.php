<?php
include_once "headerloginpage.php";

$_SESSION['logged_in'] = False;
echo '<h1>Login</h1>';

if(isset($_POST['username']) && isset($_POST['password']))// && $_GET['action'],$login)
{
    $username='temp';
    $password='temp';
    $query="select * from `users` where `password`='$password' and `username`='$username'";
    $connect = mysqli_connect("mysql.cs.dixie.edu", "ebeilmann", "kireth2002", "ebeilmann") or die("can't connect");
    $result = mysqli_query($connect, $query) or die("can't do query" . $query . mysqli_error($connect));
    $idquery="select user_id from `users` where `password`='".$_SESSION['password']."' and `username`='".$_SESSION['username'];
    echo $idquery;
    $user_id = mysqli_query($connect, $query) or die("can't do query" . $query . mysqli_error($connect));
    $_SESSION['user_id']=$user_id;

    $rows=mysqli_num_rows($result);
    if($rows==1)
    {
        echo "You are logged in as ".$username.".<br>";
        setcookie('login',$username,time()+100);
        $_SESSION['username'] = $username;
        $_SESSION['password'] = $password;
        $_SESSION['user_id'] = $user_id;
        $_SESSION['logged_in'] = True;
        header('Location: http://www.ebeilmann.php.cs.dixie.edu/CS%204000/mymedia/mediahome.php');
        die();
    }
    else
    {
         echo "Wrong username or password";
    }

}

echo "<form action='".$_SERVER['PHP_SELF']."' method='POST'>";
    echo "<label>Name</label>";
    echo "<input type='text' name='username' />";
	
    echo "<p><label>Password</label>";
    echo "<input type='text' name='password' /></p>";
	
    echo "<input type='submit' name='loginsubmit' value='Login'/>";
    echo "<p>or register with above name and password</p>";
    echo "<p><input type='submit' name='registersubmit' value='Register'/></p>";
echo "</form>";


include_once "footerloginpage.php";
?>