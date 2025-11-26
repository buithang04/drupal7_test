<div class="students-extra-wrapper">
  <h1>Thông tin sinh viên</h1>

  <?php if (!empty($extra)): ?>
    <table class="student-extra-table">
      <tr>
        <th>Avatar</th>
        <td>
          <?php 
          if (!empty($extra['avatar_fid'])) {
            $file = file_load($extra['avatar_fid']);
            if ($file && !empty($file->uri)) {
              $url = file_create_url($file->uri);
              echo '<img src="' . $url . '" alt="Avatar" style="max-width:100px; max-height:100px;">';
            }
          } else {
            echo 'Chưa có avatar';
          }
          ?>
        </td>
      </tr>
      <tr>
        <th>Tên sinh viên</th>
        <td><?php echo htmlspecialchars($extra['student_name']); ?></td>
      </tr>
      <tr>
        <th>SĐT</th>
        <td><?php echo htmlspecialchars($extra['phone']); ?></td>
      </tr>
      <tr>
        <th>Email</th>
        <td><?php echo htmlspecialchars($extra['email']); ?></td>
      </tr>
      <tr>
        <th>Địa chỉ</th>
        <td><?php echo htmlspecialchars($extra['address']); ?></td>
      </tr>
            <tr>
        <th>Tên của bố</th>
        <td><?php echo htmlspecialchars($extra['father_name']); ?></td>
      </tr>
            <tr>
        <th>SĐT của bố</th>
        <td><?php echo htmlspecialchars($extra['father_phone']); ?></td>
      </tr>
            <tr>
        <th>Tên của mẹ</th>
        <td><?php echo htmlspecialchars($extra['mother_name']); ?></td>
      </tr>
            <tr>
        <th>SĐT của mẹ</th>
        <td><?php echo htmlspecialchars($extra['mother_phone']); ?></td>
      </tr>
    </table>

    <button type="button" class="btn-edit-student-extra" 
            data-id="<?php echo $extra['student_id']; ?>" 
            data-phone="<?php echo htmlspecialchars($extra['phone']); ?>" 
            data-email="<?php echo htmlspecialchars($extra['email']); ?>" 
            data-address="<?php echo htmlspecialchars($extra['address']); ?>" 
            data-father_name="<?php echo htmlspecialchars($extra['father_name']); ?>"
            data-father_phone="<?php echo htmlspecialchars($extra['father_phone']); ?>"
            data-mother_name="<?php echo htmlspecialchars($extra['mother_name']); ?>"
            data-mother_phone="<?php echo htmlspecialchars($extra['mother_phone']); ?>"
            data-avatar-fid="<?php echo $extra['avatar_fid']; ?>"
            data-toggle="modal" data-target="#student-extra-modal">
      <i class="fa fa-edit"></i> Chỉnh sửa
    </button>

  <?php else: ?>
    <p>Không có thông tin sinh viên.</p>
  <?php endif; ?>
</div>

<div id="student-extra-modal" class="modal fade" role="dialog">
  <div class="modal-dialog">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal">&times;</button>
        <h4 class="modal-title">Thông tin sinh viên</h4>
      </div>
      <div class="modal-body">
        <?php
          if (!empty($extra['student_id'])) {
            $form = drupal_get_form("cassiopeia_student_extra_form", $extra['student_id']);
            if($form){
              print drupal_render($form);
            }
          }
        ?>
      </div>
    </div>
  </div>
</div>

<p><a href="<?php echo url('quan-ly-sinhvien'); ?>">&laquo; Quay lại danh sách sinh viên</a></p>
