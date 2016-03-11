/**
 * Created by John on 2015/8/7.
 */

function getGameURL() {
    var aigisFrame = document.getElementById("game_frame");
    var gameURL = aigisFrame.getAttribute("src");
    t_close();
    window.open(gameURL);
}

function main() {
    var sDomain = window.document.domain;
    if (sDomain ==  "www.dmm.co.jp")
    {
        setTimeout("getGameURL()",1000);
    }
}

main();
