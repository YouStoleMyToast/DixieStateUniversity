
<?php
$key='4fj73mhn4gm92vff53wnsygr';
$title="Tron";
$link = "http://api.rottentomatoes.com/api/public/v1.0/movies.json?q=".$title."&page_limit=20&apikey=".$key;

$file = file_get_contents($link);
$jsonDecode = json_decode($file,True);
$movie_array = $jsonDecode['movies'][0];


$tomato_id=$movie_array['id'];
$movie_title=$movie_array['title'];
$year=$movie_array['year'];
$genre=$movie_array['genres'];
$poster = $movie_array['posters']['thumbnail'];
$rating = $movie_array['mpaa_rating'];
$synopsis = $movie_array['synopsis'];
$link=str_replace(" ","_","http://www.rottentomatoes.com/m/$title/");

print_r($jsonDecode);

echo "<img src=$poster alt=$poster />";
echo $title;
echo $year;
echo $genre;
echo $link

//echo $rating;
//echo $synopsis;

?>

