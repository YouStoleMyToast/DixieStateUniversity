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
		  </script>
<style>
	.errors{color:red}
</style>
</head>
<body>