<?php
function query($query) {
    $connect = mysqli_connect("mysql.cs.dixie.edu", "jfrancom", "francom1", "jfrancom") or die("can't connect");

    $result = mysqli_query($connect, $query) or die("can't do query" . $query . mysqli_error($connect));
    if (!mysqli_affected_rows($connect) > 0) {
        echo "fail";
    }
    //var_dump($result);
    return $result;
}


function getBrandDropdown($brand=Null) {
    $query = "SELECT * FROM brand";
    $result = query($query);

    echo "<select name='eqt_brand' id='eqt_brand'>";
    while ($row = mysqli_fetch_assoc($result)) {
        //var_dump($row);
        $selected = ($brand==$row[brand_id])?'selected=selected':'';
        echo "<option $selected value='$row[brand_id]'>$row[brand_name]</option>";
    }
    echo "</select>";
}
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
?>