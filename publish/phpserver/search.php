<?php
$sp = $_SERVER["QUERY_STRING"];
$r1 = strstr($sp,"&",true);
$tmp = strstr($sp,"&");
$r2 = substr($tmp,1);
require_once('dbop.php');
$dbop = new DBOP();
$ret = $dbop->getFor($r1,$r2);
foreach($ret as $key=>$value){
	echo $key."__".$value."<br>";
}
?>
