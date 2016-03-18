<?php

include('../library/Requests.php');
Requests::register_autoloader();

class Webreq
{
    protected $session,$headers;

    function __construct($url) {
        $this->headers = array('Accept-Encoding' => 'gzip, deflate','User-Agent' => 'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:39.0) Gecko/20100101 Firefox/39.0');
        $this->options = array('verify' => false, 'timeout'=> 30);
        $this->session = new Requests_Session($url,$this->headers,array(),$this->options);
    }

    function get($path) {
        try {
            $response= $this->session->get($path);
            //print $response->status_code." ".$response->url.'<br>';
            return $response->body;
        }
        catch (Exception $e) {
            //print $e->getMessage().'|Exception|<br>';
        }
        return '';
    }

    function post($path,$data) {
        try {
            $response= $this->session->post($path,$this->headers,$data);
            //print $response->status_code." ".$response->url.'<br>';
            return $response->body;
        }
        catch (Exception $e) {
            //print $e->getMessage().'|Exception|<br>';
        }
        return '';
    }

    function post_xhr($path,$data,$dmm_token) {
        try {
            $tmp_header = $this->headers;
            $tmp_header['DMM_TOKEN'] = $dmm_token;
            $tmp_header['X-Requested-With'] = 'XMLHttpRequest';
            $response= $this->session->post($path,$tmp_header,$data);
            //print $response->status_code." ".$response->url.'<br>';
            return $response->body;
        }
        catch (Exception $e) {
            //print $e->getMessage().'|Exception|<br>';
        }
        return '';
    }

}

?>