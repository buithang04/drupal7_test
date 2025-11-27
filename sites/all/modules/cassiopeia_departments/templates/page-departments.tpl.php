<?php
    drupal_add_css(drupal_get_path('module', 'cassiopeia_departments') . '/css/departments.css');
    drupal_add_js(drupal_get_path('module', 'cassiopeia_departments') . '/js/departments.js');
     ?>


<div class="departments-wrapper">
  <h1>Danh sách phòng ban</h1>
  <br>
  <button type="button" class="btn-green bnt-add-department1">
                <span class="fa fa-plus"></span>
                Thêm mới phòng ban
            </button>
  <br>
  <table class="departments-table">
    <thead>
      <tr>
        <th>STT</th>
        <th>Tên Phòng ban</th>
        <th>Mô tả phòng ban</th>
        <th>Actions</th>
      </tr>
    </thead>
    <tbody>
      <?php 
      $stt = 1;
      if (!empty($departments) && is_array($departments)):
          foreach ($departments as $department): 
      ?>
      <tr>
        <td><?php echo $stt++; ?></td>
        <td><?php echo $department->department_name; ?></td>
        <td><?php echo $department->department_desc; ?></td>
        <td>
          <button type="button" 
                  class="btn-edit-department1" 
                  data-id="<?php echo $department->department_id; ?>" 
                  data-name="<?php echo htmlspecialchars($department->department_name); ?>" 
                  data-desc="<?php echo htmlspecialchars($department->department_desc); ?>" 
                  title="Sửa phòng ban">
              <i class="far fa-pen-to-square fa-fw"></i>
          </button>
          <button type="button" class="btn-delete-departments" data-id="<?php echo $department->department_id; ?>" data-name="<?php echo htmlspecialchars($department->department_name); ?>" title="Xóa phòng ban"><i class="far fa-trash-can fa-fw"></i></button>
        </td>
      </tr>

      <?php 
          endforeach; 
      else: 
      ?>
      <tr>
        <td colspan="4">Không có phòng ban nào.</td>
      </tr>
      <?php endif; ?>
    </tbody>
  </table>
</div>



  <div id="adddepartment" class="modal fade" role="dialog">
    <div class="modal-dialog">
        <!-- Modal content-->
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal">&times;</button>
                <h4 class="modal-title">T</h4>
            </div>
            <div class="modal-body">
                <?php
                $cassiopeia_department_form = drupal_get_form("cassiopeia_department_form");
                if(!empty($cassiopeia_department_form)){
                    $cassiopeia_department_form = drupal_render($cassiopeia_department_form);
                    print($cassiopeia_department_form);
                }
                ?>
            </div>
        </div>

    </div>
</div>