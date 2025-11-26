<div class="classes-wrapper">
  <h1>Thông tin lớp: <?php echo htmlspecialchars($class_name); ?></h1>
  <br>
  <h3>Giáo viên: <?php echo htmlspecialchars($teacher_name); ?></h3>
<br>
  <table class="classes-table">
    <thead>
      <tr>
        <th>STT</th>
        <th>Tên sinh viên</th>
        <th>Giới tính</th>
        <th>Ngày sinh</th>
      </tr>
    </thead>
    <tbody>
      <?php
      if (count($classinfo) === 1 && empty($classinfo[0]->student_id)) {
          echo '<tr><td colspan="4"><em>Chưa có học sinh</em></td></tr>';
      } else {
          $stt = 1;
          foreach ($classinfo as $student) {
              if (!empty($student->student_id)) {
                  echo '<tr>';
                  echo '<td>' . $stt++ . '</td>';
                  echo '<td>' . htmlspecialchars($student->student_name) . '</td>';
                  echo '<td>' . htmlspecialchars($student->gender) . '</td>';
                  echo '<td>' . htmlspecialchars($student->birthdate) . '</td>';
                  echo '</tr>';
              }
          }
      }
      ?>
    </tbody>
  </table>

  <p><a href="<?php echo url('quan-ly-sinhvien'); ?>">&laquo; Quay lại danh sách sinh viên</a></p>
</div>
