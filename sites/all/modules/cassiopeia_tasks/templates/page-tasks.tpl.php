<?php
drupal_add_css(drupal_get_path('module', 'cassiopeia_tasks') . '/css/tasks.css');
drupal_add_js(drupal_get_path('module', 'cassiopeia_tasks') . '/js/tasks.js');
?>

<div class="tasks-wrapper">
  <h1>Danh sách dự án</h1>
  <br>
  <button type="button" class="btn-green btn-add-task">
    <span class="fa fa-plus"></span>
    Thêm mới dự án
  </button>
  <br>
  <table class="tasks-table">
    <thead>
      <tr>
        <th>STT</th>
        <th>Tên dự án</th>
        <th>Mô tả</th>
        <th>Phòng ban</th>
        <th>Actions</th>
      </tr>
    </thead>
    <tbody>
      <?php 
      $stt = 1;
      if (!empty($tasks) && is_array($tasks)):
          foreach ($tasks as $task): 
      ?>
      <tr>
        <td><?php echo $stt++; ?></td>
        <td><?php echo htmlspecialchars($task->task_name); ?></td>
        <td><?php echo htmlspecialchars($task->task_desc); ?></td>
        <td><?php echo htmlspecialchars($task->department_name); ?></td>
        <td>
          <button type="button" 
                  class="btn-edit-task" 
                  data-id="<?php echo $task->task_id; ?>" 
                  data-name="<?php echo htmlspecialchars($task->task_name); ?>" 
                  data-desc="<?php echo htmlspecialchars($task->task_desc); ?>"
                  data-department-id="<?php echo $task->department_id; ?>"
                  title="Sửa dự án">
              <i class="far fa-pen-to-square fa-fw"></i>
          </button>
          <button type="button" class="btn-delete-task" 
                  data-id="<?php echo $task->task_id; ?>" 
                  data-name="<?php echo htmlspecialchars($task->task_name); ?>" 
                  title="Xóa dự án">
              <i class="far fa-trash-can fa-fw"></i>
          </button>
        </td>
      </tr>
      <?php 
          endforeach; 
      else: 
      ?>
      <tr>
        <td colspan="5">Không có dự án nào.</td>
      </tr>
      <?php endif; ?>
    </tbody>
  </table>
</div>

<div id="addtask" class="modal fade" role="dialog">
  <div class="modal-dialog">
      <div class="modal-content">
          <div class="modal-header">
              <button type="button" class="close" data-dismiss="modal">&times;</button>
              <h4 class="modal-title">t</h4>
          </div>
          <div class="modal-body">
              <?php
              $cassiopeia_tasks_form = drupal_get_form("cassiopeia_tasks_form");
              if (!empty($cassiopeia_tasks_form)) {
                  $cassiopeia_tasks_form = drupal_render($cassiopeia_tasks_form);
                  print($cassiopeia_tasks_form);
              }
              ?>
          </div>
      </div>
  </div>
</div>
