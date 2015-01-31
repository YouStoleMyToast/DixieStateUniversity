<?php
session_start();

if ($_SESSION['logged_in'] ==False)
{
    header('Location: http://www.ebeilmann.php.cs.dixie.edu/CS%204000/mymedia/login.php');
}
?>

<!DOCTYPE html>

<html>
<head>
<title>My Media</title>
<link rel="stylesheet" type="text/css" href="mediastyle.css" />
    <script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
    <script>
		jQuery(function($){
			$('.deleteLink').click(function(event){
				event.preventDefault();
				var href = $(this).attr('href');
				var parent = $(this).parent().parent();
				$.get(href);
				parent.remove();
			});
		});

		jQuery(function($){
			$('.editLink').click(function(event){
				event.preventDefault();
				var href = $(this).attr('href');
				var parent = $(this).parent().parent();
				$.get(href);
				parent.load();
			});
		});
		
		/*
		jQuery(function($){
			$('.deleteLink').click(function(event){
				event.preventDefault();
				var href = $(this).attr('href');
				var parent = $(this).parent().parent();
				$.get(href);
				parent.remove();
			});
		});
		*/
    </script>
<style>
	.errors{color:red}
</style>
</head>

<div id="linkbar">
<ul>
<li><a href="http://www.ebeilmann.php.cs.dixie.edu/CS 4000/mymedia/mediahome.php">Home</a></li>
<li><a href="http://www.ebeilmann.php.cs.dixie.edu/CS 4000/mymedia/addmedia.php">Media</a></li>
<li><a href="http://www.ebeilmann.php.cs.dixie.edu/CS 4000/mymedia/about.php">About</a></li>
<li><a href="http://www.ebeilmann.php.cs.dixie.edu/CS 4000/mymedia/contact.php">Contact</a></li>
<?php
echo"<li><a href='http://www.ebeilmann.php.cs.dixie.edu/CS 4000/mymedia/login.php?action=destroysession'>Logout</a></li>";
if(isset($_GET['action']))
{
	switch($_GET['action'])
	{	
		case "destroysession":
			session_destroy();
	}
}
include_once 'mediafunctions.php';
?>
</ul>
</div>

<div id="main">
<body>