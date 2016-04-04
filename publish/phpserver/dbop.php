<?php

class DBOP
{
	protected $conn;
	function __construct() {
		//print 'init';
		$this->conn = mysqli_connect("mysql1.webcrow-php.netowl.jp","kpli_user","pwd123","kpli_ag");
		if (mysqli_connect_errno($this->conn)) {
			echo "Failed to connect to MySQL: " . mysqli_connect_error();
		}
	}
	
    function addnew($user,$pswd) {
		//print 'addnew';
		$ssql = "INSERT INTO da_accounts (account,passwd,createtime) VALUES ('".$user."','".$pswd."',NOW())";
		mysqli_query($this->conn,$ssql);
		return true;
    }
		
    function getNotBlack() {
		//print 'getNotBlack';
		$account = '';
		$passwd = '';
		$ssql = "SELECT * FROM da_accounts WHERE createtime < DATE_SUB( NOW(), INTERVAL 30 MINUTE ) AND  random1 != 4;";
		$allrest = mysqli_query($this->conn,$ssql);
		if ($row = mysqli_fetch_assoc($allrest))
		{
			$account = $row['account'];
			$passwd = $row['passwd'];
		}
		$allrest->close();
		return array($account,$passwd);
    }
	
    function delNotBlack($user) {
		//print 'delNotBlack';
		$ssql = "DELETE FROM da_accounts WHERE account = '".$user."';";
		mysqli_query($this->conn,$ssql);
		return true;
    }
	
    function getForSecond() {
		//print 'getForSecond';
		$account = '';
		$passwd = '';
		$ssql = "SELECT * FROM da_accounts WHERE random1 = 4 AND  random2 = 0;";
		$allrest = mysqli_query($this->conn,$ssql);
		if ($row = mysqli_fetch_assoc($allrest))
		{
			$account = $row['account'];
			$passwd = $row['passwd'];
		}
		$allrest->close();
		return array($account,$passwd);
    }
	
    function setSecond($user,$color) {
		//print 'setSecond';
		$ssql = "UPDATE  `kpli_ag`.`da_accounts` SET  `random2` =  '".$color."'  WHERE account = '".$user."';";
		mysqli_query($this->conn,$ssql);
		return true;
    }
	
    function setFirst($user,$color) {
		//print 'setFirst';
		$ssql = "UPDATE  `kpli_ag`.`da_accounts` SET  `random1` =  '".$color."'  WHERE account = '".$user."';";
		mysqli_query($this->conn,$ssql);
		return true;
    }
	
    function setPass($user,$pswd) {
		//print 'setFirst';
		$ssql = "UPDATE  `kpli_ag`.`da_accounts` SET  `passwd` =  '".$pswd."'  WHERE account = '".$user."';";
		mysqli_query($this->conn,$ssql);
		return true;
    }
	
    function getFor($r1,$r2) {
		//print 'getForAll';
		$ssql = "SELECT * FROM da_accounts WHERE random1 = '".$r1."' AND random2 = '".$r2."';";
		$allrest = mysqli_query($this->conn,$ssql);
		$arrret = array();
		while($row = mysqli_fetch_assoc($allrest))
		{
			array_push($arrret,$row['account']."__".$row['passwd']."__".$row['random1']."__".$row['random2']."__".$row['createtime']);
		}
		$allrest->close();
		return $arrret;
    }
	
    function getForAll($r2) {
		//print 'getForAll';
		$ssql = "SELECT * FROM da_accounts WHERE random2 = '".$r2."';";
		$allrest = mysqli_query($this->conn,$ssql);
		$arrret = array();
		while($row = mysqli_fetch_assoc($allrest))
		{
			array_push($arrret,$row['account']."__".$row['passwd']."__".$row['random1']."__".$row['random2']."__".$row['createtime']);
		}
		$allrest->close();
		return $arrret;
    }
}
?>