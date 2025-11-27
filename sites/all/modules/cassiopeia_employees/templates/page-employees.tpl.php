<?php
drupal_add_css(drupal_get_path('module', 'cassiopeia_employees') . '/css/employees.css');
drupal_add_js(drupal_get_path('module', 'cassiopeia_employees') . '/js/employees.js');
?>

<div class="employees-wrapper">
  <h1>Danh sách nhân viên</h1>
  <br>
  <button type="button" class="btn-green bnt-add-employee1">
    <span class="fa fa-plus"></span>
    Thêm mới nhân viên
  </button>
  <br>
  <table class="employees-table">
    <thead>
      <tr>
        <th>STT</th>
        <th>Tên nhân viên</th>
        <th>Chức vụ</th>
        <th>Phòng ban</th>
        <th>Actions</th>
      </tr>
    </thead>
    <tbody>
      <?php 
      $stt = 1;
      if (!empty($employees) && is_array($employees)):
          foreach ($employees as $employee): 
      ?>
      <tr>
        <td><?php echo $stt++; ?></td>
        <td><?php echo $employee->employee_name; ?></td>
        <td><?php echo $employee->position; ?></td>
        <td><?php echo $employee->department_name; ?></td>
        <td>
          <button type="button" 
                  class="btn-edit-employee1" 
                  data-id="<?php echo $employee->employee_id; ?>" 
                  data-name="<?php echo htmlspecialchars($employee->employee_name); ?>" 
                  data-position="<?php echo htmlspecialchars($employee->position); ?>"
                  data-department-id="<?php echo $employee->department_id; ?>"
                  title="Sửa nhân viên">
              <i class="far fa-pen-to-square fa-fw"></i>
          </button>
          <button type="button" class="btn-delete-employee" 
                  data-id="<?php echo $employee->employee_id; ?>" 
                  data-name="<?php echo htmlspecialchars($employee->employee_name); ?>" 
                  title="Xóa nhân viên">
              <i class="far fa-trash-can fa-fw"></i>
          </button>
        </td>
      </tr>
      <?php 
          endforeach; 
      else: 
      ?>
      <tr>
        <td colspan="5">Không có nhân viên nào.</td>
      </tr>
      <?php endif; ?>
    </tbody>
  </table>
</div>

<div id="addemployee" class="modal fade" role="dialog">
  <div class="modal-dialog">
      <!-- Modal content-->
      <div class="modal-content">
          <div class="modal-header">
              <button type="button" class="close" data-dismiss="modal">&times;</button>
              <h4 class="modal-title">t</h4>
          </div>
          <div class="modal-body">
              <?php
              $cassiopeia_employee_form = drupal_get_form("cassiopeia_employee_form");
              if (!empty($cassiopeia_employee_form)) {
                  $cassiopeia_employee_form = drupal_render($cassiopeia_employee_form);
                  print($cassiopeia_employee_form);
              }
              ?>
          </div>
      </div>
  </div>
</div>
