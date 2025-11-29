(function ($) {
  Drupal.behaviors.cassiopeiaReports = {
    attach: function (context, settings) {

      $(".report-filter select", context).once("filter-change").on("change", function () {
        $(this).closest("form").submit();
      });


      $(".btn-reset", context).once("reset-btn").on("click", function (e) {
        e.preventDefault();
        window.location.href = window.location.pathname;
      });

      $(".task-item > strong", context).once("toggle-emp").css("cursor", "pointer").on("click", function () {
        $(this).siblings(".employee-list").slideToggle(200);
      });

    }
  };
})(jQuery);
