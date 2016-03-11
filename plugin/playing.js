/**
 * Created by John on 2015/8/7.
 */


function setTabTitle()
{
    chrome.storage.local.get("nutakuMailString", function(valueArray) {
        mailAll = valueArray["nutakuMailString"];
        document.title = mailAll;
    });
}

function main() {
    var sDomain = window.document.domain;
    if (sDomain ==  "osapi.dmm.com")
    {
        setTimeout("setTabTitle()",1000);
    }

}

main();
