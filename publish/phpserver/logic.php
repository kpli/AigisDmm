<?php

require_once('bccto.php');
require_once('dmmjp.php');
require_once('dmmjp_l.php');
require_once('dmmjp_c.php');
require_once('idd.php');

class Logic
{
    protected $gameurl,$mailuser,$mailaddr,$db;
    function __construct() {
        $this->gameurl = '';
        $this->mailuser = '';
        $this->mailaddr = '';
        $this->db = new IdoDB();
    }

    function playSecond() {
        $retquery = $this->db->query_for_second();
        if($retquery[0] == '' || $retquery[1] == ''){
            return array('empty','err.html');
        }
        return $this->login($retquery[0],$retquery[1]);
    }

    function playSignup() {
        $retquery = $this->db->query_for_signup();
        if($retquery[0] == '' || $retquery[1] == ''){
            return array('empty','err.html');
        }
        return $this->login($retquery[0],$retquery[1]);
    }

    function randName() {
        $str = null;
        $strPol = "abcdefghijklmnopqrstuvwxyz0123456789";
        $max = strlen($strPol)-1;
        for($i=0;$i<9;$i++){
            $str.=$strPol[rand(0,$max)];
        }
        return $str;
    }

    function login($mail,$paws){
        $obj_dmm = new Dmmjp_Login();
        $game_url = $obj_dmm->login($mail,$paws);
        if($game_url == ''){
            return array('empty','err.html');
        }
        return array($mail,$game_url);
    }

    function login_only($mail,$paws){
        $obj_dmm = new Dmmjp_Login();
        $game_url = $obj_dmm->login_only($mail,$paws);
        if($game_url == ''){
            return array('empty','err.html');
        }
        return array($mail,$game_url);
    
    }

    function cancel($mail,$paws,$bauto){
        if($bauto){
            $rest = $this->db->query_for_quiting();
            $mail = $rest[0];
            $paws = $rest[1];
        }
        if($mail == '' || $paws == ''){
            return array('noid','err.html');
        }
        $qt = new Dmmjp_Cancel();
        $ret = $qt->cancel($mail,$paws);
        if($ret == ''){
            return array('failed','err.html');
        }
        $this->db->del($mail);
        return array('quited','err.html');
    }


    function autoRun(){

        $ret = array('empty','err.html');

        $this->mailuser = $this->randName();
        $this->mailaddr = $this->mailuser.'@bccto.me';

        $bccto = new Bccto();
        $rest = $bccto->apply($this->mailaddr,$this->mailuser);
        //print $rest.'<br>';
        if( !$rest ){
            return $ret;
        }

        $dmmjp = new Dmmjp();
        $dmmjp->retist($this->mailaddr,$this->mailuser);
        
        $bccto->wait();
        $validurl = $bccto->view();
        if($validurl == ''){
            return $ret;
        }

        $page1 = $dmmjp->valid($validurl);
        if($page1 == ''){
            return $ret;
        }

        $page2 = $dmmjp->confirm($page1);
        if($page2 == ''){
            return $ret;
        }

        $page3 = $dmmjp->commit($page2);
        if($page3 == ''){
            return $ret;
        }

        $this->gameurl = $dmmjp->play($page3);

        if (gameurl != ''){
            $rest = $this->db->add($this->mailaddr,$this->mailuser);
            $ret = array($this->mailaddr, $this->gameurl);
        }

        return $ret;
    }

}
?>