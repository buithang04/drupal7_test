<?php
drupal_add_css(drupal_get_path('module', 'cassiopeia_reports') . '/css/reports.css');
drupal_add_js(drupal_get_path('module', 'cassiopeia_reports') . '/js/report-employee-task.js');
?>

<div class="report-employee-task">

  <h2>Báo cáo nhân viên theo dự án</h2>

  <!-- THANH TÌM KIẾM -->
  <div class="search-filter-wrapper">
    <input type="text" id="search-report" placeholder="Tìm kiếm phòng ban hoặc dự án...">
  </div>

  <!-- LỌC THEO CHỮ CÁI -->
  <div class="filter-letters">
    <span class="filter-letter active" data-letter="all">Tất cả</span>
    <?php foreach (range('A', 'Z') as $char): ?>
      <span class="filter-letter" data-letter="<?php print $char; ?>"><?php print $char; ?></span>
    <?php endforeach; ?>
  </div>

  <?php if (!empty($records)): ?>

    <?php foreach ($records as $row): ?>

      <div class="department-block accordion-item" data-department="<?php print strtolower($row->department_name); ?>">

        <!-- TIÊU ĐỀ PHÒNG BAN -->
        <h3 class="accordion-header">
          <span class="accordion-title"><?php print $row->department_name; ?></span>
          <span class="accordion-icon">+</span>
        </h3>

        <div class="accordion-content">

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
                <li class="task-item accordion-sub-item">

                  <div class="task-header">
                    <strong>Dự án:</strong> <?php print $task_names[$i]; ?>
                    <span class="accordion-sub-icon">+</span>
                  </div>

                  <div class="task-content">
                    <?php if (!empty($emp_ids)): ?>
                      <ul class="employee-list">
                        <?php foreach ($emp_names as $ename): ?>
                          <li class="employee-item"><?php print $ename; ?></li>
                        <?php endforeach; ?>
                      </ul>
                    <?php else: ?>
                      <p><em>Không có nhân viên nào.</em></p>
                    <?php endif; ?>
                  </div>

                </li>
              <?php endforeach; ?>
            </ul>

          <?php endif; ?>

        </div>

      </div>

    <?php endforeach; ?>

  <?php else: ?>
    <p><em>Không có dữ liệu báo cáo.</em></p>
  <?php endif; ?>
</div>

<div class="pagination-wrapper">
  <?php print theme('pager'); ?>
</div>
