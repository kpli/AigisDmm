<?php

require_once('webreq.php');

class Bccto
{
    protected $net,$mailuser,$mailaddr,$mailflag;

    function __construct() {
        $this->net = new Webreq('http://www.bccto.me');
        $this->mailuser = '';
        $this->mailaddr = '';
        $this->mailflag = '';
    }

    function getAddr() {
        return $this->mailaddr;
    }

    function getPswd() {
        return $this->mailuser;
    }

    function apply($addr,$user) {
        $this->net->get('http://www.bccto.me');
        $this->mailaddr = $addr;
        $this->mailuser = $user;
        $data = array('mail' => $this->mailaddr,);
        $ret= $this->net->post('http://www.bccto.me/applymail',$data);
        print $ret.'<br>';
        if($ret == '')
            return false;
        $obj=json_decode($ret);
        if(!$obj->success || $obj->success != 'true'){
            print 'applyMail failed'.'<br>';
            return false;
        }
        return true;
    }

    function wait(){
        $nLoopCounter = 0;
        while( $nLoopCounter < 10){
            sleep(1);
            $nLoopCounter = $nLoopCounter+1;
            $data = array('mail'=>$this->mailaddr, 'time'=> '0', '_'=>'0');
            $ret = $this->net->post('http://www.bccto.me/getmail',$data);
            if ($ret == 'NO NEW MAIL' || $ret == '') {
                print $ret.'<br>';
                continue;
            }
            $obj=json_decode($ret);
            if(!$obj->mail){
                print "waiting mail ... no mail ".'<br>';
                continue;
            }
            if($obj->mail == ''){
                print "waiting mail ... mail empty".'<br>';
                continue;
            }
            $from = $obj->mail[0][1];
            if( $from == 'info@mail.dmm.com'){
                $this->mailflag = $obj->mail[0][4];
                print $this->mailflag.'<br>';
                $nLoopCounter = 999;
                break;
            }
        }
    }

    function view(){
        print "view mail...".'<br>';
        if($this->mailflag == ''){
            print 'mail flag is empty'.'<br>';
            return '';
        }
        $data = array('mail'=>$this->mailflag, 'to'=>$this->mailaddr, '_'=>'0');
        $ret = $this->net->post('http://www.bccto.me/viewmail',$data);
        if ($ret == '') {
            return $ret;
        }
        $obj=json_decode($ret);
        if(!$obj->mail || $obj->mail == ''){
            return '';
        }

        preg_match('/https:.*/', $obj->mail, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];
        return $valid;
    }


}
?>