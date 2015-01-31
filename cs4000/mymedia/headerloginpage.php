<?php
session_start();
?>

<!DOCTYPE html>

<html>
<head>
<title>My Media</title>
<link rel="stylesheet" type="text/css" href="mediastyle.css" />
</head>

<div id="linkbar">
<ul>
<li><a href="http://www.ebeilmann.php.cs.dixie.edu/CS 4000/mymedia/mediahome.php">Home</a></li>
<li><a href="http://www.ebeilmann.php.cs.dixie.edu/CS 4000/mymedia/addmedia.php">Media</a></li>
<li><a href="http://www.ebeilmann.php.cs.dixie.edu/CS 4000/mymedia/about.php">About</a></li>
<li><a href="http://www.ebeilmann.php.cs.dixie.edu/CS 4000/mymedia/contact.php">Contact</a></li>
<li><a href="http://www.ebeilmann.php.cs.dixie.edu/CS 4000/mymedia/login.php">Login</a></li>

<?php
include_once 'mediafunctions.php';
?>
</ul>
</div>

<div id="main">
<body>