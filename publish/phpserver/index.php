<?php

function showTitle($ts){
    $dom = new DOMDocument('1.0');
    $title = $dom->createElement('title',$ts );
    $dom->appendChild($title);
    echo $dom->saveHTML();
}

function showFrame($fs){
    echo '<iframe src="',$fs,'" width="960" height="640" scrolling="no" frameborder="0" border="0" style="position:absolute;left:0;top:0px;" />';
}

$sp = $_SERVER["QUERY_STRING"];
echo $sp,'<br>';

if ($sp == 'regist_aigis_dmm'){
    require_once('regist.php');
    $ret = regist_dmmjp();
    showTitle($ret[0]);
    showFrame($ret[1]);
}
else {
    showTitle('empty');
}

?>