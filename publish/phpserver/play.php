<?php

$title = $_COOKIE["aigis_title"];
$frame = $_COOKIE["aigis_frame"];

function showTitle($ts){
    $dom = new DOMDocument('1.0');
    $title = $dom->createElement('title',$ts );
    $dom->appendChild($title);
    echo $dom->saveHTML();
}

function showFrame($fs){
    echo '<iframe src="',$fs,'" width="960" height="640" scrolling="no" frameborder="0" border="0" style="position:absolute;left:0;top:0px;" />';
}

showTitle($title);
showFrame($frame);

?>