<?php
$account = '';
$random1 = '';
$sp = $_SERVER["QUERY_STRING"];
$account = strstr($sp,"=",true);
$tempRand = strstr($sp,"=");
$password = substr($tempRand,1);
require_once('dbop.php');
$dbop = new DBOP();
$dbop->setPass($account,$password);
showTitle('ok');
function showTitle($ts){
    $dom = new DOMDocument('1.0');
    $title = $dom->createElement('title',$ts );
    $dom->appendChild($title);
    echo $dom->saveHTML();
}
?>
