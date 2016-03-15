<?php

require_once('bccto.php');
require_once('dmmjp.php');

class Logic
{
    protected $gameurl,$mailuser,$mailaddr;
    function __construct() {
        $this->gameurl = '';
        $this->mailuser = '';
        $this->mailaddr = '';
    }

    function getMail() {
        return $this->mailaddr;
    }

    function getGame() {
        return $this->gameurl;
    }

    function getName() {
        return $this->mailuser;
    }

    function randName() {
        $str = null;
        $strPol = "abcdefghijklmnopqrstuvwxyz0123456789";
        $max = strlen($strPol)-1;
        for($i=0;$i<8;$i++){
            $str.=$strPol[rand(0,$max)];
        }
        return $str;
    }

    function autoRun(){
        
        $this->mailuser = $this->randName();
        $this->mailaddr = $this->mailuser.'@bccto.me';

        $bccto = new Bccto();
        $rest = $bccto->apply($this->mailaddr,$this->mailuser);
        print $rest.'<br>';
        if($rest == ''){
            return ;
        }

        $dmmjp = new Dmmjp();
        $dmmjp->retist($this->mailaddr,$this->mailuser);
        
        $bccto->wait();
        $validurl = $bccto->view();
        if($validurl == ''){
            return ;
        }

        $page1 = $dmmjp->valid($validurl);
        if($page1 == ''){
            return ;
        }

        $page2 = $dmmjp->confirm($page1);
        if($page2 == ''){
            return ;
        }

        $page3 = $dmmjp->commit($page2);
        if($page3 == ''){
            return ;
        }

        $this->gameurl = $dmmjp->play($page3);

        return;
    }

}
?>