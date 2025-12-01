(function ($) {

  $("th.sort").click(function () {
    let header = $(this);
    let table = header.closest("table");
    let tbody = table.find("tbody").length ? table.find("tbody") : table;
    let sortField = header.data("sort");
    let direction = header.data("direction") === "ASC" ? 1 : -1;

    let rows = tbody.find("tr").slice(1).get(); 

    rows.sort(function (a, b) {
      let x = $(a).find(`[data-${sortField}]`).text().toLowerCase();
      let y = $(b).find(`[data-${sortField}]`).text().toLowerCase();

      if (sortField === "count") {
        return (parseInt(x) - parseInt(y)) * direction;
      }


      return x.localeCompare(y) * direction;
    });


    $.each(rows, function (_, row) {
      tbody.append(row);
    });


    header.data("direction", direction === 1 ? "DESC" : "ASC");
  });


  $("#search").on("keyup", function () {
    let keyword = $(this).val().toLowerCase();

    $(".table-report tr").each(function (i) {
      if (i === 0) return; 
      
      let name = $(this).find("[data-department]").text().toLowerCase();
      $(this).toggle(name.includes(keyword));
    });
  });


  $(".filter-letter").click(function () {
    let letter = $(this).data("letter");

    $(".filter-letter").removeClass("active");
    $(this).addClass("active");

    $(".table-report tr").each(function (i) {
      if (i === 0) return; 

      let name = $(this).find("[data-department]").text().trim();

      if (letter === "all") {
        $(this).show();
      } else {
        $(this).toggle(name.startsWith(letter));
      }
    });
  });

})(jQuery);
