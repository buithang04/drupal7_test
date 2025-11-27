(function ($) {
  $(document).ready(function() {


    $('.btn-delete-employee').click(function() {
      var employeeId = $(this).data('id');
      var employeeName = $(this).data('name');
      if (confirm('Bạn có chắc muốn xóa nhân viên "' + employeeName + '" không?')) {
        window.location.href = '/employees/delete/' + employeeId;
      }
    });


    $(".btn-edit-employee1").click(function(e) {
        e.preventDefault();

        var id         = $(this).data("id");
        var name       = $(this).data("name");
        var position   = $(this).data("position");
        var department = $(this).data("department-id");
        

        $("#edit-employee-id").val(id);
        $("#edit-employee-name").val(name);
        $("#edit-position").val(position);
        $("#edit-employee-department").val(department).trigger('change');

        $("#addemployee .modal-title").text("Cập nhật nhân viên");
        $("#addemployee .form-buttons button").html("<i class='fa fa-check'></i> Cập nhật");
        $("#addemployee button[type=submit]").val("Cập nhật");
        $("#addemployee").modal("show");

        $("#addemployee form").off("submit").on("submit", function(e) {
            if (!confirm("Vui lòng kiểm tra lại thông tin nhân viên trước khi cập nhật!")) {
                e.preventDefault();
                return false;
            }
        });
    });

    $(".bnt-add-employee1").click(function(e) {
        e.preventDefault(); 
        $("[name='employee_id']").val(0);
        $("[name='employee_name']").val('');
        $("[name='position']").val('');
        $("[name='department_id']").val('');

        $("#addemployee").css({ "display": "flex", "align-items": "center" });
        $("#addemployee").modal("show");
        $("#addemployee .modal-title").text("Thêm mới nhân viên");
        $("#addemployee button[type=submit]").val("Thêm mới");
    });

  });
})(jQuery);
