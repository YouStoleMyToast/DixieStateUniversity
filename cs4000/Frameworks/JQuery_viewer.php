<?php
include_once 'equipmentfunctions.php';
?>
<html>
    <head>
        <script src="//ajax.googleapis.com/ajax/libs/jquery/1.9.1/jquery.min.js"></script>
        <script>
            $(document).ready(function()
            {
                //$('form').submit(function(e)
                $('#eqt_brand').change(function()
                {
                    //e.preventDefault();
                    $.post('JQuery_viewer_1.php',
                    $(this).serialize(),
                    function(response)
                    {
                        //alert(response);
                        $('#results').html(response);
                    });
                });
            });

        </script>
    </head>
<Body>
	<form>
<?//note: <?= is a shorthand for echo results of...
    getBrandDropdown();
?>
	</form>
	<div id="results">
	</div>
</body>
</html>