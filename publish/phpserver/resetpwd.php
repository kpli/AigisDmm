<?php
require_once('webreq.php');
class Reset_Pwd
{
    protected $net_b,$net_c,$mailaddr,$password,$mailflag;
    function __construct() {
        $this->net_b = new Webreq('http://www.bccto.me');
        $this->net_c = new Webreq('http://www.dmm.co.jp');
        $this->mailaddr = '';
        $this->password = '';
        $this->mailflag = '';
    }

    function needReset($page,$mail){
        $this->mailaddr = $mail;
        preg_match('/passwordreminder/', $page, $matches);
        if( count($matches) == 0){
            return false;
        }
        $this->apply();
        $this->dellAll();
        return true;
    }

    function reset() {
        //print 'into reset progress'.'<br>';
        $this->wait();
        $viewret = $this->view();
        if($viewret == ''){
            return '';
        }
        //print $viewret.'<br>';
        $pageRet = $this->net_c->get($viewret);
        $rid = $this->parseRidValue($pageRet);
        if($rid == ''){
            return '';
        }

        $str = null;
        $strPol = "abcdefghijklmnopqrstuvwxyz0123456789";
        $max = strlen($strPol)-1;
        for($i=0;$i<10;$i++){
            $str.=$strPol[rand(0,$max)];
        }
        $this->password = $str;

        $data = array('password'=>$this->password, 'password_confirm'=>$this->password, 'rid'=>$rid);

        //print $this->mailaddr.'<br>';
        //print $this->password.'<br>';
        //print $rid.'<br>';
        //print $data.'<br>';

        require_once('dbop.php');
        $dbop = new DBOP();
        $dbop->setPass($this->mailaddr,$this->password);

        $this->net_c->post('https://www.dmm.co.jp/my/-/passwordreminder/complete/',$data);
        
        return $this->password;
    }

    function dellAll() {
        $nLoopCounter = 0;
        sleep(1);
        while( $nLoopCounter < 3){
            $nLoopCounter = $nLoopCounter+1;
            $data = array('mail'=>$this->mailaddr, 'time'=> '0', '_'=>'0');
            $ret = $this->net_b->post('http://www.bccto.me/getmail',$data);
            if ($ret == 'NO NEW MAIL' || $ret == '') {
                //print $ret.'<br>';
                sleep(1);
                continue;
            }
            $obj=json_decode($ret);
            if(!$obj->mail){
                //print "waiting mail ... no mail ".'<br>';
                sleep(1);
                continue;
            }
            if($obj->mail == ''){
                //print "waiting mail ... mail empty".'<br>';
                sleep(1);
                continue;
            }
            $mailflag = $obj->mail[0][4];
            //print $mailflag.'<br>';
            $this->delOne($mailflag);
            $nLoopCounter = 1;
        }
    }

    function delOne($flag) {
        if($flag == ''){
            //print 'mail flag is empty'.'<br>';
            return '';
        }
        $data = array('delMail'=>$flag, '_'=>'0');
        $ret = $this->net_b->post('http://www.bccto.me/delmail',$data);
        if ($ret == '') {
            return $ret;
        }
        $obj=json_decode($ret);
        return $obj;
    }

    function apply() {
        $this->net_b->get('http://www.bccto.me');
        $data = array('mail' => $this->mailaddr,);
        $ret= $this->net_b->post('http://www.bccto.me/applymail',$data);
        //print $ret.'<br>';
        if($ret == '')
            return false;
        $obj=json_decode($ret);
        if(!$obj->success || $obj->success != 'true'){
            //print 'applyMail failed'.'<br>';
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
            $ret = $this->net_b->post('http://www.bccto.me/getmail',$data);
            if ($ret == 'NO NEW MAIL' || $ret == '') {
                //print $ret.'<br>';
                continue;
            }
            $obj=json_decode($ret);
            if(!$obj->mail){
                //print "waiting mail ... no mail ".'<br>';
                continue;
            }
            if($obj->mail == ''){
                //print "waiting mail ... mail empty".'<br>';
                continue;
            }
            $from = $obj->mail[0][1];
            if( $from == 'info@mail.dmm.com'){
                $this->mailflag = $obj->mail[0][4];
                //print $this->mailflag.'<br>';
                $nLoopCounter = 999;
                break;
            }
        }
    }

    function view(){
        //print "view mail...".'<br>';
        if($this->mailflag == ''){
            //print 'mail flag is empty'.'<br>';
            return '';
        }
        $data = array('mail'=>$this->mailflag, 'to'=>$this->mailaddr, '_'=>'0');
        $ret = $this->net_b->post('http://www.bccto.me/viewmail',$data);
        if ($ret == '') {
            return $ret;
        }
        $obj=json_decode($ret);
        if(!$obj->mail || $obj->mail == ''){
            return '';
        }

        preg_match('/https:.*rid=.*/', $obj->mail, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];
        return $valid;
    }


    function parseRidValue($content){
        preg_match( '/input type="hidden" name="rid" value=".*"/', $content, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];

        preg_match('/value=".*"/', $valid, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];

        return $this->parseTrim($valid);
    }

    function parseTrim($content){
        preg_match('/".*"/', $content, $matches);
        if( count($matches) == 0){
            return '';
        }
        $valid = $matches[0];
        $valid = trim($valid,"\"");
        return $valid;
    }
}
?>