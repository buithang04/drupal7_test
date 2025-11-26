(function ($) {
  $(document).ready(function() {


   $('.btn-delete-student').click(function() {
    var studentId = $(this).data('id');
    var studentName = $(this).data('name');

    if (confirm('Bạn có chắc muốn xóa sinh viên "' + studentName + '" không?')) {
        window.location.href = '/students/delete/' + studentId;
    }
  });


   $(".btn-add-student12").click(function(e) {
      e.preventDefault(); 
      $("#edit-student-id").val(0);
      $("#edit-student-name").val('');
      $("#edit-gender").val('');
      $("#edit-birthdate").val('');
      $("#edit-class-id").val('');

      $("#addstudent .modal-title").text("Thêm mới sinh viên");
      $("#addstudent .form-buttons button").html("<i class=\"fa fa-check\"></i> Thêm mới");
      $("#addstudent button[type=submit]").val("Thêm mới");

      $("#addstudent").modal("show");
  });


$(".btn-edit-student12").click(function(e) {
    e.preventDefault();

    var id        = $(this).data("id");
    var name      = $(this).data("name");
    var gender    = $(this).data("gender");
    var birthdate = $(this).data("birthdate");
    var classId   = $(this).data("class-id");

    $("#edit-student-id").val(id);
    $("#edit-student-name").val(name);
    $("#edit-gender").val(gender);
    $("#edit-class-id").val(classId);

    if (birthdate) {
    $("#edit-birthdate").val(birthdate);
} else {
    $("#edit-birthdate").val('');
}

    $("#addstudent .modal-title").text("Cập nhật sinh viên");
    $("#addstudent .form-buttons button").html("<i class='fa fa-check'></i> Cập nhật");
    $("#addstudent button[type=submit]").val("Cập nhật");
    $("#addstudent").modal("show");
    $("#addstudent button[type=submit]").on("submit", function(e) {
    if (!confirm("Vui lòng kiểm tra lại thông tin cá nhân trước khi cập nhật!")) {
        e.preventDefault();
        return false;
    }
});
});



  
  });
})(jQuery);
