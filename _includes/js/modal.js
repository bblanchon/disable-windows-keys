(function() {
  var btns = document.querySelectorAll("[data-toggle=modal]")
  for (var i=0; i<btns.length; i++) {
    var btn = btns[i]
    btn.addEventListener("click", function(e) {
      var t = document.querySelector(btn.getAttribute("href"))
      t.style.visibility = 'visible';
      e.preventDefault();
    });
  }
})();

(function() {
  var btns = document.querySelectorAll("[data-dismiss=modal]")
  for (var i=0; i<btns.length; i++) {
    var btn = btns[i]
    btn.addEventListener("click", function(e) {
      var t = document.querySelector(".modal")
      t.style.visibility = 'hidden';
      e.preventDefault();
    });
  }
})();
