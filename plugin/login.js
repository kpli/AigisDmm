/**
 * Created by John on 2015/8/7.
 */


function loginAuto() {
	chrome.storage.local.set({"nutakuMailString": mailstri}, function(){});
    chrome.storage.local.get("nutakuMailString", function(valueArray) {

        var mailAll = valueArray["nutakuMailString"];
        var mailUser = mailAll.substr(0,8);

        document.getElementById("login_id").value=mailAll;
        document.getElementById("password").value=mailUser;

        var form1 = document.getElementsByClassName("validator login");
        form1[0].submit();
    });
}

function main() {
    var sDomain = window.document.domain;
	
    if (sDomain ==  "www.dmm.co.jp")
    {
        var sURL = window.document.documentURI;
        setTimeout("loginAuto()",1000);
    }
}

main();
