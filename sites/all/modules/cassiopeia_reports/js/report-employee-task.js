(function ($) {

  $("#search-report").on("keyup", function () {
    let keyword = $(this).val().toLowerCase();

    $(".department-block").each(function () {
      let text = $(this).text().toLowerCase();
      $(this).toggle(text.includes(keyword));
    });
  });

  $(".filter-letter").click(function () {
    let letter = $(this).data("letter");

    $(".filter-letter").removeClass("active");
    $(this).addClass("active");

    $(".department-block").each(function () {
      let name = $(this).data("department");

      if (letter === "all") {
        $(this).show();
      } else {
        $(this).toggle(name.startsWith(letter.toLowerCase()));
      }
    });
  });

  $(".accordion-header").click(function () {
    $(this).toggleClass("open");
    $(this).next(".accordion-content").slideToggle(200);
  });


  $(".task-header").click(function () {
    $(this).toggleClass("open");
    $(this).next(".task-content").slideToggle(200);
  });

})(jQuery);
