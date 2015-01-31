<?php
//note sites: http://jqueryui.com, http://mootools.net/, api.jquery.com

//note other effects:
//fadeout (example given with fadeout of error messages after a few miliseconds)

//Homework: probably doing some jquery changes to edit, delete, add (assignments 6 and 7) with jquery
?>
<html>
    <head>
        <script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
        <script>
            $(document).ready(function (){
                $('form').submit(function(e){
                    e.preventDefault();
                    $.post('jquery_processor_1.php',
                    $(this).serialize(), 
                    function(response){
                        //alert(response);
                        $('#errors').html(response).fadeOut(1500);
                    });
                });
                
                $('#form').keydown(function(e){
                    if (e.keyCode === 13) { // If Enter key pressed
                        $(this).trigger('submit');
                    }
                });
				
				$('form').children().each(function)
				{
					if (e.keycode==13)
					{
						$(this).trigger('submit');
					};
				};
            });
        </script>
        <style>

            .errors {color: red;}
        </style>

    </head>
    <body>
        <form>
            <input type="text" name="firstName"/>
            <input type="text" name="lastName"/>
            <input type="text" name="phone"/>
            <select name="gender">
                <option value="M">M</option>
                <option value="F">F</option>
            </select>
            <input type="text" name="url"/>
            <input type="submit" name="click" value="click"/>
        </form>
        <div id="errors" class="errors">

        </div>
    </body>
</html>
