
<!DOCTYPE html>

<html>
<head>
<script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
<script>
	$(document).ready(function(){
		$('#frmLogin').submit(function(e){//'#frmLogin' can be changed to 'form' for any form "('#submit').click"
			e.preventDefault();//three things
			$(this).serialize(),
			function(response){
				alert(response);
			};
		};
	};
		
</script>
<style>
</style>
</head>
<body>
<form id='frmLogin'>
	<input type='text' name='username' id='username'/>
	<input type='password' name='password' id='password'/>
	<input type='submit' name='submit' id='submit' value='submit'/>
</form>
</body>