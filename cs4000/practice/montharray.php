<?php

$month=array('Jan', 'Feb', 'Mar','Apr','May','Jun','Jul','Aug','Sep','Oct','Nov','Dec');

echo '<form method=GET action=arrayMonths.php>';
echo '<lable>Which Month</lable>';
echo '<select name=month>';

foreach ($month as $m)
{
	echo "<option value=$m>$m</option>";
}
echo '</select>';
echo '</form>';
?>
<?php

$a[0]='hi';
$a[1]='bye';

echo $a[0];

$a['name']='Eric'

print_r($a);

?>
<?php

$ary=explode("","this is a string");


?>