<?php
include_once "header.php";

echo "<h1>Items</h1>";
echo "<form method='post'>";
	echo "<input type='text' name='item'><br>";
	echo "<p><input type='submit' name='itemsearch' value='Search'></p>";
echo "</form>";

if(isset($_REQUEST['itemsearch']))
{
	$item=$_REQUEST['item'];
	$link = "http://rsapi.net/ge/search/".$item."/jsonp/parse_search.json";
	$file=file_get_contents($link);
	echo $file;
	$newstr="";
	$itemarr=array();

	
	
	
	for($i = 0; $i <count($file) ; $i++)
	{

		$newstr=$newstr.$file[$i];
		$newarr=explode("},{",$file);
	}
	for($j = 0; $j <count($newarr) ; $j++)
	{
		$idloc=strpos($newarr[$j],"id");
		$endloc=strpos($newarr[$j],"}");
		
		if($idloc!=1)
		{
			$newarr[$j]=substr($newarr[$j],$idloc-1);
		}
		if($endloc)
		{
			$newarr[$j]=substr($newarr[$j],0,$endloc);
		}
		$itemdata=explode(",",$newarr[$j]);
		array_push($itemarr, $itemdata);
	}
	
	
	
	$itemnamearr=array();
	for($k = 0; $k <count($itemarr); $k++)
	{
		for($q = 0; $q <count($itemarr[$k]) ; $q++)
		{
			if($q%3==1)
				array_push($itemnamearr, $itemarr[$k][$q]);
		}
	}
	
	for($m = 0; $m <count($itemnamearr); $m++)
	{
		$lastquoteloc=strrpos($itemnamearr[$m],'"');
		$itemnamearr[$m]=substr($itemnamearr[$m],0,$lastquoteloc);
		
		$firstquoteloc=strrpos($itemnamearr[$m],'"');
		$itemnamearr[$m]=substr($itemnamearr[$m],$firstquoteloc+1);
	}
	
	asort($itemnamearr);
	itemdropdown($itemnamearr);
}









if(isset($_REQUEST['itemtable']))
{

	$items=$_REQUEST['itemtable'];
	echo $items;
	echo "<p>";
	$links = "http://rsapi.net/ge/search/".$items."/jsonp/parse_search.json";
	$files=file_get_contents($links);
	echo $files;
	$newstrs="";
	$itemarrs=array();

}







function itemdropdown($itemnamearr)
{
	echo "<table border='1'>";
	echo "<tr>";
		echo "<td>";
		echo "<h2>Item</h2>";
		echo "<form method='post'>";
			echo "<label for='item'>Item</lable>";
			echo "<select name='item'>";
	
	for($p = 0; $p <count($itemnamearr); $p++)
	{
		echo '<option value="'.$p.'">'.$itemnamearr[$p].'</option>';
	}
			echo "</select>";
			echo "<p><input type='submit' name='itemtable' value='Get Item Data'/></p>";
		echo "</form>";
		echo "</td>";
	echo "</tr>";
	echo "</table>";
}
	
function createdataset($item)
{
	$link = "http://rsapi.net/ge/search/".$item."/jsonp/parse_search.json";
	$file=file_get_contents($link);
	$newstr="";
	$itemarr=array();

	for($i = 0; $i <count($file) ; $i++)
	{

		$newstr=$newstr.$file[$i];
		$newarr=explode("},{",$file);
	}
	for($j = 0; $j <count($newarr) ; $j++)
	{
		$idloc=strpos($newarr[$j],"id");
		$endloc=strpos($newarr[$j],"}");
		
		if($idloc!=1)
		{
			$newarr[$j]=substr($newarr[$j],$idloc-1);
		}
		if($endloc)
		{
			$newarr[$j]=substr($newarr[$j],0,$endloc);
		}
		$itemdata=explode(",",$newarr[$j]);
		array_push($itemarr, $itemdata);
	}
	return $itemarr;
	
}
?>

<?php
include_once "footer.php";
?>