(function ($) {
  $(document).ready(function() {


    $('.btn-delete-classes').click(function() {
      var classId = $(this).data('id');
      var className = $(this).data('name');
      if (confirm('Bạn có chắc muốn xóa lớp "' + className + '" không?')) {
        window.location.href = '/classes/delete/' + classId;
      }
    });


    $(".bnt-add-class12").click(function(e) {
        e.preventDefault(); 
        $("[name='class_id']").val(0);
        $("[name='class_name']").val('');
        $("[name='teacher_name']").val('');
        $("#addclass").css({ "display": "flex", "align-items": "center" });
        $("#addclass").modal("show");
        $("#addclass .modal-title").text("Thêm mới lớp");
        $("#addclass button[type=submit]").val("Thêm mới");
        
    });

  });
})(jQuery);
