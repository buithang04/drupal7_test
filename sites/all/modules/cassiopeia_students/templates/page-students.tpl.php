


<div class="classes-wrapper">
  <h1>Danh sách lớp</h1>
  <br>
  <button type="button" class="btn-green btn-add-student12">
                <span class="fa fa-plus"></span>
                Thêm mới sinh viên
            </button>
  <br>
  <table class="classes-table">
    <thead>
      <tr>
        <th>STT</th>
        <th>Tên sinh viên</th>
        <th>Giới tính</th>
        <th>Ngày sinh</th>
        <th>Lớp</th>
        <th>Actions</th>
      </tr>
    </thead>
    <tbody>
      <?php 
      $stt = 1;
      if (!empty($students) && is_array($students)):
          foreach ($students as $student): 
      ?>
      <tr>
        <td><?php echo $stt++; ?></td>
        <td><?php echo $student->student_name; ?></td>
        <td><?php echo $student->gender; ?></td>
        <td><?php echo date('Y-m-d', strtotime($student->birthdate)); ?></td>
        <td>
            <a href="<?php echo url('thong-tin-lop/' . $student->class_id); ?>">
        <?php echo htmlspecialchars($student->class_name); ?>
            </a>
        </td>
        <td>
          <button type="button" 
                class="btn-edit-student12"
                data-id="<?php echo $student->student_id; ?>"
                data-name="<?php echo htmlspecialchars($student->student_name); ?>"
                data-gender="<?php echo $student->gender; ?>"
                data-birthdate="<?php echo $student->birthdate; ?>"
                data-class-id="<?php echo $student->class_id; ?>"
                data-class-name="<?php echo htmlspecialchars($student->class_name); ?>">
            <i class="fa fa-edit"></i>
        </button>
          <button type="button" 
        class="btn-delete-student"
        data-id="<?php echo $student->student_id; ?>"
        data-name="<?php echo htmlspecialchars($student->student_name); ?>"
        title="Xóa sinh viên">
        <i class="far fa-trash-can fa-fw"></i>
        </button>
          <button type="button" 
                class="btn-view-student-extra"
                onclick="location.href='<?php echo url('thong-tin-ca-nhan/' . $student->student_id); ?>'">
          <i class="fa fa-user"></i> Thông tin
        </button>
        </td>
      </tr>

      <?php 
          endforeach; 
      else: 
      ?>
      <tr>
        <td colspan="4">Không có sinh viên nào.</td>
      </tr>
      <?php endif; ?>
    </tbody>
  </table>
</div>



  <div id="addstudent" class="modal fade" role="dialog">
    <div class="modal-dialog">
        <!-- Modal content-->
        <div class="modal-content">
            <div class="modal-header">
                <button type="button" class="close" data-dismiss="modal">&times;</button>
                <h4 class="modal-title">T</h4>
            </div>
            <div class="modal-body">
                <?php
                $cassiopeia_student_form = drupal_get_form("cassiopeia_student_form");
                if(!empty($cassiopeia_student_form)){
                    $cassiopeia_student_form = drupal_render($cassiopeia_student_form);
                    print($cassiopeia_student_form);
                }
                ?>
            </div>
        </div>

    </div>
</div>