<?php
drupal_add_css(drupal_get_path('module', 'cassiopeia_reports') . '/css/reports.css');
?>
<table class="table-report">
  <tr>
    <th>STT</th>
    <th>Phòng ban</th>
    <th>Số lượng nhân viên</th>
  </tr>

  <?php $i = 1; ?>
  <?php foreach ($records as $row): ?>
    <tr>
      <td><?php print $i++; ?></td>
      <td><?php print $row->department_name; ?></td>
      <td><?php print $row->total_employees; ?></td>
    </tr>
  <?php endforeach; ?>
</table>