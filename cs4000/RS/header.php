<?php
session_start();
?>

<!DOCTYPE html>

<html>
<head>
<title>Oak Island Pirates</title>
<link rel="stylesheet" type="text/css" href="style.css" />


<script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
<script>
$(document).ready(function (){
	$('#loginerror').submit(function(e){
		e.preventDefault();
		$.post('login.php',
		$(this).serialize(),
		function(response){
			//alert(response);
			$('#results').html(response);
		});
	});
});
$(document).ready(function (){
	$('#skillerror').submit(function(e){
		e.preventDefault();
		$.post('contest.php',
		$(this).serialize(),
		function(response){
			//alert(response);
			$('#results').html(response);
		});
	});
});
$(document).ready(function (){
	$('#nonameerror').submit(function(e){
		e.preventDefault();
		$.post('contest.php',
		$(this).serialize(),
		function(response){
			//alert(response);
			$('#results').html(response);
		});
	});
});
$(document).ready(function (){
	$('#caperror').submit(function(e){
		e.preventDefault();
		$.post('contest.php',
		$(this).serialize(),
		function(response){
			//alert(response);
			$('#results').html(response);
		});
	});
});
</script>


</head>

<div id="linkbar">
<ul>
<li><a href="http://www.ebeilmann.php.cs.dixie.edu/CS 4000/RS/home.php">Home</a></li>
<li><a href="http://www.ebeilmann.php.cs.dixie.edu/CS 4000/RS/about.php">About</a></li>
<li><a href="http://www.ebeilmann.php.cs.dixie.edu/CS 4000/RS/contest.php">Contests</a></li>
<li><a href="http://www.ebeilmann.php.cs.dixie.edu/CS 4000/RS/achievements.php">Achievements</a></li>
<li><a href="http://forum.oakislandpirates.com/forum/64154/">Forum</a></li>
</ul>
</div>

<div id=main>
<body>
<?php
include_once "login.php";
?>