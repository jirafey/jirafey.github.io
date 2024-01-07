function getBrowser() {
    if( navigator.userAgent.indexOf("Chrome") != -1 ) {
        return "Chrome";
  } else if( navigator.userAgent.indexOf("Opera") != -1 ) {
        return "Opera";
  } else if( navigator.userAgent.indexOf("MSIE") != -1 ) {
        return "IE";
  } else if( navigator.userAgent.indexOf("Firefox") != -1 ) {
        return "Firefox";
  } else {
        return "unknown";
  }
}

    if (getBrowser() !== "Firefox") {
        document.getElementById("browserInfo").innerHTML = "=( . w . )=  _" } 
    else {
        document.getElementById("browserInfo").innerHTML = "=( . w . )=_"; }
