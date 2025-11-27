(function ($) {
  $(document).ready(function() {

    $('.btn-delete-departments').click(function() {
      var departmentId = $(this).data('id');
      var departmentName = $(this).data('name');
      if (confirm('Bạn có chắc muốn xóa phòng ban "' + departmentName + '" không? , Khi bạn xóa đồng nghĩa việc xóa tất cả nhân viên phòng ban đó.')) {
        window.location.href = '/departments/delete/' + departmentId;
      }
    });


$(".btn-edit-department1").click(function(e) {
        e.preventDefault();

        var id   = $(this).data("id");
        var name = $(this).data("name");
        var desc = $(this).data("desc");

        $("#edit-department-id").val(id);
        $("#edit-department-name").val(name);
        $("#edit-department-desc").val(desc);

        $("#adddepartment .modal-title").text("Cập nhật phòng ban");
        $("#adddepartment .form-buttons button").html("<i class='fa fa-check'></i> Cập nhật");
        $("#adddepartment button[type=submit]").val("Cập nhật");
        $("#adddepartment").modal("show");
        $("#adddepartment form").off("submit").on("submit", function(e) {
            if (!confirm("Vui lòng kiểm tra lại thông tin phòng ban trước khi cập nhật!")) {
                e.preventDefault();
                return false;
            }
        });
    });




    $(".bnt-add-department1").click(function(e) {
        e.preventDefault(); 
        $("[name='department_id']").val(0);
        $("[name='department_name']").val('');
        $("[name='department_desc']").val('');
        $("#adddepartment").css({ "display": "flex", "align-items": "center" });
        $("#adddepartment").modal("show");
        $("#adddepartment .modal-title").text("Thêm mới phòng ban");
        $("#adddepartment button[type=submit]").val("Thêm mới");
        
    });

  });
})(jQuery);
