<?php
$sp = $_SERVER["QUERY_STRING"];
require_once('dbop.php');
$dbop = new DBOP();
$ret = $dbop->getForAll($sp);
foreach($ret as $key=>$value){
	echo $key."=>".$value."<br>";
}
?>
