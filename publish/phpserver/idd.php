<?php

class IdoDB
{
	protected $conn;
	function __construct() {
		//print 'init';
		$this->conn = mysqli_connect("mysql1.webcrow-php.netowl.jp","kpli_user","pwd123","kpli_ag");
		if (mysqli_connect_errno($this->conn)) {
			echo "Failed to connect to MySQL: ".mysqli_connect_error();
		}
	}
	
    function add($sid,$pwd) {
		//print 'add';
		$ssql = "INSERT INTO da_accounts (account,passwd,createtime,signdate) VALUES ('".$sid."','".$pwd."',NOW(),CURDATE());";
		mysqli_query($this->conn,$ssql);
		return true;
    }

    function del($sid) {
		//print 'del';
		$ssql = "DELETE FROM da_accounts WHERE account = '".$sid."';";
		mysqli_query($this->conn,$ssql);
		return true;
    }

    function update($sid,$key,$val) {
		//print 'update'.'<br>';
		$ssql = "UPDATE kpli_ag.da_accounts SET ".$key." = '".$val."' WHERE account = '".$sid."';";
		mysqli_query($this->conn,$ssql);
		return true;
    }

    function search($key,$val){
		//print 'search';
		$ssql = "SELECT * FROM da_accounts WHERE ".$key." = '".$val."' order by createtime desc;";
		$rest = mysqli_query($this->conn,$ssql);
		$arr_query = array();
		while($row = mysqli_fetch_assoc($rest))
		{
			array_push($arr_query,
                array($row['createtime'],$row['account'],$row['passwd'],$row['random1'],$row['random2'],$row['random3'],$row['signdate'])
                );
		}
		return $arr_query;
    }

    function query($ssql){
		//print 'getNotBlack';
		$sid = '';
        $pwd = '';
		$rest = mysqli_query($this->conn,$ssql);
		if ($row = mysqli_fetch_assoc($rest))
		{
			$sid = $row['account'];
			$pwd = $row['passwd'];
		}
		return array($sid,$pwd);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    function query_for_quiting(){
        $ssql = "SELECT * FROM da_accounts 
                    WHERE createtime < DATE_SUB( NOW(), INTERVAL 30 MINUTE ) AND  random1 != '4'
                    order by createtime asc;";
        return $this->query($ssql);
    }

    function query_for_second(){
		$ssql = "SELECT * FROM da_accounts 
                    WHERE random1 = '4' AND  random2 = '0' 
                    order by createtime asc;";
        return $this->query($ssql);
    }

    function query_for_signup(){
		$ssql = "SELECT * FROM da_accounts
                    WHERE random1 = '4' and signdate != CURDATE() 
                    order by signdate asc;";
        return $this->query($ssql);
    }

    function refresh_signup_date($sid){
		$ssql = "UPDATE kpli_ag.da_accounts SET  signdate =  CURDATE() WHERE account = '".$sid."';";
		mysqli_query($this->conn,$ssql);
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    function search_0_black(){
        return $this->search('random1','0');
    }

    function search_1_black(){
        return $this->search('random1','4');
    }

    function search_timeout(){
        return $this->search('random2','9');
    }

    function search_2_black(){
        return $this->search('random2','4');
    }

    function search_3_black(){
        return $this->search('random3','4');
    }

}
?>