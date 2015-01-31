<?php

?>
<html>
<head>
	<script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
	<script>
		$(document).ready(function()
		{
			$('form').submit(function(e)
			{
				e.preventDefault();
				$.post('JQuerypro.php',
				$(this).serialize(),
				function(response)
				{
					//alert(response);
					$('#errors').html(response)
				});
			});
		});
	
	</script>
	<style>
	
		.errors{color:red}
	</style>
</head>
<body>

	<form>
	<input type="text" name="firstname"/>
	<input type="text" name="lastname"/>
	<input type="text" name="phone"/>
	<select name="gender"/>
		<option value='M'>M</option>
		<option value='F'>F</option>
	</select>
	<input type="text" name="url"/>
	<input type="submit" name="click" value="click"/>
	</form>
	<div id="errors" class="errors">
	</div>
</body>
</html>