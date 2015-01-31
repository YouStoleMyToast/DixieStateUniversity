<?php

echo '<form method="GET" action="callender.php">';

echo'<select name="day">';
for ($i=0;$i<=31;$i++)
{
	echo"<option value=$i>$i</option>";//note: double quotes here is importiant
}
echo '</select>';
echo '<input type="submit">';
echo '</form>';
?>