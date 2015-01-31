<html>
    <head>
        <script src="//ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js"></script>
        <script >
            $(document).ready(function (){
                //$("form").submit(function (e){
                //    e.preventDefault();
                $('#color').change(function(){
                    var color = $('#color').val();
                    $('body').attr('style', "background-color:"+color);
                });
				
				$('#number').change(function(){
                    var number = $('#number').val();
                    //alert(number);
					//$('output').html(number);
                });
            });
        </script>
    </head>
    <body>
        <form id="myForm">
            <select name="color" id="color">
                <option value="Red">
                    Red
                </option>
                <option value="Blue">
                    Blue
                </option>
                <option value="Yellow">
                    Yellow
                </option>
            </select>
		</form>
		<form id="myForm">
            <select name="number" id="number">
				<?php
				for ($i=1;$i<=6;$i++)
				{
					echo "<option value='$i'>$i</option>";
				}
				?>
            </select>
            <input type="submit" value="submit" name="color_button"/>
			<div id="output"></div>
			<p>This is my text</p>
        </form>
    </body>
</html>
