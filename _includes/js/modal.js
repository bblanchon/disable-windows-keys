(function() {
  let btns = document.querySelectorAll("[data-toggle=modal]")
  for (let i=0; i<btns.length; i++) {
    let btn = btns[i]
    let target = document.querySelector(btn.getAttribute("href"))
    btn.addEventListener("click", function(e) {
      target.style.visibility = 'visible'
      e.preventDefault();
    });
  }
})();

(function() {
  let btns = document.querySelectorAll("[data-dismiss=modal]")
  for (let i=0; i<btns.length; i++) {
    let btn = btns[i]
    btn.addEventListener("click", function(e) {
      let modals = document.querySelectorAll(".modal")
      for (let j=0; j<modals.length; j++) {
        modals[j].style.visibility = 'hidden'
      }
      e.preventDefault();
    });
  }
})();
