<?php

include_once 'equipmentfunctions.php';
//print_r($_POST);
$brand = $_POST['eqt_brand'];

$query = "SELECT * FROM equipment WHERE brand=$brand";
$results = query($query);

if (mysqli_num_rows($results) > 0) {
    $html = '<table border=1>';
    while ($row = mysqli_fetch_assoc($results)) {
        $html.= "<tr><td>$row[name]</td><td>$row[quantity]</td></tr>";
    }

    $html.='</table>';
    echo $html;
} else {
    echo "<h1>No results found in the database.</h1>";
}
?>