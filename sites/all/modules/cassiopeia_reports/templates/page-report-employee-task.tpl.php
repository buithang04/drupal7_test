<?php
drupal_add_css(drupal_get_path('module', 'cassiopeia_reports') . '/css/reports.css');
drupal_add_css(drupal_get_path('module', 'cassiopeia_reports') . '/js/report-employee-task.js');

?>

<div class="report-employee-task">

  <h2>Báo cáo nhân viên theo dự án</h2>

  <?php if (!empty($records)): ?>

    <?php foreach ($records as $row): ?>

      <div class="department-block">

        <h3><?php print $row->department_name; ?></h3>

        <?php
          $task_ids    = $row->task_ids ? explode(',', $row->task_ids) : [];
          $task_names  = $row->task_names ? explode(',', $row->task_names) : [];
          $emp_ids     = $row->employee_ids ? explode(',', $row->employee_ids) : [];
          $emp_names   = $row->employee_names ? explode(',', $row->employee_names) : [];
        ?>

        <?php if (empty($task_ids)): ?>
          <p><em>Không có dự án nào.</em></p>

        <?php else: ?>

          <ul class="task-list">
            <?php foreach ($task_ids as $i => $task_id): ?>
              <li class="task-item">

                <strong>Dự án:</strong> <?php print $task_names[$i]; ?>

                <?php if (!empty($emp_ids)): ?>
                  <ul class="employee-list">
                    <?php foreach ($emp_names as $ename): ?>
                      <li class="employee-item"><?php print $ename; ?></li>
                    <?php endforeach; ?>
                  </ul>
                <?php else: ?>
                  <p><em>Không có nhân viên nào.</em></p>
                <?php endif; ?>

              </li>
            <?php endforeach; ?>
          </ul>

        <?php endif; ?>

      </div>

      <hr>

    <?php endforeach; ?>

  <?php else: ?>
    <p><em>Không có dữ liệu báo cáo.</em></p>
  <?php endif; ?>
</div>
