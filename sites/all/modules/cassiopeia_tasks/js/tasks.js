(function ($) {
  $(document).ready(function() {

    $('.btn-delete-task').click(function() {
      var taskId = $(this).data('id');
      var taskName = $(this).data('name');
      if (confirm('Bạn có chắc muốn xóa dự án "' + taskName + '" không?')) {
        window.location.href = '/tasks/delete/' + taskId;
      }
    });

    $(".btn-edit-task").click(function(e) {
        e.preventDefault();

        var id         = $(this).data("id");
        var name       = $(this).data("name");
        var desc       = $(this).data("desc");
        var department = $(this).data("department-id");

        $("#edit-task-id").val(id);
        $("#edit-task-name").val(name);
        $("#edit-task-desc").val(desc);
        $("#edit-task-department").val(department).trigger('change');

        $("#addtask .modal-title").text("Cập nhật dự án");
        $("#addtask .form-buttons button").html("<i class='fa fa-check'></i> Cập nhật");
        $("#addtask button[type=submit]").val("Cập nhật");
        $("#addtask").modal("show");

        $("#addtask form").off("submit").on("submit", function(e) {
            if (!confirm("Vui lòng kiểm tra lại thông tin dự án trước khi cập nhật!")) {
                e.preventDefault();
                return false;
            }
        });
    });

    $(".btn-add-task").click(function(e) {
        e.preventDefault(); 
        $("[name='task_id']").val(0);
        $("[name='task_name']").val('');
        $("[name='task_desc']").val('');
        $("[name='department_id']").val('');

        $("#addtask").css({ "display": "flex", "align-items": "center" });
        $("#addtask").modal("show");
        $("#addtask .modal-title").text("Thêm mới dự án");
        $("#addtask button[type=submit]").val("Thêm mới");
    });

  });
})(jQuery);
