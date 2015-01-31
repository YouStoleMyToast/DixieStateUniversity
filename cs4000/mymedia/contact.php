<?php
include_once "header.php";
?>

<h1>Contact Information</h1>

<h2>E-mail</h2>
<p>This is my e-mail address</p>

<h2>Phone</h2> 
<p>This is my phone number</p>

<h2>Snail Mail/stalking</h2>
<p>This is my address</p>



<div id="map3d" style="height: 400px; width: 600px;"></div>



<?php
function init() 
{
	google.earth.createInstance('map3d', initCB, failureCB);
}

function initCB(instance)
{
	ge = instance;
	ge.getWindow().setVisibility(true);
}

function failureCB(errorCode) 
{
}

include_once "footer.php";
?>
